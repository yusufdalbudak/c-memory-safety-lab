#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t count = ((size_t)1 << 62);
    size_t element = 16U;
    size_t bytes = count * element;

    printf("[vuln] Computed allocation size (may wrap): %zu\n", bytes);

    char *buffer = malloc(bytes);
    if (buffer == NULL) {
        fprintf(stderr, "[vuln] malloc returned NULL\n");
        return 1;
    }

    memset(buffer, 'A', 1024);

    printf("[vuln] Wrote past true allocation (ASan should catch)\n");

    free(buffer);
    return 0;
}
