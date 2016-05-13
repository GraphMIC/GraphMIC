#pragma once

#include "gmCoreExport.hpp"

#include <mutex>
#include <string>
#include <sstream>

namespace gm
{
    class GM_CORE_EXPORT Log
    {
    private:
        static std::mutex m_mutex;
        static Log* instance;
        Log() = delete;
    public:
        enum Type
        {
            New,
            Get,
            Set,
            Func,
            Del,
            Default
        };
    public:
        static auto format(std::string, va_list) -> std::string;
        static auto logInfo_f(std::string, ...) -> void;
        static auto logInfo(std::stringstream) -> void;
        static auto logTrace(Type, std::stringstream) -> void;
        static auto logTrace(Type) -> void;
    };
}

#   if defined _MSC_VER
#       define GM_FUNCTION_STRING __FUNCTION__
#   endif
#   if defined __GNUC__
#       define GM_FUNCTION_STRING __PRETTY_FUNCTION__
#   endif

#define log_trace_arg_0()           gm::Log::logTrace(gm::Log::Default, std::stringstream() << GM_FUNCTION_STRING)
#define log_trace_arg_1(type)       gm::Log::logTrace(type, std::stringstream() << GM_FUNCTION_STRING)
#define log_trace_arg_2(type, args) gm::Log::logTrace(type, std::stringstream() << GM_FUNCTION_STRING << " => " << args)

#define log_trace_arg_func(x, arg0, org1, func, ...) func

#define log_trace(...)      log_trace_arg_func(,##__VA_ARGS__, log_trace_arg_2(__VA_ARGS__), log_trace_arg_1(__VA_ARGS__), log_trace_arg_0(__VA_ARGS__))
#define log_exception(x)    gm::Log::logInfo(std::stringstream() << "   ..exception: " << x)
#define log_warning(x)      gm::Log::logInfo(std::stringstream() << "   ..warning: " << x)
#define log_error(x)        gm::Log::logInfo(std::stringstream() << "   ..error: " << x)
#define log_info(x)         gm::Log::logInfo(std::stringstream() << "   ..info: " << x)