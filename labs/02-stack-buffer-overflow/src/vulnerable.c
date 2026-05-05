#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16

int main(void) {
    char buffer[BUFFER_SIZE];

    const char *payload = "This string is definitely longer than sixteen characters";

    printf("[demo] Copying oversized input into a fixed-size stack buffer...\n");

    strcpy(buffer, payload);

    printf("[demo] Buffer content: %s\n", buffer);

    return 0;
}
