/**
 * @file log-test.cpp
 * @author Guillaume Delbergue <guillaume.delbergue@hiventive.com>
 * @date Feb, 2019
 * @copyright Copyright (C) 2019, Hiventive.
 *
 * @brief Tests for log.h
 */

#include <iostream>
#include "gtest/gtest.h"
#include "log.h"

template<typename T> class HVLogTest: public ::testing::Test {
};

TEST(HVLogText, generalTest) {
	HV_LOG_CRITICAL("This is a critical error log");
	HV_LOG_ERROR("This is an error log");
	HV_LOG_WARNING("This is a warning log");
	HV_LOG_INFO("This is an info log");
	HV_LOG_DEBUG("This is a debug log");
	HV_LOG_TRACE("This is a trace log");

	// FIXME
	// hv::common::setLogLevel(hv::common::log::trace);
	// hv::common::setLogFile("output.log");
}
