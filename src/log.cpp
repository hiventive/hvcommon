/**
 * @file log.cpp
 * @author Guillaume Delbergue <guillaume.delbergue@hiventive.com>
 * @date Feb, 2019
 * @copyright Copyright (C) 2019, Hiventive.
 *
 * @brief Log implementation
 */

#include "log.h"

#if !defined(_WIN32)
// Private console logger with color
static auto _hvLogger = spdlog::stdout_color_mt("console");
/* #elif !(defined(_MSC_VER) && _MSC_VER < 1900)
// Private color console is bugged with some consoles on Windows
auto _hvLogger = spdlog::stdout_logger_mt("console"); */
#endif

namespace hv {
namespace common {

#if !defined(_WIN32) // FIXME: should be !(defined(_MSC_VER) && _MSC_VER < 1900), but there is a conflict with operator | and SPDLog with VS2015/2017
std::shared_ptr<spdlog::logger> _getMainLogger() {
	return _hvLogger;
}
#endif

}
}
