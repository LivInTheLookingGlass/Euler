#pragma once
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <libgen.h>
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

char* get_parent_directory(char* path, const uint32_t levels) {
#ifdef _WIN32
    static char drive[_MAX_DRIVE];
    static char dir[_MAX_DIR];
    _splitpath(path, drive, dir, NULL, NULL);
    for (uint32_t i = 0; i < levels; ++i) {
        size_t len = strlen(dir);
        if (len > 1 && (dir[len - 1] == '\\' || dir[len - 1] == '/'))
            dir[len - 1] = '\0';
        char* last_slash = strrchr(dir, '\\');
        if (!last_slash)
            last_slash = strrchr(dir, '/');
        if (last_slash)
            *last_slash = '\0';
    }
    static char parent_dir[_MAX_PATH];
    snprintf(parent_dir, sizeof(parent_dir), "%s%s", drive, dir);
    return parent_dir;
#else
    char* dir = dirname(path);
    for (uint32_t i = 0; i < levels; ++i) {
        dir = dirname(dir);
        if (strcmp(dir, "/") == 0 || strcmp(dir, ".") == 0)
            break;
    }
    return dir;
#endif
}

char *get_data_file(const char *name) {
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
            printf("Error reading %s: unexpected end of file, read %" PRIu64 " of %"PRIu64" bytes expected\n", name, (uint64_t)ret_code, (uint64_t)length);
        else if (ferror(file))
            perror("Error reading data file");
    }

    buffer[length] = 0;
    fclose(file);

    return buffer;
}

typedef enum {
	ERRORT,
	INT8T,
	INT16T,
	INT32T,
	INT64T,
	UINT8T,
	UINT16T,
	UINT32T,
	UINT64T,
	STRINGT,
} AnswerType;

typedef struct {
    union {
        uint8_t uint8;
        uint16_t uint16;
        uint32_t uint32;
        uint64_t uint64;
        int8_t int8;
        int16_t int16;
        int32_t int32;
        int64_t int64;
        char *string;
    } value;
	uint16_t id : 12;
	AnswerType type : 4;
} Answer;

Answer get_answer(uint16_t id) {
    Answer ret = {
        .id = id,
    };
    char *answers = get_data_file("answers.tsv");
    char *linepointer, *tabpointer;

    if (!answers) {
        fprintf(stderr, "Error: Unable to get data from file\n");
        return ret;
    }

    char s_id[6];
    snprintf(s_id, sizeof(s_id), "%" PRIu16, id);

#ifdef _WIN32
    char *line = strtok_s(answers, "\n", &linepointer);  // skip header
    while ((line = strtok_s(NULL, "\n", &linepointer)) != NULL) {
#else
    char *line = strtok_r(answers, "\n", &linepointer);  // skip header
    while ((line = strtok_r(NULL, "\n", &linepointer)) != NULL) {
#endif
#ifdef _WIN32
        char *token = strtok_s(line, "\t", &tabpointer);
#else
        char *token = strtok_r(line, "\t", &tabpointer);
#endif
        if (strcmp(token, s_id) != 0)
            continue;

#ifdef _WIN32
        token = strtok_s(NULL, "\t", &tabpointer);
#else
        token = strtok_r(NULL, "\t", &tabpointer);
#endif
        if (!token)
            continue;

        if (strcmp(token, "uint") == 0) {
            ret.type = UINT8T;  // will adjust size later
        } else if (strcmp(token, "int") == 0) {
            ret.type = INT8T;  // will adjust size later
        } else if (strcmp(token, "str") == 0) {
            ret.type = STRINGT;
        } else {
            fprintf(stderr, "Error: Unknown type '%s'\n", token);
            return ret;
        }

#ifdef _WIN32
        token = strtok_s(NULL, "\t", &tabpointer);
#else
        token = strtok_r(NULL, "\t", &tabpointer);
#endif
        if (!token)
            continue;
        size_t size = strtoull(token, NULL, 10);

#ifdef _WIN32
        token = strtok_s(NULL, "\t", &tabpointer);
#else
        token = strtok_r(NULL, "\t", &tabpointer);
#endif
        if (!token)
            continue;

        switch (ret.type) {
            case UINT8T:
            case UINT16T:
            case UINT32T:
            case UINT64T:
                switch (size) {
                    case 8:
                        ret.value.uint8 = (uint8_t)strtoul(token, NULL, 10);
                        break;
                    case 16:
                        ret.value.uint16 = (uint16_t)strtoul(token, NULL, 10);
                        ret.type = UINT16T;
                        break;
                    case 32:
                        ret.value.uint32 = strtoul(token, NULL, 10);
                        ret.type = UINT32T;
                        break;
                    case 64:
                        ret.value.uint64 = strtoull(token, NULL, 10);
                        ret.type = UINT64T;
                        break;
                    default:
                        fprintf(stderr, "Error: Unsupported uint size %" PRIu64 "\n", (uint64_t)size);
                        Answer err = {0};
                        return err;
                }
                break;
            case INT8T:
            case INT16T:
            case INT32T:
            case INT64T:
                switch (size) {
                    case 8:
                        ret.value.int8 = (int8_t)strtol(token, NULL, 10);
                        break;
                    case 16:
                        ret.value.int16 = (int16_t)strtol(token, NULL, 10);
                        ret.type = INT16T;
                        break;
                    case 32:
                        ret.value.int32 = strtol(token, NULL, 10);
                        ret.type = INT32T;
                        break;
                    case 64:
                        ret.value.int64 = strtoll(token, NULL, 10);
                        ret.type = INT64T;
                        break;
                    default:
                        fprintf(stderr, "Error: Unsupported int size %" PRIu64 "\n", (uint64_t)size);
                        Answer err = {0};
                        return err;
                }
                break;
            case STRINGT:
                ret.value.string = (char *)malloc(size + 1);
                if (ret.value.string) {
                    strncpy(ret.value.string, token, size);
                    ret.value.string[size] = 0;
                } else {
                    fprintf(stderr, "Error: Memory allocation failed for string\n");
                    Answer err = {0};
                    return err;
                }
                break;
            case ERRORT:
                fprintf(stderr, "Error: Unknown type (should be unreachable)\n");
                Answer err = {0};
                return err;
        }
        break;
    }

    free(answers);
    return ret;
}
