//
// Created by Semyon Tikhonenko on 5/4/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_EXECUTORS_H
#define VOCALTRAINER_EXECUTORS_H

#include <assert.h>

#include <functional>
#include "OperationCanceler.h"
#include <vector>
#include <mutex>

namespace CppUtils {

    namespace Executors {
        void ExecuteOnMainThreadAfterDelay(const std::function<void()>&, int delayInMilliseconds);
        OperationCancelerPtr ExecuteCancelableOnMainThreadAfterDelay(const std::function<void()>&, int delayInMilliseconds);
        void ExecuteOnMainThread(const std::function<void()>& function);
        OperationCancelerPtr ExecuteCancelableOnMainThread(const std::function<void()>& function);
        // don't use it for long running operations, such as downloading content, copying large files, e.t.c.
        // use std::thread instead
        void ExecuteOnBackgroundThread(const std::function<void()>& function);
        OperationCancelerPtr ExecuteCancelableOnBackgroundThread(const std::function<void()>& function);
    }

    // Inherit your class from OnThreadExecutor to run actions on main and background thread, the actions are automatically deleted when the object is destroyed
    class OnThreadExecutor {
        mutable std::vector<OperationCancelerPtr> operations;
        mutable std::mutex mutex;
    public:
        OperationCancelerPtr executeOnMainThread(const std::function<void()>& function) const;
        OperationCancelerPtr executeOnMainThreadAfterDelay(const std::function<void()>& function, int delayMilliseconds) const;
        OperationCancelerPtr executeOnBackgroundThread(const std::function<void()>& function) const;
        void cancelAllOperations();
        ~OnThreadExecutor();
    };
}


#endif //VOCALTRAINER_EXECUTORS_H
