#include <stdio.h>
#include <string.h>

#define SECRET_CAP 48U

static char g_secret_slot[SECRET_CAP];

/* Compiler must not delete these writes when optimizing. */
static void secure_zero(void *buf, size_t len) {
    volatile unsigned char *p = buf;
    while (len > 0U) {
        len--;
        p[len] = 0;
    }
}

static void store_secret(const char *src) {
    secure_zero(g_secret_slot, sizeof g_secret_slot);
    if (src == NULL || src[0] == '\0') {
        return;
    }
    strncpy(g_secret_slot, src, sizeof g_secret_slot - 1U);
    g_secret_slot[sizeof g_secret_slot - 1U] = '\0';
}

static void print_sensitive_preview(void) {
    printf("[fixed] slot preview: %.8s***\n", g_secret_slot);
}

int main(void) {
    store_secret("NightTrainCredential");
    print_sensitive_preview();

    store_secret(""); /* rotation / logout */
    print_sensitive_preview();

    return 0;
}
