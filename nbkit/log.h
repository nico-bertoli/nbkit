#pragma once

#include <iostream>
#include <string_view>
#include <array>
#include <algorithm>
#include <functional>
#include <magic_enum.hpp>

// try to include log config (allows user to override colors and channels)
#ifdef NBKIT_LOG_CONFIG_HEADER_PATH
    #include NBKIT_LOG_CONFIG_HEADER_PATH
#endif

namespace nbkit::log
{

//================================== optional user overrides

#ifndef NBKIT_LOG_CHANNELS_OVERRIDE
    enum class Channel { kDefault };
    inline constexpr std::array<Channel, 1> kEnabledChannels = { Channel::kDefault };
#endif

#ifndef NBKIT_COLOR_OVERRIDE
namespace detail
{
    inline constexpr const char* kColorReset   = "\033[0m";
    inline constexpr const char* kColorVerbose = "\033[90m";
    inline constexpr const char* kColorInfo    = "\033[32m";
    inline constexpr const char* kColorSparkle = "\033[36m";
    inline constexpr const char* kColorWarning = "\033[33m";
    inline constexpr const char* kColorError   = "\033[31m";
}
#endif

//================================== forward decl

constexpr bool IsChannelEnabled(Channel channel);

//================================== private namespace
namespace
{
    template <Channel Ch, typename... Args>
    void BaseLog(std::string_view color, Args... args)
    {
        if constexpr (IsChannelEnabled(Ch) == false)
            return;

        std::cout << color << "[" << magic_enum::enum_name(Ch) << "] ";
        (std::cout << ... << args);
        std::cout << detail::kColorReset << "\n";
    }

    template <typename... Args>
    void BaseLogRuntime(Channel ch, std::string_view color, Args... args)
    {
        if (!IsChannelEnabled(ch))
            return;

        std::cout << color << "[" << magic_enum::enum_name(ch) << "] ";
        (std::cout << ... << args);
        std::cout << detail::kColorReset << "\n";
    }
}

//================================== public methods

//------ is channel enabled
constexpr bool IsChannelEnabled(Channel channel)
{
    for (const auto& enabled : kEnabledChannels)
        if (enabled == channel)
            return true;
    return false;
}

//------ base logging
template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void Verbose(Args... args) { BaseLog<Ch>(detail::kColorVerbose, args...); }

template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void Info(Args... args) { BaseLog<Ch>(detail::kColorInfo, args...); }

template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void Sparkle(Args... args) { BaseLog<Ch>(detail::kColorSparkle, args...); }

template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void Warning(Args... args) { BaseLog<Ch>(detail::kColorWarning, args...); }

template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void Error(Args... args) { BaseLog<Ch>(detail::kColorError, args...); }

//------ runtime logging (in some cases you dont know the channel at compiletime)
template <typename... Args>
void VerboseRuntime(Channel ch, Args... args) { BaseLogRuntime(ch, detail::kColorVerbose, args...); }

template <typename... Args>
void InfoRuntime(Channel ch, Args... args) { BaseLogRuntime(ch, detail::kColorInfo, args...); }

template <typename... Args>
void SparkleRuntime(Channel ch, Args... args) { BaseLogRuntime(ch, detail::kColorSparkle, args...); }

template <typename... Args>
void WarningRuntime(Channel ch, Args... args) { BaseLogRuntime(ch, detail::kColorWarning, args...); }

template <typename... Args>
void ErrorRuntime(Channel ch, Args... args) { BaseLogRuntime(ch, detail::kColorError, args...); }

//------ asserts
template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void AssertWarning(std::function<bool()> condition, Args... args)
{
    if (!condition())
        BaseLog<Ch>(detail::kColorWarning, args...);
}

template <Channel Ch = Channel::kDefault, typename... Args>
constexpr void AssertError(std::function<bool()> condition, Args... args)
{
    if (!condition())
        BaseLog<Ch>(detail::kColorError, args...);
}

}