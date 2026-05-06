#include <stdio.h>
#include <string.h>

#define BUF_CAP 32U
#define LOG_CAP 96U

typedef struct {
    char tag[12];
    int strict;
} lab_config_t;

static int bounded_copy(char *dest, size_t dest_cap, const char *src) {
    if (dest == NULL || src == NULL || dest_cap == 0U) {
        return -1;
    }

    size_t copied = strlcpy(dest, src, dest_cap);
    if (copied >= dest_cap) {
        return -2;
    }

    return 0;
}

static void safe_logf(const lab_config_t *cfg, const char *msg) {
    if (cfg == NULL || msg == NULL) {
        return;
    }
    char line[LOG_CAP];
    const char *mode = cfg->strict ? "strict" : "relaxed";
    int n = snprintf(line, sizeof line, "[%s|%s] %s", cfg->tag, mode, msg);
    if (n < 0 || (size_t)n >= sizeof line) {
        fprintf(stderr, "[toolkit] log truncated or encoding error\n");
        return;
    }
    fputs(line, stdout);
    fputc('\n', stdout);
}

int main(void) {
    lab_config_t cfg = {.tag = "lab15", .strict = 1};

    char buf[BUF_CAP];
    const char *input = "ControlledInput";

    int rc = bounded_copy(buf, sizeof buf, input);
    if (rc != 0) {
        safe_logf(&cfg, "copy rejected");
        return (rc == -2) ? 0 : 1;
    }

    safe_logf(&cfg, "copy ok");
    printf("[toolkit] buffer: %s\n", buf);
    return 0;
}
