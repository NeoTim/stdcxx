/***************************************************************************
 *
 * This is an internal header file used to implement the C++ Standard
 * Library. It should never be #included directly by a program.
 *
 * $Id$
 *
 ***************************************************************************
 *
 * Licensed to the Apache Software  Foundation (ASF) under one or more
 * contributor  license agreements.  See  the NOTICE  file distributed
 * with  this  work  for  additional information  regarding  copyright
 * ownership.   The ASF  licenses this  file to  you under  the Apache
 * License, Version  2.0 (the  "License"); you may  not use  this file
 * except in  compliance with the License.   You may obtain  a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the  License is distributed on an  "AS IS" BASIS,
 * WITHOUT  WARRANTIES OR CONDITIONS  OF ANY  KIND, either  express or
 * implied.   See  the License  for  the  specific language  governing
 * permissions and limitations under the License.
 *
 * Copyright 2008 Rogue Wave Software, Inc.
 *
 **************************************************************************/

#ifndef _RWSTD_RW_META_SIGN_H_INCLUDED
#define _RWSTD_RW_META_SIGN_H_INCLUDED

#include <rw/_defs.h>
#include <rw/_meta_other.h>
#include <rw/_meta_rel.h>
#include <rw/_meta_cv.h>
#include <rw/_static_assert.h>

