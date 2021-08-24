//
// Created by Semyon Tykhonenko on 8/25/19.
// Copyright (c) 2019 Semyon Tikhonenko. All rights reserved.
//

#include "Timer.h"
#include "Executors.h"
#include "TimeUtils.h"
#include "MathUtils.h"

using namespace CppUtils;
using namespace Math;

bool Timer::isRunning() const {
    return operationCanceler && !operationCanceler->isCancelled();
}

void Timer::start(int intervalInMilliseconds, const std::function<void()> &callback, int delay) {
    if (delay < 0) {
        this->initialDelay = intervalInMilliseconds;
    } else {
        this->initialDelay = delay;
    }

    assert(!isRunning());
    assert(intervalInMilliseconds > 0);
    this->iterationsCount = 0;
    this->callback = callback;
    this->intervalInMilliseconds = intervalInMilliseconds;
    timeSeek = TimeUtils::NowInMicrosecondsSinceStart();
    timerStartedTime = timeSeek;
    lastIterationTimeInMicroseconds = 0;
    currentInterval = initialDelay;
    action(currentInterval);
}
void Timer::stop() {
    assert(isRunning());
    operationCanceler->cancel();
    onStop();
}

void Timer::action(int interval) {
    operationCanceler = Executors::ExecuteCancelableOnMainThreadAfterDelay([=] {
        callback();
        int64_t now = TimeUtils::NowInMicrosecondsSinceStart();
        int timeDiff = RoundToInt(int(now - timeSeek) / 1000.0);
        timeSeek = now;
        lastIterationTimeInMicroseconds = now;
        auto delay = currentInterval * 2 - timeDiff;
        if (delay < 0) {
            delay = 0;
        }

        if (iterationsCount == 1) {
            this->currentInterval = intervalInMilliseconds;
        }

        iterationsCount++;

        this->action(delay);
    }, interval);
}

int Timer::getIterationsCount() const {
    return iterationsCount;
}

int Timer::getIntervalInMilliseconds() const {
    return intervalInMilliseconds;
}

int Timer::getInitialDelayInMilliseconds() const {
    return initialDelay;
}

int64_t Timer::getLastIterationTimeInMicroseconds() const {
    return lastIterationTimeInMicroseconds;
}

int64_t Timer::getTimerStartedTime() const {
    return timerStartedTime;
}

Timer::~Timer() {
    operationCanceler->cancel();
}
