#include <stdlib.h>
#include "processor.h"

void processor_init(Processor *p) {
    EncodedInstruction *dummy_instructions = calloc(1024, sizeof(EncodedInstruction));
    dummy_instructions[0] = 0x14000000;
    bus_init(&p->bus);
    for (int i = 0; i < NUM_CORES; i++) {
        core_init(&p->cores[i], dummy_instructions, &p->bus);
    }
}

void processor_destroy(Processor *p) {
    for (int i = 0; i < NUM_CORES; i++) {
        core_destroy(&p->cores[i]);
    }
    bus_destroy(&p->bus);
}

bool processor_is_done(const Processor *p) {
    for (int i = 0; i < NUM_CORES; i++) {
        if (!p->cores[i].is_done) return false;
    }
    return true;
}

void processor_cycle(Processor *p) {
    for (int i = 0; i < NUM_CORES; i++) {
        Core *core = &p->cores[i];
        if (core->is_done) continue;
        core_begin_cycle(core);
    }
    bus_cycle(&p->bus);
    for (int i = 0; i < NUM_CORES; i++) {
        Core *core = &p->cores[i];
        if (core->is_done) continue;
        core_finish_cycle(core);
    }
}
