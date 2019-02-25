/**
 * @file bitvector.h
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Jun, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Class for efficient and intuitive bit vector representation and manipulation
 */

#ifndef HV_BITVECTOR_H
#define HV_BITVECTOR_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cci_configuration>
#include "datatypes.h"
#include "hvutils.h"

/**
 * BitVector base type for binary number representation
 *
 * Default: hvuint32_t
 */
#define HV_BV_BASE_TYPE hvuint32_t

/**
 * BitVector number representation array size for static array
 *
 * Default: 2
 */
#define HV_BV_MAX_STATIC_ARRAY_SIZE 2

/**
 * BitVector max representable number of bytes
 *
 * Default: 8 bytes
 */
#define HV_BV_MAX_STATIC_BYTEWIDTH (HV_BV_MAX_STATIC_ARRAY_SIZE * sizeof(HV_BV_BASE_TYPE))

/**
 * BitVector max representable number of bytes
 *
 * Default: 8 bytes
 */
#define HV_BV_MAX_STATIC_BITWIDTH (HV_BV_MAX_STATIC_BYTEWIDTH * 8)

/**
 * BitVector type for sizes and index representation
 * The given type must be able to handle unsigned numbers of at least
 * HV_BV_MAX_BITWIDTH bits (128 by default)
 *
 * Default: hvuint8_t (can handle up to 256 bits)
 */
#define HV_BV_SIZE_TYPE hvuint16_t

/**
 * BitVector's array size resolution for a w-bit BitVector
 */
#define HV_BV_ARRAY_SIZE(w) ( (w % (BITWIDTH_OF(HV_BV_BASE_TYPE))) ? w / (BITWIDTH_OF(HV_BV_BASE_TYPE)) + 1 : w / (BITWIDTH_OF(HV_BV_BASE_TYPE)) )

/**
 * BitVector's mask resolution
 *
 * Creates a mask which applies to the last occupied cell of a given w-bit BitVector
 */
#define HV_BV_MASK_LAST_CELL(w) ( (w % (BITWIDTH_OF(HV_BV_BASE_TYPE))) ? HV_LSB_MASK_GEN(HV_BV_BASE_TYPE,(w % (BITWIDTH_OF(HV_BV_BASE_TYPE)))) : ~HV_BV_BASE_TYPE(0) )

/**
 * BitVector's index coordinate resolution
 *
 * Determines what index of data array corresponds to absolute index i
 */
#define HV_BV_ABS_POS_TO_ARRAY_INDEX(i) ( i / (BITWIDTH_OF(HV_BV_BASE_TYPE)) )

/**
 * BitVector's index coordinate resolution
 *
 * Determines what position of data cell is concerned by absolute index i
 */
#define HV_BV_ABS_POS_TO_REL_POS(i) (i % (BITWIDTH_OF(HV_BV_BASE_TYPE)) )

/**
 * This variable must be defined to manipulate binary string ("0100100...110101") MSB first
 *
 * If not defined, all strings are manipulated LSB first
 */
#ifndef HV_BV_STR_LSB_FIRST
#define HV_BV_STR_MSB_FIRST
#endif

namespace hv {
namespace common {

/**
 * Class for generic binary vector representation and manipulation
 */
class BitVector {
public:
	typedef HV_BV_SIZE_TYPE bvsize_t;
	typedef HV_BV_BASE_TYPE bvdata_t;

	//** Constructors **//

	/**
	 * Default constructor
	 * Creates a 32-bit BitVector worth 0.
	 */
	BitVector();

	/**
	 * Constructor from boolean value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const bool &value, BitVector *parentPtr =
			nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvuint8_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvuint8_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvuint16_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvuint16_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvuint32_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvuint32_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvuint64_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvuint64_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvint8_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvint8_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvint16_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvint16_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvint32_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvint32_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from hvint64_t value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const hvint64_t &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from std::string value
	 *
	 * The string must be composed of '0' and '1' characters.
	 * Index 0 of the string represent the Least Significant Bit (LSB).
	 *
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const std::string &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from BitVector value
	 * @param size Binary vector size
	 * @param value Initial value (default: 0)
	 * @param parentPtr Direct parent address (default: nullptr)
	 * @param lowIndexSelect Inferior index of sub-vector (default: 0)
	 * @param highIndexSelect Superior index of sub-vector (default: size-1)
	 */
	BitVector(const bvsize_t &size, const BitVector &value,
			BitVector *parentPtr = nullptr, const bvsize_t &lowIndexSelect = 0,
			const bvsize_t &highIndexSelect = 0);

