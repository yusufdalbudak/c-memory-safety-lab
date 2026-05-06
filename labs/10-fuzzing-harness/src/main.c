#include "parser.h"

#include <stdio.h>
#include <string.h>

int main(void) {
    const uint8_t ok[] = {'R', 2, 0, 'a', 'b', 'c'};
    const uint8_t bad[] = {'R', 9, 0, 'x'};

    printf("[demo] expect accept=%d reject=%d\n", 0, -1);
    printf("[demo] accept case -> %d\n", parse_record(ok, sizeof ok));
    printf("[demo] reject case -> %d\n", parse_record(bad, sizeof bad));

    return 0;
}
