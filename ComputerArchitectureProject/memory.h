#pragma once

#include <stdint.h>

#define PAGE_BITS 10
#define PAGE_SIZE (1 << PAGE_BITS)
#define MEMORY_SIZE (1 << 21)
#define NUM_PAGES (MEMORY_SIZE / PAGE_SIZE)

typedef uint32_t Page[PAGE_SIZE];

typedef struct {
    Page **pages;
} Memory;

void memory_init(Memory *m);

void memory_destroy(Memory *m);
