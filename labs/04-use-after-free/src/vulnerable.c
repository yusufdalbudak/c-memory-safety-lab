#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *value = malloc(sizeof(int));
    if (value == NULL) {
        fprintf(stderr, "[vuln] allocation failed\n");
        return 1;
    }

    *value = 42;
    free(value);

    printf("[vuln] Dereferencing pointer after free...\n");
    (void)printf("%d\n", *value);

    return 0;
}
