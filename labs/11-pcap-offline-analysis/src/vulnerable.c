#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint32_t read_le32(const uint8_t *p) {
    uint32_t v = 0;
    memcpy(&v, p, sizeof(v));
    return v;
}

int main(void) {
    /*
     * Minimal PCAP global header (24 bytes) + tiny captured octets.
     * snaplen field (offset 16) claims a large snapshot window while the local
     * demo buffer is short — the buggy path trusts snaplen for copying.
     */
    uint8_t capture[] = {
        0xa1, 0xb2, 0xc3, 0xd4, /* magic */
        0x02, 0x00,             /* major */
        0x04, 0x00,             /* minor */
        0x00, 0x00, 0x00, 0x00, /* thiszone */
        0x00, 0x00, 0x00, 0x00, /* sigfigs */
        0x00, 0x04, 0x00, 0x00, /* snaplen = 1024 (LE) */
        0x01, 0x00, 0x00, 0x00, /* network */
        0xAA, 0xBB, 0xCC        /* pretend post-header bytes */
    };

    const size_t hdr_len = 24U;
    if (sizeof capture < hdr_len) {
        return 1;
    }

    uint32_t snaplen = read_le32(capture + 16U);
    const uint8_t *post = capture + hdr_len;
    const size_t post_len = sizeof capture - hdr_len;

    printf("[vuln] PCAP snaplen field = %u, post-header bytes = %zu\n", snaplen, post_len);

    uint8_t *scratch = malloc(snaplen);
    if (scratch == NULL) {
        fprintf(stderr, "[vuln] malloc failed\n");
        return 1;
    }

    memcpy(scratch, post, snaplen);
    printf("[vuln] Copied first post byte: 0x%02x\n", scratch[0]);

    free(scratch);
    return 0;
}
