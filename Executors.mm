#include "Executors.h"

#import <dispatch/dispatch.h>
#include <thread>

namespace CppUtils {
    namespace Executors {

        namespace {
            const std::thread::id MAIN_THREAD_ID = std::this_thread::get_id();
        }

        void ExecuteOnMainThreadAfterDelay(std::function<void()> function, int delayInMilliseconds) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, delayInMilliseconds * NSEC_PER_SEC / 1000),
                dispatch_get_main_queue(), ^{
                    function();
                });
        }

        OperationCancelerPtr ExecuteCancelableOnMainThreadAfterDelay(std::function<void()> function, int delayInMilliseconds) {
            auto canceler = OperationCanceler::create();
            ExecuteOnMainThreadAfterDelay([=] {
                if (canceler->isCancelled()) {
                    return;
                }

                function();
            }, delayInMilliseconds);
            return canceler;
        }

        void ExecuteOnMainThread(std::function<void()> function) {
            if (std::this_thread::get_id() == MAIN_THREAD_ID) {
                function();
            }

            dispatch_async(dispatch_get_main_queue(), ^{
                function();
            });
        }

        void ExecuteOnBackgroundThread(std::function<void()> function) {
            dispatch_async(dispatch_get_global_queue( DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                function();
            });
        }
}}