	/**
	 * Constructor from bool
	 * @param value Assignment value
	 */
	BitVector(const bool &value);

	/**
	 * Constructor from hvuint8_t
	 * @param value Assignment value
	 */
	BitVector(const hvuint8_t &value);

	/**
	 * Constructor from hvuint16_t
	 * @param value Assignment value
	 */
	BitVector(const hvuint16_t &value);

	/**
	 * Constructor from hvuint32_t
	 * @param value Assignment value
	 */
	BitVector(const hvuint32_t &value);

	/**
	 * Constructor from hvuint64_t
	 * @param value Assignment value
	 */
	BitVector(const hvuint64_t &value);

	/**
	 * Constructor from hvint8_t
	 * @param value Assignment value
	 */
	BitVector(const hvint8_t &value);

	/**
	 * Constructor from hvint16_t
	 * @param value Assignment value
	 */
	BitVector(const hvint16_t &value);

	/**
	 * Constructor from hvint32_t
	 * @param value Assignment value
	 */
	BitVector(const hvint32_t &value);

	/**
	 * Constructor from hvint64_t
	 * @param value Assignment value
	 */
	BitVector(const hvint64_t &value);

	/**
	 * Constructor from std::string
	 * @param value Assignment value
	 */
	BitVector(const std::string &value);

	/**
	 * Copy constructor
	 *
	 * Be careful : everything is copied, including parent!
	 * To copy only value, use the multi-arguments constructor
	 * @param src Copy source
	 */
	BitVector(const BitVector &src);

	//** Destructor **//
	/**
	 * BitVector destructor
	 */
	virtual ~BitVector();

	//** Accessors **//
	/**
	 * Get BitVector size in bits
	 * @return Size in bits
	 */
	bvsize_t getSize() const;

	/**
	 * Get number of array cells containing
	 * represented object
	 * @return Array size
	 */
	bvsize_t getArraySize() const;

	/**
	 * Get mask to be applied to last cell
	 * representing data
	 * @return Last cell mask
	 */
	bvdata_t getmaskLastCell() const;

	/**
	 * Get parent address
	 * @return Parent addres
	 */
	BitVector* getParentAddress() const;

	/**
	 * Get low index of represented (sub-)BitVector
	 * @return Low index
	 */
	bvsize_t getLowIndex() const;

	/**
	 * Get high index of represented (sub-)BitVector
	 * @return High index
	 */
	bvsize_t getHighIndex() const;

	/**
	 * Get data address
	 * @return Data address
	 */
	bvdata_t* getDataAddress();

	//** Casts **//
	/**
	 * Cast to bool
	 */
	operator bool() const;

	/**
	 * Cast to hvuint8_t
	 */
	operator hvuint8_t() const;

	/**
	 * Cast to hvuint16_t
	 */
	operator hvuint16_t() const;

	/**
	 * Cast to hvuint32_t
	 */
	operator hvuint32_t() const;

	/**
	 * Cast to hvuint64_t
	 */
	operator hvuint64_t() const;

	/**
	 * Cast to hvint8_t
	 */
	operator hvint8_t() const;

	/**
	 * Cast to hvint16_t
	 */
	operator hvint16_t() const;

	/**
	 * Cast to hvint32_t
	 */
	operator hvint32_t() const;

	/**
	 * Cast to hvint64_t
	 */
	operator hvint64_t() const;

	/**
	 * Cast to std::string
	 */
	operator std::string() const;

	//** Operators overloading **//

	// Assignment
	/**
	 * Assignment from bool
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const bool &src);

	/**
	 * Assignment from hvuint8_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvuint8_t &src);

	/**
	 * Assignment from hvuint16_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvuint16_t &src);

	/**
	 * Assignment from hvuint32_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvuint32_t &src);

	/**
	 * Assignment from hvuint64_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvuint64_t &src);

	/**
	 * Assignment from hvint8_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvint8_t &src);

	/**
	 * Assignment from hvint16_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvint16_t &src);

	/**
	 * Assignment from hvint32_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvint32_t &src);

	/**
	 * Assignment from hvint64_t
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const hvint64_t &src);

	/**
	 * Assignment from std::string
	 *
	 * The string must be composed of '0' and '1' characters.
	 * Index 0 of the string represent the Least Significant Bit (LSB).
	 *
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const std::string &src);

	/**
	 * Assignment from BitVector
	 * @param src Source for assignment
	 * @return Reference to this
	 */
	BitVector& operator =(const BitVector &src);

