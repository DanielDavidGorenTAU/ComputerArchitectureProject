#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t regs[16];
    uint32_t pc;
    bool is_done;
} Core;

void core_init(Core *c);

void core_destroy(Core *c);

void core_cycle(Core *c);
