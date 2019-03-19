/**
 * @file hvutils.h
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Mar, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Utilitary functions
 */

#ifndef HVUTILS_H
#define HVUTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <cci_configuration>

#include "datatypes.h"
#include "log.h"

/**
 * Determines the binary size of type T
 */
#define BITWIDTH_OF(T) ((sizeof(T)*8))

/**
 * Determines the number of bytes occupied by a W-bit element
 */
#define HV_BIT_TO_BYTE(W) ( ((W) % 8) ? ( (W) / 8 + 1 ) : ((W) / 8) )
/**
 * Determines the number of bits by occupied by a W-byte element
 */
#define HV_BYTE_TO_BIT(W) ( (W) * 8 )

/**
 * Generates a LSB mask (0000....11111) of type T with n 1s
 */
#define HV_LSB_MASK_GEN(T,n)  (((n) < BITWIDTH_OF(T)) ? (~((static_cast<T>(~static_cast<T>(0))) << static_cast<unsigned int>((n)))) : ~static_cast<T>(0))

/**
 * Generates a MSB mask (1111....00000) of type T with n 1s
 */
#define HV_MSB_MASK_GEN(T,n)  ((n) > 0 ? (((static_cast<T>(~static_cast<T>(0))) << static_cast<unsigned int>((n)))) : ~static_cast<T>(0))

/**
 * Generates a bit mask (0000100...000) of type T with 1 at index n
 */
#define HV_BIT_MASK_GEN(T,n) (static_cast<T>(1) << (n))

/**
 * Generates a mask (0001111...1111100) of type T with 1s between l (low) and h (high) indexes
 */

#define HV_MASK_GEN(T,l,h) ((~((~static_cast<T>(0)) << static_cast<unsigned int>((h)-(l)+1))) << static_cast<unsigned int>(l))

/**
 * Gets the container size of a w-bit LongWidth
 */
#define HV_MIN(x,y) ( (x) <= (y) ? (x) : (y) )
#define HV_MAX(x,y) ( (x) >= (y) ? (x) : (y) )
#define HV_ABS(x) ( (x) < (0) ? (-x) : (x) )

/**
 * Macros to exit and abort
 */
#define HV_EXIT_FAILURE() exit(EXIT_FAILURE)
#define HV_ABORT() abort()

/**
 * Macro for assertions
 */

#ifndef NDEBUG
#define HV_ASSERT(x,...) if (!(x)) { \
	HV_LOG_ERROR(__VA_ARGS__); \
	HV_EXIT_FAILURE(); \
}
#else
#define HV_ASSERT(x,...)
#endif

/**
 * Backward compatibility // TODO: REMOVE ME
 */
#define HV_ERR(m) HV_LOG_WARNING("HV_ERR is deprecated, use HV_LOG_ERROR instead."); std::cerr << m << std::endl; HV_EXIT_FAILURE();
#define HV_WARN(m) HV_LOG_WARNING("HV_WARN is deprecated, use HV_LOG_WARNING instead."); std::cout << m << std::endl;

//** CPP MACROS **//
/**
 * Macro to know if alias template are allowed
 * They are not activated on VS 2012
 * We deactivate them on VS 2013 because there seems to be
 * problems with partial alias template specification
 */
#ifdef _MSC_VER
#if _MSC_VER < 1900
#define HV_CPLUSPLUS_NO_ALIAS_TEMPLATE
#endif
#endif

//** SYSTEMC MACROS **//
/**
 * Macro for resetting system context
 */

#define HV_SYSTEMC_RESET_CONTEXT sc_core::sc_curr_simcontext = new sc_core::sc_simcontext(); sc_core::sc_default_global_context = sc_core::sc_curr_simcontext;
#define HV_SYSTEMC_HIERARCHY_CHAR '.'

