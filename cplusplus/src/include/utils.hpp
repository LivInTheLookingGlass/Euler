#pragma once

#include <cerrno>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <sstream>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
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
