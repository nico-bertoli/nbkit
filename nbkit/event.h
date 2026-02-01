#pragma once

#include <vector>
#include <functional>

namespace nbkit
{
    template <typename... Args>
    class Event
    {
    //---------------------------------------------------------- fields
    private:
        std::vector< std::function<void(Args...)>> callbacks_;

    //---------------------------------------------------------- methods
    public:
        void Subscribe(std::function<void(Args...)> callback) { callbacks_.push_back(callback); }
        void Clear() { callbacks_.clear(); }

        void Notify(Args... args)
        {
            for (auto& callback : callbacks_)
                callback(args...);
        }
    };
}