namespace hv {
namespace common {

// Binary string manipulation
/**
 * Maps a 4-char string to a char representing its hexadecimal value (LSB to MSB)
 * @param binStr 4-char input string
 * @return Hexadecimal value
 */
char binStrToHexaMap(std::string binStr);

/**
 * Transforms a string representing binary value to a string representing hexadecimal value (LSB to MSB)
 * @param binStr Input binary string
 * @return Hexadecimal value
 */
std::string binStrToHexaStr(std::string binStr, bool MSBFirst = true);

/**
 * Transforms src to binary string of size BIT_WIDTH
 * @param src Source for the transformation
 * @return String of 0s and 1s MSB first
 */
template<typename T, std::size_t BIT_WIDTH> std::string toBinStr(const T &src) {
	const T mask = HV_BIT_MASK_GEN(T, 0);
	T tmp = src;
	std::string ret("");
	for (unsigned int i = 0; i < BIT_WIDTH; i++) {
		ret = ret + ((!(tmp & mask)) ? '0' : '1');
		tmp >>= 1;
	}
	return ret;
}

// Maths
template<typename T> T superiorPowerOf2(const T& in) {
	// Finding x = floor(log2(in))
	if (in == static_cast<T>(0)) {
		HV_LOG_ERROR("0 is an invalid input");
		HV_EXIT_FAILURE();
	}
	if (in == static_cast<T>(1))
		return static_cast<T>(1);
	T ret = 0;
	T tmp = in;
	while (tmp > 1) {
		tmp >>= 1;
		ret++;
	}
	// Computing 2^(ret)
	ret = (static_cast<T>(1) << ret);
	// Returning in if in is already a power of 2, retLog2 else
	return in == ret ? ret : static_cast<T>(2) * ret;
}

namespace test {

// "Bit" string random generation

/**
 * Generates a random string of n 0s and 1s.
 * @param n String length
 * @return Random string
 */
std::string bitRandStr(unsigned int n);

/**
 * Shifts a string
 * @param strIn Input string
 * @param nShift Shift deepness
 * @param toLeft True if shifting left, false if shifting right
 * @return Resulting string of same length
 */
std::string strShift(std::string strIn, unsigned int nShift, bool toLeft);

/**
 * Returns Hamming weight of string
 * @param str Input for Hamming weight computation
 * @return Hamming weight
 */
unsigned int getHammingWeightStr(std::string str);

/**
 * Generates a random number of type T.
 * All bits from LSBs to MSBs are randomized, whatever the bitwidth of T is.
 * @return Random number
 */
template<typename T> T randNumGen(std::size_t n) {
	T ret(0);
	static const unsigned int N_BIT_RANDMAX =
			static_cast<unsigned int>(RAND_MAX) == 32767 ? 16 : 32;
	static const unsigned int N_BIT_T = BITWIDTH_OF(T);
	static const unsigned int N_SLICES =
			(N_BIT_T <= N_BIT_RANDMAX) ? 1 :
			!(N_BIT_T % N_BIT_RANDMAX) ?
					(N_BIT_T / N_BIT_RANDMAX) : ((N_BIT_T / N_BIT_RANDMAX) + 1);

	for (unsigned int i = 0; i < N_SLICES; i++) {
		ret |= static_cast<T>(std::rand())
				<< static_cast<unsigned int>(i * N_BIT_RANDMAX);
	}
	if (n < BITWIDTH_OF(T))
		ret &= HV_LSB_MASK_GEN(T, n);
	return ret;
}

} // namespace test
} // namespace common
} // namespace hv

//** CCI value converter implementations **//
namespace cci {
// Implementation of cci_value converter from/to BitVector
template<>
struct cci_value_converter<::hv::common::hvrwmode_t> {
	typedef ::hv::common::hvrwmode_t type;
	static bool pack(cci_value::reference dst, type const & src) {
		switch (src) {
		case ::hv::common::RW:
			dst.set_string("RW");
			break;
		case ::hv::common::RO:
			dst.set_string("RO");
			break;
		case ::hv::common::WO:
			dst.set_string("WO");
			break;
		default:
			dst.set_string("NA");
			break;
		}
		return true;
	}

	static bool unpack(type & dst, cci_value::const_reference src) {
		if (!src.is_string()) {
			return false;
		}

		::std::string srcString;
		if (!src.try_get(srcString)) {
			return false;
		}

		if (!srcString.compare("RW")) {
			dst = ::hv::common::RW;
			return true;
		}

		if (!srcString.compare("RO")) {
			dst = ::hv::common::RO;
			return true;
		}

		if (!srcString.compare("WO")) {
			dst = ::hv::common::WO;
			return true;
		}

		if (!srcString.compare("NA")) {
			dst = ::hv::common::NA;
			return true;
		}
		return false;
	}
};
} // namespace cci

#endif /* HVUTILS_H */
