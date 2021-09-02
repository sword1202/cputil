//
// Created by Semyon Tikhonenko on 6/19/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_FILEUTILS_H
#define VOCALTRAINER_FILEUTILS_H

#include <stdint.h>
#include <filesystem>

namespace CppUtils {
    namespace FileUtils {
        uint64_t GetLastWriteTimeInMicroseconds(const char* filePath);
        uint64_t GetLastWriteTimeInMicroseconds(const std::filesystem::directory_entry& directoryEntry);
        void CreateDirectoriesForFile(const char* filePath);
    };
}


#endif //VOCALTRAINER_FILEUTILS_H
