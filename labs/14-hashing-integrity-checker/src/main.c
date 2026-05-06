#include <CommonCrypto/CommonDigest.h>

#include <stdio.h>
#include <string.h>

#define DATA "lab14-integrity-demo"

static void print_hex(const uint8_t *digest, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

int main(void) {
    const char *payload = DATA;
    uint8_t digest[CC_SHA256_DIGEST_LENGTH] = {0};

    CC_SHA256(payload, (CC_LONG)strlen(payload), digest);

    printf("[demo] SHA-256(\"%s\"):\n", payload);
    printf("[demo] ");
    print_hex(digest, sizeof digest);

    /* Expected digest captured once for reproducible offline comparison. */
    static const uint8_t expected[CC_SHA256_DIGEST_LENGTH] = {
        0x36, 0x70, 0x45, 0x2d, 0xee, 0xab, 0x5c, 0x3e, 0x6b, 0x56, 0xb2, 0x1b, 0x61,
        0xb8, 0x61, 0xa5, 0x08, 0x0d, 0x09, 0xf3, 0x5d, 0x55, 0xb1, 0x16, 0x23, 0x30,
        0x8f, 0x5c, 0xb6, 0xbb, 0x33, 0xe8};

    if (memcmp(digest, expected, sizeof expected) != 0) {
        fprintf(stderr, "[demo] mismatch: update expected digest after algorithm/text change\n");
        return 1;
    }

    printf("[demo] digest matches embedded expected vector\n");
    return 0;
}
