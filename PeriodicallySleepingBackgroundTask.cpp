//
// Created by Semyon Tikhonenko on 5/5/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#include "PeriodicallySleepingBackgroundTask.h"
#include <thread>

using namespace CppUtils;

PeriodicallySleepingBackgroundTask::PeriodicallySleepingBackgroundTask() : running(false) {
}

void PeriodicallySleepingBackgroundTask::runWithSleepingIntervalInMicroseconds(
        const std::function<void()> &action, int64_t interval) {
    assert(!running);
    std::thread thread([=] {
        while (running) {
            action();
            std::this_thread::sleep_for(std::chrono::microseconds(interval));
        }
        if (onTaskFinished) {
            onTaskFinished();
            onTaskFinished = nullptr;
        }
    });
    thread.detach();
}

PeriodicallySleepingBackgroundTask::~PeriodicallySleepingBackgroundTask() {
    running = false;
}

void PeriodicallySleepingBackgroundTask::stop(std::function<void()> onTaskFinished) {
    assert(running);
    this->onTaskFinished = onTaskFinished;
    running = false;
}

void PeriodicallySleepingBackgroundTask::stop() {
    assert(running);
    running = false;
}
