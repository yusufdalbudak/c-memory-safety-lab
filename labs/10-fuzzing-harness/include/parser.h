#ifndef LAB10_PARSER_H
#define LAB10_PARSER_H

#include <stddef.h>
#include <stdint.h>

/**
 * Bounded defensive parse of a toy record:
 * 'R' | u16_le length | payload (length bytes)
 * Returns 0 on accept, -1 on reject.
 */
int parse_record(const uint8_t *data, size_t len);

#endif
