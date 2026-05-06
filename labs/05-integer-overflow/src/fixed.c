#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t count = ((size_t)1 << 62);
    size_t element = 16U;
    size_t bytes;

    if (__builtin_mul_overflow(count, element, &bytes)) {
        fprintf(stderr, "[fixed] multiplication would overflow; rejecting allocation\n");
        return 0;
    }

    const size_t max_demo = (size_t)1024 * (size_t)1024;
    if (bytes > max_demo) {
        fprintf(stderr, "[fixed] demo cap: refusing oversized allocation (%zu bytes)\n", bytes);
        return 0;
    }

    char *buffer = malloc(bytes);
    if (buffer == NULL) {
        fprintf(stderr, "[fixed] malloc failed\n");
        return 1;
    }

    memset(buffer, 0, bytes);

    printf("[fixed] Allocated %zu bytes safely (sanitizer run validates access)\n", bytes);

    free(buffer);
    return 0;
}
