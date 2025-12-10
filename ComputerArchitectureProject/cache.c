#include <stdlib.h>
#include <assert.h>
#include "cache.h"

void cache_init(Cache *c, Bus *bus) {
    c->data_memory = calloc(CACHE_NUM_BLOCKS, sizeof(CacheBlock));
    c->tag_memory = calloc(CACHE_NUM_BLOCKS, sizeof(uint16_t));
    c->bus = bus;
    c->is_busy = false;
}

void cache_destroy(Cache *c) {
    free(c->data_memory);
    free(c->tag_memory);
}

void cache_begin_cycle(Cache *c) {}

void cache_finish_cycle(Cache *c) {}

void cache_begin_read(Cache *c, uint32_t address) {
    assert(!c->is_busy);
    c->current_address = address;
    c->is_busy = true;
}

void cache_begin_write(Cache *c, uint32_t address, uint32_t data) {
    assert(!c->is_busy);
    c->current_address = address;
    c->data = data;
}
