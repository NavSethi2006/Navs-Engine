#include "file_parser.h"


static char* read_file(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}

static char* find_tag(const char* xml, const char* tag) {
    char search[64];
    snprintf(search, sizeof(search), "<%s", tag);
    return strstr(xml, search);
}

static int extract_attr_int(const char* tag, const char* attr) {
    char* loc = strstr(tag, attr);
    if (!loc) return -1;

    loc += strlen(attr) + 2; // skip attr="
    return atoi(loc);
}

static char* extract_csv_data(const char* data_tag) {
    const char* start = strstr(data_tag, ">") + 1;
    const char* end = strstr(start, "</data>");
    size_t len = end - start;

    char* csv = malloc(len + 1);
    strncpy(csv, start, len);
    csv[len] = '\0';
    return csv;
}

static void parse_csv(const char* csv, int* tiles, int max) {
    int count = 0;
    const char* ptr = csv;
    while (*ptr && count < max) {
        while (*ptr && !isdigit(*ptr) && *ptr != '-') ptr++;

        if (*ptr == '\0') break;

        tiles[count++] = atoi(ptr);

        while (*ptr && (isdigit(*ptr) || *ptr == '-')) ptr++;
    }
}

