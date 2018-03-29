/*  This file is part of the Vc library. {{{
Copyright © 2018 Matthias Kretz <kretz@kde.org>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

#ifndef VC_DETAIL_X86_TYPES_H_
#define VC_DETAIL_X86_TYPES_H_

#include "../macros.h"
#include "../detail.h"

#include <x86intrin.h>
#include <climits>

namespace Vc_VERSIONED_NAMESPACE
{
namespace detail
{

// bool_storage_member_type{{{1
#ifdef Vc_HAVE_AVX512F
template <> struct bool_storage_member_type< 2> { using type = __mmask8 ; };
template <> struct bool_storage_member_type< 4> { using type = __mmask8 ; };
template <> struct bool_storage_member_type< 8> { using type = __mmask8 ; };
template <> struct bool_storage_member_type<16> { using type = __mmask16; };
template <> struct bool_storage_member_type<32> { using type = __mmask32; };
template <> struct bool_storage_member_type<64> { using type = __mmask64; };
#endif  // Vc_HAVE_AVX512F

// builtin_type{{{1
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
#ifdef Vc_GCC
template <class T, size_t Bytes>
struct builtin_type<
    T, Bytes,
    detail::void_t<std::enable_if_t<detail::conjunction_v<
        detail::is_equal_to<Bytes % sizeof(T), 0>, detail::is_vectorizable<T>>>>> {
    using type[[gnu::vector_size(Bytes)]] = T;
};
#else   // Vc_GCC
template <> struct builtin_type<         char     ,  1> { typedef          char      type [[gnu::vector_size( 1)]]; };
template <> struct builtin_type<unsigned char     ,  1> { typedef unsigned char      type [[gnu::vector_size( 1)]]; };
template <> struct builtin_type<  signed char     ,  1> { typedef   signed char      type [[gnu::vector_size( 1)]]; };

template <> struct builtin_type<         short    ,  2> { typedef          short     type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type<unsigned short    ,  2> { typedef unsigned short     type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type<         char     ,  2> { typedef          char      type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type<unsigned char     ,  2> { typedef unsigned char      type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type<  signed char     ,  2> { typedef   signed char      type [[gnu::vector_size( 2)]]; };
#if WCHAR_MAX < 0x10000
template <> struct builtin_type<         wchar_t  ,  2> { typedef          wchar_t   type [[gnu::vector_size( 2)]]; };
#endif
template <> struct builtin_type<         char16_t ,  2> { typedef          char16_t  type [[gnu::vector_size( 2)]]; };

template <> struct builtin_type<         float    ,  4> { typedef          float     type [[gnu::vector_size( 4)]]; };
#if LONG_MAX == INT_MAX
template <> struct builtin_type<         long     ,  4> { typedef          long      type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned long     ,  4> { typedef unsigned long      type [[gnu::vector_size( 4)]]; };
#endif
template <> struct builtin_type<         int      ,  4> { typedef          int       type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned int      ,  4> { typedef unsigned int       type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<         short    ,  4> { typedef          short     type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned short    ,  4> { typedef unsigned short     type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<         char     ,  4> { typedef          char      type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned char     ,  4> { typedef unsigned char      type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<  signed char     ,  4> { typedef   signed char      type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<         wchar_t  ,  4> { typedef          wchar_t   type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<         char16_t ,  4> { typedef          char16_t  type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<         char32_t ,  4> { typedef          char32_t  type [[gnu::vector_size( 4)]]; };

template <> struct builtin_type<         double   ,  8> { typedef          double    type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         float    ,  8> { typedef          float     type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         long long,  8> { typedef          long long type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned long long,  8> { typedef unsigned long long type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         long     ,  8> { typedef          long      type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned long     ,  8> { typedef unsigned long      type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         int      ,  8> { typedef          int       type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned int      ,  8> { typedef unsigned int       type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         short    ,  8> { typedef          short     type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned short    ,  8> { typedef unsigned short     type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         char     ,  8> { typedef          char      type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned char     ,  8> { typedef unsigned char      type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<  signed char     ,  8> { typedef   signed char      type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         wchar_t  ,  8> { typedef          wchar_t   type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         char16_t ,  8> { typedef          char16_t  type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<         char32_t ,  8> { typedef          char32_t  type [[gnu::vector_size( 8)]]; };

template <> struct builtin_type<         double   , 16> { typedef          double    type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         float    , 16> { typedef          float     type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         long long, 16> { typedef          long long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned long long, 16> { typedef unsigned long long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         long     , 16> { typedef          long      type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned long     , 16> { typedef unsigned long      type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         int      , 16> { typedef          int       type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned int      , 16> { typedef unsigned int       type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         short    , 16> { typedef          short     type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned short    , 16> { typedef unsigned short     type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         char     , 16> { typedef          char      type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned char     , 16> { typedef unsigned char      type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<  signed char     , 16> { typedef   signed char      type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         wchar_t  , 16> { typedef          wchar_t   type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         char16_t , 16> { typedef          char16_t  type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<         char32_t , 16> { typedef          char32_t  type [[gnu::vector_size(16)]]; };

template <> struct builtin_type<         double   , 32> { typedef          double    type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         float    , 32> { typedef          float     type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         long long, 32> { typedef          long long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned long long, 32> { typedef unsigned long long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         long     , 32> { typedef          long      type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned long     , 32> { typedef unsigned long      type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         int      , 32> { typedef          int       type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned int      , 32> { typedef unsigned int       type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         short    , 32> { typedef          short     type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned short    , 32> { typedef unsigned short     type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         char     , 32> { typedef          char      type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned char     , 32> { typedef unsigned char      type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<  signed char     , 32> { typedef   signed char      type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         wchar_t  , 32> { typedef          wchar_t   type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         char16_t , 32> { typedef          char16_t  type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<         char32_t , 32> { typedef          char32_t  type [[gnu::vector_size(32)]]; };

template <> struct builtin_type<         double   , 64> { typedef          double    type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         float    , 64> { typedef          float     type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         long long, 64> { typedef          long long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned long long, 64> { typedef unsigned long long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         long     , 64> { typedef          long      type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned long     , 64> { typedef unsigned long      type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         int      , 64> { typedef          int       type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned int      , 64> { typedef unsigned int       type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         short    , 64> { typedef          short     type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned short    , 64> { typedef unsigned short     type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         char     , 64> { typedef          char      type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned char     , 64> { typedef unsigned char      type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<  signed char     , 64> { typedef   signed char      type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         wchar_t  , 64> { typedef          wchar_t   type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         char16_t , 64> { typedef          char16_t  type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<         char32_t , 64> { typedef          char32_t  type [[gnu::vector_size(64)]]; };
#endif  // Vc_GCC
#endif  // Vc_USE_BUILTIN_VECTOR_TYPES

// intrinsic_type{{{1
// the following excludes bool via is_vectorizable
template <class T>
using void_if_integral_t = detail::void_t<std::enable_if_t<
    detail::all<std::is_integral<T>, detail::is_vectorizable<T>>::value>>;
#if defined Vc_HAVE_AVX512F
template <> struct intrinsic_type<double, 64, void> { using type = __m512d; };
template <> struct intrinsic_type< float, 64, void> { using type = __m512; };
template <typename T> struct intrinsic_type<T, 64, void_if_integral_t<T>> { using type = __m512i; };
#endif  // Vc_HAVE_AVX512F

#if defined Vc_HAVE_AVX
template <> struct intrinsic_type<double, 32, void> { using type = __m256d; };
template <> struct intrinsic_type< float, 32, void> { using type = __m256; };
template <typename T> struct intrinsic_type<T, 32, void_if_integral_t<T>> { using type = __m256i; };
#endif  // Vc_HAVE_AVX

#if defined Vc_HAVE_SSE
template <> struct intrinsic_type< float, 16, void> { using type = __m128; };
template <> struct intrinsic_type< float,  8, void> { using type = __m128; };
template <> struct intrinsic_type< float,  4, void> { using type = __m128; };
#endif  // Vc_HAVE_SSE
#if defined Vc_HAVE_SSE2
template <> struct intrinsic_type<double, 16, void> { using type = __m128d; };
template <> struct intrinsic_type<double,  8, void> { using type = __m128d; };
template <typename T> struct intrinsic_type<T, 16, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T,  8, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T,  4, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T,  2, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T,  1, void_if_integral_t<T>> { using type = __m128i; };
#endif  // Vc_HAVE_SSE2

// is_intrinsic{{{1
template <> struct is_intrinsic<__m128> : public std::true_type {};
static_assert(is_intrinsic_v<intrinsic_type_t<float, 4>>, "");
#ifdef Vc_HAVE_SSE2
template <> struct is_intrinsic<__m128d> : public std::true_type {};
template <> struct is_intrinsic<__m128i> : public std::true_type {};
static_assert(is_intrinsic_v<intrinsic_type_t<double, 2>>, "");
static_assert(is_intrinsic_v<intrinsic_type_t<int, 4>>, "");
#endif  // Vc_HAVE_SSE2
#ifdef Vc_HAVE_AVX
template <> struct is_intrinsic<__m256 > : public std::true_type {};
template <> struct is_intrinsic<__m256d> : public std::true_type {};
template <> struct is_intrinsic<__m256i> : public std::true_type {};
static_assert(is_intrinsic_v<intrinsic_type_t<float, 8>>, "");
static_assert(is_intrinsic_v<intrinsic_type_t<double, 4>>, "");
static_assert(is_intrinsic_v<intrinsic_type_t<int, 8>>, "");
#endif  // Vc_HAVE_AVX
#ifdef Vc_HAVE_AVX512F
template <> struct is_intrinsic<__m512 > : public std::true_type {};
template <> struct is_intrinsic<__m512d> : public std::true_type {};
template <> struct is_intrinsic<__m512i> : public std::true_type {};
#endif  // Vc_HAVE_AVX512F


// is_builtin_vector{{{1
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <> struct is_builtin_vector<builtin_type_t<float, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<float, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<float, 1>> : public std::true_type {};
#ifdef Vc_HAVE_SSE2
template <> struct is_builtin_vector<builtin_type_t<double, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<double, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< llong, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< llong, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ullong, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ullong, 1>> : public std::true_type {};
#if LONG_MAX == INT_MAX
template <> struct is_builtin_vector<builtin_type_t<  long, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 4>> : public std::true_type {};
#endif
template <> struct is_builtin_vector<builtin_type_t<  long, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  long, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<   int, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<   int, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<   int, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  uint, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  uint, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  uint, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar,16>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar,16>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar, 1>> : public std::true_type {};

#if WCHAR_MAX < 0x10000
template <> struct is_builtin_vector<builtin_type_t< wchar_t, 8>> : public std::true_type {};
#endif
template <> struct is_builtin_vector<builtin_type_t< wchar_t, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< wchar_t, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< wchar_t, 1>> : public std::true_type {};

template <> struct is_builtin_vector<builtin_type_t<char16_t, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 1>> : public std::true_type {};

template <> struct is_builtin_vector<builtin_type_t<char32_t, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char32_t, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char32_t, 1>> : public std::true_type {};
#endif  // Vc_HAVE_SSE2
#ifdef Vc_HAVE_AVX
template <> struct is_builtin_vector<builtin_type_t< float, 4 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<double, 2 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< llong, 2 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ullong, 2 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  long, 16 / sizeof( long) * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 16 / sizeof(ulong) * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<   int, 4 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  uint, 4 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 8 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 8 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar,16 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar,16 * 2>> : public std::true_type {};

template <> struct is_builtin_vector<builtin_type_t< wchar_t, 16 / sizeof(wchar_t) * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 8 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char32_t, 4 * 2>> : public std::true_type {};
#endif  // Vc_HAVE_AVX
#ifdef Vc_HAVE_AVX512F
template <> struct is_builtin_vector<builtin_type_t< float, 4 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<double, 2 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< llong, 2 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ullong, 2 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  long, 16 / sizeof( long) * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 16 / sizeof(ulong) * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<   int, 4 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<  uint, 4 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 8 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 8 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar,16 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar,16 * 4>> : public std::true_type {};

template <> struct is_builtin_vector<builtin_type_t< wchar_t, 16 / sizeof(wchar_t) * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 8 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char32_t, 4 * 4>> : public std::true_type {};
#endif  // Vc_HAVE_AVX512F
#endif  // Vc_USE_BUILTIN_VECTOR_TYPES

// (sse|avx|avx512)_(simd|mask)_member_type{{{1
template <class T> using sse_simd_member_type = Storage<T, 16 / sizeof(T)>;
template <class T> using sse_mask_member_type = Storage<T, 16 / sizeof(T)>;

template <class T> using avx_simd_member_type = Storage<T, 32 / sizeof(T)>;
template <class T> using avx_mask_member_type = Storage<T, 32 / sizeof(T)>;

template <class T> using avx512_simd_member_type = Storage<T, 64 / sizeof(T)>;
template <class T> using avx512_mask_member_type = Storage<bool, 64 / sizeof(T)>;
template <size_t N> using avx512_mask_member_type_n = Storage<bool, N>;

//}}}1

// x_ aliases {{{
#ifdef Vc_HAVE_SSE
using x_f32 = Storage< float,  4>;
#ifdef Vc_HAVE_SSE2
using x_f64 = Storage<double,  2>;
using x_i08 = Storage< schar, 16>;
using x_u08 = Storage< uchar, 16>;
using x_i16 = Storage< short,  8>;
using x_u16 = Storage<ushort,  8>;
using x_i32 = Storage<   int,  4>;
using x_u32 = Storage<  uint,  4>;
using x_i64 = Storage< llong,  2>;
using x_u64 = Storage<ullong,  2>;
using x_long = Storage<long,   16 / sizeof(long)>;
using x_ulong = Storage<ulong, 16 / sizeof(ulong)>;
using x_long_equiv = Storage<equal_int_type_t<long>, 16 / sizeof(long)>;
using x_ulong_equiv = Storage<equal_int_type_t<ulong>, 16 / sizeof(ulong)>;
using x_chr = Storage<    char, 16>;
using x_c16 = Storage<char16_t,  8>;
using x_c32 = Storage<char32_t,  4>;
using x_wch = Storage< wchar_t, 16 / sizeof(wchar_t)>;
#endif  // Vc_HAVE_SSE2
#endif  // Vc_HAVE_SSE

//}}}
// y_ aliases {{{
using y_f32 = Storage< float,  8>;
using y_f64 = Storage<double,  4>;
using y_i08 = Storage< schar, 32>;
using y_u08 = Storage< uchar, 32>;
using y_i16 = Storage< short, 16>;
using y_u16 = Storage<ushort, 16>;
using y_i32 = Storage<   int,  8>;
using y_u32 = Storage<  uint,  8>;
using y_i64 = Storage< llong,  4>;
using y_u64 = Storage<ullong,  4>;
using y_long = Storage<long,   32 / sizeof(long)>;
using y_ulong = Storage<ulong, 32 / sizeof(ulong)>;
using y_long_equiv = Storage<equal_int_type_t<long>, 32 / sizeof(long)>;
using y_ulong_equiv = Storage<equal_int_type_t<ulong>, 32 / sizeof(ulong)>;
using y_chr = Storage<    char, 32>;
using y_c16 = Storage<char16_t, 16>;
using y_c32 = Storage<char32_t,  8>;
using y_wch = Storage< wchar_t, 32 / sizeof(wchar_t)>;

//}}}
// z_ aliases {{{
using z_f32 = Storage< float, 16>;
using z_f64 = Storage<double,  8>;
using z_i32 = Storage<   int, 16>;
using z_u32 = Storage<  uint, 16>;
using z_i64 = Storage< llong,  8>;
using z_u64 = Storage<ullong,  8>;
using z_long = Storage<long,   64 / sizeof(long)>;
using z_ulong = Storage<ulong, 64 / sizeof(ulong)>;
using z_i08 = Storage< schar, 64>;
using z_u08 = Storage< uchar, 64>;
using z_i16 = Storage< short, 32>;
using z_u16 = Storage<ushort, 32>;
using z_long_equiv = Storage<equal_int_type_t<long>, 64 / sizeof(long)>;
using z_ulong_equiv = Storage<equal_int_type_t<ulong>, 64 / sizeof(ulong)>;
using z_chr = Storage<    char, 64>;
using z_c16 = Storage<char16_t, 32>;
using z_c32 = Storage<char32_t, 16>;
using z_wch = Storage< wchar_t, 64 / sizeof(wchar_t)>;

//}}}

}  // namespace detail
}  // namespace Vc

#endif  // VC_DETAIL_X86_TYPES_H_

// vim: foldmethod=marker
