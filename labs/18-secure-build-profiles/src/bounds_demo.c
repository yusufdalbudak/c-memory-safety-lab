#include <stdio.h>
#include <string.h>

#define BUF 32U

int main(void) {
    char buffer[BUF];
    const char *message = "architecture-demo";

    memset(buffer, 0, sizeof buffer);
    strncpy(buffer, message, sizeof buffer - 1U);
    buffer[sizeof buffer - 1U] = '\0';

    printf("[demo] profile exercise: buffer contains \"%s\"\n", buffer);
    printf("[demo] same source compiles under dev (sanitizers) vs hardened (FORTIFY/stack protector)\n");

    return 0;
}
