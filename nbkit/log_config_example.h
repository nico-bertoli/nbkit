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
    inline constexpr const char* kColorReset   = "\033[0m";
    inline constexpr const char* kColorVerbose = "\033[90m";
    inline constexpr const char* kColorInfo    = "\033[32m";
    inline constexpr const char* kColorSparkle = "\033[36m";
    inline constexpr const char* kColorWarning = "\033[33m";
    inline constexpr const char* kColorError   = "\033[31m";
}

}

#endif