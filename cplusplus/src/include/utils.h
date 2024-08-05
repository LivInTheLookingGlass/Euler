#pragma once
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <libgen.h>
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

char* get_parent_directory(char* path, const unsigned int levels) {
#ifdef _WIN32
    static char drive[_MAX_DRIVE];
    static char dir[_MAX_DIR];
    _splitpath(path, drive, dir, NULL, NULL);
    for (unsigned int i = 0; i < levels; ++i) {
        size_t len = strlen(dir);
        if (len > 1 && (dir[len - 1] == '\\' || dir[len - 1] == '/')) {
            dir[len - 1] = '\0';
        }
        char* last_slash = strrchr(dir, '\\');
        if (!last_slash) last_slash = strrchr(dir, '/');
        if (last_slash) *last_slash = '\0';
    }
    static char parent_dir[_MAX_PATH];
    snprintf(parent_dir, sizeof(parent_dir), "%s%s", drive, dir);
    return parent_dir;
#else
    char* dir = dirname(path);
    for (unsigned int i = 0; i < levels; ++i) {
        dir = dirname(dir);
        if (strcmp(dir, "/") == 0 || strcmp(dir, ".") == 0) {
            break;
        }
    }
    return dir;
#endif
}

std::string get_data_file(const char *name) {
    const char* start = __FILE__;
#ifdef _WIN32
    char absolute_path[MAX_PATH];
    if (!_fullpath(absolute_path, start, MAX_PATH)) {
        perror("_fullpath");
        return NULL;
    }
#else
   char* absolute_path = realpath(start, NULL);
    if (!absolute_path) {
        perror("realpath");
        return NULL;
    }
#endif
    char* parents_dir = get_parent_directory(absolute_path, 3);
    const size_t p_len = strlen(parents_dir),
    name_len = strlen(name);
    char *file_path = (char *)malloc(p_len + name_len + 8);
    memcpy(file_path, parents_dir, p_len);
    memcpy(file_path + p_len, PATH_SEPARATOR "_data" PATH_SEPARATOR, 7);
    memcpy(file_path + p_len + 7, name, name_len);
    file_path[p_len + name_len + 7] = 0;
    FILE* file = fopen(file_path, "r");
#ifndef _WIN32
    free(absolute_path);
#endif
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
            printf("Error reading %s: unexpected end of file, read %llu of %llu bytes expected\n", name, (unsigned long long)ret_code, (unsigned long long)length);
        else if (ferror(file))
            perror("Error reading data file");
    }

    buffer[length] = 0;
    fclose(file);

    std::string ret(buffer);
    free(buffer);
    return ret;
}
