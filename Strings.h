#ifndef CPP_UTILS_STRINGS
#define CPP_UTILS_STRINGS

#import <string>
#import <sstream>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

namespace CppUtils {
    namespace Strings {
        template<typename Iter>
        std::stringstream JoinToStringStream(Iter begin, Iter end, const char* separator) {
            std::stringstream stream;
            std::copy(begin, end, std::ostream_iterator<char>(stream, separator));
            return stream;
        }

        template<typename Container>
        std::stringstream JoinToStringStream(const Container& container, const char* separator) {
            return JoinToStringStream(container.begin(), container.end(), separator);
        }

        template<typename Iter>
        std::string Join(Iter begin, Iter end, const char* separator) {
            return JoinToStringStream(begin, end, separator).str();
        }

        template<typename Container>
        std::string Join(const Container& container, const char* separator) {
            return JoinToStringStream(container, separator).str();
        }
        
        template<typename String, typename Char>
        String Replace(const String& source, const Char* replacement) {
            size_t find = source.find(replacement);
            if (find != std::string::npos) {
                size_t resultSize =
                String result();
            } else {
                return source;
            }
        }

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
    }
}

#endif