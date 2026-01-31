#include <gtest/gtest.h>
#include <nbkit/event.h>
#include <iostream>
#include <string.h>

template<typename... Args>
using Event = nbkit::Event<Args...>;

class EventTest : public ::testing::Test
{
};

TEST_F(EventTest, VoidEvent)
{
    Event<> event;
    size_t calls_counter = 0;

    event.Subscribe([&calls_counter](){++calls_counter;});

    event.Notify();
    EXPECT_EQ(calls_counter,1);

    event.Notify();
    EXPECT_EQ(calls_counter,2);
}

TEST_F(EventTest, IntEvent)
{
    Event<int> event;
    int sum = 0;

    event.Subscribe([&sum](int to_add){sum += to_add;});
    
    event.Notify(10);
    EXPECT_EQ(sum,10);

    event.Notify(100);
    EXPECT_EQ(sum,110);
}

TEST_F(EventTest, StringEvent)
{
    Event<std::string> event;
    std::string sum = "";

    event.Subscribe([&sum](std::string to_add){sum += to_add;});

    event.Notify("substr1");
    event.Notify(" ");
    event.Notify("substr2");
    EXPECT_EQ(sum, "substr1 substr2");
}

TEST_F(EventTest, MultipleSubscriptionsVoidEvent)
{
    Event<> event;
    size_t calls_counter = 0;

    event.Subscribe([&calls_counter](){++calls_counter;});
    event.Subscribe([&calls_counter](){++calls_counter;});
    
    event.Notify();
    EXPECT_EQ(calls_counter,2);

    event.Notify();
    EXPECT_EQ(calls_counter,4);
}


TEST_F(EventTest, MultipleSubscriptionsIntEvent)
{
    Event<int> event;
    size_t calls_counter = 0;

    event.Subscribe([&calls_counter](int to_add){calls_counter += to_add;});
    event.Subscribe([&calls_counter](int to_add){calls_counter += to_add;});
    
    event.Notify(5);
    EXPECT_EQ(calls_counter,10);

    event.Notify(5);
    EXPECT_EQ(calls_counter,20);
}

TEST_F(EventTest, ClearWorks)
{
    Event<> event;

    bool any_callback_called = false;

    event.Subscribe([&any_callback_called](){any_callback_called = true;});
    event.Subscribe([&any_callback_called](){any_callback_called = true;});

    event.Clear();
    event.Notify();

    EXPECT_FALSE(any_callback_called);
}

TEST_F(EventTest, NotifyWithZeroSubscribers)
{
    Event<> event_void;
    Event<int> event_int;
    Event<std::string> event_string;
    
    EXPECT_NO_THROW(event_void.Notify());
    EXPECT_NO_THROW(event_int.Notify(42));
    EXPECT_NO_THROW(event_string.Notify("Test"));
}