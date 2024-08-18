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
    ERROR,
	INT8,
	INT16,
	INT32,
	INT64,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	STR,
} AnswerType;

typedef struct {
    union {
        uint8_t UINT8;
        uint16_t UINT16;
        uint32_t UINT32;
        uint64_t UINT64;
        int8_t INT8;
        int16_t INT16;
        int32_t INT32;
        int64_t INT64;
        char *STR;
    } value;
	uint16_t id : 12;
	AnswerType type : 4;
} Answer;

Answer get_answer(uint16_t id) {
    char *linepointer;
    char *tabpointer;
    Answer ret = {
        .id = id,
    };
    char *answers = get_data_file("answers.tsv");
    
    if (!answers) {
        fprintf(stderr, "Error: Unable to get data from file\n");
        return ret;
    }

    char s_id[6];
    snprintf(s_id, sizeof(s_id), "%" PRIu16, id);

    char *line = strtok_r(answers, "\n", &linepointer);  // skip header
    while ((line = strtok_r(NULL, "\n", &linepointer)) != NULL) {
        char *token = strtok_r(line, "\t", &tabpointer);
        if (strcmp(token, s_id) != 0)
            continue;

        token = strtok_r(NULL, "\t", &tabpointer);
        if (!token)
            continue;

        if (strcmp(token, "uint") == 0) {
            ret.type = UINT8;  // will adjust size later
        } else if (strcmp(token, "int") == 0) {
            ret.type = INT8;  // will adjust size later
        } else if (strcmp(token, "str") == 0) {
            ret.type = STR;
        } else {
            fprintf(stderr, "Error: Unknown type '%s'\n", token);
            return ret;
        }

        token = strtok_r(NULL, "\t", &tabpointer);
        if (!token)
            continue;
        size_t size = strtoull(token, NULL, 10);

        token = strtok_r(NULL, "\t", &tabpointer);
        if (!token)
            continue;

        switch (ret.type) {
            case UINT8:
            case UINT16:
            case UINT32:
            case UINT64:
                switch (size) {
                    case 8:
                        ret.value.UINT8 = (uint8_t)strtoul(token, NULL, 10);
                        break;
                    case 16:
                        ret.value.UINT16 = (uint16_t)strtoul(token, NULL, 10);
                        ret.type = UINT16;
                        break;
                    case 32:
                        ret.value.UINT32 = strtoul(token, NULL, 10);
                        ret.type = UINT32;
                        break;
                    case 64:
                        ret.value.UINT64 = strtoull(token, NULL, 10);
                        ret.type = UINT64;
                        break;
                    default:
                        fprintf(stderr, "Error: Unsupported uint size %" PRIu64 "\n", (uint64_t)size);
                        Answer err = {0};
                        return err;
                }
                break;
            case INT8:
            case INT16:
            case INT32:
            case INT64:
                switch (size) {
                    case 8:
                        ret.value.INT8 = (int8_t)strtol(token, NULL, 10);
                        break;
                    case 16:
                        ret.value.INT16 = (int16_t)strtol(token, NULL, 10);
                        ret.type = INT16;
                        break;
                    case 32:
                        ret.value.INT32 = strtol(token, NULL, 10);
                        ret.type = INT32;
                        break;
                    case 64:
                        ret.value.INT64 = strtoll(token, NULL, 10);
                        ret.type = INT64;
                        break;
                    default:
                        fprintf(stderr, "Error: Unsupported int size %" PRIu64 "\n", (uint64_t)size);
                        Answer err = {0};
                        return err;
                }
                break;
            case STR:
                ret.value.STR = (char *)malloc(size + 1);
                if (ret.value.STR) {
                    strncpy(ret.value.STR, token, size);
                    ret.value.STR[size] = 0;
                } else {
                    fprintf(stderr, "Error: Memory allocation failed for string\n");
                    Answer err = {0};
                    return err;
                }
                break;
            case ERROR:
                fprintf(stderr, "Error: Unknown type (should be unreachable)\n");
                Answer err = {0};
                return err;
        }
        break;
    }

    free(answers);
    return ret;
}
