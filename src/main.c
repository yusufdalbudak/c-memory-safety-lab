#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16

static void unsafe_copy(const char *input) {
    char buffer[BUFFER_SIZE];

    if (strlen(input) >= BUFFER_SIZE) {
        fprintf(stderr, "[unsafe] error: input is too long\n");
        return;
    }

    strcpy(buffer, input);
    printf("[unsafe] Buffer content: %s\n", buffer);
}

static void safe_copy(const char *input) {
    char buffer[BUFFER_SIZE];
    size_t copied = strlcpy(buffer, input, sizeof(buffer));

    if (copied >= sizeof(buffer)) {
        fprintf(stderr, "[safe] warning: input truncated (%zu bytes)\n", copied);
    }

    printf("[safe] Buffer content: %s\n", buffer);
}

int main(void) {
    const char *input = "Cybersecurity";
    const char *large_input = "This string is definitely longer than sixteen characters";

    printf("-- Demonstrating unsafe copy with explicit length guard --\n");
    unsafe_copy(input);
    unsafe_copy(large_input);

    printf("\n-- Demonstrating safe copy using strlcpy --\n");
    safe_copy(input);
    safe_copy(large_input);

    return 0;
}
