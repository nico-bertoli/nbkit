#pragma once

#include <array>

#define NBKIT_LOG_CHANNELS_OVERRIDE
#define NBKIT_COLOR_OVERRIDE

namespace nbkit::log
{
    enum class Channel { kDefault, kCustomChannel };

    inline constexpr std::array<Channel, 1> kEnabledChannels = { Channel::kCustomChannel };

    namespace detail
    {
        inline constexpr const char* kColorReset   = "[RST]";
        inline constexpr const char* kColorVerbose = "[V]";
        inline constexpr const char* kColorInfo    = "[I]";
        inline constexpr const char* kColorSparkle = "[S]";
        inline constexpr const char* kColorWarning = "[W]";
        inline constexpr const char* kColorError   = "[E]";
    }
}
