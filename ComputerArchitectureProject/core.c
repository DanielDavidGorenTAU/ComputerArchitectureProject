#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "core.h"
#include "util.h"

#define PC_MASK 0x3ff

void core_init(Core *c, const EncodedInstruction *instruction_memory, Bus *bus) {
    CLEAR(c->regs);
    c->pc = 0;
    c->instruction_memory = instruction_memory;
    CLEAR(c->decode_input);
    CLEAR(c->execute_input);
    CLEAR(c->mem_input);
    CLEAR(c->write_back_input);
    c->decode_input.pc = PC_STALL;
    c->execute_input.pc = PC_STALL;
    c->mem_input.pc = PC_STALL;
    c->write_back_input.pc = PC_STALL;
    cache_init(&c->cache, bus);
    c->is_done = false;
}

void core_destroy(Core *c) {
    cache_destroy(&c->cache);
}

static uint32_t get_reg(Core *c, uint8_t index, uint32_t immediate) {
    switch (index) {
    case 0:
        return 0;
    case 1:
        return immediate;
    default:
        assert(index < NUM_REGS);
        return c->regs[index];
    }
}

static void set_reg(Core *c, uint8_t index, uint32_t value) {
    if (index == 0 || index == 1) return;
    assert(index < NUM_REGS);
    c->regs[index] = value;
}

static void fetch(Core *c) {
    c->fetch_output.pc = c->pc;
    c->fetch_output.instruction = c->instruction_memory[c->pc];
    c->pc = (c->pc + 1) & PC_MASK;
}

static void decode(Core *c) {
    const FetchResult *input = &c->decode_input;
    DecodeResult *output = &c->decode_output;
    output->pc = input->pc;
    if (input->pc == PC_STALL) return;
    DecodedInstruction ins = instruction_decode(input->instruction);
    output->opcode = ins.opcode;
    output->rd_index = ins.rd;
    output->rd_value = get_reg(c, ins.rd, ins.immediate);
    output->rs_value = get_reg(c, ins.rs, ins.immediate);
    output->rt_value = get_reg(c, ins.rt, ins.immediate);
}

static void execute(Core *c) {
    const DecodeResult *input = &c->execute_input;
    ExecuteResult *output = &c->execute_output;
    output->pc = input->pc;
    output->opcode = input->opcode;
    if (input->pc == PC_STALL) return;
    output->rd_index = input->rd_index;
    output->rd_value = input->rd_value;
    switch (input->opcode) {
    case INSTRUCTION_ADD:
        output->value = input->rs_value + input->rt_value;
        break;
    case INSTRUCTION_SUB:
        output->value = input->rs_value - input->rt_value;
        break;
    case INSTRUCTION_AND:
        output->value = input->rs_value & input->rt_value;
        break;
    case INSTRUCTION_OR:
        output->value = input->rs_value | input->rt_value;
        break;
    case INSTRUCTION_XOR:
        output->value = input->rs_value ^ input->rt_value;
        break;
    case INSTRUCTION_MUL:
        output->value = input->rs_value * input->rt_value;
        break;
    case INSTRUCTION_SLL:
        output->value = input->rs_value << (input->rt_value & 0x1f);
        break;
    case INSTRUCTION_SRA:
        output->value = (uint32_t)((int32_t)input->rs_value >> (input->rt_value & 0x1f));
        break;
    case INSTRUCTION_BEQ:
    case INSTRUCTION_BNE:
    case INSTRUCTION_BLT:
    case INSTRUCTION_BGT:
    case INSTRUCTION_BLE:
    case INSTRUCTION_BGE:
    case INSTRUCTION_JAL:
        break;
    case INSTRUCTION_LW:
    case INSTRUCTION_SW:
        output->value = input->rs_value + input->rt_value;
        break;
    case INSTRUCTION_SRL:
        output->value = input->rs_value >> (input->rt_value & 0x1f);
        break;
    case INSTRUCTION_HALT:
        break;
    default:
        fprintf(stderr, "invalid opcode\n");
        exit(1);
    }
}

static void mem(Core *c) {
    const ExecuteResult *input = &c->mem_input;
    MemResult *output = &c->mem_output;
    output->pc = input->pc;
    output->opcode = input->opcode;
    output->rd_index = input->rd_index;
    if (input->pc == PC_STALL) return;
    switch (input->opcode) {
    case INSTRUCTION_LW:
        cache_begin_read(&c->cache, input->value);
        break;
    case INSTRUCTION_SW:
        cache_begin_write(&c->cache, input->value, input->rd_value);
        break;
    default:
        output->value = input->value;
    }
}

static void write_back(Core *c) {
    const MemResult *input = &c->write_back_input;
    if (input->pc == PC_STALL) return;
    switch (input->opcode) {
    case INSTRUCTION_ADD:
    case INSTRUCTION_SUB:
    case INSTRUCTION_AND:
    case INSTRUCTION_OR:
    case INSTRUCTION_XOR:
    case INSTRUCTION_MUL:
    case INSTRUCTION_SLL:
    case INSTRUCTION_SRA:
    case INSTRUCTION_SRL:
    case INSTRUCTION_LW:
        c->regs[input->rd_index] = input->value;
        break;
    case INSTRUCTION_HALT:
        c->is_done = true;
        break;
    }
}

void core_begin_cycle(Core *c) {
    printf("CORE AT %p: cycle\n", c);
    if (c->is_done) return;
    if (!c->cache.is_busy) {
        fetch(c);
        decode(c);
        execute(c);
        mem(c);
        write_back(c);
    }
    cache_begin_cycle(&c->cache);
}

void core_finish_cycle(Core *c) {
    bool was_cache_busy = c->cache.is_busy;
    cache_finish_cycle(&c->cache);
    if (!c->cache.is_busy) {
        if (was_cache_busy) {
            c->mem_output.value = c->cache.data;
        }
        c->decode_input = c->fetch_output;
        c->execute_input = c->decode_output;
        c->mem_input = c->execute_output;
        c->write_back_input = c->mem_output;
    }
}
