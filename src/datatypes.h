/**
 * @file datatypes.h
 * @author Benjamin Barrois <benjamin.barrois@hiventive.com>
 * @date Feb, 2018
 * @copyright Copyright (C) 2018, Hiventive.
 *
 * @brief Hiventive datatypes definitions and macros
 */

#ifndef HV_DATATYPES_H
#define HV_DATATYPES_H

#include <cstdlib>
#include <cstdint>
#include <iostream>


namespace hv {
namespace common {

// Hiventive types definitions
typedef uint8_t hvuint8_t;
typedef uint16_t hvuint16_t;
typedef uint32_t hvuint32_t;
typedef uint64_t hvuint64_t;

typedef int8_t hvint8_t;
typedef int16_t hvint16_t;
typedef int32_t hvint32_t;
typedef int64_t hvint64_t;

typedef hvuint64_t hvaddr_t;

typedef hvuint64_t hvcbID_t;

typedef enum {
	RW,
	RO,
	WO,
	NA
} hvrwmode_t;

} /* namespace common */
} /* namespace hv */

#endif /* HV_DATATYPES_H */
