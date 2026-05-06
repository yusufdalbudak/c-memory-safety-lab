#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_QDCOUNT 8U

static uint16_t read_be16(const uint8_t *p) {
    return (uint16_t)((uint16_t)p[0] << 8 | (uint16_t)p[1]);
}

int main(void) {
    uint8_t msg[] = {
        0x12, 0x34,
        0x80, 0x00,
        0x00, 0x08,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        0xAA, 0xBB, 0xCC, 0xDD};

    uint16_t qdcount = read_be16(msg + 4U);

    if (qdcount > MAX_QDCOUNT) {
        fprintf(stderr, "[fixed] reject: QDCOUNT %u exceeds cap %u\n", (unsigned)qdcount, (unsigned)MAX_QDCOUNT);
        return 0;
    }

    const size_t header = 12U;
    const size_t total = sizeof msg;

    if (header + (size_t)qdcount > total) {
        fprintf(stderr, "[fixed] reject: need %zu bytes for qd scan, have %zu\n",
                header + (size_t)qdcount, total);
        return 0;
    }

    printf("[fixed] bounded scan over QDCOUNT=%u within %zu-byte capture\n", (unsigned)qdcount, total);
    for (uint16_t i = 0; i < qdcount; i++) {
        printf("%02x\n", msg[header + (size_t)i]);
    }

    return 0;
}
