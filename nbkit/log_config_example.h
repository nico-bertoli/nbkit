 // Using a file like this, you can override log channels and colors.
 // If you do, it's imporant that you include this config file first, then log.h wherever you use it

#if false

#pragma once
#include <array>

namespace nbkit::log
{

#define NBKIT_LOG_CONFIG_HEADER_PATH "path/to/this_file.h"

//------ override defined channel (uncomment block to override)

#define NBKIT_LOG_CHANNELS_OVERRIDE
enum class Channel
{
    kDefault,
    kCustomChannel,
};

inline constexpr std::array<Channel, 2> kEnabledChannels =
{
    Channel::kDefault,
    Channel::kCustomChannel
};

//------ ovverride colors (uncomment block to override)

#define NBKIT_COLOR_OVERRIDE
namespace detail
{
    inline constexpr const char* kColorVerbose = "\x1b[0;38;2;148;148;148m";
    inline constexpr const char* kColorInfo    = "\x1b[0;38;2;0;255;64m";
    inline constexpr const char* kColorSparkle = "\x1b[0;38;2;0;179;255m";
    inline constexpr const char* kColorWarning = "\x1b[0;38;2;255;247;0m";
    inline constexpr const char* kColorError   = "\x1b[0;38;2;255;0;0m";
}

}

#endif