//
// Created by Semyon Tikhonenko on 5/5/18.
// Copyright (c) 2018 Mac. All rights reserved.
//

#ifndef VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H
#define VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H

#include <atomic>
#include <functional>

namespace CppUtils {

    class PeriodicallySleepingBackgroundTask {
        std::atomic_bool running;
        std::function<void()> onTaskFinished;
    public:

        PeriodicallySleepingBackgroundTask();
        ~PeriodicallySleepingBackgroundTask();
        void runWithSleepingIntervalInMicroseconds(const std::function<void()> &action, int64_t interval);
        void stop(std::function<void()> onTaskFinished);
        void stop();
    };
}


#endif //VOCALTRAINER_LONGRUNNINGBACKGROUNDTASK_H
