/*  This file is part of the Vc library. {{{
Copyright © 2016-2017 Matthias Kretz <kretz@kde.org>

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

#ifndef VC_SIMD_X86_STORAGE_H_
#define VC_SIMD_X86_STORAGE_H_

#ifndef VC_SIMD_STORAGE_H_
#error "Do not include detail/x86/storage.h directly. Include detail/storage.h instead."
#endif
#include "intrinsics.h"

Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace x86
{
#ifdef Vc_HAVE_AVX
// lo/hi/extract128 {{{
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL lo128(Storage<T, N> x)
{
    return lo128(x.intrin());
}
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL hi128(Storage<T, N> x)
{
    return hi128(x.intrin());
}

template <int offset, typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL extract128(Storage<T, N> x)
{
    return extract128<offset>(x.intrin());
}

//}}}
#endif  // Vc_HAVE_AVX

#ifdef Vc_HAVE_AVX512F
// lo/hi256 {{{
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 32 / sizeof(T)> Vc_VDECL lo256(Storage<T, N> x)
{
    return lo256(x.intrin());
}
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 32 / sizeof(T)> Vc_VDECL hi256(Storage<T, N> x)
{
    return hi256(x.intrin());
}
//}}}
#endif  // Vc_HAVE_AVX512F

// extract_part {{{1
// identity {{{2
template <class T>
Vc_INTRINSIC const Storage<T, 16 / sizeof(T)>& Vc_VDECL
    extract_part_impl(std::true_type, size_constant<0>, size_constant<1>,
                      const Storage<T, 16 / sizeof(T)>& x)
{
    return x;
}

// AVX to SSE splits {{{2
#ifdef Vc_HAVE_AVX
template <class T>
Vc_INTRINSIC Storage<T, 16 / sizeof(T)> Vc_VDECL extract_part_impl(
    std::true_type, size_constant<0>, size_constant<2>, Storage<T, 32 / sizeof(T)> x)
{
    return lo128(x);
}
template <class T>
Vc_INTRINSIC Storage<T, 16 / sizeof(T)> Vc_VDECL extract_part_impl(
    std::true_type, size_constant<1>, size_constant<2>, Storage<T, 32 / sizeof(T)> x)
{
    return hi128(x);
}
#endif  // Vc_HAVE_AVX

// AVX512 to AVX or SSE splits {{{2
#ifdef Vc_HAVE_AVX512F
template <class T, size_t Index>
Vc_INTRINSIC Storage<T, 16 / sizeof(T)> Vc_VDECL extract_part_impl(
    std::true_type, size_constant<Index>, size_constant<4>, Storage<T, 64 / sizeof(T)> x)
{
    return extract128<Index>(x);
}

template <class T>
Vc_INTRINSIC Storage<T, 32 / sizeof(T)> Vc_VDECL extract_part_impl(
    std::true_type, size_constant<0>, size_constant<2>, Storage<T, 64 / sizeof(T)> x)
{
    return lo256(x);
}
template <class T>
Vc_INTRINSIC Storage<T, 32 / sizeof(T)> Vc_VDECL extract_part_impl(
    std::true_type, size_constant<1>, size_constant<2>, Storage<T, 64 / sizeof(T)> x)
{
    return hi256(x);
}
#endif  // Vc_HAVE_AVX512F

// partial SSE (shifts) {{{2
template <class T, size_t Index, size_t Total, size_t N>
Vc_INTRINSIC Storage<T, 16 / sizeof(T)> Vc_VDECL extract_part_impl(std::false_type,
                                                                   size_constant<Index>,
                                                                   size_constant<Total>,
                                                                   Storage<T, N> x)
{
    constexpr int split = sizeof(x) / 16;
    constexpr int shift = (sizeof(x) / Total * Index) % 16;
    return x86::shift_right<shift>(
        extract_part_impl<T>(std::true_type(), size_constant<Index * split / Total>(),
                             size_constant<split>(), x));
}

// public interface {{{2
template <class T> constexpr T constexpr_max(T a, T b) { return a > b ? a : b; }

template <size_t Index, size_t Total, class T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, constexpr_max(16 / sizeof(T), N / Total)> Vc_VDECL
extract_part(Storage<T, N> x)
{
    constexpr size_t NewN = N / Total;
    static_assert(Total > 1, "Total must be greater than 1");
    static_assert(NewN * Total == N, "N must be divisible by Total");
    return extract_part_impl<T>(
        std::integral_constant<bool, (sizeof(T) * NewN >= 16)>(),  // dispatch on whether
                                                                   // the result is a
                                                                   // partial SSE register
                                                                   // or larger
        std::integral_constant<size_t, Index>(), std::integral_constant<size_t, Total>(),
        x);
}

// }}}1

// mask conversions {{{
template <size_t SizeofTo, size_t NTo, size_t SizeofFrom, size_t NFrom, class To,
          bool IsAvx512 = (sizeof(To) < sizeof(__m128))>
struct convert_mask_impl;

#ifdef Vc_HAVE_SSE2
template <size_t Sizeof, size_t N, class To>
struct convert_mask_impl<Sizeof, N, Sizeof, N, To, false> {
    template <class T> Vc_INTRINSIC To operator()(T x) { return intrin_cast<To>(x); }
};

#ifdef Vc_HAVE_AVX512F
template <size_t N, class To> struct convert_mask_impl<1, N, 1, N, To, true> {
    Vc_INTRINSIC To operator()(To x) { return x; }
};

template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 1, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi8_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi8_mask(x); }
#else   // Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi8_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi8_mask(zeroExtend64(x)); }
#endif  // Vc_HAVE_AVX512VL
#else  // Vc_HAVE_AVX512BW
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movemask_epi8(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movemask_epi8(x); }
#endif  // Vc_HAVE_AVX512BW
};
template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 2, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi16_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi16_mask(x); }
#else   // Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi16_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi16_mask(zeroExtend64(x)); }
#endif  // Vc_HAVE_AVX512VL
#else  // Vc_HAVE_AVX512BW
    Vc_INTRINSIC To operator()(__m128i x) { return x86::movemask_epi16(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return x86::movemask_epi16(x); }
#endif  // Vc_HAVE_AVX512BW
};
template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 4, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi32_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi32_mask(x); }
#else   // Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi32_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi32_mask(zeroExtend64(x)); }
#endif  // Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128 x) { return operator()(_mm_castps_si128(x)); }
    Vc_INTRINSIC To operator()(__m256 x) { return operator()(_mm256_castps_si256(x)); }
#else  // Vc_HAVE_AVX512BW
    Vc_INTRINSIC To operator()(__m128 x) { return _mm_movemask_ps(x); }
    Vc_INTRINSIC To operator()(__m256 x) { return _mm256_movemask_ps(x); }
    Vc_INTRINSIC To operator()(__m128i x) { return operator()(_mm_castsi128_ps(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return operator()(_mm256_castsi256_ps(x)); }
#endif  // Vc_HAVE_AVX512BW
};
template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 8, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi64_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi64_mask(x); }
#else   // Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi64_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi64_mask(zeroExtend64(x)); }
#endif  // Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128d x) { return operator()(_mm_castpd_si128(x)); }
    Vc_INTRINSIC To operator()(__m256d x) { return operator()(_mm256_castpd_si256(x)); }
#else  // Vc_HAVE_AVX512BW
    Vc_INTRINSIC To operator()(__m128d x) { return _mm_movemask_pd(x); }
    Vc_INTRINSIC To operator()(__m256d x) { return _mm256_movemask_pd(x); }
    Vc_INTRINSIC To operator()(__m128i x) { return operator()(_mm_castsi128_pd(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return operator()(_mm256_castsi256_pd(x)); }
#endif  // Vc_HAVE_AVX512BW
};
#endif  // Vc_HAVE_AVX512F

#define Vc_CONVERT_MASK_IMPL_BEGIN(SizeofTo_, NTo_, SizeofFrom_, NFrom_)                 \
    template <class To>                                                                  \
    struct convert_mask_impl<SizeofTo_, NTo_, SizeofFrom_, NFrom_, To, false> {          \
        template <class T> Vc_INTRINSIC To operator()(T x)                               \
        {
#define Vc_CONVERT_MASK_IMPL_END }}

Vc_CONVERT_MASK_IMPL_BEGIN(8, 2, 4, 4)
    return intrin_cast<To>(
        _mm_unpacklo_ps(intrin_cast<__m128>(x), intrin_cast<__m128>(x)));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(8, 2, 2, 8)
    auto y = _mm_unpacklo_epi16(x, x);
    return intrin_cast<To>(_mm_unpacklo_epi32(y, y));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(8, 2, 1, 16)
    auto y = _mm_unpacklo_epi8(x, x);
    y = _mm_unpacklo_epi16(y, y);
    return intrin_cast<To>(_mm_unpacklo_epi32(y, y));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(4, 4, 8, 2)
    auto y = intrin_cast<__m128i>(x);
    return intrin_cast<To>(_mm_packs_epi32(y, y));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(4, 4, 2, 8)
    return intrin_cast<To>(_mm_unpacklo_epi16(x, x));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(4, 4, 1, 16)
    auto y = _mm_unpacklo_epi8(x, x);
    return _mm_unpacklo_epi16(y, y);
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(2, 8, 8, 2)
    auto y = _mm_packs_epi32(intrin_cast<__m128i>(x), intrin_cast<__m128i>(x));
    return _mm_packs_epi32(y, y);
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(2, 8, 4, 4)
    return _mm_packs_epi32(intrin_cast<__m128i>(x), intrin_cast<__m128i>(x));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(2, 8, 1, 16)
    return _mm_unpacklo_epi8(x, x);
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(1, 16, 8, 2)
    auto y = _mm_packs_epi32(intrin_cast<__m128i>(x), intrin_cast<__m128i>(x));
    y = _mm_packs_epi32(y, y);
    return _mm_packs_epi16(y, y);
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(1, 16, 4, 4)
    auto y = _mm_packs_epi32(intrin_cast<__m128i>(x), intrin_cast<__m128i>(x));
    return _mm_packs_epi16(y, y);
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(1, 16, 2, 8)
    return _mm_packs_epi16(x, x);
Vc_CONVERT_MASK_IMPL_END;

#ifdef Vc_HAVE_AVX
Vc_CONVERT_MASK_IMPL_BEGIN(8, 4, 4, 4)
    return intrin_cast<To>(
        concat(_mm_unpacklo_ps(intrin_cast<__m128>(x), intrin_cast<__m128>(x)),
               _mm_unpackhi_ps(intrin_cast<__m128>(x), intrin_cast<__m128>(x))));
Vc_CONVERT_MASK_IMPL_END;

Vc_CONVERT_MASK_IMPL_BEGIN(4, 4, 8, 4)
    auto y = intrin_cast<__m256i>(x);
    return intrin_cast<To>(_mm_packs_epi32(lo128(y), hi128(y)));
Vc_CONVERT_MASK_IMPL_END;

#ifdef Vc_HAVE_AVX2
#endif  // Vc_HAVE_AVX2
#endif  // Vc_HAVE_AVX
#endif  // Vc_HAVE_SSE2

// }}}

}  // namespace x86

// to_<intrin> {{{
template <class T, size_t N> constexpr Vc_INTRINSIC __m128 to_m128(Storage<T, N> a)
{
    static_assert(N <= 16 / sizeof(T));
    return a.template intrin<__m128>();
}
template <class T, size_t N> constexpr Vc_INTRINSIC __m128d to_m128d(Storage<T, N> a)
{
    static_assert(N <= 16 / sizeof(T));
    return a.template intrin<__m128d>();
}
template <class T, size_t N> constexpr Vc_INTRINSIC __m128i to_m128i(Storage<T, N> a)
{
    static_assert(N <= 16 / sizeof(T));
    return a.template intrin<__m128i>();
}

template <class T, size_t N> constexpr Vc_INTRINSIC __m256 to_m256(Storage<T, N> a)
{
    static_assert(N <= 32 / sizeof(T) && N > 16 / sizeof(T));
    return a.template intrin<__m256>();
}
template <class T, size_t N> constexpr Vc_INTRINSIC __m256d to_m256d(Storage<T, N> a)
{
    static_assert(N <= 32 / sizeof(T) && N > 16 / sizeof(T));
    return a.template intrin<__m256d>();
}
template <class T, size_t N> constexpr Vc_INTRINSIC __m256i to_m256i(Storage<T, N> a)
{
    static_assert(N <= 32 / sizeof(T) && N > 16 / sizeof(T));
    return a.template intrin<__m256i>();
}

template <class T, size_t N> constexpr Vc_INTRINSIC __m512 to_m512(Storage<T, N> a)
{
    static_assert(N <= 64 / sizeof(T) && N > 32 / sizeof(T));
    return a.template intrin<__m512>();
}
template <class T, size_t N> constexpr Vc_INTRINSIC __m512d to_m512d(Storage<T, N> a)
{
    static_assert(N <= 64 / sizeof(T) && N > 32 / sizeof(T));
    return a.template intrin<__m512d>();
}
template <class T, size_t N> constexpr Vc_INTRINSIC __m512i to_m512i(Storage<T, N> a)
{
    static_assert(N <= 64 / sizeof(T) && N > 32 / sizeof(T));
    return a.template intrin<__m512i>();
}

// }}}
// to_storage {{{
template <class T> class to_storage
{
    T d;

public:
    constexpr to_storage(T x) : d(x) {}
    template <class U, size_t N> constexpr operator Storage<U, N>() const
    {
        static_assert(sizeof(builtin_type_t<U, N>) == sizeof(T));
        return {reinterpret_cast<builtin_type_t<U, N>>(d)};
    }
};

#ifdef Vc_HAVE_AVX512_ABI
template <size_t N> class to_storage<std::bitset<N>>
{
    std::bitset<N> d;

public:
    constexpr to_storage(std::bitset<N> x) : d(x) {}
    template <class U> constexpr operator Storage<U, N>() const
    {
        return reinterpret_cast<builtin_type_t<U, N>>(
            detail::x86::convert_mask<sizeof(U), sizeof(builtin_type_t<U, N>)>(d));
    }
};

#define Vc_TO_STORAGE(type_)                                                             \
    template <> class to_storage<type_>                                                  \
    {                                                                                    \
        type_ d;                                                                         \
                                                                                         \
    public:                                                                              \
        constexpr to_storage(type_ x) : d(x) {}                                          \
        template <class U, size_t N> constexpr operator Storage<U, N>() const            \
        {                                                                                \
            return reinterpret_cast<builtin_type_t<U, N>>(                               \
                detail::x86::convert_mask<sizeof(U), sizeof(builtin_type_t<U, N>)>(d));  \
        }                                                                                \
    }
Vc_TO_STORAGE(__mmask8);
Vc_TO_STORAGE(__mmask16);
Vc_TO_STORAGE(__mmask32);
Vc_TO_STORAGE(__mmask64);
#undef Vc_TO_STORAGE
#endif  // Vc_HAVE_AVX512_ABI

// }}}
// to_storage_unsafe {{{
template <class T> class to_storage_unsafe
{
    T d;
public:
    constexpr to_storage_unsafe(T x) : d(x) {}
    template <class U, size_t N> constexpr operator Storage<U, N>() const
    {
        static_assert(sizeof(builtin_type_t<U, N>) <= sizeof(T));
        return {reinterpret_cast<builtin_type_t<U, N>>(d)};
    }
};
// }}}
// concat {{{
// These functions are part of the Storage interface => same namespace.
// These functions are only available when AVX or higher is enabled. In the future there
// may be more cases (e.g. half SSE -> full SSE or even MMX -> SSE).
#if 0//def Vc_HAVE_SSE2
template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 4 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 2 / sizeof(T)> a, Storage<T, 2 / sizeof(T)> b)
{
    static_assert(std::is_integral_v<T>);
    return to_storage_unsafe(_mm_unpacklo_epi16(to_m128i(a), to_m128i(b)));
}

template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 8 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 4 / sizeof(T)> a, Storage<T, 4 / sizeof(T)> b)
{
    static_assert(std::is_integral_v<T>);
    return to_storage_unsafe(_mm_unpacklo_epi32(to_m128i(a), to_m128i(b)));
}

Vc_INTRINSIC Vc_CONST Storage<float, 4> Vc_VDECL concat(Storage<float, 2> a,
                                                        Storage<float, 2> b)
{
    return to_storage(_mm_unpacklo_pd(to_m128d(a), to_m128d(b)));
}

template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 8 / sizeof(T)> a, Storage<T, 8 / sizeof(T)> b)
{
    static_assert(std::is_integral_v<T>);
    return to_storage(_mm_unpacklo_epi64(to_m128d(a), to_m128d(b)));
}
#endif  // Vc_HAVE_SSE2

#ifdef Vc_HAVE_AVX
template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 32 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 16 / sizeof(T)> a, Storage<T, 16 / sizeof(T)> b)
{
    return x86::concat(a.intrin(), b.intrin());
}
#endif  // Vc_HAVE_AVX

#ifdef Vc_HAVE_AVX512F
template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 64 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 32 / sizeof(T)> a, Storage<T, 32 / sizeof(T)> b)
{
    return x86::concat(a.intrin(), b.intrin());
}
#endif  // Vc_HAVE_AVX512F

template <class T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 4 * N> Vc_VDECL concat(Storage<T, N> a, Storage<T, N> b,
                                                        Storage<T, N> c, Storage<T, N> d)
{
    return concat(concat(a, b), concat(c, d));
}

template <class T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 8 * N> Vc_VDECL concat(Storage<T, N> a, Storage<T, N> b,
                                                        Storage<T, N> c, Storage<T, N> d,
                                                        Storage<T, N> e, Storage<T, N> f,
                                                        Storage<T, N> g, Storage<T, N> h)
{
    return concat(concat(concat(a, b), concat(c, d)), concat(concat(e, f), concat(g, h)));
}

//}}}
template <class To, class T, size_t Size> To convert_mask(Storage<T, Size> x)
{
    return convert_mask_impl<sizeof(typename To::value_type), To::size(), sizeof(T), Size,
                             typename To::VectorType>()(x);
}

}  // namespace detail
Vc_VERSIONED_NAMESPACE_END

#endif  // VC_SIMD_X86_STORAGE_H_
