#pragma once

namespace nbkit
{
    template <typename T>
    class Singleton
    {
    //---------------------------------------------------------- fields
    public:
        static T& Instance()
        {
            static T instance;
            return instance;
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
    };
}