#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_CAP 16

int main(void) {
    const char *payload = "This string is definitely longer than sixteen characters";
    size_t need = strlen(payload) + 1U;

    if (need > HEAP_CAP) {
        fprintf(stderr, "[fixed] rejected: need %zu bytes, capacity %d\n", need, HEAP_CAP);
        return 0;
    }

    char *buffer = malloc(HEAP_CAP);
    if (buffer == NULL) {
        fprintf(stderr, "[fixed] allocation failed\n");
        return 1;
    }

    memcpy(buffer, payload, need);
    printf("[fixed] Buffer content: %s\n", buffer);

    free(buffer);
    return 0;
}
