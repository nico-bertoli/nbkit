#pragma once
#include <cstdlib>

namespace nbkit
{
    template <typename T>
    class Singleton
    {
    //---------------------------------------------------------- fields
    private:
        static inline T* instance_ = nullptr;

    public:
        static T& Instance()
        {
            if (!instance_)
            {
                instance_ = new T();

                // callback to destroy singleton when program exits normally
                static bool atexit_registered_ = false;
                if (!atexit_registered_)
                {
                    std::atexit([](){ DeleteInstance(instance_); instance_ = nullptr; });
                    atexit_registered_ = true;
                }
            }

            return *instance_;
        }

    //---------------------------------------------------------- methods
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator = (const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator = (const Singleton&&) = delete;

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    private:
        static void DeleteInstance(T* ptr) { delete ptr; }
    };
}