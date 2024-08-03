#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h> // for getcwd, chdir
#include <limits.h> // for PATH_MAX


char* get_parent_directory(const char* path, const unsigned int levels) {
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
    free(absolute_path);
    const size_t p_len = strlen(parents_dir),
    name_len = strlen(name);
    char *file_path = (char *)malloc(p_len + name_len + 8);
    memcpy(file_path, parents_dir, p_len);
    memcpy(file_path + p_len, "/_data/", 7);
    memcpy(file_path + p_len + 7, name, name_len);
    file_path[p_len + name_len + 7] = 0;
//    free(parents_dir);
    FILE* file = fopen(file_path, "r");
    free(file_path);
    if (!file) {
        perror("fopen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = 0;
    fclose(file);

    return buffer;
}
