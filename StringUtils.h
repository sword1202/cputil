#ifndef CPP_UTILS_STRINGS
#define CPP_UTILS_STRINGS

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Streams.h"

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

namespace CppUtils {
    namespace Strings {
#ifdef __OBJC__
        template<typename StdString>
        NSString* ToNSString(const StdString& str) {
            return [NSString stringWithCString:str.data()
                                      encoding:[NSString defaultCStringEncoding]];
        }

        inline NSString* ToNSString(const char* str) {
            return [NSString stringWithCString:str
                                      encoding:[NSString defaultCStringEncoding]];
        }
#endif

        template<typename Iter, typename Char>
        void JoinToStream(std::basic_ostream<Char>& stream, Iter begin, Iter end, const Char* separator) {
            if (begin != end) {
                std::copy(begin, end - 1, std::ostream_iterator<decltype(*begin)>(stream, separator));
                stream<<*(end - 1);
            }
        }

        template<typename Iter, typename Char>
        std::basic_stringstream<Char> JoinToStringStream(Iter begin, Iter end, const Char* separator) {
            std::basic_stringstream<Char> stream;
            JoinToStream(stream, begin, end, separator);
            return stream;
        }

        template<typename Iter, typename Char, typename StreamWriter>
        void JoinToStream(std::basic_ostream<Char>& stream,
                Iter begin, Iter end, const Char* separator, const StreamWriter& streamWriter) {
            while (begin != end - 1) {
                streamWriter(stream, *begin);
                stream<<separator;
                begin++;
            }

            if (begin != end) {
                streamWriter(stream, *begin);
            }
        }

        template<typename Container, typename Char, typename StreamWriter>
        void JoinToStream(std::basic_ostream<Char>& stream,
                const Container& container, const Char* separator, const StreamWriter& streamWriter) {
            JoinToStream(stream, container.begin(), container.end(), separator, streamWriter);
        };

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

        template<typename Char = char>
        std::basic_string<Char> ReadBinaryFileContent(const char* filePath) {
            std::basic_fstream<Char> file = Streams::OpenFile(filePath, std::ios::binary | std::ios::in);
            return StreamToString(file);
        }

        template<typename Char = char>
        std::basic_string<Char> ReadFileIntoString(const char* filePath) {
            std::basic_fstream<Char> file = Streams::OpenFile(filePath, std::ios::in);
            return StreamToString(file);
        }

        template<typename Char>
        void WriteToFile(const char* filePath, const Char* data, int size) {
            std::basic_fstream<Char> file = Streams::OpenFile(filePath, std::ios::out);
            file.write(data, size);
        }

        template<typename String>
        void WriteStringToFile(const char* filePath, const String& string) {
            WriteToFile(filePath, string.data(), string.size());
        }

        template<typename Char>
        std::basic_string<Char> ReadUntilTokenOrEof(std::basic_istream<Char>& is, const Char* token) {
            std::string result;
            Char ch;
            int tokenIndex = 0;
            while (!is.eof()) {
                Char tokenCh = token[tokenIndex];
                if (tokenCh == (Char)'\0'){
                    result.erase(result.end() - tokenIndex, result.end());
                    return result;
                }

                ch = is.get();
                result.push_back(ch);
                if (tokenCh == ch) {
                    tokenIndex++;
                } else {
                    tokenIndex = 0;
                }
            }

            return result;
        }

        template<typename Char>
        // [begin, end)
        std::vector<std::basic_string<Char>> Split(const std::basic_string<Char>& string, int begin, int end, char delimiter) {
            std::vector<std::basic_string<Char>> result;
            if (string.empty()) {
                return result;
            }

            for (int i = begin; i < end; ++i) {
                char ch = string[i];
                if (ch == delimiter) {
                    auto substr = string.substr(begin, i - begin);
                    begin = i + 1;
                    result.push_back(substr);
                }
            }

            auto substr = string.substr(begin, end - begin);
            result.push_back(substr);

            return result;
        }

        template<typename Char>
        // [begin, end)
        std::vector<std::basic_string<Char>> Split(const Char* string, int begin, int end, char delimiter) {
            return Split(std::basic_string<Char>(string), begin, end, delimiter);
        }

        template<typename Char>
        std::vector<std::basic_string<Char>> Split(const std::basic_string<Char>& string, Char delimiter) {
            return Split(string, 0, string.size(), delimiter);
        }

        template<typename Char>
        std::vector<std::basic_string<Char>> Split(const Char* string, Char delimiter) {
            return Split(std::basic_string<Char>(string), delimiter);
        }

        template<typename Char>
        std::vector<int> SplitIntegers(const std::basic_string<Char>& string, 
                int begin, int end, Char delimiter, bool* success) {
            std::vector<int> result;
            auto split = Split(string, begin, end, delimiter);
            for (const auto& str : split) {
                int value;
                try {
                    value = std::stoi(str);
                } catch (...) {
                    *success = false;
                    return result;
                }

                result.push_back(value);
            }

            *success = true;
            return result;
        }

        template<typename Char>
        std::vector<int> SplitIntegers(const Char* string,
                int begin, int end, Char delimiter, bool* success) {
            return SplitIntegers(std::basic_string<Char>(string), begin, end, delimiter, success);
        }

        template <typename String>
        bool IsUpperCase(const String& string) {
            return std::all_of(string.begin(), string.end(), [] (decltype(*string.begin()) ch) {
                return std::isupper(ch);
            });
        }

        template <typename Char>
        void Append(std::basic_stringstream<Char>& stream) {}

        template <typename Char, typename Arg, typename... Args>
        void Append(std::basic_stringstream<Char>& stream, const Arg& arg, Args... args) {
            stream<<arg;
            Append(stream, args...);
        }

        template <typename Char, typename... Args>
        std::basic_string<Char> ToString(Args... args) {
            std::basic_stringstream<Char> stream;
            Append(stream, args...);
            return stream.str();
        }

        template <typename... Args>
        std::string ToString(Args... args) {
            return ToString<char>(args...);
        }

        template<typename Char>
        std::basic_string<Char> FromVector(const std::vector<Char>& vec) {
            return std::basic_string<Char>(vec.begin(), vec.end());
        }
    }
}

#endif