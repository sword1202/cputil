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
    }

}


#endif //VOCALTRAINER_EXECUTORS_H
