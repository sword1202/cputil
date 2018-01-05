#ifndef CPP_UTILS_STRINGS
#define CPP_UTILS_STRINGS

#include <string>
#include <sstream>
#include <fstream>


#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

namespace CppUtils {
    namespace Strings {
        template<typename Iter, typename Char>
        std::basic_stringstream<Char> JoinToStringStream(Iter begin, Iter end, const Char* separator) {
            std::basic_stringstream<Char> stream;
            if (begin != end) {
                std::copy(begin, end - 1, std::ostream_iterator<decltype(*begin)>(stream, separator));
                stream<<*(end - 1);
            }
            return stream;
        }

        template<typename Container, typename Char>
        std::basic_stringstream<Char> JoinToStringStream(const Container& container, const Char* separator) {
            return JoinToStringStream(container.begin(), container.end(), separator);
        }

        template<typename Iter, typename Char>
        std::basic_string<Char> Join(Iter begin, Iter end, const Char* separator) {
            return JoinToStringStream(begin, end, separator).str();
        }

        template<typename Container, typename Char>
        std::basic_string<Char> Join(const Container& container, const Char* separator) {
            return JoinToStringStream(container, separator).str();
        }
        
        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> ReplaceFirst(const std::basic_string<Char, Allocator> &source,
                                                        const std::basic_string<Char, Allocator> &value,
                                                        const std::basic_string<Char, Allocator> &replacement) {
            size_t find = source.find(value);
            if (find != std::string::npos) {
                size_t resultSize = source.size() + replacement.size() - value.size();
                std::basic_string<Char, Allocator> result;
                result.resize(resultSize);
                auto begin = source.begin();
                auto i = result.begin();
                std::copy(begin, begin + find, result.begin());
                i += find;
                std::copy(replacement.begin(), replacement.end(), i);
                i += (replacement.end() - replacement.begin());
                std::copy(source.begin() + find + value.size(), source.end(), i);
                return result;
            } else {
                return source;
            }
        }

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> ReplaceFirst(const std::basic_string<Char, Allocator> &source,
                                                        const Char* value,
                                                        const Char* replacement) {
            return ReplaceFirst(source, std::basic_string<Char, Allocator>(value),
                                std::basic_string<Char, Allocator>(replacement));
        };

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> ReplaceAll(const std::basic_string<Char, Allocator> &source,
                                                      const std::basic_string<Char, Allocator> &value,
                                                      const std::basic_string<Char, Allocator> &replacement) {
            if (value.empty()) {
                return source;
            }

            std::basic_string<Char, Allocator> result;
            result.reserve(source.size());

            size_t prevI = 0;
            size_t valueLength = value.size();
            for (size_t i = source.find(value);
                 i != std::string::npos;
                 prevI = i + valueLength, i = source.find(value, i + valueLength)) {
                result.append(prevI + source.begin(), source.begin() + i);
                result.append(replacement.begin(), replacement.end());
            }

            result.append(source.begin() + prevI, source.end());
            return result;
        };

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> ReplaceAll(const std::basic_string<Char, Allocator> &source,
                                                      const Char* value,
                                                      const Char* replacement) {
            return ReplaceAll(source, std::basic_string<Char, Allocator>(value),
                              std::basic_string<Char, Allocator>(replacement));
        };

        template<typename Char, typename Allocator>
        bool StartsWith(const std::basic_string<Char, Allocator> &source,
                        const Char* value) {
            size_t sourceSize = source.size();
            for (int i = 0; value[i] != '\0'; ++i) {
                if (sourceSize <= i || value[i] != source[i]) {
                    return false;
                }
            }

            return true;
        };

        template<typename Char, typename Allocator>
        bool StartsWith(const std::basic_string<Char, Allocator> &source,
                        const std::basic_string<Char, Allocator> &value) {
            if (value.size() > source.size()) {
                return false;
            }

            return std::equal(value.begin(), value.end(), source.begin());
        };

#ifdef __OBJC__
        template<typename Iter>
        NSString* JoinToNSString(Iter begin, Iter end, const char* separator) {
            const std::stringstream &stream = JoinToStringStream(begin, end, separator);
            return [[NSString alloc] initWithCString:stream.str().c_str()];
        }

        template<typename Container>
        NSString* JoinToNSString(const Container& container, const char* separator) {
            return JoinToNSString(container.negin(), container.end(), separator);
        }
#endif

        template<typename Char>
        std::basic_string<Char> StreamToString(std::basic_istream<Char>& stream) {
            return std::basic_string<Char>(std::istreambuf_iterator<Char>(stream), {});
        }

        template<typename Char>
        std::basic_string<Char> ReadFileIntoString(const char* filePath) {
            std::basic_fstream<Char> file(filePath);
            return StreamToString(file);
        }
    }
}

#endif