/**
 * @file bitvector.cpp
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Jun, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Class for efficient and intuitive bit vector representation and manipulation
 */

#include "bitvector.h"

namespace hv {
namespace common {

BitVector::BitVector() :
		parent(nullptr), data(staticData), binSize(32u), arraySize(
				HV_BV_ARRAY_SIZE(32u)), lowIndex(0u), highIndex(31u), maskLastCell(
				HV_BV_MASK_LAST_CELL(32u)) {
	this->instantiationChecks(32u);
	this->operator =(0u);
}

BitVector::BitVector(const bvsize_t &size, const bool &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvuint8_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvuint16_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvuint32_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvuint64_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvint8_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvint16_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvint32_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const hvint64_t &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {

	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bvsize_t &size, const std::string &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {
	this->instantiationChecks(size);
	this->fromString(value);
}

BitVector::BitVector(const bvsize_t &size, const BitVector &value,
		BitVector *parentPtr, const bvsize_t &lowIndexSelect,
		const bvsize_t &highIndexSelect) :
		parent(parentPtr), data(staticData), binSize(size), arraySize(
				HV_BV_ARRAY_SIZE(size)), lowIndex(lowIndexSelect), highIndex(
				parent == nullptr ? size - 1u : highIndexSelect), maskLastCell(
				HV_BV_MASK_LAST_CELL(size)) {
	this->instantiationChecks(size);
	this->operator =(value);
}

BitVector::BitVector(const bool &value) :
		BitVector(1, value) {
}

BitVector::BitVector(const hvuint8_t &value) :
		BitVector(8, value) {
}

BitVector::BitVector(const hvuint16_t &value) :
		BitVector(16, value) {
}

BitVector::BitVector(const hvuint32_t &value) :
		BitVector(32, value) {
}

BitVector::BitVector(const hvuint64_t &value) :
		BitVector(64, value) {
}

BitVector::BitVector(const hvint8_t &value) :
		BitVector(8, value) {
}

BitVector::BitVector(const hvint16_t &value) :
		BitVector(16, value) {
}

BitVector::BitVector(const hvint32_t &value) :
		BitVector(32, value) {
}

BitVector::BitVector(const hvint64_t &value) :
		BitVector(64, value) {
}

BitVector::BitVector(const std::string &value) :
		BitVector(value.length(), value) {
}

BitVector::BitVector(const BitVector &src) :
		BitVector(src.binSize, src, src.parent, src.lowIndex, src.highIndex) {
}

BitVector::~BitVector() {
	if (data != &(staticData[0])) {
		free(data);
	}
}

BitVector::bvsize_t BitVector::getSize() const {
	return this->binSize;
}

BitVector::bvsize_t BitVector::getArraySize() const {
	return this->arraySize;
}

BitVector::bvdata_t BitVector::getmaskLastCell() const {
	return this->maskLastCell;
}

BitVector* BitVector::getParentAddress() const {
	return this->parent;
}
BitVector::bvsize_t BitVector::getLowIndex() const {
	return this->lowIndex;
}
BitVector::bvsize_t BitVector::getHighIndex() const {
	return this->highIndex;
}

BitVector::bvdata_t* BitVector::getDataAddress() {
	return this->data;
}

BitVector::operator bool() const {
	return !this->operator !();
}

BitVector::operator hvuint8_t() const {
	return this->getData<hvuint8_t>();
}

BitVector::operator hvuint16_t() const {
	return this->getData<hvuint16_t>();
}

BitVector::operator hvuint32_t() const {
	return this->getData<hvuint32_t>();
}

BitVector::operator hvuint64_t() const {
	return this->getData<hvuint64_t>();
}

BitVector::operator hvint8_t() const {
	return this->getData<hvint8_t>();
}

BitVector::operator hvint16_t() const {
	return this->getData<hvint16_t>();
}

BitVector::operator hvint32_t() const {
	return this->getData<hvint32_t>();
}

BitVector::operator hvint64_t() const {
	return this->getData<hvint64_t>();
}

BitVector::operator std::string() const {
	return this->toString();
}

BitVector& BitVector::operator =(const bool &src) {
	this->setData<bool>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvuint8_t &src) {
	this->setData<hvuint8_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvuint16_t &src) {
	this->setData<hvuint16_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvuint32_t &src) {
	this->setData<hvuint32_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvuint64_t &src) {
	this->setData<hvuint64_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvint8_t &src) {
	this->setData<hvint8_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvint16_t &src) {
	this->setData<hvint16_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvint32_t &src) {
	this->setData<hvint32_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const hvint64_t &src) {
	this->setData<hvint64_t>(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const std::string &src) {
	this->fromString(src);
	this->updateParent();
	return *this;
}

BitVector& BitVector::operator =(const BitVector &src) {
	if (src.binSize >= binSize) {
		for (bvsize_t i = 0u; i < arraySize; i++) {
			data[i] = src.data[i];
		}
	} else { // src.binSize < binSize
		for (bvsize_t i = 0u; i < src.arraySize - 1u; i++) {
			data[i] = src.data[i];
		}
		data[src.arraySize - 1u] = src.data[src.arraySize - 1u]
				& src.maskLastCell;
		for (bvsize_t i = src.arraySize; i < arraySize; i++) {
			data[i] = static_cast<bvdata_t>(0u);
		}
	}
	this->updateParent();
	return *this;
}

BitVector BitVector::operator <<(const hvuint32_t &nShift) const {
	// Case 1: no shifting
	BitVector ret(binSize, *this);
	// Case 2: shifting larger than size
	if (nShift >= binSize) {
		ret = 0u;
	}
	// Case 3: general case
	else if (nShift) {
		const hvuint32_t s(nShift % BITWIDTH_OF(bvdata_t));
		const hvuint32_t invS(BITWIDTH_OF(bvdata_t) - s);
		const hvuint32_t s2((s ? nShift - 1u : nShift) / BITWIDTH_OF(bvdata_t));
		const bvdata_t maskL((static_cast<bvdata_t>(1u) << invS) - 1u);
		const bvdata_t maskH(~maskL);

		if (s) {
			ret.data[0] = ((data[0] & maskL) << s);
			for (bvsize_t i = 1u; i < arraySize; i++) {
				ret.data[i] = ((data[i] & maskL) << s)
						| ((data[i - 1] & maskH) >> invS);
			}
			for (bvsize_t i = 0u; i < (arraySize - s2); i++) {
				ret.data[arraySize - i - 1u] =
						ret.data[arraySize - i - s2 - 1u];
			}
		} else {
			for (bvsize_t i = 0u; i < (arraySize - s2); i++) {
				ret.data[arraySize - i - 1u] = data[arraySize - i - s2 - 1u];
			}
		}

		for (bvsize_t i = 0u; i < s2; i++) {
			ret.data[i] = 0u;
		}
	}
	return ret;
}

BitVector BitVector::operator <<(const hvint32_t &nShift) const {
	if (nShift >= 0) {
		return operator <<(static_cast<hvuint32_t>(nShift));
	}
	return operator >>(static_cast<hvuint32_t>(-nShift));
}

BitVector BitVector::operator >>(const hvuint32_t &nShift) const {
	// Case 1: no shifting
	BitVector ret(binSize, *this);
	// Case 2: shifting larger than size
	if (nShift >= binSize) {
		ret = 0u;
	}
	// Case 3: general case
	else if (nShift) {
		const hvuint32_t s(nShift % BITWIDTH_OF(bvdata_t));
		const hvuint32_t invS(BITWIDTH_OF(bvdata_t) - s);
		const hvuint32_t s2(nShift / BITWIDTH_OF(bvdata_t));
		const bvdata_t maskL((static_cast<bvdata_t>(1u) << s) - 1u);
		const bvdata_t maskH(~maskL);

		ret.data[arraySize - 1u] &= maskLastCell;
		if (arraySize >= 2u) {
			for (bvsize_t i = 0u; i < arraySize - 2u; i++) {
				ret.data[i] = ((data[i + 1] & maskL) << invS)
						| ((data[i] & maskH) >> s);
			}

			ret.data[arraySize - 2u] = ((data[arraySize - 1u] & maskLastCell
					& maskL) << invS) | ((data[arraySize - 2u] & maskH) >> s);
		}
		ret.data[arraySize - 1u] =
				((data[arraySize - 1u] & maskLastCell & maskH) >> s);
		for (bvsize_t i = 0u; i < (arraySize - s2); i++) {
			ret.data[i] = ret.data[i + s2];
		}
		for (bvsize_t i = arraySize - s2; i < arraySize; i++) {
			ret.data[i] = 0u;
		}
	}
	return ret;
}

BitVector BitVector::operator >>(const hvint32_t &nShift) const {
	if (nShift >= 0) {
		return operator >>(static_cast<hvuint32_t>(nShift));
	}
	return operator <<(static_cast<hvuint32_t>(-nShift));
}

BitVector& BitVector::operator<<=(const hvuint32_t &nShift) {
	this->operator =(this->operator <<(nShift));
	return *this;
}

BitVector& BitVector::operator <<=(const hvint32_t &nShift) {
	if (nShift >= 0) {
		return this->operator <<=(static_cast<hvuint32_t>(nShift));
	}
	return this->operator >>=(static_cast<hvuint32_t>(-nShift));
}

BitVector& BitVector::operator>>=(const hvuint32_t &nShift) {
	this->operator =(this->operator >>(nShift));
	return *this;
}

BitVector& BitVector::operator >>=(const hvint32_t &nShift) {
	if (nShift >= 0) {
		return this->operator >>=(static_cast<hvuint32_t>(nShift));
	}
	return this->operator <<=(static_cast<hvuint32_t>(-nShift));
}

bool BitVector::operator !() const {
	bool ret(false);
	for (bvsize_t i = 0; i < arraySize - 1; i++) {
		ret |= data[i];
	}
	ret |= (data[arraySize - 1] & maskLastCell);
	return !ret;
}

bool BitVector::operator &&(const BitVector &op2) const {
	return !((this->operator !()) || (!op2));
}

bool BitVector::operator ||(const BitVector &op2) const {
	return !((this->operator !()) && (!op2));
}

bool BitVector::operator ==(const BitVector &op2) const {
	bool ret(true);
	bool op1SmallerThanOp2(binSize <= op2.binSize);
	bvsize_t nFullCells(HV_MIN(arraySize, op2.arraySize) - 1u);
	for (bvsize_t i = 0; ret && (i < nFullCells); i++) {
		if (data[i] != op2.data[i]) {
			ret = false;
		}
	}
	if (ret) {
		if (arraySize == op2.arraySize) {
			ret = !((data[nFullCells] & maskLastCell)
					^ (op2.data[nFullCells] & op2.maskLastCell));
		} else if (op1SmallerThanOp2) {
			ret = !((data[arraySize - 1u] & maskLastCell)
					^ (op2.data[arraySize - 1u]));

			for (bvsize_t i = arraySize; ret && (i < op2.arraySize - 1u); i++) {
				if (op2.data[i] != 0u) {
					ret = false;
				}
			}
			if (ret
					&& ((op2.data[op2.arraySize - 1u] & op2.maskLastCell) != 0u)) {
				ret = false;
			}
		} else {
			ret = !((data[op2.arraySize - 1u])
					^ (op2.data[op2.arraySize - 1u] & op2.maskLastCell));
			for (bvsize_t i = op2.arraySize; ret && (i < arraySize - 1u); i++) {
				if (data[i] != 0u) {
					ret = false;
				}
			}
			if (ret && ((data[arraySize - 1u] & maskLastCell) != 0u)) {
				ret = false;
			}
		}
	}
	return ret;
}

bool BitVector::operator !=(const BitVector &op2) const {
	return !this->operator ==(op2);
}

BitVector BitVector::operator ~() const {
	BitVector ret(binSize, 0u);
	for (bvsize_t i = 0u; i < arraySize; i++) {
		ret.data[i] = ~data[i];
	}
	return ret;
}

BitVector BitVector::operator &(const BitVector &op2) const {
	bvsize_t retSize(HV_MAX(binSize, op2.binSize));
	bvsize_t minArraySize(HV_MIN(arraySize, op2.arraySize));
	bool op1SmallerThanOp2(binSize <= op2.binSize);
	BitVector ret(retSize, 0u);
	for (bvsize_t i = 0u; i < minArraySize - 1u; i++) {
		ret.data[i] = data[i] & op2.data[i];
	}
	ret.data[minArraySize - 1u] =
			op1SmallerThanOp2 ?
					(data[minArraySize - 1u] & op2.data[minArraySize - 1u])
							& maskLastCell :
					(data[minArraySize - 1u] & op2.data[minArraySize - 1u])
							& op2.maskLastCell;
	return ret;
}

BitVector BitVector::operator |(const BitVector &op2) const {
	bvsize_t retSize(HV_MAX(binSize, op2.binSize));
	bvsize_t minArraySize(HV_MIN(arraySize, op2.arraySize));
	bool op1SmallerThanOp2(binSize <= op2.binSize);
	BitVector ret(retSize, 0u);
	for (bvsize_t i = 0u; i < minArraySize - 1u; i++) {
		ret.data[i] = data[i] | op2.data[i];
	}
	if (arraySize == op2.arraySize) {
		ret.data[minArraySize - 1u] = (data[minArraySize - 1u] & maskLastCell)
				| (op2.data[minArraySize - 1u] & op2.maskLastCell);
	} else if (op1SmallerThanOp2) {
		ret.data[minArraySize - 1u] = (data[minArraySize - 1u] & maskLastCell)
				| op2.data[minArraySize - 1u];
		for (bvsize_t i = minArraySize; i < op2.arraySize; i++) {
			ret.data[i] = op2.data[i];
		}
	} else {
		ret.data[minArraySize - 1u] = data[minArraySize - 1u]
				| (op2.data[minArraySize - 1u] & op2.arraySize);
		for (bvsize_t i = minArraySize; i < arraySize; i++) {
			ret.data[i] = data[i];
		}
	}
	return ret;
}

BitVector BitVector::operator ^(const BitVector &op2) const {
	bvsize_t retSize(HV_MAX(binSize, op2.binSize));
	bvsize_t minArraySize(HV_MIN(arraySize, op2.arraySize));
	bool op1SmallerThanOp2(binSize <= op2.binSize);
	BitVector ret(retSize, 0u);
	for (bvsize_t i = 0u; i < minArraySize - 1u; i++) {
		ret.data[i] = data[i] ^ op2.data[i];
	}
	ret.data[minArraySize - 1u] =
			op1SmallerThanOp2 ?
					(data[minArraySize - 1u] ^ op2.data[minArraySize - 1u])
							& maskLastCell :
					(data[minArraySize - 1u] ^ op2.data[minArraySize - 1u])
							& op2.maskLastCell;
	return ret;
}

BitVector& BitVector::operator &=(const BitVector &op2) {
	this->operator =(this->operator &(op2));
	return *this;
}

BitVector& BitVector::operator |=(const BitVector &op2) {
	this->operator =(this->operator |(op2));
	return *this;
}

BitVector& BitVector::operator ^=(const BitVector &op2) {
	this->operator =(this->operator ^(op2));
	return *this;
}

BitVector BitVector::operator +(const BitVector &op2) const {
	BitVector ret(binSize + op2.binSize, op2);
	BitVector tmp(binSize + op2.binSize, *this);
	tmp <<= op2.binSize;
	ret |= tmp;
	return ret;
}

BitVector BitVector::operator ()(const bvsize_t &ind1, const bvsize_t &ind2) {
	bool ind1SupInd2 = ind1 > ind2;
	bvsize_t ind1Tmp = ind1SupInd2 ? ind2 : ind1;
	bvsize_t ind2Tmp = ind1SupInd2 ? ind1 : ind2;
	// We now are sure that ind1Tmp <= ind2Tmp
	HV_ASSERT((0u <= ind1Tmp) && (ind2Tmp < binSize),
			"Index out of scope ({},{}) is not in (0,{})", ind1Tmp, ind2Tmp, (binSize - 1u));
	return BitVector(ind2Tmp - ind1Tmp + static_cast<bvsize_t>(1u),
			this->operator >>(ind1Tmp), this, ind1Tmp, ind2Tmp);

}

BitVector BitVector::operator ()(const bvsize_t &ind1,
		const bvsize_t &ind2) const {
	bool ind1SupInd2 = ind1 > ind2;
	bvsize_t ind1Tmp = ind1SupInd2 ? ind2 : ind1;
	bvsize_t ind2Tmp = ind1SupInd2 ? ind1 : ind2;
	// We now are sure that ind1Tmp <= ind2Tmp
	HV_ASSERT((0u <= ind1Tmp) && (ind2Tmp < binSize),
			"Index out of scope ({},{}) is not in (0,{})", ind1Tmp, ind2Tmp, (binSize - 1u));
	return BitVector(ind2Tmp - ind1Tmp + 1u, this->operator >>(ind1Tmp));
}

BitVector BitVector::operator [](const bvsize_t &ind) {
	HV_ASSERT((0u <= ind) && (ind < binSize),
			"Index out of scope ({}) is not in (0,{})", ind, (binSize - 1u));
	return BitVector(1u, this->operator >>(ind), this, ind, ind);
}

BitVector BitVector::operator [](const bvsize_t &ind) const {
	HV_ASSERT((0u <= ind) && (ind < binSize),
			"Index out of scope ({}) is not in (0,{})", ind, (binSize - 1u));
	return BitVector(1u, this->operator >>(ind));
}

void BitVector::rand() {
	// rand numbers are set by slices of 16 bits
	const bvsize_t HOW_MANY_RAND_NUMBERS_IN_A_CELL(sizeof(bvdata_t) / 2);
	const hvuint32_t sixteenBitsMask(
			static_cast<hvuint32_t>(~static_cast<hvuint16_t>(0u)));
	for (bvsize_t i = 0; i < arraySize; i++) {
		bvdata_t tmp = static_cast<bvdata_t>(::std::rand() & sixteenBitsMask);
		for (bvsize_t j = 1; j < HOW_MANY_RAND_NUMBERS_IN_A_CELL; j++) {
			tmp <<= 16;
			tmp |= static_cast<bvdata_t>(::std::rand() & sixteenBitsMask);
		}
		data[i] = tmp;
	}
}

void BitVector::fromString(const std::string &src) {
	this->reset();
	bvsize_t dataCpt(0u);
	bvsize_t arrayCpt(0u);
	bvdata_t mask(1u);
	bvsize_t assignmentLength(HV_MIN(src.length(), binSize));
	for (std::size_t i = 0; i < assignmentLength; i++) {
#ifdef HV_BV_STR_MSB_FIRST
		if (src[assignmentLength - i - 1u] == '1')
#else
			if (src[i] == '1')
#endif
			data[arrayCpt] |= mask;

		if (++dataCpt == BITWIDTH_OF(bvdata_t)) {
			arrayCpt++;
			dataCpt = static_cast<bvsize_t>(0u);
			mask = static_cast<bvdata_t>(1u);
		} else {
			mask <<= 1;
		}
	}
}

std::string BitVector::toString() const {

	std::string ret = "";
	bvdata_t mask(1u);
	bvdata_t dataTmp;
	for (bvsize_t i = 0; i < arraySize - 1; i++) {
		dataTmp = data[i];
		for (bvsize_t j = 0; j < BITWIDTH_OF(bvdata_t); j++) {
#ifdef HV_BV_STR_MSB_FIRST
			ret = ((dataTmp & mask) ? "1" : "0") + ret;
#else
			ret += (dataTmp & mask) ? "1" : "0";
#endif
			dataTmp >>= 1;
		}
	}
	dataTmp = data[arraySize - 1];
	bvsize_t nBitsLastCell(this->getLastCellSize());
	for (bvsize_t j = 0; j < nBitsLastCell; j++) {
#ifdef HV_BV_STR_MSB_FIRST
		ret = ((dataTmp & mask) ? "1" : "0") + ret;
#else
		ret += (dataTmp & mask) ? "1" : "0";
#endif
		dataTmp >>= 1;
	}
	return ret;
}

std::ostream& operator <<(std::ostream &strm, const BitVector &bv) {
	return strm << bv.toString();
}

BitVector BitVector::copy() const {
	return BitVector(binSize, *this);
}

BitVector BitVector::flip() const {
	BitVector ret(binSize, 0u);
	// Copy is inevitable to keep const qualifier
	BitVector tmp(*this);
	for (bvsize_t i = 0u; i < binSize; i++) {
		ret[i] = tmp[binSize - i - static_cast<bvsize_t>(1u)];
	}
	return ret;
}

BitVector BitVector::strip() const {

	if (this->operator !()) {
		return BitVector(1u, 0u);
	}

	// Copy is inevitable to keep const qualifier
	BitVector tmp(*this);
	bvsize_t nZeros(0u);
	bool oneWasFound(false);
	while (!oneWasFound) {
		if (!!tmp[binSize - nZeros - static_cast<bvsize_t>(1u)]) {
			oneWasFound = true;
		} else {
			nZeros++;
		}
	}
	return BitVector(binSize - nZeros, tmp);
}

void BitVector::resize(bvsize_t newSize) {
	if (parent != nullptr) {
		HV_LOG_ERROR("You can't resize a BitVector which has a parent");
		HV_EXIT_FAILURE();
	}
	bvsize_t newArraySize = HV_BV_ARRAY_SIZE(newSize);
	lowIndex = 0u;
	highIndex = newSize - 1u;

	// Managing size and data
	if (newSize < binSize) {
		maskLastCell = HV_BV_MASK_LAST_CELL(newSize);
		if ((arraySize > HV_BV_MAX_STATIC_ARRAY_SIZE)
				&& (newArraySize <= HV_BV_MAX_STATIC_ARRAY_SIZE)) {
			// Dynamically created array is now useless
			// Copying data
			for (bvsize_t i = 0u; i < newArraySize; i++) {
				staticData[i] = data[i];
			}
			free(data);
			data = staticData;
		}
		// Else there is nothing to do
	} else if (newSize > binSize) {
		// Applying last cell mask before copying
		data[arraySize - 1] &= maskLastCell;
		maskLastCell = HV_BV_MASK_LAST_CELL(newSize);

		// If array size has changed, modifications must be done
		if (newArraySize > arraySize) {
			// Memory reallocation could be necessary
			if (newArraySize > HV_BV_MAX_STATIC_ARRAY_SIZE) {
				bvdata_t* dataTmp = (bvdata_t*) malloc(
						newArraySize * sizeof(bvdata_t));
				if (dataTmp == nullptr) {
					std::cerr << "Allocation error" << std::endl;
					exit(EXIT_FAILURE);
				}
				for (bvsize_t i = 0u; i < arraySize; i++) {
					dataTmp[i] = data[i];
				}
				if (arraySize > HV_BV_MAX_STATIC_ARRAY_SIZE) {
					free(data);
				}
				data = dataTmp;
			}
			for (bvsize_t i = arraySize; i < newArraySize; i++) {
				data[i] = 0u;
			}
		}

	}
	arraySize = newArraySize;
	binSize = newSize;
}

void BitVector::instantiationChecks(const bvsize_t &size) {
	// Checking size and switching to dynamic if needed
	HV_ASSERT(size > 0, "BitVector size must be > 0");
	if (size > HV_BV_MAX_STATIC_BITWIDTH) {
		data = (bvdata_t*) malloc(arraySize * sizeof(bvdata_t));
		if (data == nullptr) {
			std::cerr << "Allocation error" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

void BitVector::updateParent() {
	if (parent != nullptr) {
		BitVector bvTmp(parent->binSize, *this);
		BitVector maskTmp(binSize, 0u);
		BitVector mask(parent->binSize, ~maskTmp);
		mask <<= lowIndex;
		bvTmp <<= lowIndex;
		*parent &= ~mask;
		*parent |= bvTmp;
		parent->updateParent();
	}
}

BitVector::bvsize_t BitVector::getLastCellSize() const {
	bvsize_t nBitsLastCell(binSize % BITWIDTH_OF(bvdata_t));
	if (!nBitsLastCell)
		nBitsLastCell = BITWIDTH_OF(bvdata_t);
	return nBitsLastCell;
}

void BitVector::reset() {
	for (bvsize_t i = 0u; i < arraySize; i++) {
		data[i] = static_cast<bvdata_t>(0u);
	}
}

} // namespace common
} // namespace hv

