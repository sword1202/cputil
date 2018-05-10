//
// Created by Semyon Tikhonenko on 5/5/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H
#define VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H

#include <atomic>
#include <functional>
#include "SynchronizedCallbacksQueue.h"

namespace CppUtils {

    class PeriodicallySleepingBackgroundTask {
        std::atomic_bool running;
        std::function<void()> onTaskFinished;
    public:

        bool isRunning() const;

        PeriodicallySleepingBackgroundTask();
        ~PeriodicallySleepingBackgroundTask();

        virtual void runWithSleepingIntervalInMicroseconds(const std::function<void()> &action, int64_t interval);
        void stop(std::function<void()> onTaskFinished);
        void stop();
    };

    class PeriodicallySleepingBackgroundTaskWithCallbacksQueue : public PeriodicallySleepingBackgroundTask {
        SynchronizedCallbacksQueue queue;
    public:
        void processQueue();
        void runWithSleepingIntervalInMicroseconds(const std::function<void()> &action, int64_t interval) override;
        void runWithSleepingIntervalInMicroseconds(int64_t interval);
        void postCallback(const std::function<void()>& callback);
    };
}


#endif //VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H
