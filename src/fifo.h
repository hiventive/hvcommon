/**
 * @file hvutils.h
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date May, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief FIFO class
 */

#ifndef HV_FIFO_H
#define HV_FIFO_H

#include <cstdlib>
#include <iostream>
#include <array>

#include "hvutils.h"
#include "datatypes.h"

namespace hv {
namespace common {

template<typename T, std::size_t SIZE> class FIFO {
	public:
		FIFO(const T& resetValIn) :
				resetVal(resetValIn), startIndex(0), nextIndex(0), nElem(0) {
			reset();
		}
		virtual ~FIFO() {
		}

		void reset() {
			for (auto &it : values) {
				it = resetVal;
			}
		}

		bool isEmpty() const {
			return nElem == std::size_t(0);
		}

		bool isFull() const {
			return nElem == SIZE;
		}

		std::size_t size() {
			return nElem;
		}

		bool insert(const T& elem) {
			if (this->isFull()) {
				return false;
			}
			values[nextIndex] = elem;
			nextIndex = (nextIndex + 1u) % SIZE;
			nElem++;
			return true;
		}

		T pop() {
			if (!this->isEmpty()) {
				T ret = values[startIndex];
				startIndex = (startIndex + 1u) % SIZE;
				nElem--;
				return ret;
			} else {
				HV_LOG_ERROR("FIFO empty. Consider checking emptiness before popping");
				HV_EXIT_FAILURE();
				return T(0);
			}
		}

	protected:
		std::array<T, SIZE> values;
		T resetVal;
		std::size_t startIndex;
		std::size_t nextIndex;
		std::size_t nElem;

	};

} // namespace common
} // namespace

#endif
