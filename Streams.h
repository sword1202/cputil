#ifndef CPP_UTILS_STREAMS
#define CPP_UTILS_STREAMS

#include <fstream>
#include <sstream>

namespace CppUtils {
    namespace Streams {
        template <typename Char = char>
        std::basic_fstream<Char> OpenFile(const char* filePath, std::ios::openmode openmode) {
            std::basic_fstream<Char> file(filePath, openmode);
            if (!file.is_open()) {
                std::stringstream error;
                error<<"Unable to open file "<<filePath<<": "<< strerror(errno);
                throw std::runtime_error(error.str());
            }

            return file;
        }
    }
}

#endif //CPP_UTILS_STREAMS