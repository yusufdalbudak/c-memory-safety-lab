#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(void) {
    /*
     * Synthetic "TCP-like" prefix: first 12 bytes ports/seq, byte 12 carries
     * data offset in the high nibble (RFC 793 style). Remainder padded zeros.
     */
    uint8_t segment[24] = {
        0x00, 0x50, /* src */
        0x01, 0xBB, /* dst */
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        (uint8_t)(15U << 4), 0x00, /* DO=15 => 60-byte header claim */
        0x00, 0x00,
        0xDE, 0xAD, 0xBE, 0xEF};

    size_t seg_len = sizeof segment;
    uint8_t doff_nibble = (uint8_t)(segment[12U] >> 4);
    size_t hdr_len = (size_t)doff_nibble * 4U;

    printf("[vuln] Data offset => %zu-byte header (segment is %zu bytes)\n", hdr_len, seg_len);

    uint8_t *copy = malloc(hdr_len);
    if (copy == NULL) {
        fprintf(stderr, "[vuln] malloc failed\n");
        return 1;
    }

    memcpy(copy, segment, hdr_len);
    printf("[vuln] First copy byte: 0x%02x\n", copy[0]);

    free(copy);
    return 0;
}
