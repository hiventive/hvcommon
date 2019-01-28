/**
 * @file callback.h
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Mar, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Callback class
 */

#ifndef HV_CALLBACK_H
#define HV_CALLBACK_H

#include <algorithm>
#include <iterator>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>
#include "datatypes.h"
#include "hvutils.h"

namespace hv {
namespace common {

/**
 * Untyped callback class
 * This class is an interface-like
 */
class CallbackUntyped {
public:
	typedef CallbackUntyped type;

	CallbackUntyped() {
	}

	virtual ~CallbackUntyped() {};

	template<typename T, typename R, typename ... Args> CallbackUntyped(
			R (T::*cbIn)(Args...), T *objIn) {
		this->set(cbIn, objIn);
	}

	template<typename R, typename ... Args> R invoke(Args ... args) const;

	template<typename T, typename R, typename ... Args> void set(
			R (T::*cbIn)(Args...), T *objIn);

	template<typename T> void set(const T &fIn);

	template<typename R, typename ... Args> std::function<R(Args...)> get() const;

};

template<typename R, typename ... Args> class CallbackImpl;
template<typename R, typename ... Args> class CallbackImpl<R(Args...)> : public CallbackUntyped {

public:
	typedef std::function<R(Args...)> Functor;
	typedef R (*signature)(Args...);
	typedef R return_t;
	typedef CallbackImpl<R(Args...)> type;

	/**
	 * Empty constructor
	 * Sets callback to an empty pointer
	 */
	CallbackImpl() : f(nullptr), id(0u) {
	}

	/**
	 * Generic callback constructor
	 * T can represent a classical function, a std::function, a std::bind...
	 * @param fIn Input function
	 */
	template<typename T> CallbackImpl(const T &fIn) :
			f(fIn), id(0u) {
	}

	/**
	 * Constructor from method of a class instance
	 * @param cb Class method
	 * @param obj Class instance
	 */
	template<typename T> CallbackImpl(R (T::*cbIn)(Args...), T *objIn) :
			f([objIn, cbIn](Args... args) {return (objIn->*cbIn)(args...);}), id(
					0u) {
	}

	/**
	 * Copy constructor
	 * @param src Source for copy
	 */
	CallbackImpl(const CallbackImpl &src) :
			f(src.f), id(src.id) {

	}

	virtual ~CallbackImpl() {
	}

	/**
	 * Call operator
	 * @param args Arguments for function call
	 * @return Return of function
	 */
	inline R operator()(Args ... args) const {
		return f(args...);
	}

	/**
	 * Callback invocation
	 * @param args Callback arguments
	 * @return Callback return
	 */
	R invoke(Args ... args) const {
		return this->operator()(args...);
	}

	/**
	 * Sets f to cbIn applied to objIn
	 * @param cbIn Class method
	 * @param objIn Class instance
	 */
	template<typename T> void set(R (T::*cbIn)(Args...), T *objIn) {
		f = [objIn, cbIn](Args... args) {return (objIn->*cbIn)(args...);};
	}

	template<typename T> void set(const T &fIn) {
		f = fIn;
	}

	Functor get() const {
		return f;
	}

	hvcbID_t getId() const {
		return id;
	}

	void setId(const hvcbID_t &idVal) {
		id = idVal;
	}

	explicit operator bool() const {
		return bool(f);
	}

	bool isEmpty() const {
		return bool(f);
	}

protected:
	Functor f;
	hvcbID_t id;
};

class CallbackUntypedHandle {
public:
	typedef CallbackUntypedHandle type;

	CallbackUntypedHandle(const CallbackUntypedHandle &cbUT) :
			cb(cbUT.cb), cpt(cbUT.cpt) {
		(*cpt)++;
	}

	template<typename T, typename R, typename ... Args> CallbackUntypedHandle(
			R (T::*cbIn)(Args...), T *objIn) :
			cb(new CallbackImpl<R(Args...)>(cbIn, objIn)), cpt(new std::size_t(1u)) {
	}

	template<typename R, typename ... Args> CallbackUntypedHandle(
			R (*fIn)(Args...)) :
			cb(new CallbackImpl<R(Args...)>(fIn)), cpt(new std::size_t(1u)) {
	}

	template<typename R, typename ... Args> CallbackUntypedHandle(
			std::function<R(Args...)> fIn) :
			cb(new CallbackImpl<R(Args...)>(fIn)), cpt(new std::size_t(1u)) {
	}

	template<typename R, typename ... Args> CallbackUntypedHandle(
			const CallbackImpl<R(Args...)> &cbIn) :
			cb(new CallbackImpl<R(Args...)>(cbIn)), cpt(new std::size_t(1u)) {
	}

	~CallbackUntypedHandle() {
		(*cpt)--;
		if (!(*cpt)) {
			delete cb;
			delete cpt;
		}
	}

	template<typename R, typename ... Args> R invoke(Args ... args) const;

	CallbackUntyped* cb;
	std::size_t* cpt;
};

template<typename R, typename ... Args> class CallbackTypedHandle;
template<typename R, typename ... Args> class CallbackTypedHandle<R(Args...)> : public CallbackUntypedHandle {
public:
	template<class, class ...> friend class CallbackTypedHandle;
	typedef CallbackTypedHandle<R(Args...)> type;

	template<typename T> CallbackTypedHandle(R (T::*cbIn)(Args...), T *objIn) :
	CallbackUntypedHandle(cbIn, objIn) {
	}

	template<typename T> CallbackTypedHandle(const T &fIn) :
	CallbackUntypedHandle(fIn) {
	}

	CallbackTypedHandle(const CallbackUntypedHandle &cbUT) :
	CallbackUntypedHandle(cbUT) {
	}

	CallbackTypedHandle(const CallbackImpl<R(Args...)> &cbIn) : CallbackUntypedHandle(cbIn) {}

	virtual ~CallbackTypedHandle() {
	}

	R invoke(Args ... args) const {
		return static_cast<CallbackImpl<R(Args...)>*>(cb)->invoke(args...);
	}

	inline R operator()(Args ... args) const {
		return this->invoke(args...);
	}
};

}
 // namespace hv
}// namespace common

#endif

