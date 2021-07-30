#include "Executors.h"
#include "Algorithms.h"

using namespace CppUtils;

#define LOCK std::lock_guard<std::mutex> _(mutex)

OperationCancelerPtr OnThreadExecutor::executeOnMainThread(std::function<void()> function) const {
    auto canceler = OperationCanceler::create();
    {
        LOCK;
        operations.push_back(canceler);
    }
    Executors::ExecuteOnMainThread([=] {
        if (canceler->isCancelled()) {
            return;
        }

        {
            LOCK;
            Remove(operations, canceler);
        }
        function();
    });
    return canceler;
}

OperationCancelerPtr OnThreadExecutor::executeOnBackgroundThread(std::function<void()> function) const {
    auto canceler = OperationCanceler::create();
    Executors::ExecuteOnBackgroundThread([=] {
        if (canceler->isCancelled()) {
            return;
        }

        {
            LOCK;
            Remove(operations, canceler);
        }
        function();
    });
    {
        LOCK;
        operations.push_back(canceler);
    }
    return canceler;
}

OperationCancelerPtr OnThreadExecutor::executeOnMainThreadAfterDelay(std::function<void()> function, int delayMilliseconds) const {
    auto canceler = OperationCanceler::create();
    Executors::ExecuteCancelableOnMainThreadAfterDelay([=] {
        if (canceler->isCancelled()) {
            return;
        }

        {
            LOCK;
            Remove(operations, canceler);
        }
        function();
    }, delayMilliseconds);
    {
        LOCK;
        operations.push_back(canceler);
    }
    return canceler;
}

OnThreadExecutor::~OnThreadExecutor() {
    cancelAllOperations();
}

void OnThreadExecutor::cancelAllOperations() {
    LOCK;
    for (const auto& o : operations) {
        o->cancel();
    }
    operations.clear();
}
