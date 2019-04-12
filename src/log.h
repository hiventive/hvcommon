/**
 * @file log.h
 * @author Guillaume Delbergue <guillaume.delbergue@hiventive.com>
 * @date May, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Logger
 */

#ifndef HV_LOG_H
#define HV_LOG_H

#include "log-level.h"

#define HV_LOG_STR(x) #x
#define HV_LOG_XSTR(x) HV_LOG_STR(x)
#define HV_LOG_DEFER(M,...) M(__VA_ARGS__)
#define HV_LOG_CONCATENATE(x, y) x ## y

// Disable logger time
#ifdef HV_LOG_DISABLE_CLOCK
#define SPDLOG_NO_DATETIME
#endif

// Disable logger name
#if defined(HV_LOG_DISABLE_NAME)
#define SPDLOG_NO_NAME
#endif

// Log levels
#if !defined(HV_LOG_ACTIVE_LEVEL)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_WARN // Default log level: warning
#else
#if HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_TRACE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#elif HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#elif HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_INFO
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#elif HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_WARNING
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_WARN
#elif HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_ERROR
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_ERROR
#elif HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_CRITICAL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_CRITICAL
#elif HV_LOG_ACTIVE_LEVEL == HV_LOG_LEVEL_OFF
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_WARN
#endif
#endif

#if !defined(_WIN32) // FIXME: should be !(defined(_MSC_VER) && _MSC_VER < 1900), but there is a conflict with operator | and SPDLog with VS2015/2017
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <fmt/format.h>
#endif

namespace hv {
namespace common {

/**
 * Private method to get the main logger
 *
 * @return Main logger
 */
#if !defined(_WIN32) // FIXME: should be !(defined(_MSC_VER) && _MSC_VER < 1900), but there is a conflict with operator | and SPDLog with VS2015/2017
std::shared_ptr<spdlog::logger> _getMainLogger();
#endif

/**
 * HV Logger
 *
 * Example usage:
 * 		HV_LOG_CRITICAL("A critical error")
 */

#if !defined(_WIN32) // FIXME: should be !(defined(_MSC_VER) && _MSC_VER < 1900), but there is a conflict with operator | and SPDLog with VS2015/2017
	#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
		#define HV_LOG_TRACE(...) 			SPDLOG_LOGGER_CALL(hv::common::_getMainLogger(), spdlog::level::trace, __VA_ARGS__)
	#else
		#define HV_LOG_TRACE(...) 			(void)0
	#endif
	#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
		#define HV_LOG_DEBUG(...) 			SPDLOG_LOGGER_CALL(hv::common::_getMainLogger(), spdlog::level::debug, __VA_ARGS__)
	#else
		#define HV_LOG_DEBUG(...) 			(void)0
	#endif
	#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
		#define HV_LOG_INFO(...) 			SPDLOG_LOGGER_CALL(hv::common::_getMainLogger(), spdlog::level::info, __VA_ARGS__)
	#else
		#define HV_LOG_INFO(...) 			(void)0
	#endif
	#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
		#define HV_LOG_WARNING(...) 		SPDLOG_LOGGER_CALL(hv::common::_getMainLogger(), spdlog::level::warn, __VA_ARGS__)
	#else
		#define HV_LOG_WARNING(...) 		(void)0
	#endif
	#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
		#define HV_LOG_ERROR(...) 			SPDLOG_LOGGER_CALL(hv::common::_getMainLogger(), spdlog::level::err, __VA_ARGS__)
	#else
		#define HV_LOG_ERROR(...) 			(void)0
	#endif
	#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
		#define HV_LOG_CRITICAL(...) 		SPDLOG_LOGGER_CALL(hv::common::_getMainLogger(), spdlog::level::critical, __VA_ARGS__)
	#else
		#define HV_LOG_CRITICAL(...) 		(void)0
	#endif
#else
	#if HV_LOG_ACTIVE_LEVEL <= HV_LOG_LEVEL_TRACE
		#define HV_LOG_TRACE(...) 			std::cout << fmt::format(__VA_ARGS__) << std::endl
	#else
		#define HV_LOG_TRACE(...) 			(void)0
    #endif
	#if HV_LOG_ACTIVE_LEVEL <= HV_LOG_LEVEL_DEBUG
		#define HV_LOG_DEBUG(...) 			std::cout << fmt::format(__VA_ARGS__) << std::endl
	#else
		#define HV_LOG_DEBUG(...) 			(void)0
    #endif
	#if HV_LOG_ACTIVE_LEVEL <= HV_LOG_LEVEL_INFO
		#define HV_LOG_INFO(...) 			std::cout << fmt::format(__VA_ARGS__) << std::endl
	#else
		#define HV_LOG_INFO(...) 			(void)0
    #endif
	#if HV_LOG_ACTIVE_LEVEL <= HV_LOG_LEVEL_WARNING
		#define HV_LOG_WARNING(...) 		std::cout << fmt::format(__VA_ARGS__) << std::endl
	#else
		#define HV_LOG_WARNING(...) 		(void)0
    #endif
	#if HV_LOG_ACTIVE_LEVEL <= HV_LOG_LEVEL_ERROR
		#define HV_LOG_ERROR(...) 			std::cout << fmt::format(__VA_ARGS__) << std::endl
	#else
		#define HV_LOG_ERROR(...) 			(void)0
    #endif
	#if HV_LOG_ACTIVE_LEVEL <= HV_LOG_LEVEL_CRITICAL
		#define HV_LOG_CRITICAL(...) 		std::cout << fmt::format(__VA_ARGS__) << std::endl
	#else
		#define HV_LOG_CRITICAL(...) 		(void)0
	#endif
#endif

namespace log {
	enum LogLevel
	{
		trace 		= HV_LOG_LEVEL_TRACE,
		debug 		= HV_LOG_LEVEL_DEBUG,
		info 		= HV_LOG_LEVEL_INFO,
		warning 	= HV_LOG_LEVEL_WARNING,
		error 		= HV_LOG_LEVEL_ERROR,
		critical 	= HV_LOG_LEVEL_CRITICAL,
		off 		= HV_LOG_LEVEL_OFF,
	};
}

void setLogLevel(enum log::LogLevel logLevel);

} // namespace common
} // namespace hv

#endif
