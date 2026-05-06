#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_CAP 16

int main(void) {
    char *buffer = malloc(HEAP_CAP);
    if (buffer == NULL) {
        fprintf(stderr, "[vuln] allocation failed\n");
        return 1;
    }

    const char *payload = "This string is definitely longer than sixteen characters";

    printf("[vuln] Copying into %d-byte heap buffer without bounds check...\n", HEAP_CAP);

    strcpy(buffer, payload);

    printf("[vuln] Buffer content: %s\n", buffer);

    free(buffer);
    return 0;
}
