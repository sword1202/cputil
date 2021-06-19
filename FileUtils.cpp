//
// Created by Semyon Tikhonenko on 6/19/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#include "FileUtils.h"

namespace CppUtils {
    namespace FileUtils {
        uint64_t GetLastWriteTimeInMicroseconds(const std::filesystem::directory_entry& directoryEntry) {
            return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(
                    directoryEntry.last_write_time().time_since_epoch()).count());
        }
    };
}