	// Shifting
	/**
	 * Left shift
	 * @param nShift Left shift depth
	 * @return Result of left shifting
	 */
	BitVector operator <<(const hvuint32_t &nShift) const;

	/**
	 * Left shift
	 * @param nShift Left shift depth
	 * @return Result of left shifting
	 */
	BitVector operator <<(const hvint32_t &nShift) const;

	/**
	 * Right shift
	 * @param nShift Right shift depth
	 * @return Result of right shifting
	 */
	BitVector operator >>(const hvuint32_t &nShift) const;

	/**
	 * Right shift
	 * @param nShift Right shift depth
	 * @return Result of right shifting
	 */
	BitVector operator >>(const hvint32_t &nShift) const;

	/**
	 * Self left shift
	 * @param nShift Self left shift depth
	 * @return Reference to this
	 */
	BitVector& operator <<=(const hvuint32_t &nShift);

	/**
	 * Self left shift
	 * @param nShift Self left shift depth
	 * @return Reference to this
	 */
	BitVector& operator <<=(const hvint32_t &nShift);

	/**
	 * Self right shift
	 * @param nShift Self right shift depth
	 * @return Reference to this
	 */
	BitVector& operator >>=(const hvuint32_t &nShift);

	/**
	 * Self right shift
	 * @param nShift Self right shift depth
	 * @return Reference to this
	 */
	BitVector& operator >>=(const hvint32_t &nShift);

	// Boolean tests
	/**
	 * Boolean negation
	 * @return True if BitVector == 0, false else
	 */
	bool operator !() const;

	/**
	 * Equal comparison
	 * @param op2 Right-hand operand
	 * @return True if equal, false else
	 */
	bool operator ==(const BitVector &op2) const;

	/**
	 * Different comparison
	 * @param op2 Right-hand operand
	 * @return True if different, false else
	 */
	bool operator !=(const BitVector &op2) const;

	/**
	 * Logical AND
	 * @param op2 Right-hand operand
	 * @return True if both operands are non-zero, false otherwise
	 */
	bool operator &&(const BitVector &op2) const;

	/**
	 * Logical OR
	 * @param op2 Right-hand operand
	 * @return True if at least one operand is non-zero, false otherwise
	 */
	bool operator ||(const BitVector &op2) const;

	/* Note: no operators <=, <, >=, >
	 * If they are defined in the future they should be defined by
	 * using Hamming weight ordering since BitVector is nor signed
	 * neither unsigned
	 */

	// Binary operators
	/**
	 * Binary negation
	 * @return bit-negated BitVector
	 */
	BitVector operator ~() const;

	/**
	 * Binary AND
	 * @param op2 Right-hand operand
	 * @return Binary AND result
	 */
	BitVector operator &(const BitVector &op2) const;

	/**
	 * Binary OR
	 * @param op2 Right-hand operand
	 * @return Binary OR result
	 */
	BitVector operator |(const BitVector &op2) const;

	/**
	 * Binary XOR
	 * @param op2 Right-hand operand
	 * @return Binary XOR result
	 */
	BitVector operator ^(const BitVector &op2) const;

	/**
	 * Binary AND and assignment
	 * @param op2 Right-hand operand
	 * @return Reference to this
	 */
	BitVector& operator &=(const BitVector &op2);

	/**
	 * Binary AND and assignment
	 * @param op2 Right-hand operand
	 * @return Reference to this
	 */
	BitVector& operator |=(const BitVector &op2);

	/**
	 * Binary AND and assignment
	 * @param op2 Right-hand operand
	 * @return Reference to this
	 */
	BitVector& operator ^=(const BitVector &op2);

	// Concatenation
	/**
	 * Concatenation operator
	 *
	 * Concatenates BitVectors. Left-hand operand is set to MSB side,
	 * right-hand operand to LSB side.
	 * @param op2 Right-hand operand
	 * @return Concatenated BitVector
	 */
	BitVector operator +(const BitVector &op2) const;

	// Vector and bit selection
	/**
	 * Vector selection
	 *
	 * If bv is a BitVector, then bv(ind1, ind2) selects the bits
	 * between indexes ind1 and ind2. the order of ind1 and ind2 is
	 * not important.
	 * @param ind1 First index (LSB, resp. MSB of selection)
	 * @param ind2 Second index (MSB, resp. LSB of selection)
	 * @return BitVector representing selected vector
	 */
	BitVector operator ()(const bvsize_t &ind1, const bvsize_t &ind2);

