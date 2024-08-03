#pragma once
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


char* get_parent_directory(char* path, const unsigned int levels) {
    char* dir = dirname(path);
    for (unsigned int i = 0; i < levels; ++i) {
        dir = dirname(dir);
        if (strcmp(dir, "/") == 0 || strcmp(dir, ".") == 0) {
            break;
        }
    }

    return dir;
}


char *get_data_file(const char *name) {
    const char* start = __FILE__;
    char* absolute_path = realpath(start, NULL);
    if (!absolute_path) {
        perror("realpath");
    }
    char* parents_dir = get_parent_directory(absolute_path, 3);
    const size_t p_len = strlen(parents_dir),
    name_len = strlen(name);
    char *file_path = (char *)malloc(p_len + name_len + 8);
    memcpy(file_path, parents_dir, p_len);
    memcpy(file_path + p_len, "/_data/", 7);
    memcpy(file_path + p_len + 7, name, name_len);
    file_path[p_len + name_len + 7] = 0;
    FILE* file = fopen(file_path, "r");
    free(absolute_path);
//    free(parents_dir);
    free(file_path);
    if (!file) {
        perror("fopen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    const size_t ret_code = fread(buffer, 1, length, file);
    if (ret_code != length) {
        if (feof(file))
            printf("Error reading %s: unexpected end of file, read %zu of %zu bytes expected\n", name, ret_code, length);
        else if (ferror(file))
            perror("Error reading data file");
    }

    buffer[length] = 0;
    fclose(file);

    return buffer;
}
