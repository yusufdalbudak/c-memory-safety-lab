#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SEG 256U
#define MAX_TCP_HDR 60U

int main(void) {
    uint8_t segment[MAX_SEG] = {0};
    segment[0] = 0x00;
    segment[1] = 0x50;
    segment[2] = 0x01;
    segment[3] = 0xBB;
    segment[12] = (uint8_t)(15U << 4);
    segment[20] = 0xDE;
    segment[21] = 0xAD;
    segment[22] = 0xBE;
    segment[23] = 0xEF;

    size_t seg_len = 24U;
    uint8_t doff_nibble = (uint8_t)(segment[12U] >> 4);
    size_t hdr_len = (size_t)doff_nibble * 4U;

    if (hdr_len < 20U || hdr_len > MAX_TCP_HDR) {
        fprintf(stderr, "[fixed] reject: impossible TCP header length %zu\n", hdr_len);
        return 0;
    }

    if (hdr_len > seg_len) {
        fprintf(stderr, "[fixed] reject: header %zu exceeds segment %zu\n", hdr_len, seg_len);
        return 0;
    }

    uint8_t *copy = malloc(hdr_len);
    if (copy == NULL) {
        fprintf(stderr, "[fixed] malloc failed\n");
        return 1;
    }

    memcpy(copy, segment, hdr_len);
    printf("[fixed] Copied %zu-byte TCP header from offline segment\n", hdr_len);

    free(copy);
    return 0;
}