	/**
	 * Vector selection - const version
	 *
	 * This method returns a BitVector in read-mode only (trying to modify it
	 * won't do anything to the source). Anyway, if you are trying to modify it,
	 * the non-const version of operator () will be called.
	 * @param ind1 First index (LSB, resp. MSB of selection)
	 * @param ind2 Second index (MSB, resp. LSB of selection)
	 * @return BitVector representing selected vector's value
	 */
	BitVector operator ()(const bvsize_t &ind1, const bvsize_t &ind2) const;

	/**
	 * Bit selection
	 *
	 * This method returns a BitVector in read-mode only (trying to modify it
	 * won't do anything to the source). Anyway, if you are trying to modify it,
	 * the non-const version of operator [] will be called.
	 *
	 * Is equivalent to vector selection with ind1 == ind2
	 * @param ind Index of the bit to be selected
	 * @return BitVector representing selected bit
	 */
	BitVector operator [](const bvsize_t &ind);

	/**
	 * Bit selection - const version
	 *
	 * Is equivalent to vector selection with ind1 == ind2
	 * @param ind Index of the bit to be selected
	 * @return BitVector representing selected bit
	 */
	BitVector operator [](const bvsize_t &ind) const;

	//** Helpers **//
	// Random values
	/**
	 * Applies a random value to BitVector
	 *
	 * All bits are set whether to 0 or 1 with a 0.5 probability
	 */
	void rand();

	// String manipulation
	/**
	 * Assignment from string
	 *
	 * LSB or MSB first is defined by macro HV_BV_STR_MSB_FIRST
	 * @param src Source for assignment
	 */
	void fromString(const std::string &src);

	/**
	 * Conversion to string
	 *
	 * LSB or MSB first is defined by macro HV_BV_STR_MSB_FIRST
	 * @return String of 0s and 1s
	 */
	std::string toString() const;

	/**
	 * Output stream operator overloading
	 * @param strm Stream
	 * @param vs Binary vector object to output
	 * @return Stream
	 */
	friend std::ostream& operator <<(std::ostream &strm, const BitVector &bv);

	// Copy creation
	/**
	 * Creates a BitVector with the same size and the same value
	 * Does not copy any other member (the returned BitVector has no
	 * parent)
	 * @return BitVector of same size and same value
	 */
	BitVector copy() const;

	// Binary string manipulation
	/**
	 * Creates a flipped BitVector
	 * E.g. if current BitVector is worth 00110101,
	 * an independent BitVector of same size worth
	 * 10101100 is created.
	 *
	 * @return Flipped BitVector
	 */
	BitVector flip() const;

	/**
	 * Creates a stripped BitVector
	 * E.g if current BitVector is worth 00110101,
	 * an independent BitVector of same value with a
	 * MSB worth 1 is returned (i.e. 110101)
	 * If current BitVector is 0, then 0 is returned.
	 *
	 * @return Stripped BitVector
	 */
	BitVector strip() const;

//** BitVector resizing **//
	/**
	 * Resizes BitVector to a given size.
	 *
	 * Only works if current BitVector has no parent (this would be too risky for memory leaks)
	 * indLow and indHigh are adapted in function of new size
	 * If size gets bigger, the value is filled with zeros
	 * If size gets smaller, the value is truncated MSB side.
	 * @param newSize New BitVector size
	 */
	void resize(bvsize_t newSize);

protected:
	inline void instantiationChecks(const bvsize_t &size);

	/**
	 * Update parent with the value of current sub vector
	 */
	void updateParent();

	// Helper struct for setData(...) and getData(...)
	template<typename T, bool COMP> struct dataHandleHelper {
	};

	/**
	 * Set data from source
	 *
	 * This function is private to prevent undefined behavior.
	 * @param src Source for data modification
	 */
	template<typename T> void setData(const T &src);
	template<typename T, bool COMP> void _setData(dataHandleHelper<T, COMP>,
			const T &src);
	template<typename T> void _setData(dataHandleHelper<T, true>, const T &src);
	template<typename T> void _setData(dataHandleHelper<T, false>,
			const T &src);

	/**
	 * Get data as typename T
	 *
	 * This function is private to prevent undefined behavior.
	 * @return data as typename T
	 */
	template<typename T> T getData() const;
	template<typename T, bool COMP> T _getData(dataHandleHelper<T, COMP>) const;
	template<typename T> T _getData(dataHandleHelper<T, true>) const;
	template<typename T> T _getData(dataHandleHelper<T, false>) const;

	/**
	 * Get the number of bits of last cell in data array
	 * @return The number of bits of last cell in data array
	 */
	inline bvsize_t getLastCellSize() const;

