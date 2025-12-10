#pragma once

#include <stdbool.h>
#include "core.h"
#include "bus.h"

#define NUM_CORES 4

typedef struct {
    Core cores[NUM_CORES];
    Bus bus;
} Processor;

void processor_init(Processor *p);

void processor_destroy(Processor *p);

bool processor_is_done(const Processor *p);

void processor_cycle(Processor *p);
