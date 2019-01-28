/**
 * @file hvutilstest.cpp
 * @author Benjamin Barrois benjamin.barrois@hiventive.com>
 * @date Mar, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Tests for hvutils
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "gtest/gtest.h"
#include "hvutils.h"

using namespace ::hv::common;

TEST(hvutilstest,binstr2hextest) {
	std::string str(
			"1000110011010100111000011000101111110111000011001010101100");
	std::string strRet(binStrToHexaStr(str));
	ASSERT_STREQ(strRet.c_str(), std::string("0x23353862FDC32AC").c_str());
}

TEST(hvutilstest, superiorPowerOf2Test) {
	ASSERT_EQ(superiorPowerOf2(1), 1);
	ASSERT_EQ(superiorPowerOf2(2), 2);
	ASSERT_EQ(superiorPowerOf2(3), 4);
	ASSERT_EQ(superiorPowerOf2(4), 4);
	ASSERT_EQ(superiorPowerOf2(5), 8);
	ASSERT_EQ(superiorPowerOf2(6), 8);
	ASSERT_EQ(superiorPowerOf2(7), 8);
	ASSERT_EQ(superiorPowerOf2(8), 8);
	ASSERT_EQ(superiorPowerOf2(9), 16);
	ASSERT_EQ(superiorPowerOf2(15), 16);
	ASSERT_EQ(superiorPowerOf2(16), 16);
	ASSERT_EQ(superiorPowerOf2(17), 32);
}

TEST(hvutilstest, hvRWModePackUnpackTest) {
	::cci::cci_value mRWModeCCI;
	hvrwmode_t mRWMode;

	mRWMode = RW;
	mRWModeCCI.set(mRWMode);
	mRWMode = NA;
	mRWModeCCI.try_get(mRWMode);
	ASSERT_EQ(mRWMode, RW);

	mRWMode = RO;
	mRWModeCCI.set(mRWMode);
	mRWMode = NA;
	mRWModeCCI.try_get(mRWMode);
	ASSERT_EQ(mRWMode, RO);

	mRWMode = WO;
	mRWModeCCI.set(mRWMode);
	mRWMode = NA;
	mRWModeCCI.try_get(mRWMode);
	ASSERT_EQ(mRWMode, WO);

	mRWMode = NA;
	mRWModeCCI.set(mRWMode);
	mRWMode = RW;
	mRWModeCCI.try_get(mRWMode);
	ASSERT_EQ(mRWMode, NA);
}
