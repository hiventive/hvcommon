/*
 * @file cplusplus.h
 * @author Guillaume Delbergue <guillaume.delbergue@hiventive.com>
 * @date March, 2019
 * @copyright Copyright (C) 2019, Hiventive.
 *
 * @brief Common C++ macros
 */

#if defined(_MSC_VER) && _MSC_VER <= 1700
  #define HV_CPLUSPLUS_MEMBER_FUNCTION_DEFAULT {}
  #define HV_CPLUSPLUS_MEMBER_FUNCTION_DELETE
#else
  #define HV_CPLUSPLUS_MEMBER_FUNCTION_DEFAULT = default
  #define HV_CPLUSPLUS_MEMBER_FUNCTION_DELETE = delete
#endif
