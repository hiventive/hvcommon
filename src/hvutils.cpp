/**
 * @file hvutils.cpp
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Mar, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Utilitary functions
 */

#include "hvutils.h"

namespace hv {
namespace common {

char binStrToHexaMap(std::string binStr) {
	unsigned char tmp = 0;
	char ret;
	for (unsigned int i = 0; i < 4; i++) {
		tmp |= (binStr[i] == '1') ? (static_cast<unsigned char>(1) << i) : 0;
	}
	switch (tmp) {
	case 0:
		ret = '0';
		break;
	case 1:
		ret = '1';
		break;
	case 2:
		ret = '2';
		break;
	case 3:
		ret = '3';
		break;
	case 4:
		ret = '4';
		break;
	case 5:
		ret = '5';
		break;
	case 6:
		ret = '6';
		break;
	case 7:
		ret = '7';
		break;
	case 8:
		ret = '8';
		break;
	case 9:
		ret = '9';
		break;
	case 10:
		ret = 'A';
		break;
	case 11:
		ret = 'B';
		break;
	case 12:
		ret = 'C';
		break;
	case 13:
		ret = 'D';
		break;
	case 14:
		ret = 'E';
		break;
	default:
		ret = 'F';
		break;
	}
	return ret;
}

/**
 * Transforms a string representing binary value to a string representing hexadecimal value (MSB to LSB)
 * @param binStr Input binary string
 * @return Hexadecimal value
 */
std::string binStrToHexaStr(std::string binStr, bool MSBFirst) {
	std::string ret("");
	std::string binStrTmp(binStr);
	std::string tmp("");
	if(MSBFirst) {
		std::reverse(binStrTmp.begin(), binStrTmp.end());
	}
	const unsigned int N_SECTIONS =
			(binStrTmp.length() % 4) ?
					static_cast<unsigned int>(binStrTmp.length() / 4) + 1 :
					static_cast<unsigned int>(binStrTmp.length() / 4);
	for (unsigned int i = 0; i < N_SECTIONS; i++) {
		tmp = binStrTmp.substr(i * 4, 4);
		while (tmp.length() < 4) {
			tmp = tmp + '0';
		}
		ret = binStrToHexaMap(tmp) + ret;

	}
	ret = "0x" + ret;
	return ret;
}

namespace test {

// "Bit" string random generation

/**
 * Generates a random string of n 0s and 1s.
 * @param n String length
 * @return Random string
 */
std::string bitRandStr(unsigned int n) {
	std::string ret(n, '0');
	for (unsigned int i = 0; i < n; i++) {
		if (std::rand() % 2)
			ret[i] = '1';
	}
	return ret;

}

/**
 * Shifts a string
 * @param strIn Input string
 * @param nShift Shift deepness
 * @param toLeft True if shifting left, false if shifting right
 * @return Resulting string of same length
 */
std::string strShift(std::string strIn, unsigned int nShift, bool toLeft) {
	std::string ret(strIn);
	for (int i = 0; i < static_cast<int>(nShift); i++) {
		if (toLeft) {
			for (std::size_t j = 0; j < strIn.length() - 1; j++) {
				ret[j] = ret[j + 1];
			}
			ret[strIn.length() - 1] = '0';
		} else {
			for (std::size_t j = 0; j < strIn.length() - 1; j++) {
				ret[strIn.length() - 1 - j] = ret[strIn.length() - 2 - j];
			}
			ret[0] = '0';
		}
	}
	return ret;
}

/**
 * Returns Hamming weight of string
 * @param str Input for Hamming weight computation
 * @return Hamming weight
 */
unsigned int getHammingWeightStr(std::string str) {
	unsigned int ret = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == '1')
			ret++;
	}
	return ret;
}

} // namespace test

} // namespace common
} // namespace hv
