#pragma once

#include <cerrno>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <inttypes.h>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <libgen.h>
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

#ifndef MAX_PATH
#define MAX_PATH 4096
#endif

std::string get_parent_directory(const std::string &path, const uint32_t levels) {
    std::string dir = path;
    for (uint32_t i = 0; i < levels; ++i) {
        size_t pos = dir.find_last_of(PATH_SEPARATOR);
        if (pos != std::string::npos) {
            dir.erase(pos);
        } else {
            break;
        }
    }
    return dir;
}

std::string get_data_file(const std::string &name) {
    char absolute_path[MAX_PATH];
#ifdef _WIN32
    if (!_fullpath(absolute_path, __FILE__, sizeof(absolute_path))) {
        std::ostringstream oss;
        oss << "_fullpath failed with error code " << GetLastError();
        throw std::runtime_error(oss.str());
    }
#else
    if (!realpath(__FILE__, absolute_path)) {
        std::ostringstream oss;
        oss << "realpath failed with error code " << errno;
        throw std::runtime_error(oss.str());
    }
#endif

    std::string file_path = get_parent_directory(std::string(absolute_path), 4) + PATH_SEPARATOR "_data" PATH_SEPARATOR + name;
    std::ifstream file(file_path.c_str(), std::ios::in | std::ios::binary);
    if (!file) {
        std::ostringstream oss;
        oss << "Failed to open file: " << file_path << " with error code " << errno;
        throw std::runtime_error(oss.str());
    }

    std::ostringstream content_stream;
    content_stream << file.rdbuf();
    if (!file) {
        std::ostringstream oss;
        oss << "Error reading file: " << file_path << " with error code " << errno;
        throw std::runtime_error(oss.str());
    }

    return content_stream.str();
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
	STRINGT
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

Answer get_answer(const uint16_t id) {
    Answer answer;
    char c_id[6];
    snprintf(c_id, sizeof(c_id), "%" PRIu16, id);
    std::string s_id(c_id);
    std::string answers = get_data_file("answers.tsv");
    if (answers.empty()) {
        std::cerr << "Error: Failed to read data from file\n";
        return answer;
    }

    std::string line;
    std::istringstream stream(answers);

    // Read and skip the header
    if (!std::getline(stream, line)) {
        std::cerr << "Error: Empty or invalid input\n";
        return answer;
    }

    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        std::string token;

        if (!std::getline(lineStream, token, '\t') || token != s_id)
            continue;

        if (!std::getline(lineStream, token, '\t'))
            continue;

        if (token == "uint") {
            answer.type = UINT8T;  // will adjust size later
        } else if (token == "int") {
            answer.type = INT8T;  // will adjust size later
        } else if (token == "str") {
            answer.type = STRINGT;
        } else {
            std::cerr << "Error: Unknown type '" << token << "'\n";
            return answer;
        }

        if (!std::getline(lineStream, token, '\t'))
            continue;
        size_t size = strtoull(token.c_str(), NULL, 10);

        if (!std::getline(lineStream, token, '\t'))
            continue;

        switch (answer.type) {
            case UINT8T:
                switch (size) {
                    case 8:
                        answer.value.uint8 = (uint8_t)strtoul(token.c_str(), NULL, 10);
                        break;
                    case 16:
                        answer.value.uint16 = (uint16_t)strtoul(token.c_str(), NULL, 10);
                        answer.type = UINT16T;
                        break;
                    case 32:
                        answer.value.uint32 = strtoul(token.c_str(), NULL, 10);
                        answer.type = UINT32T;
                        break;
                    case 64:
                        answer.value.uint64 = strtoull(token.c_str(), NULL, 10);
                        answer.type = UINT64T;
                        break;
                    default:
                        std::cerr << "Error: Unsupported int size " << size << "'\n";
                        Answer err = {{0}};
                        return err;
                }
                break;
            case INT8T:
                switch (size) {
                    case 8:
                        answer.value.int8 = (int8_t)strtol(token.c_str(), NULL, 10);
                        break;
                    case 16:
                        answer.value.int16 = (int16_t)strtol(token.c_str(), NULL, 10);
                        answer.type = INT16T;
                        break;
                    case 32:
                        answer.value.int32 = strtol(token.c_str(), NULL, 10);
                        answer.type = INT32T;
                        break;
                    case 64:
                        answer.value.int64 = strtoll(token.c_str(), NULL, 10);
                        answer.type = INT64T;
                        break;
                    default:
                        std::cerr << "Error: Unsupported uint size " << size << "'\n";
                        Answer err = {{0}};
                        return err;
                }
                break;
            case STRINGT:
                answer.value.string = (char *)malloc(size + 1);
                if (answer.value.string) {
                    strncpy(answer.value.string, token.c_str(), size);
                    answer.value.string[size] = 0;
                } else {
                        std::cerr << "Error: Memory allocation failed for string\n";
                    Answer err = {{0}};
                    return err;
                }
                break;
            default:
                std::cerr << "Error: Unknown type (should be unreachable)\n";
                Answer err = {{0}};
                return err;
        }
    }

    return answer;
}