_RWSTD_NAMESPACE (__rw) {

/**
 * Provides typedefs mapping non-boolean integral types to signed
 * and unsigned integral types of the same base type.
 */
template <class _TypeT>
struct __rw_sign_helper
{
    typedef void _C_Sint;
    typedef void _C_Uint;
};

template <>
struct __rw_sign_helper<char>
{
    typedef   signed char _C_Sint;
    typedef unsigned char _C_Uint;
};

template <>
struct __rw_sign_helper<wchar_t>
{
    typedef _RWSTD_SWCHAR_INT_T _C_Sint;
    typedef _RWSTD_UWCHAR_INT_T _C_Uint;
};

template <>
struct __rw_sign_helper<signed char>
{
    typedef   signed char _C_Sint;
    typedef unsigned char _C_Uint;
};

template <>
struct __rw_sign_helper<unsigned char>
{
    typedef   signed char _C_Sint;
    typedef unsigned char _C_Uint;
};

template <>
struct __rw_sign_helper<signed short>
{
    typedef   signed short _C_Sint;
    typedef unsigned short _C_Uint;
};

template <>
struct __rw_sign_helper<unsigned short>
{
    typedef   signed short _C_Sint;
    typedef unsigned short _C_Uint;
};

template <>
struct __rw_sign_helper<signed int>
{
    typedef   signed int _C_Sint;
    typedef unsigned int _C_Uint;
};

template <>
struct __rw_sign_helper<unsigned int>
{
    typedef   signed int _C_Sint;
    typedef unsigned int _C_Uint;
};

template <>
struct __rw_sign_helper<signed long>
{
    typedef   signed long _C_Sint;
    typedef unsigned long _C_Uint;
};

template <>
struct __rw_sign_helper<unsigned long>
{
    typedef   signed long _C_Sint;
    typedef unsigned long _C_Uint;
};


#ifndef _RWSTD_NO_LONG_LONG

template <>
struct __rw_sign_helper<signed long long>
{
    typedef   signed long long _C_Sint;
    typedef unsigned long long _C_Uint;
};

template <>
struct __rw_sign_helper<unsigned long long>
{
    typedef   signed long long _C_Sint;
    typedef unsigned long long _C_Uint;
};

#endif // !_RWSTD_NO_LONG_LONG


/**
 * Class template provides typedefs mapping enumeration types to integral
 * types of the same size.
 */
template <_RWSTD_SIZE_T _Size>
struct __rw_enum_helper
{
    typedef void _C_Sint;
    typedef void _C_Uint;
};

template <>
struct __rw_enum_helper<_RWSTD_CHAR_SIZE>
{
    typedef   signed char _C_Sint;
    typedef unsigned char _C_Uint;
};

template <>
struct __rw_enum_helper<_RWSTD_SHRT_SIZE>
{
    typedef   signed short _C_Sint;
    typedef unsigned short _C_Uint;
};

template <>
struct __rw_enum_helper<_RWSTD_INT_SIZE>
{
    typedef   signed int _C_Sint;
    typedef unsigned int _C_Uint;
};

#if (_RWSTD_INT_SIZE != _RWSTD_LONG_SIZE)

template <>
struct __rw_enum_helper<_RWSTD_LONG_SIZE>
{
    typedef   signed long _C_Sint;
    typedef unsigned long _C_Uint;
};

#endif // (_RWSTD_INT_SIZE != _RWSTD_LONG_SIZE)

#ifndef _RWSTD_NO_LONG_LONG
#  if (_RWSTD_LONG_SIZE != _RWSTD_LLONG_SIZE)

template <>
struct __rw_enum_helper<sizeof (long long)> //_RWSTD_LLONG_SIZE>
{
    typedef   signed long long _C_Sint;
    typedef unsigned long long _C_Uint;
};

#  endif // _RWSTD_LONG_SIZE != _RWSTD_LLONG_SIZE
#endif // !_RWSTD_NO_LONG_LONG

/**
 * If _TypeT names a (possibly cv-qualified) signed integral type then the
 * member typedef type shall name the type _TypeT. Otherwise, if _TypeT
 * names a (possibly cv-qualified) unsigned integral type, then type shall
 * name the corresponding signed integral type with the same cv-qualifiers
 * as _TypeT. Otherwise, _TypeT shall name the signed integral type with
 * the smallest rank for which sizeof(_TypeT) == sizeof(_C_type), with the
 * same cv-qualifiers as _TypeT.
 *
 * note requires _TypeT shall be a (possibly cv-qualified) integral or
 * enum type, but not a bool type.
 */
template <class _TypeT>
struct __rw_make_signed
{
private:
    //_RWSTD_STATIC_ASSERT (   __rw_is_integral<_TypeT>::value
    //                      || __rw_is_enum<_TypeT>::value);

    typedef typename __rw_remove_cv<_TypeT>::type _NoCV_TypeT;

    //_RWSTD_STATIC_ASSERT (!__rw_is_same<_NoCV_TypeT, bool>::value);

    typedef typename
    __rw_conditional<__rw_is_integral<_NoCV_TypeT>::value,
                     typename __rw_sign_helper<_NoCV_TypeT>::_C_Sint,
                     typename __rw_enum_helper< sizeof (_TypeT) >::_C_Sint
                    >::type _NoCV_TypeU;

    typedef typename
    __rw_conditional<__rw_is_const<_TypeT>::value,
                     typename __rw_add_const<_NoCV_TypeU>::type,
                     _NoCV_TypeU>::type _NoV_TypeU;

    typedef typename
    __rw_conditional<__rw_is_volatile<_TypeT>::value,
                     typename __rw_add_volatile<_NoV_TypeU>::type,
                     _NoV_TypeU>::type _TypeU;

public:
    typedef _TypeU type;
};

//#define _RWSTD_MAKE_SIGNED(T) typename _RW::__rw_make_signed<T>::type

/**
 * If _TypeT names a (possibly cv-qualified) unsigned integral type then the
 * member typedef type shall name the type _TypeT. Otherwise, if _TypeT
 * names a (possibly cv-qualified) ununsigned integral type, then type shall
 * name the corresponding unsigned integral type with the same cv-qualifiers
 * as _TypeT. Otherwise, _TypeT shall name the unsigned integral type with
 * the smallest rank for which sizeof(_TypeT) == sizeof(_C_type), with the
 * same cv-qualifiers as _TypeT.
 *
 * note requires _TypeT shall be a (possibly cv-qualified) integral or
 * enum type, but not a bool type.
 */
template <class _TypeT>
struct __rw_make_unsigned
{
private:
    //_RWSTD_STATIC_ASSERT (   __rw_is_integral<_TypeT>::value
    //                      || __rw_is_enum<_TypeT>::value);

    typedef typename __rw_remove_cv<_TypeT>::type _NoCV_TypeT;

    //_RWSTD_STATIC_ASSERT (!__rw_is_same<_NoCV_TypeT, bool>::value);

    typedef typename
    __rw_conditional<__rw_is_integral<_NoCV_TypeT>::value,
                     typename __rw_sign_helper<_NoCV_TypeT>::_C_Uint,
                     typename __rw_enum_helper< sizeof (_TypeT) >::_C_Uint
                    >::type _NoCV_TypeU;

    typedef typename
    __rw_conditional<__rw_is_const<_TypeT>::value,
                     typename __rw_add_const<_NoCV_TypeU>::type,
                     _NoCV_TypeU>::type _NoV_TypeU;

    typedef typename
    __rw_conditional<__rw_is_volatile<_TypeT>::value,
                     typename __rw_add_volatile<_NoV_TypeU>::type,
                     _NoV_TypeU>::type _TypeU;

public:
    typedef _TypeU type;
};

//#define _RWSTD_MAKE_UNSIGNED(T) typename _RW::__rw_make_unsigned<T>::type

} // namespace __rw


#endif   // _RWSTD_RW_META_SIGN_H_INCLUDED

