#pragma once

#include "instruction.h"

// In every step of the pipeline, ff pc equals PC_STALL,
// skip this step.
#define PC_STALL 0xffff

typedef struct {
    uint16_t pc;
    EncodedInstruction instruction;
} FetchResult;

typedef struct {
    uint16_t pc;
    uint8_t opcode;
    uint8_t rd_index;
    uint32_t rd_value;
    uint32_t rs_value;
    uint32_t rt_value;
} DecodeResult;

typedef struct {
    uint16_t pc;
    uint8_t opcode;
    uint8_t rd_index;
    uint32_t rd_value;
    uint32_t value;
} ExecuteResult;

typedef struct {
    uint16_t pc;
    uint8_t opcode;
    uint8_t rd_index;
    uint32_t value;
} MemResult;
