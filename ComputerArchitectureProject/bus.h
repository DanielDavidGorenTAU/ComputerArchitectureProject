#pragma once

#include "memory.h"

typedef struct {
    Memory memory;
} Bus;

void bus_init(Bus *bus);

void bus_destroy(Bus *bus);

void bus_cycle(Bus *bus);
