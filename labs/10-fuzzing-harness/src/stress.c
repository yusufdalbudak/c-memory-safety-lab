#include "parser.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t xorshift32(uint32_t *state) {
    uint32_t x = *state;
    x ^= x << 13U;
    x ^= x >> 17U;
    x ^= x << 5U;
    *state = x;
    return x;
}

int main(void) {
    uint32_t rng = 0xC0FFEEu;
    uint8_t buf[512] = {0};

    const int rounds = 50000;
    for (int round = 0; round < rounds; round++) {
        size_t n = (size_t)(xorshift32(&rng) % (uint32_t)(sizeof buf + 1U));
        for (size_t i = 0; i < n; i++) {
            buf[i] = (uint8_t)xorshift32(&rng);
        }
        (void)parse_record(buf, n);
    }

    printf("[stress] completed %d pseudo-random probe rounds (local sanitizer-friendly harness)\n", rounds);
    return 0;
}