	/**
	 * Resets data value to 0;
	 */
	void reset();

	/**
	 * Parent BitVector for sub-vectors
	 *
	 * If nullptr, current BitVector is the origin
	 */
	BitVector* parent;

	/**
	 * Data address
	 */
	bvdata_t* data;

	/**
	 * Static array for smaller data (default: <= 64 bit)
	 */
	bvdata_t staticData[HV_BV_MAX_STATIC_ARRAY_SIZE];

	/**
	 * Size: Size in bits of current vector/sub-vector
	 * arraySize: Size of total array to be considered for current vector/sub-vector
	 */
	bvsize_t binSize, arraySize;

	/**
	 * For sub-vectors, lowIndex and highIndex represent the bound indexes of their direct parent they represent
	 */
	bvsize_t lowIndex, highIndex;

	/**
	 * Mask for last array cell
	 */
	bvdata_t maskLastCell;
};

// Template methods definitions
template<typename T> void BitVector::setData(const T &src) {
	this->_setData(dataHandleHelper<T, sizeof(T) <= sizeof(bvdata_t)>(), src);
}

template<typename T, bool COMP> void BitVector::_setData(
		dataHandleHelper<T, COMP>, const T &src) {
	HV_LOG_ERROR("This function should not have been generated");
	HV_EXIT_FAILURE();
}

template<typename T> void BitVector::_setData(dataHandleHelper<T, true>,
		const T &src) {
	data[0] = static_cast<bvdata_t>(src);
	data[0] &= HV_LSB_MASK_GEN(bvdata_t, BITWIDTH_OF(T));

	for (bvsize_t i = 1; i < arraySize; i++) {
		data[i] = 0;
	}
}

template<typename T> void BitVector::_setData(dataHandleHelper<T, false>,
		const T &src) {
	HV_ASSERT(!(sizeof(T) % sizeof(bvsize_t)),
			"Size of source has to be a multiple of bvdata_t")
	const bvsize_t HOW_BIGGER = sizeof(T) / sizeof(bvdata_t);
	T srcTmp(src);
	bvsize_t cpt;
	for (cpt = 0; cpt < HOW_BIGGER; cpt++) {
		data[cpt] = static_cast<bvdata_t>(srcTmp);
		srcTmp >>= BITWIDTH_OF(bvdata_t);
	}
	for (bvsize_t i = HOW_BIGGER; i < arraySize; i++) {
		data[i] = 0;
	}
}

template<typename T> T BitVector::getData() const {
	return this->_getData(dataHandleHelper<T, sizeof(T) <= sizeof(bvdata_t)>());
}

template<typename T, bool COMP> T BitVector::_getData(
		dataHandleHelper<T, COMP>) const {
	HV_LOG_ERROR("This function should not have been generated");
	HV_EXIT_FAILURE();
	return T(0);
}

template<typename T> T BitVector::_getData(dataHandleHelper<T, true>) const {
	T ret(data[0]);
	if (arraySize == static_cast<bvsize_t>(1u)) {
		ret &= static_cast<T>(maskLastCell);
	}
	return static_cast<T>(ret);
}

template<typename T> T BitVector::_getData(dataHandleHelper<T, false>) const {
	HV_ASSERT(!(sizeof(T) % sizeof(bvsize_t)),
			"Size of source has to be a multiple of bvsize_t")
	T ret(0u);
	const bvsize_t HOW_BIGGER = sizeof(T) / sizeof(bvdata_t);
	for (bvsize_t i = 0u; (i < arraySize) && (i < HOW_BIGGER); i++) {
		T tmp(i == (arraySize - 1u) ? data[i] & maskLastCell : data[i]);
		tmp <<= BITWIDTH_OF(bvdata_t) * i;
		ret |= tmp;
	}
	return ret;
}

// Interoperability

// OPERATOR ==
template<typename T> inline bool bv_operator_isequal1(const BitVector &a,
		const T &b) {
	return (a == BitVector(BITWIDTH_OF(T), b));
}

template<typename T> inline bool bv_operator_isequal2(const T &a,
		const BitVector &b) {
	return (b == a);
}

#define BV_OP_ISEQUAL(T) inline bool operator == (const BitVector &a, const T &b) {return bv_operator_isequal1(a, b);} \
inline bool operator == (const T &a, const BitVector &b) {return bv_operator_isequal2(a, b);}
BV_OP_ISEQUAL(bool)
BV_OP_ISEQUAL(hvuint8_t)
BV_OP_ISEQUAL(hvuint16_t)
BV_OP_ISEQUAL(hvuint32_t)
BV_OP_ISEQUAL(hvuint64_t)
BV_OP_ISEQUAL(hvint8_t)
BV_OP_ISEQUAL(hvint16_t)
BV_OP_ISEQUAL(hvint32_t)
BV_OP_ISEQUAL(hvint64_t)
BV_OP_ISEQUAL(std::string)

// OPERATOR !=
template<typename T> inline bool bv_operator_isdifferent1(const BitVector &a,
		const T &b) {
	return (a != BitVector(b));
}

template<typename T> inline bool bv_operator_isdifferent2(const T &a,
		const BitVector &b) {
	return (b != a);
}

#define BV_OP_ISDIFFERENT(T) inline bool operator != (const BitVector &a, const T &b) {return bv_operator_isdifferent1(a, b);} \
inline bool operator != (const T &a, const BitVector &b) {return bv_operator_isdifferent2(a, b);}
BV_OP_ISDIFFERENT(bool)
BV_OP_ISDIFFERENT(hvuint8_t)
BV_OP_ISDIFFERENT(hvuint16_t)
BV_OP_ISDIFFERENT(hvuint32_t)
BV_OP_ISDIFFERENT(hvuint64_t)
BV_OP_ISDIFFERENT(hvint8_t)
BV_OP_ISDIFFERENT(hvint16_t)
BV_OP_ISDIFFERENT(hvint32_t)
BV_OP_ISDIFFERENT(hvint64_t)
BV_OP_ISDIFFERENT(std::string)

// OPERATOR &&
template<typename T> inline bool bv_operator_booland1(const BitVector &a,
		const T &b) {
	return (a && BitVector(b));
}

template<typename T> inline bool bv_operator_booland2(const T &a,
		const BitVector &b) {
	return (b && a);
}

#define BV_OP_BOOLAND(T) inline bool operator && (const BitVector &a, const T &b) {return bv_operator_booland1(a, b);} \
inline bool operator && (const T &a, const BitVector &b) {return bv_operator_booland2(a, b);}
BV_OP_BOOLAND(bool)
BV_OP_BOOLAND(hvuint8_t)
BV_OP_BOOLAND(hvuint16_t)
BV_OP_BOOLAND(hvuint32_t)
BV_OP_BOOLAND(hvuint64_t)
BV_OP_BOOLAND(hvint8_t)
BV_OP_BOOLAND(hvint16_t)
BV_OP_BOOLAND(hvint32_t)
BV_OP_BOOLAND(hvint64_t)
BV_OP_BOOLAND(std::string)

// OPERATOR ||
template<typename T> inline bool bv_operator_boolor1(const BitVector &a,
		const T &b) {
	return (a || BitVector(b));
}

template<typename T> inline bool bv_operator_boolor2(const T &a,
		const BitVector &b) {
	return (b || a);
}

#define BV_OP_BOOLOR(T) inline bool operator || (const BitVector &a, const T &b) {return bv_operator_boolor1(a, b);} \
inline bool operator || (const T &a, const BitVector &b) {return bv_operator_boolor2(a, b);}
BV_OP_BOOLOR(bool)
BV_OP_BOOLOR(hvuint8_t)
BV_OP_BOOLOR(hvuint16_t)
BV_OP_BOOLOR(hvuint32_t)
BV_OP_BOOLOR(hvuint64_t)
BV_OP_BOOLOR(hvint8_t)
BV_OP_BOOLOR(hvint16_t)
BV_OP_BOOLOR(hvint32_t)
BV_OP_BOOLOR(hvint64_t)
BV_OP_BOOLOR(std::string)

// OPERATOR &
template<typename T> inline BitVector bv_operator_bitwiseand1(
		const BitVector &a, const T &b) {
	return (a & BitVector(HV_MIN(a.getSize(), BITWIDTH_OF(T)), b));
}

template<typename T> inline BitVector bv_operator_bitwiseand2(const T &a,
		const BitVector &b) {
	return (b & a);
}

#define BV_OP_BITWISEAND(T) inline BitVector operator & (const BitVector &a, const T &b) {return bv_operator_bitwiseand1(a, b);} \
inline BitVector operator & (const T &a, const BitVector &b) {return bv_operator_bitwiseand2(a, b);}
BV_OP_BITWISEAND(bool)
BV_OP_BITWISEAND(hvuint8_t)
BV_OP_BITWISEAND(hvuint16_t)
BV_OP_BITWISEAND(hvuint32_t)
BV_OP_BITWISEAND(hvuint64_t)
BV_OP_BITWISEAND(hvint8_t)
BV_OP_BITWISEAND(hvint16_t)
BV_OP_BITWISEAND(hvint32_t)
BV_OP_BITWISEAND(hvint64_t)
BV_OP_BITWISEAND(std::string)

// OPERATOR |
template<typename T> inline BitVector bv_operator_bitwiseor1(const BitVector &a,
		const T &b) {
	return (a | BitVector(b));
}

template<typename T> inline BitVector bv_operator_bitwiseor2(const T &a,
		const BitVector &b) {
	return (b | a);
}

#define BV_OP_BITWISEOR(T) inline BitVector operator | (const BitVector &a, const T &b) {return bv_operator_bitwiseor1(a, b);} \
inline BitVector operator | (const T &a, const BitVector &b) {return bv_operator_bitwiseor2(a, b);}
BV_OP_BITWISEOR(bool)
BV_OP_BITWISEOR(hvuint8_t)
BV_OP_BITWISEOR(hvuint16_t)
BV_OP_BITWISEOR(hvuint32_t)
BV_OP_BITWISEOR(hvuint64_t)
BV_OP_BITWISEOR(hvint8_t)
BV_OP_BITWISEOR(hvint16_t)
BV_OP_BITWISEOR(hvint32_t)
BV_OP_BITWISEOR(hvint64_t)
BV_OP_BITWISEOR(std::string)

// OPERATOR ^
template<typename T> inline BitVector bv_operator_bitwisexor1(
		const BitVector &a, const T &b) {
	return (a ^ BitVector(b));
}

template<typename T> inline BitVector bv_operator_bitwisexor2(const T &a,
		const BitVector &b) {
	return (b ^ a);
}

#define BV_OP_BITWISEXOR(T) inline BitVector operator ^ (const BitVector &a, const T &b) {return bv_operator_bitwisexor1(a, b);} \
inline BitVector operator ^ (const T &a, const BitVector &b) {return bv_operator_bitwisexor2(a, b);}
BV_OP_BITWISEXOR(bool)
BV_OP_BITWISEXOR(hvuint8_t)
BV_OP_BITWISEXOR(hvuint16_t)
BV_OP_BITWISEXOR(hvuint32_t)
BV_OP_BITWISEXOR(hvuint64_t)
BV_OP_BITWISEXOR(hvint8_t)
BV_OP_BITWISEXOR(hvint16_t)
BV_OP_BITWISEXOR(hvint32_t)
BV_OP_BITWISEXOR(hvint64_t)
BV_OP_BITWISEXOR(std::string)

// Operator &=
// Only one, the other one is achieved by implicit conversion
template<typename T> inline T& bv_operator_bitwiseandequal(T &a,
		const BitVector &b) {
	return (a &= T(b));
}
#define BV_OP_BITWISEANDEQUAL(T) inline T& operator &= (T &a, const BitVector &b) {return bv_operator_bitwiseandequal(a, b);}
BV_OP_BITWISEANDEQUAL(bool)
BV_OP_BITWISEANDEQUAL(hvuint8_t)
BV_OP_BITWISEANDEQUAL(hvuint16_t)
BV_OP_BITWISEANDEQUAL(hvuint32_t)
BV_OP_BITWISEANDEQUAL(hvuint64_t)
BV_OP_BITWISEANDEQUAL(hvint8_t)
BV_OP_BITWISEANDEQUAL(hvint16_t)
BV_OP_BITWISEANDEQUAL(hvint32_t)
BV_OP_BITWISEANDEQUAL(hvint64_t)
// Specialization for std::string
inline std::string& operator &=(std::string &a, const BitVector &b) {
	BitVector tmp(a);
	tmp &= b;
	a = tmp.toString();
	return a;
}

// Operator |=
// Only one, the other one is achieved by implicit conversion
template<typename T> inline T& bv_operator_bitwiseorequal(T &a,
		const BitVector &b) {
	return (a |= T(b));
}
#define BV_OP_BITWISEOREQUAL(T) inline T& operator |= (T &a, const BitVector &b) {return bv_operator_bitwiseorequal(a, b);}
BV_OP_BITWISEOREQUAL(bool)
BV_OP_BITWISEOREQUAL(hvuint8_t)
BV_OP_BITWISEOREQUAL(hvuint16_t)
BV_OP_BITWISEOREQUAL(hvuint32_t)
BV_OP_BITWISEOREQUAL(hvuint64_t)
BV_OP_BITWISEOREQUAL(hvint8_t)
BV_OP_BITWISEOREQUAL(hvint16_t)
BV_OP_BITWISEOREQUAL(hvint32_t)
BV_OP_BITWISEOREQUAL(hvint64_t)
// Specialization for std::string
inline std::string& operator |=(std::string &a, const BitVector &b) {
	BitVector tmp(a);
	tmp |= b;
	a = tmp.toString();
	return a;
}

// Operator ^=
// Only one, the other one is achieved by implicit conversion
template<typename T> inline T& bv_operator_bitwisexorequal(T &a,
		const BitVector &b) {
	return (a ^= T(b));
}
#define BV_OP_BITWISEXOREQUAL(T) inline T& operator ^= (T &a, const BitVector &b) {return bv_operator_bitwisexorequal(a, b);}
BV_OP_BITWISEXOREQUAL(bool)
BV_OP_BITWISEXOREQUAL(hvuint8_t)
BV_OP_BITWISEXOREQUAL(hvuint16_t)
BV_OP_BITWISEXOREQUAL(hvuint32_t)
BV_OP_BITWISEXOREQUAL(hvuint64_t)
BV_OP_BITWISEXOREQUAL(hvint8_t)
BV_OP_BITWISEXOREQUAL(hvint16_t)
BV_OP_BITWISEXOREQUAL(hvint32_t)
BV_OP_BITWISEXOREQUAL(hvint64_t)
// Specialization for std::string
inline std::string& operator ^=(std::string &a, const BitVector &b) {
	BitVector tmp(a);
	tmp ^= b;
	a = tmp.toString();
	return a;
}

// Operator +
template<typename T> inline BitVector bv_operator_concat1(const BitVector &a,
		const T &b) {
	return (a + BitVector(b));
}

template<typename T> inline BitVector bv_operator_concat2(const T& a,
		const BitVector &b) {
	return (BitVector(a) + b);
}

#define BV_OP_PLUS(T) inline BitVector operator +(const BitVector &a, const T &b) { return bv_operator_concat1(a, b); } \
inline BitVector operator +(const T &a, const BitVector &b) { return bv_operator_concat2(a, b); }
BV_OP_PLUS(bool)
BV_OP_PLUS(hvuint8_t)
BV_OP_PLUS(hvuint16_t)
BV_OP_PLUS(hvuint32_t)
BV_OP_PLUS(hvuint64_t)
BV_OP_PLUS(hvint8_t)
BV_OP_PLUS(hvint16_t)
BV_OP_PLUS(hvint32_t)
BV_OP_PLUS(hvint64_t)
BV_OP_PLUS(std::string)

} // namespace common
} // namespace hv

