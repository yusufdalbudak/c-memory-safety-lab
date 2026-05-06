#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PCAP_MAGIC_LE 0xd4c3b2a1U
#define MAX_SNAPLEN ((uint32_t)(64U * 1024U))

static uint32_t read_le32(const uint8_t *p) {
    uint32_t v = 0;
    memcpy(&v, p, sizeof(v));
    return v;
}

int main(void) {
    uint8_t capture[] = {
        0xa1, 0xb2, 0xc3, 0xd4,
        0x02, 0x00,
        0x04, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x04, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00,
        0xAA, 0xBB, 0xCC};

    const size_t hdr_len = 24U;
    if (sizeof capture < hdr_len) {
        return 1;
    }

    uint32_t magic = read_le32(capture);
    if (magic != PCAP_MAGIC_LE && magic != 0xa1b2c3d4U) {
        fprintf(stderr, "[fixed] unsupported pcap magic: 0x%08x\n", magic);
        return 1;
    }

    uint32_t snaplen = read_le32(capture + 16U);
    const uint8_t *post = capture + hdr_len;
    const size_t post_len = sizeof capture - hdr_len;

    if (snaplen > MAX_SNAPLEN) {
        fprintf(stderr, "[fixed] reject: snaplen %u exceeds policy %u\n", snaplen, MAX_SNAPLEN);
        return 0;
    }

    size_t to_copy = (size_t)snaplen;
    if (to_copy > post_len) {
        fprintf(stderr, "[fixed] reject: need %zu bytes after header, have %zu\n", to_copy, post_len);
        return 0;
    }

    uint8_t *scratch = malloc(to_copy == 0 ? 1U : to_copy);
    if (scratch == NULL) {
        fprintf(stderr, "[fixed] malloc failed\n");
        return 1;
    }

    memcpy(scratch, post, to_copy);
    printf("[fixed] Parsed offline header; copied %zu post-header octets (bounded)\n", to_copy);

    free(scratch);
    return 0;
}
