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

int main(void) {
    guarded_frame_t frame;
    frame.pre_guard = PRE_MAGIC;
    frame.post_guard = POST_MAGIC;

    const char *input = "This payload is longer than eight bytes";

    printf("[vuln] copying into %zu-byte scratch without canary audit...\n", sizeof frame.scratch);

    /* Classic pattern: overflow clobbers post_guard, but we never verify. */
    strcpy(frame.scratch, input);

    printf("[vuln] pre_guard=0x%08x post_guard=0x%08x (may already be corrupted)\n",
           frame.pre_guard, frame.post_guard);

    return 0;
}
