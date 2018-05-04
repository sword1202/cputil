#include "Executors.h"

#import <dispatch/dispatch.h>

namespace CppUtils {
    namespace Executors {

        void ExecuteOnMainThreadAfterDelay(std::function<void()> function, int delayInMilliseconds) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, delayInMilliseconds * NSEC_PER_SEC / 1000),
                dispatch_get_main_queue(), ^{
                    function();
                });
        }

        void ExecuteOnMainThread(std::function<void()> function) {
            dispatch_async(dispatch_get_main_queue(), ^{
                function();
            });
        }
}}