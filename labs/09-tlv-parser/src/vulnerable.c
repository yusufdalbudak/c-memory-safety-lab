#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(void) {
    /* type(1) len(1) ... len claims 40 but buffer ends early */
    uint8_t buf[] = {0x01U, 40U, 0xAA, 0xBB};

    size_t offset = 0U;
    if (offset + 2U > sizeof(buf)) {
        fprintf(stderr, "[vuln] truncated header\n");
        return 1;
    }

    uint8_t type = buf[offset];
    uint8_t len = buf[offset + 1U];
    offset += 2U;

    printf("[vuln] TLV type=0x%02x len=%u\n", type, len);

    /* Bug: does not verify len against remaining bytes. */
    const uint8_t *value = buf + offset;
    printf("[vuln] First value byte: 0x%02x\n", value[0]);
    if (len > 1U) {
        printf("[vuln] Last requested byte: 0x%02x\n", value[len - 1U]);
    }

    (void)type;
    return 0;
}
