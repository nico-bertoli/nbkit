#include "nbkit/log.h"

#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <string>

using namespace nbkit::log;

namespace
{
    struct CoutCapture
    {
        std::ostringstream oss;
        std::streambuf* old_buf;

        CoutCapture()
            : old_buf(std::cout.rdbuf(oss.rdbuf()))
        {}

        ~CoutCapture()
        {
            std::cout.rdbuf(old_buf);
        }

        std::string str() const
        {
            return oss.str();
        }
    };
}

TEST(LogDefaultTest, BasicLevelsPrint)
{
    CoutCapture capture;

    Info("MSG_INFO");
    Verbose("MSG_VERBOSE");
    Sparkle("MSG_SPARKLE");
    Warning("MSG_WARNING");
    Error("MSG_ERROR");

    const std::string out = capture.str();

    EXPECT_NE(out.find("[kDefault] MSG_INFO"), std::string::npos);
    EXPECT_NE(out.find("[kDefault] MSG_VERBOSE"), std::string::npos);
    EXPECT_NE(out.find("[kDefault] MSG_SPARKLE"), std::string::npos);
    EXPECT_NE(out.find("[kDefault] MSG_WARNING"), std::string::npos);
    EXPECT_NE(out.find("[kDefault] MSG_ERROR"), std::string::npos);
}

TEST(LogDefaultTest, RuntimeLoggingPrints)
{
    CoutCapture capture;

    InfoRuntime(Channel::kDefault, "MSG_INFO_RT");

    const std::string out = capture.str();
    EXPECT_NE(out.find("[kDefault] MSG_INFO_RT"), std::string::npos);
}

TEST(LogDefaultTest, AssertWarningAndErrorOnlyFireOnFailure)
{
    CoutCapture capture;

    AssertWarning<Channel::kDefault>([](){ return false; }, "ASSERT_WARN");
    AssertWarning<Channel::kDefault>([](){ return true; }, "ASSERT_WARN_SHOULDNT_PRINT");
    AssertError<Channel::kDefault>([](){ return false; }, "ASSERT_ERR");
    AssertError<Channel::kDefault>([](){ return true; }, "ASSERT_ERR_SHOULDNT_PRINT");

    const std::string out = capture.str();

    EXPECT_NE(out.find("[kDefault] ASSERT_WARN"), std::string::npos);
    EXPECT_NE(out.find("[kDefault] ASSERT_ERR"), std::string::npos);
    EXPECT_EQ(out.find("ASSERT_WARN_SHOULDNT_PRINT"), std::string::npos);
    EXPECT_EQ(out.find("ASSERT_ERR_SHOULDNT_PRINT"), std::string::npos);
}

TEST(LogDefaultTest, ColorMarkersAndDefaultChannelEnabled)
{
    CoutCapture capture;

    Info("MSG_INFO");

    const std::string out = capture.str();
    EXPECT_NE(out.find(detail::kColorInfo), std::string::npos);
    EXPECT_NE(out.find(detail::kColorReset), std::string::npos);
    EXPECT_TRUE(IsChannelEnabled(Channel::kDefault));
}
