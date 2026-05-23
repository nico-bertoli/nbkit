#define NBKIT_LOG_CONFIG_HEADER_PATH "tests/log_config_test.h"
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

TEST(LogOverrideTest, ChannelOverrideSanity)
{
    EXPECT_FALSE(IsChannelEnabled(Channel::kDefault));
    EXPECT_TRUE(IsChannelEnabled(Channel::kCustomChannel));
}

TEST(LogOverrideTest, DisabledChannelDoesNotPrint)
{
    CoutCapture capture;

    Info<Channel::kDefault>("NO_PRINT");

    const std::string out = capture.str();
    EXPECT_EQ(out.find("NO_PRINT"), std::string::npos);
}

TEST(LogOverrideTest, EnabledChannelPrintsWithChannelName)
{
    CoutCapture capture;

    Info<Channel::kCustomChannel>("YES_PRINT");
    InfoRuntime(Channel::kCustomChannel, "YES_RT");

    const std::string out = capture.str();
    EXPECT_NE(out.find("[kCustomChannel] YES_PRINT"), std::string::npos);
    EXPECT_NE(out.find("[kCustomChannel] YES_RT"), std::string::npos);
}

TEST(LogOverrideTest, ColorMarkerOverridesApply)
{
    CoutCapture capture;

    Info<Channel::kCustomChannel>("COLOR_TEST");

    const std::string out = capture.str();
    EXPECT_NE(out.find("[I]"), std::string::npos);
    EXPECT_NE(out.find("[RST]"), std::string::npos);
}
