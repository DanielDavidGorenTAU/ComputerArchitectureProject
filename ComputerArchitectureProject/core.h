#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "buffers.h"
#include "cache.h"

#define NUM_REGS 16

typedef struct {
    uint32_t regs[NUM_REGS];
    uint16_t pc;
    const EncodedInstruction *instruction_memory;
    FetchResult fetch_output;
    FetchResult decode_input;
    DecodeResult decode_output;
    DecodeResult execute_input;
    ExecuteResult execute_output;
    ExecuteResult mem_input;
    MemResult mem_output;
    MemResult write_back_input;
    Cache cache;
    bool is_done;
} Core;

void core_init(Core *c, const EncodedInstruction *instruction_memory, Bus *bus);

void core_destroy(Core *c);

void core_begin_cycle(Core *c);

void core_finish_cycle(Core *c);
