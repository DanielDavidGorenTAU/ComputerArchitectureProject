#include <stdio.h>
#include "processor.h"

int main() {
    Processor processor;
    processor_init(&processor);
    while (!processor_is_done(&processor)) {
        processor_cycle(&processor);
    }
    processor_destroy(&processor);
}
