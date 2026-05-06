#include <stdio.h>
#include <string.h>

#define SECRET_CAP 48U

static char g_secret_slot[SECRET_CAP];

static void store_secret(const char *src) {
    if (src == NULL) {
        return;
    }

    /*
     * Intentional weakness: no wipe before reuse — short rotation leaves tail
     * bytes from the previous secret in the buffer.
     */
    strncpy(g_secret_slot, src, sizeof g_secret_slot - 1U);
    g_secret_slot[sizeof g_secret_slot - 1U] = '\0';
}

static void print_sensitive_preview(void) {
    printf("[vuln] leaked slot preview: %.8s***\n", g_secret_slot);
}

int main(void) {
    store_secret("NightTrainCredential");
    print_sensitive_preview();

    store_secret("");
    print_sensitive_preview();

    return 0;
}
