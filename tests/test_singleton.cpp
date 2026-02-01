#include <gtest/gtest.h>
#include <nbkit/singleton.h>
#include <vector>
#include <string>
#include <type_traits>

template<typename T>
using Singleton = nbkit::Singleton<T>;

//-------------------------------------------------------- classes

class SingletonInt : public Singleton<SingletonInt>
{
    friend class Singleton<SingletonInt>;

private:
    SingletonInt() = default;
    ~SingletonInt() = default;

public:
    int value_ = 0;
    void SetValue(int v) { value_ = v; }
    int GetValue() const { return value_; }
};

class SingletonString : public Singleton<SingletonString>
{
    friend class Singleton<SingletonString>;

private:
    SingletonString() = default;
    ~SingletonString() = default;

public:
    std::string name_;
    void SetName(const std::string& n) { name_ = n; }
    const std::string& GetName() const { return name_; }
};

//-------------------------------------------------------- test class

class SingletonTest : public ::testing::Test
{
protected:
    //automatically called before each test case
    void SetUp() override
    {
        // Reset the state
        SingletonInt::Instance().SetValue(0);
        SingletonString::Instance().SetName("");
    }
};

//-------------------------------------------------------- tests

TEST_F(SingletonTest, CopyPrevented)
{
    static_assert(!std::is_copy_constructible_v<SingletonInt>, 
                  "SingletonInt should not be copy constructible");
    
    static_assert(!std::is_copy_assignable_v<SingletonInt>, 
                  "SingletonInt should not be copy assignable");
    
    static_assert(!std::is_move_constructible_v<SingletonInt>, 
                  "SingletonInt should not be move constructible");
    
    static_assert(!std::is_move_assignable_v<SingletonInt>, 
                  "SingletonInt should not be move assignable");
}

TEST_F(SingletonTest, InstantiationPrevented)
{
    static_assert(!std::is_default_constructible_v<SingletonInt>, 
                  "SingletonInt should not be directly constructible");
    
    static_assert(!std::is_default_constructible_v<SingletonString>, 
                  "SingletonString should not be directly constructible");
}

TEST_F(SingletonTest, SameInstanceReturned)
{
    SingletonInt& instance1 = SingletonInt::Instance();
    SingletonInt& instance2 = SingletonInt::Instance();
    SingletonInt& instance3 = SingletonInt::Instance();

    EXPECT_EQ(&instance1, &instance2);
    EXPECT_EQ(&instance2, &instance3);
    EXPECT_EQ(&instance1, &instance3);
}

TEST_F(SingletonTest, InstancePersistsState)
{
    SingletonInt& instance1 = SingletonInt::Instance();
    instance1.SetValue(42);

    SingletonInt& instance2 = SingletonInt::Instance();
    EXPECT_EQ(instance2.GetValue(), 42);
    EXPECT_EQ(instance1.GetValue(), 42);

    instance2.SetValue(100);
    SingletonInt& instance3 = SingletonInt::Instance();
    EXPECT_EQ(instance3.GetValue(), 100);
    EXPECT_EQ(instance1.GetValue(), 100);
    EXPECT_EQ(instance2.GetValue(), 100);
}

TEST_F(SingletonTest, WorksAcrossScopes)
{
    constexpr int kValueSet = 99;
    SingletonInt* instance1_ptr = nullptr;
    {
        SingletonInt& instance1 = SingletonInt::Instance();
        instance1_ptr = &instance1;
        instance1.SetValue(kValueSet);
    }

    {
        SingletonInt& instance2 = SingletonInt::Instance();
        EXPECT_EQ(instance2.GetValue(), kValueSet);
        EXPECT_EQ(instance1_ptr, &instance2);
    }
}