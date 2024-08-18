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
	ERR,
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
            answer.type = UINT8;  // will adjust size later
        } else if (token == "int") {
            answer.type = INT8;  // will adjust size later
        } else if (token == "str") {
            answer.type = STR;
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
            case UINT8:
                switch (size) {
                    case 8:
                        answer.value.UINT8 = (uint8_t)strtoul(token.c_str(), NULL, 10);
                        break;
                    case 16:
                        answer.value.UINT16 = (uint16_t)strtoul(token.c_str(), NULL, 10);
                        answer.type = UINT16;
                        break;
                    case 32:
                        answer.value.UINT32 = strtoul(token.c_str(), NULL, 10);
                        answer.type = UINT32;
                        break;
                    case 64:
                        answer.value.UINT64 = strtoull(token.c_str(), NULL, 10);
                        answer.type = UINT64;
                        break;
                    default:
                        std::cerr << "Error: Unsupported int size " << size << "'\n";
                        Answer err = {{0}};
                        return err;
                }
                break;
            case INT8:
                switch (size) {
                    case 8:
                        answer.value.INT8 = (int8_t)strtol(token.c_str(), NULL, 10);
                        break;
                    case 16:
                        answer.value.INT16 = (int16_t)strtol(token.c_str(), NULL, 10);
                        answer.type = INT16;
                        break;
                    case 32:
                        answer.value.INT32 = strtol(token.c_str(), NULL, 10);
                        answer.type = INT32;
                        break;
                    case 64:
                        answer.value.INT64 = strtoll(token.c_str(), NULL, 10);
                        answer.type = INT64;
                        break;
                    default:
                        std::cerr << "Error: Unsupported uint size " << size << "'\n";
                        Answer err = {{0}};
                        return err;
                }
                break;
            case STR:
                answer.value.STR = (char *)malloc(size + 1);
                if (answer.value.STR) {
                    strncpy(answer.value.STR, token.c_str(), size);
                    answer.value.STR[size] = 0;
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
