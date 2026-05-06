#include "parser.h"

#include <stddef.h>
#include <stdint.h>

int parse_record(const uint8_t *data, size_t len) {
    if (data == NULL) {
        return -1;
    }
    if (len < 3U) {
        return -1;
    }
    if (data[0] != 'R') {
        return -1;
    }

    uint16_t reclen =
        (uint16_t)((unsigned int)data[1] | ((unsigned int)data[2] << 8U));
    if ((size_t)reclen > SIZE_MAX - 3U) {
        return -1;
    }

    size_t need = 3U + (size_t)reclen;

    if (need > len) {
        return -1;
    }

    return 0;
}
