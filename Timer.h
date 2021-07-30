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
        int currentInterval;
        int initialDelay = -1;
        int iterationsCount = 0;
        int64_t lastIterationTimeInMicroseconds = 0;
        std::function<void()> callback;
        OperationCancelerPtr operationCanceler;
        int64_t timeSeek;
        int64_t timerStartedTime;
        void action(int interval);
    public:
        std::function<void()> onStop;

        void start(int intervalInMilliseconds, const std::function<void()> &callback, int delay = -1);
        void stop();
        bool isRunning() const;
        int getIterationsCount() const;
        int getIntervalInMilliseconds() const;
        int getInitialDelayInMilliseconds() const;
        int64_t getLastIterationTimeInMicroseconds() const;
        int64_t getTimerStartedTime() const;

        ~Timer();
    };
}

#endif //VOCALTRAINER_TIMER_H
