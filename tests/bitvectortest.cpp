/**
 * @file bitvectortest.cpp
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Jun, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Tests for bitvector.h
 *
 * These tests are memory-leak-free.
 * Most tests rely on random numbers generation.
 * The probability of false positive is extremely low.
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cci_configuration>
#include "gtest/gtest.h"
#include "bitvector.h"
#include "hvutils.h"

using namespace ::hv::common;
using namespace ::cci;

class BitVectorTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Tests are iterated 1000 times (except slower tests
		// which are iterated a fraction of 1000 times (10, 100)).
		nTests = 1000;
		// All sizes from 1 to 130 are tested
		maxSize = 130;
	}

	virtual void TearDown() {
	}

	hvuint32_t nTests;
	BitVector::bvsize_t maxSize;
};

TEST_F(BitVectorTest, AssignmentCastTestFromBool) {
	for (auto size = 1u; size <= maxSize; size++) {
		bool x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = rand() % 2;
			bv = x;
			y = bool(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvuint8) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvuint8_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvuint8_t>(HV_MIN(8, size));
			bv = x;
			y = hvuint8_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvuint16) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvuint16_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvuint16_t>(HV_MIN(16, size));
			bv = x;
			y = hvuint16_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvuint32) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvuint32_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvuint32_t>(HV_MIN(32, size));
			bv = x;
			y = hvuint32_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvuint64) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvuint64_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvuint64_t>(HV_MIN(64, size));
			bv = x;
			y = hvuint64_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvint8) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvint8_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvint8_t>(HV_MIN(8, size));
			bv = x;
			y = hvint8_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvint16) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvint16_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvint16_t>(HV_MIN(16, size));
			bv = x;
			y = hvint16_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvint32) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvint32_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvint32_t>(HV_MIN(32, size));
			bv = x;
			y = hvint32_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromHvint64) {
	for (auto size = 1u; size <= maxSize; size++) {
		hvint64_t x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests; j++) {
			x = ::hv::common::test::randNumGen<hvint64_t>(HV_MIN(64, size));
			bv = x;
			y = hvint64_t(bv);
			ASSERT_EQ(x, y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromString) {
	for (auto size = 1u; size <= maxSize; size++) {
		std::string x, y;
		BitVector bv(size, 0u);
		for (auto j = 0u; j < nTests / 10; j++) {
			// TODO: more tests with strings of length != size
			// Until then let's have faith
			x = ::hv::common::test::bitRandStr(size);
			bv = x;
			y = bv.toString();
			ASSERT_STREQ(x.c_str(), y.c_str())<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
		}
	}
}

TEST_F(BitVectorTest, AssignmentCastTestFromBitVector) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector x(size, 0u);
		for (auto size2 = 1u; size2 <= maxSize; size2++) {
			BitVector y(size2, 0u);
			for (auto j = 0u; j < nTests / 10; j++) {
				x.rand();
				y = x;
				x = y;
				ASSERT_TRUE(x == y)<< "Assignment/Cast failed (size = " << size << ", x = " << x << ", y = " << y << ")";
			}
		}

	}
}

TEST_F(BitVectorTest, LeftShiftTest) {
	for (auto size = 1u; size <= 70; size++) {
		for (auto j = 0u; j < 5; j++) {
			BitVector bv1(size, 0u);
			BitVector bv2(size, 0u);
			bv1.rand();
			std::string bv1Str = bv1;
			std::string bv2Str;
			for (auto shiftVal = 0u; shiftVal < size; shiftVal++) {
				bv2 = bv1 << shiftVal;
#ifdef HV_BV_STR_MSB_FIRST
				bv2Str = ::hv::common::test::strShift(bv1Str, shiftVal, true);
#else
				bv2Str = ::hv::common::test::strShift(bv1Str,shiftVal,false);
#endif
				ASSERT_STREQ(bv2.toString().c_str(), bv2Str.c_str())<< "Left shift test failed (shifting by " << shiftVal << ", origin = " << bv1Str << ")";
			}
		}
	}
}

TEST_F(BitVectorTest, RightShiftTest) {
	for (auto size = 12u; size <= 70; size++) {
		for (auto j = 0u; j < 5; j++) {
			BitVector bv1(size, 0u);
			BitVector bv2(size, 0u);
			bv1.rand();
			std::string bv1Str = bv1;
			std::string bv2Str;
			for (auto shiftVal = 0u; shiftVal < size; shiftVal++) {
				bv2 = bv1 >> shiftVal;
#ifdef HV_BV_STR_MSB_FIRST
				bv2Str = ::hv::common::test::strShift(bv1Str, shiftVal, false);
#else
				bv2Str = ::hv::common::test::strShift(bv1Str,shiftVal,true);
#endif
				ASSERT_STREQ(bv2.toString().c_str(), bv2Str.c_str())<< "Right shift test failed (shifting by " << shiftVal << ", origin = " << bv1Str << ")";
			}
		}
	}
}

TEST_F(BitVectorTest, SelfLeftShiftTest) {
	for (auto size = 1u; size <= 70; size++) {
		for (auto j = 0u; j < 5; j++) {
			BitVector bv1(size, 0u);
			BitVector bv2(size, 0u);
			bv1.rand();
			bv2 = bv1;
			std::string bv1Str = bv1;
			std::string bv2Str;
			for (auto shiftVal = 1u; shiftVal < size; shiftVal++) {
				bv2 <<= 1;
#ifdef HV_BV_STR_MSB_FIRST
				bv2Str = ::hv::common::test::strShift(bv1Str, shiftVal, true);
#else
				bv2Str = ::hv::common::test::strShift(bv1Str,shiftVal,false);
#endif
				ASSERT_STREQ(bv2.toString().c_str(), bv2Str.c_str())<< "Self left shift test failed (shifting by " << shiftVal << ", origin = " << bv1Str << ")";
			}
		}
	}
}

TEST_F(BitVectorTest, SelfRightShiftTest) {
	for (auto size = 1u; size <= 70; size++) {
		for (auto j = 0u; j < 5; j++) {
			BitVector bv1(size, 0u);
			BitVector bv2(size, 0u);
			bv1.rand();
			bv2 = bv1;
			std::string bv1Str = bv1;
			std::string bv2Str;
			for (auto shiftVal = 1u; shiftVal < size; shiftVal++) {
				bv2 >>= 1;
#ifdef HV_BV_STR_MSB_FIRST
				bv2Str = ::hv::common::test::strShift(bv1Str, shiftVal, false);
#else
				bv2Str = ::hv::common::test::strShift(bv1Str,shiftVal,true);
#endif
				ASSERT_STREQ(bv2.toString().c_str(), bv2Str.c_str())<< "Self right shift test failed (shifting by " << shiftVal << ", origin = " << bv1Str << ")";
			}
		}
	}
}

TEST_F(BitVectorTest, LogicalNegationTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv(size, 0u);
		ASSERT_TRUE(!bv)<< "Logical negation test failed (1)";
		bv = ~bv;
		ASSERT_FALSE(!bv)<< "Logical negation test failed (2)";
	}
}

TEST_F(BitVectorTest, LogicalANDTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		ASSERT_FALSE(bv1 && bv2)<< "Logical AND test failed (1)";
		ASSERT_FALSE((~bv1) && bv2)<< "Logical AND test failed (2)";
		ASSERT_FALSE(bv1 && ~(bv2))<< "Logical AND test failed (3)";
		ASSERT_TRUE((~bv1) && ~(bv2))<< "Logical AND test failed (4)";
	}
}

TEST_F(BitVectorTest, LogicalORTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		ASSERT_FALSE(bv1 || bv2)<< "Logical OR test failed (1)";
		ASSERT_TRUE((~bv1) || bv2)<< "Logical OR test failed (2)";
		ASSERT_TRUE(bv1 || ~(bv2))<< "Logical OR test failed (3)";
		ASSERT_TRUE((~bv1) || ~(bv2))<< "Logical OR test failed (4)";
	}
}

TEST_F(BitVectorTest, IsEqualTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		for (auto size2 = 1u; size2 <= size; size2++) {
			BitVector bv2(size2, 0u);
			for (auto j = 0u; j < nTests / 10; j++) {
				bv2.rand();
				bv1 = bv2;
				ASSERT_TRUE(bv1 == bv2)<< "Equality test failed";
			}
		}
	}
}

TEST_F(BitVectorTest, IsDifferentTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		for (auto size2 = 1u; size2 <= maxSize; size2++) {
			BitVector bv2(size2, 0u);
			for (auto j = 0u; j < nTests / 10; j++) {
				bv2.rand();
				do {
					bv1.rand();
				} while (bv1 == bv2);
				ASSERT_TRUE(bv1 != bv2)<< "Difference test failed";
			}
		}
	}
}

TEST_F(BitVectorTest, BinaryNegationTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		for (auto j = 0u; j < nTests / 10; j++) {
			bv1.rand();
			bv2 = ~bv1;
			ASSERT_TRUE(bv1 != bv2)<< "Binary negation test failed (1)";
			ASSERT_TRUE(bv1 == ~bv2)<< "Binary negation test failed (2)";
		}
	}
}

TEST_F(BitVectorTest, BinaryANDTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		ASSERT_TRUE((bv1 & bv2) == 0u)<< "Binary AND failed (1)";
		ASSERT_TRUE((bv1 & ~bv2) == 0u)<< "Binary AND failed (2)";
		ASSERT_TRUE(~(~bv1 & ~bv2) == 0u)<< "Binary AND failed (3)";
	}
}

TEST_F(BitVectorTest, BinaryORTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		ASSERT_TRUE((bv1 | bv2) == 0u)<< "Binary OR failed (1)";
		ASSERT_TRUE(~(bv1 | ~bv2) == 0u)<< "Binary OR failed (2)";
		ASSERT_TRUE(~(~bv1 | ~bv2) == 0u)<< "Binary OR failed (3)";
	}
}

TEST_F(BitVectorTest, BinaryXORTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		ASSERT_TRUE((bv1 ^ bv2) == 0u)<< "Binary XOR failed (1)";
		ASSERT_TRUE(~(bv1 ^ ~bv2) == 0u)<< "Binary XOR failed (2)";
		ASSERT_TRUE((~bv1 ^ ~bv2) == 0u)<< "Binary XOR failed (3)";
	}
}

TEST_F(BitVectorTest, SelfBinaryANDTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		bv2 &= bv1;
		ASSERT_TRUE(bv2 == 0u)<< "Binary AND and assignment failed (1)";
		bv2 &= ~bv1;
		ASSERT_TRUE(bv2 == 0u)<< "Binary AND and assignment failed (2)";
		bv2 = ~bv2;
		bv2 &= ~bv1;
		ASSERT_TRUE(~bv2 == 0u)<< "Binary AND and assignment failed (3)";
	}
}

TEST_F(BitVectorTest, SelfBinaryORTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		bv2 |= bv1;
		ASSERT_TRUE(bv2 == 0u)<< "Binary OR and assignment failed (1)";
		bv2 |= ~bv1;
		ASSERT_TRUE(~bv2 == 0u)<< "Binary OR and assignment failed (2)";
		bv2 |= bv1;
		ASSERT_TRUE(~bv2 == 0u)<< "Binary OR and assignment failed (3)";
	}
}

TEST_F(BitVectorTest, SelfBinaryXORTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv1(size, 0u);
		BitVector bv2(size, 0u);
		bv2 ^= bv1;
		ASSERT_TRUE(bv2 == 0u)<< "Binary XOR and assignment failed (1)";
		bv2 ^= ~bv1;
		ASSERT_TRUE(~bv2 == 0u)<< "Binary XOR and assignment failed (2)";
		bv2 = ~bv2;
		bv2 ^= bv1;
		ASSERT_TRUE(bv2 == 0u)<< "Binary XOR and assignment failed (3)";
	}
}

TEST_F(BitVectorTest, ConcatenationTest) {
	for (auto size = 12u; size <= maxSize; size++) {
		for (auto j = 0u; j < 5; j++) {
			BitVector::bvsize_t size1 = (std::rand() % (size - 1)) + 1;
			BitVector::bvsize_t size2 = size - size1;
			std::string bv1Str = test::bitRandStr(size1);
			std::string bv2Str = test::bitRandStr(size2);
			BitVector bv1(bv1Str);
			BitVector bv2(bv2Str);
			std::string concatStr;
#ifdef HV_BV_STR_MSB_FIRST
			concatStr = bv2Str + bv1Str;
#else
			concatStr = bv1Str + bv2Str;
#endif
			ASSERT_STREQ(concatStr.c_str(), (bv2 + bv1).toString().c_str())<< "Concatenation test failed (part1 = " << bv1Str << ", part2 = " << bv2Str << ")";
		}
	}
}

TEST_F(BitVectorTest, VectorSelectionTest) {
	for (auto size = 12u; size <= maxSize; size++) {
		std::string str(size, '0');
		BitVector bv(size, 0u);
		for (auto j = 0u; j < 10; j++) {
			// Picking random indexes
			hvuint32_t ind1 = rand() % size;
			hvuint32_t ind2 = rand() % size;
			if (ind1 > ind2) {
				hvuint32_t indTmp = ind1;
				ind1 = ind2;
				ind2 = indTmp;
			}
			hvuint32_t pickedSize(ind2 - ind1 + 1u);
			std::string strTmp = ::hv::common::test::bitRandStr(pickedSize);

			bv(ind1, ind2) = strTmp;
			for (auto ind = 0u; ind < pickedSize; ind++) {
#ifdef HV_BV_STR_MSB_FIRST
				str[size - ind - 1u - ind1] = strTmp[pickedSize - ind - 1u];
#else
				str[ind + ind1] = strTmp[ind];
#endif
			}
			ASSERT_STREQ(bv.toString().c_str(), str.c_str())<< "Vector selection failed (ind1 = " << ind1 << ", ind2 = " << ind2 << ", selection = " << strTmp << ")";
		}
	}
}

TEST_F(BitVectorTest, BitSelectionTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		std::string str(size, '0');
		BitVector bv(size, 0u);
		for (auto ind = 0u; ind < size; ind++) {
			bv[ind] = 1;
#ifdef HV_BV_STR_MSB_FIRST
			str[size - ind - 1] = '1';
#else
			str[ind] = '1';
#endif
			ASSERT_STREQ(bv.toString().c_str(), str.c_str())<< "Bit selection failed";
		}
		for (auto ind = 0u; ind < size; ind++) {
			bv[ind] = 0;
#ifdef HV_BV_STR_MSB_FIRST
			str[size - ind - 1] = '0';
#else
			str[ind] = '0';
#endif
			ASSERT_STREQ(bv.toString().c_str(), str.c_str())<< "Bit selection failed";
		}
	}
}

TEST_F(BitVectorTest, InteroperabilityTest) {
	hvuint32_t x;
	BitVector bv(32, 0u);

	for (auto i = 0u; i < nTests; i++) {
		bv = 0;
		bv.rand();
		x = 0xFFFFFFFF;
		x &= bv;
		ASSERT_TRUE((bv & 0xFFFFFFFF) == bv)<< "Interoperability of & failed (1)";
		ASSERT_TRUE((0xFFFFFFFF & bv) == bv)<< "Interoperability of & failed (2)";
		ASSERT_EQ(x, hvuint32_t(bv))<< "Interoperability of &= failed (1)";
		bv = 0xFFFFFFFF;
		x = ::std::rand();
		bv &= x;
		ASSERT_EQ(hvuint32_t(bv), x)<< "Interoperability of &= failed (2)";

		bv.rand();
		x = 0;
		x |= bv;
		ASSERT_TRUE((bv | 0) == bv)<< "Interoperability of | failed (1)";
		ASSERT_TRUE((0 | bv) == bv)<< "Interoperability of | failed (2)";
		ASSERT_EQ(x, hvuint32_t(bv))<< "Interoperability of |= failed (1)";
		bv = 0;
		x = ::std::rand();
		bv |= x;
		ASSERT_EQ(hvuint32_t(bv), x)<< "Interoperability of |= failed (2)";

		bv.rand();
		x = 0;
		x ^= bv;
		ASSERT_TRUE((bv ^ 0) == bv)<< "Interoperability of ^ failed (1)";
		ASSERT_TRUE((0 ^ bv) == bv)<< "Interoperability of ^ failed (2)";
		ASSERT_EQ(x, hvuint32_t(bv))<< "Interoperability of ^= failed (1)";
		bv = 0;
		x = ::std::rand();
		bv ^= x;
		ASSERT_EQ(hvuint32_t(bv), x)<< "Interoperability of ^= failed (2)";

		bv.rand();
		x = bv;
		ASSERT_TRUE(x == bv)<< "Interoperability of == failed (1)";
		ASSERT_TRUE(bv == x)<< "Interoperability of == failed (2)";
		ASSERT_FALSE(x != bv)<< "Interoperability of != failed (1)";
		ASSERT_FALSE(bv != x)<< "Interoperability of != failed (2)";

		// TODO test interoperability with std::string
	}

}

TEST_F(BitVectorTest, FlipTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv(size, 0u);
		for (auto i = 0u; i < nTests / 100; i++) {
			bv.rand();
			std::string str(bv);
			std::reverse(str.begin(), str.end());
			ASSERT_STREQ(bv.flip().toString().c_str(), str.c_str())<< "Flip test failed";
		}
	}

}

TEST_F(BitVectorTest, StripTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bv(size, 0u);
		for (auto i = 0u; i < nTests / 100; i++) {
			bv.rand();
			std::string str;
			if (!bv) {
				str = "0";
			} else {
				str = bv.toString();
				std::size_t nZeros(0u);
				bool oneWasFound(false);
				while (!oneWasFound) {
					if (str[nZeros] == '1') {
						oneWasFound = true;
					} else {
						nZeros++;
					}
				}
				str = str.substr(nZeros, str.length() - nZeros);
			}

			ASSERT_STREQ(bv.strip().toString().c_str(), str.c_str())<< "Strip test failed";
		}
	}
}

TEST_F(BitVectorTest, StartingGuidePart1Test) {
	// Declarations and initialization
	BitVector bv1(12, 0);
	BitVector bv2(18, 1748);
	BitVector bv3("010101010101010101");

	// Display
	std::cout << "bv1 = " << bv1 << std::endl;
	std::cout << "bv2 = " << bv2 << std::endl;
	std::cout << "bv3 = " << bv3 << std::endl;

	// Dangerous initialization
	BitVector bv4(12);

	std::cout << "bv4 = " << bv4 << std::endl;

	// Initialization from negative number
	BitVector bv5(18, -1843);

	std::cout << "bv5 = " << bv5 << std::endl;

	// Creation from copy
	BitVector x(8, 0xF0);
	BitVector y(x);

	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

	// Assignment from int
	x = 0x55;

	// Assignment from BitVector
	y = x;

	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

	// Assignment from std::string
	x = "00110011"; // or x.fromString("00110011");
	std::cout << "x = " << x << std::endl;

	// unsigned char initialization from BitVector
	hvuint8_t z1(x);

	// unsigned char assignment from BitVector
	hvuint32_t z2;
	z2 = x;
	std::cout << "z1 = " << hvuint32_t(z1) << std::endl;
	std::cout << "z2 = " << z2 << std::endl;

	// std::string initialization from BitVector
	std::string str1(x);

	// std::string assignment from BitVector
	std::string str2;
	str2 = std::string(x); // or str2 = x.toString();
	std::cout << "str1 = " << str1 << std::endl;
	std::cout << "str2 = " << str2 << std::endl;

}

TEST_F(BitVectorTest, StartingGuidePart2Test) {
	// BitVector declarations
	BitVector x(8, 0), y(12, 0xFFF);
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

	x[2] = y[5];

	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

	y(3, 0) = x(7, 4);

	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

	y(11, 8) = x(3, 0).flip();
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

}

TEST_F(BitVectorTest, StartingGuidePart3Test) {
	// Declarations/instantiations
	BitVector x(8, 0xF0);
	BitVector y(8, 0x0F);

	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;

	// Concatenation
	BitVector z1(16, 0);
	z1 = x + y;

	std::cout << "z1 = " << z1 << std::endl;

	// Slices concatenation
	BitVector z2(16, 0);
	z2(9, 2) = x(6, 3) + y(4, 1);

	std::cout << "z2 = " << z2 << std::endl;

}

TEST_F(BitVectorTest, StartingGuidePart4Test) {
	// Declarations/instantiations
	BitVector a(32, 0x00000000);
	BitVector b(32, 0xFFFFFFFF);
	BitVector c(16, 0xFF00);
	BitVector d(8, 0xF0);
//	hvuint32_t x;

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;

	// Bitwise negation examples
	BitVector e(16, 0);
	e = ~c;
	b(7, 0) = ~c(11, 4);

	std::cout << "e = " << e << std::endl;
	std::cout << "b = " << b << std::endl;

	// Bitwise AND, OR and XOR examples
	d = a(12, 5) | c(10, 3);
	b(23, 20) &= a(15, 12) | (d(5, 2) ^ b(12, 9));

	std::cout << "d = " << d << std::endl;
	std::cout << "b = " << b << std::endl;

	// Declarations/instantiations
	BitVector f(32, 0xF0F0F0F0);
	BitVector g(16, 0xFF00);
	hvuint16_t h(0x0FF0);
	hvint16_t i(-1); // 0xFFFF
	BitVector j(32, 0x55555555);
	hvuint8_t k(160); // 0xA0

	// A lot of operations in one single line
	f(31, 16) |= ((g(14, 0) + f[6]) & ((h | (k + j(20, 5))) ^ i)).flip();
	std::cout << "f = " << f << std::endl;
}

TEST_F(BitVectorTest, StartingGuidePart5Test) {
	// Declarations/instantiations
	BitVector f(8, 0x00);
	BitVector g(8, 0x0F);
	hvuint8_t h(0);
	hvuint8_t i(12);

	// Some boolean tests
	bool test1 = (f && g);
	bool test2 = (!f && g);
	bool test3 = (f || g);
	bool test4 = (f || !g);
	bool test5 = (h || g);
	bool test6 = (g && !i);
	bool test7 = (g(7, 4) && i);

	std::cout << "test1 = " << (test1 ? "true" : "false") << std::endl;
	std::cout << "test2 = " << (test2 ? "true" : "false") << std::endl;
	std::cout << "test3 = " << (test3 ? "true" : "false") << std::endl;
	std::cout << "test4 = " << (test4 ? "true" : "false") << std::endl;
	std::cout << "test5 = " << (test5 ? "true" : "false") << std::endl;
	std::cout << "test6 = " << (test6 ? "true" : "false") << std::endl;
	std::cout << "test7 = " << (test7 ? "true" : "false") << std::endl;

}

TEST_F(BitVectorTest, CCIValueTest) {
	for (auto size = 1u; size <= maxSize; size++) {
		BitVector bvSrc(size, 0u);
		BitVector bvDest(size, 0u);
		for (auto i = 0u; i < nTests / 100; i++) {
			bvSrc.rand();
			cci_value x(bvSrc);
			bvDest = x.get<BitVector>();
			ASSERT_TRUE(bvSrc == bvDest)<< "Error in cci_value packing/unpacking";
		}
	}
}

