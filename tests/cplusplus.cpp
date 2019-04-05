/**
 * @file cplusplus.cpp
 * @author Guillaume Delbergue <guillaume.delbergue@hiventive.com>
 * @date March, 2019
 * @copyright Copyright (C) 2019, Hiventive.
 *
 * @brief Tests for cplusplus.h
 */

#include <iostream>
#include "gtest/gtest.h"
#include "cplusplus.h"

template<typename T> class HVCPlusPlusTest: public ::testing::Test {
};

TEST(HVCPlusPlusTest, deleteTest) {
	class A {
	public:
		A() {};
		// Delete
		A(const ::std::string a) HV_CPLUSPLUS_MEMBER_FUNCTION_DELETE;
		A(const int b) HV_CPLUSPLUS_MEMBER_FUNCTION_DELETE;
		void test() {std::cout << "ok" << std::endl;}
	};

	A a;
	a.test();
}

TEST(HVCPlusPlusTest, defaultTest) {
	class A {
	public:
		A() {};
		virtual ~A() {};
	};

	class B : public A {
	public:
		B():A() {};
		// Default
		~B() override HV_CPLUSPLUS_MEMBER_FUNCTION_DEFAULT;
		void test() {std::cout << "ok" << std::endl;}
	};

	B b;
	b.test();
}
