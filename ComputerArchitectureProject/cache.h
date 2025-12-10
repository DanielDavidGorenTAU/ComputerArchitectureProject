#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "bus.h"

enum MesiTag {
    MESI_INVALID,
    MESI_SHARED,
    MESI_EXCLUSIVE,
    MESI_MODIFIED,
};

#define CACHE_SIZE 512
#define CACHE_BLOCK_SIZE 8
#define CACHE_NUM_BLOCKS (CACHE_SIZE / CACHE_BLOCK_SIZE)

typedef uint32_t CacheBlock[CACHE_BLOCK_SIZE];

typedef struct {
    CacheBlock *data_memory;
    uint16_t *tag_memory;
    Bus *bus;
    bool is_busy;
    uint32_t current_address;
    uint32_t data;
} Cache;

void cache_init(Cache *c, Bus *bus);

void cache_destroy(Cache *c);

void cache_begin_cycle(Cache *c);

void cache_finish_cycle(Cache *c);

void cache_begin_read(Cache *c, uint32_t address);

void cache_begin_write(Cache *c, uint32_t address, uint32_t value);
