#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>

const char* parse_input(int argc, const char* argv[argc + 1]);
size_t request_callback(char *buffer, size_t itemsize, size_t numitems, void* _);

#endif
