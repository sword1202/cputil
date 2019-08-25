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

void Timer::start(int intervalInMilliseconds, const std::function<void()> &callback) {
    assert(!isRunning());
    assert(intervalInMilliseconds > 0);
    this->callback = callback;
    this->intervalInMilliseconds = intervalInMilliseconds;
    timeSeek = TimeUtils::NowInMicroseconds();
    action(intervalInMilliseconds);
}
void Timer::stop() {
    assert(isRunning());
    operationCanceler->cancel();
}

void Timer::action(int interval) {
    operationCanceler = Executors::ExecuteCancelableOnMainThreadAfterDelay([=] {
        callback();
        int64_t now = TimeUtils::NowInMicroseconds();
        int timeDiff = RoundToInt(int(now - timeSeek) / 1000.0);
        timeSeek = now;
        auto delay = intervalInMilliseconds * 2 - timeDiff;
        if (delay < 0) {
            delay = 0;
        }

        this->action(delay);
    }, interval);
}