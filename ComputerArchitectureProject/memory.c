#include <stdlib.h>
#include "memory.h"

void memory_init(Memory *m) {
    m->pages = calloc(NUM_PAGES, sizeof(Page*));
}

void memory_destroy(Memory *m) {
    for (int i = 0; i < NUM_PAGES; i++) {
        free(m->pages[i]);
    }
    free(m->pages);
}

static Page *get_page(Memory *m, uint32_t index) {
    Page **page_ptr = &m->pages[index];
    if (*page_ptr == NULL) {
        *page_ptr = calloc(PAGE_SIZE, sizeof(uint32_t));
    }
    return *page_ptr;
}

static uint32_t *get_word(Memory *m, uint32_t address) {
    Page *page = get_page(m, address >> PAGE_BITS);
    return &(*page)[address & (PAGE_SIZE - 1)];
}
