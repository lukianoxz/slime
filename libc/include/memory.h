#ifndef LIBC_MEMORY_H
#define LIBC_MEMORY_H

#include "../../shared/slm.h"

static inline void *memcpy(void *dest, const void *src, uint16_t size) {
    char *dest_target = (char *)dest;
    char *src_target = (char *)src;

    while (size--) {
        *dest_target++ = *src_target++;
    };

    return dest;
}

#endif