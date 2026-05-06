#include <stdio.h>

int main(void) {
    const char *untrusted_like = "%x %x %x";

    printf("[fixed] Constant format; value treated as data:\n");
    printf("%s\n", untrusted_like);

    return 0;
}
