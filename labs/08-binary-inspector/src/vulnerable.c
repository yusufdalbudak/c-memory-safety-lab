#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAGIC "LAB8"

static uint32_t read_le32(const uint8_t *p) {
    uint32_t v = 0;
    memcpy(&v, p, sizeof(v));
    return v;
}

int main(void) {
    /* Magic + claimed payload length + short tail (intentionally inconsistent). */
    uint8_t blob[] = {
        'L', 'A', 'B', '8', 80, 0, 0, 0, /* claims 80 payload bytes */
        0x01, 0x02, 0x03, 0x04, 0x05     /* only 5 bytes available */
    };

    if (memcmp(blob, MAGIC, 4U) != 0) {
        fprintf(stderr, "[vuln] bad magic\n");
        return 1;
    }

    uint32_t claimed = read_le32(blob + 4U);
    const uint8_t *payload = blob + 8U;
    const size_t blob_total = sizeof(blob);
    const size_t available = blob_total - 8U;

    printf("[vuln] Claimed payload length: %u (available %zu)\n", claimed, available);

    uint8_t *copy = malloc(claimed);
    if (copy == NULL) {
        fprintf(stderr, "[vuln] malloc failed\n");
        return 1;
    }

    /* Bug: trusts claimed length without bounding to buffer. */
    memcpy(copy, payload, claimed);
    printf("[vuln] Copied first byte: 0x%02x\n", copy[0]);

    free(copy);
    return 0;
}
