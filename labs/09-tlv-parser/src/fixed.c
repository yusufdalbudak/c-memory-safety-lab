#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_TLV_LEN 64U

int main(void) {
    uint8_t buf[] = {0x01U, 40U, 0xAA, 0xBB};

    size_t offset = 0U;
    if (offset + 2U > sizeof(buf)) {
        fprintf(stderr, "[fixed] truncated header\n");
        return 1;
    }

    uint8_t type = buf[offset];
    uint8_t len = buf[offset + 1U];
    offset += 2U;

    if (len > MAX_TLV_LEN) {
        fprintf(stderr, "[fixed] reject: tlv len %u exceeds cap %u\n", len, MAX_TLV_LEN);
        return 0;
    }

    if (offset + (size_t)len > sizeof(buf)) {
        fprintf(stderr, "[fixed] reject: need %zu bytes, have %zu\n",
                offset + (size_t)len, sizeof(buf));
        return 0;
    }

    printf("[fixed] TLV type=0x%02x len=%u (bounded)\n", type, len);
    if (len > 0U) {
        const uint8_t *value = buf + offset;
        printf("[fixed] First value byte: 0x%02x\n", value[0]);
    }

    return 0;
}
