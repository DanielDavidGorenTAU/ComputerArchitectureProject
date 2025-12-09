#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "core.h"

void core_init(Core *c) {
    memset(&c->regs, 0, sizeof c->regs);
    c->pc = 0;
    c->is_done = false;
}

void core_destroy(Core *c) {}

void core_cycle(Core *c) {
    printf("CORE AT %p: cycle\n", c);
    c->is_done = true;
}
