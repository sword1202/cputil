//
// Created by Semyon Tikhonenko on 5/4/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_EXECUTORS_H
#define VOCALTRAINER_EXECUTORS_H

#include <assert.h>
#import <functional>

namespace CppUtils {

    namespace Executors {
        void ExecuteOnMainThreadAfterDelay(std::function<void()> function, int delayInMilliseconds);
        void ExecuteOnMainThread(std::function<void()> function);
        // don't use it for long running operations, such as downloading content, copying large files, e.t.c.
        // use std::thread instead
        void ExecuteOnBackgroundThread(std::function<void()> function);
    }

}


#endif //VOCALTRAINER_EXECUTORS_H
