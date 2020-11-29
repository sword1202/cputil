#ifndef CPP_UTILS_STRINGS
#define CPP_UTILS_STRINGS

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

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

        const std::string EMPTY = "";

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

        template<typename Char, typename FilterPredicate>
        std::vector<std::basic_string<Char>> ReadAllIntoLines(std::basic_istream<Char>& is,
                const FilterPredicate& predicate) {
            std::vector<std::basic_string<Char>> result;
            std::string line;
            char ch;
            while (true) {
                ch = Char(is.get());
                if (is.eof()) {
                    break;
                }

                if (ch == '\n') {
                    if (predicate(line)) {
                        result.push_back(line);
                    }
                    line.clear();
                } else {
                    line += ch;
                }
            }

            if (ch != '\n') {
                result.push_back(line);
            }

            return result;
        }

        template<typename Char, typename FilterPredicate>
        std::vector<std::basic_string<Char>> ReadAllIntoLines(const char* filePath,
                const FilterPredicate& predicate) {
            std::basic_fstream<Char> is = Streams::OpenFile<Char>(filePath, std::ios::in);
            return ReadAllIntoLines(is, predicate);
        }

        template<typename Char = char>
        std::vector<std::basic_string<Char>> ReadAllIntoLines(const char* filePath) {
            return ReadAllIntoLines<Char>(filePath, [] (const std::basic_string<Char>&) {return true;});
        }

        template<typename Char>
        std::vector<std::basic_string<Char>> ReadAllIntoLines(std::basic_istream<Char>& is) {
            return ReadAllIntoLines(is, [] (const std::basic_string<Char>&) {return true;});
        }

        template<typename LinesContainer>
        void WriteLines(std::ostream& os, const LinesContainer& linesContainer) {
            JoinToStream(os, linesContainer.begin(), linesContainer.end(), "\n");
        }

        template<typename LinesContainer>
        void WriteLinesToFile(const char* filePath, const LinesContainer& linesContainer) {
            auto os = Streams::OpenFile<typename LinesContainer::value_type::value_type>(filePath, std::ios::out);
            WriteLines(os, linesContainer);
        }

        namespace {
            const int ASCII_HEX_TABLE[] = {
                    // ASCII
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
                    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

                    // 0x80-FF (Omit this if you don't need to check for non-ASCII)
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
            };

            const char* HEX_BYTE_STRING_TABLE[] = {
                    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
                    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
                    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
                    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
                    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
                    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
                    "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
                    "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
                    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
                    "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
                    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
                    "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
                    "c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
                    "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df",
                    "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
                    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
            };
        }

        inline unsigned char ParseHexByte(const char* str) {
            assert(strlen(str) >= 2);
            int digit1 = ASCII_HEX_TABLE[str[0]];
            int digit2 = ASCII_HEX_TABLE[str[1]];

            assert(digit1 >= 0 && digit2 >= 0);
            return static_cast<unsigned char>(digit1 * 16 + digit2);
        }

        inline const char* ToHexByteString(unsigned char byte) {
            return HEX_BYTE_STRING_TABLE[byte];
        }

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> GetFileNameWithoutExtension(const std::basic_string<Char, Allocator>& fileName) {
            auto dotIndex = fileName.find_last_of('.');
            return std::basic_string<Char, Allocator>(fileName.begin(), fileName.begin() + dotIndex);
        }

        template<typename Char>
        std::basic_string<Char> GetFileNameWithoutExtension(const Char* fileName) {
            return GetFileNameWithoutExtension(std::basic_string<Char>(fileName));
        }

        template<typename Char, typename Allocator>
        int ParseInt(const std::basic_string<Char, Allocator>& str, int defaultValue = 0) {
            try {
                return std::stoi(str);
            } catch (std::exception& e) {
                return defaultValue;
            }
        }

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> Unquote(const std::basic_string<Char, Allocator>& str, Char quote = '"') {
            if (str.front() == quote && str.back() == quote) {
                return str.substr(1, str.size() - 2);
            } else {
                return str;
            }
        }

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> RemoveLongestPrefixEndingWith(
                const std::basic_string<Char, Allocator>& str,
                const std::basic_string<Char, Allocator>& prefixEnding)
        {
            auto index = str.find_last_of(prefixEnding);
            if (index == std::string::npos) {
                return str;
            }

            return str.substr(index + prefixEnding.size());
        }

        template<typename Char, typename Allocator>
        std::basic_string<Char, Allocator> RemoveLongestPrefixEndingWith(
                const std::basic_string<Char, Allocator>& str,
                const Char* prefixEnding)
        {
            return RemoveLongestPrefixEndingWith(str, std::basic_string<Char, Allocator>(prefixEnding));
        }

        template<typename Char, typename Allocator>
        void ExtractFilenameAndExtension(
                const std::basic_string<Char, Allocator>& str,
                std::basic_string<Char, Allocator>* name,
                std::basic_string<Char, Allocator>* extension)
        {
            auto indexOfDot = str.find_last_of('.');
            if (indexOfDot == std::string::npos) {
                *name = str;
                *extension = "";
            } else {
                *name = str.substr(0, indexOfDot);
                *extension = str.substr(indexOfDot + 1);
            }
        }
    }
}

#endif
