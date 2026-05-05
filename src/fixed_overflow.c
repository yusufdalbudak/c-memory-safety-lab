#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16

static int guarded_copy(char *destination, size_t destination_size, const char *source) {
    if (destination == NULL || source == NULL || destination_size == 0) {
        return -1;
    }

    if (strlen(source) >= destination_size) {
        return -2;
    }

    strcpy(destination, source);
    return 0;
}

int main(void) {
    char buffer[BUFFER_SIZE];

    const char *payload = "This string is definitely longer than sixteen characters";

    printf("[fixed] Validating input length before copy...\n");

    int result = guarded_copy(buffer, sizeof(buffer), payload);

    if (result == -2) {
        fprintf(stderr, "[fixed] rejected oversized input safely\n");
        return 0;
    }

    if (result != 0) {
        fprintf(stderr, "[fixed] copy failed\n");
        return 1;
    }

    printf("[fixed] Buffer content: %s\n", buffer);

    return 0;
}
