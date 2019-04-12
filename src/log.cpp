/**
 * @file log.cpp
 * @author Guillaume Delbergue <guillaume.delbergue@hiventive.com>
 * @date Feb, 2019
 * @copyright Copyright (C) 2019, Hiventive.
 *
 * @brief Log implementation
 */

#include <iostream>
#include "log.h"

#if !defined(_WIN32)
// Private console logger with color
static auto _hvLogger = spdlog::stdout_color_mt("global");
static auto _hvLoggerLevelInitialized = false;
/* #elif !(defined(_MSC_VER) && _MSC_VER < 1900)
// Private color console is bugged with some consoles on Windows
auto _hvLogger = spdlog::stdout_logger_mt("console"); */
#endif

namespace hv {
namespace common {

#if !defined(_WIN32) // FIXME: should be !(defined(_MSC_VER) && _MSC_VER < 1900), but there is a conflict with operator | and SPDLog with VS2015/2017
std::shared_ptr<spdlog::logger> _getMainLogger() {
	if(!_hvLoggerLevelInitialized) {
		_hvLogger->set_level(spdlog::level::warn);
		_hvLoggerLevelInitialized = true;
	}
	return _hvLogger;
}
#endif

#if !defined(_WIN32)
void setLogLevel(enum log::LogLevel logLevel) {
	_hvLoggerLevelInitialized = true;
	switch(logLevel) {
		case log::trace:
			hv::common::_getMainLogger()->set_level(spdlog::level::trace);
			break;
		case log::debug:
			hv::common::_getMainLogger()->set_level(spdlog::level::debug);
			break;
		case log::info:
			hv::common::_getMainLogger()->set_level(spdlog::level::info);
			break;
		case log::warning:
			hv::common::_getMainLogger()->set_level(spdlog::level::warn);
			break;
		case log::error:
			hv::common::_getMainLogger()->set_level(spdlog::level::err);
			break;
		case log::critical:
			hv::common::_getMainLogger()->set_level(spdlog::level::critical);
			break;
		case log::off:
			hv::common::_getMainLogger()->set_level(spdlog::level::off);
			break;
	}
}
#else
void setLogLevel(enum log::LogLevel logLevel) {};
#endif

}
}
