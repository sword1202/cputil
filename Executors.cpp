#include "Executors.h"
#include "Algorithms.h"
#include "NotImplementedAssert.h"

#ifdef __ANDROID__
#include "android/AndroidExecutor.h"
#endif

using namespace CppUtils;

#define LOCK std::lock_guard<std::mutex> _(mutex)

namespace CppUtils::Executors {
#ifdef __ANDROID__
    static AndroidExecutor androidExecutor;

    void ExecuteOnMainThread(const std::function<void()>& function) {
        androidExecutor.executeOnMainThread(function);
    }

    void ExecuteOnBackgroundThread(const std::function<void()>& function) {
        androidExecutor.executeOnBackgroundThread(function);
    }

    void ExecuteOnMainThreadAfterDelay(const std::function<void()>&, int delayInMilliseconds) {
        NOT_IMPLEMENTED_ASSERT
    }
#endif

    OperationCancelerPtr ExecuteCancelableOnBackgroundThread(const std::function<void()>& function) {
        auto canceler = OperationCanceler::create();
        ExecuteOnBackgroundThread([=] {
            if (canceler->isCancelled()) {
                return;
            }

            function();
        });
        return canceler;
    }

    OperationCancelerPtr ExecuteCancelableOnMainThreadAfterDelay(const std::function<void()>& function, int delayInMilliseconds) {
        auto canceler = OperationCanceler::create();
        ExecuteOnMainThreadAfterDelay([=] {
            if (canceler->isCancelled()) {
                return;
            }

            function();
        }, delayInMilliseconds);
        return canceler;
    }
}

OperationCancelerPtr OnThreadExecutor::executeOnMainThread(const std::function<void()>& function) const {
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

OperationCancelerPtr OnThreadExecutor::executeOnBackgroundThread(const std::function<void()>& function) const {
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

OperationCancelerPtr OnThreadExecutor::executeOnMainThreadAfterDelay(const std::function<void()>& function, int delayMilliseconds) const {
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
