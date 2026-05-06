#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *value = malloc(sizeof(int));
    if (value == NULL) {
        fprintf(stderr, "[fixed] allocation failed\n");
        return 1;
    }

    *value = 42;
    int copy = *value;
    free(value);
    value = NULL;

    printf("[fixed] Used value before free; after free pointer is NULL\n");
    printf("[fixed] Stored: %d\n", copy);

    return 0;
}
