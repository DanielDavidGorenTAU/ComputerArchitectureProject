#pragma once

#include <stdint.h>

typedef uint32_t EncodedInstruction;

typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    uint16_t immediate;
} DecodedInstruction;

typedef enum {
    INSTRUCTION_ADD = 0,
    INSTRUCTION_SUB = 1,
    INSTRUCTION_AND = 2,
    INSTRUCTION_OR = 3,
    INSTRUCTION_XOR = 4,
    INSTRUCTION_MUL = 5,
    INSTRUCTION_SLL = 6,
    INSTRUCTION_SRA = 7,
    INSTRUCTION_SRL = 8,
    INSTRUCTION_BEQ = 9,
    INSTRUCTION_BNE = 10,
    INSTRUCTION_BLT = 11,
    INSTRUCTION_BGT = 12,
    INSTRUCTION_BLE = 13,
    INSTRUCTION_BGE = 14,
    INSTRUCTION_JAL = 15,
    INSTRUCTION_LW = 16,
    INSTRUCTION_SW = 17,
    INSTRUCTION_HALT = 20,
} Opcode;

DecodedInstruction instruction_decode(EncodedInstruction ins);
