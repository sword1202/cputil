//
// Created by Semyon Tikhonenko on 5/5/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H
#define VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H

#include <atomic>
#include <functional>
#include "CallbacksQueue.h"

namespace CppUtils {

    class PeriodicallySleepingBackgroundTask {
        std::atomic_bool running;
        std::function<void()> onTaskFinished;
    protected:
        // deleted automatically after task is finished, don't allocate memory without running
        // runWithSleepingIntervalInMicroseconds
        virtual ~PeriodicallySleepingBackgroundTask();
    public:

        bool isRunning() const;

        PeriodicallySleepingBackgroundTask();

        virtual void runWithSleepingIntervalInMicroseconds(const std::function<void()> &action, int64_t interval);
        void stop(std::function<void()> onTaskFinished);
        void stop();
    };

    class PeriodicallySleepingBackgroundTaskWithCallbacksQueue : public PeriodicallySleepingBackgroundTask {
        CallbacksQueue queue;
    public:
        void processQueue();
        void runWithSleepingIntervalInMicroseconds(const std::function<void()> &action, int64_t interval) override;
        void runWithSleepingIntervalInMicroseconds(int64_t interval);
        void postCallback(const std::function<void()>& callback);
    };
}


#endif //VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H
