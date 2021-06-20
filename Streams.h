#ifndef CPP_UTILS_STREAMS
#define CPP_UTILS_STREAMS

#include <fstream>
#include <sstream>
#include <cstring>
#include <memory>
#include "FileUtils.h"

namespace CppUtils {
    namespace Streams {
        namespace {
            template <typename Char>
            void CheckFile(const char* filePath, std::basic_fstream<Char>& file) {
                if (!file.is_open()) {
                    std::stringstream error;
                    error << "Unable to open file " << filePath << ": " << strerror(errno);
                    throw std::runtime_error(error.str());
                }
            }
        }

        template <typename Char = char>
        std::basic_fstream<Char> OpenFile(const char* filePath, std::ios::openmode openmode, bool makedirs = true) {
            if (makedirs && openmode & std::ios::out) {
                FileUtils::CreateDirectoriesForFile(filePath);
            }
            std::basic_fstream<Char> file(filePath, openmode);
            CheckFile(filePath, file);
            return file;
        }

        template <typename Char = char>
        std::shared_ptr<std::basic_fstream<Char>> OpenFileAsSharedPtr(const char* filePath, std::ios::openmode openmode, bool makedirs = true) {
            if (makedirs && openmode & std::ios::out) {
                FileUtils::CreateDirectoriesForFile(filePath);
            }

            std::shared_ptr<std::basic_fstream<Char>> file = std::make_shared<std::basic_fstream<Char>>(filePath, openmode);
            CheckFile(filePath, *file.get());

            return file;
        }
    }
}

#endif //CPP_UTILS_STREAMS
