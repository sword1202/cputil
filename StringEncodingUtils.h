//
// Created by Semyon Tikhonenko on 2/22/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_STRINGENCODINGUTILS_H
#define VOCALTRAINER_STRINGENCODINGUTILS_H

#include <string>

namespace CppUtils {
    namespace UtfUtils {
        std::string ToUtf8(std::string const & s);
        std::string ToUtf8(std::u32string const & s);
        std::string ToUtf8(std::wstring const & s);
        std::wstring ToWString(std::wstring const & s);
        std::wstring ToWString(std::string const & s);
        std::wstring ToWString(std::u32string const & s);
        std::u16string ToUtf16(std::string const & s);
        std::u16string ToUtf16(std::u16string const & s);
        std::u32string ToUtf32(std::u32string const & s);
        std::u32string ToUtf32(std::string const & s);
        std::u32string ToUtf32(std::wstring const & s);
    };
}


#endif //VOCALTRAINER_STRINGENCODINGUTILS_H
