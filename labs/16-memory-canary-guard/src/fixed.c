#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PRE_MAGIC  0xC0FFEEu
#define POST_MAGIC 0xFACADEu

typedef struct {
    uint32_t pre_guard;
    char scratch[8];
    uint32_t post_guard;
} guarded_frame_t;

static int guards_ok(const guarded_frame_t *frame) {
    return frame->pre_guard == PRE_MAGIC && frame->post_guard == POST_MAGIC;
}

static int bounded_copy(guarded_frame_t *frame, const char *input) {
    size_t need = strlen(input) + 1U;
    if (need > sizeof frame->scratch) {
        fprintf(stderr, "[fixed] reject: need %zu bytes, scratch holds %zu\n", need,
                sizeof frame->scratch);
        return -1;
    }

    memcpy(frame->scratch, input, need);
    return 0;
}

int main(void) {
    guarded_frame_t frame;
    frame.pre_guard = PRE_MAGIC;
    frame.post_guard = POST_MAGIC;

    const char *too_long = "This payload is longer than eight bytes";
    const char *fits = "tiny";

    if (bounded_copy(&frame, too_long) != 0) {
        if (!guards_ok(&frame)) {
            fprintf(stderr, "[fixed] guard corruption after rejected copy — investigate\n");
            return 1;
        }
        printf("[fixed] Long payload rejected; guards still intact\n");
    }

    if (bounded_copy(&frame, fits) != 0) {
        fprintf(stderr, "[fixed] unexpected failure on short payload\n");
        return 1;
    }

    if (!guards_ok(&frame)) {
        fprintf(stderr, "[fixed] memory canaries mismatch — spill detected\n");
        return 1;
    }

    printf("[fixed] copy ok; guards intact (pre=0x%08x post=0x%08x)\n", frame.pre_guard,
           frame.post_guard);
    printf("[fixed] scratch=%s\n", frame.scratch);

    return 0;
}
