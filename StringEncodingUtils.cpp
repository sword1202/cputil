//
// Created by Semyon Tikhonenko on 2/22/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#include "StringEncodingUtils.h"

#include <codecvt>
#include <iterator>
#include <locale>
#include <string>
#include <vector>

namespace CppUtils {
    namespace UtfUtils {

#ifdef _MSC_VER

        std::string ToUtf8(std::u32string const & s)
        {
            std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
            auto const p = reinterpret_cast<int32_t const *>(s.data());
            return convert.to_bytes(p, p + s.size());
        }

        std::u16string ToUtf16(std::string const & s)
        {
            std::wstring_convert<std::codecvt_utf8<int16_t>, int16_t> convert;
            auto asInt = convert.from_bytes(s);
            return std::u16string(reinterpret_cast<char16_t const *>(asInt.data()), asInt.length());
        }

        std::u32string ToUtf32(std::string const & s)
        {
            std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
            auto asInt = convert.from_bytes(s);
            return std::u32string(reinterpret_cast<char32_t const *>(asInt.data()), asInt.length());
        }

#else

        std::string ToUtf8(std::u16string const &s) {
            std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv;
            return conv.to_bytes(s);
        }

        std::string ToUtf8(std::u32string const &s) {
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
            return conv.to_bytes(s);
        }

        std::u16string ToUtf16(std::string const &s) {
            std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
            return convert.from_bytes(s);
        }

        std::u32string ToUtf32(std::string const &s) {
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
            return conv.from_bytes(s);
        }

#endif

        std::string ToUtf8(std::string const &s) {
            return s;
        }

        std::string ToUtf8(std::wstring const &s) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            auto const p = reinterpret_cast<wchar_t const *>(s.data());
            return convert.to_bytes(p, p + s.size());
        }

        std::wstring ToWString(std::wstring const &s) {
            return s;
        }

        std::wstring ToWString(std::string const &s) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            auto asInt = convert.from_bytes(s);
            return std::wstring(reinterpret_cast<wchar_t const *>(asInt.data()), asInt.length());
        }

        std::wstring ToWString(std::u32string const &s) {
            return ToWString(ToUtf8(s));
        }

        std::u16string ToUtf16(std::u16string const &s) {
            return s;
        }

        std::u16string ToUtf16(std::wstring const &s) {
            return ToUtf16(ToUtf8(s));
        }

        std::u32string ToUtf32(std::u32string const &s) {
            return s;
        }

        std::u32string ToUtf32(std::wstring const &s) {
            return ToUtf32(ToUtf8(s));
        }
    }
}