namespace cci {
// Implementation of cci_value converter from/to BitVector
template<>
struct cci_value_converter<::hv::common::BitVector> {
	typedef ::hv::common::BitVector type;
	static bool pack(cci_value::reference dst, type const & src) {
		cci_value_map_ref mref(dst.set_map());
		std::size_t nValues = ((src.getSize() - 1u) / 64u) + 1u;
		mref.push_entry("size", src.getSize());
		mref.push_entry("value_0", static_cast<uint64_t>(src));
		for (std::size_t i = 1u; i < nValues; i++) {
			mref.push_entry("value_" + std::to_string(i),
					static_cast<uint64_t>(src
							>> (static_cast<uint32_t>(i) * 64u)));
		}
		return true;
	}

	static bool unpack(type & dst, cci_value::const_reference src) {
		if (!src.is_map())
			return false;
		cci_value::const_map_reference m = src.get_map();
		std::size_t bvSize;
		if (m.has_entry("size") && m.at("size").try_get(bvSize)) {
			std::size_t nValues = ((bvSize - 1u) / 64u) + 1u;
			uint64_t ulongTmp;
			if (m.has_entry("value_0") && m.at("value_0").try_get(ulongTmp)) {
				::hv::common::BitVector ret(bvSize, ulongTmp);
				for (std::size_t i = 1u; i < nValues; i++) {
					std::string valStr("value_" + std::to_string(i));
					if (m.has_entry(valStr) && m.at(valStr).try_get(ulongTmp)) {
						::hv::common::BitVector bvTmp(bvSize, ulongTmp);
						ret |= (bvTmp << (static_cast<uint32_t>(i) * 64u));
					} else {
						return false;
					}
				}
				dst.resize(ret.getSize());
				dst = ret;
				return true;
			}
			return false;
		}
		return false;
	}
};
} // namespace cci

#endif // HV_BITVECTOR_H

