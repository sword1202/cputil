//
// Created by Semyon Tykhonenko on 2019-06-28.
//

#ifndef TEXTIMAGESGENERATOR_DESTRUCTORQUEUE_H
#define TEXTIMAGESGENERATOR_DESTRUCTORQUEUE_H

#include "CallbacksQueue.h"

namespace CppUtils {
    class AbstractDestructorQueue {
    public:
        virtual ~AbstractDestructorQueue() = default;
        virtual void executeOnDestructor(const std::function<void()>& func) = 0;
    };

    template <typename Mutex>
    class BaseDestructorQueue : public AbstractDestructorQueue {
        BaseCallbacksQueue<DummyMutex>* destructorCallbackQueue = nullptr;
    public:
        void executeOnDestructor(const std::function<void()>& func) override {
            if (!destructorCallbackQueue) {
                destructorCallbackQueue = new CallbacksQueue();
            }

            destructorCallbackQueue->post(func);
        }

        ~BaseDestructorQueue() override {
            if (destructorCallbackQueue) {
                destructorCallbackQueue->process();
                delete destructorCallbackQueue;
            }
        }
    };

    using DestructorQueue = BaseDestructorQueue<DummyMutex>;
    using SynchronizedDestructorQueue = BaseDestructorQueue<std::mutex>;
}


#endif //TEXTIMAGESGENERATOR_DESTRUCTORQUEUE_H
