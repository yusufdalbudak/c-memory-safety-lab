#include <stdio.h>
#include <string.h>
#include <stdint.h>

static uint16_t read_be16(const uint8_t *p) {
    return (uint16_t)((uint16_t)p[0] << 8 | (uint16_t)p[1]);
}

int main(void) {
    /* Wire-format DNS header (12 bytes) + 4 extra octets (too short for questions). */
    uint8_t msg[] = {
        0x12, 0x34,             /* ID */
        0x80, 0x00,             /* flags (response) */
        0x00, 0x08,             /* QDCOUNT = 8 (big-endian) */
        0x00, 0x00,             /* ANCOUNT */
        0x00, 0x00,             /* NSCOUNT */
        0x00, 0x00,             /* ARCOUNT */
        0xAA, 0xBB, 0xCC, 0xDD /* stub tail */
    };

    uint16_t qdcount = read_be16(msg + 4U);

    printf("[vuln] QDCOUNT=%u — walking bytes without total length policy\n", (unsigned)qdcount);

    const size_t header = 12U;
    const size_t total = sizeof msg;

    /* Bug: indexes header + i without bounding to message length. */
    for (uint16_t i = 0; i < qdcount; i++) {
        (void)printf("%02x\n", msg[header + (size_t)i]);
    }

    return 0;
}
