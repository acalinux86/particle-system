#include "./file.h"

char *read_file(const char *file_path, uint32_t *size)
{
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file %s: %s.\n", file_path, strerror(errno));
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    uint32_t len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(len+1);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to Allocate Memory For Buffer.\n");
        return NULL;
    }

    size_t n = fread(buffer, 1, len, fp);
    assert(n == (size_t) len);

    if (ferror(fp) < 0) {
        fprintf(stderr, "fread failed!.\n");
        return NULL;
    }

    buffer[len] = '\0';
    *size = len;

    fclose(fp);
    return buffer;
}

