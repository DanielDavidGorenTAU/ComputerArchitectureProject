#include "processor.h"

void processor_init(Processor *p) {
    for (int i = 0; i < NUM_CORES; i++) {
        core_init(&p->cores[i]);
    }
}

void processor_destroy(Processor *p) {
    for (int i = 0; i < NUM_CORES; i++) {
        core_destroy(&p->cores[i]);
    }
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
        core_cycle(core);
    }
}
