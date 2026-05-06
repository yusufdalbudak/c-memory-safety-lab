#include "parser.h"

#include <stddef.h>
#include <stdint.h>

/* LibFuzzer entrypoint for `make fuzz-libfuzzer`; not linked in CI builds. */
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    (void)parse_record(data, size);
    return 0;
}
