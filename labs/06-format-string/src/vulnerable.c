#include <stdio.h>

int main(void) {
    const char *untrusted_like = "%x %x %x";

    printf("[vuln] Non-constant format string (information-leak / UB risk):\n");
    printf(untrusted_like);

    printf("\n");
    return 0;
}
