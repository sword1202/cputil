//
// Created by Semyon Tykhonenko on 8/25/19.
// Copyright (c) 2019 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_TIMER_H
#define VOCALTRAINER_TIMER_H

#include <functional>
#include "OperationCanceler.h"

namespace CppUtils {
    class Timer {
        int intervalInMilliseconds;
        std::function<void()> callback;
        OperationCancelerPtr operationCanceler;
        int64_t timeSeek;
        void action(int interval);
    public:
        void start(int intervalInMilliseconds, const std::function<void()> &callback);
        void stop();
        bool isRunning() const;
    };
}

#endif //VOCALTRAINER_TIMER_H
