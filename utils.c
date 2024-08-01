#include <stddef.h>
#include <stdio.h>
#include "utils.h"

const char* parse_input(int argc, const char* argv[argc + 1]) {
    if (argc != 2) {
        printf("Usage %s <url>\n", argv[0]);
        return NULL;
    }

    return argv[1];
}

size_t request_callback(char *buffer, size_t itemsize, size_t numitems, void* _ __attribute__((unused))) {
    size_t bytes = itemsize * numitems;
    for (size_t i = 0; i < numitems; i++) {
        printf("%c", buffer[i]);
    }
    return bytes;
}
