# Callback - Starting Guide

## Description

### What is a callback?

A callback is a notification mechanism triggered from a specific event in a given context. Adding a callback mechanism to a given context __C__ allows __C__ to be given a custom behaviour without modifying its source code, callbacks being __registered__ to __C__ context from another context __D__ including __C__. This mechanism gives an easy and fast access to an important scope of actions.

### Accessing Callback and CallbackVector classes

Callback and CallbackVector classes are declared in `callback.h` and are part of namespace `::hv::common`.

```cpp
#include "callback.h"
using namespace ::hv::common;
```

### Classes Description

Two main template classes constitute our callback mechanism: __Callback__ and __CallbackVector__.

__Callback__ is a container for functions to be registered as callbacks. It includes constructors from:

- Classical function pointers,
- `std::function` instances,
- Lambda functions, and
- Couple class instance/class method.

**CallbackVector** simply contains a `std::vector` of **Callback** instances. Its main advantage compared to a simple `std::vector` is that checking if a **CallbackVector** is empty is faster, which is profitable in contexts implementing callback mechanism but with no callback registered.

## A Basic How-To

This section develops a demonstration of callback specification and usage. All pieces of code presented here must be seen as a single monolithic code.

In this example, a class named **MasterClass** implements a single callback vector which is called when a method **SuperMethod()** is called. **MasterClass** has four data members:

1. An integer `value` which is the data member we want to be modified by callbacks,
2. A string `str` which will be used to track and monitor what happens,
3. An unsigned integer `cpt` which will also be used for tracking, and
4. A **CallbackVector** `myCallbackVector`.

The (arbitrary) function prototype of our callbacks will be:

```cpp
int(const int&, std::string&)
```

Considering what was previously discussed, the base for our **MasterClass** is:

```cpp
class MasterClass {
protected:
	// Type definitions for callbacks
	typedef Callback<int(const int&, std::string&)> cb_t;
	typedef CallbackVector<int(const int&, std::string&)> cbv_t;

	// Main data member
	int value;

	// Monitoring helpers
	std::string str;
	unsigned int cpt;

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
    
    std::string superMethod() {
        this->str += std::to_string(cpt++) + " - Entering superMethod()\n"; // Tracking
        this->str += std::to_string(cpt++) + " - Leaving superMethod()\n"; // Tracking
        return this->str;
    }
}
```

Well, this class is great, but we still need to implement our callback mechanism to:

- Register callbacks to `myCallbackVector`, and
- Run callbacks registered in `myCallbackVector` in `superMethod()`.

As `myCallbackVector` is protected, we need to add a registration method:

```cpp
void registerCallback(const cb_t &callback) {
    this->myCallbackVector.pushBack(callback);
}
```

We can also, why not, redirect other methods of **CallbackVector** like `size()` to get information:

```cpp
std::size_t howManyCallbacks() const {
    return this->myCallbackVector.size();
}
```

Finally, we have to add the calls to our callbacks in `superMethod()`. We (arbitrarily again) choose to make our callbacks work this way:

- The first parameter of each callback is **MasterClass** data member `value`.
- The second parameter is **MasterClass** data member `str` for tracking.
- The return value is then copied to **MasterClass** data member `value`.

```cpp
std::string superMethod() {
    this->str += std::to_string(cpt++) + " - Entering superMethod()\n"; // Tracking

    // Checking if there are registered callbacks
    if (!myCallbackVector.isEmpty()) {
        // Iterating on callbacks
        for (cbv_t::callbacks_it_t it = myCallbackVector.begin();
             it != myCallbackVector.end(); ++it) {

            std::string strTmp(std::to_string(cpt++) + " - "); // Tracking

            // Invoking callback
            this->value = (*it)(this->value, strTmp);

            this->str += strTmp + " - value = " + std::to_string(this->value) + "\n"; // Tracking
        }
    }
    this->str += std::to_string(cpt++) + " - Leaving superMethod()\n"; // Tracking
    return this->str;
}
```

You can notice that the method `myCallbackVector.isEmpty()` is called here to test if there are callbacks. However, it is obvious that the usage of the loop on the iterator coming just next would be enough to ensure the exact same behavior. To understand this syntax, let's compare the complexities:

- Not using `isEmpty()` method:
  1. Initialization of an iterator by a call to `myCallbackVector.begin()`,
  2. Initialization of an iterator by a call to `myCallbackVector.end()`, and
  3. Inequality test between both


- Using `isEmpty()` method:
  1. Comparison with a boolean contained by `myCallbackVector` instance.
  2. And that's all.
  3. Really, nothing more.

In C++ codes in general, a vector or an array is set to be used, so it is barely never empty when used. In the context of a general callback implementation however, the callback vector has non-negligible chances to be empty (you just don't always need callbacks. You even often don't need callbacks). Therefore, the cost of iterator initialization becomes a generally important penalty. The only thing to remember here is: **if you want performance in general, use CallbackVector::isEmpty()**.

Our **MasterClass** is now full. Here is its complete listing which won't be modified in the rest of the demonstration:

```cpp
class MasterClass {
protected:
	// Type definitions for callbacks
	typedef Callback<int(const int&, std::string&)> cb_t;
	typedef CallbackVector<int(const int&, std::string&)> cbv_t;

	// Main data member
	int value;

	// Monitoring helpers
	std::string str;
	unsigned int cpt;

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
		this->myCallbackVector.pushBack(callback);
	}

	// Accessor to myCallbackVector's size
	std::size_t howManyCallbacks() const {
		return this->myCallbackVector.size();
	}

	// Method using callbacks
	std::string superMethod() {
		this->str += std::to_string(cpt++) + " - Entering superMethod()\n"; // Tracking

		// Checking if there are registered callbacks
		if (!myCallbackVector.isEmpty()) {
			// Iterating on callbacks
			for (cbv_t::callbacks_it_t it = myCallbackVector.begin();
					it != myCallbackVector.end(); ++it) {

				std::string strTmp(std::to_string(cpt++) + " - "); // Tracking

				// Invoking callback
				this->value = (*it)(this->value, strTmp);

				this->str += strTmp + " - value = " + std::to_string(this->value)
						+ "\n"; // Tracking
			}
		}
		this->str += std::to_string(cpt++) + " - Leaving superMethod()\n"; // Tracking
		return this->str;
	}
};
```

Now, we need some callbacks to be registered. Let's start with a general function, which returns the result of the input integer plus five:

```cpp
int addFive(const int &intIn, std::string &strIn) {
	strIn += "Adding 5"; // Tracking
	return intIn + 5;
}
```

This function can be anywhere in the visible dependencies of our code. Let's imagine that in another dependency, we have the following class:

```cpp
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
```

Here, `MultiplyClass::multiplyByMultiplier()` method can be registered as a callback of **MasterClass** as it has the corresponding prototype.

Now our field is prepared, let's start. First, we have to create an instance of **MasterClass**:

```cpp
// Creating an instance of MasterClass
MasterClass masterInstance(11);
```

Then, we can directly register `addFive` function, which is as simple as:

```cpp
// Registering addFive function as a callback
masterInstance.registerCallback(addFive);
```

Then, we create an instance of **MultiplyClass**, setting the multiplier to -2:

```cpp
// Creating an instance of MultiplyClass
MultiplyClass multiplyInstance(-2);
```

Finally, we register `multiplyInstance.multiplyByMultiplier` method as the second callback of `masterInstance` the following way:

```cpp
// Registering multiplyByMultiplier method as a callback
masterInstance.registerCallback(std::bind(&MultiplyClass::multiplyByMultiplier, &multiplyInstance, std::placeholders::_1, std::placeholders::_2));
```

Let's stop a few seconds on this syntax. The standard function `std::bind(...)` is used to return a function binding the object `multiplyInstance` to the class method `MultiplyClass::multiplyByMultiplier`. The following arguments `std::placeholders::_1` and `std::placeholders::_2` link the argument positions 1 and 2 of `multiplyClass::multiplyByMultiplier` to the output function. It is important to put as many placeholders as there are arguments (possible from 0 to 29 arguments).

I now want to register a function adding 32 to `masterInstance` value, but some superior force forbid me to insert any code outside of the context where `masterInstance` is declared. No problem, let's use a lambda:

```cpp
// Registering a lambda function adding 32
masterInstance.registerCallback([](const int &intIn, std::string &strIn) {
    strIn += "Adding 32"; // Tracking
    return intIn + 32;
});
```

Now we added 3 callbacks, let's run `superMethod()` and display its return string to see what happens:

```cpp
// Calling superMethod
std::string ret = masterInstance.superMethod();

// Displaying output
std::cout << ret << std::endl;
```

which outputs at execution just as intended:

```bash
0 - Initialization - value = 11
1 - Entering superMethod()
2 - Adding 5 - value = 16
3 - Multiplying by -2 - value = -32
4 - Adding 32 - value = 0
5 - Leaving superMethod()
```

If we check the value of `masterInstance.value`:

```cpp
std::cout << "masterInstance.value = " << masterInstance.getValue() << std::endl;
```

We get:

```bash
masterInstance.value = 0
```

More interesting, let's check the value of `multiplyInstance.result`:

```bash
std::cout << "multiplyInstance.result = " << multiplyInstance.getResult() << std::endl;
```

which outputs:

```bash
multiplyInstance.result = -32
```

This means that an instance of **MasterClass** is able to operate on the data members of an instance of **MultiplyClass** being related only by a callback registration.

If we now call `superMethod()` again and display, we get:

```bash
0 - Initialization - value = 11
1 - Entering superMethod()
2 - Adding 5 - value = 16
3 - Multiplying by -2 - value = -32
4 - Adding 32 - value = 0
5 - Leaving superMethod()
6 - Entering superMethod()
7 - Adding 5 - value = 5
8 - Multiplying by -2 - value = -10
9 - Adding 32 - value = 22
10 - Leaving superMethod()
```

Combining this memory effect and the ability to activate methods of any unrelated class instance, the possibilities brought by callbacks are nearly infinite.

Now it's up to you. Be Hiventive!