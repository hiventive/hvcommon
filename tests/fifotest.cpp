/**
 * @file bitvectortest.cpp
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Feb, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Tests for bitvector.h
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "gtest/gtest.h"
#include "fifo.h"

using namespace ::hv::common;

template<typename T> class FIFOTest: public ::testing::Test {
};

TEST(FIFOTest, generalTest) {

	FIFO<hvuint32_t, 4> myFIFO(0u);

	ASSERT_EQ(myFIFO.size(), std::size_t(0));
	ASSERT_TRUE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());
	myFIFO.insert(1);
	ASSERT_EQ(myFIFO.size(), std::size_t(1));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());
	myFIFO.insert(2);
	ASSERT_EQ(myFIFO.size(), std::size_t(2));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());
	myFIFO.insert(3);
	ASSERT_EQ(myFIFO.size(), std::size_t(3));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());
	myFIFO.insert(4);
	ASSERT_EQ(myFIFO.size(), std::size_t(4));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_TRUE(myFIFO.isFull());

	ASSERT_EQ(myFIFO.pop(), 1u);
	ASSERT_EQ(myFIFO.size(), std::size_t(3));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());

	myFIFO.insert(12);
	ASSERT_EQ(myFIFO.size(), std::size_t(4));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_TRUE(myFIFO.isFull());

	ASSERT_EQ(myFIFO.pop(), 2u);
	ASSERT_EQ(myFIFO.size(), std::size_t(3));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());

	ASSERT_EQ(myFIFO.pop(), 3u);
	ASSERT_EQ(myFIFO.size(), std::size_t(2));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());

	ASSERT_EQ(myFIFO.pop(), 4u);
	ASSERT_EQ(myFIFO.size(), std::size_t(1));
	ASSERT_FALSE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());

	ASSERT_EQ(myFIFO.pop(), 12u);
	ASSERT_EQ(myFIFO.size(), std::size_t(0));
	ASSERT_TRUE(myFIFO.isEmpty());
	ASSERT_FALSE(myFIFO.isFull());

}
