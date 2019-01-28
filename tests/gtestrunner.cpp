/**
 * @file gtest_runner.cpp
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Feb, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Test runner for Register project
 */
#include "gtest/gtest.h"
#include <ctime>
#include <systemc>

int sc_main(int argc, char* argv[]) {
	::std::srand(std::time(NULL));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
