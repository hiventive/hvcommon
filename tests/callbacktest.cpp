/**
 * @file callbacktest.cpp
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Feb, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Tests for callback.h
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cci_core/cci_callback.h>
#include "gtest/gtest.h"
#include "callback.h"

using namespace ::hv::common;

class CallbackTest: public ::testing::Test {
};

class Foo {
protected:

	long val;

public:
	Foo() :
			val(0) {
	}

	long getVal() {
		return val;
	}

	long Add(const int &wIn, const long &xIn, const unsigned int &yIn,
			const unsigned long &zIn) {
		val = static_cast<long>(static_cast<long>(wIn) + xIn
				+ static_cast<long>(yIn) + static_cast<long>(zIn));
		return val;
	}

};

long mul(const int &wIn, const long &xIn, const unsigned int &yIn,
		const unsigned long &zIn) {
	return static_cast<long>(static_cast<long>(wIn) * xIn
			* static_cast<long>(yIn) * static_cast<long>(zIn));
}

long addMul(const int &wIn, const long &xIn, const unsigned int &yIn,
		const unsigned long &zIn) {
	return static_cast<long>(static_cast<long>(wIn)
			+ xIn * static_cast<long>(yIn) + static_cast<long>(zIn));
}

TEST_F(CallbackTest, CallbackCreationTest) {
	// Function types declarations (std::function and classical function)
	typedef std::function<
			long(const int&, const long&, const unsigned int&,
					const unsigned long&)> stdfunc_t;
	typedef CallbackImpl<
			long(const int&, const long&, const unsigned int&,
					const unsigned long&)> cb_t;

	Foo fooVal;

	cb_t addCb(&Foo::Add, &fooVal);
	cb_t mulCb(mul);

	stdfunc_t addMulStdFunc(addMul);
	cb_t addMulCb(addMulStdFunc);

	int w = 1;
	unsigned int x = 2;
	long y = 3;
	unsigned long z = 4;
	long tmp = addCb(w, x, y, z);

	ASSERT_EQ(tmp,1 + 2 + 3 + 4)<< "Error applying addCb";
	ASSERT_EQ(fooVal.getVal(), 1 + 2 + 3 + 4)<< "Error in modification of val member of Foo";

	ASSERT_EQ(mulCb(w, x, y, z), 1*2*3*4)<< "Error applying mulCb";
	ASSERT_EQ(addMulCb(w, x, y, z), 1+2*3+4)<< "Error applying addMulCB";

}

TEST_F(CallbackTest, CallbackVectorTest) {
	// Function types declarations (std::function and classical function)
	typedef std::function<
			long(const int&, const long&, const unsigned int&,
					const unsigned long&)> stdfunc_t;
	typedef CallbackImpl<
			long(const int&, const long&, const unsigned int&,
					const unsigned long&)> cb_t;
	typedef std::vector<
			CallbackImpl<
					long(const int&, const long&, const unsigned int&,
							const unsigned long&)>> cbv_t;

	Foo fooVal;

	cb_t addCb(&Foo::Add, &fooVal);
	cb_t mulCb(mul);

	stdfunc_t addMulStdFunc(addMul);
	cb_t addMulCb(addMulStdFunc);

	int w = 1;
	unsigned int x = 2;
	long y = 3;
	unsigned long z = 4;

	cbv_t myCbv;

	ASSERT_TRUE(myCbv.empty())<< "Callback vector should be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(0))<< "Callback vector should be of size 0";
	myCbv.push_back(mulCb);
	ASSERT_FALSE(myCbv.empty())<< "Callback vector should not be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(1))<< "Callback vector should be of size 1";

	auto itTmp = myCbv.begin();
	myCbv.insert(itTmp, addCb);

	ASSERT_FALSE(myCbv.empty())<< "Callback vector should not be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(2))<< "Callback vector should be of size 2";

	myCbv.push_back(addMulCb);

	ASSERT_FALSE(myCbv.empty())<< "Callback vector should not be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(3))<< "Callback vector should be of size 3";

	// Calling functions by iterator
	long res[3];
	int ind = 0;
	for (auto it = myCbv.cbegin(); it != myCbv.cend(); ++it) {
		res[ind] = (*it)(w, x, y, z);
		ind++;
	}

	ASSERT_EQ(res[0], 1+2+3+4)<< "Error in addition function";
	ASSERT_EQ(res[1], 1*2*3*4)<< "Error in multiplication function";
	ASSERT_EQ(res[2], 1+2*3+4)<< "Error in addition/multiplication function";

	// Calling functions by 'at' method
	ASSERT_EQ(myCbv.at(0)(w, x, y, z), 1+2+3+4)<< "Error in addition function";
	ASSERT_EQ(myCbv.at(1)(w, x, y, z), 1*2*3*4)<< "Error in multiplication function";
	ASSERT_EQ(myCbv.at(2)(w, x, y, z), 1+2*3+4)<< "Error in addition/multiplication function";

	// Calling functions by [] operator
	ASSERT_EQ(myCbv[0](w, x, y, z), 1+2+3+4)<< "Error in addition function";
	ASSERT_EQ(myCbv[1](w, x, y, z), 1*2*3*4)<< "Error in multiplication function";
	ASSERT_EQ(myCbv[2](w, x, y, z), 1+2*3+4)<< "Error in addition/multiplication function";

	//Erasing first element
	itTmp = myCbv.begin();
	myCbv.erase(itTmp);
	ASSERT_FALSE(myCbv.empty())<< "Callback vector should not be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(2))<< "Callback vector should be of size 2";

	// Erasing second element
	itTmp = myCbv.begin();
	myCbv.erase(itTmp);
	ASSERT_FALSE(myCbv.empty())<< "Callback vector should not be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(1))<< "Callback vector should be of size 1";

	// Erasing last element
	itTmp = myCbv.begin();
	myCbv.erase(itTmp);
	ASSERT_TRUE(myCbv.empty())<< "Callback vector should be empty";
	ASSERT_EQ(myCbv.size(),std::size_t(0))<< "Callback vector should be of size 0";

}

class MasterClass {
protected:
	// Type definitions for callbacks
	typedef CallbackImpl<int(const int&, std::string&)> cb_t;
	typedef std::vector<cb_t> cbv_t;

	// Main data member
	int value;

	// Monitoring helpers
	unsigned int cpt;
	std::string str;

	// Callback vector
	cbv_t myCallbackVector;

public:
	// Constructor
	MasterClass(const int &valueIn) :
			value(valueIn), cpt(1), str(
					"0 - Initialization - value = " + std::to_string(valueIn)
							+ "\n") {
	}

	// Destructor
	virtual ~MasterClass() {
	}

	// Accessor to value
	int getValue() {
		return value;
	}

	// Method to register callback to myCallbackVector
	void registerCallback(const cb_t &callback) {
		this->myCallbackVector.push_back(callback);
	}

	// Accessor to myCallbackVector's size
	std::size_t howManyCallbacks() const {
		return this->myCallbackVector.size();
	}

	// Method using callbacks
	std::string superMethod() {
		this->str += std::to_string(cpt++) + " - Entering superMethod()\n"; // Tracking

		// Checking if there are registered callbacks
		if (!myCallbackVector.empty()) {
			// Iterating on callbacks
			for (auto it = myCallbackVector.cbegin();
					it != myCallbackVector.cend(); ++it) {

				std::string strTmp(std::to_string(cpt++) + " - "); // Tracking

				// Invoking callback
				this->value = (*it)(this->value, strTmp);

				this->str += strTmp + " - value = "
						+ std::to_string(this->value) + "\n"; // Tracking
			}
		}
		this->str += std::to_string(cpt++) + " - Leaving superMethod()\n"; // Tracking
		return this->str;
	}
};

int addFive(const int &intIn, std::string &strIn) {
	strIn += "Adding 5"; // Tracking
	return intIn + 5;
}

class MultiplyClass {
protected:
	int multiplier;
	int result;

public:
	MultiplyClass(const int &multiplierIn) :
			multiplier(multiplierIn), result(0) {
	}

	virtual ~MultiplyClass() {
	}

	int getResult() {
		return result;
	}

	int multiplyByMultiplier(const int &intIn, std::string &strIn) {
		strIn += "Multiplying by " + std::to_string(multiplier); // Tracking
		this->result = intIn * this->multiplier;
		return this->result;
	}
};

TEST_F(CallbackTest, StartingUpGuideTest) {
	// Creating an instance of MasterClass
	MasterClass masterInstance(11);

	// Registering addFive function as a callback
	masterInstance.registerCallback(addFive);

	// Creating an instance of MultiplyClass
	MultiplyClass multiplyInstance(-2);
	// Registering multiplyByMultiplier method as a callback
	masterInstance.registerCallback(
			std::bind(&MultiplyClass::multiplyByMultiplier, &multiplyInstance,
					std::placeholders::_1, std::placeholders::_2));

	// Registering a lambda function adding 32
	masterInstance.registerCallback([](const int &intIn, std::string &strIn) {
		strIn += "Adding 32"; // Tracking
			return intIn + 32;
		});

	// Calling superMethod
	std::string ret = masterInstance.superMethod();

	// Displaying output
	std::cout << ret << std::endl;

	ASSERT_EQ(masterInstance.getValue(), 0);
	ASSERT_EQ(multiplyInstance.getResult(), -32);

	// Calling superMethod
	ret = masterInstance.superMethod();
	// Displaying output
	std::cout << ret << std::endl;

	ASSERT_EQ(masterInstance.getValue(), 22);

}

int addInt(const int &a, const int &b) {
	return a + b;
}

long addLong(const long &a, const long &b) {
	return a + b;
}

double addDouble(const double &a, const double &b) {
	return a + b;
}

struct someStruct {

	someStruct(double xIn) :
			x(xIn) {
	}

	void multiplyMyself(const int &val) {
		x *= static_cast<double>(val);
	}

	double x;
};

TEST_F(CallbackTest, CallbackUntypedTest) {
	someStruct someInstance(2.5);

	std::vector<CallbackUntypedHandle> cbUTVector;
	CallbackUntypedHandle a(addInt);
	CallbackUntypedHandle b(addLong);
	CallbackUntypedHandle c(addDouble);
	CallbackUntypedHandle d(&someStruct::multiplyMyself, &someInstance);

	cbUTVector.push_back(a);
	cbUTVector.push_back(b);
	cbUTVector.push_back(c);
	cbUTVector.push_back(d);

	CallbackTypedHandle<int(const int&, const int&)> aTyped(cbUTVector[0]);
	CallbackTypedHandle<long(const long&, const long&)> bTyped(cbUTVector[1]);
	CallbackTypedHandle<double(const double&, const double&)> cTyped(
			cbUTVector[2]);
	CallbackTypedHandle<void(const int&)> dTyped(cbUTVector[3]);

	ASSERT_EQ(aTyped((int ) 12, (int ) 24), 36);
	ASSERT_EQ(bTyped((long ) 12l, (long ) 24l), 36l);
	ASSERT_FLOAT_EQ(cTyped((double ) 12.0, (double ) 24.0), 36.0);
	dTyped((int) 3);
	ASSERT_EQ(someInstance.x, 7.5);
}

TEST_F(CallbackTest, EmptyCallbackTest) {
	CallbackImpl<int(const int&, const int &)> cb;
	ASSERT_FALSE(cb);
	ASSERT_FALSE(cb.isEmpty());
	cb.set(addInt);
	ASSERT_TRUE(cb);
	ASSERT_TRUE(cb.isEmpty());

}
