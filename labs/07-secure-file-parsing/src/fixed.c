#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILE_BYTES ((size_t)(64U * 1024U))

static int read_entire_file_bounded(const char *path, char **out_data, size_t *out_size) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "[fixed] open failed: %s\n", path);
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fprintf(stderr, "[fixed] seek failed\n");
        fclose(fp);
        return -1;
    }

    long len = ftell(fp);
    if (len < 0) {
        fprintf(stderr, "[fixed] ftell failed\n");
        fclose(fp);
        return -1;
    }

    if (len > (long)MAX_FILE_BYTES) {
        fprintf(stderr, "[fixed] reject: file too large (%ld bytes, cap %zu)\n", len, MAX_FILE_BYTES);
        fclose(fp);
        return -2;
    }

    size_t size = (size_t)len;
    if (fseek(fp, 0, SEEK_SET) != 0) {
        fprintf(stderr, "[fixed] rewind failed\n");
        fclose(fp);
        return -1;
    }

    char *buffer = malloc(size + 1U);
    if (buffer == NULL) {
        fprintf(stderr, "[fixed] malloc failed\n");
        fclose(fp);
        return -1;
    }

    size_t read_count = fread(buffer, 1U, size, fp);
    fclose(fp);

    if (read_count != size) {
        fprintf(stderr, "[fixed] short read\n");
        free(buffer);
        return -1;
    }

    buffer[size] = '\0';
    *out_data = buffer;
    *out_size = size;
    return 0;
}

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : "fixtures/sample.txt";

    struct stat st;
    if (stat(path, &st) != 0) {
        fprintf(stderr, "[fixed] stat failed: %s\n", path);
        return 1;
    }

    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "[fixed] not a regular file: %s\n", path);
        return 1;
    }

    if (st.st_size < 0 || st.st_size > (off_t)MAX_FILE_BYTES) {
        fprintf(stderr, "[fixed] reject: stat size exceeds cap before open-read\n");
        return 0;
    }

    size_t size = 0;
    char *data = NULL;
    int rc = read_entire_file_bounded(path, &data, &size);
    if (rc == -2) {
        return 0;
    }
    if (rc != 0 || data == NULL) {
        return 1;
    }

    printf("[fixed] Read %zu bytes under cap %zu\n", size, MAX_FILE_BYTES);
    printf("[fixed] Preview: %.40s%s\n", data, (size > 40U) ? "..." : "");

    free(data);
    return 0;
}
