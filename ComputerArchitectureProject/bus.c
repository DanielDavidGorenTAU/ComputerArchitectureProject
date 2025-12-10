#include "bus.h"

void bus_init(Bus *bus) {
    memory_init(&bus->memory);
}

void bus_destroy(Bus *bus) {
    memory_destroy(&bus->memory);
}

void bus_cycle(Bus *bus) {}
