#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

static char *read_entire_file(const char *path, size_t *out_size) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "[vuln] open failed: %s\n", path);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fprintf(stderr, "[vuln] seek failed\n");
        fclose(fp);
        return NULL;
    }

    long len = ftell(fp);
    if (len < 0) {
        fprintf(stderr, "[vuln] ftell failed\n");
        fclose(fp);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_SET) != 0) {
        fprintf(stderr, "[vuln] rewind failed\n");
        fclose(fp);
        return NULL;
    }

    size_t size = (size_t)len;
    char *buffer = malloc(size + 1U);
    if (buffer == NULL) {
        fprintf(stderr, "[vuln] malloc failed\n");
        fclose(fp);
        return NULL;
    }

    size_t read_count = fread(buffer, 1U, size, fp);
    fclose(fp);

    if (read_count != size) {
        fprintf(stderr, "[vuln] short read\n");
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';
    *out_size = size;
    return buffer;
}

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : "fixtures/sample.txt";

    struct stat st;
    if (stat(path, &st) != 0) {
        fprintf(stderr, "[vuln] stat failed: %s\n", path);
        return 1;
    }

    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "[vuln] not a regular file: %s\n", path);
        return 1;
    }

    /* Intentional weakness: no upper bound on file size before malloc/fread. */
    size_t size = 0;
    char *data = read_entire_file(path, &size);
    if (data == NULL) {
        return 1;
    }

    printf("[vuln] Read %zu bytes (no max-file policy)\n", size);
    printf("[vuln] Preview: %.40s%s\n", data, (size > 40U) ? "..." : "");

    free(data);
    return 0;
}
