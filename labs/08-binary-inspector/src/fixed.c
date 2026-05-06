#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAGIC "LAB8"
#define MAX_PAYLOAD ((size_t)512U)

static uint32_t read_le32(const uint8_t *p) {
    uint32_t v = 0;
    memcpy(&v, p, sizeof(v));
    return v;
}

int main(void) {
    uint8_t blob[] = {
        'L', 'A', 'B', '8',
        80, 0, 0, 0,
        0x01, 0x02, 0x03, 0x04, 0x05};

    if (memcmp(blob, MAGIC, 4U) != 0) {
        fprintf(stderr, "[fixed] bad magic\n");
        return 1;
    }

    uint32_t claimed_u = read_le32(blob + 4U);
    size_t claimed = (size_t)claimed_u;
    const uint8_t *payload = blob + 8U;
    const size_t blob_total = sizeof(blob);
    const size_t available = blob_total - 8U;

    if (claimed_u > MAX_PAYLOAD) {
        fprintf(stderr, "[fixed] reject: claimed payload %u exceeds cap %zu\n", claimed_u, MAX_PAYLOAD);
        return 0;
    }

    if (claimed > available) {
        fprintf(stderr, "[fixed] reject: need %zu bytes, have %zu\n", claimed, available);
        return 0;
    }

    uint8_t *copy = malloc(claimed == 0 ? 1U : claimed);
    if (copy == NULL) {
        fprintf(stderr, "[fixed] malloc failed\n");
        return 1;
    }

    memcpy(copy, payload, claimed);
    printf("[fixed] Copied %zu-byte payload under policy\n", claimed);
    if (claimed > 0) {
        printf("[fixed] First byte: 0x%02x\n", copy[0]);
    }

    free(copy);
    return 0;
}
