#ifndef VC_FWDDECL_H_
#define VC_FWDDECL_H_ 
#include <cstddef>
namespace Vc
{
inline namespace v2
{
}
}
#define Vc_VERSIONED_NAMESPACE Vc::v2
#define Vc_VERSIONED_NAMESPACE_BEGIN namespace Vc { inline namespace v2 {
#define Vc_VERSIONED_NAMESPACE_END }}
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
struct scalar_abi;
template <int N> struct fixed_abi;
template <int Bytes> struct sse_abi;
template <int Bytes> struct avx_abi;
template <int Bytes> struct avx512_abi;
template <int Bytes> struct neon_abi;
}
namespace simd_abi
{
template <int N> using fixed_size = Vc::detail::fixed_abi<N>;
using scalar = Vc::detail::scalar_abi;
#ifdef __INTEL_COMPILER
#define Vc_DEPRECATED_ 
#else
#define Vc_DEPRECATED_ [[deprecated("Capitalize the first letter of non-std ABI tags")]]
#endif
using sse Vc_DEPRECATED_ = Vc::detail::sse_abi<16>;
using avx Vc_DEPRECATED_ = Vc::detail::avx_abi<32>;
using avx512 Vc_DEPRECATED_ = Vc::detail::avx512_abi<64>;
using neon Vc_DEPRECATED_ = Vc::detail::neon_abi<16>;
#undef Vc_DEPRECATED_
using Sse = Vc::detail::sse_abi<16>;
using Avx = Vc::detail::avx_abi<32>;
using Avx512 = Vc::detail::avx512_abi<64>;
using Neon128 = Vc::detail::neon_abi<16>;
using Neon64 = Vc::detail::neon_abi<8>;
using Neon = Neon128;
}
template <class T> struct is_simd;
template <class T> struct is_simd_mask;
template <class T, class Abi> class simd;
template <class T, class Abi> class simd_mask;
template <class T, std::size_t N, class... > struct abi_for_size;
template <class T, class Abi> struct simd_size;
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_MACROS_H_
#define VC_SIMD_MACROS_H_ 
#ifndef VC_VERSION_H_
#define VC_VERSION_H_ 
#define Vc_VERSION_STRING "1.71.0-dev"
#define Vc_VERSION_CHECK(major,minor,patch) ((major << 16) | (minor << 8) | (patch << 1))
#define Vc_VERSION_NUMBER (Vc_VERSION_CHECK(1, 71, 0) + 1)
#ifdef Vc_OVERRIDE_VERSION_NUMBER
#undef Vc_VERSION_NUMBER
#define Vc_VERSION_NUMBER Vc_OVERRIDE_VERSION_NUMBER
#endif
#define Vc_LIBRARY_ABI_VERSION 6
#define Vc_IS_VERSION_2 (Vc_VERSION_NUMBER < Vc_VERSION_CHECK(2, 70, 0))
#define Vc_IS_VERSION_1 0
#endif
#define Vc_PRAGMA_(x_) _Pragma(#x_)
#ifdef __GNUC__
#define Vc_CPP_WARNING(msg) Vc_PRAGMA_(GCC warning msg)
#else
#define Vc_CPP_WARNING(msg) Vc_PRAGMA_(message "warning: " msg)
#endif
#if defined(_MSC_VER)
#define Vc_MSVC_WARNING_(...) __pragma(warning(__VA_ARGS__))
#else
#define Vc_MSVC_WARNING_(...) 
#endif
#if defined VC_IMPL || defined Vc_IMPL
Vc_CPP_WARNING("The Vc_IMPL macro was removed for Vc 2.0. "
               "Instructions are restricted solely via compiler flags. "
               "The vector ABI is chosen via code. "
               "The default vector ABI is currently not selectable.")
#endif
#ifndef Vc_NO_OPTIMIZATION_WARNINGS
#if defined Vc_GCC || defined Vc_CLANG
#define Vc_NOT_OPTIMIZED [[deprecated("\x8\x8\x8\x8\x8\x8\x8\x8\x8\x8\x8\x8not optimized yet, if you care about speed please help out! [-DVc_NO_OPTIMIZATION_WARNINGS]")]]
#else
#define Vc_NOT_OPTIMIZED [[deprecated("NOT DEPRECATED, just a note: this function is not optimized yet, if you care about speed please help out! [-DVc_NO_OPTIMIZATION_WARNINGS]")]]
#endif
#else
#define Vc_NOT_OPTIMIZED 
#endif
#ifdef DOXYGEN
#define Vc_ICC __INTEL_COMPILER_BUILD_DATE
#undef Vc_ICC
#define Vc_CLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#undef Vc_CLANG
#define Vc_APPLECLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#undef Vc_APPLECLANG
#define Vc_GCC (__GNUC__ * 0x10000 + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
#define Vc_MSVC _MSC_FULL_VER
#undef Vc_MSVC
#endif
#ifdef __INTEL_COMPILER
#define Vc_ICC __INTEL_COMPILER_BUILD_DATE
#elif defined __clang__ && defined __apple_build_version__
#define Vc_APPLECLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#elif defined(__clang__)
#define Vc_CLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#elif defined(__GNUC__)
#define Vc_GCC (__GNUC__ * 0x10000 + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
#define Vc_MSVC _MSC_FULL_VER
#else
#define Vc_UNSUPPORTED_COMPILER 1
#endif
#if !(defined Vc_ICC || (defined Vc_MSVC && Vc_MSVC >= 191025017) || __cplusplus >= 201402L)
#error "Vc requires support for C++14."
#endif
#define Vc_CXX14 1
#if __cplusplus > 201700L
#define Vc_CXX17 1
#endif
#if !(defined __cpp_inline_variables && __cpp_inline_variables >= 201606)
# error "Need support for C++17 inline variables"
#endif
#ifdef Vc_MSVC
#define Vc_ALIGNED_TYPEDEF(n_,type_,new_type_) \
    typedef __declspec(align(n_)) type_ new_type_
#elif __GNUC__
#define Vc_ALIGNED_TYPEDEF(n_,type_,new_type_) \
    typedef type_ new_type_[[gnu::aligned(n_)]]
#else
#define Vc_ALIGNED_TYPEDEF(n_,type_,new_type_) \
    using new_type_ alignas(sizeof(n_)) = type_
#endif
#ifdef WIN32
#define NOMINMAX 1
#if defined min
#undef min
#endif
#if defined max
#undef max
#endif
#endif
#ifdef __aarch64__
#define Vc_IS_AARCH64 1
#endif
#ifdef __ARM_NEON
#define Vc_HAVE_NEON 
#define Vc_HAVE_NEON_ABI 1
#define Vc_HAVE_FULL_NEON_ABI 1
#endif
#if defined __x86_64__ || defined __amd64__ || defined __amd64 || defined __x86_64 || \
    defined _M_AMD64
#define Vc_IS_AMD64 1
#endif
#ifdef __MMX__
#define Vc_HAVE_MMX 1
#endif
#if defined __SSE__ || defined Vc_IS_AMD64 || (defined _M_IX86_FP && _M_IX86_FP >= 1)
#define Vc_HAVE_SSE 1
#endif
#if defined __SSE2__ || defined Vc_IS_AMD64 || (defined _M_IX86_FP && _M_IX86_FP >= 2)
#define Vc_HAVE_SSE2 1
#endif
#ifdef __SSE3__
#define Vc_HAVE_SSE3 1
#endif
#ifdef __SSSE3__
#define Vc_HAVE_SSSE3 1
#endif
#ifdef __SSE4_1__
#define Vc_HAVE_SSE4_1 1
#endif
#ifdef __SSE4_2__
#define Vc_HAVE_SSE4_2 1
#endif
#ifdef __XOP__
#define Vc_HAVE_XOP 1
#endif
#ifdef __AVX__
#define Vc_HAVE_AVX 1
#endif
#ifdef __AVX2__
#define Vc_HAVE_AVX2 1
#define Vc_HAVE_BMI1 1
#define Vc_HAVE_BMI2 1
#define Vc_HAVE_LZCNT 1
#if !defined Vc_ICC && !defined Vc_MSVC
#ifndef __BMI__
#error "expected AVX2 to imply the availability of BMI1"
#endif
#ifndef __BMI2__
#error "expected AVX2 to imply the availability of BMI2"
#endif
#ifndef __LZCNT__
#error "expected AVX2 to imply the availability of LZCNT"
#endif
#endif
#endif
#ifdef __SSE4A__
#define Vc_HAVE_SSE4A 1
#endif
#ifdef __FMA__
#define Vc_HAVE_FMA 1
#endif
#ifdef __FMA4__
#define Vc_HAVE_FMA4 1
#endif
#ifdef __F16C__
#define Vc_HAVE_F16C 1
#endif
#if defined __POPCNT__ || \
    (defined Vc_ICC && (defined Vc_HAVE_SSE4_2 || defined Vc_HAVE_SSE4A))
#define Vc_HAVE_POPCNT 1
#endif
#ifdef __AVX512F__
#define Vc_HAVE_AVX512F 1
#endif
#ifdef __AVX512DQ__
#define Vc_HAVE_AVX512DQ 1
#endif
#ifdef __AVX512VL__
#define Vc_HAVE_AVX512VL 1
#endif
#ifdef __AVX512BW__
#define Vc_HAVE_AVX512BW 1
#endif
#if defined Vc_HAVE_SSE
#define Vc_HAVE_SSE_ABI 1
#ifdef Vc_HAVE_SSE2
#define Vc_HAVE_FULL_SSE_ABI 1
#endif
#endif
#if defined Vc_HAVE_AVX
#define Vc_HAVE_AVX_ABI 1
#if defined Vc_HAVE_AVX2
#define Vc_HAVE_FULL_AVX_ABI 1
#endif
#endif
#ifdef Vc_HAVE_AVX512F
#define Vc_HAVE_AVX512_ABI 1
#ifdef Vc_HAVE_AVX512BW
#define Vc_HAVE_FULL_AVX512_ABI 1
#endif
#endif
#if defined Vc_ICC
#warning "ICC crashes in so many places of the code that it needs a half-time position just to keep workarounds working. Any native SIMD ABIs are therefore disabled until a maintainer steps up."
#undef Vc_HAVE_SSE_ABI
#undef Vc_HAVE_AVX_ABI
#undef Vc_HAVE_AVX512_ABI
#undef Vc_HAVE_FULL_SSE_ABI
#undef Vc_HAVE_FULL_AVX_ABI
#undef Vc_HAVE_FULL_AVX512_ABI
#endif
#if defined Vc_GCC && Vc_GCC >= 0x60000
#define Vc_TEMPLATES_DROP_ATTRIBUTES 1
#endif
#if defined(__GNUC__) && !defined(Vc_NO_INLINE_ASM)
#define Vc_GNU_ASM 1
#endif
#if defined(Vc_GCC) || defined(Vc_CLANG) || defined Vc_APPLECLANG || defined Vc_ICC
#define Vc_USE_BUILTIN_VECTOR_TYPES 1
#endif
#ifdef Vc_MSVC
#define Vc_CDECL __cdecl
#define Vc_VDECL __vectorcall
#else
#define Vc_CDECL 
#define Vc_VDECL 
#endif
#define Vc_CONCAT_IMPL(a_,b_,c_) a_ ##b_ ##c_
#define Vc_CONCAT(a_,b_,c_) Vc_CONCAT_IMPL(a_, b_, c_)
#if defined Vc_CLANG || defined Vc_APPLECLANG
#define Vc_UNREACHABLE __builtin_unreachable
#define Vc_NEVER_INLINE [[gnu::noinline]]
#define Vc_INTRINSIC_L inline
#define Vc_INTRINSIC_R __attribute__((always_inline))
#define Vc_INTRINSIC Vc_INTRINSIC_L Vc_INTRINSIC_R
#define Vc_FLATTEN 
#define Vc_CONST __attribute__((const))
#define Vc_CONST_L 
#define Vc_CONST_R Vc_CONST
#define Vc_PURE __attribute__((pure))
#define Vc_PURE_L 
#define Vc_PURE_R Vc_PURE
#define Vc_MAY_ALIAS __attribute__((may_alias))
#define Vc_ALWAYS_INLINE_L inline
#define Vc_ALWAYS_INLINE_R __attribute__((always_inline))
#define Vc_ALWAYS_INLINE Vc_ALWAYS_INLINE_L Vc_ALWAYS_INLINE_R
#define Vc_IS_UNLIKELY(x) __builtin_expect(x, 0)
#define Vc_IS_LIKELY(x) __builtin_expect(x, 1)
#define Vc_RESTRICT __restrict__
#define Vc_DEPRECATED_ALIAS(msg) 
#define Vc_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#elif defined(__GNUC__)
#define Vc_UNREACHABLE __builtin_unreachable
# if defined Vc_GCC && !defined __OPTIMIZE__
#define Vc_MAY_ALIAS 
# else
#define Vc_MAY_ALIAS __attribute__((__may_alias__))
# endif
#define Vc_INTRINSIC_R __attribute__((__always_inline__, __artificial__))
#define Vc_INTRINSIC_L inline
#define Vc_INTRINSIC Vc_INTRINSIC_L Vc_INTRINSIC_R
#define Vc_FLATTEN __attribute__((__flatten__))
#define Vc_ALWAYS_INLINE_L inline
#define Vc_ALWAYS_INLINE_R __attribute__((__always_inline__))
#define Vc_ALWAYS_INLINE Vc_ALWAYS_INLINE_L Vc_ALWAYS_INLINE_R
# ifdef Vc_ICC
#define Vc_PURE 
#define Vc_CONST 
#define Vc_NEVER_INLINE 
# else
#define Vc_NEVER_INLINE [[gnu::noinline]]
#define Vc_PURE __attribute__((__pure__))
#define Vc_CONST __attribute__((__const__))
# endif
#define Vc_CONST_L 
#define Vc_CONST_R Vc_CONST
#define Vc_PURE_L 
#define Vc_PURE_R Vc_PURE
#define Vc_IS_UNLIKELY(x) __builtin_expect(x, 0)
#define Vc_IS_LIKELY(x) __builtin_expect(x, 1)
#define Vc_RESTRICT __restrict__
# ifdef Vc_ICC
#define Vc_DEPRECATED_ALIAS(msg) 
# else
#define Vc_DEPRECATED_ALIAS(msg) __attribute__((__deprecated__(msg)))
# endif
#define Vc_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#else
#define Vc_NEVER_INLINE 
#define Vc_FLATTEN 
# ifdef Vc_PURE
#undef Vc_PURE
# endif
#define Vc_MAY_ALIAS 
# ifdef Vc_MSVC
#define Vc_ALWAYS_INLINE inline __forceinline
#define Vc_ALWAYS_INLINE_L Vc_ALWAYS_INLINE
#define Vc_ALWAYS_INLINE_R 
#define Vc_CONST __declspec(noalias)
#define Vc_CONST_L Vc_CONST
#define Vc_CONST_R 
#define Vc_PURE 
#define Vc_PURE_L Vc_PURE
#define Vc_PURE_R 
#define Vc_INTRINSIC inline __forceinline
#define Vc_INTRINSIC_L Vc_INTRINSIC
#define Vc_INTRINSIC_R 
#define Vc_UNREACHABLE [] { __assume(0); }
# else
#define Vc_ALWAYS_INLINE 
#define Vc_ALWAYS_INLINE_L 
#define Vc_ALWAYS_INLINE_R 
#define Vc_CONST 
#define Vc_CONST_L 
#define Vc_CONST_R 
#define Vc_PURE 
#define Vc_PURE_L 
#define Vc_PURE_R 
#define Vc_INTRINSIC 
#define Vc_INTRINSIC_L 
#define Vc_INTRINSIC_R 
#define Vc_UNREACHABLE std::abort
# endif
#define Vc_IS_UNLIKELY(x) x
#define Vc_IS_LIKELY(x) x
#define Vc_RESTRICT __restrict
#define Vc_DEPRECATED_ALIAS(msg) 
#define Vc_WARN_UNUSED_RESULT 
#endif
#ifdef Vc_CXX17
#define Vc_NODISCARD [[nodiscard]]
#elif defined __GNUC__
#define Vc_NODISCARD [[gnu::warn_unused_result]]
#else
#define Vc_NODISCARD 
#endif
#define Vc_NOTHING_EXPECTING_SEMICOLON static_assert(true, "")
#ifdef Vc_CXX17
#define Vc_FREE_STORE_OPERATORS_ALIGNED(align_) 
#else
#define Vc_FREE_STORE_OPERATORS_ALIGNED(align_) \
                                                                                         \
                                                                                         \
                                                                                         \
    Vc_ALWAYS_INLINE void *operator new(size_t size) \
    { \
        return Vc::Common::aligned_malloc<align_>(size); \
    } \
                                                                                         \
    Vc_ALWAYS_INLINE void *operator new(size_t, void *p) { return p; } \
                                                                                         \
    Vc_ALWAYS_INLINE void *operator new[](size_t size) \
    { \
        return Vc::Common::aligned_malloc<align_>(size); \
    } \
                                                                                         \
    Vc_ALWAYS_INLINE void *operator new[](size_t, void *p) { return p; } \
                                                                                         \
    Vc_ALWAYS_INLINE void operator delete(void *ptr, size_t) { Vc::Common::free(ptr); } \
                                                                                         \
    Vc_ALWAYS_INLINE void operator delete(void *, void *) {} \
                                                                                         \
    Vc_ALWAYS_INLINE void operator delete[](void *ptr, size_t) \
    { \
        Vc::Common::free(ptr); \
    } \
                                                                                         \
    Vc_ALWAYS_INLINE void operator delete[](void *, void *) {} \
                                                                                         \
    Vc_NOTHING_EXPECTING_SEMICOLON
#endif
#ifdef Vc_ASSERT
#define Vc_EXTERNAL_ASSERT 1
#else
#ifdef NDEBUG
#define Vc_ASSERT(x) Vc::detail::dummy_assert{} << ' '
#else
#define Vc_ASSERT(x) Vc::detail::real_assert(x, #x, __FILE__, __LINE__)
#endif
#endif
#ifdef COMPILE_FOR_UNIT_TESTS
#define Vc_NOEXCEPT_OR_IN_TEST 
#else
#define Vc_NOEXCEPT_OR_IN_TEST noexcept
#endif
#if defined Vc_CLANG || defined Vc_APPLECLANG
#define Vc_HAS_BUILTIN(x) __has_builtin(x)
#else
#define Vc_HAS_BUILTIN(x) 0
#endif
#define Vc_APPLY_IMPL_1_(macro,a,b,c,d,e) macro(a)
#define Vc_APPLY_IMPL_2_(macro,a,b,c,d,e) macro(a, b)
#define Vc_APPLY_IMPL_3_(macro,a,b,c,d,e) macro(a, b, c)
#define Vc_APPLY_IMPL_4_(macro,a,b,c,d,e) macro(a, b, c, d)
#define Vc_APPLY_IMPL_5_(macro,a,b,c,d,e) macro(a, b, c, d, e)
#define Vc_LIST_FLOAT_VECTOR_TYPES(size,macro,a,b,c,d) \
    size(macro, double_v, a, b, c, d) \
    size(macro, float_v, a, b, c, d)
#define Vc_LIST_INT_VECTOR_TYPES(size,macro,a,b,c,d) \
    size(macro, int_v, a, b, c, d) \
    size(macro, uint_v, a, b, c, d) \
    size(macro, short_v, a, b, c, d) \
    size(macro, ushort_v, a, b, c, d)
#define Vc_LIST_VECTOR_TYPES(size,macro,a,b,c,d) \
    Vc_LIST_FLOAT_VECTOR_TYPES(size, macro, a, b, c, d) \
    Vc_LIST_INT_VECTOR_TYPES(size, macro, a, b, c, d)
#define Vc_LIST_COMPARES(size,macro,a,b,c,d) \
    size(macro, ==, a, b, c, d) \
    size(macro, !=, a, b, c, d) \
    size(macro, <=, a, b, c, d) \
    size(macro, >=, a, b, c, d) \
    size(macro, < , a, b, c, d) \
    size(macro, > , a, b, c, d)
#define Vc_LIST_LOGICAL(size,macro,a,b,c,d) \
    size(macro, &&, a, b, c, d) \
    size(macro, ||, a, b, c, d)
#define Vc_LIST_BINARY(size,macro,a,b,c,d) \
    size(macro, |, a, b, c, d) \
    size(macro, &, a, b, c, d) \
    size(macro, ^, a, b, c, d)
#define Vc_LIST_SHIFTS(size,macro,a,b,c,d) \
    size(macro, <<, a, b, c, d) \
    size(macro, >>, a, b, c, d)
#define Vc_LIST_ARITHMETICS(size,macro,a,b,c,d) \
    size(macro, +, a, b, c, d) \
    size(macro, -, a, b, c, d) \
    size(macro, *, a, b, c, d) \
    size(macro, /, a, b, c, d) \
    size(macro, %, a, b, c, d)
#define Vc_APPLY_0(_list,macro) _list(Vc_APPLY_IMPL_1_, macro, 0, 0, 0, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_1(_list,macro,a) _list(Vc_APPLY_IMPL_2_, macro, a, 0, 0, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_2(_list,macro,a,b) _list(Vc_APPLY_IMPL_3_, macro, a, b, 0, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_3(_list,macro,a,b,c) _list(Vc_APPLY_IMPL_4_, macro, a, b, c, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_4(_list,macro,a,b,c,d) _list(Vc_APPLY_IMPL_5_, macro, a, b, c, d) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_ALL_COMPARES(macro) Vc_APPLY_0(Vc_LIST_COMPARES, macro)
#define Vc_ALL_LOGICAL(macro) Vc_APPLY_0(Vc_LIST_LOGICAL, macro)
#define Vc_ALL_BINARY(macro) Vc_APPLY_0(Vc_LIST_BINARY, macro)
#define Vc_ALL_SHIFTS(macro) Vc_APPLY_0(Vc_LIST_SHIFTS, macro)
#define Vc_ALL_ARITHMETICS(macro) Vc_APPLY_0(Vc_LIST_ARITHMETICS, macro)
#define Vc_ALL_FLOAT_VECTOR_TYPES(macro) Vc_APPLY_0(Vc_LIST_FLOAT_VECTOR_TYPES, macro)
#define Vc_ALL_VECTOR_TYPES(macro) Vc_APPLY_0(Vc_LIST_VECTOR_TYPES, macro)
#ifdef Vc_NO_ALWAYS_INLINE
#undef Vc_ALWAYS_INLINE
#undef Vc_ALWAYS_INLINE_L
#undef Vc_ALWAYS_INLINE_R
#define Vc_ALWAYS_INLINE inline
#define Vc_ALWAYS_INLINE_L inline
#define Vc_ALWAYS_INLINE_R 
#undef Vc_INTRINSIC
#undef Vc_INTRINSIC_L
#undef Vc_INTRINSIC_R
#define Vc_INTRINSIC inline
#define Vc_INTRINSIC_L inline
#define Vc_INTRINSIC_R 
#endif
#endif
#if defined Vc_GCC && Vc_GCC >= 0x60000
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif
#ifndef VC_GLOBAL_H_
#define VC_GLOBAL_H_ 
#include <cstdint>
Vc_VERSIONED_NAMESPACE_BEGIN
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
enum MallocAlignment {
    AlignOnVector,
    AlignOnCacheline,
    AlignOnPage
};
enum Implementation : std::uint_least32_t {
    ScalarImpl,
    SSE2Impl,
    SSE3Impl,
    SSSE3Impl,
    SSE41Impl,
    SSE42Impl,
    AVXImpl,
    AVX2Impl,
    MICImpl,
    NeonImpl,
    ImplementationMask = 0xfff };
enum ExtraInstructions : std::uint_least32_t {
    Float16cInstructions = 0x01000,
    Fma4Instructions = 0x02000,
    XopInstructions = 0x04000,
    PopcntInstructions = 0x08000,
    Sse4aInstructions = 0x10000,
    FmaInstructions = 0x20000,
    VexInstructions = 0x40000,
    Bmi2Instructions = 0x80000,
    ExtraInstructionsMask = 0xfffff000u
};
template <unsigned int Features> struct ImplementationT {
    static constexpr Implementation current()
    {
        return static_cast<Implementation>(Features & ImplementationMask);
    }
    static constexpr bool is(Implementation impl)
    {
        return static_cast<unsigned int>(impl) == current();
    }
    static constexpr bool is_between(Implementation low, Implementation high)
    {
        return static_cast<unsigned int>(low) <= current() &&
               static_cast<unsigned int>(high) >= current();
    }
    static constexpr bool runs_on(unsigned int extraInstructions)
    {
        return (extraInstructions & Features & ExtraInstructionsMask) ==
               (Features & ExtraInstructionsMask);
    }
};
using CurrentImplementation = ImplementationT<
#if defined Vc_HAVE_NEON
    NeonImpl
#elif defined(Vc_HAVE_MIC)
    MICImpl
#elif defined(Vc_HAVE_AVX2)
    AVX2Impl
#elif defined(Vc_HAVE_AVX)
    AVXImpl
#elif defined(Vc_HAVE_SSE4_2)
    SSE42Impl
#elif defined(Vc_HAVE_SSE4_1)
    SSE41Impl
#elif defined(Vc_HAVE_SSSE3)
    SSSE3Impl
#elif defined(Vc_HAVE_SSE3)
    SSE3Impl
#elif defined(Vc_HAVE_SSE2)
    SSE2Impl
#endif
#ifdef Vc_HAVE_SSE4a
    + Vc::Sse4aInstructions
#ifdef Vc_HAVE_XOP
    + Vc::XopInstructions
#ifdef Vc_HAVE_FMA4
    + Vc::Fma4Instructions
#endif
#endif
#endif
#ifdef Vc_HAVE_POPCNT
    + Vc::PopcntInstructions
#endif
#ifdef Vc_HAVE_FMA
    + Vc::FmaInstructions
#endif
#ifdef Vc_HAVE_BMI2
    + Vc::Bmi2Instructions
#endif
#ifdef Vc_USE_VEX_CODING
    + Vc::VexInstructions
#endif
    >;
inline const char *versionString() { return Vc_VERSION_STRING; }
constexpr unsigned int versionNumber() { return Vc_VERSION_NUMBER; }
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_SYNOPSIS_H_
#define VC_SIMD_SYNOPSIS_H_ 
#include <bitset>
#ifndef VC_INCLUDE_VC_DECLVAL_H_
#define VC_INCLUDE_VC_DECLVAL_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T, class U = T&&> U declval_(int);
template <class T> T declval_(long);
}
template <class T> decltype(detail::declval_<T>(0)) declval() noexcept;
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_DETAIL_H_
#define VC_SIMD_DETAIL_H_ 
#include <functional>
#ifndef NDEBUG
#include <iostream>
#endif
#include <limits>
#ifndef VC_SIMD_FLAGS_H_
#define VC_SIMD_FLAGS_H_ 
#include <cstddef>
Vc_VERSIONED_NAMESPACE_BEGIN
using size_t = std::size_t;
struct element_aligned_tag {};
struct vector_aligned_tag {};
template <size_t> struct overaligned_tag {};
inline constexpr element_aligned_tag element_aligned = {};
inline constexpr vector_aligned_tag vector_aligned = {};
template <size_t N> inline constexpr overaligned_tag<N> overaligned = {};
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_TYPE_TRAITS_H_
#define VC_SIMD_TYPE_TRAITS_H_ 
#ifndef VC_TRAITS_TYPE_TRAITS_H_
#define VC_TRAITS_TYPE_TRAITS_H_ 
#include <type_traits>
#ifndef VC_TRAITS_DECAY_H_
#define VC_TRAITS_DECAY_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
template <typename T> using decay = typename std::decay<T>::type;
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_TRAITS_HAS_NO_ALLOCATED_DATA_H_
#define VC_TRAITS_HAS_NO_ALLOCATED_DATA_H_ 
#include <array>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
template<typename T> struct has_no_allocated_data_impl : public std::false_type {};
template <typename T>
struct has_no_allocated_data
    : public has_no_allocated_data_impl<
          typename std::remove_cv<typename std::remove_reference<T>::type>::type>
{
};
template<typename T, std::size_t N> struct has_no_allocated_data_impl<std::array<T, N>> : public std::true_type {};
template<typename T, std::size_t N> struct has_no_allocated_data_impl<T[N]> : public std::true_type {};
template<typename T> struct has_no_allocated_data_impl<T[]> : public std::true_type {};
static_assert(has_no_allocated_data<int[256]>::value, "");
static_assert(has_no_allocated_data<const int[256]>::value, "");
static_assert(has_no_allocated_data<volatile int[256]>::value, "");
static_assert(has_no_allocated_data<const volatile int[256]>::value, "");
static_assert(has_no_allocated_data<int[]>::value, "");
static_assert(has_no_allocated_data<int[2][2]>::value, "");
static_assert(has_no_allocated_data<const volatile std::array<int, 256> &>::value, "");
static_assert(has_no_allocated_data<const volatile std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<volatile std::array<int, 256> &>::value, "");
static_assert(has_no_allocated_data<volatile std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<const std::array<int, 256> &>::value, "");
static_assert(has_no_allocated_data<const std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<std::array<int, 256> &&>::value, "");
static_assert(!has_no_allocated_data<int*>::value, "");
static_assert(!has_no_allocated_data<const int*>::value, "");
static_assert(!has_no_allocated_data<const int *const>::value, "");
static_assert(!has_no_allocated_data<int *const>::value, "");
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_
#define VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_ 
#include <initializer_list>
#include <memory>
#ifdef _LIBCPP_BEGIN_NAMESPACE_STD
_LIBCPP_BEGIN_NAMESPACE_STD
#else
namespace std
{
#endif
#ifdef _WIN32
template <typename T, size_t N> class array;
#else
template <typename T, size_t N> struct array;
#endif
template <typename T, typename Allocator> class vector;
#ifdef _LIBCPP_END_NAMESPACE_STD
_LIBCPP_END_NAMESPACE_STD
#else
}
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
namespace has_contiguous_storage_detail
{
template <typename T, typename It = typename T::iterator>
std::is_base_of<std::random_access_iterator_tag,
                typename It::iterator_category>
test(int);
template <typename T>
std::is_base_of<std::random_access_iterator_tag,
                typename T::iterator_category>
test(long);
template <typename T> std::false_type test(...);
}
template <typename T>
struct has_contiguous_storage_impl
    : public decltype(has_contiguous_storage_detail::test<T>(int())) {
};
template <typename T>
struct has_contiguous_storage
    : public has_contiguous_storage_impl<
          typename std::remove_cv<typename std::remove_reference<T>::type>::type>
{
};
template <typename T> struct has_contiguous_storage_impl<const T *> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<T *> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<std::unique_ptr<T[]>> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<std::initializer_list<T>> : public std::true_type {};
template <typename T, std::size_t N> struct has_contiguous_storage_impl<T[N]> : public std::true_type {};
template <typename T, std::size_t N> struct has_contiguous_storage_impl<std::array<T, N>> : public std::true_type {};
template <typename T, typename A> struct has_contiguous_storage_impl<std::vector<T, A>> : public std::true_type {};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_TRAITS_IS_INITIALIZER_LIST_H_
#define VC_TRAITS_IS_INITIALIZER_LIST_H_ 
#include <initializer_list>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
namespace is_initializer_list_impl
{
template <typename... Args> struct test : public std::false_type {};
template <typename I> struct test<std::initializer_list<I>> : public std::true_type {};
}
template <typename... Args>
struct is_initializer_list
    : public is_initializer_list_impl::test<decay<Args>...>
{
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_TRAITS_IS_FUNCTOR_ARGUMENT_IMMUTABLE_H_
#define VC_TRAITS_IS_FUNCTOR_ARGUMENT_IMMUTABLE_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
namespace is_functor_argument_immutable_impl
{
template <typename F, typename A> std::true_type test(void (F::*)(A));
template <typename F, typename A> std::true_type test(void (F::*)(A) const);
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &));
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &) const);
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &&));
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &&) const);
struct dummy {};
template <
    typename F, typename A
#ifdef Vc_ICC
    ,
    typename = decltype(std::declval<F &>()(std::declval<dummy &>()))
#endif
    ,
#ifdef Vc_MSVC
#define Vc_TEMPLATE_ 
#else
#define Vc_TEMPLATE_ template
#endif
    typename MemberPtr = decltype(&F::Vc_TEMPLATE_ operator()<A>)>
decltype(is_functor_argument_immutable_impl::test(std::declval<MemberPtr>())) test2(int);
#undef Vc_TEMPLATE_
template <typename F, typename A>
decltype(
    is_functor_argument_immutable_impl::test(std::declval<decltype(&F::operator())>()))
test2(float);
template <typename A> std::true_type test3(void(*)(A));
template <typename A> std::is_const<A> test3(void(*)(A &));
template <typename A> std::is_const<A> test3(void(*)(A &&));
}
template <typename F, typename A, bool = std::is_function<F>::value>
struct is_functor_argument_immutable;
template <typename F, typename A>
struct is_functor_argument_immutable<F, A, false>
    : public decltype(is_functor_argument_immutable_impl::test2<
                      typename std::remove_reference<F>::type, A>(int())) {
};
template <typename F, typename A>
struct is_functor_argument_immutable<F, A, true>
    : public decltype(is_functor_argument_immutable_impl::test3(std::declval<F>())) {
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_TRAITS_IS_OUTPUT_ITERATOR_H_
#define VC_TRAITS_IS_OUTPUT_ITERATOR_H_ 
#include <iterator>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
namespace is_output_iterator_impl
{
template <typename T, typename ValueType = typename std::iterator_traits<T>::value_type,
          typename = decltype(*std::declval<T &>() = std::declval<
                                  ValueType>())
          >
std::true_type test(int);
template <typename T> std::false_type test(...);
}
template <typename T>
struct is_output_iterator
    : public std::conditional<
          std::is_void<typename std::iterator_traits<T>::value_type>::value,
          std::true_type, decltype(is_output_iterator_impl::test<T>(int()))>::type
{
};
static_assert(!std::is_void<std::iterator_traits<int *>::value_type>::value, "");
static_assert(is_output_iterator<int *>::value, "");
static_assert(!is_output_iterator<const int *>::value, "");
}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
struct enable_if_default_type
{
    constexpr enable_if_default_type() {}
};
static constexpr enable_if_default_type nullarg;
template <bool Test, typename T = enable_if_default_type> using enable_if = typename std::enable_if<Test, T>::type;
namespace Traits
{
#ifndef VC_TRAITS_HAS_SUBSCRIPT_OPERATOR_H_
#define VC_TRAITS_HAS_SUBSCRIPT_OPERATOR_H_ 
namespace has_subscript_operator_impl
{
template <typename T, typename I, typename = decltype(std::declval<T &>()[std::declval<I>()])> std::true_type test(int);
template <typename T, typename I> std::false_type test(float);
}
template <typename T, typename I = std::size_t>
struct has_subscript_operator : public decltype(has_subscript_operator_impl::test<T, I>(1))
{
};
static_assert(has_subscript_operator<int[]>::value, "");
static_assert(has_subscript_operator<int[], int>::value, "");
static_assert(!has_subscript_operator<int[], void *>::value, "");
#endif
#ifndef VC_TRAITS_HAS_MULTIPLY_OPERATOR_H_
#define VC_TRAITS_HAS_MULTIPLY_OPERATOR_H_ 
namespace has_multiply_operator_impl
{
template <typename T, typename U, typename = decltype(std::declval<T>() * std::declval<U>())> std::true_type test(int);
template <typename T, typename U> std::false_type test(...);
}
template <typename T, typename U = T>
struct has_multiply_operator : public decltype(has_multiply_operator_impl::test<T, U>(1))
{
};
#endif
#ifndef VC_TRAITS_HAS_ADDITION_OPERATOR_H_
#define VC_TRAITS_HAS_ADDITION_OPERATOR_H_ 
namespace has_addition_operator_impl
{
template <typename T, typename U, typename = decltype(std::declval<T>() + std::declval<U>())> std::true_type test(int);
template <typename T, typename U> std::false_type test(...);
}
template <typename T, typename U = T>
struct has_addition_operator : public decltype(has_addition_operator_impl::test<T, U>(1))
{
};
#endif
#ifndef VC_TRAITS_HAS_EQUALITY_OPERATOR_H_
#define VC_TRAITS_HAS_EQUALITY_OPERATOR_H_ 
namespace has_equality_operator_impl
{
template <typename T, typename U,
          typename = enable_if<!std::is_same<void, decltype(std::declval<T>() == std::declval<U>())>::value>>
std::true_type test(int);
template <typename T, typename U> std::false_type test(...);
}
template <typename T, typename U = T>
struct has_equality_operator : public decltype(has_equality_operator_impl::test<T, U>(1))
{
};
static_assert(has_equality_operator<int>::value, "has_equality_operator fails");
namespace
{
class Foobar {};
static_assert(!has_equality_operator<Foobar>::value, "has_equality_operator fails");
}
#endif
template<typename T> struct is_simd_mask_internal : public std::false_type {};
template<typename T> struct is_simd_vector_internal : public std::false_type {};
template<typename T> struct is_subscript_operation_internal : public std::false_type {};
template<typename T> struct is_simdarray_internal : public std::false_type {};
template<typename T> struct is_simd_mask_array_internal : public std::false_type {};
template<typename T> struct is_loadstoreflag_internal : public std::false_type {};
template <std::size_t, typename... Args> struct is_gather_signature_impl;
template <std::size_t N_, typename Arg0, typename Arg1, typename... MoreArguments>
struct is_gather_signature_impl<N_, Arg0, Arg1, MoreArguments...>
    : public std::integral_constant<bool, has_subscript_operator<Arg0>::value &&
                                              !is_loadstoreflag_internal<Arg1>::value &&
                                              has_subscript_operator<Arg1>::value> {
};
template<typename... Args> struct is_gather_signature_impl<0, Args...> : public std::false_type {};
template<typename... Args> struct is_gather_signature_impl<1, Args...> : public std::false_type {};
template <typename... Args> struct is_gather_signature : public is_gather_signature_impl<sizeof...(Args), decay<Args>...> {};
template <std::size_t, typename... Args> struct is_cast_arguments_internal : public std::false_type {};
template <typename Arg>
struct is_cast_arguments_internal<1, Arg> : public std::integral_constant<
                                                bool,
                                                is_simdarray_internal<Arg>::value ||
                                                    is_simd_vector_internal<Arg>::value>
{
};
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_integral_internal;
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_floating_point_internal;
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_signed_internal;
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_unsigned_internal;
template <typename T> struct is_integral_internal <T, false> : public std::is_integral <T> {};
template <typename T> struct is_floating_point_internal<T, false> : public std::is_floating_point<T> {};
template <typename T> struct is_signed_internal <T, false> : public std::is_signed <T> {};
template <typename T> struct is_unsigned_internal <T, false> : public std::is_unsigned <T> {};
template <typename V> struct is_integral_internal <V, true> : public std::is_integral <typename V::EntryType> {};
template <typename V> struct is_floating_point_internal<V, true> : public std::is_floating_point<typename V::EntryType> {};
template <typename V> struct is_signed_internal <V, true> : public std::is_signed <typename V::EntryType> {};
template <typename V> struct is_unsigned_internal <V, true> : public std::is_unsigned <typename V::EntryType> {};
template <typename T>
struct is_arithmetic_internal
    : public std::integral_constant<
          bool,
          (is_floating_point_internal<T>::value || is_integral_internal<T>::value)>
{
};
template <typename T,
          bool = (is_simd_vector_internal<T>::value || is_simd_mask_internal<T>::value ||
                  is_simdarray_internal<T>::value ||
                  is_simd_mask_array_internal<T>::value)>
struct vector_size_internal;
template <typename T>
struct vector_size_internal<T, true> : public std::integral_constant<std::size_t, T::Size>
{
};
template <typename T>
struct vector_size_internal<T, false> : public std::integral_constant<std::size_t, 0>
{
};
template <typename T>
struct is_simd_mask : public std::integral_constant<bool,
                                                    (is_simd_mask_internal<decay<T>>::value ||
                                                     is_simd_mask_array_internal<decay<T>>::value)>
{
};
template <typename T>
struct is_simd_vector
    : public std::integral_constant<bool,
                                    (is_simd_vector_internal<decay<T>>::value ||
                                     is_simdarray_internal<decay<T>>::value)>
{
};
template <typename T>
struct isSimdArray : public is_simdarray_internal<decay<T>>
{
};
template <typename T>
struct isSimdMaskArray : public is_simd_mask_array_internal<decay<T>>
{
};
template <typename T> struct is_subscript_operation : public is_subscript_operation_internal<decay<T>> {};
template <typename T> struct is_load_store_flag : public is_loadstoreflag_internal<decay<T>> {};
template <typename... Args> struct is_cast_arguments : public is_cast_arguments_internal<sizeof...(Args), decay<Args>...> {};
template <typename T> struct is_atomic_simdarray_internal : public std::false_type {};
template <typename T> using isAtomicSimdArray = is_atomic_simdarray_internal<decay<T>>;
template <typename T> struct is_atomic_simd_mask_array_internal : public std::false_type {};
template <typename T> using isAtomicSimdMaskArray = is_atomic_simd_mask_array_internal<decay<T>>;
template <typename T> struct simd_vector_size : public vector_size_internal<decay<T>> {};
template <typename T> struct is_integral : public is_integral_internal<decay<T>> {};
template <typename T> struct is_floating_point : public is_floating_point_internal<decay<T>> {};
template <typename T> struct is_arithmetic : public is_arithmetic_internal<decay<T>> {};
template <typename T> struct is_signed : public is_signed_internal<decay<T>> {};
template <typename T> struct is_unsigned : public is_unsigned_internal<decay<T>> {};
template <typename T, bool IsSimdVector> struct scalar_type_internal { using type = T; };
template <typename T> struct scalar_type_internal<T, true> { using type = typename T::EntryType; };
template <typename T> using scalar_type = typename scalar_type_internal<decay<T>, is_simd_vector<T>::value>::type;
}
Vc_VERSIONED_NAMESPACE_END
#ifndef VC_TRAITS_ENTRY_TYPE_OF_H_
#define VC_TRAITS_ENTRY_TYPE_OF_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace Traits
{
namespace entry_type_of_internal
{
template <typename T, bool = Traits::is_simd_vector<T>::value> struct entry_type;
template <typename T> struct entry_type<T, true>
{
    using type = typename decay<T>::EntryType;
};
template <typename T> struct entry_type<T, false>
{
    using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};
}
template <typename T> using entry_type_of = typename entry_type_of_internal::entry_type<T>::type;
}
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail {
template <class... Ts> using void_t = void;
#ifdef Vc_CXX17
template <class... Ts> using all = std::conjunction<Ts...>;
template <class... Ts> using any = std::disjunction<Ts...>;
using std::negation;
#else
template <class... Ts>
struct all : std::true_type {};
template <class A> struct all<A> : public A {};
template <class A, class... Ts>
struct all<A, Ts...>
    : public std::conditional<A::value, all<Ts...>, A>::type {
};
template <class... Ts>
struct any : std::false_type {};
template <class A> struct any<A> : public A {};
template <class A, class... Ts>
struct any<A, Ts...>
    : public std::conditional<A::value, A, any<Ts...>>::type {
};
template <class T> struct negation : public std::integral_constant<bool, !T::value> {
};
#endif
using std::is_arithmetic;
using std::is_convertible;
using std::is_same;
using std::is_signed;
using std::is_unsigned;
using std::enable_if_t;
template <class T, T a, T b> struct is_equal : public std::false_type {
};
template <class T, T a> struct is_equal<T, a, a> : public std::true_type {
};
template <class T, T a, T b> inline constexpr bool is_equal_v = is_equal<T, a, b>::value;
template <class... Ts> struct none : public negation<any<Ts...>> {};
template <class T> struct is_arithmetic_not_bool : public std::is_arithmetic<T> {
};
template <> struct is_arithmetic_not_bool<bool> : public std::false_type {
};
template <class Ptr, class ValueType>
struct is_possible_loadstore_conversion
    : all<is_arithmetic_not_bool<Ptr>, is_arithmetic_not_bool<ValueType>> {
};
template <> struct is_possible_loadstore_conversion<bool, bool> : std::true_type {
};
template <class T, std::size_t Expected>
struct has_expected_sizeof : public std::integral_constant<bool, sizeof(T) == Expected> {
};
template <class... Ts>
inline constexpr bool conjunction_v = all<Ts...>::value;
template <class... Ts> inline constexpr bool disjunction_v = any<Ts...>::value;
template <class T> inline constexpr bool negation_v = negation<T>::value;
template <class... Ts> inline constexpr bool none_v = none<Ts...>::value;
template <class T, std::size_t Expected>
inline constexpr bool has_expected_sizeof_v = has_expected_sizeof<T, Expected>::value;
template <class T> typename T::value_type value_type_or_identity_impl(int);
template <class T> T value_type_or_identity_impl(float);
template <class T>
using value_type_or_identity = decltype(value_type_or_identity_impl<T>(int()));
template <class T> struct is_vectorizable : public std::is_arithmetic<T> {};
template <> struct is_vectorizable<bool> : public std::false_type {};
template <class T> inline constexpr bool is_vectorizable_v = is_vectorizable<T>::value;
template <int A, int B> struct is_less_than : public std::integral_constant<bool, (A < B)> {
};
template <int A, int B>
struct is_equal_to : public std::integral_constant<bool, (A == B)> {
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T> static constexpr void unused(T && ) {}
#if defined Vc_GCC
template <class T>
[[gnu::weak, gnu::noinline,
gnu::warning("Your code is invoking undefined behavior. Please fix your code.")]]
const T &warn_ub(const T &x);
template <class T>
[[gnu::weak, gnu::noinline]]
const T &warn_ub(const T &x) { return x; }
#else
template <class T> const T &warn_ub(const T &x) { return x; }
#endif
#ifdef NDEBUG
struct dummy_assert {
    template <class T> Vc_INTRINSIC dummy_assert &operator<<(T &&) noexcept
    {
        return *this;
    }
};
#else
struct real_assert {
    Vc_INTRINSIC real_assert(bool ok, const char *code, const char *file, int line)
        : failed(!ok)
    {
        if (Vc_IS_UNLIKELY(failed)) {
            printFirst(code, file, line);
        }
    }
    Vc_INTRINSIC ~real_assert()
    {
        if (Vc_IS_UNLIKELY(failed)) {
            finalize();
        }
    }
    template <class T> Vc_INTRINSIC real_assert &operator<<(T &&x)
    {
        if (Vc_IS_UNLIKELY(failed)) {
            print(std::forward<T>(x));
        }
        return *this;
    }
private:
    void printFirst(const char *code, const char *file, int line)
    {
        std::cerr << file << ':' << line << ": assert(" << code << ") failed.";
    }
    template <class T> void print(T &&x) const { std::cerr << std::forward<T>(x); }
    void finalize()
    {
        std::cerr << std::endl;
        std::abort();
    }
    bool failed;
};
#endif
#if defined Vc_CHECK_ALIGNMENT || defined COMPILE_FOR_UNIT_TESTS
template <class V = void, class T>
Vc_ALWAYS_INLINE void assertCorrectAlignment(const T *ptr)
{
    auto &&is_aligned = [](const T *p) -> bool {
        constexpr size_t s =
            alignof(std::conditional_t<std::is_same<void, V>::value, T, V>);
        return (reinterpret_cast<size_t>(p) & (s - 1)) == 0;
    };
#ifdef COMPILE_FOR_UNIT_TESTS
    Vc_ASSERT(is_aligned(ptr))
        << " ptr = " << ptr << ", expected alignment = "
        << alignof(std::conditional_t<std::is_same<void, V>::value, T, V>);
    detail::unused(is_aligned);
#else
    if (Vc_IS_UNLIKELY(!is_aligned(ptr))) {
        std::fprintf(stderr, "A load with incorrect alignment has just been called. Look at the stacktrace to find the guilty load.\n");
        std::abort();
    }
#endif
}
#else
template <class V = void, class T>
Vc_ALWAYS_INLINE void assertCorrectAlignment(const T *)
{
}
#endif
template <size_t X> using size_constant = std::integral_constant<size_t, X>;
template <class T, class A>
auto size_tag_type_f(int)->size_constant<simd_size<T, A>::value>;
template <class T, class A> auto size_tag_type_f(float)->size_constant<0>;
template <class T, class A> using size_tag_type = decltype(size_tag_type_f<T, A>(0));
using uchar = unsigned char;
using schar = signed char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using llong = long long;
using ullong = unsigned long long;
template <class T, size_t = sizeof(T)> struct equal_int_type;
template <> struct equal_int_type< long, 4> { using type = int; };
template <> struct equal_int_type< long, 8> { using type = llong; };
template <> struct equal_int_type<ulong, 4> { using type = uint; };
template <> struct equal_int_type<ulong, 8> { using type = ullong; };
template <class T> using equal_int_type_t = typename equal_int_type<T>::type;
template <class T> Vc_INTRINSIC const T &promote_preserving_unsigned(const T &x)
{
    return x;
}
Vc_INTRINSIC unsigned int promote_preserving_unsigned(const unsigned char &x)
{
    return x;
}
Vc_INTRINSIC unsigned int promote_preserving_unsigned(const unsigned short &x)
{
    return x;
}
class exact_bool {
    const bool d;
public:
    constexpr exact_bool(bool b) : d(b) {}
    exact_bool(int) = delete;
    constexpr operator bool() const { return d; }
};
template <typename F, size_t... I>
Vc_INTRINSIC void execute_on_index_sequence(F && f, std::index_sequence<I...>)
{
    auto &&x = {(f(size_constant<I>()), 0)...};
    unused(x);
}
template <typename F>
Vc_INTRINSIC void execute_on_index_sequence(F &&, std::index_sequence<>)
{
}
template <typename R, typename F, size_t... I>
Vc_INTRINSIC R execute_on_index_sequence_with_return(F && f, std::index_sequence<I...>)
{
    return R{f(size_constant<I>())...};
}
template <size_t N, typename F> Vc_INTRINSIC void execute_n_times(F && f)
{
    execute_on_index_sequence(std::forward<F>(f), std::make_index_sequence<N>{});
}
template <size_t N, typename R, typename F>
Vc_INTRINSIC R generate_from_n_evaluations(F && f)
{
    return execute_on_index_sequence_with_return<R>(std::forward<F>(f),
                                                    std::make_index_sequence<N>{});
}
template <typename T> struct may_alias_impl {
    typedef T type Vc_MAY_ALIAS;
};
#if 1
template <typename T> using may_alias [[gnu::may_alias]] = T;
#else
template <typename T> using may_alias = typename may_alias_impl<T>::type;
#endif
struct unsupported_base {
    unsupported_base() = delete;
    unsupported_base(const unsupported_base &) = delete;
    unsupported_base &operator=(const unsupported_base &) = delete;
    ~unsupported_base() = delete;
};
struct invalid_traits {
    using is_valid = std::false_type;
    static constexpr size_t simd_member_alignment = 1;
    struct simd_impl_type;
    struct simd_member_type {};
    struct simd_cast_type;
    using simd_base = unsupported_base;
    static constexpr size_t mask_member_alignment = 1;
    struct mask_impl_type;
    struct mask_member_type {};
    struct mask_cast_type;
    using mask_base = unsupported_base;
};
template <class T, class Abi, class = void_t<>> struct traits : invalid_traits {
};
template <class T> struct get_impl;
template <class T> using get_impl_t = typename get_impl<std::decay_t<T>>::type;
template <class T> struct get_traits;
template <class T> using get_traits_t = typename get_traits<std::decay_t<T>>::type;
constexpr std::size_t next_power_of_2(std::size_t x)
{
    return (x & (x - 1)) == 0 ? x : next_power_of_2((x | (x >> 1)) + 1);
}
inline constexpr struct private_init_t {} private_init = {};
inline constexpr struct bitset_init_t {} bitset_init = {};
template <size_t N> inline constexpr size_constant<N> size_tag = {};
template <class T> struct identity {
    using type = T;
};
template <class T> using id = typename identity<T>::type;
template <bool Value> using bool_constant = std::integral_constant<bool, Value>;
using std::true_type;
using std::false_type;
template <class From, class To, bool = std::is_arithmetic<From>::value,
          bool = std::is_arithmetic<To>::value>
struct is_narrowing_conversion;
Vc_MSVC_WARNING_(push)
Vc_MSVC_WARNING_(disable : 4018)
template <class From, class To>
struct is_narrowing_conversion<From, To, true, true>
    : public bool_constant<(
          std::numeric_limits<From>::digits > std::numeric_limits<To>::digits ||
          std::numeric_limits<From>::max() > std::numeric_limits<To>::max() ||
          std::numeric_limits<From>::lowest() < std::numeric_limits<To>::lowest() ||
          (std::is_signed<From>::value && std::is_unsigned<To>::value))> {
};
Vc_MSVC_WARNING_(pop)
template <class T> struct is_narrowing_conversion<bool, T, true, true> : public std::true_type {};
template <> struct is_narrowing_conversion<bool, bool, true, true> : public std::false_type {};
template <class T> struct is_narrowing_conversion<T, T, true, true> : public std::false_type {
};
template <class From, class To>
struct is_narrowing_conversion<From, To, false, true>
    : public negation<std::is_convertible<From, To>> {
};
template <class From, class To, bool = (sizeof(From) < sizeof(To))>
struct converts_to_higher_integer_rank : public std::true_type {
};
template <class From, class To>
struct converts_to_higher_integer_rank<From, To, false>
    : public std::is_same<decltype(declval<From>() + declval<To>()), To> {
};
template <class Flag, size_t Alignment> struct is_aligned;
template <size_t Alignment>
struct is_aligned<vector_aligned_tag, Alignment> : public std::true_type {
};
template <size_t Alignment>
struct is_aligned<element_aligned_tag, Alignment> : public std::false_type {
};
template <size_t GivenAlignment, size_t Alignment>
struct is_aligned<overaligned_tag<GivenAlignment>, Alignment>
    : public std::integral_constant<bool, (GivenAlignment >= Alignment)> {
};
template <class Flag, size_t Alignment>
inline constexpr bool is_aligned_v = is_aligned<Flag, Alignment>::value;
template <size_t Alignment>
class when_aligned
{
public:
    constexpr when_aligned(vector_aligned_tag) {}
    template <size_t Given, class = std::enable_if_t<(Given >= Alignment)>>
    constexpr when_aligned(overaligned_tag<Given>)
    {
    }
};
template <size_t Alignment>
class when_unaligned
{
public:
    constexpr when_unaligned(element_aligned_tag) {}
    template <size_t Given, class = std::enable_if_t<(Given < Alignment)>>
    constexpr when_unaligned(overaligned_tag<Given>)
    {
    }
};
template <class T, class A> Vc_INTRINSIC_L const auto &data(const Vc::simd<T, A> &x) Vc_INTRINSIC_R;
template <class T, class A> Vc_INTRINSIC_L auto &data(Vc::simd<T, A> & x) Vc_INTRINSIC_R;
template <class T, class A> Vc_INTRINSIC_L const auto &data(const Vc::simd_mask<T, A> &x) Vc_INTRINSIC_R;
template <class T, class A> Vc_INTRINSIC_L auto &data(Vc::simd_mask<T, A> &x) Vc_INTRINSIC_R;
template <class FromT, class FromA, class ToT, class ToA> struct simd_converter;
template <class T, class A> struct simd_converter<T, A, T, A> {
    template <class U> Vc_INTRINSIC const U &operator()(const U &x) { return x; }
};
template <class V>
Vc_INTRINSIC auto to_value_type_or_member_type(const V &x)->decltype(detail::data(x))
{
    return detail::data(x);
}
template <class V>
Vc_INTRINSIC const typename V::value_type &to_value_type_or_member_type(
    const typename V::value_type &x)
{
    return x;
}
template <class IfFun, class ElseFun>
Vc_INTRINSIC auto impl_or_fallback_dispatch(std::true_type, IfFun &&fun, ElseFun &&)
{
    return fun(0);
}
template <class IfFun, class ElseFun>
Vc_INTRINSIC auto impl_or_fallback_dispatch(std::false_type, IfFun &&, ElseFun &&fun)
{
    return fun(0);
}
template <bool Condition, class IfFun, class ElseFun>
Vc_INTRINSIC auto constexpr_if(IfFun &&if_fun, ElseFun &&else_fun)
{
    return impl_or_fallback_dispatch(Vc::detail::bool_constant<Condition>(), if_fun,
                                     else_fun);
}
template <bool Condition, class IfFun> Vc_INTRINSIC auto constexpr_if(IfFun &&if_fun)
{
    return impl_or_fallback_dispatch(Vc::detail::bool_constant<Condition>(), if_fun,
                                     [](int) {});
}
template <bool Condition, bool Condition2, class IfFun, class... Remainder>
Vc_INTRINSIC auto constexpr_if(IfFun &&if_fun, Vc::detail::bool_constant<Condition2>,
                               Remainder &&... rem)
{
    return impl_or_fallback_dispatch(
        Vc::detail::bool_constant<Condition>(), if_fun, [&](auto tmp_) {
            return constexpr_if<(std::is_same<decltype(tmp_), int>::value && Condition2)>(
                rem...);
        });
}
#ifdef __cpp_if_constexpr
#define Vc_CONSTEXPR_IF_RETURNING(...) if constexpr (__VA_ARGS__) {
#define Vc_CONSTEXPR_IF(...) if constexpr (__VA_ARGS__) {
#define Vc_CONSTEXPR_ELSE_IF(...) } else if constexpr (__VA_ARGS__) {
#define Vc_CONSTEXPR_ELSE } else {
#define Vc_CONSTEXPR_ENDIF }
#else
#define Vc_CONSTEXPR_IF_RETURNING(...) return Vc::detail::constexpr_if<(__VA_ARGS__)>([&](auto) {
#define Vc_CONSTEXPR_IF(...) Vc::detail::constexpr_if<(__VA_ARGS__)>([&](auto) {
#define Vc_CONSTEXPR_ELSE_IF(...) }, Vc::detail::bool_constant<(__VA_ARGS__)>(), [&](auto) {
#define Vc_CONSTEXPR_ELSE }, [&](auto) {
#define Vc_CONSTEXPR_ENDIF });
#endif
template <size_t Size> struct bool_storage_member_type;
template <class T, size_t Bytes, class = detail::void_t<>> struct intrinsic_type;
template <class T, size_t Size>
using intrinsic_type_t = typename intrinsic_type<T, Size * sizeof(T)>::type;
template <class T> struct is_intrinsic : public std::false_type {};
template <class T> inline constexpr bool is_intrinsic_v = is_intrinsic<T>::value;
template <class T, size_t Bytes, class = detail::void_t<>> struct builtin_type {};
template <class T, size_t Size>
using builtin_type_t = typename builtin_type<T, Size * sizeof(T)>::type;
template <class T> struct is_builtin_vector : public std::false_type {};
template <class T> inline constexpr bool is_builtin_vector_v = is_builtin_vector<T>::value;
template <class T, int N> struct fixed_size_storage_builder_wrapper;
template <class T, int N>
using fixed_size_storage = typename fixed_size_storage_builder_wrapper<T, N>::type;
}
Vc_VERSIONED_NAMESPACE_END
#endif
#include <utility>
#include <functional>
#ifndef VC_SIMD_WHERE_H_
#define VC_SIMD_WHERE_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T = void> struct shift_left {
    constexpr T operator()(const T &a, const T &b) const { return a << b; }
};
template <> struct shift_left<void> {
    template <typename L, typename R> constexpr auto operator()(L &&a, R &&b) const
    {
        return std::forward<L>(a) << std::forward<R>(b);
    }
};
template <class T = void> struct shift_right {
    constexpr T operator()(const T &a, const T &b) const { return a >> b; }
};
template <> struct shift_right<void> {
    template <typename L, typename R> constexpr auto operator()(L &&a, R &&b) const
    {
        return std::forward<L>(a) >> std::forward<R>(b);
    }
};
template <class T = void> struct increment {
    constexpr T operator()(T a) const { return ++a; }
};
template <> struct increment<void> {
    template <typename T> constexpr T operator()(T a) const { return ++a; }
};
template <class T = void> struct decrement {
    constexpr T operator()(T a) const { return --a; }
};
template <> struct decrement<void> {
    template <typename T> constexpr T operator()(T a) const { return --a; }
};
template <class T> struct get_impl {
    static_assert(
        std::is_arithmetic<T>::value,
        "Vc chose the wrong implementation class. This should not be possible.");
    template <class U, class F>
    Vc_INTRINSIC void masked_load(T &d, bool k, const U *mem, F)
    {
        if (k) {
            d = static_cast<T>(mem[0]);
        }
    }
};
template <> struct get_impl<bool> {
    template <class F> Vc_INTRINSIC void masked_load(bool &d, bool k, const bool *mem, F)
    {
        if (k) {
            d = mem[0];
        }
    }
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_DETAIL_CONCEPTS_H_
#define VC_DETAIL_CONCEPTS_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T, class = std::enable_if_t<std::is_signed<T>::value>>
using SignedArithmetic = T;
template <class T, size_t ExpectedSizeof, class DstT,
          class = enable_if_t<all<has_expected_sizeof<T, ExpectedSizeof>,
                                  is_convertible<T, DstT>>::value>>
using convertible_memory = T;
template <class From, class To,
          class = enable_if_t<
              negation<detail::is_narrowing_conversion<std::decay_t<From>, To>>::value>>
using value_preserving = From;
template <class From, class To, class DecayedFrom = std::decay_t<From>,
          class = enable_if_t<all<
              is_convertible<From, To>,
              any<is_same<DecayedFrom, To>, is_same<DecayedFrom, int>,
                  all<is_same<DecayedFrom, uint>, is_unsigned<To>>,
                  negation<detail::is_narrowing_conversion<DecayedFrom, To>>>>::value>>
using value_preserving_or_int = From;
template <int...> struct tag {
};
template <class T, class = enable_if_t<is_arithmetic_not_bool<T>::value>>
using arithmetic = T;
template <
    class Ptr, class ValueType,
    class = enable_if_t<detail::is_possible_loadstore_conversion<Ptr, ValueType>::value>>
using loadstore_ptr_type = Ptr;
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_STORAGE_H_
#define VC_SIMD_STORAGE_H_ 
#include <iosfwd>
#ifdef Vc_HAVE_NEON_ABI
#ifndef VC_SIMD_AARCH_H_
#define VC_SIMD_AARCH_H_ 
#include <limits>
#ifndef VC_DETAIL_CONST_H_
#define VC_DETAIL_CONST_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <int exponent, bool = (exponent < 0),
          bool = (exponent < std::numeric_limits<unsigned>::digits)>
struct double_2_pow_impl;
template <> struct double_2_pow_impl<0, false, true> {
    static constexpr double value = 1.;
};
template <int exponent> struct double_2_pow_impl<exponent, true, true> {
    static constexpr double value = 1. / double_2_pow_impl<-exponent>::value;
};
template <int exponent> struct double_2_pow_impl<exponent, false, true> {
    static constexpr double value = (1u << exponent);
};
template <int exponent> struct double_2_pow_impl<exponent, false, false> {
    static constexpr double value =
        (~0u + 1.) *
        double_2_pow_impl<exponent - std::numeric_limits<unsigned>::digits>::value;
};
template <int exponent>
constexpr double double_2_pow = double_2_pow_impl<exponent>::value;
template <int sign, unsigned long long mantissa, int exponent>
constexpr double double_const = (static_cast<double>((mantissa & 0x000fffffffffffffull) |
                                                     0x0010000000000000ull) /
                                 0x0010000000000000ull) *
                                double_2_pow<exponent> * sign;
template <int sign, unsigned int mantissa, int exponent>
constexpr float float_const = (float((mantissa & 0x007fffffu) | 0x00800000u) /
                               0x00800000u) *
                              float(double_2_pow<exponent>) * sign;
template <class T, class = void> struct constants {
    static constexpr float f32_pi_4 = float_const< 1, 0x490FDB, -1>;
    static constexpr float f32_pi_4_hi = float_const< 1, 0x491000, -1>;
    static constexpr float f32_pi_4_rem1 = float_const<-1, 0x157000, -19>;
    static constexpr float f32_pi_4_rem2 = float_const<-1, 0x6F4B9F, -32>;
    static constexpr float f32_1_16 = 0.0625f;
    static constexpr float f32_16 = 16.f;
    static constexpr float f32_cos_c0 = 4.166664568298827e-2f;
    static constexpr float f32_cos_c1 = -1.388731625493765e-3f;
    static constexpr float f32_cos_c2 = 2.443315711809948e-5f;
    static constexpr float f32_sin_c0 = -1.6666654611e-1f;
    static constexpr float f32_sin_c1 = 8.3321608736e-3f;
    static constexpr float f32_sin_c2 = -1.9515295891e-4f;
    static constexpr float f32_loss_threshold = 8192.f;
    static constexpr float f32_4_pi = float_const< 1, 0x22F983, 0>;
    static constexpr float f32_pi_2 = float_const< 1, 0x490FDB, 0>;
    static constexpr float f32_pi = float_const< 1, 0x490FDB, 1>;
    static constexpr float f32_atan_p0 = 8.05374449538e-2f;
    static constexpr float f32_atan_p1 = 1.38776856032e-1f;
    static constexpr float f32_atan_p2 = 1.99777106478e-1f;
    static constexpr float f32_atan_p3 = 3.33329491539e-1f;
    static constexpr float f32_atan_threshold_hi = 2.414213562373095f;
    static constexpr float f32_atan_threshold_lo = 0.414213562373095f;
    static constexpr float f32_pi_2_rem = float_const<-1, 0x3BBD2E, -25>;
    static constexpr float f32_small_asin_input = 1.e-4f;
    static constexpr float f32_large_asin_input = 0.f;
    static constexpr float f32_asin_c0_0 = 4.2163199048e-2f;
    static constexpr float f32_asin_c0_1 = 2.4181311049e-2f;
    static constexpr float f32_asin_c0_2 = 4.5470025998e-2f;
    static constexpr float f32_asin_c0_3 = 7.4953002686e-2f;
    static constexpr float f32_asin_c0_4 = 1.6666752422e-1f;
    static constexpr double f64_pi_4 = double_const< 1, 0x921fb54442d18, -1>;
    static constexpr double f64_pi_4_hi = double_const< 1, 0x921fb40000000, -1>;
    static constexpr double f64_pi_4_rem1 = double_const< 1, 0x4442d00000000, -25>;
    static constexpr double f64_pi_4_rem2 = double_const< 1, 0x8469898cc5170, -49>;
    static constexpr double f64_1_16 = 0.0625;
    static constexpr double f64_16 = 16.;
    static constexpr double f64_cos_c0 = double_const< 1, 0x555555555554b, -5 >;
    static constexpr double f64_cos_c1 = double_const<-1, 0x6c16c16c14f91, -10>;
    static constexpr double f64_cos_c2 = double_const< 1, 0xa01a019c844f5, -16>;
    static constexpr double f64_cos_c3 = double_const<-1, 0x27e4f7eac4bc6, -22>;
    static constexpr double f64_cos_c4 = double_const< 1, 0x1ee9d7b4e3f05, -29>;
    static constexpr double f64_cos_c5 = double_const<-1, 0x8fa49a0861a9b, -37>;
    static constexpr double f64_sin_c0 = double_const<-1, 0x5555555555548, -3 >;
    static constexpr double f64_sin_c1 = double_const< 1, 0x111111110f7d0, -7 >;
    static constexpr double f64_sin_c2 = double_const<-1, 0xa01a019bfdf03, -13>;
    static constexpr double f64_sin_c3 = double_const< 1, 0x71de3567d48a1, -19>;
    static constexpr double f64_sin_c4 = double_const<-1, 0xae5e5a9291f5d, -26>;
    static constexpr double f64_sin_c5 = double_const< 1, 0x5d8fd1fd19ccd, -33>;
    static constexpr double f64_4_pi = double_const< 1, 0x8BE60DB939105, 0 >;
    static constexpr double f64_pi_2 = double_const< 1, 0x921fb54442d18, 0 >;
    static constexpr double f64_pi = double_const< 1, 0x921fb54442d18, 1 >;
    static constexpr double f64_atan_p0 = double_const<-1, 0xc007fa1f72594, -1>;
    static constexpr double f64_atan_p1 = double_const<-1, 0x028545b6b807a, 4 >;
    static constexpr double f64_atan_p2 = double_const<-1, 0x2c08c36880273, 6 >;
    static constexpr double f64_atan_p3 = double_const<-1, 0xeb8bf2d05ba25, 6 >;
    static constexpr double f64_atan_p4 = double_const<-1, 0x03669fd28ec8e, 6 >;
    static constexpr double f64_atan_q0 = double_const< 1, 0x8dbc45b14603c, 4 >;
    static constexpr double f64_atan_q1 = double_const< 1, 0x4a0dd43b8fa25, 7 >;
    static constexpr double f64_atan_q2 = double_const< 1, 0xb0e18d2e2be3b, 8 >;
    static constexpr double f64_atan_q3 = double_const< 1, 0xe563f13b049ea, 8 >;
    static constexpr double f64_atan_q4 = double_const< 1, 0x8519efbbd62ec, 7 >;
    static constexpr double f64_atan_threshold_hi = double_const< 1, 0x3504f333f9de6, 1>;
    static constexpr double f64_atan_threshold_lo = 0.66;
    static constexpr double f64_pi_2_rem = double_const< 1, 0x1A62633145C07, -54>;
    static constexpr double f64_small_asin_input = 1.e-8;
    static constexpr double f64_large_asin_input = 0.625;
    static constexpr double f64_asin_c0_0 = double_const< 1, 0x84fc3988e9f08, -9>;
    static constexpr double f64_asin_c0_1 = double_const<-1, 0x2079259f9290f, -1>;
    static constexpr double f64_asin_c0_2 = double_const< 1, 0xbdff5baf33e6a, 2 >;
    static constexpr double f64_asin_c0_3 = double_const<-1, 0x991aaac01ab68, 4 >;
    static constexpr double f64_asin_c0_4 = double_const< 1, 0xc896240f3081d, 4 >;
    static constexpr double f64_asin_c1_0 = double_const<-1, 0x5f2a2b6bf5d8c, 4 >;
    static constexpr double f64_asin_c1_1 = double_const< 1, 0x26219af6a7f42, 7 >;
    static constexpr double f64_asin_c1_2 = double_const<-1, 0x7fe08959063ee, 8 >;
    static constexpr double f64_asin_c1_3 = double_const< 1, 0x56709b0b644be, 8 >;
    static constexpr double f64_asin_c2_0 = double_const< 1, 0x16b9b0bd48ad3, -8>;
    static constexpr double f64_asin_c2_1 = double_const<-1, 0x34341333e5c16, -1>;
    static constexpr double f64_asin_c2_2 = double_const< 1, 0x5c74b178a2dd9, 2 >;
    static constexpr double f64_asin_c2_3 = double_const<-1, 0x04331de27907b, 4 >;
    static constexpr double f64_asin_c2_4 = double_const< 1, 0x39007da779259, 4 >;
    static constexpr double f64_asin_c2_5 = double_const<-1, 0x0656c06ceafd5, 3 >;
    static constexpr double f64_asin_c3_0 = double_const<-1, 0xd7b590b5e0eab, 3 >;
    static constexpr double f64_asin_c3_1 = double_const< 1, 0x19fc025fe9054, 6 >;
    static constexpr double f64_asin_c3_2 = double_const<-1, 0x265bb6d3576d7, 7 >;
    static constexpr double f64_asin_c3_3 = double_const< 1, 0x1705684ffbf9d, 7 >;
    static constexpr double f64_asin_c3_4 = double_const<-1, 0x898220a3607ac, 5 >;
};
template <class Abi,class T> struct trig;
template <class Abi> struct trig<Abi, float> {
    using C = constants<Abi>;
    static Vc_INTRINSIC Vc_CONST simd<float, Abi> load(const float *arr)
    {
        return {arr, vector_aligned};
    }
    static Vc_INTRINSIC Vc_CONST simd<float, Abi> load(float arr)
    {
        return arr;
    }
    static Vc_INTRINSIC simd<float, Abi> pi_4() { return load(C::f32_pi_4); }
    static Vc_INTRINSIC simd<float, Abi> pi_4_hi() { return load(C::f32_pi_4_hi); }
    static Vc_INTRINSIC simd<float, Abi> pi_4_rem1() { return load(C::f32_pi_4_rem1); }
    static Vc_INTRINSIC simd<float, Abi> pi_4_rem2() { return load(C::f32_pi_4_rem2); }
    static Vc_INTRINSIC simd<float, Abi> _1_16() { return load(C::f32_1_16); }
    static Vc_INTRINSIC simd<float, Abi> _16() { return load(C::f32_16); }
    static Vc_INTRINSIC simd<float, Abi> cos_c0() { return load(C::f32_cos_c0); }
    static Vc_INTRINSIC simd<float, Abi> cos_c1() { return load(C::f32_cos_c1); }
    static Vc_INTRINSIC simd<float, Abi> cos_c2() { return load(C::f32_cos_c2); }
    static Vc_INTRINSIC simd<float, Abi> sin_c0() { return load(C::f32_sin_c0); }
    static Vc_INTRINSIC simd<float, Abi> sin_c1() { return load(C::f32_sin_c1); }
    static Vc_INTRINSIC simd<float, Abi> sin_c2() { return load(C::f32_sin_c2); }
    static Vc_INTRINSIC simd<float, Abi> loss_threshold() { return load(C::f32_loss_threshold); }
    static Vc_INTRINSIC simd<float, Abi> _4_pi() { return load(C::f32_4_pi); }
    static Vc_INTRINSIC simd<float, Abi> pi_2() { return load(C::f32_pi_2); }
    static Vc_INTRINSIC simd<float, Abi> pi() { return load(C::f32_pi); }
    static Vc_INTRINSIC simd<float, Abi> atan_p0() { return load(C::f32_atan_p0); }
    static Vc_INTRINSIC simd<float, Abi> atan_p1() { return load(C::f32_atan_p1); }
    static Vc_INTRINSIC simd<float, Abi> atan_p2() { return load(C::f32_atan_p2); }
    static Vc_INTRINSIC simd<float, Abi> atan_p3() { return load(C::f32_atan_p3); }
    static Vc_INTRINSIC simd<float, Abi> atan_threshold_hi() { return load(C::f32_atan_threshold_hi); }
    static Vc_INTRINSIC simd<float, Abi> atan_threshold_lo() { return load(C::f32_atan_threshold_lo); }
    static Vc_INTRINSIC simd<float, Abi> pi_2_rem() { return load(C::f32_pi_2_rem); }
    static Vc_INTRINSIC simd<float, Abi> small_asin_input() { return load(C::f32_small_asin_input); }
    static Vc_INTRINSIC simd<float, Abi> large_asin_input() { return load(C::f32_large_asin_input); }
    static Vc_INTRINSIC simd<float, Abi> asin_c0_0() { return load(C::f32_asin_c0_0); }
    static Vc_INTRINSIC simd<float, Abi> asin_c0_1() { return load(C::f32_asin_c0_1); }
    static Vc_INTRINSIC simd<float, Abi> asin_c0_2() { return load(C::f32_asin_c0_2); }
    static Vc_INTRINSIC simd<float, Abi> asin_c0_3() { return load(C::f32_asin_c0_3); }
    static Vc_INTRINSIC simd<float, Abi> asin_c0_4() { return load(C::f32_asin_c0_4); }
};
template <class Abi> struct trig<Abi, double> {
    using C = constants<Abi>;
    static Vc_INTRINSIC Vc_CONST simd<double, Abi> load(const double *arr)
    {
        return {arr, vector_aligned};
    }
    static Vc_INTRINSIC Vc_CONST simd<double, Abi> load(double arr)
    {
        return arr;
    }
    static Vc_INTRINSIC simd<double, Abi> pi_4() { return load(C::f64_pi_4); }
    static Vc_INTRINSIC simd<double, Abi> pi_4_hi() { return load(C::f64_pi_4_hi); }
    static Vc_INTRINSIC simd<double, Abi> pi_4_rem1() { return load(C::f64_pi_4_rem1); }
    static Vc_INTRINSIC simd<double, Abi> pi_4_rem2() { return load(C::f64_pi_4_rem2); }
    static Vc_INTRINSIC simd<double, Abi> _1_16() { return load(C::f64_1_16); }
    static Vc_INTRINSIC simd<double, Abi> _16() { return load(C::f64_16); }
    static Vc_INTRINSIC simd<double, Abi> cos_c0() { return load(C::f64_cos_c0); }
    static Vc_INTRINSIC simd<double, Abi> cos_c1() { return load(C::f64_cos_c1); }
    static Vc_INTRINSIC simd<double, Abi> cos_c2() { return load(C::f64_cos_c2); }
    static Vc_INTRINSIC simd<double, Abi> cos_c3() { return load(C::f64_cos_c3); }
    static Vc_INTRINSIC simd<double, Abi> cos_c4() { return load(C::f64_cos_c4); }
    static Vc_INTRINSIC simd<double, Abi> cos_c5() { return load(C::f64_cos_c5); }
    static Vc_INTRINSIC simd<double, Abi> sin_c0() { return load(C::f64_sin_c0); }
    static Vc_INTRINSIC simd<double, Abi> sin_c1() { return load(C::f64_sin_c1); }
    static Vc_INTRINSIC simd<double, Abi> sin_c2() { return load(C::f64_sin_c2); }
    static Vc_INTRINSIC simd<double, Abi> sin_c3() { return load(C::f64_sin_c3); }
    static Vc_INTRINSIC simd<double, Abi> sin_c4() { return load(C::f64_sin_c4); }
    static Vc_INTRINSIC simd<double, Abi> sin_c5() { return load(C::f64_sin_c5); }
    static Vc_INTRINSIC simd<double, Abi> loss_threshold() { return load(C::f64_loss_threshold); }
    static Vc_INTRINSIC simd<double, Abi> _4_pi() { return load(C::f64_4_pi); }
    static Vc_INTRINSIC simd<double, Abi> pi_2() { return load(C::f64_pi_2); }
    static Vc_INTRINSIC simd<double, Abi> pi() { return load(C::f64_pi); }
    static Vc_INTRINSIC simd<double, Abi> atan_p0() { return load(C::f64_atan_p0); }
    static Vc_INTRINSIC simd<double, Abi> atan_p1() { return load(C::f64_atan_p1); }
    static Vc_INTRINSIC simd<double, Abi> atan_p2() { return load(C::f64_atan_p2); }
    static Vc_INTRINSIC simd<double, Abi> atan_p3() { return load(C::f64_atan_p3); }
    static Vc_INTRINSIC simd<double, Abi> atan_threshold_hi() { return load(C::f64_atan_threshold_hi); }
    static Vc_INTRINSIC simd<double, Abi> atan_threshold_lo() { return load(C::f64_atan_threshold_lo); }
    static Vc_INTRINSIC simd<double, Abi> pi_2_rem() { return load(C::f64_pi_2_rem); }
    static Vc_INTRINSIC simd<double, Abi> small_asin_input() { return load(C::f64_small_asin_input); }
    static Vc_INTRINSIC simd<double, Abi> large_asin_input() { return load(C::f64_large_asin_input); }
    static Vc_INTRINSIC simd<double, Abi> asin_c0_0() { return load(C::f64_asin_c0_0); }
    static Vc_INTRINSIC simd<double, Abi> asin_c0_1() { return load(C::f64_asin_c0_1); }
    static Vc_INTRINSIC simd<double, Abi> asin_c0_2() { return load(C::f64_asin_c0_2); }
    static Vc_INTRINSIC simd<double, Abi> asin_c0_3() { return load(C::f64_asin_c0_3); }
    static Vc_INTRINSIC simd<double, Abi> asin_c0_4() { return load(C::f64_asin_c0_4); }
};
}
Vc_VERSIONED_NAMESPACE_END
#ifdef Vc_HAVE_SSE
#ifndef VC_DETAIL_X86_CONST_H_
#define VC_DETAIL_X86_CONST_H_ 
#if defined Vc_MSVC && Vc_MSVC < 191024903
#define Vc_WORK_AROUND_ICE 
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
#ifdef Vc_HAVE_SSE_ABI
#ifdef Vc_WORK_AROUND_ICE
namespace x86
{
namespace sse_const
{
#define constexpr const
#else
template <class X> struct constants<simd_abi::Sse, X> {
#endif
    alignas(64) static constexpr int absMaskFloat[4] = {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};
    alignas(16) static constexpr uint signMaskFloat[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
    alignas(16) static constexpr uint highMaskFloat[4] = {0xfffff000u, 0xfffff000u, 0xfffff000u, 0xfffff000u};
    alignas(16) static constexpr float oneFloat[4] = {1.f, 1.f, 1.f, 1.f};
    alignas(16) static constexpr short minShort[8] = {-0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000};
    alignas(16) static constexpr uchar one8[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    alignas(16) static constexpr ushort one16[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    alignas(16) static constexpr uint one32[4] = {1, 1, 1, 1};
    alignas(16) static constexpr ullong one64[2] = {1, 1};
    alignas(16) static constexpr double oneDouble[2] = {1., 1.};
    alignas(16) static constexpr ullong highMaskDouble[2] = {0xfffffffff8000000ull, 0xfffffffff8000000ull};
    alignas(16) static constexpr llong absMaskDouble[2] = {0x7fffffffffffffffll, 0x7fffffffffffffffll};
    alignas(16) static constexpr ullong signMaskDouble[2] = {0x8000000000000000ull, 0x8000000000000000ull};
    alignas(16) static constexpr ullong frexpMask[2] = {0xbfefffffffffffffull, 0xbfefffffffffffffull};
    alignas(16) static constexpr uint IndexesFromZero4[4] = { 0, 1, 2, 3 };
    alignas(16) static constexpr ushort IndexesFromZero8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    alignas(16) static constexpr uchar IndexesFromZero16[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    alignas(16) static constexpr uint AllBitsSet[4] = { 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU };
    alignas(16) static constexpr uchar cvti16_i08_shuffle[16] = {
        0, 2, 4, 6, 8, 10, 12, 14, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};
    using float4 = float[4];
    using double2 = double[2];
#define Vc_2(x_) {x_, x_}
#define Vc_4(x_) {x_, x_, x_, x_}
    alignas(64) static constexpr float4 f32_pi_4 = Vc_4((constants<simd_abi::scalar, X>::f32_pi_4));
    alignas(16) static constexpr float4 f32_pi_4_hi = Vc_4((constants<simd_abi::scalar, X>::f32_pi_4_hi));
    alignas(16) static constexpr float4 f32_pi_4_rem1 = Vc_4((constants<simd_abi::scalar, X>::f32_pi_4_rem1));
    alignas(16) static constexpr float4 f32_pi_4_rem2 = Vc_4((constants<simd_abi::scalar, X>::f32_pi_4_rem2));
    alignas(16) static constexpr float4 f32_1_16 = Vc_4(0.0625f);
    alignas(16) static constexpr float4 f32_16 = Vc_4(16.f);
    alignas(16) static constexpr float4 f32_cos_c0 = Vc_4(4.166664568298827e-2f);
    alignas(16) static constexpr float4 f32_cos_c1 = Vc_4(-1.388731625493765e-3f);
    alignas(16) static constexpr float4 f32_cos_c2 = Vc_4(2.443315711809948e-5f);
    alignas(16) static constexpr float4 f32_sin_c0 = Vc_4(-1.6666654611e-1f);
    alignas(16) static constexpr float4 f32_sin_c1 = Vc_4(8.3321608736e-3f);
    alignas(16) static constexpr float4 f32_sin_c2 = Vc_4(-1.9515295891e-4f);
    alignas(16) static constexpr float4 f32_loss_threshold = Vc_4(8192.f);
    alignas(16) static constexpr float4 f32_4_pi = Vc_4((float_const< 1, 0x22F983, 0>));
    alignas(16) static constexpr float4 f32_pi_2 = Vc_4((float_const< 1, 0x490FDB, 0>));
    alignas(16) static constexpr float4 f32_pi = Vc_4((float_const< 1, 0x490FDB, 1>));
    alignas(16) static constexpr float4 f32_atan_p0 = Vc_4(8.05374449538e-2f);
    alignas(16) static constexpr float4 f32_atan_p1 = Vc_4(1.38776856032e-1f);
    alignas(16) static constexpr float4 f32_atan_p2 = Vc_4(1.99777106478e-1f);
    alignas(16) static constexpr float4 f32_atan_p3 = Vc_4(3.33329491539e-1f);
    alignas(16) static constexpr float4 f32_atan_threshold_hi = Vc_4(2.414213562373095f);
    alignas(16) static constexpr float4 f32_atan_threshold_lo = Vc_4(0.414213562373095f);
    alignas(16) static constexpr float4 f32_pi_2_rem = Vc_4((float_const<-1, 0x3BBD2E, -25>));
    alignas(16) static constexpr float4 f32_small_asin_input = Vc_4(1.e-4f);
    alignas(16) static constexpr float4 f32_large_asin_input = Vc_4(0.f);
    alignas(16) static constexpr float4 f32_asin_c0_0 = Vc_4(4.2163199048e-2f);
    alignas(16) static constexpr float4 f32_asin_c0_1 = Vc_4(2.4181311049e-2f);
    alignas(16) static constexpr float4 f32_asin_c0_2 = Vc_4(4.5470025998e-2f);
    alignas(16) static constexpr float4 f32_asin_c0_3 = Vc_4(7.4953002686e-2f);
    alignas(16) static constexpr float4 f32_asin_c0_4 = Vc_4(1.6666752422e-1f);
    alignas(16) static constexpr double2 f64_pi_4 = Vc_2((double_const< 1, 0x921fb54442d18, -1>));
    alignas(16) static constexpr double2 f64_pi_4_hi = Vc_2((double_const< 1, 0x921fb40000000, -1>));
    alignas(16) static constexpr double2 f64_pi_4_rem1 = Vc_2((double_const< 1, 0x4442d00000000, -25>));
    alignas(16) static constexpr double2 f64_pi_4_rem2 = Vc_2((double_const< 1, 0x8469898cc5170, -49>));
    alignas(16) static constexpr double2 f64_1_16 = Vc_2(0.0625);
    alignas(16) static constexpr double2 f64_16 = Vc_2(16.);
    alignas(16) static constexpr double2 f64_cos_c0 = Vc_2((double_const< 1, 0x555555555554b, -5 >));
    alignas(16) static constexpr double2 f64_cos_c1 = Vc_2((double_const<-1, 0x6c16c16c14f91, -10>));
    alignas(16) static constexpr double2 f64_cos_c2 = Vc_2((double_const< 1, 0xa01a019c844f5, -16>));
    alignas(16) static constexpr double2 f64_cos_c3 = Vc_2((double_const<-1, 0x27e4f7eac4bc6, -22>));
    alignas(16) static constexpr double2 f64_cos_c4 = Vc_2((double_const< 1, 0x1ee9d7b4e3f05, -29>));
    alignas(16) static constexpr double2 f64_cos_c5 = Vc_2((double_const<-1, 0x8fa49a0861a9b, -37>));
    alignas(16) static constexpr double2 f64_sin_c0 = Vc_2((double_const<-1, 0x5555555555548, -3 >));
    alignas(16) static constexpr double2 f64_sin_c1 = Vc_2((double_const< 1, 0x111111110f7d0, -7 >));
    alignas(16) static constexpr double2 f64_sin_c2 = Vc_2((double_const<-1, 0xa01a019bfdf03, -13>));
    alignas(16) static constexpr double2 f64_sin_c3 = Vc_2((double_const< 1, 0x71de3567d48a1, -19>));
    alignas(16) static constexpr double2 f64_sin_c4 = Vc_2((double_const<-1, 0xae5e5a9291f5d, -26>));
    alignas(16) static constexpr double2 f64_sin_c5 = Vc_2((double_const< 1, 0x5d8fd1fd19ccd, -33>));
    alignas(16) static constexpr double2 f64_4_pi = Vc_2((double_const< 1, 0x8BE60DB939105, 0 >));
    alignas(16) static constexpr double2 f64_pi_2 = Vc_2((double_const< 1, 0x921fb54442d18, 0 >));
    alignas(16) static constexpr double2 f64_pi = Vc_2((double_const< 1, 0x921fb54442d18, 1 >));
    alignas(16) static constexpr double2 f64_atan_p0 = Vc_2((double_const<-1, 0xc007fa1f72594, -1>));
    alignas(16) static constexpr double2 f64_atan_p1 = Vc_2((double_const<-1, 0x028545b6b807a, 4 >));
    alignas(16) static constexpr double2 f64_atan_p2 = Vc_2((double_const<-1, 0x2c08c36880273, 6 >));
    alignas(16) static constexpr double2 f64_atan_p3 = Vc_2((double_const<-1, 0xeb8bf2d05ba25, 6 >));
    alignas(16) static constexpr double2 f64_atan_p4 = Vc_2((double_const<-1, 0x03669fd28ec8e, 6 >));
    alignas(16) static constexpr double2 f64_atan_q0 = Vc_2((double_const< 1, 0x8dbc45b14603c, 4 >));
    alignas(16) static constexpr double2 f64_atan_q1 = Vc_2((double_const< 1, 0x4a0dd43b8fa25, 7 >));
    alignas(16) static constexpr double2 f64_atan_q2 = Vc_2((double_const< 1, 0xb0e18d2e2be3b, 8 >));
    alignas(16) static constexpr double2 f64_atan_q3 = Vc_2((double_const< 1, 0xe563f13b049ea, 8 >));
    alignas(16) static constexpr double2 f64_atan_q4 = Vc_2((double_const< 1, 0x8519efbbd62ec, 7 >));
    alignas(16) static constexpr double2 f64_atan_threshold_hi = Vc_2((double_const< 1, 0x3504f333f9de6, 1>));
    alignas(16) static constexpr double2 f64_atan_threshold_lo = Vc_2(0.66);
    alignas(16) static constexpr double2 f64_pi_2_rem = Vc_2((double_const< 1, 0x1A62633145C07, -54>));
    alignas(16) static constexpr double2 f64_small_asin_input = Vc_2(1.e-8);
    alignas(16) static constexpr double2 f64_large_asin_input = Vc_2(0.625);
    alignas(16) static constexpr double2 f64_asin_c0_0 = Vc_2((double_const< 1, 0x84fc3988e9f08, -9>));
    alignas(16) static constexpr double2 f64_asin_c0_1 = Vc_2((double_const<-1, 0x2079259f9290f, -1>));
    alignas(16) static constexpr double2 f64_asin_c0_2 = Vc_2((double_const< 1, 0xbdff5baf33e6a, 2 >));
    alignas(16) static constexpr double2 f64_asin_c0_3 = Vc_2((double_const<-1, 0x991aaac01ab68, 4 >));
    alignas(16) static constexpr double2 f64_asin_c0_4 = Vc_2((double_const< 1, 0xc896240f3081d, 4 >));
    alignas(16) static constexpr double2 f64_asin_c1_0 = Vc_2((double_const<-1, 0x5f2a2b6bf5d8c, 4 >));
    alignas(16) static constexpr double2 f64_asin_c1_1 = Vc_2((double_const< 1, 0x26219af6a7f42, 7 >));
    alignas(16) static constexpr double2 f64_asin_c1_2 = Vc_2((double_const<-1, 0x7fe08959063ee, 8 >));
    alignas(16) static constexpr double2 f64_asin_c1_3 = Vc_2((double_const< 1, 0x56709b0b644be, 8 >));
    alignas(16) static constexpr double2 f64_asin_c2_0 = Vc_2((double_const< 1, 0x16b9b0bd48ad3, -8>));
    alignas(16) static constexpr double2 f64_asin_c2_1 = Vc_2((double_const<-1, 0x34341333e5c16, -1>));
    alignas(16) static constexpr double2 f64_asin_c2_2 = Vc_2((double_const< 1, 0x5c74b178a2dd9, 2 >));
    alignas(16) static constexpr double2 f64_asin_c2_3 = Vc_2((double_const<-1, 0x04331de27907b, 4 >));
    alignas(16) static constexpr double2 f64_asin_c2_4 = Vc_2((double_const< 1, 0x39007da779259, 4 >));
    alignas(16) static constexpr double2 f64_asin_c2_5 = Vc_2((double_const<-1, 0x0656c06ceafd5, 3 >));
    alignas(16) static constexpr double2 f64_asin_c3_0 = Vc_2((double_const<-1, 0xd7b590b5e0eab, 3 >));
    alignas(16) static constexpr double2 f64_asin_c3_1 = Vc_2((double_const< 1, 0x19fc025fe9054, 6 >));
    alignas(16) static constexpr double2 f64_asin_c3_2 = Vc_2((double_const<-1, 0x265bb6d3576d7, 7 >));
    alignas(16) static constexpr double2 f64_asin_c3_3 = Vc_2((double_const< 1, 0x1705684ffbf9d, 7 >));
    alignas(16) static constexpr double2 f64_asin_c3_4 = Vc_2((double_const<-1, 0x898220a3607ac, 5 >));
#undef Vc_2
#undef Vc_4
#ifdef Vc_WORK_AROUND_ICE
#undef constexpr
}
}
#else
};
template <class X> alignas(64) constexpr int constants<simd_abi::Sse, X>::absMaskFloat[4];
template <class X> alignas(16) constexpr uint constants<simd_abi::Sse, X>::signMaskFloat[4];
template <class X> alignas(16) constexpr uint constants<simd_abi::Sse, X>::highMaskFloat[4];
template <class X> alignas(16) constexpr float constants<simd_abi::Sse, X>::oneFloat[4];
template <class X> alignas(16) constexpr short constants<simd_abi::Sse, X>::minShort[8];
template <class X> alignas(16) constexpr uchar constants<simd_abi::Sse, X>::one8[16];
template <class X> alignas(16) constexpr ushort constants<simd_abi::Sse, X>::one16[8];
template <class X> alignas(16) constexpr uint constants<simd_abi::Sse, X>::one32[4];
template <class X> alignas(16) constexpr ullong constants<simd_abi::Sse, X>::one64[2];
template <class X> alignas(16) constexpr double constants<simd_abi::Sse, X>::oneDouble[2];
template <class X> alignas(16) constexpr ullong constants<simd_abi::Sse, X>::highMaskDouble[2];
template <class X> alignas(16) constexpr llong constants<simd_abi::Sse, X>::absMaskDouble[2];
template <class X> alignas(16) constexpr ullong constants<simd_abi::Sse, X>::signMaskDouble[2];
template <class X> alignas(16) constexpr ullong constants<simd_abi::Sse, X>::frexpMask[2];
template <class X> alignas(16) constexpr uint constants<simd_abi::Sse, X>::IndexesFromZero4[4];
template <class X> alignas(16) constexpr ushort constants<simd_abi::Sse, X>::IndexesFromZero8[8];
template <class X> alignas(16) constexpr uchar constants<simd_abi::Sse, X>::IndexesFromZero16[16];
template <class X> alignas(16) constexpr uint constants<simd_abi::Sse, X>::AllBitsSet[4];
template <class X> alignas(16) constexpr uchar constants<simd_abi::Sse, X>::cvti16_i08_shuffle[16];
template <class X> alignas(64) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi_4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi_4_hi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi_4_rem1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi_4_rem2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_1_16;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_16;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_cos_c0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_cos_c1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_cos_c2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_sin_c0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_sin_c1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_sin_c2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_loss_threshold;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_4_pi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_atan_p0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_atan_p1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_atan_p2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_atan_p3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_atan_threshold_hi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_atan_threshold_lo;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_pi_2_rem;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_small_asin_input;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_large_asin_input;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_asin_c0_0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_asin_c0_1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_asin_c0_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_asin_c0_3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::float4 constants<simd_abi::Sse, X>::f32_asin_c0_4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi_4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi_4_hi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi_4_rem1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi_4_rem2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_1_16;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_16;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_cos_c0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_cos_c1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_cos_c2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_cos_c3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_cos_c4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_cos_c5;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_sin_c0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_sin_c1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_sin_c2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_sin_c3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_sin_c4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_sin_c5;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_4_pi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_p0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_p1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_p2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_p3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_p4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_q0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_q1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_q2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_q3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_q4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_threshold_hi;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_atan_threshold_lo;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_pi_2_rem;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_small_asin_input;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_large_asin_input;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c0_0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c0_1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c0_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c0_3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c0_4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c1_0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c1_1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c1_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c1_3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c2_0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c2_1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c2_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c2_3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c2_4;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c2_5;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c3_0;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c3_1;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c3_2;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c3_3;
template <class X> alignas(16) constexpr typename constants<simd_abi::Sse, X>::double2 constants<simd_abi::Sse, X>::f64_asin_c3_4;
namespace x86
{
using sse_const = constants<simd_abi::Sse>;
}
#endif
#endif
#ifdef Vc_HAVE_AVX
#ifdef Vc_WORK_AROUND_ICE
namespace x86
{
namespace avx_const
{
#define constexpr const
#else
template <class X>
struct constants<simd_abi::Avx, X> : public constants<simd_abi::scalar, X> {
#endif
    alignas(64) static constexpr ullong IndexesFromZero64[ 4] = { 0, 1, 2, 3 };
    alignas(32) static constexpr uint IndexesFromZero32[ 8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    alignas(32) static constexpr ushort IndexesFromZero16[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    alignas(32) static constexpr uchar IndexesFromZero8 [32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    alignas(32) static constexpr uint AllBitsSet[8] = {
        0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU
    };
    static constexpr uint absMaskFloat[2] = { 0xffffffffu, 0x7fffffffu };
    static constexpr uint signMaskFloat[2] = { 0x0u, 0x80000000u };
    static constexpr uint highMaskFloat = 0xfffff000u;
    static constexpr float oneFloat = 1.f;
    alignas(float) static constexpr ushort one16[2] = { 1, 1 };
    alignas(float) static constexpr uchar one8[4] = { 1, 1, 1, 1 };
    static constexpr float _2_pow_31 = 1u << 31;
    static constexpr ullong highMaskDouble = 0xfffffffff8000000ull;
    static constexpr double oneDouble = 1.;
#ifdef Vc_WORK_AROUND_ICE
#undef constexpr
#undef Vc_WORK_AROUND_ICE
}
}
#else
};
template <class X> alignas(64) constexpr ullong constants<simd_abi::Avx, X>::IndexesFromZero64[ 4];
template <class X> alignas(32) constexpr uint constants<simd_abi::Avx, X>::IndexesFromZero32[ 8];
template <class X> alignas(32) constexpr ushort constants<simd_abi::Avx, X>::IndexesFromZero16[16];
template <class X> alignas(32) constexpr uchar constants<simd_abi::Avx, X>::IndexesFromZero8 [32];
template <class X> alignas(32) constexpr uint constants<simd_abi::Avx, X>::AllBitsSet[8];
template <class X> constexpr uint constants<simd_abi::Avx, X>::absMaskFloat[2];
template <class X> constexpr uint constants<simd_abi::Avx, X>::signMaskFloat[2];
template <class X> constexpr uint constants<simd_abi::Avx, X>::highMaskFloat;
template <class X> constexpr float constants<simd_abi::Avx, X>::oneFloat;
template <class X> alignas(float) constexpr ushort constants<simd_abi::Avx, X>::one16[2];
template <class X> alignas(float) constexpr uchar constants<simd_abi::Avx, X>::one8[4];
template <class X> constexpr float constants<simd_abi::Avx, X>::_2_pow_31;
template <class X> constexpr ullong constants<simd_abi::Avx, X>::highMaskDouble;
template <class X> constexpr double constants<simd_abi::Avx, X>::oneDouble;
namespace x86
{
using avx_const = constants<simd_abi::Avx>;
}
#endif
#endif
}
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#ifdef Vc_HAVE_NEON
#ifndef VC_DETAIL_AARCH_CONST_H_
#define VC_DETAIL_AARCH_CONST_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
#ifdef Vc_HAVE_NEON
#ifdef Vc_WORK_AROUND_ICE
namespace aarch
{
namespace neon_const
{
#define constexpr const
#else
template <class X> struct constants<simd_abi::neon, X> {
#endif
    alignas(64) static constexpr int absMaskFloat[4] = {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};
    alignas(16) static constexpr uint signMaskFloat[4] = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
    alignas(16) static constexpr uint highMaskFloat[4] = {0xfffff000u, 0xfffff000u, 0xfffff000u, 0xfffff000u};
    alignas(16) static constexpr float oneFloat[4] = {1.f, 1.f, 1.f, 1.f};
    alignas(16) static constexpr short minShort[8] = {-0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000};
    alignas(16) static constexpr uchar one8[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    alignas(16) static constexpr ushort one16[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    alignas(16) static constexpr uint one32[4] = {1, 1, 1, 1};
    alignas(16) static constexpr ullong one64[2] = {1, 1};
    alignas(16) static constexpr double oneDouble[2] = {1., 1.};
    alignas(16) static constexpr ullong highMaskDouble[2] = {0xfffffffff8000000ull, 0xfffffffff8000000ull};
    alignas(16) static constexpr llong absMaskDouble[2] = {0x7fffffffffffffffll, 0x7fffffffffffffffll};
    alignas(16) static constexpr ullong signMaskDouble[2] = {0x8000000000000000ull, 0x8000000000000000ull};
    alignas(16) static constexpr ullong frexpMask[2] = {0xbfefffffffffffffull, 0xbfefffffffffffffull};
    alignas(16) static constexpr uint IndexesFromZero4[4] = { 0, 1, 2, 3 };
    alignas(16) static constexpr ushort IndexesFromZero8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    alignas(16) static constexpr uchar IndexesFromZero16[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    alignas(16) static constexpr uint AllBitsSet[4] = { 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU };
#ifdef Vc_WORK_AROUND_ICE
#undef constexpr
}
}
#else
};
template <class X> alignas(64) constexpr int constants<simd_abi::neon, X>::absMaskFloat[4];
template <class X> alignas(16) constexpr uint constants<simd_abi::neon, X>::signMaskFloat[4];
template <class X> alignas(16) constexpr uint constants<simd_abi::neon, X>::highMaskFloat[4];
template <class X> alignas(16) constexpr float constants<simd_abi::neon, X>::oneFloat[4];
template <class X> alignas(16) constexpr short constants<simd_abi::neon, X>::minShort[8];
template <class X> alignas(16) constexpr uchar constants<simd_abi::neon, X>::one8[16];
template <class X> alignas(16) constexpr ushort constants<simd_abi::neon, X>::one16[8];
template <class X> alignas(16) constexpr uint constants<simd_abi::neon, X>::one32[4];
template <class X> alignas(16) constexpr ullong constants<simd_abi::neon, X>::one64[2];
template <class X> alignas(16) constexpr double constants<simd_abi::neon, X>::oneDouble[2];
template <class X> alignas(16) constexpr ullong constants<simd_abi::neon, X>::highMaskDouble[2];
template <class X> alignas(16) constexpr llong constants<simd_abi::neon, X>::absMaskDouble[2];
template <class X> alignas(16) constexpr ullong constants<simd_abi::neon, X>::signMaskDouble[2];
template <class X> alignas(16) constexpr ullong constants<simd_abi::neon, X>::frexpMask[2];
template <class X> alignas(16) constexpr uint constants<simd_abi::neon, X>::IndexesFromZero4[4];
template <class X> alignas(16) constexpr ushort constants<simd_abi::neon, X>::IndexesFromZero8[8];
template <class X> alignas(16) constexpr uchar constants<simd_abi::neon, X>::IndexesFromZero16[16];
template <class X> alignas(16) constexpr uint constants<simd_abi::neon, X>::AllBitsSet[4];
namespace aarch
{
using neon_const = constants<simd_abi::neon>;
}
#endif
#endif
}
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#endif
#include <arm_neon.h>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <> struct builtin_type< double , 16> { typedef double type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< float , 16> { typedef float type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< long long, 16> { typedef long long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned long long, 16> { typedef unsigned long long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< long , 16> { typedef long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned long , 16> { typedef unsigned long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< int , 16> { typedef int type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned int , 16> { typedef unsigned int type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< short , 16> { typedef short type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned short , 16> { typedef unsigned short type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< char , 16> { typedef char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned char , 16> { typedef unsigned char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< signed char , 16> { typedef signed char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< bool , 16> { typedef unsigned char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< double , 32> { typedef double type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< float , 32> { typedef float type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< long long, 32> { typedef long long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned long long, 32> { typedef unsigned long long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< long , 32> { typedef long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned long , 32> { typedef unsigned long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< int , 32> { typedef int type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned int , 32> { typedef unsigned int type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< short , 32> { typedef short type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned short , 32> { typedef unsigned short type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< char , 32> { typedef char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned char , 32> { typedef unsigned char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< signed char , 32> { typedef signed char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< bool , 32> { typedef unsigned char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< double , 64> { typedef double type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< float , 64> { typedef float type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< long long, 64> { typedef long long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned long long, 64> { typedef unsigned long long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< long , 64> { typedef long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned long , 64> { typedef unsigned long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< int , 64> { typedef int type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned int , 64> { typedef unsigned int type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< short , 64> { typedef short type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned short , 64> { typedef unsigned short type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< char , 64> { typedef char type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned char , 64> { typedef unsigned char type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< signed char , 64> { typedef signed char type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< bool , 64> { typedef unsigned char type [[gnu::vector_size(64)]]; };
#endif
template <> struct intrinsic_type<double, 16> { using type = float64x2_t; };
template <> struct intrinsic_type<int, 16> { using type = int32x4_t; };
template <> struct is_intrinsic<float32x4_t> : public std::true_type {};
template <> struct is_intrinsic<float64x2_t> : public std::true_type {};
template <> struct is_intrinsic<int32x4_t> : public std::true_type {};
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <> struct is_builtin_vector<builtin_type<float, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type<double, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< llong, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type<ullong, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< long, 16 / sizeof( long)>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< ulong, 16 / sizeof(ulong)>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< int, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< uint, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< short, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type<ushort, 8>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< schar,16>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type< uchar,16>> : public std::true_type {};
#endif
namespace aarch
{
using aarch_const = constants<simd_abi::neon>;
template<typename T> Vc_INTRINSIC_L T intrin_cast(float32x4_t v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(int32x4_t v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(float64x2_t v) Vc_INTRINSIC_R;
template<> Vc_INTRINSIC float32x4_t intrin_cast(float32x4_t v) { return v; }
template<> Vc_INTRINSIC float32x4_t intrin_cast(int32x4_t v) { return vcvtq_f32_s32(v); }
template<> Vc_INTRINSIC float32x4_t intrin_cast(float64x2_t v) { return vreinterpretq_f32_f64(v); }
template<> Vc_INTRINSIC int32x4_t intrin_cast(float32x4_t v) { return vcvtq_s32_f32(v); }
template<> Vc_INTRINSIC int32x4_t intrin_cast(int32x4_t v) { return v; }
template<> Vc_INTRINSIC int32x4_t intrin_cast(float64x2_t v) { return vreinterpretq_s32_f64(v); }
template<> Vc_INTRINSIC float64x2_t intrin_cast(float32x4_t v) { return vreinterpretq_f64_f32(v); }
template<> Vc_INTRINSIC float64x2_t intrin_cast(int32x4_t v) { return vreinterpretq_f64_s32(v); }
template<> Vc_INTRINSIC float64x2_t intrin_cast(float64x2_t v) { return v; }
template <typename V> Vc_INTRINSIC_L Vc_CONST_L V allone() Vc_INTRINSIC_R Vc_CONST_R;
template <> Vc_INTRINSIC Vc_CONST float32x4_t allone<float32x4_t>()
{
    return vld1q_f32(reinterpret_cast<const float *>(neon_const::AllBitsSet));
}
template <> Vc_INTRINSIC Vc_CONST int32x4_t allone<int32x4_t>()
{
    return vld1q_s32(reinterpret_cast<const int32_t *>(neon_const::AllBitsSet));
}
template <> Vc_INTRINSIC Vc_CONST float64x2_t allone<float64x2_t>()
{
    return vld1q_f64(reinterpret_cast<const double *>(neon_const::AllBitsSet));
}
template <typename V> Vc_INTRINSIC_L Vc_CONST_L V zero() Vc_INTRINSIC_R Vc_CONST_R;
template<> Vc_INTRINSIC Vc_CONST float32x4_t zero<float32x4_t >() { return vdupq_n_f32(0); }
template<> Vc_INTRINSIC Vc_CONST int32x4_t zero<int32x4_t>() { return vdupq_n_s32(0); }
template<> Vc_INTRINSIC Vc_CONST float64x2_t zero<float64x2_t>() { return vdupq_n_f64(0); }
Vc_INTRINSIC Vc_CONST float32x4_t one16( float) { return vld1q_f32(neon_const::oneFloat); }
Vc_INTRINSIC Vc_CONST float64x2_t one16(double) { return vld1q_f64(neon_const::oneDouble); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( schar) { return vld1q_s32(reinterpret_cast<const int32_t *>(neon_const::one8)); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( uchar) { return one16(schar()); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( short) { return vld1q_s32(reinterpret_cast<const int32_t *>(neon_const::one16)); }
Vc_INTRINSIC Vc_CONST int32x4_t one16(ushort) { return one16(short()); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( int) { return vld1q_s32(reinterpret_cast<const int32_t *>(neon_const::one32)); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( uint) { return one16(int()); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( llong) { return vld1q_s32(reinterpret_cast<const int32_t *>(neon_const::one64)); }
Vc_INTRINSIC Vc_CONST int32x4_t one16(ullong) { return one16(llong()); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( long) { return one16(equal_int_type_t<long>()); }
Vc_INTRINSIC Vc_CONST int32x4_t one16( ulong) { return one16(equal_int_type_t<ulong>()); }
Vc_INTRINSIC Vc_CONST float64x2_t signmask16(double){ return vld1q_f64(reinterpret_cast<const double *>(neon_const::signMaskDouble)); }
Vc_INTRINSIC Vc_CONST float32x4_t signmask16( float){ return vld1q_f32(reinterpret_cast<const float *>(neon_const::signMaskFloat)); }
Vc_INTRINSIC Vc_CONST float32x4_t set(float x0, float x1, float x2, float x3)
{
    float __attribute__((aligned(16))) data[4] = { x0, x1, x2, x3 };
 return vld1q_f32(data);
}
Vc_INTRINSIC Vc_CONST float64x2_t set(double x0, double x1)
{
 double __attribute__((aligned(16))) data[2] = { x0, x1 };
 return vld1q_f64(data);
}
Vc_INTRINSIC Vc_CONST int32x4_t set(int x0, int x1, int x2, int x3)
{
    int __attribute__((aligned(16))) data[4] = { x0, x1, x2, x3 };
 return vld1q_s32(data);
}
Vc_INTRINSIC Vc_CONST uint32x4_t set(uint x0, uint x1, uint x2, uint x3)
{
    uint __attribute__((aligned(16))) data[4] = { x0, x1, x2, x3 };
 return vld1q_u32(data);
}
Vc_INTRINSIC Vc_CONST int16x8_t set(short x0, short x1, short x2, short x3, short x4,
                                  short x5, short x6, short x7)
{
    short __attribute__((aligned(16))) data[8] = { x0, x1, x2, x3, x4, x5, x6, x7 };
 return vld1q_s16(data);
}
Vc_INTRINSIC Vc_CONST uint16x8_t set(ushort x0, ushort x1, ushort x2, ushort x3, ushort x4,
                                  ushort x5, ushort x6, ushort x7)
{
    ushort __attribute__((aligned(16))) data[8] = { x0, x1, x2, x3, x4, x5, x6, x7 };
 return vld1q_u16(data);
}
Vc_INTRINSIC Vc_CONST int8x16_t set(schar x0, schar x1, schar x2, schar x3, schar x4,
                                  schar x5, schar x6, schar x7, schar x8, schar x9,
                                  schar x10, schar x11, schar x12, schar x13, schar x14,
                                  schar x15)
{
    schar __attribute__((aligned(16))) data[16] = { x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15 };
 return vld1q_s8(data);
}
Vc_INTRINSIC Vc_CONST uint8x16_t set(uchar x0, uchar x1, uchar x2, uchar x3, uchar x4,
                                  uchar x5, uchar x6, uchar x7, uchar x8, uchar x9,
                                  uchar x10, uchar x11, uchar x12, uchar x13, uchar x14,
                                  uchar x15)
{
    uchar __attribute__((aligned(16))) data[16] = { x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15 };
    return vld1q_u8(data);
}
template <typename... Ts> Vc_INTRINSIC Vc_CONST auto set(Ts... args)
{
    return set(static_cast<equal_int_type_t<Ts>>(args)...);
}
Vc_INTRINSIC float32x4_t broadcast16( float x) { return vdupq_n_f32(x); }
Vc_INTRINSIC float64x2_t broadcast16(double x) { return vdupq_n_f64(x); }
Vc_INTRINSIC int8x16_t broadcast16( schar x) { return vdupq_n_s8(x); }
Vc_INTRINSIC uint8x16_t broadcast16( uchar x) { return vdupq_n_u8(x); }
Vc_INTRINSIC int16x8_t broadcast16( short x) { return vdupq_n_s16(x); }
Vc_INTRINSIC uint16x8_t broadcast16(ushort x) { return vdupq_n_u16(x); }
Vc_INTRINSIC int32x4_t broadcast16( int x) { return vdupq_n_s32(x); }
Vc_INTRINSIC uint32x4_t broadcast16( uint x) { return vdupq_n_u32(x); }
Vc_INTRINSIC Vc_CONST float32x4_t blend(float32x4_t mask, float32x4_t at0, float32x4_t at1){}
Vc_INTRINSIC Vc_CONST float64x2_t blend(float64x2_t mask, float64x4_t at0, float64x2_t at1){}
Vc_INTRINSIC Vc_CONST int32x4_t blend(int32x4_t mask, int32x4_t at0, int32x4_t at1){}
Vc_INTRINSIC Vc_CONST int movemask_f32(float32x4_t a){}
Vc_INTRINSIC Vc_CONST int movemask_f64(float64x2_t a){}
Vc_INTRINSIC Vc_CONST int movemask_s32(int32x4_t a){}
Vc_INTRINSIC Vc_CONST int movemask_s16(int16x8_t a){}
Vc_INTRINSIC Vc_CONST int movemask_s8(int8x16_t a){}
Vc_ALWAYS_INLINE Vc_CONST int32x4_t negate(int32x4_t v, std::integral_constant<std::size_t, 4>)
{
 return vnegq_s32(v);
}
Vc_ALWAYS_INLINE Vc_CONST int32x4_t negate(int32x4_t v, std::integral_constant<std::size_t, 2>)
{
 return vnegq_s32(v);
}
Vc_INTRINSIC int64x2_t xor_(int64x2_t a, int64x2_t b) { return veorq_s64(a, b); }
Vc_INTRINSIC int32x4_t xor_(int32x4_t a, int32x4_t b) { return veorq_s32(a, b); }
Vc_INTRINSIC int64x2_t or_(int64x2_t a, int64x2_t b) { return vorrq_s64(a, b); }
Vc_INTRINSIC int32x4_t or_(int32x4_t a, int32x4_t b) { return vorrq_s32(a, b); }
Vc_INTRINSIC int64x2_t and_(int64x2_t a, int64x2_t b) { return vandq_s64(a, b); }
Vc_INTRINSIC int32x4_t and_(int32x4_t a, int32x4_t b) { return vandq_s32(a, b); }
Vc_INTRINSIC int64x2_t andnot_(int64x2_t a, int64x2_t b) { return vbicq_s64(a, b); }
Vc_INTRINSIC int32x4_t andnot_(int32x4_t a, int32x4_t b) { return vbicq_s32(a, b); }
template <int n> Vc_INTRINSIC int64x2_t shift_left(int64x2_t v) { return vshlq_n_s64(v, n); }
template <int n> Vc_INTRINSIC int32x4_t shift_left(int32x4_t v) { return vshlq_n_s32(v, n); }
template <int n> Vc_INTRINSIC int64x2_t shift_right(int64x2_t v) { return vshrq_n_s64(v, n); }
template <int n> Vc_INTRINSIC int32x4_t shift_right(int32x4_t v) { return vshrq_n_s32(v, n); }
Vc_INTRINSIC Vc_CONST unsigned int popcnt4(unsigned int n) {}
Vc_INTRINSIC Vc_CONST unsigned int popcnt8(unsigned int n) {}
Vc_INTRINSIC Vc_CONST unsigned int popcnt16(unsigned int n) {}
Vc_INTRINSIC Vc_CONST unsigned int popcnt32(unsigned int n) {}
template <size_t Size> int mask_count(float32x4_t );
template <size_t Size> int mask_count(int32x4_t);
template <size_t Size> int mask_count(float64x2_t);
template<> Vc_INTRINSIC Vc_CONST int mask_count<2>(float64x2_t k)
{
    int mask = movemask_f64(k);
    return (mask & 1) + (mask >> 1);
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<2>(int32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_count<4>(float32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_count<4>(int32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_count<8>(int32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_count<16>(int32x4_t k) {}
template <size_t Size> inline int mask_to_int(int32x4_t) { static_assert(Size == Size, "Size value not implemented"); return 0; }
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<2>(int32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(int32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<8>(int32x4_t k) {}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<16>(int32x4_t k) {}
Vc_INTRINSIC float32x4_t load16(const float *mem, when_aligned<16>)
{
    return vld1q_f32(mem);
}
Vc_INTRINSIC float32x4_t load16(const float *mem, when_unaligned<16>)
{
    return vld1q_f32(mem);
}
Vc_INTRINSIC float64x2_t load16(const double *mem, when_aligned<16>)
{
    return vld1q_f64(mem);
}
Vc_INTRINSIC float64x2_t load16(const double *mem, when_unaligned<16>)
{
    return vld1q_f64(mem);
}
template <class T> Vc_INTRINSIC int32x4_t load16(const T *mem, when_aligned<16>)
{
    static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
    return vld1q_s32(reinterpret_cast<const int32_t *>(mem));
}
template <class T> Vc_INTRINSIC int32x4_t load16(const T *mem, when_unaligned<16>)
{
    static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
    return vld1q_s32(reinterpret_cast<const int32_t *>(mem));
}
template <class Flags> Vc_INTRINSIC void store4(float32x4_t v, float *mem, Flags)
{
    *mem = vgetq_lane_f32(v, 0);
}
template <class Flags> Vc_INTRINSIC void store8(float32x4_t v, float *mem, Flags) {}
Vc_INTRINSIC void store16(float32x4_t v, float *mem, when_aligned<16>)
{
    vst1q_f32(mem, v);
}
Vc_INTRINSIC void store16(float32x4_t v, float *mem, when_unaligned<16>)
{
    vst1q_f32(mem, v);
}
template <class Flags> Vc_INTRINSIC void store8(float64x2_t v, double *mem, Flags) {}
Vc_INTRINSIC void store16(float64x2_t v, double *mem, when_aligned<16>)
{
    vst1q_f64(mem, v);
}
Vc_INTRINSIC void store16(float64x2_t v, double *mem, when_unaligned<16>)
{
    vst1q_f64(mem, v);
}
template <class T, class Flags> Vc_INTRINSIC void store2(int32x4_t v, T *mem, Flags)
{
    static_assert(std::is_integral<T>::value && sizeof(T) <= 2,
                  "store4<T> is only intended for integral T with sizeof(T) <= 2");
    *reinterpret_cast<may_alias<ushort> *>(mem) = uint(vgetq_lane_s32(v, 0));
}
template <class T, class Flags> Vc_INTRINSIC void store4(int32x4_t v, T *mem, Flags)
{
    static_assert(std::is_integral<T>::value && sizeof(T) <= 4,
                  "store4<T> is only intended for integral T with sizeof(T) <= 4");
    *reinterpret_cast<may_alias<int> *>(mem) = vgetq_lane_s32(v, 0);
}
template <class T, class Flags> Vc_INTRINSIC void store8(int32x4_t v, T *mem, Flags)
{
    static_assert(std::is_integral<T>::value, "store8<T> is only intended for integral T");
    *mem = (int32x4_t)vsetq_lane_s64((int64_t)vget_low_s32(v), *(int64x2_t*)v, 0);
}
template <class T> Vc_INTRINSIC void store16(int32x4_t v, T *mem, when_aligned<16>)
{
    static_assert(std::is_integral<T>::value, "store16<T> is only intended for integral T");
    vst1q_s32(reinterpret_cast<int32_t *>(mem), v);
}
template <class T> Vc_INTRINSIC void store16(int32x4_t v, T *mem, when_unaligned<16>)
{
    static_assert(std::is_integral<T>::value, "store16<T> is only intended for integral T");
    vst1q_s32(reinterpret_cast<int32_t *>(mem), v);
}
}
using namespace aarch;
}
Vc_VERSIONED_NAMESPACE_END
#endif
#elif defined Vc_HAVE_SSE_ABI
#ifndef VC_SIMD_X86_H_
#define VC_SIMD_X86_H_ 
#include <limits>
#include <climits>
#include <cstring>
#ifdef Vc_HAVE_SSE
#ifdef Vc_MSVC
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
#ifdef Vc_HAVE_AVX512F
template <> struct bool_storage_member_type< 2> { using type = __mmask8 ; };
template <> struct bool_storage_member_type< 4> { using type = __mmask8 ; };
template <> struct bool_storage_member_type< 8> { using type = __mmask8 ; };
template <> struct bool_storage_member_type<16> { using type = __mmask16; };
template <> struct bool_storage_member_type<32> { using type = __mmask32; };
template <> struct bool_storage_member_type<64> { using type = __mmask64; };
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
#ifdef Vc_GCC
template <class T, size_t Bytes>
struct builtin_type<
    T, Bytes,
    detail::void_t<std::enable_if_t<detail::conjunction_v<
        detail::is_equal_to<Bytes % sizeof(T), 0>, detail::is_vectorizable<T>>>>> {
    using type[[gnu::vector_size(Bytes)]] = T;
};
#else
template <> struct builtin_type< char , 1> { typedef char type [[gnu::vector_size( 1)]]; };
template <> struct builtin_type<unsigned char , 1> { typedef unsigned char type [[gnu::vector_size( 1)]]; };
template <> struct builtin_type< signed char , 1> { typedef signed char type [[gnu::vector_size( 1)]]; };
template <> struct builtin_type< short , 2> { typedef short type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type<unsigned short , 2> { typedef unsigned short type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type< char , 2> { typedef char type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type<unsigned char , 2> { typedef unsigned char type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type< signed char , 2> { typedef signed char type [[gnu::vector_size( 2)]]; };
#if WCHAR_MAX < 0x10000
template <> struct builtin_type< wchar_t , 2> { typedef wchar_t type [[gnu::vector_size( 2)]]; };
#endif
template <> struct builtin_type< char16_t , 2> { typedef char16_t type [[gnu::vector_size( 2)]]; };
template <> struct builtin_type< float , 4> { typedef float type [[gnu::vector_size( 4)]]; };
#if LONG_MAX == INT_MAX
template <> struct builtin_type< long , 4> { typedef long type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned long , 4> { typedef unsigned long type [[gnu::vector_size( 4)]]; };
#endif
template <> struct builtin_type< int , 4> { typedef int type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned int , 4> { typedef unsigned int type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< short , 4> { typedef short type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned short , 4> { typedef unsigned short type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< char , 4> { typedef char type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type<unsigned char , 4> { typedef unsigned char type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< signed char , 4> { typedef signed char type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< wchar_t , 4> { typedef wchar_t type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< char16_t , 4> { typedef char16_t type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< char32_t , 4> { typedef char32_t type [[gnu::vector_size( 4)]]; };
template <> struct builtin_type< double , 8> { typedef double type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< float , 8> { typedef float type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< long long, 8> { typedef long long type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned long long, 8> { typedef unsigned long long type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< long , 8> { typedef long type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned long , 8> { typedef unsigned long type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< int , 8> { typedef int type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned int , 8> { typedef unsigned int type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< short , 8> { typedef short type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned short , 8> { typedef unsigned short type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< char , 8> { typedef char type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type<unsigned char , 8> { typedef unsigned char type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< signed char , 8> { typedef signed char type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< wchar_t , 8> { typedef wchar_t type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< char16_t , 8> { typedef char16_t type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< char32_t , 8> { typedef char32_t type [[gnu::vector_size( 8)]]; };
template <> struct builtin_type< double , 16> { typedef double type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< float , 16> { typedef float type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< long long, 16> { typedef long long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned long long, 16> { typedef unsigned long long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< long , 16> { typedef long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned long , 16> { typedef unsigned long type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< int , 16> { typedef int type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned int , 16> { typedef unsigned int type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< short , 16> { typedef short type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned short , 16> { typedef unsigned short type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< char , 16> { typedef char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type<unsigned char , 16> { typedef unsigned char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< signed char , 16> { typedef signed char type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< wchar_t , 16> { typedef wchar_t type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< char16_t , 16> { typedef char16_t type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< char32_t , 16> { typedef char32_t type [[gnu::vector_size(16)]]; };
template <> struct builtin_type< double , 32> { typedef double type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< float , 32> { typedef float type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< long long, 32> { typedef long long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned long long, 32> { typedef unsigned long long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< long , 32> { typedef long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned long , 32> { typedef unsigned long type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< int , 32> { typedef int type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned int , 32> { typedef unsigned int type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< short , 32> { typedef short type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned short , 32> { typedef unsigned short type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< char , 32> { typedef char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type<unsigned char , 32> { typedef unsigned char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< signed char , 32> { typedef signed char type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< wchar_t , 32> { typedef wchar_t type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< char16_t , 32> { typedef char16_t type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< char32_t , 32> { typedef char32_t type [[gnu::vector_size(32)]]; };
template <> struct builtin_type< double , 64> { typedef double type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< float , 64> { typedef float type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< long long, 64> { typedef long long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned long long, 64> { typedef unsigned long long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< long , 64> { typedef long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned long , 64> { typedef unsigned long type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< int , 64> { typedef int type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned int , 64> { typedef unsigned int type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< short , 64> { typedef short type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned short , 64> { typedef unsigned short type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< char , 64> { typedef char type [[gnu::vector_size(64)]]; };
template <> struct builtin_type<unsigned char , 64> { typedef unsigned char type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< signed char , 64> { typedef signed char type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< wchar_t , 64> { typedef wchar_t type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< char16_t , 64> { typedef char16_t type [[gnu::vector_size(64)]]; };
template <> struct builtin_type< char32_t , 64> { typedef char32_t type [[gnu::vector_size(64)]]; };
#endif
#endif
template <class T>
using void_if_integral_t = detail::void_t<std::enable_if_t<
    detail::all<std::is_integral<T>, detail::is_vectorizable<T>>::value>>;
#if defined Vc_HAVE_AVX512F
template <> struct intrinsic_type<double, 64, void> { using type = __m512d; };
template <> struct intrinsic_type< float, 64, void> { using type = __m512; };
template <typename T> struct intrinsic_type<T, 64, void_if_integral_t<T>> { using type = __m512i; };
#endif
#if defined Vc_HAVE_AVX
template <> struct intrinsic_type<double, 32, void> { using type = __m256d; };
template <> struct intrinsic_type< float, 32, void> { using type = __m256; };
template <typename T> struct intrinsic_type<T, 32, void_if_integral_t<T>> { using type = __m256i; };
#endif
#if defined Vc_HAVE_SSE
template <> struct intrinsic_type< float, 16, void> { using type = __m128; };
template <> struct intrinsic_type< float, 8, void> { using type = __m128; };
template <> struct intrinsic_type< float, 4, void> { using type = __m128; };
#endif
#if defined Vc_HAVE_SSE2
template <> struct intrinsic_type<double, 16, void> { using type = __m128d; };
template <> struct intrinsic_type<double, 8, void> { using type = __m128d; };
template <typename T> struct intrinsic_type<T, 16, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T, 8, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T, 4, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T, 2, void_if_integral_t<T>> { using type = __m128i; };
template <typename T> struct intrinsic_type<T, 1, void_if_integral_t<T>> { using type = __m128i; };
#endif
template <> struct is_intrinsic<__m128> : public std::true_type {};
static_assert(is_intrinsic_v<intrinsic_type_t<float, 4>>, "");
#ifdef Vc_HAVE_SSE2
template <> struct is_intrinsic<__m128d> : public std::true_type {};
template <> struct is_intrinsic<__m128i> : public std::true_type {};
static_assert(is_intrinsic_v<intrinsic_type_t<double, 2>>, "");
static_assert(is_intrinsic_v<intrinsic_type_t<int, 4>>, "");
#endif
#ifdef Vc_HAVE_AVX
template <> struct is_intrinsic<__m256 > : public std::true_type {};
template <> struct is_intrinsic<__m256d> : public std::true_type {};
template <> struct is_intrinsic<__m256i> : public std::true_type {};
static_assert(is_intrinsic_v<intrinsic_type_t<float, 8>>, "");
static_assert(is_intrinsic_v<intrinsic_type_t<double, 4>>, "");
static_assert(is_intrinsic_v<intrinsic_type_t<int, 8>>, "");
#endif
#ifdef Vc_HAVE_AVX512F
template <> struct is_intrinsic<__m512 > : public std::true_type {};
template <> struct is_intrinsic<__m512d> : public std::true_type {};
template <> struct is_intrinsic<__m512i> : public std::true_type {};
#endif
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
template <> struct is_builtin_vector<builtin_type_t< long, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 4>> : public std::true_type {};
#endif
template <> struct is_builtin_vector<builtin_type_t< long, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< long, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< int, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< int, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< int, 1>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uint, 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uint, 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uint, 1>> : public std::true_type {};
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
#endif
#ifdef Vc_HAVE_AVX
template <> struct is_builtin_vector<builtin_type_t< float, 4 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<double, 2 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< llong, 2 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ullong, 2 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< long, 16 / sizeof( long) * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 16 / sizeof(ulong) * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< int, 4 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uint, 4 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 8 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 8 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar,16 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar,16 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< wchar_t, 16 / sizeof(wchar_t) * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 8 * 2>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char32_t, 4 * 2>> : public std::true_type {};
#endif
#ifdef Vc_HAVE_AVX512F
template <> struct is_builtin_vector<builtin_type_t< float, 4 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<double, 2 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< llong, 2 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ullong, 2 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< long, 16 / sizeof( long) * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< ulong, 16 / sizeof(ulong) * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< int, 4 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uint, 4 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< short, 8 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<ushort, 8 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< schar,16 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< uchar,16 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t< wchar_t, 16 / sizeof(wchar_t) * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char16_t, 8 * 4>> : public std::true_type {};
template <> struct is_builtin_vector<builtin_type_t<char32_t, 4 * 4>> : public std::true_type {};
#endif
#endif
namespace x86
{
#ifdef Vc_HAVE_AVX
#if defined Vc_MSVC || defined Vc_CLANG || defined Vc_APPLECLANG
Vc_INTRINSIC Vc_CONST __m256 zeroExtend(__m128 v) { return _mm256_permute2f128_ps (_mm256_castps128_ps256(v), _mm256_castps128_ps256(v), 0x80); }
Vc_INTRINSIC Vc_CONST __m256i zeroExtend(__m128i v) { return _mm256_permute2f128_si256(_mm256_castsi128_si256(v), _mm256_castsi128_si256(v), 0x80); }
Vc_INTRINSIC Vc_CONST __m256d zeroExtend(__m128d v) { return _mm256_permute2f128_pd (_mm256_castpd128_pd256(v), _mm256_castpd128_pd256(v), 0x80); }
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m512 zeroExtend(__m256 v) { return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_setzero_pd(), _mm256_castps_pd(v), 0x0)); }
Vc_INTRINSIC Vc_CONST __m512d zeroExtend(__m256d v) { return _mm512_insertf64x4(_mm512_setzero_pd(), v, 0x0); }
Vc_INTRINSIC Vc_CONST __m512i zeroExtend(__m256i v) { return _mm512_inserti64x4(_mm512_setzero_si512(), v, 0x0); }
Vc_INTRINSIC Vc_CONST __m512 zeroExtend64(__m128 v) { return _mm512_insertf32x4(_mm512_setzero_ps(), v, 0x0); }
Vc_INTRINSIC Vc_CONST __m512d zeroExtend64(__m128d v) { return _mm512_castps_pd(_mm512_insertf32x4(_mm512_setzero_ps(), _mm_castpd_ps(v), 0x0)); }
Vc_INTRINSIC Vc_CONST __m512i zeroExtend64(__m128i v) { return _mm512_inserti32x4(_mm512_setzero_si512(), v, 0x0); }
#endif
#else
Vc_INTRINSIC Vc_CONST __m256 zeroExtend(__m128 v) { return _mm256_castps128_ps256(v); }
Vc_INTRINSIC Vc_CONST __m256i zeroExtend(__m128i v) { return _mm256_castsi128_si256(v); }
Vc_INTRINSIC Vc_CONST __m256d zeroExtend(__m128d v) { return _mm256_castpd128_pd256(v); }
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m512 zeroExtend(__m256 v) { return _mm512_castps256_ps512(v); }
Vc_INTRINSIC Vc_CONST __m512d zeroExtend(__m256d v) { return _mm512_castpd256_pd512(v); }
Vc_INTRINSIC Vc_CONST __m512i zeroExtend(__m256i v) { return _mm512_castsi256_si512(v); }
Vc_INTRINSIC Vc_CONST __m512 zeroExtend64(__m128 v) { return _mm512_castps128_ps512(v); }
Vc_INTRINSIC Vc_CONST __m512d zeroExtend64(__m128d v) { return _mm512_castpd128_pd512(v); }
Vc_INTRINSIC Vc_CONST __m512i zeroExtend64(__m128i v) { return _mm512_castsi128_si512(v); }
#endif
#endif
#endif
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m128 v) Vc_INTRINSIC_R;
#ifdef Vc_HAVE_SSE2
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m128i v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m128d v) Vc_INTRINSIC_R;
#endif
#ifdef Vc_HAVE_AVX
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m256 v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m256i v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m256d v) Vc_INTRINSIC_R;
#endif
#ifdef Vc_HAVE_AVX512F
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m512 v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m512i v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T intrin_cast(__m512d v) Vc_INTRINSIC_R;
#endif
template<> Vc_INTRINSIC __m128 intrin_cast(__m128 v) { return v; }
#ifdef Vc_HAVE_SSE2
template<> Vc_INTRINSIC __m128 intrin_cast(__m128i v) { return _mm_castsi128_ps(v); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m128d v) { return _mm_castpd_ps(v); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m128 v) { return _mm_castps_si128(v); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m128i v) { return v; }
template<> Vc_INTRINSIC __m128i intrin_cast(__m128d v) { return _mm_castpd_si128(v); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m128 v) { return _mm_castps_pd(v); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m128i v) { return _mm_castsi128_pd(v); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m128d v) { return v; }
#ifdef Vc_HAVE_AVX
template<> Vc_INTRINSIC __m256 intrin_cast(__m128 v) { return _mm256_castps128_ps256(v); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m128i v) { return _mm256_castps128_ps256(_mm_castsi128_ps(v)); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m128d v) { return _mm256_castps128_ps256(_mm_castpd_ps(v)); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m128 v) { return _mm256_castsi128_si256(_mm_castps_si128(v)); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m128i v) { return _mm256_castsi128_si256(v); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m128d v) { return _mm256_castsi128_si256(_mm_castpd_si128(v)); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m128 v) { return _mm256_castpd128_pd256(_mm_castps_pd(v)); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m128i v) { return _mm256_castpd128_pd256(_mm_castsi128_pd(v)); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m128d v) { return _mm256_castpd128_pd256(v); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m256 v) { return _mm256_castps256_ps128(v); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m256i v) { return _mm256_castps256_ps128(_mm256_castsi256_ps(v)); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m256d v) { return _mm256_castps256_ps128(_mm256_castpd_ps(v)); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m256 v) { return _mm256_castsi256_si128(_mm256_castps_si256(v)); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m256i v) { return _mm256_castsi256_si128(v); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m256d v) { return _mm256_castsi256_si128(_mm256_castpd_si256(v)); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m256 v) { return _mm256_castpd256_pd128(_mm256_castps_pd(v)); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m256i v) { return _mm256_castpd256_pd128(_mm256_castsi256_pd(v)); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m256d v) { return _mm256_castpd256_pd128(v); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m256 v) { return v; }
template<> Vc_INTRINSIC __m256 intrin_cast(__m256i v) { return _mm256_castsi256_ps(v); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m256d v) { return _mm256_castpd_ps(v); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m256 v) { return _mm256_castps_si256(v); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m256i v) { return v; }
template<> Vc_INTRINSIC __m256i intrin_cast(__m256d v) { return _mm256_castpd_si256(v); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m256 v) { return _mm256_castps_pd(v); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m256i v) { return _mm256_castsi256_pd(v); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m256d v) { return v; }
#ifdef Vc_HAVE_AVX512F
template<> Vc_INTRINSIC __m512 intrin_cast(__m256 v) { return _mm512_castps256_ps512(v); }
template<> Vc_INTRINSIC __m512 intrin_cast(__m256i v) { return _mm512_castps256_ps512(intrin_cast<__m256>(v)); }
template<> Vc_INTRINSIC __m512 intrin_cast(__m256d v) { return _mm512_castps256_ps512(intrin_cast<__m256>(v)); }
template<> Vc_INTRINSIC __m512i intrin_cast(__m256 v) { return _mm512_castsi256_si512(intrin_cast<__m256i>(v)); }
template<> Vc_INTRINSIC __m512i intrin_cast(__m256i v) { return _mm512_castsi256_si512(v); }
template<> Vc_INTRINSIC __m512i intrin_cast(__m256d v) { return _mm512_castsi256_si512(intrin_cast<__m256i>(v)); }
template<> Vc_INTRINSIC __m512d intrin_cast(__m256 v) { return _mm512_castpd256_pd512(intrin_cast<__m256d>(v)); }
template<> Vc_INTRINSIC __m512d intrin_cast(__m256i v) { return _mm512_castpd256_pd512(intrin_cast<__m256d>(v)); }
template<> Vc_INTRINSIC __m512d intrin_cast(__m256d v) { return _mm512_castpd256_pd512(v); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m512 v) { return _mm512_castps512_ps128(v); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m512i v) { return _mm512_castps512_ps128(_mm512_castsi512_ps(v)); }
template<> Vc_INTRINSIC __m128 intrin_cast(__m512d v) { return _mm512_castps512_ps128(_mm512_castpd_ps(v)); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m512 v) { return _mm512_castsi512_si128(_mm512_castps_si512(v)); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m512i v) { return _mm512_castsi512_si128(v); }
template<> Vc_INTRINSIC __m128i intrin_cast(__m512d v) { return _mm512_castsi512_si128(_mm512_castpd_si512(v)); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m512 v) { return _mm512_castpd512_pd128(_mm512_castps_pd(v)); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m512i v) { return _mm512_castpd512_pd128(_mm512_castsi512_pd(v)); }
template<> Vc_INTRINSIC __m128d intrin_cast(__m512d v) { return _mm512_castpd512_pd128(v); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m512 v) { return _mm512_castps512_ps256(v); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m512i v) { return _mm512_castps512_ps256(_mm512_castsi512_ps(v)); }
template<> Vc_INTRINSIC __m256 intrin_cast(__m512d v) { return _mm512_castps512_ps256(_mm512_castpd_ps(v)); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m512 v) { return _mm512_castsi512_si256(_mm512_castps_si512(v)); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m512i v) { return _mm512_castsi512_si256(v); }
template<> Vc_INTRINSIC __m256i intrin_cast(__m512d v) { return _mm512_castsi512_si256(_mm512_castpd_si512(v)); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m512 v) { return _mm512_castpd512_pd256(_mm512_castps_pd(v)); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m512i v) { return _mm512_castpd512_pd256(_mm512_castsi512_pd(v)); }
template<> Vc_INTRINSIC __m256d intrin_cast(__m512d v) { return _mm512_castpd512_pd256(v); }
template<> Vc_INTRINSIC __m512 intrin_cast(__m512 v) { return v; }
template<> Vc_INTRINSIC __m512 intrin_cast(__m512i v) { return _mm512_castsi512_ps(v); }
template<> Vc_INTRINSIC __m512 intrin_cast(__m512d v) { return _mm512_castpd_ps(v); }
template<> Vc_INTRINSIC __m512i intrin_cast(__m512 v) { return _mm512_castps_si512(v); }
template<> Vc_INTRINSIC __m512i intrin_cast(__m512i v) { return v; }
template<> Vc_INTRINSIC __m512i intrin_cast(__m512d v) { return _mm512_castpd_si512(v); }
template<> Vc_INTRINSIC __m512d intrin_cast(__m512 v) { return _mm512_castps_pd(v); }
template<> Vc_INTRINSIC __m512d intrin_cast(__m512i v) { return _mm512_castsi512_pd(v); }
template<> Vc_INTRINSIC __m512d intrin_cast(__m512d v) { return v; }
#endif
#endif
#endif
#ifdef Vc_HAVE_AVX
template <int offset> Vc_INTRINSIC __m256 insert128(__m256 a, __m128 b)
{
    return _mm256_insertf128_ps(a, b, offset);
}
template <int offset> Vc_INTRINSIC __m256d insert128(__m256d a, __m128d b)
{
    return _mm256_insertf128_pd(a, b, offset);
}
template <int offset> Vc_INTRINSIC __m256i insert128(__m256i a, __m128i b)
{
#ifdef Vc_HAVE_AVX2
    return _mm256_inserti128_si256(a, b, offset);
#else
    return _mm256_insertf128_si256(a, b, offset);
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <int offset> Vc_INTRINSIC __m512 insert256(__m512 a, __m256 b)
{
    return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(a), _mm256_castps_pd(b), offset));
}
template <int offset> Vc_INTRINSIC __m512d insert256(__m512d a, __m256d b)
{
    return _mm512_insertf64x4(a, b, offset);
}
template <int offset> Vc_INTRINSIC __m512i insert256(__m512i a, __m256i b)
{
    return _mm512_inserti64x4(a, b, offset);
}
#endif
#ifdef Vc_HAVE_AVX
template <int offset> Vc_INTRINSIC __m128 extract128(__m256 a)
{
    return _mm256_extractf128_ps(a, offset);
}
template <int offset> Vc_INTRINSIC __m128d extract128(__m256d a)
{
    return _mm256_extractf128_pd(a, offset);
}
template <int offset> Vc_INTRINSIC __m128i extract128(__m256i a)
{
#ifdef Vc_IMPL_AVX2
    return _mm256_extracti128_si256(a, offset);
#else
    return _mm256_extractf128_si256(a, offset);
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <int offset> Vc_INTRINSIC __m128 extract128(__m512 a)
{
    return _mm512_extractf32x4_ps(a, offset);
}
template <int offset> Vc_INTRINSIC __m128d extract128(__m512d a)
{
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_extractf64x2_pd(a, offset);
#else
    return _mm_castps_pd(_mm512_extractf32x4_ps(_mm512_castpd_ps(a), offset));
#endif
}
template <int offset> Vc_INTRINSIC __m128i extract128(__m512i a)
{
    return _mm512_extracti32x4_epi32(a, offset);
}
#endif
#ifdef Vc_HAVE_AVX512F
template <int offset> Vc_INTRINSIC __m256 extract256(__m512 a)
{
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_extractf32x8_ps(a, offset);
#else
    return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(a), offset));
#endif
}
template <int offset> Vc_INTRINSIC __m256d extract256(__m512d a)
{
    return _mm512_extractf64x4_pd(a, offset);
}
template <int offset> Vc_INTRINSIC __m256i extract256(__m512i a)
{
    return _mm512_extracti64x4_epi64(a, offset);
}
Vc_INTRINSIC __m256 extract256_center(__m512 a)
{
    return intrin_cast<__m256>(
        _mm512_shuffle_f32x4(a, a, 1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40));
}
Vc_INTRINSIC __m256d extract256_center(__m512d a)
{
    return intrin_cast<__m256d>(
        _mm512_shuffle_f64x2(a, a, 1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40));
}
Vc_INTRINSIC __m256i extract256_center(__m512i a)
{
    return intrin_cast<__m256i>(
        _mm512_shuffle_i32x4(a, a, 1 + 2 * 0x4 + 2 * 0x10 + 3 * 0x40));
}
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST __m128 lo128(__m256 v) { return intrin_cast<__m128 >(v); }
Vc_INTRINSIC Vc_CONST __m128d lo128(__m256d v) { return intrin_cast<__m128d>(v); }
Vc_INTRINSIC Vc_CONST __m128i lo128(__m256i v) { return intrin_cast<__m128i>(v); }
Vc_INTRINSIC Vc_CONST __m128 hi128(__m256 v) { return extract128<1>(v); }
Vc_INTRINSIC Vc_CONST __m128d hi128(__m256d v) { return extract128<1>(v); }
Vc_INTRINSIC Vc_CONST __m128i hi128(__m256i v) { return extract128<1>(v); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m256 lo256(__m512 v) { return intrin_cast<__m256 >(v); }
Vc_INTRINSIC Vc_CONST __m256d lo256(__m512d v) { return intrin_cast<__m256d>(v); }
Vc_INTRINSIC Vc_CONST __m256i lo256(__m512i v) { return intrin_cast<__m256i>(v); }
Vc_INTRINSIC Vc_CONST __m256 hi256(__m512 v) { return extract256<1>(v); }
Vc_INTRINSIC Vc_CONST __m256d hi256(__m512d v) { return extract256<1>(v); }
Vc_INTRINSIC Vc_CONST __m256i hi256(__m512i v) { return extract256<1>(v); }
Vc_INTRINSIC Vc_CONST __m128 lo128(__m512 v) { return intrin_cast<__m128 >(v); }
Vc_INTRINSIC Vc_CONST __m128d lo128(__m512d v) { return intrin_cast<__m128d>(v); }
Vc_INTRINSIC Vc_CONST __m128i lo128(__m512i v) { return intrin_cast<__m128i>(v); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST __m256 concat(__m128 a, __m128 b)
{
    return insert128<1>(intrin_cast<__m256>(a), b);
}
Vc_INTRINSIC Vc_CONST __m256d concat(__m128d a, __m128d b)
{
    return insert128<1>(intrin_cast<__m256d>(a), b);
}
Vc_INTRINSIC Vc_CONST __m256i concat(__m128i a, __m128i b)
{
    return insert128<1>(intrin_cast<__m256i>(a), b);
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m512 concat(__m256 a, __m256 b)
{
    return insert256<1>(intrin_cast<__m512>(a), b);
}
Vc_INTRINSIC Vc_CONST __m512d concat(__m256d a, __m256d b)
{
    return insert256<1>(intrin_cast<__m512d>(a), b);
}
Vc_INTRINSIC Vc_CONST __m512i concat(__m256i a, __m256i b)
{
    return insert256<1>(intrin_cast<__m512i>(a), b);
}
#endif
template <typename V> Vc_INTRINSIC_L Vc_CONST_L V allone() Vc_INTRINSIC_R Vc_CONST_R;
template <> Vc_INTRINSIC Vc_CONST __m128 allone<__m128>()
{
    return _mm_load_ps(reinterpret_cast<const float *>(sse_const::AllBitsSet));
}
#ifdef Vc_HAVE_SSE2
template <> Vc_INTRINSIC Vc_CONST __m128i allone<__m128i>()
{
    return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::AllBitsSet));
}
template <> Vc_INTRINSIC Vc_CONST __m128d allone<__m128d>()
{
    return _mm_load_pd(reinterpret_cast<const double *>(sse_const::AllBitsSet));
}
#endif
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC Vc_CONST __m256 allone<__m256>()
{
    return _mm256_load_ps(reinterpret_cast<const float *>(avx_const::AllBitsSet));
}
template <> Vc_INTRINSIC Vc_CONST __m256i allone<__m256i>()
{
    return _mm256_load_si256(reinterpret_cast<const __m256i *>(avx_const::AllBitsSet));
}
template <> Vc_INTRINSIC Vc_CONST __m256d allone<__m256d>()
{
    return _mm256_load_pd(reinterpret_cast<const double *>(avx_const::AllBitsSet));
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC Vc_CONST __m512 allone<__m512>()
{
    return _mm512_broadcast_f32x4(allone<__m128>());
}
template <> Vc_INTRINSIC Vc_CONST __m512d allone<__m512d>()
{
    return _mm512_castps_pd(allone<__m512>());
}
template <> Vc_INTRINSIC Vc_CONST __m512i allone<__m512i>()
{
    return _mm512_broadcast_i32x4(allone<__m128i>());
}
#endif
template <typename V> Vc_INTRINSIC_L Vc_CONST_L V zero() Vc_INTRINSIC_R Vc_CONST_R;
template<> Vc_INTRINSIC Vc_CONST __m128 zero<__m128 >() { return _mm_setzero_ps(); }
#ifdef Vc_HAVE_SSE2
template<> Vc_INTRINSIC Vc_CONST __m128i zero<__m128i>() { return _mm_setzero_si128(); }
template<> Vc_INTRINSIC Vc_CONST __m128d zero<__m128d>() { return _mm_setzero_pd(); }
#endif
#ifdef Vc_HAVE_AVX
template<> Vc_INTRINSIC Vc_CONST __m256 zero<__m256 >() { return _mm256_setzero_ps(); }
template<> Vc_INTRINSIC Vc_CONST __m256i zero<__m256i>() { return _mm256_setzero_si256(); }
template<> Vc_INTRINSIC Vc_CONST __m256d zero<__m256d>() { return _mm256_setzero_pd(); }
#endif
#ifdef Vc_HAVE_AVX512F
template<> Vc_INTRINSIC Vc_CONST __m512 zero<__m512 >() { return _mm512_setzero_ps(); }
template<> Vc_INTRINSIC Vc_CONST __m512i zero<__m512i>() { return _mm512_setzero_si512(); }
template<> Vc_INTRINSIC Vc_CONST __m512d zero<__m512d>() { return _mm512_setzero_pd(); }
#endif
template <class T> struct auto_cvt_t {
    const T x;
    template <class U> Vc_INTRINSIC operator U() const { return intrin_cast<U>(x); }
};
template <class T> auto_cvt_t<T> auto_cvt(T x) { return {x}; }
Vc_INTRINSIC Vc_CONST __m128 one16( float) { return _mm_load_ps(sse_const::oneFloat); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST __m128d one16(double) { return _mm_load_pd(sse_const::oneDouble); }
Vc_INTRINSIC Vc_CONST __m128i one16( schar) { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::one8)); }
Vc_INTRINSIC Vc_CONST __m128i one16( uchar) { return one16(schar()); }
Vc_INTRINSIC Vc_CONST __m128i one16( short) { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::one16)); }
Vc_INTRINSIC Vc_CONST __m128i one16(ushort) { return one16(short()); }
Vc_INTRINSIC Vc_CONST __m128i one16( int) { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::one32)); }
Vc_INTRINSIC Vc_CONST __m128i one16( uint) { return one16(int()); }
Vc_INTRINSIC Vc_CONST __m128i one16( llong) { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::one64)); }
Vc_INTRINSIC Vc_CONST __m128i one16(ullong) { return one16(llong()); }
Vc_INTRINSIC Vc_CONST __m128i one16( long) { return one16(equal_int_type_t<long>()); }
Vc_INTRINSIC Vc_CONST __m128i one16( ulong) { return one16(equal_int_type_t<ulong>()); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST __m256 one32( float) { return _mm256_broadcast_ss(&avx_const::oneFloat); }
Vc_INTRINSIC Vc_CONST __m256d one32(double) { return _mm256_broadcast_sd(&avx_const::oneDouble); }
Vc_INTRINSIC Vc_CONST __m256i one32( llong) { return _mm256_castpd_si256(_mm256_broadcast_sd(reinterpret_cast<const double *>(&avx_const::IndexesFromZero64[1]))); }
Vc_INTRINSIC Vc_CONST __m256i one32(ullong) { return one32(llong()); }
Vc_INTRINSIC Vc_CONST __m256i one32( int) { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(&avx_const::IndexesFromZero32[1]))); }
Vc_INTRINSIC Vc_CONST __m256i one32( uint) { return one32(int()); }
Vc_INTRINSIC Vc_CONST __m256i one32( short) { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(avx_const::one16))); }
Vc_INTRINSIC Vc_CONST __m256i one32(ushort) { return one32(short()); }
Vc_INTRINSIC Vc_CONST __m256i one32( schar) { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(avx_const::one8))); }
Vc_INTRINSIC Vc_CONST __m256i one32( uchar) { return one32(schar()); }
Vc_INTRINSIC Vc_CONST __m256i one32( long) { return one32(equal_int_type_t<long>()); }
Vc_INTRINSIC Vc_CONST __m256i one32( ulong) { return one32(equal_int_type_t<ulong>()); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m512 one64( float) { return _mm512_broadcastss_ps(_mm_load_ss(&avx_const::oneFloat)); }
Vc_INTRINSIC Vc_CONST __m512d one64(double) { return _mm512_broadcastsd_pd(_mm_load_sd(&avx_const::oneDouble)); }
Vc_INTRINSIC Vc_CONST __m512i one64( llong) { return _mm512_set1_epi64(1ll); }
Vc_INTRINSIC Vc_CONST __m512i one64(ullong) { return _mm512_set1_epi64(1ll); }
Vc_INTRINSIC Vc_CONST __m512i one64( int) { return _mm512_set1_epi32(1); }
Vc_INTRINSIC Vc_CONST __m512i one64( uint) { return _mm512_set1_epi32(1); }
Vc_INTRINSIC Vc_CONST __m512i one64( short) { return _mm512_set1_epi16(1); }
Vc_INTRINSIC Vc_CONST __m512i one64(ushort) { return _mm512_set1_epi16(1); }
Vc_INTRINSIC Vc_CONST __m512i one64( schar) { return _mm512_broadcast_i32x4(one16(schar())); }
Vc_INTRINSIC Vc_CONST __m512i one64( uchar) { return one64(schar()); }
Vc_INTRINSIC Vc_CONST __m512i one64( long) { return one64(equal_int_type_t<long>()); }
Vc_INTRINSIC Vc_CONST __m512i one64( ulong) { return one64(equal_int_type_t<ulong>()); }
#endif
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST __m128d signmask16(double){ return _mm_load_pd(reinterpret_cast<const double *>(sse_const::signMaskDouble)); }
#endif
Vc_INTRINSIC Vc_CONST __m128 signmask16( float){ return _mm_load_ps(reinterpret_cast<const float *>(sse_const::signMaskFloat)); }
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST __m256d signmask32(double){ return _mm256_broadcast_sd(reinterpret_cast<const double *>(&avx_const::signMaskFloat[0])); }
Vc_INTRINSIC Vc_CONST __m256 signmask32( float){ return _mm256_broadcast_ss(reinterpret_cast<const float *>(&avx_const::signMaskFloat[1])); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m512d signmask64(double){ return _mm512_broadcast_f64x4(signmask32(double())); }
Vc_INTRINSIC Vc_CONST __m512 signmask64( float){ return _mm512_broadcast_f32x4(signmask16(float())); }
#endif
Vc_INTRINSIC Vc_CONST __m128 set(float x0, float x1, float x2, float x3)
{
    return _mm_set_ps(x3, x2, x1, x0);
}
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST __m128d set(double x0, double x1) { return _mm_set_pd(x1, x0); }
Vc_INTRINSIC Vc_CONST __m128i set(llong x0, llong x1) { return _mm_set_epi64x(x1, x0); }
Vc_INTRINSIC Vc_CONST __m128i set(ullong x0, ullong x1) { return _mm_set_epi64x(x1, x0); }
Vc_INTRINSIC Vc_CONST __m128i set(int x0, int x1, int x2, int x3)
{
    return _mm_set_epi32(x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m128i set(uint x0, uint x1, uint x2, uint x3)
{
    return _mm_set_epi32(x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m128i set(short x0, short x1, short x2, short x3, short x4,
                                  short x5, short x6, short x7)
{
    return _mm_set_epi16(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m128i set(ushort x0, ushort x1, ushort x2, ushort x3, ushort x4,
                                  ushort x5, ushort x6, ushort x7)
{
    return _mm_set_epi16(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m128i set(schar x0, schar x1, schar x2, schar x3, schar x4,
                                  schar x5, schar x6, schar x7, schar x8, schar x9,
                                  schar x10, schar x11, schar x12, schar x13, schar x14,
                                  schar x15)
{
    return _mm_set_epi8(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1,
                         x0);
}
Vc_INTRINSIC Vc_CONST __m128i set(uchar x0, uchar x1, uchar x2, uchar x3, uchar x4,
                                  uchar x5, uchar x6, uchar x7, uchar x8, uchar x9,
                                  uchar x10, uchar x11, uchar x12, uchar x13, uchar x14,
                                  uchar x15)
{
    return _mm_set_epi8(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1,
                         x0);
}
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST __m256 set(float x0, float x1, float x2, float x3, float x4,
                                 float x5, float x6, float x7)
{
    return _mm256_set_ps(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256d set(double x0, double x1, double x2, double x3)
{
    return _mm256_set_pd(x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(llong x0, llong x1, llong x2, llong x3)
{
    return _mm256_set_epi64x(x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(ullong x0, ullong x1, ullong x2, ullong x3)
{
    return _mm256_set_epi64x(x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(int x0, int x1, int x2, int x3, int x4, int x5, int x6,
                                  int x7)
{
    return _mm256_set_epi32(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(uint x0, uint x1, uint x2, uint x3, uint x4, uint x5,
                                  uint x6, uint x7)
{
    return _mm256_set_epi32(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(short x0, short x1, short x2, short x3, short x4,
                                  short x5, short x6, short x7, short x8, short x9,
                                  short x10, short x11, short x12, short x13, short x14,
                                  short x15)
{
    return _mm256_set_epi16(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2,
                            x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(ushort x0, ushort x1, ushort x2, ushort x3, ushort x4,
                                  ushort x5, ushort x6, ushort x7, ushort x8, ushort x9,
                                  ushort x10, ushort x11, ushort x12, ushort x13,
                                  ushort x14, ushort x15)
{
    return _mm256_set_epi16(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2,
                            x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(schar x0, schar x1, schar x2, schar x3, schar x4,
                                  schar x5, schar x6, schar x7, schar x8, schar x9,
                                  schar x10, schar x11, schar x12, schar x13, schar x14,
                                  schar x15, schar x16, schar x17, schar x18, schar x19,
                                  schar x20, schar x21, schar x22, schar x23, schar x24,
                                  schar x25, schar x26, schar x27, schar x28, schar x29,
                                  schar x30, schar x31)
{
    return _mm256_set_epi8(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21, x20,
                           x19, x18, x17, x16, x15, x14, x13, x12, x11, x10, x9, x8, x7,
                           x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m256i set(uchar x0, uchar x1, uchar x2, uchar x3, uchar x4,
                                  uchar x5, uchar x6, uchar x7, uchar x8, uchar x9,
                                  uchar x10, uchar x11, uchar x12, uchar x13, uchar x14,
                                  uchar x15, uchar x16, uchar x17, uchar x18, uchar x19,
                                  uchar x20, uchar x21, uchar x22, uchar x23, uchar x24,
                                  uchar x25, uchar x26, uchar x27, uchar x28, uchar x29,
                                  uchar x30, uchar x31)
{
    return _mm256_set_epi8(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21, x20,
                           x19, x18, x17, x16, x15, x14, x13, x12, x11, x10, x9, x8, x7,
                           x6, x5, x4, x3, x2, x1, x0);
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __m512d set(double x0, double x1, double x2, double x3, double x4,
                                  double x5, double x6, double x7)
{
    return _mm512_set_pd(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m512 set(float x0, float x1, float x2, float x3, float x4,
                                 float x5, float x6, float x7, float x8, float x9,
                                 float x10, float x11, float x12, float x13, float x14,
                                 float x15)
{
    return _mm512_set_ps(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1,
                         x0);
}
Vc_INTRINSIC Vc_CONST __m512i set(llong x0, llong x1, llong x2, llong x3, llong x4,
                                  llong x5, llong x6, llong x7)
{
    return _mm512_set_epi64(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m512i set(ullong x0, ullong x1, ullong x2, ullong x3, ullong x4,
                                  ullong x5, ullong x6, ullong x7)
{
    return _mm512_set_epi64(x7, x6, x5, x4, x3, x2, x1, x0);
}
Vc_INTRINSIC Vc_CONST __m512i set(int x0, int x1, int x2, int x3, int x4, int x5, int x6,
                                  int x7, int x8, int x9, int x10, int x11, int x12,
                                  int x13, int x14, int x15)
{
    return _mm512_set_epi32(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2,
                            x1, x0);
}
Vc_INTRINSIC Vc_CONST __m512i set(uint x0, uint x1, uint x2, uint x3, uint x4, uint x5,
                                  uint x6, uint x7, uint x8, uint x9, uint x10, uint x11,
                                  uint x12, uint x13, uint x14, uint x15)
{
    return _mm512_set_epi32(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2,
                            x1, x0);
}
Vc_INTRINSIC Vc_CONST __m512i set(short x0, short x1, short x2, short x3, short x4,
                                  short x5, short x6, short x7, short x8, short x9,
                                  short x10, short x11, short x12, short x13, short x14,
                                  short x15, short x16, short x17, short x18, short x19,
                                  short x20, short x21, short x22, short x23, short x24,
                                  short x25, short x26, short x27, short x28, short x29,
                                  short x30, short x31)
{
    return concat(_mm256_set_epi16(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4,
                                   x3, x2, x1, x0),
                  _mm256_set_epi16(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21,
                                   x20, x19, x18, x17, x16));
}
Vc_INTRINSIC Vc_CONST __m512i set(ushort x0, ushort x1, ushort x2, ushort x3, ushort x4,
                                  ushort x5, ushort x6, ushort x7, ushort x8, ushort x9,
                                  ushort x10, ushort x11, ushort x12, ushort x13, ushort x14,
                                  ushort x15, ushort x16, ushort x17, ushort x18, ushort x19,
                                  ushort x20, ushort x21, ushort x22, ushort x23, ushort x24,
                                  ushort x25, ushort x26, ushort x27, ushort x28, ushort x29,
                                  ushort x30, ushort x31)
{
    return concat(_mm256_set_epi16(x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4,
                                   x3, x2, x1, x0),
                  _mm256_set_epi16(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21,
                                   x20, x19, x18, x17, x16));
}
Vc_INTRINSIC Vc_CONST __m512i
set(schar x0, schar x1, schar x2, schar x3, schar x4, schar x5, schar x6, schar x7,
    schar x8, schar x9, schar x10, schar x11, schar x12, schar x13, schar x14, schar x15,
    schar x16, schar x17, schar x18, schar x19, schar x20, schar x21, schar x22,
    schar x23, schar x24, schar x25, schar x26, schar x27, schar x28, schar x29,
    schar x30, schar x31, schar x32, schar x33, schar x34, schar x35, schar x36,
    schar x37, schar x38, schar x39, schar x40, schar x41, schar x42, schar x43,
    schar x44, schar x45, schar x46, schar x47, schar x48, schar x49, schar x50,
    schar x51, schar x52, schar x53, schar x54, schar x55, schar x56, schar x57,
    schar x58, schar x59, schar x60, schar x61, schar x62, schar x63)
{
    return concat(_mm256_set_epi8(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21,
                                  x20, x19, x18, x17, x16, x15, x14, x13, x12, x11, x10,
                                  x9, x8, x7, x6, x5, x4, x3, x2, x1, x0),
                  _mm256_set_epi8(x63, x62, x61, x60, x59, x58, x57, x56, x55, x54, x53,
                                  x52, x51, x50, x49, x48, x47, x46, x45, x44, x43, x42,
                                  x41, x40, x39, x38, x37, x36, x35, x34, x33, x32));
}
Vc_INTRINSIC Vc_CONST __m512i
set(uchar x0, uchar x1, uchar x2, uchar x3, uchar x4, uchar x5, uchar x6, uchar x7,
    uchar x8, uchar x9, uchar x10, uchar x11, uchar x12, uchar x13, uchar x14, uchar x15,
    uchar x16, uchar x17, uchar x18, uchar x19, uchar x20, uchar x21, uchar x22,
    uchar x23, uchar x24, uchar x25, uchar x26, uchar x27, uchar x28, uchar x29,
    uchar x30, uchar x31, uchar x32, uchar x33, uchar x34, uchar x35, uchar x36,
    uchar x37, uchar x38, uchar x39, uchar x40, uchar x41, uchar x42, uchar x43,
    uchar x44, uchar x45, uchar x46, uchar x47, uchar x48, uchar x49, uchar x50,
    uchar x51, uchar x52, uchar x53, uchar x54, uchar x55, uchar x56, uchar x57,
    uchar x58, uchar x59, uchar x60, uchar x61, uchar x62, uchar x63)
{
    return concat(_mm256_set_epi8(x31, x30, x29, x28, x27, x26, x25, x24, x23, x22, x21,
                                  x20, x19, x18, x17, x16, x15, x14, x13, x12, x11, x10,
                                  x9, x8, x7, x6, x5, x4, x3, x2, x1, x0),
                  _mm256_set_epi8(x63, x62, x61, x60, x59, x58, x57, x56, x55, x54, x53,
                                  x52, x51, x50, x49, x48, x47, x46, x45, x44, x43, x42,
                                  x41, x40, x39, x38, x37, x36, x35, x34, x33, x32));
}
#endif
template <typename... Ts> Vc_INTRINSIC Vc_CONST auto set(Ts... args)
{
    return set(static_cast<equal_int_type_t<Ts>>(args)...);
}
Vc_INTRINSIC __m128 broadcast16( float x) { return _mm_set1_ps(x); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d broadcast16(double x) { return _mm_set1_pd(x); }
Vc_INTRINSIC __m128i broadcast16( schar x) { return _mm_set1_epi8(x); }
Vc_INTRINSIC __m128i broadcast16( uchar x) { return _mm_set1_epi8(x); }
Vc_INTRINSIC __m128i broadcast16( short x) { return _mm_set1_epi16(x); }
Vc_INTRINSIC __m128i broadcast16(ushort x) { return _mm_set1_epi16(x); }
Vc_INTRINSIC __m128i broadcast16( int x) { return _mm_set1_epi32(x); }
Vc_INTRINSIC __m128i broadcast16( uint x) { return _mm_set1_epi32(x); }
Vc_INTRINSIC __m128i broadcast16( long x) { return sizeof( long) == 4 ? _mm_set1_epi32(x) : _mm_set1_epi64x(x); }
Vc_INTRINSIC __m128i broadcast16( ulong x) { return sizeof(ulong) == 4 ? _mm_set1_epi32(x) : _mm_set1_epi64x(x); }
Vc_INTRINSIC __m128i broadcast16( llong x) { return _mm_set1_epi64x(x); }
Vc_INTRINSIC __m128i broadcast16(ullong x) { return _mm_set1_epi64x(x); }
#endif
template <class T> Vc_INTRINSIC auto broadcast(T x, size_constant<16>)
{
    return broadcast16(x);
}
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 broadcast32( float x) { return _mm256_set1_ps(x); }
Vc_INTRINSIC __m256d broadcast32(double x) { return _mm256_set1_pd(x); }
Vc_INTRINSIC __m256i broadcast32( schar x) { return _mm256_set1_epi8(x); }
Vc_INTRINSIC __m256i broadcast32( uchar x) { return _mm256_set1_epi8(x); }
Vc_INTRINSIC __m256i broadcast32( short x) { return _mm256_set1_epi16(x); }
Vc_INTRINSIC __m256i broadcast32(ushort x) { return _mm256_set1_epi16(x); }
Vc_INTRINSIC __m256i broadcast32( int x) { return _mm256_set1_epi32(x); }
Vc_INTRINSIC __m256i broadcast32( uint x) { return _mm256_set1_epi32(x); }
Vc_INTRINSIC __m256i broadcast32( long x) { return sizeof( long) == 4 ? _mm256_set1_epi32(x) : _mm256_set1_epi64x(x); }
Vc_INTRINSIC __m256i broadcast32( ulong x) { return sizeof(ulong) == 4 ? _mm256_set1_epi32(x) : _mm256_set1_epi64x(x); }
Vc_INTRINSIC __m256i broadcast32( llong x) { return _mm256_set1_epi64x(x); }
Vc_INTRINSIC __m256i broadcast32(ullong x) { return _mm256_set1_epi64x(x); }
template <class T> Vc_INTRINSIC auto broadcast(T x, size_constant<32>)
{
    return broadcast32(x);
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 broadcast64( float x) { return _mm512_set1_ps(x); }
Vc_INTRINSIC __m512d broadcast64(double x) { return _mm512_set1_pd(x); }
Vc_INTRINSIC __m512i broadcast64( schar x) { return _mm512_set1_epi8(x); }
Vc_INTRINSIC __m512i broadcast64( uchar x) { return _mm512_set1_epi8(x); }
Vc_INTRINSIC __m512i broadcast64( short x) { return _mm512_set1_epi16(x); }
Vc_INTRINSIC __m512i broadcast64(ushort x) { return _mm512_set1_epi16(x); }
Vc_INTRINSIC __m512i broadcast64( int x) { return _mm512_set1_epi32(x); }
Vc_INTRINSIC __m512i broadcast64( uint x) { return _mm512_set1_epi32(x); }
Vc_INTRINSIC __m512i broadcast64( long x) { return sizeof( long) == 4 ? _mm512_set1_epi32(x) : _mm512_set1_epi64(x); }
Vc_INTRINSIC __m512i broadcast64( ulong x) { return sizeof(ulong) == 4 ? _mm512_set1_epi32(x) : _mm512_set1_epi64(x); }
Vc_INTRINSIC __m512i broadcast64( llong x) { return _mm512_set1_epi64(x); }
Vc_INTRINSIC __m512i broadcast64(ullong x) { return _mm512_set1_epi64(x); }
template <class T> Vc_INTRINSIC auto broadcast(T x, size_constant<64>)
{
    return broadcast64(x);
}
#endif
template <class T> struct broadcast_t {
    const T scalar;
    operator __m128i() { return broadcast16(scalar); }
#ifdef Vc_HAVE_AVX
    operator __m256i() { return broadcast32(scalar); }
#endif
#ifdef Vc_HAVE_AVX512F
    operator __m512i() { return broadcast64(scalar); }
#endif
};
template <> struct broadcast_t<float> {
    const float scalar;
    operator __m128() { return broadcast16(scalar); }
#ifdef Vc_HAVE_AVX
    operator __m256() { return broadcast32(scalar); }
#endif
#ifdef Vc_HAVE_AVX512F
    operator __m512() { return broadcast64(scalar); }
#endif
};
template <> struct broadcast_t<double> {
    const double scalar;
    operator __m128d() { return broadcast16(scalar); }
#ifdef Vc_HAVE_AVX
    operator __m256d() { return broadcast32(scalar); }
#endif
#ifdef Vc_HAVE_AVX512F
    operator __m512d() { return broadcast64(scalar); }
#endif
};
template <class T> broadcast_t<T> broadcast(T scalar) { return {scalar}; }
template <class T>
Vc_INTRINSIC Vc_CONST typename intrinsic_type<T, 16>::type lowest16()
{
    return broadcast16(std::numeric_limits<T>::lowest());
}
#ifdef Vc_HAVE_SSE2
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< short>() { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::minShort)); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< int>() { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::signMaskFloat)); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< llong>() { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::signMaskDouble)); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< long>() { return lowest16<equal_int_type_t<long>>(); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< uchar>() { return _mm_setzero_si128(); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16<ushort>() { return _mm_setzero_si128(); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< uint>() { return _mm_setzero_si128(); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16< ulong>() { return _mm_setzero_si128(); }
template <> Vc_INTRINSIC Vc_CONST __m128i lowest16<ullong>() { return _mm_setzero_si128(); }
#endif
#ifdef Vc_HAVE_AVX
template <class T>
Vc_INTRINSIC Vc_CONST typename intrinsic_type<T, 32>::type lowest32()
{
    return broadcast32(std::numeric_limits<T>::lowest());
}
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32<short>() { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(sse_const::minShort))); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32< int>() { return _mm256_castps_si256(signmask32(float())); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32<llong>() { return _mm256_castpd_si256(signmask32(double())); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32< long>() { return lowest32<equal_int_type_t<long>>(); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32< uchar>() { return _mm256_setzero_si256(); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32<ushort>() { return _mm256_setzero_si256(); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32< uint>() { return _mm256_setzero_si256(); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32< ulong>() { return _mm256_setzero_si256(); }
template <> Vc_INTRINSIC Vc_CONST __m256i lowest32<ullong>() { return _mm256_setzero_si256(); }
#endif
#ifdef Vc_HAVE_AVX512F
template <class T>
Vc_INTRINSIC Vc_CONST typename intrinsic_type<T, 64>::type lowest64()
{
    return broadcast64(std::numeric_limits<T>::lowest());
}
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64<short>() { return _mm512_broadcast_i32x4(lowest16<short>()); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64< int>() { return _mm512_broadcast_i32x4(lowest16< int>()); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64<llong>() { return _mm512_broadcast_i32x4(lowest16<llong>()); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64< long>() { return _mm512_broadcast_i32x4(lowest16< long>()); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64< uchar>() { return _mm512_setzero_si512(); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64<ushort>() { return _mm512_setzero_si512(); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64< uint>() { return _mm512_setzero_si512(); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64< ulong>() { return _mm512_setzero_si512(); }
template <> Vc_INTRINSIC Vc_CONST __m512i lowest64<ullong>() { return _mm512_setzero_si512(); }
#endif
template <class T> inline typename intrinsic_type<T, 16>::type sse_2_pow_31();
template <> Vc_INTRINSIC Vc_CONST __m128 sse_2_pow_31< float>() { return broadcast16( float(1u << 31)); }
#ifdef Vc_HAVE_SSE2
template <> Vc_INTRINSIC Vc_CONST __m128d sse_2_pow_31<double>() { return broadcast16(double(1u << 31)); }
template <> Vc_INTRINSIC Vc_CONST __m128i sse_2_pow_31< uint>() { return lowest16<int>(); }
#endif
#ifdef Vc_HAVE_AVX
template <class T> inline typename intrinsic_type<T, 32>::type avx_2_pow_31();
template <> Vc_INTRINSIC Vc_CONST __m256 avx_2_pow_31< float>() { return _mm256_broadcast_ss(&avx_const::_2_pow_31); }
template <> Vc_INTRINSIC Vc_CONST __m256d avx_2_pow_31<double>() { return broadcast32(double(1u << 31)); }
template <> Vc_INTRINSIC Vc_CONST __m256i avx_2_pow_31< uint>() { return lowest32<int>(); }
#endif
Vc_INTRINSIC __m128i shift_msb_to_lsb(__m128i v)
{
#if defined Vc_GCC && Vc_GCC < 0x60400 && defined Vc_HAVE_AVX512F && \
    !defined Vc_HAVE_AVX512VL
    asm("vpsrlw $15,%0,%0" : "+x"(v));
    return v;
#else
    return _mm_srli_epi16(v, 15);
#endif
}
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC __m256i shift_msb_to_lsb(__m256i v)
{
#if defined Vc_GCC && Vc_GCC < 0x60400 && defined Vc_HAVE_AVX512F && \
    !defined Vc_HAVE_AVX512VL
    asm("vpsrlw $15,%0,%0" : "+x"(v));
    return v;
#else
    return _mm256_srli_epi16(v, 15);
#endif
}
#endif
template <int n> Vc_INTRINSIC __m128i slli_epi16(__m128i v)
{
#if defined Vc_GCC && Vc_GCC < 0x60400 && defined Vc_HAVE_AVX512F && \
    !defined Vc_HAVE_AVX512VL
    asm("vpsllw %1,%0,%0" : "+x"(v) : "i"(n));
    return v;
#else
    return _mm_slli_epi16(v, n);
#endif
}
#ifdef Vc_HAVE_AVX2
template <int n> Vc_INTRINSIC __m256i slli_epi16(__m256i v)
{
#if defined Vc_GCC && Vc_GCC < 0x60400 && defined Vc_HAVE_AVX512F && \
    !defined Vc_HAVE_AVX512VL
    asm("vpsllw %1,%0,%0" : "+x"(v) : "i"(n));
    return v;
#else
    return _mm256_slli_epi16(v, n);
#endif
}
#endif
template <int n> Vc_INTRINSIC __m128i srli_epi16(__m128i v)
{
#if defined Vc_GCC && Vc_GCC < 0x60400 && defined Vc_HAVE_AVX512F && \
    !defined Vc_HAVE_AVX512VL
    asm("vpsrlw %1,%0,%0" : "+x"(v) : "i"(n));
    return v;
#else
    return _mm_srli_epi16(v, n);
#endif
}
#ifdef Vc_HAVE_AVX2
template <int n> Vc_INTRINSIC __m256i srli_epi16(__m256i v)
{
#if defined Vc_GCC && Vc_GCC < 0x60400 && defined Vc_HAVE_AVX512F && \
    !defined Vc_HAVE_AVX512VL
    asm("vpsrlw %1,%0,%0" : "+x"(v) : "i"(n));
    return v;
#else
    return _mm256_srli_epi16(v, n);
#endif
}
#endif
Vc_INTRINSIC __m128 setone_ps16() { return _mm_load_ps(sse_const::oneFloat); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d setone_pd16() { return _mm_load_pd(sse_const::oneDouble); }
Vc_INTRINSIC __m128i setone_epi8 () { return _mm_set1_epi8(1); }
Vc_INTRINSIC __m128i setone_epu8 () { return setone_epi8(); }
Vc_INTRINSIC __m128i setone_epi16() { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::one16)); }
Vc_INTRINSIC __m128i setone_epu16() { return setone_epi16(); }
Vc_INTRINSIC __m128i setone_epi32() { return _mm_load_si128(reinterpret_cast<const __m128i *>(sse_const::one32)); }
Vc_INTRINSIC __m128i setone_epu32() { return setone_epi32(); }
#endif
Vc_INTRINSIC __m128 setabsmask_ps_16() { return _mm_load_ps(reinterpret_cast<const float *>(sse_const::absMaskFloat)); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d setabsmask_pd_16() { return _mm_load_pd(reinterpret_cast<const double *>(sse_const::absMaskDouble)); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 setabsmask_ps_32() { return _mm256_broadcast_ss(reinterpret_cast<const float *>(&avx_const::absMaskFloat[1])); }
Vc_INTRINSIC __m256d setabsmask_pd_32() { return _mm256_broadcast_sd(reinterpret_cast<const double *>(&avx_const::absMaskFloat[0])); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 setabsmask_ps_64() { return _mm512_broadcast_f32x4(setabsmask_ps_16()); }
Vc_INTRINSIC __m512d setabsmask_pd_64() { return _mm512_broadcast_f64x4(setabsmask_pd_32()); }
#endif
#ifdef Vc_HAVE_SSE2
#if defined(Vc_IMPL_XOP)
Vc_INTRINSIC __m128i cmplt_epu8 (__m128i a, __m128i b) { return _mm_comlt_epu8 (a, b); }
Vc_INTRINSIC __m128i cmpgt_epu8 (__m128i a, __m128i b) { return _mm_comgt_epu8 (a, b); }
Vc_INTRINSIC __m128i cmplt_epu16(__m128i a, __m128i b) { return _mm_comlt_epu16(a, b); }
Vc_INTRINSIC __m128i cmpgt_epu16(__m128i a, __m128i b) { return _mm_comgt_epu16(a, b); }
Vc_INTRINSIC __m128i cmplt_epu32(__m128i a, __m128i b) { return _mm_comlt_epu32(a, b); }
Vc_INTRINSIC __m128i cmpgt_epu32(__m128i a, __m128i b) { return _mm_comgt_epu32(a, b); }
Vc_INTRINSIC __m128i cmplt_epu64(__m128i a, __m128i b) { return _mm_comlt_epu64(a, b); }
Vc_INTRINSIC __m128i cmpgt_epu64(__m128i a, __m128i b) { return _mm_comgt_epu64(a, b); }
#else
Vc_INTRINSIC __m128i Vc_CONST cmplt_epu8(__m128i a, __m128i b)
{
    return _mm_cmplt_epi8(_mm_xor_si128(a, lowest16<schar>()),
                          _mm_xor_si128(b, lowest16<schar>()));
}
Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu8(__m128i a, __m128i b)
{
    return _mm_cmpgt_epi8(_mm_xor_si128(a, lowest16<schar>()),
                          _mm_xor_si128(b, lowest16<schar>()));
}
Vc_INTRINSIC __m128i Vc_CONST cmplt_epu16(__m128i a, __m128i b)
{
    return _mm_cmplt_epi16(_mm_xor_si128(a, lowest16<short>()),
                           _mm_xor_si128(b, lowest16<short>()));
}
Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu16(__m128i a, __m128i b)
{
    return _mm_cmpgt_epi16(_mm_xor_si128(a, lowest16<short>()),
                           _mm_xor_si128(b, lowest16<short>()));
}
Vc_INTRINSIC __m128i Vc_CONST cmplt_epu32(__m128i a, __m128i b)
{
    return _mm_cmplt_epi32(_mm_xor_si128(a, lowest16<int>()),
                           _mm_xor_si128(b, lowest16<int>()));
}
Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu32(__m128i a, __m128i b)
{
    return _mm_cmpgt_epi32(_mm_xor_si128(a, lowest16<int>()),
                           _mm_xor_si128(b, lowest16<int>()));
}
Vc_INTRINSIC __m128i Vc_CONST cmpgt_epi64(__m128i a, __m128i b)
{
#ifdef Vc_IMPL_SSE4_2
    return _mm_cmpgt_epi64(a, b);
#else
    const auto aa = _mm_xor_si128(a, _mm_srli_epi64(lowest16<int>(), 32));
    const auto bb = _mm_xor_si128(b, _mm_srli_epi64(lowest16<int>(), 32));
    const auto gt = _mm_cmpgt_epi32(aa, bb);
    const auto eq = _mm_cmpeq_epi32(aa, bb);
    const auto gt2 =
        _mm_shuffle_epi32(gt, 0xf5);
    const auto lo = _mm_shuffle_epi32(_mm_and_si128(_mm_srli_epi64(eq, 32), gt), 0xa0);
    return _mm_or_si128(gt2, lo);
#endif
}
Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu64(__m128i a, __m128i b)
{
    return cmpgt_epi64(_mm_xor_si128(a, lowest16<llong>()),
                       _mm_xor_si128(b, lowest16<llong>()));
}
#endif
template <int s> Vc_INTRINSIC Vc_CONST __m128i alignr(__m128i a, __m128i b)
{
#ifdef Vc_HAVE_SSSE3
    return _mm_alignr_epi8(a, b, s & 0x1fu);
#else
    switch (s & 0x1fu) {
        case 0: return b;
        case 1: return _mm_or_si128(_mm_slli_si128(a, 15), _mm_srli_si128(b, 1));
        case 2: return _mm_or_si128(_mm_slli_si128(a, 14), _mm_srli_si128(b, 2));
        case 3: return _mm_or_si128(_mm_slli_si128(a, 13), _mm_srli_si128(b, 3));
        case 4: return _mm_or_si128(_mm_slli_si128(a, 12), _mm_srli_si128(b, 4));
        case 5: return _mm_or_si128(_mm_slli_si128(a, 11), _mm_srli_si128(b, 5));
        case 6: return _mm_or_si128(_mm_slli_si128(a, 10), _mm_srli_si128(b, 6));
        case 7: return _mm_or_si128(_mm_slli_si128(a, 9), _mm_srli_si128(b, 7));
        case 8: return _mm_or_si128(_mm_slli_si128(a, 8), _mm_srli_si128(b, 8));
        case 9: return _mm_or_si128(_mm_slli_si128(a, 7), _mm_srli_si128(b, 9));
        case 10: return _mm_or_si128(_mm_slli_si128(a, 6), _mm_srli_si128(b, 10));
        case 11: return _mm_or_si128(_mm_slli_si128(a, 5), _mm_srli_si128(b, 11));
        case 12: return _mm_or_si128(_mm_slli_si128(a, 4), _mm_srli_si128(b, 12));
        case 13: return _mm_or_si128(_mm_slli_si128(a, 3), _mm_srli_si128(b, 13));
        case 14: return _mm_or_si128(_mm_slli_si128(a, 2), _mm_srli_si128(b, 14));
        case 15: return _mm_or_si128(_mm_slli_si128(a, 1), _mm_srli_si128(b, 15));
        case 16: return a;
        case 17: return _mm_srli_si128(a, 1);
        case 18: return _mm_srli_si128(a, 2);
        case 19: return _mm_srli_si128(a, 3);
        case 20: return _mm_srli_si128(a, 4);
        case 21: return _mm_srli_si128(a, 5);
        case 22: return _mm_srli_si128(a, 6);
        case 23: return _mm_srli_si128(a, 7);
        case 24: return _mm_srli_si128(a, 8);
        case 25: return _mm_srli_si128(a, 9);
        case 26: return _mm_srli_si128(a, 10);
        case 27: return _mm_srli_si128(a, 11);
        case 28: return _mm_srli_si128(a, 12);
        case 29: return _mm_srli_si128(a, 13);
        case 30: return _mm_srli_si128(a, 14);
        case 31: return _mm_srli_si128(a, 15);
    }
    return _mm_setzero_si128();
#endif
}
#endif
#ifdef Vc_HAVE_AVX
template <int shift> Vc_INTRINSIC Vc_CONST __m256i alignr(__m256i s1, __m256i s2)
{
#ifdef Vc_HAVE_AVX2
    return _mm256_alignr_epi8(s1, s2, shift);
#else
    return insert128<1>(
        _mm256_castsi128_si256(_mm_alignr_epi8(_mm256_castsi256_si128(s1),
                                               _mm256_castsi256_si128(s2), shift)),
        _mm_alignr_epi8(extract128<1>(s1), extract128<1>(s2), shift));
#endif
}
#endif
#ifdef Vc_HAVE_SSE4_1
Vc_INTRINSIC Vc_CONST __m128i cmpeq_epi64(__m128i a, __m128i b)
{
    return _mm_cmpeq_epi64(a, b);
}
template <int index> Vc_INTRINSIC Vc_CONST int extract_epi32(__m128i v)
{
    return _mm_extract_epi32(v, index);
}
Vc_INTRINSIC Vc_CONST __m128d blendv_pd(__m128d a, __m128d b, __m128d c)
{
    return _mm_blendv_pd(a, b, c);
}
Vc_INTRINSIC Vc_CONST __m128 blendv_ps(__m128 a, __m128 b, __m128 c)
{
    return _mm_blendv_ps(a, b, c);
}
Vc_INTRINSIC Vc_CONST __m128i blendv_epi8(__m128i a, __m128i b, __m128i c)
{
    return _mm_blendv_epi8(a, b, c);
}
Vc_INTRINSIC Vc_CONST __m128i max_epi8(__m128i a, __m128i b)
{
    return _mm_max_epi8(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i max_epi32(__m128i a, __m128i b)
{
    return _mm_max_epi32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i max_epu16(__m128i a, __m128i b)
{
    return _mm_max_epu16(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i max_epu32(__m128i a, __m128i b)
{
    return _mm_max_epu32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epu16(__m128i a, __m128i b)
{
    return _mm_min_epu16(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epu32(__m128i a, __m128i b)
{
    return _mm_min_epu32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epi8(__m128i a, __m128i b)
{
    return _mm_min_epi8(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epi32(__m128i a, __m128i b)
{
    return _mm_min_epi32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi16(__m128i epu8)
{
    return _mm_cvtepu8_epi16(epu8);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi16(__m128i epi8)
{
    return _mm_cvtepi8_epi16(epi8);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu16_epi32(__m128i epu16)
{
    return _mm_cvtepu16_epi32(epu16);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi16_epi32(__m128i epu16)
{
    return _mm_cvtepi16_epi32(epu16);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi32(__m128i epu8)
{
    return _mm_cvtepu8_epi32(epu8);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi32(__m128i epi8)
{
    return _mm_cvtepi8_epi32(epi8);
}
Vc_INTRINSIC Vc_PURE __m128i stream_load_si128(__m128i *mem)
{
    return _mm_stream_load_si128(mem);
}
#else
Vc_INTRINSIC Vc_CONST __m128 blendv_ps(__m128 a, __m128 b, __m128 c) {
    return _mm_or_ps(_mm_andnot_ps(c, a), _mm_and_ps(c, b));
}
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST __m128d blendv_pd(__m128d a, __m128d b, __m128d c) {
    return _mm_or_pd(_mm_andnot_pd(c, a), _mm_and_pd(c, b));
}
Vc_INTRINSIC Vc_CONST __m128i blendv_epi8(__m128i a, __m128i b, __m128i c) {
    return _mm_or_si128(_mm_andnot_si128(c, a), _mm_and_si128(c, b));
}
Vc_INTRINSIC Vc_CONST __m128i cmpeq_epi64(__m128i a, __m128i b) {
    auto tmp = _mm_cmpeq_epi32(a, b);
    return _mm_and_si128(tmp, _mm_shuffle_epi32(tmp, 1*1 + 0*4 + 3*16 + 2*64));
}
template <int index> Vc_INTRINSIC Vc_CONST int extract_epi32(__m128i v)
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    typedef int int32v4 __attribute__((__vector_size__(16)));
    return reinterpret_cast<const may_alias<int32v4> &>(v)[index];
#else
    return _mm_cvtsi128_si32(_mm_srli_si128(v, index * 4));
#endif
}
Vc_INTRINSIC Vc_CONST __m128i max_epi8 (__m128i a, __m128i b) {
    return blendv_epi8(b, a, _mm_cmpgt_epi8 (a, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epi32(__m128i a, __m128i b) {
    return blendv_epi8(b, a, _mm_cmpgt_epi32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epu16(__m128i a, __m128i b) {
    return blendv_epi8(b, a, cmpgt_epu16(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epu32(__m128i a, __m128i b) {
    return blendv_epi8(b, a, cmpgt_epu32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epu16(__m128i a, __m128i b) {
    return blendv_epi8(a, b, cmpgt_epu16(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epu32(__m128i a, __m128i b) {
    return blendv_epi8(a, b, cmpgt_epu32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epi8 (__m128i a, __m128i b) {
    return blendv_epi8(a, b, _mm_cmpgt_epi8 (a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epi32(__m128i a, __m128i b) {
    return blendv_epi8(a, b, _mm_cmpgt_epi32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi16(__m128i epu8) {
    return _mm_unpacklo_epi8(epu8, _mm_setzero_si128());
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi16(__m128i epi8) {
    return _mm_unpacklo_epi8(epi8, _mm_cmplt_epi8(epi8, _mm_setzero_si128()));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu16_epi32(__m128i epu16) {
    return _mm_unpacklo_epi16(epu16, _mm_setzero_si128());
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi16_epi32(__m128i epu16) {
    return _mm_unpacklo_epi16(epu16, _mm_cmplt_epi16(epu16, _mm_setzero_si128()));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi32(__m128i epu8) {
    return cvtepu16_epi32(cvtepu8_epi16(epu8));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi32(__m128i epi8) {
    const __m128i neg = _mm_cmplt_epi8(epi8, _mm_setzero_si128());
    const __m128i epi16 = _mm_unpacklo_epi8(epi8, neg);
    return _mm_unpacklo_epi16(epi16, _mm_unpacklo_epi8(neg, neg));
}
Vc_INTRINSIC Vc_PURE __m128i stream_load_si128(__m128i *mem) {
    return _mm_load_si128(mem);
}
#endif
#endif
Vc_INTRINSIC Vc_CONST __m128 blend(__m128 mask, __m128 at0, __m128 at1)
{
    return blendv_ps(at0, at1, mask);
}
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST __m128d blend(__m128d mask, __m128d at0, __m128d at1)
{
    return blendv_pd(at0, at1, mask);
}
Vc_INTRINSIC Vc_CONST __m128i blend(__m128i mask, __m128i at0, __m128i at1)
{
    return blendv_epi8(at0, at1, mask);
}
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST __m256 blend(__m256 mask, __m256 at0, __m256 at1)
{
    return _mm256_blendv_ps(at0, at1, mask);
}
Vc_INTRINSIC Vc_CONST __m256d blend(__m256d mask, __m256d at0, __m256d at1)
{
    return _mm256_blendv_pd(at0, at1, mask);
}
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC Vc_CONST __m256i blend(__m256i mask, __m256i at0, __m256i at1)
{
    return _mm256_blendv_epi8(at0, at1, mask);
}
#endif
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST __mmask8 blend(__mmask8 mask, __mmask8 at0, __mmask8 at1)
{
    return (mask & at1) | (~mask & at0);
}
Vc_INTRINSIC Vc_CONST __mmask16 blend(__mmask16 mask, __mmask16 at0, __mmask16 at1)
{
    return _mm512_kor(_mm512_kand(mask, at1), _mm512_kandn(mask, at0));
}
Vc_INTRINSIC Vc_CONST __m512 blend(__mmask16 mask, __m512 at0, __m512 at1)
{
    return _mm512_mask_mov_ps(at0, mask, at1);
}
Vc_INTRINSIC Vc_CONST __m512d blend(__mmask8 mask, __m512d at0, __m512d at1)
{
    return _mm512_mask_mov_pd(at0, mask, at1);
}
Vc_INTRINSIC Vc_CONST __m512i blend(__mmask8 mask, __m512i at0, __m512i at1)
{
    return _mm512_mask_mov_epi64(at0, mask, at1);
}
Vc_INTRINSIC Vc_CONST __m512i blend(__mmask16 mask, __m512i at0, __m512i at1)
{
    return _mm512_mask_mov_epi32(at0, mask, at1);
}
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC Vc_CONST __mmask32 blend(__mmask32 mask, __mmask32 at0, __mmask32 at1)
{
    return (mask & at1) | (~mask & at0);
}
Vc_INTRINSIC Vc_CONST __mmask64 blend(__mmask64 mask, __mmask64 at0, __mmask64 at1)
{
    return (mask & at1) | (~mask & at0);
}
Vc_INTRINSIC Vc_CONST __m512i blend(__mmask32 mask, __m512i at0, __m512i at1)
{
    return _mm512_mask_mov_epi16(at0, mask, at1);
}
Vc_INTRINSIC Vc_CONST __m512i blend(__mmask64 mask, __m512i at0, __m512i at1)
{
    return _mm512_mask_mov_epi8(at0, mask, at1);
}
#endif
#endif
#ifdef Vc_HAVE_SSE4_1
Vc_INTRINSIC Vc_CONST int testc(__m128 a, __m128 b) { return _mm_testc_si128(_mm_castps_si128(a), _mm_castps_si128(b)); }
Vc_INTRINSIC Vc_CONST int testc(__m128d a, __m128d b) { return _mm_testc_si128(_mm_castpd_si128(a), _mm_castpd_si128(b)); }
Vc_INTRINSIC Vc_CONST int testc(__m128i a, __m128i b) { return _mm_testc_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST int testc(__m256 a, __m256 b) { return _mm256_testc_ps(a, b); }
Vc_INTRINSIC Vc_CONST int testc(__m256d a, __m256d b) { return _mm256_testc_pd(a, b); }
Vc_INTRINSIC Vc_CONST int testc(__m256i a, __m256i b) { return _mm256_testc_si256(a, b); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC Vc_CONST bool testallset(__mmask8 a) { return a == 0xffU; }
Vc_INTRINSIC Vc_CONST bool testallset(__mmask16 a)
{
#ifdef Vc_GCC
    return a == 0xffffU;
#else
    return _mm512_kortestc(a, a);
#endif
}
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC Vc_CONST bool testallset(__mmask32 a) { return a == 0xffffffffU; }
Vc_INTRINSIC Vc_CONST bool testallset(__mmask64 a) { return a == 0xffffffffffffffffULL; }
#endif
#endif
#ifdef Vc_HAVE_SSE4_1
Vc_INTRINSIC Vc_CONST int testz(__m128 a, __m128 b) { return _mm_testz_si128(_mm_castps_si128(a), _mm_castps_si128(b)); }
Vc_INTRINSIC Vc_CONST int testz(__m128d a, __m128d b) { return _mm_testz_si128(_mm_castpd_si128(a), _mm_castpd_si128(b)); }
Vc_INTRINSIC Vc_CONST int testz(__m128i a, __m128i b) { return _mm_testz_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST int testz(__m256 a, __m256 b) { return _mm256_testz_ps(a, b); }
Vc_INTRINSIC Vc_CONST int testz(__m256d a, __m256d b) { return _mm256_testz_pd(a, b); }
Vc_INTRINSIC Vc_CONST int testz(__m256i a, __m256i b) { return _mm256_testz_si256(a, b); }
#endif
#ifdef Vc_HAVE_SSE4_1
Vc_INTRINSIC Vc_CONST int testnzc(__m128 a, __m128 b) { return _mm_testnzc_si128(_mm_castps_si128(a), _mm_castps_si128(b)); }
Vc_INTRINSIC Vc_CONST int testnzc(__m128d a, __m128d b) { return _mm_testnzc_si128(_mm_castpd_si128(a), _mm_castpd_si128(b)); }
Vc_INTRINSIC Vc_CONST int testnzc(__m128i a, __m128i b) { return _mm_testnzc_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST int testnzc(__m256 a, __m256 b) { return _mm256_testnzc_ps(a, b); }
Vc_INTRINSIC Vc_CONST int testnzc(__m256d a, __m256d b) { return _mm256_testnzc_pd(a, b); }
Vc_INTRINSIC Vc_CONST int testnzc(__m256i a, __m256i b) { return _mm256_testnzc_si256(a, b); }
#endif
Vc_INTRINSIC Vc_CONST int movemask(__m128 a) { return _mm_movemask_ps(a); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST int movemask(__m128d a) { return _mm_movemask_pd(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m128i a) { return _mm_movemask_epi8(a); }
Vc_INTRINSIC Vc_CONST int movemask_epi16(__m128i a) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    return _mm_cmp_epi16_mask(a, zero<__m128i>(), _MM_CMPINT_NE);
#else
    return _mm_movemask_epi8(_mm_packs_epi16(a, zero<__m128i>()));
#endif
}
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC Vc_CONST int movemask(__m256i a) {
#ifdef Vc_HAVE_AVX2
    return _mm256_movemask_epi8(a);
#else
    return _mm_movemask_epi8(lo128(a)) | (_mm_movemask_epi8(hi128(a)) << 16);
#endif
}
Vc_INTRINSIC Vc_CONST int movemask(__m256d a) { return _mm256_movemask_pd(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m256 a) { return _mm256_movemask_ps(a); }
Vc_INTRINSIC Vc_CONST int movemask_epi16(__m256i a) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    return _mm256_cmp_epi16_mask(a, zero<__m256i>(), _MM_CMPINT_NE);
#else
    return _mm_movemask_epi8(_mm_packs_epi16(lo128(a), hi128(a)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <size_t VectorSize> struct convert_mask_return_type;
template <> struct convert_mask_return_type<16> { using type = __m128i; };
template <> struct convert_mask_return_type<32> { using type = __m256i; };
template <> struct convert_mask_return_type<64> { using type = __m512i; };
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(__mmask8);
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(__mmask16);
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(__mmask32);
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(__mmask64);
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(std::bitset<2> bs)
{
    static_assert(VectorSize / EntrySize == 2, "");
    return convert_mask<EntrySize, VectorSize>(__mmask8(bs.to_ullong()));
}
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(std::bitset<4> bs)
{
    static_assert(VectorSize / EntrySize == 4, "");
    return convert_mask<EntrySize, VectorSize>(__mmask8(bs.to_ullong()));
}
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(std::bitset<8> bs)
{
    static_assert(VectorSize / EntrySize == 8, "");
    return convert_mask<EntrySize, VectorSize>(__mmask8(bs.to_ullong()));
}
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(std::bitset<16> bs)
{
    static_assert(VectorSize / EntrySize == 16, "");
    return convert_mask<EntrySize, VectorSize>(__mmask16(bs.to_ullong()));
}
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(std::bitset<32> bs)
{
    static_assert(VectorSize / EntrySize == 32, "");
    return convert_mask<EntrySize, VectorSize>(__mmask32(bs.to_ullong()));
}
template <size_t EntrySize, size_t VectorSize>
inline typename convert_mask_return_type<VectorSize>::type convert_mask(std::bitset<64> bs)
{
    static_assert(VectorSize / EntrySize == 64, "");
    return convert_mask<EntrySize, VectorSize>(__mmask64(bs.to_ullong()));
}
#ifdef Vc_HAVE_AVX512VL
#ifdef Vc_HAVE_AVX512BW
template <> Vc_INTRINSIC __m128i convert_mask<1, 16>(__mmask16 k) { return _mm_movm_epi8 (k); }
template <> Vc_INTRINSIC __m128i convert_mask<2, 16>(__mmask8 k) { return _mm_movm_epi16(k); }
template <> Vc_INTRINSIC __m256i convert_mask<1, 32>(__mmask32 k) { return _mm256_movm_epi8 (k); }
template <> Vc_INTRINSIC __m256i convert_mask<2, 32>(__mmask16 k) { return _mm256_movm_epi16(k); }
#endif
#ifdef Vc_HAVE_AVX512DQ
template <> Vc_INTRINSIC __m128i convert_mask<4, 16>(__mmask8 k) { return _mm_movm_epi32(k); }
template <> Vc_INTRINSIC __m128i convert_mask<8, 16>(__mmask8 k) { return _mm_movm_epi64(k); }
template <> Vc_INTRINSIC __m256i convert_mask<4, 32>(__mmask8 k) { return _mm256_movm_epi32(k); }
template <> Vc_INTRINSIC __m256i convert_mask<8, 32>(__mmask8 k) { return _mm256_movm_epi64(k); }
#endif
#else
#ifdef Vc_HAVE_AVX512BW
template <> Vc_INTRINSIC __m128i convert_mask<1, 16>(__mmask16 k) { return lo128(_mm512_movm_epi8 (k)); }
template <> Vc_INTRINSIC __m128i convert_mask<2, 16>(__mmask8 k) { return lo128(_mm512_movm_epi16(k)); }
template <> Vc_INTRINSIC __m256i convert_mask<1, 32>(__mmask32 k) { return lo256(_mm512_movm_epi8 (k)); }
template <> Vc_INTRINSIC __m256i convert_mask<2, 32>(__mmask16 k) { return lo256(_mm512_movm_epi16(k)); }
#endif
#ifdef Vc_HAVE_AVX512DQ
template <> Vc_INTRINSIC __m128i convert_mask<4, 16>(__mmask8 k) { return lo128(_mm512_movm_epi32(k)); }
template <> Vc_INTRINSIC __m128i convert_mask<8, 16>(__mmask8 k) { return lo128(_mm512_movm_epi64(k)); }
template <> Vc_INTRINSIC __m256i convert_mask<4, 32>(__mmask8 k) { return lo256(_mm512_movm_epi32(k)); }
template <> Vc_INTRINSIC __m256i convert_mask<8, 32>(__mmask8 k) { return lo256(_mm512_movm_epi64(k)); }
#endif
#endif
#ifdef Vc_HAVE_AVX512BW
template <> Vc_INTRINSIC __m512i convert_mask<1, 64>(__mmask64 k) { return _mm512_movm_epi8 (k); }
template <> Vc_INTRINSIC __m512i convert_mask<2, 64>(__mmask32 k) { return _mm512_movm_epi16(k); }
#endif
#ifdef Vc_HAVE_AVX512DQ
template <> Vc_INTRINSIC __m512i convert_mask<4, 64>(__mmask16 k) { return _mm512_movm_epi32(k); }
template <> Vc_INTRINSIC __m512i convert_mask<8, 64>(__mmask8 k) { return _mm512_movm_epi64(k); }
#endif
#endif
Vc_ALWAYS_INLINE Vc_CONST __m128 negate(__m128 v, std::integral_constant<std::size_t, 4>)
{
    return _mm_xor_ps(v, signmask16(float()));
}
#ifdef Vc_HAVE_SSE2
Vc_ALWAYS_INLINE Vc_CONST __m128d negate(__m128d v, std::integral_constant<std::size_t, 8>)
{
    return _mm_xor_pd(v, signmask16(double()));
}
Vc_ALWAYS_INLINE Vc_CONST __m128i negate(__m128i v, std::integral_constant<std::size_t, 4>)
{
#ifdef Vc_IMPL_SSSE3
    return _mm_sign_epi32(v, allone<__m128i>());
#else
    return _mm_sub_epi32(zero<__m128i>(), v);
#endif
}
Vc_ALWAYS_INLINE Vc_CONST __m128i negate(__m128i v, std::integral_constant<std::size_t, 2>)
{
#ifdef Vc_IMPL_SSSE3
    return _mm_sign_epi16(v, allone<__m128i>());
#else
    return _mm_sub_epi16(zero<__m128i>(), v);
#endif
}
#endif
#ifdef Vc_HAVE_AVX
Vc_ALWAYS_INLINE Vc_CONST __m256 negate(__m256 v, std::integral_constant<std::size_t, 4>)
{
    return _mm256_xor_ps(v, signmask32(float()));
}
Vc_ALWAYS_INLINE Vc_CONST __m256d negate(__m256d v, std::integral_constant<std::size_t, 8>)
{
    return _mm256_xor_pd(v, signmask32(double()));
}
#ifdef Vc_HAVE_AVX2
Vc_ALWAYS_INLINE Vc_CONST __m256i negate(__m256i v, std::integral_constant<std::size_t, 4>)
{
    return _mm256_sign_epi32(v, allone<__m256i>());
}
Vc_ALWAYS_INLINE Vc_CONST __m256i negate(__m256i v, std::integral_constant<std::size_t, 2>)
{
    return _mm256_sign_epi16(v, allone<__m256i>());
}
Vc_ALWAYS_INLINE Vc_CONST __m256i negate(__m256i v, std::integral_constant<std::size_t, 1>)
{
    return _mm256_sign_epi8(v, allone<__m256i>());
}
#endif
#endif
Vc_INTRINSIC __m128 xor_(__m128 a, __m128 b) { return _mm_xor_ps(a, b); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d xor_(__m128d a, __m128d b) { return _mm_xor_pd(a, b); }
Vc_INTRINSIC __m128i xor_(__m128i a, __m128i b) { return _mm_xor_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 xor_(__m256 a, __m256 b) { return _mm256_xor_ps(a, b); }
Vc_INTRINSIC __m256d xor_(__m256d a, __m256d b) { return _mm256_xor_pd(a, b); }
Vc_INTRINSIC __m256i xor_(__m256i a, __m256i b) {
#ifdef Vc_HAVE_AVX2
    return _mm256_xor_si256(a, b);
#else
    return _mm256_castps_si256(xor_(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
#ifdef Vc_HAVE_AVX512DQ
Vc_INTRINSIC __m512 xor_(__m512 a, __m512 b) { return _mm512_xor_ps(a, b); }
Vc_INTRINSIC __m512d xor_(__m512d a, __m512d b) { return _mm512_xor_pd(a, b); }
#else
Vc_INTRINSIC __m512 xor_(__m512 a, __m512 b)
{
    return intrin_cast<__m512>(
        _mm512_xor_epi32(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)));
}
Vc_INTRINSIC __m512d xor_(__m512d a, __m512d b)
{
    return intrin_cast<__m512d>(
        _mm512_xor_epi64(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)));
}
#endif
Vc_INTRINSIC __m512i xor_(__m512i a, __m512i b) { return _mm512_xor_epi32(a, b); }
#endif
Vc_INTRINSIC __m128 or_(__m128 a, __m128 b) { return _mm_or_ps(a, b); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d or_(__m128d a, __m128d b) { return _mm_or_pd(a, b); }
Vc_INTRINSIC __m128i or_(__m128i a, __m128i b) { return _mm_or_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 or_(__m256 a, __m256 b) { return _mm256_or_ps(a, b); }
Vc_INTRINSIC __m256d or_(__m256d a, __m256d b) { return _mm256_or_pd(a, b); }
Vc_INTRINSIC __m256i or_(__m256i a, __m256i b) {
#ifdef Vc_HAVE_AVX2
    return _mm256_or_si256(a, b);
#else
    return _mm256_castps_si256(or_(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 or_(__m512 a, __m512 b) { return _mm512_or_ps(a, b); }
Vc_INTRINSIC __m512d or_(__m512d a, __m512d b) { return _mm512_or_pd(a, b); }
Vc_INTRINSIC __m512i or_(__m512i a, __m512i b) { return _mm512_or_epi32(a, b); }
#endif
Vc_INTRINSIC __m128 and_(__m128 a, __m128 b) { return _mm_and_ps(a, b); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d and_(__m128d a, __m128d b) { return _mm_and_pd(a, b); }
Vc_INTRINSIC __m128i and_(__m128i a, __m128i b) { return _mm_and_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 and_(__m256 a, __m256 b) { return _mm256_and_ps(a, b); }
Vc_INTRINSIC __m256d and_(__m256d a, __m256d b) { return _mm256_and_pd(a, b); }
Vc_INTRINSIC __m256i and_(__m256i a, __m256i b) {
#ifdef Vc_HAVE_AVX2
    return _mm256_and_si256(a, b);
#else
    return _mm256_castps_si256(and_(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512i and_(__m512i a, __m512i b) { return _mm512_and_epi32(a, b); }
#ifdef Vc_HAVE_AVX512DQ
Vc_INTRINSIC __m512 and_(__m512 a, __m512 b) { return _mm512_and_ps(a, b); }
Vc_INTRINSIC __m512d and_(__m512d a, __m512d b) { return _mm512_and_pd(a, b); }
#else
Vc_INTRINSIC __m512 and_(__m512 a, __m512 b) { return _mm512_castsi512_ps(and_(_mm512_castps_si512(a),_mm512_castps_si512(b))); }
Vc_INTRINSIC __m512d and_(__m512d a, __m512d b) { return _mm512_castsi512_pd(and_(_mm512_castpd_si512(a),_mm512_castpd_si512(b))); }
#endif
#endif
Vc_INTRINSIC __m128 andnot_(__m128 a, __m128 b) { return _mm_andnot_ps(a, b); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d andnot_(__m128d a, __m128d b) { return _mm_andnot_pd(a, b); }
Vc_INTRINSIC __m128i andnot_(__m128i a, __m128i b) { return _mm_andnot_si128(a, b); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 andnot_(__m256 a, __m256 b) { return _mm256_andnot_ps(a, b); }
Vc_INTRINSIC __m256d andnot_(__m256d a, __m256d b) { return _mm256_andnot_pd(a, b); }
Vc_INTRINSIC __m256i andnot_(__m256i a, __m256i b) {
#ifdef Vc_HAVE_AVX2
    return _mm256_andnot_si256(a, b);
#else
    return _mm256_castps_si256(andnot_(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 andnot_(__m512 a, __m512 b) { return _mm512_andnot_ps(a, b); }
Vc_INTRINSIC __m512d andnot_(__m512d a, __m512d b) { return _mm512_andnot_pd(a, b); }
Vc_INTRINSIC __m512i andnot_(__m512i a, __m512i b) { return _mm512_andnot_epi32(a, b); }
Vc_INTRINSIC __m512d andnot_(__mmask8 k, __m512d a) { return _mm512_maskz_mov_pd(~k, a); }
Vc_INTRINSIC __m512 andnot_(__mmask16 k, __m512 a) { return _mm512_maskz_mov_ps(~k, a); }
Vc_INTRINSIC __m512i andnot_(__mmask8 k, __m512i a) { return _mm512_maskz_mov_epi64(~k, a); }
Vc_INTRINSIC __m512i andnot_(__mmask16 k, __m512i a) { return _mm512_maskz_mov_epi32(~k, a); }
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC __m512i andnot_(__mmask32 k, __m512i a) { return _mm512_maskz_mov_epi16(~k, a); }
Vc_INTRINSIC __m512i andnot_(__mmask64 k, __m512i a) { return _mm512_maskz_mov_epi8 (~k, a); }
#endif
#endif
Vc_INTRINSIC __m128 not_(__m128 a) { return andnot_(a, allone<__m128 >()); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d not_(__m128d a) { return andnot_(a, allone<__m128d>()); }
Vc_INTRINSIC __m128i not_(__m128i a) { return andnot_(a, allone<__m128i>()); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 not_(__m256 a) { return andnot_(a, allone<__m256 >()); }
Vc_INTRINSIC __m256d not_(__m256d a) { return andnot_(a, allone<__m256d>()); }
Vc_INTRINSIC __m256i not_(__m256i a) { return andnot_(a, allone<__m256i>()); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 not_(__m512 a) { return andnot_(a, allone<__m512 >()); }
Vc_INTRINSIC __m512d not_(__m512d a) { return andnot_(a, allone<__m512d>()); }
Vc_INTRINSIC __m512i not_(__m512i a) { return andnot_(a, allone<__m512i>()); }
Vc_INTRINSIC __mmask8 not_(__mmask8 a) { return ~a; }
Vc_INTRINSIC __mmask16 not_(__mmask16 a) { return ~a; }
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC __mmask32 not_(__mmask32 a) { return ~a; }
Vc_INTRINSIC __mmask64 not_(__mmask64 a) { return ~a; }
#endif
#endif
#ifdef Vc_HAVE_SSE2
template <int n> Vc_INTRINSIC __m128 shift_left(__m128 v) { return _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(v), n)); }
template <int n> Vc_INTRINSIC __m128d shift_left(__m128d v) { return _mm_castsi128_pd(_mm_slli_si128(_mm_castpd_si128(v), n)); }
template <int n> Vc_INTRINSIC __m128i shift_left(__m128i v) { return _mm_slli_si128(v, n); }
#endif
#ifdef Vc_HAVE_AVX2
template <int n> Vc_INTRINSIC __m256 shift_left(__m256 v)
{
    __m256i vi = _mm256_castps_si256(v);
    return _mm256_castsi256_ps(
        n < 16 ? _mm256_slli_si256(vi, n)
               : _mm256_slli_si256(_mm256_permute2x128_si256(vi, vi, 0x08), n));
}
template <int n> Vc_INTRINSIC __m256d shift_left(__m256d v)
{
    __m256i vi = _mm256_castpd_si256(v);
    return _mm256_castsi256_pd(
        n < 16 ? _mm256_slli_si256(vi, n)
               : _mm256_slli_si256(_mm256_permute2x128_si256(vi, vi, 0x08), n));
}
template <int n> Vc_INTRINSIC __m256i shift_left(__m256i v)
{
    return _mm256_castsi256_pd(
        n < 16 ? _mm256_slli_si256(v, n)
               : _mm256_slli_si256(_mm256_permute2x128_si256(v, v, 0x08), n));
}
#endif
template <int n> Vc_INTRINSIC __m128 shift_right(__m128 v);
template <> Vc_INTRINSIC __m128 shift_right< 0>(__m128 v) { return v; }
template <> Vc_INTRINSIC __m128 shift_right<16>(__m128 ) { return _mm_setzero_ps(); }
#ifdef Vc_HAVE_SSE2
template <int n> Vc_INTRINSIC __m128 shift_right(__m128 v) { return _mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v), n)); }
template <int n> Vc_INTRINSIC __m128d shift_right(__m128d v) { return _mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(v), n)); }
template <int n> Vc_INTRINSIC __m128i shift_right(__m128i v) { return _mm_srli_si128(v, n); }
template <> Vc_INTRINSIC __m128 shift_right< 8>(__m128 v) { return _mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(v), _mm_setzero_pd())); }
template <> Vc_INTRINSIC __m128d shift_right< 0>(__m128d v) { return v; }
template <> Vc_INTRINSIC __m128d shift_right< 8>(__m128d v) { return _mm_unpackhi_pd(v, _mm_setzero_pd()); }
template <> Vc_INTRINSIC __m128d shift_right<16>(__m128d ) { return _mm_setzero_pd(); }
template <> Vc_INTRINSIC __m128i shift_right< 0>(__m128i v) { return v; }
template <> Vc_INTRINSIC __m128i shift_right<16>(__m128i ) { return _mm_setzero_si128(); }
#endif
#ifdef Vc_HAVE_AVX2
template <int n> Vc_INTRINSIC __m256 shift_right(__m256 v)
{
    __m256i vi = _mm256_castps_si256(v);
    return _mm256_castsi256_ps(
        n < 16 ? _mm256_srli_si256(vi, n)
               : _mm256_srli_si256(_mm256_permute2x128_si256(vi, vi, 0x81), n));
}
template <> Vc_INTRINSIC __m256 shift_right<0>(__m256 v) { return v; }
template <> Vc_INTRINSIC __m256 shift_right<16>(__m256 v) { return intrin_cast<__m256>(lo128(v)); }
template <int n> Vc_INTRINSIC __m256d shift_right(__m256d v)
{
    __m256i vi = _mm256_castpd_si256(v);
    return _mm256_castsi256_pd(
        n < 16 ? _mm256_srli_si256(vi, n)
               : _mm256_srli_si256(_mm256_permute2x128_si256(vi, vi, 0x81), n));
}
template <> Vc_INTRINSIC __m256d shift_right<0>(__m256d v) { return v; }
template <> Vc_INTRINSIC __m256d shift_right<16>(__m256d v) { return intrin_cast<__m256d>(lo128(v)); }
template <int n> Vc_INTRINSIC __m256i shift_right(__m256i v)
{
    return n < 16 ? _mm256_srli_si256(v, n)
                  : _mm256_srli_si256(_mm256_permute2x128_si256(v, v, 0x81), n);
}
template <> Vc_INTRINSIC __m256i shift_right<0>(__m256i v) { return v; }
template <> Vc_INTRINSIC __m256i shift_right<16>(__m256i v) { return _mm256_permute2x128_si256(v, v, 0x81); }
#endif
Vc_INTRINSIC Vc_CONST unsigned int popcnt4(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
    return _mm_popcnt_u32(n);
#else
    n = (n & 0x5U) + ((n >> 1) & 0x5U);
    n = (n & 0x3U) + ((n >> 2) & 0x3U);
    return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt8(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
    return _mm_popcnt_u32(n);
#else
    n = (n & 0x55U) + ((n >> 1) & 0x55U);
    n = (n & 0x33U) + ((n >> 2) & 0x33U);
    n = (n & 0x0fU) + ((n >> 4) & 0x0fU);
    return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt16(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
    return _mm_popcnt_u32(n);
#else
    n = (n & 0x5555U) + ((n >> 1) & 0x5555U);
    n = (n & 0x3333U) + ((n >> 2) & 0x3333U);
    n = (n & 0x0f0fU) + ((n >> 4) & 0x0f0fU);
    n = (n & 0x00ffU) + ((n >> 8) & 0x00ffU);
    return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt32(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
    return _mm_popcnt_u32(n);
#else
    n = (n & 0x55555555U) + ((n >> 1) & 0x55555555U);
    n = (n & 0x33333333U) + ((n >> 2) & 0x33333333U);
    n = (n & 0x0f0f0f0fU) + ((n >> 4) & 0x0f0f0f0fU);
    n = (n & 0x00ff00ffU) + ((n >> 8) & 0x00ff00ffU);
    n = (n & 0x0000ffffU) + ((n >>16) & 0x0000ffffU);
    return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt64(ullong n)
{
#ifdef Vc_IMPL_POPCNT
#ifdef Vc_IS_AMD64
    return _mm_popcnt_u64(n);
#else
    return _mm_popcnt_u32(n) + _mm_popcnt_u32(n >> 32u);
#endif
#else
    n = (n & 0x5555555555555555ULL) + ((n >> 1) & 0x5555555555555555ULL);
    n = (n & 0x3333333333333333ULL) + ((n >> 2) & 0x3333333333333333ULL);
    n = (n & 0x0f0f0f0f0f0f0f0fULL) + ((n >> 4) & 0x0f0f0f0f0f0f0f0fULL);
    n = (n & 0x00ff00ff00ff00ffULL) + ((n >> 8) & 0x00ff00ff00ff00ffULL);
    n = (n & 0x0000ffff0000ffffULL) + ((n >>16) & 0x0000ffff0000ffffULL);
    n = (n & 0x00000000ffffffffULL) + ((n >>32) & 0x00000000ffffffffULL);
    return n;
#endif
}
Vc_INTRINSIC Vc_CONST int firstbit(ullong bits)
{
#ifdef Vc_HAVE_BMI1
#ifdef Vc_IS_AMD64
    return _tzcnt_u64(bits);
#else
    uint lo = bits;
    uint hi = bits >> 32u;
    if (lo == 0u) {
        return 32u + _tzcnt_u32(hi);
    } else {
        return _tzcnt_u32(lo);
    }
#endif
#else
    return __builtin_ctzll(bits);
#endif
}
#ifdef Vc_MSVC
#pragma intrinsic(_BitScanForward)
#pragma intrinsic(_BitScanReverse)
#endif
Vc_INTRINSIC Vc_CONST auto firstbit(uint x)
{
#if defined Vc_ICC || defined Vc_GCC
    return _bit_scan_forward(x);
#elif defined Vc_CLANG || defined Vc_APPLECLANG
    return __builtin_ctz(x);
#elif defined Vc_MSVC
    unsigned long index;
    _BitScanForward(&index, x);
    return index;
#else
#error "Implementation for firstbit(uint) is missing"
#endif
}
Vc_INTRINSIC Vc_CONST auto firstbit(llong bits) { return firstbit(ullong(bits)); }
#if LONG_MAX == LLONG_MAX
Vc_INTRINSIC Vc_CONST auto firstbit(ulong bits) { return firstbit(ullong(bits)); }
Vc_INTRINSIC Vc_CONST auto firstbit(long bits) { return firstbit(ullong(bits)); }
#endif
template <class T> Vc_INTRINSIC Vc_CONST auto firstbit(T bits)
{
    static_assert(sizeof(T) <= sizeof(uint),
                  "there's a missing overload to call the 64-bit variant");
    return firstbit(uint(bits));
}
Vc_INTRINSIC Vc_CONST int lastbit(ullong bits)
{
#ifdef Vc_HAVE_BMI1
#ifdef Vc_IS_AMD64
    return 63u - _lzcnt_u64(bits);
#else
    uint lo = bits;
    uint hi = bits >> 32u;
    if (hi == 0u) {
        return 31u - _lzcnt_u32(lo);
    } else {
        return 63u - _lzcnt_u32(hi);
    }
#endif
#else
    return 63 - __builtin_clzll(bits);
#endif
}
Vc_INTRINSIC Vc_CONST auto lastbit(uint x)
{
#if defined Vc_ICC || defined Vc_GCC
    return _bit_scan_reverse(x);
#elif defined Vc_CLANG || defined Vc_APPLECLANG
    return 31 - __builtin_clz(x);
#elif defined(Vc_MSVC)
    unsigned long index;
    _BitScanReverse(&index, x);
    return index;
#else
#error "Implementation for lastbit(uint) is missing"
#endif
}
Vc_INTRINSIC Vc_CONST auto lastbit(llong bits) { return lastbit(ullong(bits)); }
#if LONG_MAX == LLONG_MAX
Vc_INTRINSIC Vc_CONST auto lastbit(ulong bits) { return lastbit(ullong(bits)); }
Vc_INTRINSIC Vc_CONST auto lastbit(long bits) { return lastbit(ullong(bits)); }
#endif
template <class T> Vc_INTRINSIC Vc_CONST auto lastbit(T bits)
{
    static_assert(sizeof(T) <= sizeof(uint),
                  "there's a missing overload to call the 64-bit variant");
    return lastbit(uint(bits));
}
template <size_t Size> int mask_count(__m128 );
template<> Vc_INTRINSIC Vc_CONST int mask_count<4>(__m128 k)
{
#ifdef Vc_IMPL_POPCNT
    return _mm_popcnt_u32(_mm_movemask_ps(k));
#elif defined Vc_HAVE_SSE2
    auto x = _mm_srli_epi32(_mm_castps_si128(k), 31);
    x = _mm_add_epi32(x, _mm_shuffle_epi32(x, _MM_SHUFFLE(0, 1, 2, 3)));
    x = _mm_add_epi32(x, _mm_shufflelo_epi16(x, _MM_SHUFFLE(1, 0, 3, 2)));
    return _mm_cvtsi128_si32(x);
#else
    return popcnt4(_mm_movemask_ps(k));
#endif
}
#ifdef Vc_HAVE_SSE2
template <size_t Size> int mask_count(__m128i);
template <size_t Size> int mask_count(__m128d);
template<> Vc_INTRINSIC Vc_CONST int mask_count<2>(__m128d k)
{
    int mask = _mm_movemask_pd(k);
    return (mask & 1) + (mask >> 1);
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<2>(__m128i k)
{
    return mask_count<2>(_mm_castsi128_pd(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<4>(__m128i k)
{
    return mask_count<4>(_mm_castsi128_ps(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<8>(__m128i k)
{
#ifdef Vc_IMPL_POPCNT
    return _mm_popcnt_u32(_mm_movemask_epi8(k)) / 2;
#else
    auto x = srli_epi16<15>(k);
    x = _mm_add_epi16(x, _mm_shuffle_epi32(x, _MM_SHUFFLE(0, 1, 2, 3)));
    x = _mm_add_epi16(x, _mm_shufflelo_epi16(x, _MM_SHUFFLE(0, 1, 2, 3)));
    x = _mm_add_epi16(x, _mm_shufflelo_epi16(x, _MM_SHUFFLE(2, 3, 0, 1)));
    return _mm_extract_epi16(x, 0);
#endif
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<16>(__m128i k)
{
    return popcnt16(_mm_movemask_epi8(k));
}
#endif
template <size_t Size> inline int mask_to_int(__m128 ) { static_assert(Size == Size, "Size value not implemented"); return 0; }
#ifdef Vc_HAVE_SSE2
template <size_t Size> inline int mask_to_int(__m128d) { static_assert(Size == Size, "Size value not implemented"); return 0; }
template <size_t Size> inline int mask_to_int(__m128i) { static_assert(Size == Size, "Size value not implemented"); return 0; }
#endif
#ifdef Vc_HAVE_AVX
template <size_t Size> inline int mask_to_int(__m256 ) { static_assert(Size == Size, "Size value not implemented"); return 0; }
template <size_t Size> inline int mask_to_int(__m256d) { static_assert(Size == Size, "Size value not implemented"); return 0; }
template <size_t Size> inline int mask_to_int(__m256i) { static_assert(Size == Size, "Size value not implemented"); return 0; }
#endif
#ifdef Vc_HAVE_AVX512F
template <size_t Size> inline uint mask_to_int(__mmask8 k) { return k; }
template <size_t Size> inline uint mask_to_int(__mmask16 k) { return k; }
template <size_t Size> inline uint mask_to_int(__mmask32 k) { return k; }
template <size_t Size> inline ullong mask_to_int(__mmask64 k) { return k; }
#endif
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(__m128 k)
{
    return _mm_movemask_ps(k);
}
#ifdef Vc_HAVE_SSE2
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<2>(__m128d k)
{
    return _mm_movemask_pd(k);
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<2>(__m128i k)
{
    return _mm_movemask_pd(_mm_castsi128_pd(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(__m128i k)
{
    return _mm_movemask_ps(_mm_castsi128_ps(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<8>(__m128i k)
{
    return _mm_movemask_epi8(_mm_packs_epi16(k, _mm_setzero_si128()));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<16>(__m128i k)
{
    return _mm_movemask_epi8(k);
}
#endif
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(__m256d k)
{
    return _mm256_movemask_pd(k);
}
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(__m256i k)
{
    return mask_to_int<4>(_mm256_castsi256_pd(k));
}
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<8>(__m256 k)
{
    return _mm256_movemask_ps(k);
}
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<8>(__m256i k)
{
    return mask_to_int<8>(_mm256_castsi256_ps(k));
}
#ifdef Vc_HAVE_AVX2
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<16>(__m256i k)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    return _mm256_movepi16_mask(k);
#else
    return _mm256_movemask_epi8(_mm256_packs_epi16(k, intrin_cast<__m256i>(hi128(k)))) &
           0xffff;
#endif
}
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<32>(__m256i k)
{
    return _mm256_movemask_epi8(k);
}
#endif
#endif
#ifdef Vc_HAVE_AVX512F
template <int = sizeof(long)> Vc_INTRINSIC auto cmpeq_long_mask(__m512i x, __m512i y);
template <> Vc_INTRINSIC auto cmpeq_long_mask<8>(__m512i x, __m512i y)
{
    return _mm512_cmpeq_epi64_mask(x, y);
}
template <> Vc_INTRINSIC auto cmpeq_long_mask<4>(__m512i x, __m512i y)
{
    return _mm512_cmpeq_epi32_mask(x, y);
}
template <int = sizeof(long)> Vc_INTRINSIC auto cmplt_long_mask(__m512i x, __m512i y);
template <> Vc_INTRINSIC auto cmplt_long_mask<8>(__m512i x, __m512i y)
{
    return _mm512_cmplt_epi64_mask(x, y);
}
template <> Vc_INTRINSIC auto cmplt_long_mask<4>(__m512i x, __m512i y)
{
    return _mm512_cmplt_epi32_mask(x, y);
}
template <int = sizeof(long)> Vc_INTRINSIC auto cmplt_ulong_mask(__m512i x, __m512i y);
template <> Vc_INTRINSIC auto cmplt_ulong_mask<8>(__m512i x, __m512i y)
{
    return _mm512_cmplt_epu64_mask(x, y);
}
template <> Vc_INTRINSIC auto cmplt_ulong_mask<4>(__m512i x, __m512i y)
{
    return _mm512_cmplt_epu32_mask(x, y);
}
template <int = sizeof(long)> Vc_INTRINSIC auto cmple_long_mask(__m512i x, __m512i y);
template <> Vc_INTRINSIC auto cmple_long_mask<8>(__m512i x, __m512i y)
{
    return _mm512_cmple_epi64_mask(x, y);
}
template <> Vc_INTRINSIC auto cmple_long_mask<4>(__m512i x, __m512i y)
{
    return _mm512_cmple_epi32_mask(x, y);
}
template <int = sizeof(long)> Vc_INTRINSIC auto cmple_ulong_mask(__m512i x, __m512i y);
template <> Vc_INTRINSIC auto cmple_ulong_mask<8>(__m512i x, __m512i y)
{
    return _mm512_cmple_epu64_mask(x, y);
}
template <> Vc_INTRINSIC auto cmple_ulong_mask<4>(__m512i x, __m512i y)
{
    return _mm512_cmple_epu32_mask(x, y);
}
#endif
#ifdef Vc_HAVE_SSE2
template <class T> Vc_INTRINSIC __m128i load2(const T *mem, when_aligned<2>)
{
    assertCorrectAlignment<unsigned short>(mem);
    static_assert(sizeof(T) == 1, "expected argument with sizeof == 1");
    return _mm_cvtsi32_si128(*reinterpret_cast<const unsigned short *>(mem));
}
template <class T> Vc_INTRINSIC __m128i load2(const T *mem, when_unaligned<2>)
{
    static_assert(sizeof(T) == 1, "expected argument with sizeof == 1");
    short tmp;
    std::memcpy(&tmp, mem, 2);
    return _mm_cvtsi32_si128(tmp);
}
#endif
template <class F> Vc_INTRINSIC __m128 load4(const float *mem, F)
{
    assertCorrectAlignment<float>(mem);
    return _mm_load_ss(mem);
}
#ifdef Vc_HAVE_SSE2
template <class F> Vc_INTRINSIC __m128i load4(const int *mem, F)
{
    assertCorrectAlignment<int>(mem);
    return _mm_cvtsi32_si128(mem[0]);
}
template <class F> Vc_INTRINSIC __m128i load4(const unsigned int *mem, F)
{
    assertCorrectAlignment<unsigned int>(mem);
    return _mm_cvtsi32_si128(mem[0]);
}
template <class T, class F> Vc_INTRINSIC __m128i load4(const T *mem, F)
{
    static_assert(sizeof(T) <= 2, "expected argument with sizeof <= 2");
    int tmp;
    std::memcpy(&tmp, mem, 4);
    return _mm_cvtsi32_si128(tmp);
}
#endif
template <class F> Vc_INTRINSIC __m128 load8(const float *mem, F)
{
    assertCorrectAlignment<float>(mem);
#ifdef Vc_HAVE_SSE2
    return _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double *>(mem)));
#else
    return _mm_loadl_pi(_mm_undefined_ps(), reinterpret_cast<const __m64 *>(mem));
#endif
}
#ifdef Vc_HAVE_SSE2
template <class F> Vc_INTRINSIC __m128d load8(const double *mem, F)
{
    assertCorrectAlignment<double>(mem);
    return _mm_load_sd(mem);
}
template <class T, class F> Vc_INTRINSIC __m128i load8(const T *mem, F)
{
    assertCorrectAlignment<T>(mem);
    static_assert(std::is_integral<T>::value, "load8<T> is only intended for integral T");
    return _mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem));
}
#endif
#ifdef Vc_HAVE_SSE
Vc_INTRINSIC __m128 load16(const float *mem, when_aligned<16>)
{
    assertCorrectAlignment<__m128>(mem);
    return _mm_load_ps(mem);
}
Vc_INTRINSIC __m128 load16(const float *mem, when_unaligned<16>)
{
    return _mm_loadu_ps(mem);
}
#endif
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d load16(const double *mem, when_aligned<16>)
{
    assertCorrectAlignment<__m128d>(mem);
    return _mm_load_pd(mem);
}
Vc_INTRINSIC __m128d load16(const double *mem, when_unaligned<16>)
{
    return _mm_loadu_pd(mem);
}
template <class T> Vc_INTRINSIC __m128i load16(const T *mem, when_aligned<16>)
{
    assertCorrectAlignment<__m128i>(mem);
    static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
    return _mm_load_si128(reinterpret_cast<const __m128i *>(mem));
}
template <class T> Vc_INTRINSIC __m128i load16(const T *mem, when_unaligned<16>)
{
    static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
    return _mm_loadu_si128(reinterpret_cast<const __m128i *>(mem));
}
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 load32(const float *mem, when_aligned<32>)
{
    assertCorrectAlignment<__m256>(mem);
    return _mm256_load_ps(mem);
}
Vc_INTRINSIC __m256 load32(const float *mem, when_unaligned<32>)
{
    return _mm256_loadu_ps(mem);
}
Vc_INTRINSIC __m256d load32(const double *mem, when_aligned<32>)
{
    assertCorrectAlignment<__m256d>(mem);
    return _mm256_load_pd(mem);
}
Vc_INTRINSIC __m256d load32(const double *mem, when_unaligned<32>)
{
    return _mm256_loadu_pd(mem);
}
template <class T> Vc_INTRINSIC __m256i load32(const T *mem, when_aligned<32>)
{
    assertCorrectAlignment<__m256i>(mem);
    static_assert(std::is_integral<T>::value, "load32<T> is only intended for integral T");
    return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
template <class T> Vc_INTRINSIC __m256i load32(const T *mem, when_unaligned<32>)
{
    static_assert(std::is_integral<T>::value, "load32<T> is only intended for integral T");
    return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(mem));
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 load64(const float *mem, when_aligned<64>)
{
    assertCorrectAlignment<__m512>(mem);
    return _mm512_load_ps(mem);
}
Vc_INTRINSIC __m512 load64(const float *mem, when_unaligned<64>)
{
    return _mm512_loadu_ps(mem);
}
Vc_INTRINSIC __m512d load64(const double *mem, when_aligned<64>)
{
    assertCorrectAlignment<__m512d>(mem);
    return _mm512_load_pd(mem);
}
Vc_INTRINSIC __m512d load64(const double *mem, when_unaligned<64>)
{
    return _mm512_loadu_pd(mem);
}
template <class T>
Vc_INTRINSIC __m512i load64(const T *mem, when_aligned<64>)
{
    assertCorrectAlignment<__m512i>(mem);
    static_assert(std::is_integral<T>::value, "load64<T> is only intended for integral T");
    return _mm512_load_si512(mem);
}
template <class T>
Vc_INTRINSIC __m512i load64(const T *mem, when_unaligned<64>)
{
    static_assert(std::is_integral<T>::value, "load64<T> is only intended for integral T");
    return _mm512_loadu_si512(mem);
}
#endif
#ifdef Vc_HAVE_SSE
Vc_INTRINSIC void store4(__m128 v, float *mem, when_aligned<alignof(float)>)
{
    assertCorrectAlignment<float>(mem);
    *mem = _mm_cvtss_f32(v);
}
Vc_INTRINSIC void store4(__m128 v, float *mem, when_unaligned<alignof(float)>)
{
    *mem = _mm_cvtss_f32(v);
}
Vc_INTRINSIC void store8(__m128 v, float *mem, when_aligned<alignof(__m64)>)
{
    assertCorrectAlignment<__m64>(mem);
    _mm_storel_pi(reinterpret_cast<__m64 *>(mem), v);
}
Vc_INTRINSIC void store8(__m128 v, float *mem, when_unaligned<alignof(__m64)>)
{
    _mm_storel_pi(reinterpret_cast<__m64 *>(mem), v);
}
Vc_INTRINSIC void store16(__m128 v, float *mem, when_aligned<16>)
{
    assertCorrectAlignment<__m128>(mem);
    _mm_store_ps(mem, v);
}
Vc_INTRINSIC void store16(__m128 v, float *mem, when_unaligned<16>)
{
    _mm_storeu_ps(mem, v);
}
#endif
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC void store8(__m128d v, double *mem, when_aligned<alignof(double)>)
{
    assertCorrectAlignment<double>(mem);
    *mem = _mm_cvtsd_f64(v);
}
Vc_INTRINSIC void store8(__m128d v, double *mem, when_unaligned<alignof(double)>)
{
    *mem = _mm_cvtsd_f64(v);
}
Vc_INTRINSIC void store16(__m128d v, double *mem, when_aligned<16>)
{
    assertCorrectAlignment<__m128d>(mem);
    _mm_store_pd(mem, v);
}
Vc_INTRINSIC void store16(__m128d v, double *mem, when_unaligned<16>)
{
    _mm_storeu_pd(mem, v);
}
template <class T> Vc_INTRINSIC void store2(__m128i v, T *mem, when_aligned<alignof(ushort)>)
{
    assertCorrectAlignment<ushort>(mem);
    static_assert(std::is_integral<T>::value && sizeof(T) <= 2,
                  "store4<T> is only intended for integral T with sizeof(T) <= 2");
    *reinterpret_cast<may_alias<ushort> *>(mem) = uint(_mm_cvtsi128_si32(v));
}
template <class T> Vc_INTRINSIC void store2(__m128i v, T *mem, when_unaligned<alignof(ushort)>)
{
    static_assert(std::is_integral<T>::value && sizeof(T) <= 2,
                  "store4<T> is only intended for integral T with sizeof(T) <= 2");
    const uint tmp(_mm_cvtsi128_si32(v));
    std::memcpy(mem, &tmp, 2);
}
template <class T> Vc_INTRINSIC void store4(__m128i v, T *mem, when_aligned<alignof(int)>)
{
    assertCorrectAlignment<int>(mem);
    static_assert(std::is_integral<T>::value && sizeof(T) <= 4,
                  "store4<T> is only intended for integral T with sizeof(T) <= 4");
    *reinterpret_cast<may_alias<int> *>(mem) = _mm_cvtsi128_si32(v);
}
template <class T> Vc_INTRINSIC void store4(__m128i v, T *mem, when_unaligned<alignof(int)>)
{
    static_assert(std::is_integral<T>::value && sizeof(T) <= 4,
                  "store4<T> is only intended for integral T with sizeof(T) <= 4");
    const int tmp = _mm_cvtsi128_si32(v);
    std::memcpy(mem, &tmp, 4);
}
template <class T> Vc_INTRINSIC void store8(__m128i v, T *mem, when_aligned<8>)
{
    assertCorrectAlignment<__m64>(mem);
    static_assert(std::is_integral<T>::value, "store8<T> is only intended for integral T");
    _mm_storel_epi64(reinterpret_cast<__m128i *>(mem), v);
}
template <class T> Vc_INTRINSIC void store8(__m128i v, T *mem, when_unaligned<8>)
{
    static_assert(std::is_integral<T>::value, "store8<T> is only intended for integral T");
    _mm_storel_epi64(reinterpret_cast<__m128i *>(mem), v);
}
template <class T> Vc_INTRINSIC void store16(__m128i v, T *mem, when_aligned<16>)
{
    assertCorrectAlignment<__m128i>(mem);
    static_assert(std::is_integral<T>::value, "store16<T> is only intended for integral T");
    _mm_store_si128(reinterpret_cast<__m128i *>(mem), v);
}
template <class T> Vc_INTRINSIC void store16(__m128i v, T *mem, when_unaligned<16>)
{
    static_assert(std::is_integral<T>::value, "store16<T> is only intended for integral T");
    _mm_storeu_si128(reinterpret_cast<__m128i *>(mem), v);
}
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC void store32(__m256 v, float *mem, when_aligned<32>)
{
    assertCorrectAlignment<__m256>(mem);
    _mm256_store_ps(mem, v);
}
Vc_INTRINSIC void store32(__m256 v, float *mem, when_unaligned<32>)
{
    _mm256_storeu_ps(mem, v);
}
Vc_INTRINSIC void store32(__m256d v, double *mem, when_aligned<32>)
{
    assertCorrectAlignment<__m256d>(mem);
    _mm256_store_pd(mem, v);
}
Vc_INTRINSIC void store32(__m256d v, double *mem, when_unaligned<32>)
{
    _mm256_storeu_pd(mem, v);
}
template <class T> Vc_INTRINSIC void store32(__m256i v, T *mem, when_aligned<32>)
{
    assertCorrectAlignment<__m256i>(mem);
    static_assert(std::is_integral<T>::value, "store32<T> is only intended for integral T");
    _mm256_store_si256(reinterpret_cast<__m256i *>(mem), v);
}
template <class T> Vc_INTRINSIC void store32(__m256i v, T *mem, when_unaligned<32>)
{
    static_assert(std::is_integral<T>::value, "store32<T> is only intended for integral T");
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(mem), v);
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC void store64(__m512 v, float *mem, when_aligned<64>)
{
    assertCorrectAlignment<__m512>(mem);
    _mm512_store_ps(mem, v);
}
Vc_INTRINSIC void store64(__m512 v, float *mem, when_unaligned<64>)
{
    _mm512_storeu_ps(mem, v);
}
Vc_INTRINSIC void store64(__m512d v, double *mem, when_aligned<64>)
{
    assertCorrectAlignment<__m512d>(mem);
    _mm512_store_pd(mem, v);
}
Vc_INTRINSIC void store64(__m512d v, double *mem, when_unaligned<64>)
{
    _mm512_storeu_pd(mem, v);
}
template <class T>
Vc_INTRINSIC void store64(__m512i v, T *mem, when_aligned<64>)
{
    assertCorrectAlignment<__m512i>(mem);
    static_assert(std::is_integral<T>::value, "store64<T> is only intended for integral T");
    _mm512_store_si512(mem, v);
}
template <class T>
Vc_INTRINSIC void store64(__m512i v, T *mem, when_unaligned<64>)
{
    static_assert(std::is_integral<T>::value, "store64<T> is only intended for integral T");
    _mm512_storeu_si512(mem, v);
}
#endif
#ifdef Vc_HAVE_AVX512F
template <class T, class F, size_t N>
Vc_INTRINSIC void store_n_bytes(size_constant<N>, __m512i v, T *mem, F)
{
    std::memcpy(mem, &v, N);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<4>, __m512i v, T *mem, F f)
{
    store4(lo128(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<8>, __m512i v, T *mem, F f)
{
    store8(lo128(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<16>, __m512i v, T *mem, F f)
{
    store16(lo128(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<32>, __m512i v, T *mem, F f)
{
    store32(lo256(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<64>, __m512i v, T *mem, F f)
{
    store64(v, mem, f);
}
#endif
#ifdef Vc_HAVE_AVX
template <class T, class F, size_t N>
Vc_INTRINSIC void store_n_bytes(size_constant<N>, __m256i v, T *mem, F)
{
    std::memcpy(mem, &v, N);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<4>, __m256i v, T *mem, F f)
{
    store4(lo128(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<8>, __m256i v, T *mem, F f)
{
    store8(lo128(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<16>, __m256i v, T *mem, F f)
{
    store16(lo128(v), mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<32>, __m256i v, T *mem, F f)
{
    store32(v, mem, f);
}
#endif
#ifdef Vc_HAVE_SSE2
template <class T, class F, size_t N>
Vc_INTRINSIC void store_n_bytes(size_constant<N>, __m128i v, T *mem, F)
{
    std::memcpy(mem, &v, N);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<4>, __m128i v, T *mem, F f)
{
    store4(v, mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<8>, __m128i v, T *mem, F f)
{
    store8(v, mem, f);
}
template <class T, class F>
Vc_INTRINSIC void store_n_bytes(size_constant<16>, __m128i v, T *mem, F f)
{
    store16(v, mem, f);
}
#endif
}
using namespace x86;
}
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace AliasStrategy
{
struct MayAlias {};
struct VectorBuiltin {};
struct UnionMembers {};
using Default =
#if defined Vc_USE_ALIASSTRATEGY_VECTORBUILTIN
#ifndef Vc_USE_BUILTIN_VECTOR_TYPES
#define Vc_USE_BUILTIN_VECTOR_TYPES 1
#endif
    VectorBuiltin;
#elif defined Vc_USE_ALIASSTRATEGY_UNIONMEMBERS
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
#undef Vc_USE_BUILTIN_VECTOR_TYPES
#endif
    UnionMembers;
#elif defined Vc_USE_ALIASSTRATEGY_MAYALIAS
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
#undef Vc_USE_BUILTIN_VECTOR_TYPES
#endif
    MayAlias;
#elif defined Vc_USE_BUILTIN_VECTOR_TYPES
    VectorBuiltin;
#elif defined Vc_MSVC
    UnionMembers;
#elif defined __GNUC__
    MayAlias;
#else
    MayAlias;
#endif
}
template <typename ValueType, size_t Size, typename Strategy = AliasStrategy::Default>
class Storage;
template <size_t Size> class Storage<bool, Size, AliasStrategy::Default>
{
public:
    using VectorType = typename bool_storage_member_type<Size>::type;
    using value_type = bool;
    using EntryType = value_type;
    static constexpr size_t size() { return Size; }
    Vc_INTRINSIC Storage() = default;
    template <class... Args, class = enable_if_t<sizeof...(Args) == Size>>
    Vc_INTRINSIC Storage(Args &&... init)
        : data{static_cast<EntryType>(std::forward<Args>(init))...}
    {
    }
    Vc_INTRINSIC Storage(const VectorType &x) : data(x) {}
    Vc_INTRINSIC Storage(const Storage &) = default;
    Vc_INTRINSIC Storage &operator=(const Storage &) = default;
    Vc_INTRINSIC Vc_PURE operator const VectorType &() const { return v(); }
    Vc_INTRINSIC Vc_PURE VectorType &v() { return data; }
    Vc_INTRINSIC Vc_PURE const VectorType &v() const { return data; }
    Vc_INTRINSIC Vc_PURE EntryType operator[](size_t i) const { return m(i); }
    Vc_INTRINSIC Vc_PURE EntryType m(size_t i) const { return data & (VectorType(1) << i); }
    Vc_INTRINSIC void set(size_t i, EntryType x)
    {
        if (x) {
            data |= (VectorType(1) << i);
        } else {
            data &= ~(VectorType(1) << i);
        }
    }
private:
    VectorType data;
};
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::MayAlias>
{
    static_assert(std::is_fundamental<ValueType>::value &&
                      std::is_arithmetic<ValueType>::value,
                  "Only works for fundamental arithmetic types.");
    struct
#ifndef Vc_MSVC
        [[gnu::may_alias]]
#endif
        aliased_construction
    {
        may_alias<ValueType> d[Size];
    };
public:
    using VectorType = intrinsic_type_t<ValueType, Size>;
    using value_type = ValueType;
    using EntryType = value_type;
    static constexpr size_t size() { return Size; }
    Vc_INTRINSIC Storage() = default;
    template <class... Args, class = enable_if_t<sizeof...(Args) == Size>>
    Vc_INTRINSIC Storage(Args &&... init)
        : data(x86::set(static_cast<EntryType>(std::forward<Args>(init))...))
    {
        assertCorrectAlignment(&data);
    }
#ifdef Vc_HAVE_AVX512_ABI
#ifdef Vc_HAVE_AVX512BW
    inline Storage(__mmask64 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
    inline Storage(__mmask32 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
#endif
#if defined Vc_HAVE_AVX512DQ || (defined Vc_HAVE_AVX512BW && defined Vc_HAVE_AVX512VL)
    inline Storage(__mmask16 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
    inline Storage(__mmask8 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
#endif
#endif
    Vc_INTRINSIC Storage(const VectorType &x) : data(x)
    {
        assertCorrectAlignment(&data);
    }
    template <typename U>
    Vc_INTRINSIC explicit Storage(const U &x,
                                  enable_if<sizeof(U) == sizeof(VectorType)> = nullarg)
        : data(reinterpret_cast<const VectorType &>(x))
    {
        assertCorrectAlignment(&data);
    }
    template <typename U>
    Vc_INTRINSIC explicit Storage(Storage<U, Size, AliasStrategy::MayAlias> x)
        : data(reinterpret_cast<VectorType>(x.v()))
    {
        assertCorrectAlignment(&data);
    }
    Vc_INTRINSIC Storage(const Storage &) = default;
    Vc_INTRINSIC Storage &operator=(const Storage &) = default;
    Vc_INTRINSIC operator const VectorType &() const { return v(); }
    Vc_INTRINSIC Vc_PURE VectorType &v() { return data; }
    Vc_INTRINSIC Vc_PURE const VectorType &v() const { return data; }
    Vc_INTRINSIC Vc_PURE EntryType operator[](size_t i) const { return m(i); }
    Vc_INTRINSIC Vc_PURE EntryType m(size_t i) const
    {
        return reinterpret_cast<const may_alias<EntryType> *>(&data)[i];
    }
    Vc_INTRINSIC void set(size_t i, EntryType x)
    {
        reinterpret_cast<may_alias<EntryType> *>(&data)[i] = x;
    }
private:
    VectorType data;
};
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::VectorBuiltin>
{
    static_assert(std::is_fundamental<ValueType>::value &&
                      std::is_arithmetic<ValueType>::value,
                  "Only works for fundamental arithmetic types.");
public:
    using Builtin = builtin_type_t<ValueType, Size>;
    using VectorType =
#ifdef Vc_TEMPLATES_DROP_ATTRIBUTES
        may_alias<intrinsic_type_t<ValueType, Size>>;
#else
        intrinsic_type_t<ValueType, Size>;
#endif
    using value_type = ValueType;
    using EntryType = value_type;
    static constexpr size_t size() { return Size; }
    Vc_INTRINSIC Storage() = default;
    template <class... Args, class = enable_if_t<sizeof...(Args) == Size>>
    Vc_INTRINSIC Storage(Args &&... init)
        : data{static_cast<EntryType>(std::forward<Args>(init))...}
    {
    }
#ifdef Vc_HAVE_AVX512_ABI
#ifdef Vc_HAVE_AVX512BW
    inline Storage(__mmask64 k)
        : data(reinterpret_cast<Builtin>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
    inline Storage(__mmask32 k)
        : data(reinterpret_cast<Builtin>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
#endif
#if defined Vc_HAVE_AVX512DQ || (defined Vc_HAVE_AVX512BW && defined Vc_HAVE_AVX512VL)
    inline Storage(__mmask16 k)
        : data(reinterpret_cast<Builtin>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
    inline Storage(__mmask8 k)
        : data(reinterpret_cast<Builtin>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
    }
#endif
#endif
    Vc_INTRINSIC Storage(Builtin x) : data(x) { assertCorrectAlignment(&data); }
    template <typename U>
    Vc_INTRINSIC Storage(const U &x,
                         enable_if<(is_builtin_vector_v<U> || is_intrinsic_v<U>)&&sizeof(
                                       U) == sizeof(VectorType)> = nullarg)
        : data(reinterpret_cast<Builtin>(x))
    {
        assertCorrectAlignment(&data);
    }
    template <typename U>
    Vc_INTRINSIC explicit Storage(Storage<U, Size, AliasStrategy::VectorBuiltin> x)
        : data(reinterpret_cast<Builtin>(x.v()))
    {
        assertCorrectAlignment(&data);
    }
    Vc_INTRINSIC Storage(const Storage &) = default;
    Vc_INTRINSIC Storage &operator=(const Storage &) = default;
    Vc_INTRINSIC operator const VectorType &() const { return v(); }
    Vc_INTRINSIC Vc_PURE VectorType &v() { return reinterpret_cast<VectorType &>(data); }
    Vc_INTRINSIC Vc_PURE const VectorType &v() const { return reinterpret_cast<const VectorType &>(data); }
    Vc_INTRINSIC Vc_PURE EntryType operator[](size_t i) const { return m(i); }
    Vc_INTRINSIC Vc_PURE EntryType m(size_t i) const { return data[i]; }
    Vc_INTRINSIC void set(size_t i, EntryType x) { data[i] = x; }
    Vc_INTRINSIC Builtin &builtin() { return data; }
    Vc_INTRINSIC const Builtin &builtin() const { return data; }
private:
    Builtin data;
};
#if defined Vc_CLANG && !defined Vc_HAVE_SSE4_1
#if Vc_CLANG <= 0x60000
template <> void Storage<double, 2, AliasStrategy::VectorBuiltin>::set(size_t i, double x)
{
    if (x == 0. && i == 1)
        asm("" : "+g"(x));
    data[i] = x;
}
#else
#warning "clang 5 failed operators_sse2_vectorbuiltin_ldouble_float_double_schar_uchar in operator<simd<double, Sse>> and required a workaround. Is this still the case for newer clang versions?"
#endif
#endif
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::UnionMembers>
{
    static_assert(std::is_fundamental<ValueType>::value &&
                      std::is_arithmetic<ValueType>::value,
                  "Only works for fundamental arithmetic types.");
public:
    using VectorType = intrinsic_type_t<ValueType, Size>;
    using value_type = ValueType;
    using EntryType = value_type;
    static constexpr size_t size() { return Size; }
    Vc_INTRINSIC Storage() = default;
    template <class... Args, class = enable_if_t<sizeof...(Args) == Size>>
    Vc_INTRINSIC Storage(Args &&... init)
        : data(x86::set(static_cast<EntryType>(std::forward<Args>(init))...))
    {
        assertCorrectAlignment(&data);
    }
#ifdef Vc_HAVE_AVX512_ABI
#ifdef Vc_HAVE_AVX512BW
    inline Storage(__mmask64 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
        assertCorrectAlignment(&data);
    }
    inline Storage(__mmask32 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
        assertCorrectAlignment(&data);
    }
#endif
#if defined Vc_HAVE_AVX512DQ || (defined Vc_HAVE_AVX512BW && defined Vc_HAVE_AVX512VL)
    inline Storage(__mmask16 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
        assertCorrectAlignment(&data);
    }
    inline Storage(__mmask8 k)
        : data(intrin_cast<VectorType>(
              convert_mask<sizeof(EntryType), sizeof(VectorType)>(k)))
    {
        assertCorrectAlignment(&data);
    }
#endif
#endif
    Vc_INTRINSIC Storage(const VectorType &x) : data(x)
    {
        assertCorrectAlignment(&data);
    }
    template <typename U>
    Vc_INTRINSIC explicit Storage(const U &x
#ifndef Vc_MSVC
                                  ,
                                  enable_if<sizeof(U) == sizeof(VectorType)> = nullarg
#endif
                                  )
        : data(reinterpret_cast<const VectorType &>(x))
    {
        static_assert(sizeof(U) == sizeof(VectorType),
                      "invalid call to converting Storage constructor");
        assertCorrectAlignment(&data);
    }
    static const VectorType &adjustVectorType(const VectorType &x) { return x; }
    template <typename T> static VectorType adjustVectorType(const T &x)
    {
        return reinterpret_cast<VectorType>(x);
    }
    template <typename U>
    Vc_INTRINSIC explicit Storage(const Storage<U, Size, AliasStrategy::UnionMembers> &x)
        : data(adjustVectorType(x.v()))
    {
        assertCorrectAlignment(&data);
    }
    Vc_INTRINSIC Storage(const Storage &) = default;
    Vc_INTRINSIC Storage &operator=(const Storage &) = default;
    Vc_INTRINSIC operator const VectorType &() const { return v(); }
    Vc_INTRINSIC Vc_PURE VectorType &v() { return data; }
    Vc_INTRINSIC Vc_PURE const VectorType &v() const { return data; }
    Vc_INTRINSIC Vc_PURE EntryType operator[](size_t i) const { return m(i); }
    Vc_INTRINSIC_L Vc_PURE_L EntryType m(size_t i) const Vc_INTRINSIC_R Vc_PURE_R;
    Vc_INTRINSIC void set(size_t i, EntryType x) { ref(i) = x; }
private:
    Vc_INTRINSIC_L Vc_PURE_L typename std::conditional<
        std::is_same<EntryType, signed char>::value, char,
        typename std::conditional<
            std::is_same<EntryType, long>::value, int,
            typename std::conditional<std::is_same<EntryType, ulong>::value, uint,
                                      EntryType>::type>::type>::type &
    ref(size_t i) Vc_INTRINSIC_R Vc_PURE_R;
    VectorType data;
};
#ifdef Vc_MSVC
template <> Vc_INTRINSIC Vc_PURE double Storage<double, 2, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float Storage< float, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE llong Storage< llong, 2, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i64[i]; }
template <> Vc_INTRINSIC Vc_PURE long Storage< long, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE int Storage< int, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE short Storage< short, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE schar Storage< schar,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i8[i]; }
template <> Vc_INTRINSIC Vc_PURE ullong Storage<ullong, 2, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u64[i]; }
template <> Vc_INTRINSIC Vc_PURE ulong Storage< ulong, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE uint Storage< uint, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE ushort Storage<ushort, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE uchar Storage< uchar,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u8[i]; }
template <> Vc_INTRINSIC Vc_PURE double &Storage<double, 2, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float &Storage< float, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE llong &Storage< llong, 2, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i64[i]; }
template <> Vc_INTRINSIC Vc_PURE int &Storage< long, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE int &Storage< int, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE short &Storage< short, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE char &Storage< schar,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i8[i]; }
template <> Vc_INTRINSIC Vc_PURE ullong &Storage<ullong, 2, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u64[i]; }
template <> Vc_INTRINSIC Vc_PURE uint &Storage< ulong, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE uint &Storage< uint, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE ushort &Storage<ushort, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE uchar &Storage< uchar,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u8[i]; }
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC Vc_PURE double Storage<double, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float Storage< float, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE llong Storage< llong, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i64[i]; }
template <> Vc_INTRINSIC Vc_PURE long Storage< long, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE int Storage< int, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE short Storage< short,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE schar Storage< schar,32, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i8[i]; }
template <> Vc_INTRINSIC Vc_PURE ullong Storage<ullong, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u64[i]; }
template <> Vc_INTRINSIC Vc_PURE ulong Storage< ulong, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE uint Storage< uint, 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE ushort Storage<ushort,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE uchar Storage< uchar,32, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u8[i]; }
template <> Vc_INTRINSIC Vc_PURE double &Storage<double, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float &Storage< float, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE llong &Storage< llong, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i64[i]; }
template <> Vc_INTRINSIC Vc_PURE int &Storage< long, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE int &Storage< int, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE short &Storage< short,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE char &Storage< schar,32, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i8[i]; }
template <> Vc_INTRINSIC Vc_PURE ullong &Storage<ullong, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u64[i]; }
template <> Vc_INTRINSIC Vc_PURE uint &Storage< ulong, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE uint &Storage< uint, 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE ushort &Storage<ushort,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE uchar &Storage< uchar,32, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u8[i]; }
#endif
#endif
template <class CharT, class T, size_t N>
inline std::basic_ostream<CharT> &operator<<(std::basic_ostream<CharT> & s,
                                             const Storage<T, N> &v)
{
    s << '[' << v[0];
    for (size_t i = 1; i < N; ++i) {
        s << ((i % 4) ? " " : " | ") << v[i];
    }
    return s << ']';
}
}
Vc_VERSIONED_NAMESPACE_END
#ifdef Vc_HAVE_NEON_ABI
#ifndef VC_SIMD_AARCH_STORAGE_H_
#define VC_SIMD_AARCH_STORAGE_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace aarch
{
using x_f64 = Storage<double, 2>;
using x_f32 = Storage< float, 4>;
using x_s08 = Storage< schar, 16>;
using x_u08 = Storage< uchar, 16>;
using x_s16 = Storage< short, 8>;
using x_u16 = Storage<ushort, 8>;
using x_s32 = Storage< int, 4>;
using x_u32 = Storage< uint, 4>;
}}
Vc_VERSIONED_NAMESPACE_END
#endif
#elif defined Vc_HAVE_SSE_ABI
#ifndef VC_SIMD_X86_STORAGE_H_
#define VC_SIMD_X86_STORAGE_H_ 
#ifndef VC_SIMD_STORAGE_H_
#error "Do not include detail/x86/storage.h directly. Include detail/storage.h instead."
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T> using sse_simd_member_type = Storage<T, 16 / sizeof(T)>;
template <class T> using sse_mask_member_type = Storage<T, 16 / sizeof(T)>;
template <class T> using avx_simd_member_type = Storage<T, 32 / sizeof(T)>;
template <class T> using avx_mask_member_type = Storage<T, 32 / sizeof(T)>;
template <class T> using avx512_simd_member_type = Storage<T, 64 / sizeof(T)>;
template <class T> using avx512_mask_member_type = Storage<bool, 64 / sizeof(T)>;
template <size_t N> using avx512_mask_member_type_n = Storage<bool, N>;
namespace x86
{
#ifdef Vc_HAVE_SSE
using x_f32 = Storage< float, 4>;
#ifdef Vc_HAVE_SSE2
using x_f64 = Storage<double, 2>;
using x_i08 = Storage< schar, 16>;
using x_u08 = Storage< uchar, 16>;
using x_i16 = Storage< short, 8>;
using x_u16 = Storage<ushort, 8>;
using x_i32 = Storage< int, 4>;
using x_u32 = Storage< uint, 4>;
using x_i64 = Storage< llong, 2>;
using x_u64 = Storage<ullong, 2>;
using x_long = Storage<long, 16 / sizeof(long)>;
using x_ulong = Storage<ulong, 16 / sizeof(ulong)>;
using x_long_equiv = Storage<equal_int_type_t<long>, x_long::size()>;
using x_ulong_equiv = Storage<equal_int_type_t<ulong>, x_ulong::size()>;
#endif
#endif
#ifdef Vc_HAVE_AVX
using y_f32 = Storage< float, 8>;
using y_f64 = Storage<double, 4>;
using y_i08 = Storage< schar, 32>;
using y_u08 = Storage< uchar, 32>;
using y_i16 = Storage< short, 16>;
using y_u16 = Storage<ushort, 16>;
using y_i32 = Storage< int, 8>;
using y_u32 = Storage< uint, 8>;
using y_i64 = Storage< llong, 4>;
using y_u64 = Storage<ullong, 4>;
using y_long = Storage<long, 32 / sizeof(long)>;
using y_ulong = Storage<ulong, 32 / sizeof(ulong)>;
using y_long_equiv = Storage<equal_int_type_t<long>, y_long::size()>;
using y_ulong_equiv = Storage<equal_int_type_t<ulong>, y_ulong::size()>;
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL lo128(Storage<T, N> x)
{
    return lo128(x.v());
}
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL hi128(Storage<T, N> x)
{
    return hi128(x.v());
}
template <int offset, typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 16 / sizeof(T)> Vc_VDECL extract128(Storage<T, N> x)
{
    return extract128<offset>(x.v());
}
#endif
#ifdef Vc_HAVE_AVX512F
using z_f32 = Storage< float, 16>;
using z_f64 = Storage<double, 8>;
using z_i32 = Storage< int, 16>;
using z_u32 = Storage< uint, 16>;
using z_i64 = Storage< llong, 8>;
using z_u64 = Storage<ullong, 8>;
using z_long = Storage<long, 64 / sizeof(long)>;
using z_ulong = Storage<ulong, 64 / sizeof(ulong)>;
using z_i08 = Storage< schar, 64>;
using z_u08 = Storage< uchar, 64>;
using z_i16 = Storage< short, 32>;
using z_u16 = Storage<ushort, 32>;
using z_long_equiv = Storage<equal_int_type_t<long>, z_long::size()>;
using z_ulong_equiv = Storage<equal_int_type_t<ulong>, z_ulong::size()>;
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 32 / sizeof(T)> Vc_VDECL lo256(Storage<T, N> x)
{
    return lo256(x.v());
}
template <typename T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, 32 / sizeof(T)> Vc_VDECL hi256(Storage<T, N> x)
{
    return hi256(x.v());
}
#endif
template <class T>
Vc_INTRINSIC const Storage<T, 16 / sizeof(T)>& Vc_VDECL
    extract_part_impl(std::true_type, size_constant<0>, size_constant<1>,
                      const Storage<T, 16 / sizeof(T)>& x)
{
    return x;
}
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
#endif
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
#endif
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
template <class T> constexpr T constexpr_max(T a, T b) { return a > b ? a : b; }
template <size_t Index, size_t Total, class T, size_t N>
Vc_INTRINSIC Vc_CONST Storage<T, constexpr_max(16 / sizeof(T), N / Total)> Vc_VDECL
extract_part(Storage<T, N> x)
{
    constexpr size_t NewN = N / Total;
    static_assert(Total > 1, "Total must be greater than 1");
    static_assert(NewN * Total == N, "N must be divisible by Total");
    return extract_part_impl<T>(
        std::integral_constant<bool, (sizeof(T) * NewN >= 16)>(),
        std::integral_constant<size_t, Index>(), std::integral_constant<size_t, Total>(),
        x);
}
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
#else
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi8_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi8_mask(zeroExtend64(x)); }
#endif
#else
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movemask_epi8(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movemask_epi8(x); }
#endif
};
template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 2, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi16_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi16_mask(x); }
#else
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi16_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi16_mask(zeroExtend64(x)); }
#endif
#else
    Vc_INTRINSIC To operator()(__m128i x) { return x86::movemask_epi16(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return x86::movemask_epi16(x); }
#endif
};
template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 4, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi32_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi32_mask(x); }
#else
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi32_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi32_mask(zeroExtend64(x)); }
#endif
    Vc_INTRINSIC To operator()(__m128 x) { return operator()(_mm_castps_si128(x)); }
    Vc_INTRINSIC To operator()(__m256 x) { return operator()(_mm256_castps_si256(x)); }
#else
    Vc_INTRINSIC To operator()(__m128 x) { return _mm_movemask_ps(x); }
    Vc_INTRINSIC To operator()(__m256 x) { return _mm256_movemask_ps(x); }
    Vc_INTRINSIC To operator()(__m128i x) { return operator()(_mm_castsi128_ps(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return operator()(_mm256_castsi256_ps(x)); }
#endif
};
template <size_t NTo, size_t NFrom, class To>
struct convert_mask_impl<1, NTo, 8, NFrom, To, true> {
#ifdef Vc_HAVE_AVX512BW
#ifdef Vc_HAVE_AVX512VL
    Vc_INTRINSIC To operator()(__m128i x) { return _mm_movepi64_mask(x); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm256_movepi64_mask(x); }
#else
    Vc_INTRINSIC To operator()(__m128i x) { return _mm512_movepi64_mask(zeroExtend64(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return _mm512_movepi64_mask(zeroExtend64(x)); }
#endif
    Vc_INTRINSIC To operator()(__m128d x) { return operator()(_mm_castpd_si128(x)); }
    Vc_INTRINSIC To operator()(__m256d x) { return operator()(_mm256_castpd_si256(x)); }
#else
    Vc_INTRINSIC To operator()(__m128d x) { return _mm_movemask_pd(x); }
    Vc_INTRINSIC To operator()(__m256d x) { return _mm256_movemask_pd(x); }
    Vc_INTRINSIC To operator()(__m128i x) { return operator()(_mm_castsi128_pd(x)); }
    Vc_INTRINSIC To operator()(__m256i x) { return operator()(_mm256_castsi256_pd(x)); }
#endif
};
#endif
#define Vc_CONVERT_MASK_IMPL_BEGIN(SizeofTo_,NTo_,SizeofFrom_,NFrom_) \
    template <class To> \
    struct convert_mask_impl<SizeofTo_, NTo_, SizeofFrom_, NFrom_, To, false> { \
        template <class T> Vc_INTRINSIC To operator()(T x) \
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
#endif
#endif
#endif
}
#ifdef Vc_HAVE_AVX
template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 32 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 16 / sizeof(T)> a, Storage<T, 16 / sizeof(T)> b)
{
    return x86::concat(a.v(), b.v());
}
#endif
#ifdef Vc_HAVE_AVX512F
template <class T>
Vc_INTRINSIC Vc_CONST Storage<T, 64 / sizeof(T)> Vc_VDECL
    concat(Storage<T, 32 / sizeof(T)> a, Storage<T, 32 / sizeof(T)> b)
{
    return x86::concat(a.v(), b.v());
}
#endif
template <class To, class T, size_t Size> To convert_mask(Storage<T, Size> x)
{
    return convert_mask_impl<sizeof(typename To::value_type), To::size(), sizeof(T), Size,
                             typename To::VectorType>()(x);
}
}
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#endif
#ifndef VC_FWDDECL_H_
#error
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T, class A0, class A1> struct fallback_abi_for_long_double {
    using type = A0;
};
template <class A0, class A1> struct fallback_abi_for_long_double<long double, A0, A1> {
    using type = A1;
};
template <class T, class A0, class A1>
using fallback_abi_for_long_double_t =
    typename fallback_abi_for_long_double<T, A0, A1>::type;
}
namespace simd_abi
{
template <class T> inline constexpr int max_fixed_size = 32;
#if defined Vc_IS_AMD64
#if !defined Vc_HAVE_SSE2
#error "Use of SSE2 is required on AMD64"
#endif
template <typename T>
using compatible = detail::fallback_abi_for_long_double_t<T, Sse, scalar>;
#elif defined Vc_IS_AARCH64
template <typename T>
using compatible = detail::fallback_abi_for_long_double_t<T, Neon, scalar>;
#else
template <typename> using compatible = scalar;
#endif
#if defined Vc_HAVE_FULL_AVX512_ABI
template <typename T>
using native = detail::fallback_abi_for_long_double_t<T, Avx512, scalar>;
#elif defined Vc_HAVE_AVX512_ABI
template <typename T>
using native =
    std::conditional_t<(sizeof(T) >= 4),
                       detail::fallback_abi_for_long_double_t<T, Avx512, scalar>, Avx>;
#elif defined Vc_HAVE_FULL_AVX_ABI
template <typename T> using native = detail::fallback_abi_for_long_double_t<T, Avx, scalar>;
#elif defined Vc_HAVE_AVX_ABI
template <typename T>
using native =
    std::conditional_t<std::is_floating_point<T>::value,
                       detail::fallback_abi_for_long_double_t<T, Avx, scalar>, Sse>;
#elif defined Vc_HAVE_FULL_SSE_ABI
template <typename T>
using native = detail::fallback_abi_for_long_double_t<T, Sse, scalar>;
#elif defined Vc_HAVE_SSE_ABI
template <typename T>
using native = std::conditional_t<std::is_same<float, T>::value, Sse, scalar>;
#elif defined Vc_HAVE_FULL_NEON_ABI
template <typename T>
using native = detail::fallback_abi_for_long_double_t<T, Neon, scalar>;
#else
template <typename> using native = scalar;
#endif
namespace detail
{
#if defined Vc_DEFAULT_ABI
template <typename T> using default_abi = Vc_DEFAULT_ABI<T>;
#else
template <typename T> using default_abi = compatible<T>;
#endif
}
}
template <class T, class = detail::void_t<>> struct is_abi_tag : std::false_type {
};
template <class T>
struct is_abi_tag<T, detail::void_t<typename T::is_valid_abi_tag>>
    : public T::is_valid_abi_tag {
};
template <class T> inline constexpr bool is_abi_tag_v = is_abi_tag<T>::value;
template <class T> struct is_simd : public std::false_type {};
template <class T> inline constexpr bool is_simd_v = is_simd<T>::value;
template <class T> struct is_simd_mask : public std::false_type {};
template <class T> inline constexpr bool is_simd_mask_v = is_simd_mask<T>::value;
namespace detail
{
template <class T, class Abi, class = detail::void_t<>> struct simd_size_impl {
};
template <class T, class Abi>
struct simd_size_impl<T, Abi, detail::void_t<std::enable_if_t<detail::conjunction_v<
                                  detail::is_vectorizable<T>, Vc::is_abi_tag<Abi>>>>>
    : Abi::template size_tag<T> {
};
}
template <class T, class Abi = simd_abi::detail::default_abi<T>>
struct simd_size : detail::simd_size_impl<T, Abi> {
};
template <class T, class Abi = simd_abi::detail::default_abi<T>>
inline constexpr size_t simd_size_v = simd_size<T, Abi>::value;
namespace detail
{
template <class T, size_t N, bool, bool> struct abi_for_size_impl;
template <class T, size_t N> struct abi_for_size_impl<T, N, true, true> {
    using type = simd_abi::fixed_size<N>;
};
template <class T> struct abi_for_size_impl<T, 1, true, true> {
    using type = simd_abi::scalar;
};
#ifdef Vc_HAVE_SSE_ABI
template <> struct abi_for_size_impl<float, 4, true, true> { using type = simd_abi::Sse; };
#endif
#ifdef Vc_HAVE_FULL_SSE_ABI
template <> struct abi_for_size_impl<double, 2, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< llong, 2, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl<ullong, 2, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< long, 16 / sizeof(long), true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< ulong, 16 / sizeof(long), true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< int, 4, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< uint, 4, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< short, 8, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl<ushort, 8, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< schar, 16, true, true> { using type = simd_abi::Sse; };
template <> struct abi_for_size_impl< uchar, 16, true, true> { using type = simd_abi::Sse; };
#endif
#ifdef Vc_HAVE_AVX_ABI
template <> struct abi_for_size_impl<double, 4, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl<float, 8, true, true> { using type = simd_abi::Avx; };
#endif
#ifdef Vc_HAVE_FULL_AVX_ABI
template <> struct abi_for_size_impl< llong, 4, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl<ullong, 4, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< long, 32 / sizeof(long), true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< ulong, 32 / sizeof(long), true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< int, 8, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< uint, 8, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< short, 16, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl<ushort, 16, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< schar, 32, true, true> { using type = simd_abi::Avx; };
template <> struct abi_for_size_impl< uchar, 32, true, true> { using type = simd_abi::Avx; };
#endif
#ifdef Vc_HAVE_AVX512_ABI
template <> struct abi_for_size_impl<double, 8, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl<float, 16, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< llong, 8, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl<ullong, 8, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< long, 64 / sizeof(long), true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< ulong, 64 / sizeof(long), true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< int, 16, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< uint, 16, true, true> { using type = simd_abi::Avx512; };
#endif
#ifdef Vc_HAVE_FULL_AVX512_ABI
template <> struct abi_for_size_impl< short, 32, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl<ushort, 32, true, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< schar, 64, false, true> { using type = simd_abi::Avx512; };
template <> struct abi_for_size_impl< uchar, 64, false, true> { using type = simd_abi::Avx512; };
template <class T> struct abi_for_size_impl<T, 64, false, true> {
    using type = simd_abi::fixed_size<64>;
};
#endif
#ifdef Vc_HAVE_FULL_NEON_ABI
template <> struct abi_for_size_impl<double, 2, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< float, 4, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< llong, 2, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl<ullong, 2, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< long, 16 / sizeof(long), true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< ulong, 16 / sizeof(long), true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< int, 4, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< uint, 4, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< short, 8, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl<ushort, 8, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< schar, 16, true, true> { using type = simd_abi::Neon; };
template <> struct abi_for_size_impl< uchar, 16, true, true> { using type = simd_abi::Neon; };
#endif
}
template <class T, size_t N, class... Abis>
struct abi_for_size
    : public detail::abi_for_size_impl<T, N, (N <= simd_abi::max_fixed_size<T>),
                                       std::is_arithmetic<T>::value> {
};
template <size_t N, class... Abis> struct abi_for_size<bool, N, Abis...> {
};
template <class T, class... Abis> struct abi_for_size<T, 0, Abis...> {
};
template <class T, size_t N, class... Abis>
using abi_for_size_t = typename abi_for_size<T, N, Abis...>::type;
namespace experimental
{
template <class T, class V> struct rebind_simd;
template <class T, class U, class Abi> struct rebind_simd<T, simd<U, Abi>> {
    using type = simd<T, abi_for_size_t<T, simd_size_v<U, Abi>, Abi>>;
};
template <class T, class U, class Abi> struct rebind_simd<T, simd_mask<U, Abi>> {
    using type = simd_mask<T, abi_for_size_t<T, simd_size_v<U, Abi>, Abi>>;
};
template <class T, class V> using rebind_simd_t = typename rebind_simd<T, V>::type;
template <int N, class V> struct resize_simd;
template <int N, class T, class Abi> struct resize_simd<N, simd<T, Abi>> {
    using type = simd<T, abi_for_size_t<T, N, Abi>>;
};
template <int N, class T, class Abi> struct resize_simd<N, simd_mask<T, Abi>> {
    using type = simd_mask<T, abi_for_size_t<T, N, Abi>>;
};
template <int N, class V> using resize_simd_t = typename resize_simd<N, V>::type;
}
namespace detail
{
using Vc::experimental::rebind_simd_t;
using Vc::experimental::resize_simd_t;
}
template <class T, class U = typename T::value_type>
struct memory_alignment
    : public detail::size_constant<detail::next_power_of_2(sizeof(U) * T::size())> {
};
template <class T, class U = typename T::value_type>
inline constexpr size_t memory_alignment_v = memory_alignment<T, U>::value;
template <class T, class Abi = simd_abi::detail::default_abi<T>> class simd;
template <class T, class Abi> struct is_simd<simd<T, Abi>> : public std::true_type {};
template <class T> using native_simd = simd<T, simd_abi::native<T>>;
template <class T, int N> using fixed_size_simd = simd<T, simd_abi::fixed_size<N>>;
template <class T, class Abi = simd_abi::detail::default_abi<T>> class simd_mask;
template <class T, class Abi> struct is_simd_mask<simd_mask<T, Abi>> : public std::true_type {};
template <class T> using native_mask = simd_mask<T, simd_abi::native<T>>;
template <class T, int N> using fixed_size_mask = simd_mask<T, simd_abi::fixed_size<N>>;
namespace detail
{
template <class T, class Abi> struct get_impl<Vc::simd_mask<T, Abi>> {
    using type = typename traits<T, Abi>::mask_impl_type;
};
template <class T, class Abi> struct get_impl<Vc::simd<T, Abi>> {
    using type = typename traits<T, Abi>::simd_impl_type;
};
template <class T, class Abi> struct get_traits<Vc::simd_mask<T, Abi>> {
    using type = detail::traits<T, Abi>;
};
template <class T, class Abi> struct get_traits<Vc::simd<T, Abi>> {
    using type = detail::traits<T, Abi>;
};
}
namespace detail
{
template <class From, class To> struct static_simd_cast_return_type2;
template <class From, class To>
struct static_simd_cast_return_type : public static_simd_cast_return_type2<From, To> {
};
template <class From> struct static_simd_cast_return_type<From, From> {
    using type = From;
};
template <class U, class A1>
struct static_simd_cast_return_type2<simd<U, A1>, U> {
    using type = simd<U, A1>;
};
template <class U, class A1, class T>
struct static_simd_cast_return_type2<simd<U, A1>, T> {
    static_assert(!is_simd_v<T>,
                  "this specialization should never match for T = simd<...>");
    template <class TT>
    using make_unsigned_t =
        typename std::conditional_t<std::is_integral<TT>::value, std::make_unsigned<TT>,
                                    identity<TT>>::type;
    using type =
        simd<T,
             std::conditional_t<detail::all<std::is_integral<T>, std::is_integral<U>,
                                            std::is_same<make_unsigned_t<T>,
                                                         make_unsigned_t<U>>>::value,
                                A1, simd_abi::fixed_size<simd_size_v<U, A1>>>>;
};
template <class U, class A1, class T, class A0>
struct static_simd_cast_return_type2<simd<U, A1>, simd<T, A0>>
    : public std::enable_if<(simd_size_v<U, A1> == simd_size_v<T, A0>), simd<T, A0>> {
};
template <class T> T convert_mask(bool x);
template <class To, class, class, class Native, class From>
Vc_INTRINSIC To mask_cast_impl(const Native *, const From &x)
{
    return {Vc::detail::private_init,
            detail::convert_mask<typename detail::get_traits_t<To>::mask_member_type>(x)};
}
template <class To, class, class, class Native, size_t N>
Vc_INTRINSIC To mask_cast_impl(const Native *, const std::bitset<N> &x)
{
    return {Vc::detail::bitset_init, x};
}
template <class To, class, class>
Vc_INTRINSIC To mask_cast_impl(const std::bitset<1> *, bool x)
{
    return To(x);
}
template <class To, class T, class Abi, size_t N, class From>
Vc_INTRINSIC To mask_cast_impl(const std::bitset<N> *, const From &x)
{
    using impl = typename detail::traits<T, Abi>::mask_impl_type;
    return {Vc::detail::private_init, impl::to_bitset(x)};
}
template <class To, class, class, size_t N>
Vc_INTRINSIC To mask_cast_impl(const std::bitset<N> *, const std::bitset<N> &x)
{
    return {Vc::detail::private_init, x};
}
}
template <class T, class U, class A,
          class R = typename detail::static_simd_cast_return_type<simd<U, A>, T>::type>
Vc_INTRINSIC R static_simd_cast(const simd<U, A> &x)
{
#ifdef __cpp_if_constexpr
    if constexpr(std::is_same<R, simd<U, A>>::value) {
        return x;
    }
#endif
    detail::simd_converter<U, A, typename R::value_type, typename R::abi_type> c;
    return R(detail::private_init, c(detail::data(x)));
}
template <class T, class U, class A,
          class R = typename detail::static_simd_cast_return_type<
              simd<U, A>, typename T::simd_type>::type>
Vc_INTRINSIC typename R::mask_type static_simd_cast(const simd_mask<U, A> &x)
{
    using RM = typename R::mask_type;
#ifdef __cpp_if_constexpr
    if constexpr(std::is_same<RM, simd_mask<U, A>>::value) {
        return x;
    }
#endif
    using traits = detail::traits<typename R::value_type, typename R::abi_type>;
    const typename traits::mask_member_type *tag = nullptr;
    return detail::mask_cast_impl<RM, U, A>(tag, detail::data(x));
}
template <class T, class U, class A, class To = detail::value_type_or_identity<T>>
Vc_INTRINSIC auto simd_cast(const simd<detail::value_preserving<U, To>, A> &x)
    ->decltype(static_simd_cast<T>(x))
{
    return static_simd_cast<T>(x);
}
template <class T, class U, class A, class To = detail::value_type_or_identity<T>>
Vc_INTRINSIC auto simd_cast(const simd_mask<detail::value_preserving<U, To>, A> &x)
    ->decltype(static_simd_cast<T>(x))
{
    return static_simd_cast<T>(x);
}
template <class T, int N>
Vc_INTRINSIC fixed_size_simd<T, N> to_fixed_size(const fixed_size_simd<T, N> &x)
{
    return x;
}
template <class T, int N>
Vc_INTRINSIC fixed_size_mask<T, N> to_fixed_size(const fixed_size_mask<T, N> &x)
{
    return x;
}
template <class T, class A> Vc_INTRINSIC auto to_fixed_size(const simd<T, A> &x)
{
    return simd<T, simd_abi::fixed_size<simd_size_v<T, A>>>(
        [&x](auto i) { return x[i]; });
}
template <class T, class A> Vc_INTRINSIC auto to_fixed_size(const simd_mask<T, A> &x)
{
    constexpr int N = simd_mask<T, A>::size();
    fixed_size_mask<T, N> r;
    detail::execute_n_times<N>([&](auto i) { r[i] = x[i]; });
    return r;
}
template <class T, int N>
Vc_INTRINSIC std::enable_if_t<(N == native_simd<T>::size()), native_simd<T>>
to_native(const fixed_size_simd<T, N> &x)
{
    alignas(memory_alignment_v<native_simd<T>>) T mem[N];
    x.copy_to(mem, vector_aligned);
    return {mem, vector_aligned};
}
template <class T, size_t N>
Vc_INTRINSIC std::enable_if_t<(N == native_mask<T>::size()), native_mask<T>> to_native(
    const fixed_size_mask<T, N> &x)
{
    return native_mask<T>([&](auto i) { return x[i]; });
}
template <class T, size_t N>
Vc_INTRINSIC std::enable_if_t<(N == simd<T>::size()), simd<T>> to_compatible(
    const simd<T, simd_abi::fixed_size<N>> &x)
{
    alignas(memory_alignment_v<simd<T>>) T mem[N];
    x.copy_to(mem, vector_aligned);
    return {mem, vector_aligned};
}
template <class T, size_t N>
Vc_INTRINSIC std::enable_if_t<(N == simd_mask<T>::size()), simd_mask<T>> to_compatible(
    const simd_mask<T, simd_abi::fixed_size<N>> &x)
{
    return simd_mask<T>([&](auto i) { return x[i]; });
}
namespace detail
{
template <class To, size_t N> Vc_INTRINSIC To simd_reinterpret_cast_impl(std::bitset<N> x)
{
    return {bitset_init, x};
}
template <class To, class T, size_t N>
Vc_INTRINSIC To simd_reinterpret_cast_impl(Storage<T, N> x)
{
    return {private_init, x};
}
}
namespace experimental
{
template <class To, class T, class A,
          class = std::enable_if_t<sizeof(To) == sizeof(simd<T, A>) &&
                                   (is_simd_v<To> || is_simd_mask_v<To>)>>
Vc_INTRINSIC To simd_reinterpret_cast(const simd<T, A> &x)
{
    return reinterpret_cast<const To &>(x);
}
template <class To, class T, class A,
          class = std::enable_if_t<(is_simd_v<To> || is_simd_mask_v<To>)>>
Vc_INTRINSIC To simd_reinterpret_cast(const simd_mask<T, A> &x)
{
    return Vc::detail::simd_reinterpret_cast_impl<To>(detail::data(x));
}
}
template <class T, class Abi> inline bool all_of(const simd_mask<T, Abi> &k);
template <class T, class Abi> inline bool any_of(const simd_mask<T, Abi> &k);
template <class T, class Abi> inline bool none_of(const simd_mask<T, Abi> &k);
template <class T, class Abi> inline bool some_of(const simd_mask<T, Abi> &k);
template <class T, class Abi> inline int popcount(const simd_mask<T, Abi> &k);
template <class T, class Abi> inline int find_first_set(const simd_mask<T, Abi> &k);
template <class T, class Abi> inline int find_last_set(const simd_mask<T, Abi> &k);
constexpr bool all_of(detail::exact_bool x) { return x; }
constexpr bool any_of(detail::exact_bool x) { return x; }
constexpr bool none_of(detail::exact_bool x) { return !x; }
constexpr bool some_of(detail::exact_bool) { return false; }
constexpr int popcount(detail::exact_bool x) { return x; }
constexpr int find_first_set(detail::exact_bool) { return 0; }
constexpr int find_last_set(detail::exact_bool) { return 0; }
#ifdef Vc_EXPERIMENTAL
namespace detail {
template <class T, class A> class masked_simd_impl;
template <class T, class A>
masked_simd_impl<T, A> masked_simd(const typename simd<T, A>::mask_type &k,
                                         simd<T, A> &v);
}
#endif
template <typename M, typename T> class const_where_expression
{
    using V = T;
    static_assert(std::is_same_v<V, std::decay_t<T>>);
    struct Wrapper {
        using value_type = V;
    };
protected:
    using value_type =
        typename std::conditional_t<std::is_arithmetic<V>::value, Wrapper, V>::value_type;
    friend Vc_INTRINSIC const M &get_mask(const const_where_expression &x) { return x.k; }
    friend Vc_INTRINSIC const T &get_lvalue(const const_where_expression &x) { return x.d; }
    const M &k;
    T &d;
public:
    const_where_expression(const const_where_expression &) = delete;
    const_where_expression &operator=(const const_where_expression &) = delete;
    Vc_INTRINSIC const_where_expression(const M &kk, const T &dd) : k(kk), d(const_cast<T &>(dd)) {}
    Vc_INTRINSIC V operator-() const &&
    {
        return {detail::private_init,
                detail::get_impl_t<V>::template masked_unary<std::negate>(
                    detail::data(k), detail::data(d))};
    }
    template <class U, class Flags>
    Vc_NODISCARD Vc_INTRINSIC V
    copy_from(const detail::loadstore_ptr_type<U, value_type> *mem, Flags f) const &&
    {
        V r = d;
        detail::get_impl_t<V>::masked_load(detail::data(r), detail::data(k), mem, f);
        return r;
    }
    template <class U, class Flags>
    Vc_INTRINSIC void copy_to(detail::loadstore_ptr_type<U, value_type> *mem,
                              Flags f) const &&
    {
        detail::get_impl_t<V>::masked_store(detail::data(d), mem, f, detail::data(k));
    }
};
template <typename T> class const_where_expression<bool, T>
{
    using M = bool;
    using V = T;
    static_assert(std::is_same_v<V, std::decay_t<T>>);
    struct Wrapper {
        using value_type = V;
    };
protected:
    using value_type =
        typename std::conditional_t<std::is_arithmetic<V>::value, Wrapper, V>::value_type;
    friend Vc_INTRINSIC const M &get_mask(const const_where_expression &x) { return x.k; }
    friend Vc_INTRINSIC const T &get_lvalue(const const_where_expression &x) { return x.d; }
    const bool k;
    T &d;
public:
    const_where_expression(const const_where_expression &) = delete;
    const_where_expression &operator=(const const_where_expression &) = delete;
    Vc_INTRINSIC const_where_expression(const bool kk, const T &dd) : k(kk), d(const_cast<T &>(dd)) {}
    Vc_INTRINSIC V operator-() const && { return k ? -d : d; }
    template <class U, class Flags>
    Vc_NODISCARD Vc_INTRINSIC V
    copy_from(const detail::loadstore_ptr_type<U, value_type> *mem, Flags) const &&
    {
        return k ? static_cast<V>(mem[0]) : d;
    }
    template <class U, class Flags>
    Vc_INTRINSIC void copy_to(detail::loadstore_ptr_type<U, value_type> *mem,
                              Flags) const &&
    {
        if (k) {
            mem[0] = d;
        }
    }
};
template <typename M, typename T>
class where_expression : public const_where_expression<M, T>
{
    static_assert(!std::is_const<T>::value, "where_expression may only be instantiated with a non-const T parameter");
    using typename const_where_expression<M, T>::value_type;
    using const_where_expression<M, T>::k;
    using const_where_expression<M, T>::d;
    static_assert(std::is_same<typename M::abi_type, typename T::abi_type>::value, "");
    static_assert(M::size() == T::size(), "");
    friend Vc_INTRINSIC T &get_lvalue(where_expression &x) { return x.d; }
public:
    where_expression(const where_expression &) = delete;
    where_expression &operator=(const where_expression &) = delete;
    Vc_INTRINSIC where_expression(const M &kk, T &dd)
        : const_where_expression<M, T>(kk, dd)
    {
    }
    template <class U> Vc_INTRINSIC void operator=(U &&x) &&
    {
        Vc::detail::get_impl_t<T>::masked_assign(
            detail::data(k), detail::data(d),
            detail::to_value_type_or_member_type<T>(std::forward<U>(x)));
    }
#define Vc_OP_(op_,name_) \
    template <class U> Vc_INTRINSIC void operator op_##=(U &&x) && \
    { \
        Vc::detail::get_impl_t<T>::template masked_cassign<name_>( \
            detail::data(k), detail::data(d), \
            detail::to_value_type_or_member_type<T>(std::forward<U>(x))); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
    Vc_OP_(+, std::plus);
    Vc_OP_(-, std::minus);
    Vc_OP_(*, std::multiplies);
    Vc_OP_(/, std::divides);
    Vc_OP_(%, std::modulus);
    Vc_OP_(&, std::bit_and);
    Vc_OP_(|, std::bit_or);
    Vc_OP_(^, std::bit_xor);
    Vc_OP_(<<, detail::shift_left);
    Vc_OP_(>>, detail::shift_right);
#undef Vc_OP_
    Vc_INTRINSIC void operator++() &&
    {
        detail::data(d) = detail::get_impl_t<T>::template masked_unary<detail::increment>(
            detail::data(k), detail::data(d));
    }
    Vc_INTRINSIC void operator++(int) &&
    {
        detail::data(d) = detail::get_impl_t<T>::template masked_unary<detail::increment>(
            detail::data(k), detail::data(d));
    }
    Vc_INTRINSIC void operator--() &&
    {
        detail::data(d) = detail::get_impl_t<T>::template masked_unary<detail::decrement>(
            detail::data(k), detail::data(d));
    }
    Vc_INTRINSIC void operator--(int) &&
    {
        detail::data(d) = detail::get_impl_t<T>::template masked_unary<detail::decrement>(
            detail::data(k), detail::data(d));
    }
    template <class U, class Flags>
    Vc_INTRINSIC void copy_from(const detail::loadstore_ptr_type<U, value_type> *mem,
                                Flags f) &&
    {
        detail::get_impl_t<T>::masked_load(detail::data(d), detail::data(k), mem, f);
    }
#ifdef Vc_EXPERIMENTAL
    template <class F>
    Vc_INTRINSIC std::enable_if_t<
        detail::all<std::is_same<decltype(declval<F>()(detail::masked_simd(
                                     declval<const M &>(), declval<T &>()))),
                                 void>>::value,
        where_expression &&>
    apply(F &&f) &&
    {
        std::forward<F>(f)(detail::masked_simd(k, d));
        return std::move(*this);
    }
    template <class F>
    Vc_INTRINSIC std::enable_if_t<
        detail::all<std::is_same<decltype(declval<F>()(detail::masked_simd(
                                     declval<const M &>(), declval<T &>()))),
                                 void>>::value,
        where_expression &&>
    apply_inv(F &&f) &&
    {
        std::forward<F>(f)(detail::masked_simd(!k, d));
        return std::move(*this);
    }
#endif
};
template <typename T>
class where_expression<bool, T> : public const_where_expression<bool, T>
{
    using M = bool;
    using typename const_where_expression<M, T>::value_type;
    using const_where_expression<M, T>::k;
    using const_where_expression<M, T>::d;
public:
    where_expression(const where_expression &) = delete;
    where_expression &operator=(const where_expression &) = delete;
    Vc_INTRINSIC where_expression(const M &kk, T &dd)
        : const_where_expression<M, T>(kk, dd)
    {
    }
#define Vc_OP_(op_) \
    template <class U> Vc_INTRINSIC void operator op_(U &&x) && \
    { \
        if (k) { \
            d op_ std::forward<U>(x); \
        } \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
    Vc_OP_(=);
    Vc_OP_(+=);
    Vc_OP_(-=);
    Vc_OP_(*=);
    Vc_OP_(/=);
    Vc_OP_(%=);
    Vc_OP_(&=);
    Vc_OP_(|=);
    Vc_OP_(^=);
    Vc_OP_(<<=);
    Vc_OP_(>>=);
#undef Vc_OP_
    Vc_INTRINSIC void operator++() && { if (k) { ++d; } }
    Vc_INTRINSIC void operator++(int) && { if (k) { ++d; } }
    Vc_INTRINSIC void operator--() && { if (k) { --d; } }
    Vc_INTRINSIC void operator--(int) && { if (k) { --d; } }
    template <class U, class Flags>
    Vc_INTRINSIC void copy_from(const detail::loadstore_ptr_type<U, value_type> *mem,
                                Flags) &&
    {
        if (k) {
            d = mem[0];
        }
    }
};
#ifdef Vc_EXPERIMENTAL
template <typename M, typename... Ts> class where_expression<M, std::tuple<Ts &...>>
{
    const M &k;
    std::tuple<Ts &...> d;
public:
    where_expression(const where_expression &) = delete;
    where_expression &operator=(const where_expression &) = delete;
    Vc_INTRINSIC where_expression(const M &kk, std::tuple<Ts &...> &&dd) : k(kk), d(dd) {}
private:
    template <class F, std::size_t... Is>
    Vc_INTRINSIC void apply_helper(F &&f, const M &simd_mask, std::index_sequence<Is...>)
    {
        return std::forward<F>(f)(detail::masked_simd(simd_mask, std::get<Is>(d))...);
    }
public:
    template <class F>
    Vc_INTRINSIC std::enable_if_t<
        detail::all<std::is_same<decltype(declval<F>()(detail::masked_simd(
                                     declval<const M &>(), declval<Ts &>())...)),
                                 void>>::value,
        where_expression &&>
    apply(F &&f) &&
    {
        apply_helper(std::forward<F>(f), k, std::make_index_sequence<sizeof...(Ts)>());
        return std::move(*this);
    }
    template <class F>
    Vc_INTRINSIC std::enable_if_t<
        detail::all<std::is_same<decltype(declval<F>()(detail::masked_simd(
                                     declval<const M &>(), declval<Ts &>())...)),
                                 void>>::value,
        where_expression &&>
    apply_inv(F &&f) &&
    {
        apply_helper(std::forward<F>(f), !k, std::make_index_sequence<sizeof...(Ts)>());
        return std::move(*this);
    }
};
template <class T, class A, class... Vs>
Vc_INTRINSIC where_expression<simd_mask<T, A>, std::tuple<simd<T, A> &, Vs &...>> where(
    const typename simd<T, A>::mask_type &k, simd<T, A> &v0, Vs &... vs)
{
    return {k, std::tie(v0, vs...)};
}
#endif
template <class T, class A>
Vc_INTRINSIC where_expression<simd_mask<T, A>, simd<T, A>> where(
    const typename simd<T, A>::mask_type &k, simd<T, A> &d)
{
    return {k, d};
}
template <class T, class A>
Vc_INTRINSIC const_where_expression<simd_mask<T, A>, simd<T, A>> where(
    const typename simd<T, A>::mask_type &k, const simd<T, A> &d)
{
    return {k, d};
}
template <class T, class A>
Vc_INTRINSIC where_expression<simd_mask<T, A>, simd_mask<T, A>> where(
    const std::remove_const_t<simd_mask<T, A>> &k, simd_mask<T, A> &d)
{
    return {k, d};
}
template <class T, class A>
Vc_INTRINSIC const_where_expression<simd_mask<T, A>, simd_mask<T, A>> where(
    const std::remove_const_t<simd_mask<T, A>> &k, const simd_mask<T, A> &d)
{
    return {k, d};
}
template <class T>
Vc_INTRINSIC where_expression<bool, T> where(detail::exact_bool k, T &d)
{
    return {k, d};
}
template <class T>
Vc_INTRINSIC const_where_expression<bool, T> where(detail::exact_bool k, const T &d)
{
    return {k, d};
}
template <class T, class A> void where(bool k, simd<T, A> &d) = delete;
template <class T, class A> void where(bool k, const simd<T, A> &d) = delete;
namespace experimental
{
template <size_t N> class where_range
{
    const std::bitset<N> bits;
public:
    where_range(std::bitset<N> b) : bits(b) {}
    class iterator
    {
#ifdef Vc_MSVC
        unsigned long mask;
        unsigned long bit;
#else
        size_t mask;
        size_t bit;
#endif
        void next_bit()
        {
#ifdef Vc_GNU_ASM
            bit = __builtin_ctzl(mask);
#elif defined(Vc_MSVC)
            _BitScanForward(&bit, mask);
#else
#error "Not implemented yet."
#endif
        }
        void reset_lsb()
        {
            mask &= (mask - 1);
        }
    public:
        iterator(decltype(mask) m) : mask(m) { next_bit(); }
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        Vc_ALWAYS_INLINE size_t operator->() const { return bit; }
        Vc_ALWAYS_INLINE size_t operator*() const { return bit; }
        Vc_ALWAYS_INLINE iterator &operator++()
        {
            reset_lsb();
            next_bit();
            return *this;
        }
        Vc_ALWAYS_INLINE iterator operator++(int)
        {
            iterator tmp = *this;
            reset_lsb();
            next_bit();
            return tmp;
        }
        Vc_ALWAYS_INLINE bool operator==(const iterator &rhs) const
        {
            return mask == rhs.mask;
        }
        Vc_ALWAYS_INLINE bool operator!=(const iterator &rhs) const
        {
            return mask != rhs.mask;
        }
    };
    iterator begin() const { return bits.to_ullong(); }
    iterator end() const { return 0; }
};
template <class T, class A> where_range<simd_size_v<T, A>> where(const simd_mask<T, A> &k)
{
    return k.to_bitset();
}
}
template <class T, class Abi, class BinaryOperation = std::plus<>>
Vc_INTRINSIC T reduce(const simd<T, Abi> &v,
                      BinaryOperation binary_op = BinaryOperation())
{
    using V = simd<T, Abi>;
    return detail::get_impl_t<V>::reduce(detail::size_tag<V::size()>, v, binary_op);
}
template <class M, class V, class BinaryOperation = std::plus<>>
Vc_INTRINSIC typename V::value_type reduce(const const_where_expression<M, V> &x,
                                           typename V::value_type identity_element,
                                           BinaryOperation binary_op)
{
    V tmp = identity_element;
    detail::get_impl_t<V>::masked_assign(detail::data(get_mask(x)), detail::data(tmp),
                                         detail::data(get_lvalue(x)));
    return reduce(tmp, binary_op);
}
template <class M, class V>
Vc_INTRINSIC typename V::value_type reduce(const const_where_expression<M, V> &x,
                                           std::plus<> binary_op = {})
{
    return reduce(x, 0, binary_op);
}
template <class M, class V>
Vc_INTRINSIC typename V::value_type reduce(const const_where_expression<M, V> &x,
                                           std::multiplies<> binary_op)
{
    return reduce(x, 1, binary_op);
}
template <class M, class V>
Vc_INTRINSIC typename V::value_type reduce(const const_where_expression<M, V> &x,
                                           std::bit_and<> binary_op)
{
    return reduce(x, ~typename V::value_type(), binary_op);
}
template <class M, class V>
Vc_INTRINSIC typename V::value_type reduce(const const_where_expression<M, V> &x,
                                           std::bit_or<> binary_op)
{
    return reduce(x, 0, binary_op);
}
template <class M, class V>
Vc_INTRINSIC typename V::value_type reduce(const const_where_expression<M, V> &x,
                                           std::bit_xor<> binary_op)
{
    return reduce(x, 0, binary_op);
}
template <class T, class A>
Vc_INTRINSIC simd<T, A> min(const simd<T, A> &a, const simd<T, A> &b)
{
    return {detail::private_init,
            A::simd_impl_type::min(detail::data(a), detail::data(b))};
}
template <class T, class A>
Vc_INTRINSIC simd<T, A> max(const simd<T, A> &a, const simd<T, A> &b)
{
    return {detail::private_init,
            A::simd_impl_type::max(detail::data(a), detail::data(b))};
}
template <class T, class A>
Vc_INTRINSIC std::pair<simd<T, A>, simd<T, A>> minmax(const simd<T, A> &a,
                                                            const simd<T, A> &b)
{
    const auto pair_of_members =
        A::simd_impl_type::minmax(detail::data(a), detail::data(b));
    return {simd<T, A>(detail::private_init, pair_of_members.first),
            simd<T, A>(detail::private_init, pair_of_members.second)};
}
template <class T, class A>
Vc_INTRINSIC simd<T, A> clamp(const simd<T, A> &v, const simd<T, A> &lo,
                                 const simd<T, A> &hi)
{
    using Impl = typename A::simd_impl_type;
    return {detail::private_init,
            Impl::min(detail::data(hi), Impl::max(detail::data(lo), detail::data(v)))};
}
namespace experimental
{
template <int Stride, int Offset = 0> struct strided {
    static constexpr int stride = Stride;
    static constexpr int offset = Offset;
    template <class T, class A>
    using shuffle_return_type =
        fixed_size_simd<T, (simd_size_v<T, A> - Offset + Stride - 1) / Stride>;
    template <class T> static constexpr auto src_index(T dst_index)
    {
        return Offset + dst_index * Stride;
    }
};
template <class P, class T, class A,
          class R = typename P::template shuffle_return_type<T, A>,
          class = decltype(P::src_index(Vc::detail::size_constant<0>()))>
Vc_NOT_OPTIMIZED Vc_INTRINSIC R shuffle(const simd<T, A> &x)
{
    return R([&x](auto i) { return x[P::src_index(i)]; });
}
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_DETAIL_SPLIT_H_
#define VC_DETAIL_SPLIT_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class V, size_t Parts> struct split_to_array {
    template <class A, size_t... Indexes>
    std::array<V, Parts> operator()(const simd<typename V::value_type, A> &x,
                                    std::index_sequence<Indexes...>)
    {
        return {[](size_t j, const simd<typename V::value_type, A> &y) {
            return V([&](auto i) { return y[i + j * V::size()]; });
        }(Indexes, x)...};
    }
};
}
template <class V, class A,
          size_t Parts = simd_size_v<typename V::value_type, A> / V::size()>
std::enable_if_t<(is_simd<V>::value &&
                  simd_size_v<typename V::value_type, A> == Parts * V::size()),
                 std::array<V, Parts>>
split(const simd<typename V::value_type, A> &x)
{
    return detail::split_to_array<V, Parts>()(x, std::make_index_sequence<Parts>());
}
namespace detail
{
template <class Tuple, class From> struct split_to_tuple {
    using T = typename std::tuple_element<0, Tuple>::type::value_type;
    Vc_INTRINSIC Tuple operator()(const simd<T, From> &x)
    {
        Tuple tup;
        size_t offset = 0;
        detail::execute_n_times<std::tuple_size<Tuple>::value>([&](auto i) {
            auto &v_i = std::get<i>(tup);
            constexpr size_t N = std::decay_t<decltype(v_i)>::size();
            detail::execute_n_times<N>([&](auto j) { v_i[j] = x[j + offset]; });
            offset += N;
        });
        return tup;
    }
};
}
template <size_t... Sizes, class T, class A
#ifdef __cpp_fold_expressions
          , class = std::enable_if_t<((Sizes + ...) == simd<T, A>::size())>
#endif
          >
Vc_ALWAYS_INLINE std::tuple<simd<T, abi_for_size_t<T, Sizes>>...> split(
    const simd<T, A> &x)
{
    return detail::split_to_tuple<std::tuple<simd<T, abi_for_size_t<T, Sizes>>...>, A>()(
        x);
}
namespace detail
{
template <class T, class...> struct typelist
{
    using first_type = T;
};
template <size_t N, class T, class List,
          bool = (N < simd_size_v<T, typename List::first_type>)>
struct subscript_in_pack;
template <size_t N, class T, class A, class... As>
struct subscript_in_pack<N, T, detail::typelist<A, As...>, true> {
    static Vc_INTRINSIC T get(const simd<T, A> &x, const simd<T, As> &...)
    {
        return x[N];
    }
};
template <size_t N, class T, class A, class... As>
struct subscript_in_pack<N, T, detail::typelist<A, As...>, false> {
    static Vc_INTRINSIC T get(const simd<T, A> &, const simd<T, As> &... xs)
    {
        return subscript_in_pack<N - simd<T, A>::size(), T,
                                 detail::typelist<As...>>::get(xs...);
    }
};
}
#if defined __cpp_fold_expressions
template <class T, class... As>
simd<T, abi_for_size_t<T, (simd_size_v<T, As> + ...)>> concat(
    const simd<T, As> &... xs)
{
    return simd<T, abi_for_size_t<T, (simd_size_v<T, As> + ...)>>([&](auto i) {
        return detail::subscript_in_pack<i, T, detail::typelist<As...>>::get(xs...);
    });
}
#endif
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_MASK_H_
#define VC_SIMD_MASK_H_ 
#ifndef VC_SIMD_SMART_REFERENCE_H_
#define VC_SIMD_SMART_REFERENCE_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail {
template <class U, class Accessor = U, class ValueType = typename U::value_type>
class smart_reference
{
    friend Accessor;
    static constexpr bool get_noexcept = noexcept(Accessor::get(declval<U &>(), int()));
    template <typename T = ValueType> static constexpr bool set_noexcept()
    {
        return noexcept(Accessor::set(declval<U &>(), int(), declval<T>()));
    }
    int index;
    U &obj;
public:
    Vc_INTRINSIC smart_reference(U &o, int i) noexcept : index(i), obj(o) {}
    using value_type = ValueType;
    Vc_INTRINSIC smart_reference(const smart_reference &) = delete;
    Vc_INTRINSIC operator value_type() const noexcept(get_noexcept)
    {
        return Accessor::get(obj, index);
    }
    template <class T,
              class = detail::value_preserving_or_int<std::decay_t<T>, value_type>>
        Vc_INTRINSIC smart_reference operator=(T &&x) && noexcept(set_noexcept())
    {
        Accessor::set(obj, index, std::forward<T>(x));
        return {obj, index};
    }
#define Vc_OP_(op_) \
    template <class T, \
              class TT = decltype(std::declval<value_type>() op_ std::declval<T>()), \
              class = detail::value_preserving_or_int<std::decay_t<T>, TT>, \
              class = detail::value_preserving_or_int<TT, value_type>> \
        Vc_INTRINSIC smart_reference operator op_##=(T &&x) && \
        noexcept(get_noexcept && set_noexcept()) \
    { \
        const value_type &lhs = Accessor::get(obj, index); \
        Accessor::set(obj, index, lhs op_ x); \
        return {obj, index}; \
    }
    Vc_ALL_ARITHMETICS(Vc_OP_);
    Vc_ALL_SHIFTS(Vc_OP_);
    Vc_ALL_BINARY(Vc_OP_);
#undef Vc_OP_
    template <typename = void>
        Vc_INTRINSIC smart_reference operator++() &&
        noexcept(noexcept(declval<value_type &>() = Accessor::get(declval<U &>(),
                                                                  int())) &&
                 set_noexcept<decltype(++declval<value_type &>())>())
    {
        value_type x = Accessor::get(obj, index);
        Accessor::set(obj, index, ++x);
        return {obj, index};
    }
    template <typename = void>
        Vc_INTRINSIC value_type operator++(int) &&
        noexcept(noexcept(declval<value_type &>() = Accessor::get(declval<U &>(),
                                                                  int())) &&
                 set_noexcept<decltype(declval<value_type &>()++)>())
    {
        const value_type r = Accessor::get(obj, index);
        value_type x = r;
        Accessor::set(obj, index, ++x);
        return r;
    }
    template <typename = void>
        Vc_INTRINSIC smart_reference operator--() &&
        noexcept(noexcept(declval<value_type &>() = Accessor::get(declval<U &>(),
                                                                  int())) &&
                 set_noexcept<decltype(--declval<value_type &>())>())
    {
        value_type x = Accessor::get(obj, index);
        Accessor::set(obj, index, --x);
        return {obj, index};
    }
    template <typename = void>
        Vc_INTRINSIC value_type operator--(int) &&
        noexcept(noexcept(declval<value_type &>() = Accessor::get(declval<U &>(),
                                                                  int())) &&
                 set_noexcept<decltype(declval<value_type &>()--)>())
    {
        const value_type r = Accessor::get(obj, index);
        value_type x = r;
        Accessor::set(obj, index, --x);
        return r;
    }
    friend inline void swap(smart_reference &&a, smart_reference &&b) noexcept(
        all<std::is_nothrow_constructible<value_type, smart_reference &&>,
            std::is_nothrow_assignable<smart_reference &&, value_type &&>>::value)
    {
        value_type tmp = static_cast<smart_reference &&>(a);
        static_cast<smart_reference &&>(a) = static_cast<value_type>(b);
        static_cast<smart_reference &&>(b) = std::move(tmp);
    }
    friend inline void swap(value_type &a, smart_reference &&b) noexcept(
        all<std::is_nothrow_constructible<value_type, value_type &&>,
            std::is_nothrow_assignable<value_type &, value_type &&>,
            std::is_nothrow_assignable<smart_reference &&, value_type &&>>::value)
    {
        value_type tmp(std::move(a));
        a = static_cast<value_type>(b);
        static_cast<smart_reference &&>(b) = std::move(tmp);
    }
    friend inline void swap(smart_reference &&a, value_type &b) noexcept(
        all<std::is_nothrow_constructible<value_type, smart_reference &&>,
            std::is_nothrow_assignable<value_type &, value_type &&>,
            std::is_nothrow_assignable<smart_reference &&, value_type &&>>::value)
    {
        value_type tmp(a);
        static_cast<smart_reference &&>(a) = std::move(b);
        b = std::move(tmp);
    }
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#include <bitset>
Vc_VERSIONED_NAMESPACE_BEGIN
Vc_MSVC_WARNING_(push)
Vc_MSVC_WARNING_(disable : 4624)
template <class T, class Abi> class simd_mask : public detail::traits<T, Abi>::mask_base
{
    using traits = detail::traits<T, Abi>;
    using impl = typename traits::mask_impl_type;
    using member_type = typename traits::mask_member_type;
    static constexpr detail::size_tag_type<T, Abi> size_tag = {};
    static constexpr T *type_tag = nullptr;
    friend typename traits::mask_base;
    friend class simd<T, Abi>;
    friend impl;
    friend typename traits::simd_impl_type;
public:
    using value_type = bool;
    using reference = detail::smart_reference<member_type, impl, value_type>;
    using simd_type = simd<T, Abi>;
    using size_type = size_t;
    using abi_type = Abi;
    static constexpr size_type size()
    {
        constexpr size_type N = size_tag;
        return N;
    }
    simd_mask() = default;
    simd_mask(const simd_mask &) = default;
    simd_mask(simd_mask &&) = default;
    simd_mask &operator=(const simd_mask &) = default;
    simd_mask &operator=(simd_mask &&) = default;
    static constexpr size_type size_v = size_tag;
    explicit Vc_ALWAYS_INLINE simd_mask(typename traits::mask_cast_type init) : d{init} {}
    static Vc_ALWAYS_INLINE simd_mask from_bitset(std::bitset<size_v> bs) { return {detail::bitset_init, bs}; }
    std::bitset<size_v> Vc_ALWAYS_INLINE to_bitset() const { return impl::to_bitset(d); }
    explicit Vc_ALWAYS_INLINE simd_mask(value_type x) : d(impl::broadcast(x, type_tag)) {}
    template <class U>
    Vc_ALWAYS_INLINE simd_mask(const simd_mask<U, simd_abi::fixed_size<size_v>> &x,
         enable_if<detail::all<std::is_same<abi_type, simd_abi::fixed_size<size_v>>,
                               std::is_same<U, U>>::value> = nullarg)
        : simd_mask{detail::bitset_init, detail::data(x)}
    {
    }
    template <class Flags>
    Vc_ALWAYS_INLINE simd_mask(const value_type *mem, Flags f)
        : d(impl::load(mem, f, size_tag))
    {
    }
    template <class Flags> Vc_ALWAYS_INLINE simd_mask(const value_type *mem, simd_mask k, Flags f) : d{}
    {
        impl::masked_load(d, k.d, mem, f, size_tag);
    }
    template <class Flags> Vc_ALWAYS_INLINE void copy_from(const value_type *mem, Flags f)
    {
        d = static_cast<decltype(d)>(impl::load(mem, f, size_tag));
    }
    template <class Flags> Vc_ALWAYS_INLINE void copy_to(value_type *mem, Flags f) const
    {
        impl::store(d, mem, f, size_tag);
    }
    Vc_ALWAYS_INLINE reference operator[](size_type i) { return {d, int(i)}; }
    Vc_ALWAYS_INLINE value_type operator[](size_type i) const { return impl::get(d, int(i)); }
    Vc_ALWAYS_INLINE simd_mask operator!() const { return {detail::private_init, impl::negate(d, size_tag)}; }
    friend Vc_ALWAYS_INLINE simd_mask operator&&(const simd_mask &x, const simd_mask &y)
    {
        return impl::logical_and(x, y);
    }
    friend Vc_ALWAYS_INLINE simd_mask operator||(const simd_mask &x, const simd_mask &y)
    {
        return impl::logical_or(x, y);
    }
    friend Vc_ALWAYS_INLINE simd_mask operator&(const simd_mask &x, const simd_mask &y) { return impl::bit_and(x, y); }
    friend Vc_ALWAYS_INLINE simd_mask operator|(const simd_mask &x, const simd_mask &y) { return impl::bit_or(x, y); }
    friend Vc_ALWAYS_INLINE simd_mask operator^(const simd_mask &x, const simd_mask &y) { return impl::bit_xor(x, y); }
    friend Vc_ALWAYS_INLINE simd_mask &operator&=(simd_mask &x, const simd_mask &y) { return x = impl::bit_and(x, y); }
    friend Vc_ALWAYS_INLINE simd_mask &operator|=(simd_mask &x, const simd_mask &y) { return x = impl::bit_or (x, y); }
    friend Vc_ALWAYS_INLINE simd_mask &operator^=(simd_mask &x, const simd_mask &y) { return x = impl::bit_xor(x, y); }
    friend Vc_ALWAYS_INLINE simd_mask operator==(const simd_mask &x, const simd_mask &y) { return !operator!=(x, y); }
    friend Vc_ALWAYS_INLINE simd_mask operator!=(const simd_mask &x, const simd_mask &y) { return impl::bit_xor(x, y); }
    Vc_INTRINSIC simd_mask(detail::private_init_t, typename traits::mask_member_type init)
        : d(init)
    {
    }
    Vc_INTRINSIC simd_mask(detail::bitset_init_t, std::bitset<size_v> init)
        : d(impl::from_bitset(init, type_tag))
    {
    }
private:
#ifdef Vc_MSVC
    template <class U, class A> friend const auto &detail::data(const simd_mask<U, A> &);
    template <class U, class A> friend auto &detail::data(simd_mask<U, A> &);
#else
    friend const auto &detail::data<T, abi_type>(const simd_mask &);
    friend auto &detail::data<T, abi_type>(simd_mask &);
#endif
    alignas(traits::mask_member_alignment)
        typename traits::mask_member_type d;
};
Vc_MSVC_WARNING_(pop)
namespace detail
{
template <class T, class A> Vc_INTRINSIC const auto &data(const simd_mask<T, A> &x) { return x.d; }
template <class T, class A> Vc_INTRINSIC auto &data(simd_mask<T, A> &x) { return x.d; }
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_SIMD_H_
#define VC_SIMD_SIMD_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
Vc_MSVC_WARNING_(push)
Vc_MSVC_WARNING_(disable : 4624)
namespace detail
{
template <class Derived> struct generic_simd_impl;
template <class T0, class T1, class A, bool BothIntegral> struct allow_conversion_ctor2_1;
template <class T0, class T1, class A>
struct allow_conversion_ctor2
    : public allow_conversion_ctor2_1<
          T0, T1, A, detail::all<std::is_integral<T0>, std::is_integral<T1>>::value> {
};
template <class T, class A> struct allow_conversion_ctor2<T, T, A> : public std::false_type {};
template <class T0, class T1, int N>
struct allow_conversion_ctor2<T0, T1, simd_abi::fixed_size<N>> : public std::false_type {};
template <class T, int N>
struct allow_conversion_ctor2<T, T, simd_abi::fixed_size<N>> : public std::false_type {};
template <class T0, class T1, class A>
struct allow_conversion_ctor2_1<T0, T1, A, true>
    : public std::is_same<std::make_signed_t<T0>, std::make_signed_t<T1>> {
};
template <class T0, class T1, class A>
struct allow_conversion_ctor2_1<T0, T1, A, false> : public std::false_type {
};
template <class T0, class A0, class T1, class A1, bool = std::is_same<A0, A1>::value>
struct allow_conversion_ctor3 : public std::false_type {
};
template <class T0, class T1, class A1>
struct allow_conversion_ctor3<T0, simd_abi::fixed_size<simd_size_v<T1, A1>>, T1, A1,
                              false
                              > : public std::is_convertible<T1, T0> {
};
template <class V, bool> class simd_int_operators;
template <class V> class simd_int_operators<V, false>
{
};
template <class V> class simd_int_operators<V, true>
{
    using impl = detail::get_impl_t<V>;
    Vc_INTRINSIC const V &derived() const { return *static_cast<const V *>(this); }
    template <class T> static Vc_INTRINSIC V make_derived(T &&d)
    {
        return {detail::private_init, std::forward<T>(d)};
    }
public:
    friend V &operator %=(V &lhs, const V &x) { return lhs = lhs % x; }
    friend V &operator &=(V &lhs, const V &x) { return lhs = lhs & x; }
    friend V &operator |=(V &lhs, const V &x) { return lhs = lhs | x; }
    friend V &operator ^=(V &lhs, const V &x) { return lhs = lhs ^ x; }
    friend V &operator<<=(V &lhs, const V &x) { return lhs = lhs << x; }
    friend V &operator>>=(V &lhs, const V &x) { return lhs = lhs >> x; }
    friend V &operator<<=(V &lhs, int x) { return lhs = lhs << x; }
    friend V &operator>>=(V &lhs, int x) { return lhs = lhs >> x; }
    friend V operator% (const V &x, const V &y) { return simd_int_operators::make_derived(impl::modulus (data(x), data(y))); }
    friend V operator& (const V &x, const V &y) { return simd_int_operators::make_derived(impl::bit_and (data(x), data(y))); }
    friend V operator| (const V &x, const V &y) { return simd_int_operators::make_derived(impl::bit_or (data(x), data(y))); }
    friend V operator^ (const V &x, const V &y) { return simd_int_operators::make_derived(impl::bit_xor (data(x), data(y))); }
    friend V operator<<(const V &x, const V &y) { return simd_int_operators::make_derived(impl::bit_shift_left (data(x), data(y))); }
    friend V operator>>(const V &x, const V &y) { return simd_int_operators::make_derived(impl::bit_shift_right(data(x), data(y))); }
    friend V operator<<(const V &x, int y) { return simd_int_operators::make_derived(impl::bit_shift_left (data(x), y)); }
    friend V operator>>(const V &x, int y) { return simd_int_operators::make_derived(impl::bit_shift_right(data(x), y)); }
    V operator~() const
    {
        return {private_init, impl::complement(derived().d)};
    }
};
}
template <class T, class Abi>
class simd
    : public detail::simd_int_operators<
          simd<T, Abi>,
          detail::all<std::is_integral<T>, typename detail::traits<T, Abi>::is_valid>::value>,
      public detail::traits<T, Abi>::simd_base
{
    using traits = detail::traits<T, Abi>;
    using impl = typename traits::simd_impl_type;
    using member_type = typename traits::simd_member_type;
    using cast_type = typename traits::simd_cast_type;
    static constexpr detail::size_tag_type<T, Abi> size_tag = {};
    static constexpr T *type_tag = nullptr;
    friend typename traits::simd_base;
    friend impl;
    friend detail::generic_simd_impl<impl>;
    friend detail::simd_int_operators<simd, true>;
public:
    using value_type = T;
    using reference = detail::smart_reference<member_type, impl, value_type>;
    using mask_type = simd_mask<T, Abi>;
    using size_type = size_t;
    using abi_type = Abi;
    static constexpr size_type size()
    {
        constexpr size_type N = size_tag;
        return N;
    }
    simd() = default;
    simd(const simd &) = default;
    simd(simd &&) = default;
    simd &operator=(const simd &) = default;
    simd &operator=(simd &&) = default;
    static constexpr size_type size_v = size_tag;
    template <class U, class = detail::value_preserving_or_int<U, value_type>>
    Vc_ALWAYS_INLINE simd(U &&x)
        : d(impl::broadcast(static_cast<value_type>(std::forward<U>(x)), size_tag))
    {
    }
    template <class U>
    Vc_ALWAYS_INLINE simd(
        const simd<U, simd_abi::fixed_size<size_v>> &x,
        std::enable_if_t<
            detail::all<std::is_same<simd_abi::fixed_size<size_v>, abi_type>,
                        detail::negation<detail::is_narrowing_conversion<U, value_type>>,
                        detail::converts_to_higher_integer_rank<U, value_type>>::value,
            void *> = nullptr)
        : simd{static_cast<std::array<U, size()>>(x).data(), vector_aligned}
    {
    }
#ifdef Vc_EXPERIMENTAL
    template <class U>
    explicit Vc_ALWAYS_INLINE simd(
        const simd<U, simd_abi::fixed_size<size_v>> &x,
        std::enable_if_t<
            detail::any<detail::all<detail::negation<std::is_same<
                                        simd_abi::fixed_size<size_v>, abi_type>>,
                                    std::is_convertible<U, value_type>>,
                        detail::is_narrowing_conversion<U, value_type>>::value,
            void *> = nullptr)
        : simd{static_cast<std::array<U, size()>>(x).data(), vector_aligned}
    {
    }
    template <class U>
    explicit Vc_ALWAYS_INLINE simd(
        const simd<U, Abi> &x,
        std::enable_if_t<detail::allow_conversion_ctor2<value_type, U, Abi>::value,
                         void *> = nullptr)
        : d{static_cast<cast_type>(x)}
    {
    }
    template <class U, class Abi2>
    explicit Vc_ALWAYS_INLINE simd(
        const simd<U, Abi2> &x,
        std::enable_if_t<detail::allow_conversion_ctor3<value_type, Abi, U, Abi2>::value,
                         void *> = nullptr)
    {
        x.copy_to(d.data(), overaligned<alignof(simd)>);
    }
#endif
    template <class F>
    explicit Vc_ALWAYS_INLINE simd(
        F &&gen,
        detail::value_preserving_or_int<
            decltype(declval<F>()(declval<detail::size_constant<0> &>())), value_type> * =
            nullptr)
        : d(impl::generator(std::forward<F>(gen), type_tag, size_tag))
    {
    }
#ifdef Vc_EXPERIMENTAL
    template <class U, U... Indexes>
    static Vc_ALWAYS_INLINE simd seq(std::integer_sequence<U, Indexes...>)
    {
        constexpr auto N = size();
        alignas(memory_alignment<simd>::value) static constexpr value_type mem[N] = {
            value_type(Indexes)...};
        return simd(mem, vector_aligned);
    }
    static Vc_ALWAYS_INLINE simd seq() {
#ifdef Vc_ICC
        simd r;
        detail::execute_n_times<size()>([&](auto i_) { r[i_] = i_; });
        return r;
#else
        return seq(std::make_index_sequence<size()>());
#endif
    }
#endif
    template <class U, class Flags>
    Vc_ALWAYS_INLINE simd(const U *mem, Flags f)
        : d(impl::load(mem, f, type_tag))
    {
    }
    template <class U, class Flags>
    Vc_ALWAYS_INLINE void copy_from(const detail::arithmetic<U> *mem, Flags f)
    {
        d = static_cast<decltype(d)>(impl::load(mem, f, type_tag));
    }
    template <class U, class Flags>
    Vc_ALWAYS_INLINE void copy_to(detail::arithmetic<U> *mem, Flags f) const
    {
        impl::store(d, mem, f, type_tag);
    }
    Vc_ALWAYS_INLINE reference operator[](size_type i) { return {d, int(i)}; }
    Vc_ALWAYS_INLINE value_type operator[](size_type i) const { return impl::get(d, int(i)); }
    Vc_ALWAYS_INLINE simd &operator++() { impl::increment(d); return *this; }
    Vc_ALWAYS_INLINE simd operator++(int) { simd r = *this; impl::increment(d); return r; }
    Vc_ALWAYS_INLINE simd &operator--() { impl::decrement(d); return *this; }
    Vc_ALWAYS_INLINE simd operator--(int) { simd r = *this; impl::decrement(d); return r; }
    Vc_ALWAYS_INLINE mask_type operator!() const
    {
        return {detail::private_init, impl::negate(d)};
    }
    Vc_ALWAYS_INLINE simd operator+() const { return *this; }
    Vc_ALWAYS_INLINE simd operator-() const
    {
        return {detail::private_init, impl::unary_minus(d)};
    }
    explicit Vc_ALWAYS_INLINE simd(cast_type init) : d(init) {}
    friend Vc_ALWAYS_INLINE simd &operator+=(simd &lhs, const simd &x) { return lhs = lhs + x; }
    friend Vc_ALWAYS_INLINE simd &operator-=(simd &lhs, const simd &x) { return lhs = lhs - x; }
    friend Vc_ALWAYS_INLINE simd &operator*=(simd &lhs, const simd &x) { return lhs = lhs * x; }
    friend Vc_ALWAYS_INLINE simd &operator/=(simd &lhs, const simd &x) { return lhs = lhs / x; }
    friend Vc_ALWAYS_INLINE simd operator+(const simd &x, const simd &y)
    {
        return {detail::private_init, impl::plus(x.d, y.d)};
    }
    friend Vc_ALWAYS_INLINE simd operator-(const simd &x, const simd &y)
    {
        return {detail::private_init, impl::minus(x.d, y.d)};
    }
    friend Vc_ALWAYS_INLINE simd operator*(const simd &x, const simd &y)
    {
        return {detail::private_init, impl::multiplies(x.d, y.d)};
    }
    friend Vc_ALWAYS_INLINE simd operator/(const simd &x, const simd &y)
    {
        return {detail::private_init, impl::divides(x.d, y.d)};
    }
    friend Vc_ALWAYS_INLINE mask_type operator==(const simd &x, const simd &y)
    {
        return simd::make_mask(impl::equal_to(x.d, y.d));
    }
    friend Vc_ALWAYS_INLINE mask_type operator!=(const simd &x, const simd &y)
    {
        return simd::make_mask(impl::not_equal_to(x.d, y.d));
    }
    friend Vc_ALWAYS_INLINE mask_type operator<(const simd &x, const simd &y)
    {
        return simd::make_mask(impl::less(x.d, y.d));
    }
    friend Vc_ALWAYS_INLINE mask_type operator<=(const simd &x, const simd &y)
    {
        return simd::make_mask(impl::less_equal(x.d, y.d));
    }
    friend Vc_ALWAYS_INLINE mask_type operator>(const simd &x, const simd &y)
    {
        return simd::make_mask(impl::less(y.d, x.d));
    }
    friend Vc_ALWAYS_INLINE mask_type operator>=(const simd &x, const simd &y)
    {
        return simd::make_mask(impl::less_equal(y.d, x.d));
    }
    Vc_INTRINSIC simd(detail::private_init_t, const member_type &init) : d(init) {}
    Vc_INTRINSIC simd(detail::bitset_init_t, std::bitset<size_v> init) : d() {
        where(mask_type(detail::bitset_init, init), *this) = ~*this;
    }
private:
    static Vc_INTRINSIC mask_type make_mask(typename mask_type::member_type k)
    {
        return {detail::private_init, k};
    }
#ifdef Vc_MSVC
    template <class U, class A> friend const auto &detail::data(const simd<U, A> &);
    template <class U, class A> friend auto &detail::data(simd<U, A> &);
#else
    friend const auto &detail::data<value_type, abi_type>(const simd &);
    friend auto &detail::data<value_type, abi_type>(simd &);
#endif
    alignas(traits::simd_member_alignment) member_type d;
};
Vc_MSVC_WARNING_(pop)
namespace detail
{
template <class T, class A> Vc_INTRINSIC const auto &data(const simd<T, A> &x)
{
    return x.d;
}
template <class T, class A> Vc_INTRINSIC auto &data(simd<T, A> &x) { return x.d; }
}
namespace experimental
{
namespace float_bitwise_operators
{
template <class T, class A>
Vc_INTRINSIC simd<T, A> operator|(const simd<T, A> &a, const simd<T, A> &b)
{
    return {Vc::detail::private_init, Vc::detail::get_impl_t<simd<T, A>>::bit_or(
                                          Vc::detail::data(a), Vc::detail::data(b))};
}
template <class T, class A>
Vc_INTRINSIC simd<T, A> operator&(const simd<T, A> &a, const simd<T, A> &b)
{
    return {Vc::detail::private_init, Vc::detail::get_impl_t<simd<T, A>>::bit_and(
                                          Vc::detail::data(a), Vc::detail::data(b))};
}
}
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_DETAIL_MASKEDSIMD_H_
#define VC_DETAIL_MASKEDSIMD_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
#ifdef Vc_EXPERIMENTAL
namespace detail {
template <class T> struct is_masked_simd : public std::false_type {};
template <class T, class A> class masked_simd_impl;
template <class T, class A>
struct is_masked_simd<masked_simd_impl<T, A>> : public std::true_type {
};
template <class T, class A> class masked_simd_impl {
public:
    using value_type = T;
    using abi_type = A;
    using simd_type = simd<T, A>;
    using mask_type = simd_mask<T, A>;
    masked_simd_impl(const mask_type &kk, simd<T, A> &vv) : k(kk), v(vv) {}
    masked_simd_impl &operator=(const masked_simd_impl &rhs)
    {
        Vc::detail::get_impl_t<simd_type>::masked_assign(
            Vc::detail::data(k), Vc::detail::data(v), Vc::detail::data(rhs.v));
        return *this;
    }
    template <class U>
    std::enable_if_t<!is_masked_simd<std::decay_t<U>>::value, masked_simd_impl &>
    operator=(U &&rhs)
    {
        Vc::detail::get_impl_t<simd_type>::masked_assign(
            Vc::detail::data(k), Vc::detail::data(v),
            detail::to_value_type_or_member_type<simd_type>(std::forward<U>(rhs)));
        return *this;
    }
private:
    const mask_type &k;
    simd_type &v;
};
template <class T, class A>
masked_simd_impl<T, A> masked_simd(const typename simd<T, A>::mask_type &k,
                                         simd<T, A> &v)
{
    return {k, v};
}
}
#endif
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_DETAIL_SCALAR_H_
#define VC_DETAIL_SCALAR_H_ 
#include <bitset>
#include <cmath>
#include <cstdlib>
#ifndef VC_DETAIL_SIMD_TUPLE_H_
#define VC_DETAIL_SIMD_TUPLE_H_ 
#ifndef VC_DETAIL_ABIS_H_
#define VC_DETAIL_ABIS_H_ 
#include "detail.h"
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T, class MT, class Abi, size_t N> struct gnu_traits {
    using is_valid = std::true_type;
    using simd_impl_type = typename Abi::simd_impl_type;
    using mask_impl_type = typename Abi::mask_impl_type;
    using simd_member_type = Storage<T, N>;
    using mask_member_type = Storage<MT, N>;
    static constexpr size_t simd_member_alignment = alignof(simd_member_type);
    static constexpr size_t mask_member_alignment = alignof(mask_member_type);
    struct simd_base2 {
        explicit operator detail::intrinsic_type_t<T, N>() const
        {
            return static_cast<const simd<T, Abi> *>(this)->d.v();
        }
        explicit operator detail::builtin_type_t<T, N>() const
        {
            return static_cast<const simd<T, Abi> *>(this)->d.builtin();
        }
    };
    struct simd_base1 {
        explicit operator detail::intrinsic_type_t<T, N>() const
        {
            return detail::data(*static_cast<const simd<T, Abi> *>(this));
        }
    };
    using simd_base = std::conditional_t<
        std::is_same<detail::intrinsic_type_t<T, N>, detail::builtin_type_t<T, N>>::value,
        simd_base1, simd_base2>;
    struct mask_base2 {
        explicit operator detail::intrinsic_type_t<T, N>() const
        {
            return static_cast<const simd_mask<T, Abi> *>(this)->d.v();
        }
        explicit operator detail::builtin_type_t<T, N>() const
        {
            return static_cast<const simd_mask<T, Abi> *>(this)->d.builtin();
        }
    };
    struct mask_base1 {
        explicit operator detail::intrinsic_type_t<T, N>() const
        {
            return detail::data(*static_cast<const simd_mask<T, Abi> *>(this));
        }
    };
    using mask_base = std::conditional_t<
        std::is_same<detail::intrinsic_type_t<T, N>, detail::builtin_type_t<T, N>>::value,
        mask_base1, mask_base2>;
    class mask_cast_type
    {
        using U = detail::intrinsic_type_t<T, N>;
        U d;
    public:
        mask_cast_type(U x) : d(x) {}
        operator mask_member_type() const { return d; }
    };
    class simd_cast_type1
    {
        using A = detail::intrinsic_type_t<T, N>;
        A d;
    public:
        simd_cast_type1(A a) : d(a) {}
        operator simd_member_type() const { return d; }
    };
    class simd_cast_type2
    {
        using A = detail::intrinsic_type_t<T, N>;
        using B = detail::builtin_type_t<T, N>;
        A d;
    public:
        simd_cast_type2(A a) : d(a) {}
        simd_cast_type2(B b) : d(x86::intrin_cast<A>(b)) {}
        operator simd_member_type() const { return d; }
    };
    using simd_cast_type = std::conditional_t<
        std::is_same<detail::intrinsic_type_t<T, N>, detail::builtin_type_t<T, N>>::value,
        simd_cast_type1, simd_cast_type2>;
};
#ifdef Vc_HAVE_NEON_ABI
template <class T> struct neon_is_vectorizable : detail::is_vectorizable<T> {};
template <> struct neon_is_vectorizable<long double> : std::false_type {};
#ifndef Vc_HAVE_FULL_NEON_ABI
template <> struct neon_is_vectorizable<double> : std::false_type {};
#endif
#else
template <class T> struct neon_is_vectorizable : std::false_type {};
#endif
struct neon_simd_impl;
struct neon_mask_impl;
template <int Bytes> struct neon_abi {
    template <class T> using size_tag = size_constant<Bytes / sizeof(T)>;
    struct is_valid_abi_tag : detail::bool_constant<(Bytes > 0 && Bytes <= 16)> {
    };
    template <class T>
    struct is_valid_size_for : detail::bool_constant<(Bytes % sizeof(T) == 0)> {
    };
    template <class T>
    struct is_valid
        : detail::all<is_valid_abi_tag, neon_is_vectorizable<T>, is_valid_size_for<T>> {
    };
    template <class T> static constexpr bool is_valid_v = is_valid<T>::value;
    using simd_impl_type = neon_simd_impl;
    using mask_impl_type = neon_mask_impl;
    template <class T>
    using traits =
        std::conditional_t<is_valid_v<T>, gnu_traits<T, T, neon_abi, size_tag<T>::value>,
                           detail::invalid_traits>;
};
#ifdef Vc_HAVE_FULL_SSE_ABI
template <class T> struct sse_is_vectorizable : detail::is_vectorizable<T> {};
template <> struct sse_is_vectorizable<long double> : std::false_type {};
#elif defined Vc_HAVE_SSE_ABI
template <class T> struct sse_is_vectorizable : detail::is_same<T, float> {};
#else
template <class T> struct sse_is_vectorizable : std::false_type {};
#endif
struct sse_mask_impl;
struct sse_simd_impl;
template <int Bytes> struct sse_abi {
    template <class T> using size_tag = size_constant<Bytes / sizeof(T)>;
    struct is_valid_abi_tag : detail::bool_constant<(Bytes > 0 && Bytes <= 16)> {
    };
    template <class T>
    struct is_valid_size_for : detail::bool_constant<(Bytes % sizeof(T) == 0)> {
    };
    template <class T>
    struct is_valid
        : detail::all<is_valid_abi_tag, sse_is_vectorizable<T>, is_valid_size_for<T>> {
    };
    template <class T> static constexpr bool is_valid_v = is_valid<T>::value;
    using simd_impl_type = sse_simd_impl;
    using mask_impl_type = sse_mask_impl;
    template <class T>
    using traits = std::conditional_t<is_valid_v<T>,
                                      gnu_traits<T, T, sse_abi, Bytes / sizeof(T)>,
                                      detail::invalid_traits>;
};
#ifdef Vc_HAVE_FULL_AVX_ABI
template <class T> struct avx_is_vectorizable : detail::is_vectorizable<T> {};
#elif defined Vc_HAVE_AVX_ABI
template <class T> struct avx_is_vectorizable : std::is_floating_point<T> {};
#else
template <class T> struct avx_is_vectorizable : std::false_type {};
#endif
template <> struct avx_is_vectorizable<long double> : std::false_type {};
struct avx_mask_impl;
struct avx_simd_impl;
template <int Bytes> struct avx_abi {
    template <class T> using size_tag = size_constant<Bytes / sizeof(T)>;
    struct is_valid_abi_tag : detail::bool_constant<(Bytes > 0 && Bytes <= 32)> {
    };
    template <class T>
    struct is_valid_size_for : detail::bool_constant<(Bytes % sizeof(T) == 0)> {
    };
    template <class T>
    struct is_valid
        : detail::all<is_valid_abi_tag, avx_is_vectorizable<T>, is_valid_size_for<T>> {
    };
    template <class T> static constexpr bool is_valid_v = is_valid<T>::value;
    using simd_impl_type = avx_simd_impl;
    using mask_impl_type = avx_mask_impl;
    template <class T>
    using traits = std::conditional_t<is_valid_v<T>,
                                      gnu_traits<T, T, avx_abi, Bytes / sizeof(T)>,
                                      detail::invalid_traits>;
};
#ifdef Vc_HAVE_AVX512_ABI
template <class T> struct avx512_is_vectorizable : detail::is_vectorizable<T> {};
template <> struct avx512_is_vectorizable<long double> : std::false_type {};
#ifndef Vc_HAVE_FULL_AVX512_ABI
template <> struct avx512_is_vectorizable< char> : std::false_type {};
template <> struct avx512_is_vectorizable< uchar> : std::false_type {};
template <> struct avx512_is_vectorizable< schar> : std::false_type {};
template <> struct avx512_is_vectorizable< short> : std::false_type {};
template <> struct avx512_is_vectorizable<ushort> : std::false_type {};
template <> struct avx512_is_vectorizable<char16_t> : std::false_type {};
template <> struct avx512_is_vectorizable<wchar_t> : detail::bool_constant<sizeof(wchar_t) == 2> {};
#endif
#else
template <class T> struct avx512_is_vectorizable : std::false_type {};
#endif
struct avx512_mask_impl;
struct avx512_simd_impl;
template <int Bytes> struct avx512_abi {
    template <class T> using size_tag = size_constant<Bytes / sizeof(T)>;
    struct is_valid_abi_tag : detail::bool_constant<(Bytes > 0 && Bytes <= 64)> {
    };
    template <class T>
    struct is_valid_size_for : detail::bool_constant<(Bytes % sizeof(T) == 0)> {
    };
    template <class T>
    struct is_valid
        : detail::all<is_valid_abi_tag, avx512_is_vectorizable<T>, is_valid_size_for<T>> {
    };
    template <class T> static constexpr bool is_valid_v = is_valid<T>::value;
    using simd_impl_type = avx512_simd_impl;
    using mask_impl_type = avx512_mask_impl;
    template <class T>
    using traits = std::conditional_t<is_valid_v<T>,
                                      gnu_traits<T, bool, avx512_abi, Bytes / sizeof(T)>,
                                      detail::invalid_traits>;
};
struct scalar_simd_impl;
struct scalar_mask_impl;
struct scalar_abi {
    template <class T> using size_tag = size_constant<1>;
    struct is_valid_abi_tag : std::true_type {};
    template <class T> struct is_valid_size_for : std::true_type {};
    template <class T> struct is_valid : is_vectorizable<T> {};
    template <class T> static constexpr bool is_valid_v = is_valid<T>::value;
    using simd_impl_type = scalar_simd_impl;
    using mask_impl_type = scalar_mask_impl;
    template <class T, bool = is_valid_v<T>> struct traits : detail::invalid_traits {
    };
    template <class T> struct traits<T, true> {
        using is_valid = std::true_type;
        using simd_impl_type = scalar_simd_impl;
        using mask_impl_type = scalar_mask_impl;
        using simd_member_type = T;
        using mask_member_type = bool;
        static constexpr size_t simd_member_alignment = alignof(simd_member_type);
        static constexpr size_t mask_member_alignment = alignof(mask_member_type);
        struct simd_cast_type {
            simd_cast_type() = delete;
        };
        struct mask_cast_type {
            mask_cast_type() = delete;
        };
        struct simd_base {};
        struct mask_base {};
    };
};
template <int N> struct fixed_size_simd_impl;
template <int N> struct fixed_size_mask_impl;
template <int N> struct fixed_abi {
    template <class T> using size_tag = size_constant<N>;
    struct is_valid_abi_tag
        : public detail::bool_constant<(N > 0)> {
    };
    template <class T>
    struct is_valid_size_for
        : detail::bool_constant<((N <= simd_abi::max_fixed_size<T>) ||
                                 (simd_abi::Neon::is_valid_v<char> &&
                                  N == simd_size_v<char, simd_abi::Neon>) ||
                                 (simd_abi::Sse::is_valid_v<char> &&
                                  N == simd_size_v<char, simd_abi::Sse>) ||
                                 (simd_abi::Avx::is_valid_v<char> &&
                                  N == simd_size_v<char, simd_abi::Avx>) ||
                                 (simd_abi::Avx512::is_valid_v<char> &&
                                  N == simd_size_v<char, simd_abi::Avx512>))> {
    };
    template <class T>
    struct is_valid
        : detail::all<is_valid_abi_tag, is_vectorizable<T>, is_valid_size_for<T>> {
    };
    template <class T> static constexpr bool is_valid_v = is_valid<T>::value;
    using simd_impl_type = fixed_size_simd_impl<N>;
    using mask_impl_type = fixed_size_mask_impl<N>;
    template <class T, bool = is_valid_v<T>> struct traits : detail::invalid_traits {
    };
    template <class T> struct traits<T, true> {
        using is_valid = std::true_type;
        using simd_impl_type = fixed_size_simd_impl<N>;
        using mask_impl_type = fixed_size_mask_impl<N>;
        using simd_member_type = fixed_size_storage<T, N>;
        using mask_member_type = std::bitset<N>;
        static constexpr size_t simd_member_alignment =
#ifdef Vc_GCC
            std::min(size_t(
#ifdef __AVX__
                         256
#else
                         128
#endif
                         ),
#else
            (
#endif
                     next_power_of_2(N * sizeof(T)));
        static constexpr size_t mask_member_alignment = alignof(mask_member_type);
        struct simd_base {
            simd_base(const simd_base &) {}
            simd_base() = default;
            explicit operator const simd_member_type &() const
            {
                return static_cast<const simd<T, fixed_abi> *>(this)->d;
            }
            explicit operator std::array<T, N>() const
            {
                std::array<T, N> r;
                static_assert(sizeof(r) <= sizeof(simd_member_type), "");
                std::memcpy(r.data(), &static_cast<const simd_member_type &>(*this),
                            sizeof(r));
                return r;
            }
        };
        struct mask_base {};
        struct simd_cast_type {
            simd_cast_type(const std::array<T, N> &);
            simd_cast_type(const simd_member_type &dd) : d(dd) {}
            explicit operator const simd_member_type &() const { return d; }
        private:
            const simd_member_type &d;
        };
        class mask_cast_type
        {
            mask_cast_type() = delete;
        };
    };
};
template <class T, class Abi>
struct traits<T, Abi, void_t<typename Abi::template is_valid<T>>>
    : Abi::template traits<T> {
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_DETAIL_DEBUG_H_
#define VC_DETAIL_DEBUG_H_ 
#include <iostream>
#include <iomanip>
#include <sstream>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
#ifdef Vc_MSVC
#define Vc_PRETTY_FUNCTION __FUNCSIG__
#else
#define Vc_PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif
enum class area : unsigned {
    _disabled = 0,
    _enabled = 1,
    _ = _enabled,
#ifdef Vc_DEBUG
#define Vc_ENABLE_DEBUG 1
#define sine 0x0000000000000001ull
#define cosine 0x0000000000000002ull
#define simd_tuple 0x0000000000000004ull
#define simd_view 0x0000000000000008ull
#define logarithm 0x0000000000000010ull
    _sine = ((Vc_DEBUG) & sine) ? _enabled : _disabled,
    _cosine = ((Vc_DEBUG) & cosine) ? _enabled : _disabled,
    _simd_tuple = ((Vc_DEBUG) & simd_tuple) ? _enabled : _disabled,
    _simd_view = ((Vc_DEBUG) & simd_view ) ? _enabled : _disabled,
    _logarithm = ((Vc_DEBUG) & logarithm ) ? _enabled : _disabled,
#undef sine
#undef cosine
#undef simd_tuple
#undef simd_view
#undef logarithm
#undef Vc_DEBUG
#else
    _sine = _disabled,
    _cosine = _disabled,
    _simd_tuple = _disabled,
    _simd_view = _disabled,
    _logarithm = _disabled,
#endif
};
#define Vc_DEBUG(area_) \
    Vc::detail::debug_stream<Vc::detail::area::_##area_>(Vc_PRETTY_FUNCTION, __FILE__, \
                                                         __LINE__, Vc::detail::debug_instr_ptr())
#define Vc_PRETTY_PRINT(var_) std::setw(16), #var_ " = ", (var_)
#ifdef Vc_ENABLE_DEBUG
#define Vc_DEBUG_DEFERRED(area_,...) \
    const auto &Vc_CONCAT(Vc_deferred_, __LINE__, _) = \
        detail::defer([&]() { Vc_DEBUG(area_)(__VA_ARGS__); });
#else
#define Vc_DEBUG_DEFERRED(area_,...) 
#endif
Vc_ALWAYS_INLINE void *debug_instr_ptr()
{
    void *ip;
#ifdef __GNUC__
#ifdef __x86_64__
    asm volatile("lea 0(%%rip),%0" : "=r"(ip));
#elif defined __i386__
    asm volatile("1: movl $1b,%0" : "=r"(ip));
#elif defined __arm__
    asm volatile("mov %0,pc" : "=r"(ip));
#else
    ip = nullptr;
#endif
#else
    ip = nullptr;
#endif
    return ip;
}
template <area> class debug_stream;
template <> class debug_stream<area::_enabled>
{
    std::stringstream buffer;
    int color = 31;
public:
    debug_stream(const char *func, const char *file, int line, void *instr_ptr)
    {
        buffer << "\033[1;40;" << color << "mDEBUG: " << file << ':' << line << " @ "
               << instr_ptr << "\n       " << func;
    }
    ~debug_stream()
    {
        buffer << "\033[0m\n";
        std::cout << buffer.str() << std::flush;
    }
    template <class... Ts> debug_stream &operator()(const Ts &... args)
    {
        color = color > 37 ? 30 : color + 1;
        buffer << "\n\033[1;40;" << color << "m       ";
#if 0
        buffer << ... << std::forward<Ts>(args);
#else
        [](const std::initializer_list<int> &) {}({(print(args, int()), 0)...});
#endif
        return *this;
    }
private:
    template <class T, class = decltype(buffer << std::declval<const T &>())>
    void print(const T &x, int)
    {
        buffer << x;
    }
    static char hexChar(char x) { return x + (x > 9 ? 87 : 48); }
    template <class T> void print(const T &x, float)
    {
        using Bytes = char[sizeof(T)];
        auto &&bytes = reinterpret_cast<const Bytes &>(x);
        int i = -1;
        for (const unsigned char b : bytes) {
            if (++i && (i & 0x3) == 0) {
                buffer.put('\'');
            }
            buffer.put(hexChar(b >> 4));
            buffer.put(hexChar(b & 0xf));
        }
    }
};
template <> class debug_stream<area::_disabled>
{
public:
    debug_stream(const char *, const char *, int, void *) {}
    template <class... Ts> const debug_stream &operator()(Ts &&...) const { return *this; }
};
template <typename F> class defer_raii
{
public:
    template <typename FF> defer_raii(FF &&f) : cleanup_function(std::forward<FF>(f)) {}
    ~defer_raii() { cleanup_function(); }
private:
    F cleanup_function;
};
template <typename F> detail::defer_raii<F> defer(F && f) { return {std::forward<F>(f)}; }
}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class T> T subscript_read(arithmetic<T> x, size_t) noexcept { return x; }
template <class T>
void subscript_write(arithmetic<T> &x, size_t, detail::id<T> y) noexcept
{
    x = y;
}
template <class T> typename T::value_type subscript_read(const T &x, size_t i) noexcept
{
    return x[i];
}
template <class T> void subscript_write(T &x, size_t i, typename T::value_type y) noexcept
{
    return x.set(i, y);
}
template <class T, class... Abis> struct simd_tuple;
template <size_t I, class T> struct tuple_element;
template <class T, class A0, class... As>
struct tuple_element<0, simd_tuple<T, A0, As...>> {
    using type = Vc::simd<T, A0>;
};
template <size_t I, class T, class A0, class... As>
struct tuple_element<I, simd_tuple<T, A0, As...>> {
    using type = typename tuple_element<I - 1, simd_tuple<T, As...>>::type;
};
template <size_t I, class T> using tuple_element_t = typename tuple_element<I, T>::type;
template <class T, class... A1s>
Vc_INTRINSIC simd_tuple<T, A1s...> tuple_concat(const simd_tuple<T>,
                                                const simd_tuple<T, A1s...> right)
{
    return right;
}
template <class T, class A00, class... A0s, class A10, class... A1s>
Vc_INTRINSIC simd_tuple<T, A00, A0s..., A10, A1s...> tuple_concat(
    const simd_tuple<T, A00, A0s...> left, const simd_tuple<T, A10, A1s...> right)
{
    return {left.first, tuple_concat(left.second, right)};
}
template <class T, class A00, class... A0s>
Vc_INTRINSIC simd_tuple<T, A00, A0s...> tuple_concat(
    const simd_tuple<T, A00, A0s...> left, const simd_tuple<T>)
{
    return left;
}
template <class T, class A10, class... A1s>
Vc_INTRINSIC simd_tuple<T, simd_abi::scalar, A10, A1s...> tuple_concat(
    const T left, const simd_tuple<T, A10, A1s...> right)
{
    return {left, right};
}
template <class T> Vc_INTRINSIC const T &tuple_pop_front(size_constant<0>, const T &x)
{
    return x;
}
template <class T> Vc_INTRINSIC T &tuple_pop_front(size_constant<0>, T &x) { return x; }
template <size_t K, class T>
Vc_INTRINSIC const auto &tuple_pop_front(size_constant<K>, const T &x)
{
    return tuple_pop_front(size_constant<K - 1>(), x.second);
}
template <size_t K, class T> Vc_INTRINSIC auto &tuple_pop_front(size_constant<K>, T &x)
{
    return tuple_pop_front(size_constant<K - 1>(), x.second);
}
namespace simd_tuple_impl
{
namespace as_simd
{
struct yes {};
struct no {};
}
template <class T, class A0, class... Abis>
simd<T, A0> get_impl(as_simd::yes, const simd_tuple<T, A0, Abis...> &t, size_constant<0>)
{
    return {private_init, t.first};
}
template <class T, class A0, class... Abis>
const auto &get_impl(as_simd::no, const simd_tuple<T, A0, Abis...> &t, size_constant<0>)
{
    return t.first;
}
template <class T, class A0, class... Abis>
auto &get_impl(as_simd::no, simd_tuple<T, A0, Abis...> &t, size_constant<0>)
{
    return t.first;
}
template <class R, size_t N, class T, class... Abis>
auto get_impl(R, const simd_tuple<T, Abis...> &t, size_constant<N>)
{
    return get_impl(R(), t.second, size_constant<N - 1>());
}
template <size_t N, class T, class... Abis>
auto &get_impl(as_simd::no, simd_tuple<T, Abis...> &t, size_constant<N>)
{
    return get_impl(as_simd::no(), t.second, size_constant<N - 1>());
}
}
template <size_t N, class T, class... Abis> auto get_simd(const simd_tuple<T, Abis...> &t)
{
    return simd_tuple_impl::get_impl(simd_tuple_impl::as_simd::yes(), t,
                                     size_constant<N>());
}
template <size_t N, class T, class... Abis> auto get(const simd_tuple<T, Abis...> &t)
{
    return simd_tuple_impl::get_impl(simd_tuple_impl::as_simd::no(), t,
                                     size_constant<N>());
}
template <size_t N, class T, class... Abis> auto &get(simd_tuple<T, Abis...> &t)
{
    return simd_tuple_impl::get_impl(simd_tuple_impl::as_simd::no(), t,
                                     size_constant<N>());
}
template <size_t LeftN, class RightT> struct foo;
template <class RightT> struct foo<0, RightT> : public size_constant<0> {
};
template <size_t LeftN, class RightT>
struct foo
    : public size_constant<
          1 + foo<LeftN - RightT::first_size_v, typename RightT::second_type>::value> {
};
template <size_t LeftN, class RightT, bool = (RightT::first_size_v < LeftN)>
struct how_many_to_extract;
template <size_t LeftN, class RightT> struct how_many_to_extract<LeftN, RightT, true> {
    static constexpr std::make_index_sequence<
        1 + foo<LeftN - RightT::first_size_v, typename RightT::second_type>::value>
    tag()
    {
        return {};
    }
};
template <class T, size_t Offset, size_t Length, bool Done, class IndexSeq>
struct chunked {
};
template <size_t LeftN, class RightT> struct how_many_to_extract<LeftN, RightT, false> {
    static_assert(LeftN != RightT::first_size_v, "");
    static constexpr chunked<typename RightT::first_type, 0, LeftN, false,
                             std::make_index_sequence<LeftN>>
    tag()
    {
        return {};
    }
};
template <class T, class Abi, size_t Offset>
struct tuple_element_meta : public Abi::simd_impl_type {
    using value_type = T;
    using abi_type = Abi;
    using traits = detail::traits<T, Abi>;
    using maskimpl = typename traits::mask_impl_type;
    using member_type = typename traits::simd_member_type;
    using mask_member_type = typename traits::mask_member_type;
    using simd_type = Vc::simd<T, Abi>;
    static constexpr size_t offset = Offset;
    static constexpr size_t size() { return simd_size<T, Abi>::value; }
    static constexpr size_constant<simd_size<T, Abi>::value> size_tag = {};
    static constexpr maskimpl simd_mask = {};
    template <size_t N>
    static Vc_INTRINSIC mask_member_type make_mask(std::bitset<N> bits)
    {
        constexpr T *type_tag = nullptr;
        return maskimpl::from_bitset(std::bitset<size()>((bits >> Offset).to_ullong()),
                                     type_tag);
    }
    static Vc_INTRINSIC ullong mask_to_shifted_ullong(mask_member_type k)
    {
        return maskimpl::to_bitset(k).to_ullong() << Offset;
    }
};
template <size_t Offset, class T, class Abi, class... As>
tuple_element_meta<T, Abi, Offset> make_meta(const simd_tuple<T, Abi, As...> &)
{
    return {};
}
template <class T> struct simd_tuple<T> {
    using value_type = T;
    static constexpr size_t tuple_size = 0;
    static constexpr size_t size() { return 0; }
    static constexpr size_t size_v = 0;
};
template <class T, class Abi0> struct simd_tuple<T, Abi0> {
    using value_type = T;
    using first_type = typename detail::traits<T, Abi0>::simd_member_type;
    using second_type = simd_tuple<T>;
    using first_abi = Abi0;
    static constexpr size_t tuple_size = 1;
    static constexpr size_t size() { return simd_size_v<T, Abi0>; }
    static constexpr size_t size_v = simd_size_v<T, Abi0>;
    static constexpr size_t first_size_v = simd_size_v<T, Abi0>;
    first_type first;
    static constexpr second_type second = {};
    template <size_t Offset = 0, class F>
    static Vc_INTRINSIC simd_tuple generate(F &&gen, detail::size_constant<Offset> = {})
    {
        return {gen(tuple_element_meta<T, Abi0, Offset>())};
    }
    template <size_t Offset = 0, class F, class... More>
    Vc_INTRINSIC simd_tuple apply_wrapped(F &&fun, const More &... more) const
    {
        Vc_DEBUG(simd_tuple);
        return {fun(make_meta<Offset>(*this), first, more.first...)};
    }
    template <class F, class... More>
    friend Vc_INTRINSIC simd_tuple apply(F &&fun, const simd_tuple &x, More &&... more)
    {
        Vc_DEBUG(simd_tuple);
        return simd_tuple::apply_impl(
            bool_constant<all<is_equal<size_t, first_size_v,
                                       std::decay_t<More>::first_size_v>...>::value>(),
            std::forward<F>(fun), x, std::forward<More>(more)...);
    }
private:
    template <class F, class... More>
    static Vc_INTRINSIC simd_tuple
    apply_impl(true_type,
               F &&fun, const simd_tuple &x, More &&... more)
    {
        Vc_DEBUG(simd_tuple);
        return {fun(tuple_element_meta<T, Abi0, 0>(), x.first, more.first...)};
    }
    template <class F, class More>
    static Vc_INTRINSIC simd_tuple apply_impl(false_type,
                                              F &&fun, const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        return apply_impl(std::make_index_sequence<std::decay_t<More>::tuple_size>(),
                          std::forward<F>(fun), x, std::forward<More>(y));
    }
    template <class F, class More, size_t... Indexes>
    static Vc_INTRINSIC simd_tuple apply_impl(std::index_sequence<Indexes...>, F &&fun,
                                              const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        auto tmp = Vc::concat(detail::get_simd<Indexes>(y)...);
        const auto first = fun(tuple_element_meta<T, Abi0, 0>(), x.first, tmp);
#ifdef __cpp_if_constexpr
        if constexpr (std::is_lvalue_reference<More>::value && !std::is_const<More>::value) {
#endif
            const auto tup =
                Vc::split<tuple_element_t<Indexes, std::decay_t<More>>::size()...>(tmp);
            auto &&ignore = {
                (get<Indexes>(y) = detail::data(std::get<Indexes>(tup)), 0)...};
            detail::unused(ignore);
#ifdef __cpp_if_constexpr
        }
#endif
        return {first};
    }
public:
    template <class Tuple, size_t Offset, class F2>
    static Vc_INTRINSIC simd_tuple extract(
        size_constant<Offset>, size_constant<std::decay_t<Tuple>::first_size_v - Offset>,
        Tuple &&tup, F2 &&fun2)
    {
        static_assert(Offset > 0, "");
        auto splitted =
            split<Offset, std::decay_t<Tuple>::first_size_v - Offset>(get_simd<0>(tup));
        simd_tuple r = fun2(detail::data(std::get<1>(splitted)));
        tup.first = detail::data(concat(std::get<0>(splitted), std::get<1>(splitted)));
        return r;
    }
    template <class F, class More, class U, size_t Length, size_t... Indexes>
    static Vc_INTRINSIC simd_tuple
    apply_impl2(chunked<U, std::decay_t<More>::first_size_v, Length, true,
                        std::index_sequence<Indexes...>>,
                F &&fun, const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        return apply(std::forward<F>(fun), x, y.second);
    }
    template <class F, class More, class U, size_t Offset, size_t Length,
              size_t... Indexes>
    static Vc_INTRINSIC simd_tuple
    apply_impl2(chunked<U, Offset, Length, false, std::index_sequence<Indexes...>>,
                F &&fun, const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        static_assert(Offset < std::decay_t<More>::first_size_v, "");
        static_assert(Offset > 0, "");
        return extract(size_constant<Offset>(), size_constant<Length>(), y,
                       [&](auto &&yy) -> simd_tuple {
                           return {fun(tuple_element_meta<T, Abi0, 0>(), x.first, yy)};
                       });
    }
    template <class R = T, class F, class... More>
    Vc_INTRINSIC fixed_size_storage<R, size_v> apply_r(F &&fun,
                                                       const More &... more) const
    {
        Vc_DEBUG(simd_tuple);
        return {fun(tuple_element_meta<T, Abi0, 0>(), first, more.first...)};
    }
    template <class F, class... More>
    friend Vc_INTRINSIC std::bitset<size_v> test(F &&fun, const simd_tuple &x,
                                                 const More &... more)
    {
        return Abi0::mask_impl_type::to_bitset(
            fun(tuple_element_meta<T, Abi0, 0>(), x.first, more.first...));
    }
    T operator[](size_t i) const noexcept { return subscript_read(first, i); }
    void set(size_t i, T val) noexcept { subscript_write(first, i, val); }
};
template <class T, class Abi0, class... Abis> struct simd_tuple<T, Abi0, Abis...> {
    using value_type = T;
    using first_type = typename detail::traits<T, Abi0>::simd_member_type;
    using first_abi = Abi0;
    using second_type = simd_tuple<T, Abis...>;
    static constexpr size_t tuple_size = sizeof...(Abis) + 1;
    static constexpr size_t size() { return simd_size_v<T, Abi0> + second_type::size(); }
    static constexpr size_t size_v = simd_size_v<T, Abi0> + second_type::size();
    static constexpr size_t first_size_v = simd_size_v<T, Abi0>;
    first_type first;
    second_type second;
    template <size_t Offset = 0, class F>
    static Vc_INTRINSIC simd_tuple generate(F &&gen, detail::size_constant<Offset> = {})
    {
        return {gen(tuple_element_meta<T, Abi0, Offset>()),
                second_type::generate(
                    std::forward<F>(gen),
                    detail::size_constant<Offset + simd_size_v<T, Abi0>>())};
    }
    template <size_t Offset = 0, class F, class... More>
    Vc_INTRINSIC simd_tuple apply_wrapped(F &&fun, const More &... more) const
    {
        Vc_DEBUG(simd_tuple);
        return {fun(make_meta<Offset>(*this), first, more.first...),
                second.template apply_wrapped<Offset + simd_size_v<T, Abi0>>(
                    std::forward<F>(fun), more.second...)};
    }
    template <class F, class... More>
    friend Vc_INTRINSIC simd_tuple apply(F &&fun, const simd_tuple &x, More &&... more)
    {
        Vc_DEBUG(simd_tuple);
        return simd_tuple::apply_impl(
            bool_constant<all<is_equal<size_t, first_size_v,
                                       std::decay_t<More>::first_size_v>...>::value>(),
            std::forward<F>(fun), x, std::forward<More>(more)...);
    }
private:
    template <class F, class... More>
    static Vc_INTRINSIC simd_tuple
    apply_impl(true_type,
               F &&fun, const simd_tuple &x, More &&... more)
    {
        Vc_DEBUG(simd_tuple);
        return {fun(tuple_element_meta<T, Abi0, 0>(), x.first, more.first...),
                apply(std::forward<F>(fun), x.second, more.second...)};
    }
    template <class F, class More>
    static Vc_INTRINSIC simd_tuple
    apply_impl(false_type,
               F &&fun, const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        return apply_impl2(how_many_to_extract<first_size_v, std::decay_t<More>>::tag(),
                           std::forward<F>(fun), x, y);
    }
    template <class F, class More, size_t... Indexes>
    static Vc_INTRINSIC simd_tuple apply_impl2(std::index_sequence<Indexes...>, F &&fun,
                                               const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        auto tmp = Vc::concat(detail::get_simd<Indexes>(y)...);
        const auto first = fun(tuple_element_meta<T, Abi0, 0>(), x.first, tmp);
#ifdef __cpp_if_constexpr
        if constexpr (std::is_lvalue_reference<More>::value && !std::is_const<More>::value) {
#endif
            const auto tup =
                Vc::split<tuple_element_t<Indexes, std::decay_t<More>>::size()...>(tmp);
            [](std::initializer_list<int>) {
            }({(get<Indexes>(y) = detail::data(std::get<Indexes>(tup)), 0)...});
#ifdef __cpp_if_constexpr
        }
#endif
        return {first, apply(std::forward<F>(fun), x.second,
                             tuple_pop_front(size_constant<sizeof...(Indexes)>(), y))};
    }
public:
    template <class F, class More, class U, size_t Length, size_t... Indexes>
    static Vc_INTRINSIC simd_tuple
    apply_impl2(chunked<U, std::decay_t<More>::first_size_v, Length, true,
                        std::index_sequence<Indexes...>>,
                F &&fun, const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        return apply(std::forward<F>(fun), x, y.second);
    }
    template <class Tuple, size_t Length, class F2>
    static Vc_INTRINSIC auto extract(size_constant<0>, size_constant<Length>, Tuple &&tup,
                                     F2 &&fun2)
    {
        auto splitted =
            split<Length, std::decay_t<Tuple>::first_size_v - Length>(get_simd<0>(tup));
        auto r = fun2(detail::data(std::get<0>(splitted)));
        tup.first = detail::data(concat(std::get<0>(splitted), std::get<1>(splitted)));
        return r;
    }
    template <class Tuple, size_t Offset, class F2>
    static Vc_INTRINSIC auto extract(
        size_constant<Offset>, size_constant<std::decay_t<Tuple>::first_size_v - Offset>,
        Tuple &&tup, F2 &&fun2)
    {
        auto splitted =
            split<Offset, std::decay_t<Tuple>::first_size_v - Offset>(get_simd<0>(tup));
        auto r = fun2(detail::data(std::get<1>(splitted)));
        tup.first = detail::data(concat(std::get<0>(splitted), std::get<1>(splitted)));
        return r;
    }
    template <
        class Tuple, size_t Offset, size_t Length, class F2,
        class = std::enable_if_t<(Offset + Length < std::decay_t<Tuple>::first_size_v)>>
    static Vc_INTRINSIC auto extract(size_constant<Offset>, size_constant<Length>,
                                     Tuple &&tup, F2 &&fun2)
    {
        static_assert(Offset + Length < std::decay_t<Tuple>::first_size_v, "");
        auto splitted =
            split<Offset, Length, std::decay_t<Tuple>::first_size_v - Offset - Length>(
                get_simd<0>(tup));
        auto r = fun2(detail::data(std::get<1>(splitted)));
        tup.first = detail::data(
            concat(std::get<0>(splitted), std::get<1>(splitted), std::get<2>(splitted)));
        return r;
    }
    template <class F, class More, class U, size_t Offset, size_t Length,
              size_t... Indexes>
    static Vc_INTRINSIC simd_tuple
    apply_impl2(chunked<U, Offset, Length, false, std::index_sequence<Indexes...>>,
                F &&fun, const simd_tuple &x, More &&y)
    {
        Vc_DEBUG(simd_tuple);
        static_assert(Offset < std::decay_t<More>::first_size_v, "");
        return {extract(size_constant<Offset>(), size_constant<Length>(), y,
                        [&](auto &&yy) {
                            return fun(tuple_element_meta<T, Abi0, 0>(), x.first, yy);
                        }),
                second_type::apply_impl2(
                    chunked<U, Offset + Length, Length,
                            Offset + Length == std::decay_t<More>::first_size_v,
                            std::index_sequence<Indexes...>>(),
                    std::forward<F>(fun), x.second, y)};
    }
    template <class R = T, class F, class... More>
    Vc_INTRINSIC auto apply_r(F &&fun, const More &... more) const
    {
        Vc_DEBUG(simd_tuple);
        return detail::tuple_concat<R>(
            fun(tuple_element_meta<T, Abi0, 0>(), first, more.first...),
            second.template apply_r<R>(std::forward<F>(fun), more.second...));
    }
    template <class F, class... More>
    friend Vc_INTRINSIC std::bitset<size_v> test(F &&fun, const simd_tuple &x,
                                                 const More &... more)
    {
        return Abi0::mask_impl_type::to_bitset(
                   fun(tuple_element_meta<T, Abi0, 0>(), x.first, more.first...))
                   .to_ullong() |
               (test(fun, x.second, more.second...).to_ullong() << simd_size_v<T, Abi0>);
    }
    T operator[](size_t i) const noexcept
    {
#ifdef __GNUC__
        return reinterpret_cast<const may_alias<T> *>(this)[i];
#else
        return i < simd_size_v<T, Abi0> ? subscript_read(first, i)
                                        : second[i - simd_size_v<T, Abi0>];
#endif
    }
    void set(size_t i, T val) noexcept
    {
#ifdef __GNUC__
        reinterpret_cast<may_alias<T> *>(this)[i] = val;
#else
        if (i < simd_size_v<T, Abi0>) {
            subscript_write(first, i, val);
        } else {
            second.set(i - simd_size_v<T, Abi0>, val);
        }
#endif
    }
};
template <class T, class A0>
Vc_INTRINSIC simd_tuple<T, A0> make_tuple(Vc::simd<T, A0> x0)
{
    return {detail::data(x0)};
}
template <class T, class A0, class... As>
Vc_INTRINSIC simd_tuple<T, A0, As...> make_tuple(const Vc::simd<T, A0> &x0,
                                                    const Vc::simd<T, As> &... xs)
{
    return {detail::data(x0), make_tuple(xs...)};
}
template <class T, class A0>
Vc_INTRINSIC simd_tuple<T, A0> make_tuple(
    const typename detail::traits<T, A0>::simd_member_type &arg0)
{
    return {arg0};
}
template <class T, class A0, class A1, class... Abis>
Vc_INTRINSIC simd_tuple<T, A0, A1, Abis...> make_tuple(
    const typename detail::traits<T, A0>::simd_member_type &arg0,
    const typename detail::traits<T, A1>::simd_member_type &arg1,
    const typename detail::traits<T, Abis>::simd_member_type &... args)
{
    return {arg0, make_tuple<T, A1, Abis...>(arg1, args...)};
}
template <size_t, class T> using to_tuple_helper = T;
template <class T, class A0, size_t... Indexes>
Vc_INTRINSIC simd_tuple<T, to_tuple_helper<Indexes, A0>...> to_tuple_impl(
    std::index_sequence<Indexes...>,
    const std::array<typename detail::traits<T, A0>::simd_member_type, sizeof...(Indexes)>
        &args)
{
    return make_tuple<T, to_tuple_helper<Indexes, A0>...>(args[Indexes]...);
}
template <class T, class A0, size_t N>
Vc_INTRINSIC auto to_tuple(
    const std::array<typename detail::traits<T, A0>::simd_member_type, N> &args)
{
    return to_tuple_impl<T, A0>(std::make_index_sequence<N>(), args);
}
template <class T> Vc_INTRINSIC simd_tuple<T> optimize_tuple(const simd_tuple<T>)
{
    return {};
}
template <class T, class A>
Vc_INTRINSIC const simd_tuple<T, A> &optimize_tuple(const simd_tuple<T, A> &x)
{
    return x;
}
template <class T, class A0, class A1, class... Abis,
          class R = fixed_size_storage<T, simd_tuple<T, A0, A1, Abis...>::size_v>>
Vc_INTRINSIC R optimize_tuple(const simd_tuple<T, A0, A1, Abis...> &x)
{
    using Tup = simd_tuple<T, A0, A1, Abis...>;
    Vc_CONSTEXPR_IF_RETURNING(R::first_size_v == simd_size_v<T, A0>) {
        return tuple_concat(simd_tuple<T, typename R::first_abi>{x.first},
                            optimize_tuple(x.second));
    } Vc_CONSTEXPR_ELSE_IF(R::first_size_v == simd_size_v<T, A0> + simd_size_v<T, A1>) {
        return tuple_concat(simd_tuple<T, typename R::first_abi>{detail::data(
                                Vc::concat(get_simd<0>(x), get_simd<1>(x)))},
                            optimize_tuple(x.second.second));
    } Vc_CONSTEXPR_ELSE_IF(sizeof...(Abis) >= 2) {
        Vc_CONSTEXPR_IF_RETURNING(
            R::first_size_v ==
            tuple_element_t<0, Tup>::size() + tuple_element_t<1, Tup>::size() +
                tuple_element_t<2, Tup>::size() + tuple_element_t<3, Tup>::size()) {
            return tuple_concat(
                simd_tuple<T, typename R::first_abi>{detail::data(concat(
                    get_simd<0>(x), get_simd<1>(x), get_simd<2>(x), get_simd<3>(x)))},
                optimize_tuple(x.second.second.second.second));
        } Vc_CONSTEXPR_ENDIF
    } Vc_CONSTEXPR_ELSE {
        return x;
    } Vc_CONSTEXPR_ENDIF
}
template <size_t I, class T> struct number_of_preceding_elements;
template <class T, class A0, class... As>
struct number_of_preceding_elements<0, simd_tuple<T, A0, As...>>
    : public size_constant<0> {
};
template <size_t I, class T, class A0, class... As>
struct number_of_preceding_elements<I, simd_tuple<T, A0, As...>>
    : public std::integral_constant<
          size_t,
          simd<T, A0>::size() +
              number_of_preceding_elements<I - 1, simd_tuple<T, As...>>::value> {
};
template <size_t Offset = 0, class T, class A0, class F>
Vc_INTRINSIC void for_each(const simd_tuple<T, A0> &t_, F &&fun_)
{
    std::forward<F>(fun_)(make_meta<Offset>(t_), t_.first);
}
template <size_t Offset = 0, class T, class A0, class A1, class... As, class F>
Vc_INTRINSIC void for_each(const simd_tuple<T, A0, A1, As...> &t_, F &&fun_)
{
    fun_(make_meta<Offset>(t_), t_.first);
    for_each<Offset + simd_size<T, A0>::value>(t_.second, std::forward<F>(fun_));
}
template <size_t Offset = 0, class T, class A0, class F>
Vc_INTRINSIC void for_each(simd_tuple<T, A0> &t_, F &&fun_)
{
    std::forward<F>(fun_)(make_meta<Offset>(t_), t_.first);
}
template <size_t Offset = 0, class T, class A0, class A1, class... As, class F>
Vc_INTRINSIC void for_each(simd_tuple<T, A0, A1, As...> &t_, F &&fun_)
{
    fun_(make_meta<Offset>(t_), t_.first);
    for_each<Offset + simd_size<T, A0>::value>(t_.second, std::forward<F>(fun_));
}
template <size_t Offset = 0, class T, class A0, class F>
Vc_INTRINSIC void for_each(simd_tuple<T, A0> &a_, const simd_tuple<T, A0> &b_,
                           F &&fun_)
{
    std::forward<F>(fun_)(make_meta<Offset>(a_), a_.first, b_.first);
}
template <size_t Offset = 0, class T, class A0, class A1, class... As, class F>
Vc_INTRINSIC void for_each(simd_tuple<T, A0, A1, As...> & a_,
                           const simd_tuple<T, A0, A1, As...> &b_, F &&fun_)
{
    fun_(make_meta<Offset>(a_), a_.first, b_.first);
    for_each<Offset + simd_size<T, A0>::value>(a_.second, b_.second,
                                                  std::forward<F>(fun_));
}
template <size_t Offset = 0, class T, class A0, class F>
Vc_INTRINSIC void for_each(const simd_tuple<T, A0> &a_, const simd_tuple<T, A0> &b_,
                           F &&fun_)
{
    std::forward<F>(fun_)(make_meta<Offset>(a_), a_.first, b_.first);
}
template <size_t Offset = 0, class T, class A0, class A1, class... As, class F>
Vc_INTRINSIC void for_each(const simd_tuple<T, A0, A1, As...> &a_,
                           const simd_tuple<T, A0, A1, As...> &b_, F &&fun_)
{
    fun_(make_meta<Offset>(a_), a_.first, b_.first);
    for_each<Offset + simd_size<T, A0>::value>(a_.second, b_.second,
                                                  std::forward<F>(fun_));
}
}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail {
template <class T> using scalar_mask = simd_mask<T, simd_abi::scalar>;
template <class T> using scalar_simd = simd<T, simd_abi::scalar>;
struct scalar_simd_impl {
    using abi = Vc::simd_abi::scalar;
    using mask_member_type = bool;
    template <class T> using simd_member_type = T;
    template <class T> using simd = Vc::simd<T, abi>;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    using size_tag = size_constant<1>;
    template <class T> using type_tag = T *;
    template <class T> static Vc_INTRINSIC T broadcast(T x, size_tag) noexcept
    {
        return x;
    }
    template <class F, class T>
    static Vc_INTRINSIC T generator(F &&gen, type_tag<T>, size_tag)
    {
        return gen(size_constant<0>());
    }
    template <class T, class U, class F>
    static inline T load(const U *mem, F, type_tag<T>) noexcept
    {
        return static_cast<T>(mem[0]);
    }
    template <class T, class U, class F>
    static inline void masked_load(T &merge, bool k, const U *mem, F) noexcept
    {
        if (k) {
            merge = static_cast<T>(mem[0]);
        }
    }
    template <class T, class U, class F>
    static inline void store(T v, U *mem, F, type_tag<T>) noexcept
    {
        mem[0] = static_cast<T>(v);
    }
    template <class T, class U, class F>
    static inline void masked_store(const T v, U *mem, F, const bool k) noexcept
    {
        if (k) {
            mem[0] = v;
        }
    }
    template <class T> static inline bool negate(T x) noexcept { return !x; }
    template <class T, class BinaryOperation>
    static inline T reduce(size_tag, const simd<T> &x, BinaryOperation &)
    {
        return x.d;
    }
    template <class T> static inline T min(const T a, const T b)
    {
        return std::min(a, b);
    }
    template <class T> static inline T max(const T a, const T b)
    {
        return std::max(a, b);
    }
    template <class T> static inline T complement(T x) noexcept
    {
        return static_cast<T>(~x);
    }
    template <class T> static inline T unary_minus(T x) noexcept
    {
        return static_cast<T>(-x);
    }
    template <class T> static inline T plus(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) +
                              detail::promote_preserving_unsigned(y));
    }
    template <class T> static inline T minus(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) -
                              detail::promote_preserving_unsigned(y));
    }
    template <class T> static inline T multiplies(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) *
                              detail::promote_preserving_unsigned(y));
    }
    template <class T> static inline T divides(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) /
                              detail::promote_preserving_unsigned(y));
    }
    template <class T> static inline T modulus(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) %
                              detail::promote_preserving_unsigned(y));
    }
    template <class T> static inline T bit_and(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) &
                              detail::promote_preserving_unsigned(y));
    }
    static inline float bit_and(float x, float y)
    {
        static_assert(sizeof(float) == sizeof(uint), "");
        const uint r = reinterpret_cast<const may_alias<uint> &>(x) &
                       reinterpret_cast<const may_alias<uint> &>(y);
        return reinterpret_cast<const may_alias<float> &>(r);
    }
    static inline double bit_and(double x, double y)
    {
        static_assert(sizeof(double) == sizeof(ullong), "");
        const ullong r = reinterpret_cast<const may_alias<ullong> &>(x) &
                         reinterpret_cast<const may_alias<ullong> &>(y);
        return reinterpret_cast<const may_alias<double> &>(r);
    }
    template <class T> static inline T bit_or(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) |
                              detail::promote_preserving_unsigned(y));
    }
    static inline float bit_or(float x, float y)
    {
        static_assert(sizeof(float) == sizeof(uint), "");
        const uint r = reinterpret_cast<const may_alias<uint> &>(x) |
                       reinterpret_cast<const may_alias<uint> &>(y);
        return reinterpret_cast<const may_alias<float> &>(r);
    }
    static inline double bit_or(double x, double y)
    {
        static_assert(sizeof(double) == sizeof(ullong), "");
        const ullong r = reinterpret_cast<const may_alias<ullong> &>(x) |
                         reinterpret_cast<const may_alias<ullong> &>(y);
        return reinterpret_cast<const may_alias<double> &>(r);
    }
    template <class T> static inline T bit_xor(T x, T y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) ^
                              detail::promote_preserving_unsigned(y));
    }
    template <class T> static inline T bit_shift_left(T x, int y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) << y);
    }
    template <class T> static inline T bit_shift_right(T x, int y)
    {
        return static_cast<T>(detail::promote_preserving_unsigned(x) >> y);
    }
    template <class T> static Vc_INTRINSIC T abs(T x) { return T(std::abs(x)); }
    template <class T> static Vc_INTRINSIC T sqrt(T x) { return std::sqrt(x); }
    template <class T> static Vc_INTRINSIC T logb(T x) { return std::logb(x); }
    template <class T> static Vc_INTRINSIC T trunc(T x) { return std::trunc(x); }
    template <class T> static Vc_INTRINSIC T floor(T x) { return std::floor(x); }
    template <class T> static Vc_INTRINSIC T ceil(T x) { return std::ceil(x); }
    template <class T> static Vc_INTRINSIC T frexp(T x, int &exp)
    {
        return std::frexp(x, &exp);
    }
    template <class T> static Vc_INTRINSIC T frexp(T x, simd_tuple<int, abi> &exp)
    {
        return frexp(x, exp.first);
    }
    template <class T> static Vc_INTRINSIC simd_tuple<int, abi> fpclassify(T x)
    {
        return {std::fpclassify(x)};
    }
    template <class T> static Vc_INTRINSIC bool isfinite(T x) { return std::isfinite(x); }
    template <class T> static Vc_INTRINSIC bool isinf(T x) { return std::isinf(x); }
    template <class T> static Vc_INTRINSIC bool isnan(T x) { return std::isnan(x); }
    template <class T> static Vc_INTRINSIC bool isnormal(T x) { return std::isnormal(x); }
    template <class T> static Vc_INTRINSIC bool signbit(T x) { return std::signbit(x); }
    template <class T> static Vc_INTRINSIC bool isunordered(T x, T y) { return std::isunordered(x, y); }
    template <class T> static inline void increment(T &x) { ++x; }
    template <class T> static inline void decrement(T &x) { --x; }
#define Vc_CMP_OPERATIONS(cmp_) \
    template <class T> static inline bool cmp_(T x, T y) \
    { \
        return std::cmp_<T>()(x, y); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
    Vc_CMP_OPERATIONS(equal_to);
    Vc_CMP_OPERATIONS(not_equal_to);
    Vc_CMP_OPERATIONS(less);
    Vc_CMP_OPERATIONS(greater);
    Vc_CMP_OPERATIONS(less_equal);
    Vc_CMP_OPERATIONS(greater_equal);
#undef Vc_CMP_OPERATIONS
    template <class T> static T get(const T v, int i) noexcept
    {
        Vc_ASSERT(i == 0);
        unused(i);
        return v;
    }
    template <class T, class U> static void set(T &v, int i, U &&x) noexcept
    {
        Vc_ASSERT(i == 0);
        unused(i);
        v = std::forward<U>(x);
    }
    template <typename T> static Vc_INTRINSIC void masked_assign(bool k, T &lhs, T rhs)
    {
        if (k) {
            lhs = rhs;
        }
    }
    template <template <typename> class Op, typename T>
    static Vc_INTRINSIC void masked_cassign(const bool k, T &lhs, const T rhs)
    {
        if (k) {
            lhs = Op<T>{}(lhs, rhs);
        }
    }
    template <template <typename> class Op, typename T>
    static Vc_INTRINSIC T masked_unary(const bool k, const T v)
    {
        return static_cast<T>(k ? Op<T>{}(v) : v);
    }
};
struct scalar_mask_impl {
    template <class T> using simd_mask = Vc::simd_mask<T, simd_abi::scalar>;
    using size_tag = size_constant<1>;
    template <class T> using type_tag = T *;
    static Vc_INTRINSIC std::bitset<1> to_bitset(bool x) noexcept { return unsigned(x); }
    template <class T>
    static Vc_INTRINSIC bool from_bitset(std::bitset<1> bs, type_tag<T>) noexcept
    {
        return bs[0];
    }
    template <class T> static Vc_INTRINSIC bool broadcast(bool x, type_tag<T>) noexcept
    {
        return x;
    }
    template <class F>
    static Vc_INTRINSIC bool load(const bool *mem, F, size_tag) noexcept
    {
        return mem[0];
    }
    template <class F>
    static Vc_INTRINSIC void masked_load(bool &merge, bool mask, const bool *mem,
                                         F) noexcept
    {
        if (mask) {
            merge = mem[0];
        }
    }
    template <class F> static inline void store(bool v, bool *mem, F, size_tag) noexcept
    {
        mem[0] = v;
    }
    template <class F>
    static Vc_INTRINSIC void masked_store(const bool v, bool *mem, F,
                                          const bool k) noexcept
    {
        if (k) {
            mem[0] = v;
        }
    }
    static inline bool negate(bool x, size_tag) noexcept { return !x; }
    template <class T>
    static inline simd_mask<T> logical_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, x.d && y.d};
    }
    template <class T>
    static inline simd_mask<T> logical_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, x.d || y.d};
    }
    template <class T> static inline simd_mask<T> bit_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, x.d && y.d};
    }
    template <class T> static inline simd_mask<T> bit_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, x.d || y.d};
    }
    template <class T> static inline simd_mask<T> bit_xor(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, x.d != y.d};
    }
    static bool get(const bool k, int i) noexcept
    {
        Vc_ASSERT(i == 0);
        detail::unused(i);
        return k;
    }
    static void set(bool &k, int i, bool x) noexcept
    {
        Vc_ASSERT(i == 0);
        detail::unused(i);
        k = x;
    }
    static Vc_INTRINSIC void masked_assign(bool k, bool &lhs, bool rhs)
    {
        if (k) {
            lhs = rhs;
        }
    }
};
template <class T> struct simd_converter<T, simd_abi::scalar, T, simd_abi::scalar> {
    Vc_INTRINSIC T operator()(T a) { return a; }
};
template <class From, class To>
struct simd_converter<From, simd_abi::scalar, To, simd_abi::scalar> {
    Vc_INTRINSIC To operator()(From a)
    {
        return static_cast<To>(a);
    }
};
template <> Vc_ALWAYS_INLINE bool convert_mask<bool>(bool x) { return x; }
}
template <class T> inline bool all_of(const detail::scalar_mask<T> &k) { return k[0]; }
template <class T> inline bool any_of(const detail::scalar_mask<T> &k) { return k[0]; }
template <class T> inline bool none_of(const detail::scalar_mask<T> &k) { return !k[0]; }
template <class T> inline bool some_of(const detail::scalar_mask<T> &) { return false; }
template <class T> inline int popcount(const detail::scalar_mask<T> &k) { return k[0]; }
template <class T> inline int find_first_set(const detail::scalar_mask<T> &) { return 0; }
template <class T> inline int find_last_set(const detail::scalar_mask<T> &) { return 0; }
Vc_VERSIONED_NAMESPACE_END
namespace std
{
template <class T> struct equal_to<Vc::simd_mask<T, Vc::simd_abi::scalar>> {
private:
    using M = Vc::simd_mask<T, Vc::simd_abi::scalar>;
public:
    bool operator()(const M &x, const M &y) const { return x[0] == y[0]; }
};
}
#endif
#ifndef VC_SIMD_SSE_H_
#define VC_SIMD_SSE_H_ 
#ifdef Vc_HAVE_SSE_ABI
#ifndef VC_SIMD_X86_CONVERT_H_
#define VC_SIMD_X86_CONVERT_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace x86
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])...};
}
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, From v1, std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])..., static_cast<T>(v1[I])...};
}
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3,
                                std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])..., static_cast<T>(v1[I])...,
                                static_cast<T>(v2[I])..., static_cast<T>(v3[I])...};
}
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3, From v4, From v5,
                                From v6, From v7, std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])..., static_cast<T>(v1[I])...,
                                static_cast<T>(v2[I])..., static_cast<T>(v3[I])...,
                                static_cast<T>(v4[I])..., static_cast<T>(v5[I])...,
                                static_cast<T>(v6[I])..., static_cast<T>(v7[I])...};
}
template <typename To, typename From, size_t... I0, size_t... I1>
Vc_INTRINSIC To convert_builtin(From v0, From v1, std::index_sequence<I0...>,
                                std::index_sequence<I1...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I0])..., static_cast<T>(v1[I0])...,
                                (I1, T{})...};
}
template <typename To, typename From, size_t... I0, size_t... I1>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3,
                                std::index_sequence<I0...>, std::index_sequence<I1...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I0])..., static_cast<T>(v1[I0])...,
                                static_cast<T>(v2[I0])..., static_cast<T>(v3[I0])...,
                                (I1, T{})...};
}
template <typename To, typename From, size_t... I0, size_t... I1>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3, From v4, From v5,
                                From v6, From v7, std::index_sequence<I0...>,
                                std::index_sequence<I1...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{
        static_cast<T>(v0[I0])..., static_cast<T>(v1[I0])..., static_cast<T>(v2[I0])...,
        static_cast<T>(v3[I0])..., static_cast<T>(v4[I0])..., static_cast<T>(v5[I0])...,
        static_cast<T>(v6[I0])..., static_cast<T>(v7[I0])..., (I1, T{})...};
}
#endif
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0, x_f32 v1);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0, x_f32 v1, x_f32 v2, x_f32 v3);
#ifdef Vc_HAVE_SSE2
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3, x_f64 v4, x_f64 v5, x_f64 v6, x_f64 v7);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i16, x_i16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u16, x_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i32, x_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i32, x_i32, x_i32, x_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32, x_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32, x_u32, x_u32, x_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64, x_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64, x_i64, x_i64, x_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64, x_i64, x_i64, x_i64, x_i64, x_i64, x_i64, x_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64, x_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64, x_u64, x_u64, x_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64, x_u64, x_u64, x_u64, x_u64, x_u64, x_u64, x_u64);
#endif
#ifdef Vc_HAVE_AVX
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f32, y_f32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f32, y_f32, y_f32, y_f32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64, y_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64, y_f64, y_f64, y_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64, y_f64, y_f64, y_f64, y_f64, y_f64, y_f64, y_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i16, y_i16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u16, y_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i32, y_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i32, y_i32, y_i32, y_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u32, y_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u32, y_u32, y_u32, y_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64, y_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64, y_i64, y_i64, y_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64, y_i64, y_i64, y_i64, y_i64, y_i64, y_i64, y_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64, y_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64, y_u64, y_u64, y_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64, y_u64, y_u64, y_u64, y_u64, y_u64, y_u64, y_u64);
#endif
#ifdef Vc_HAVE_AVX512F
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f32, z_f32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f32, z_f32, z_f32, z_f32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64, z_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64, z_f64, z_f64, z_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64, z_f64, z_f64, z_f64, z_f64, z_f64, z_f64, z_f64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i16, z_i16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u16, z_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i32, z_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i32, z_i32, z_i32, z_i32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u32, z_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u32, z_u32, z_u32, z_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64, z_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64, z_i64, z_i64, z_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64, z_i64, z_i64, z_i64, z_i64, z_i64, z_i64, z_i64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64, z_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64, z_u64, z_u64, z_u64);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64, z_u64, z_u64, z_u64, z_u64, z_u64, z_u64, z_u64);
#endif
#ifdef Vc_HAVE_SSE2
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_f32 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvttps_epi64(v);
#else
    return {v.m(0), v.m(1)};
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvttpd_epi64(v);
#else
    return {v.m(0), v.m(1)};
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_i64 v) { return v; }
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_i32 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepi32_epi64(v);
#else
    return _mm_unpacklo_epi32(v, _mm_srai_epi32(v, 32));
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_u32 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepu32_epi64(v);
#else
    return _mm_unpacklo_epi32(v, zero<__m128i>());
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_i16 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepi16_epi64(v);
#else
    auto x = _mm_srai_epi16(v, 16);
    auto y = _mm_unpacklo_epi16(v, x);
    x = _mm_unpacklo_epi16(x, x);
    return _mm_unpacklo_epi32(y, x);
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_u16 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepu16_epi64(v);
#else
    return _mm_unpacklo_epi32(_mm_unpacklo_epi16(v, zero<__m128i>()), zero<__m128i>());
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_i08 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepi8_epi64(v);
#else
    auto x = _mm_cmplt_epi8(v, zero<__m128i>());
    auto y = _mm_unpacklo_epi8(v, x);
    x = _mm_unpacklo_epi8(x, x);
    y = _mm_unpacklo_epi16(y, x);
    x = _mm_unpacklo_epi16(x, x);
    return _mm_unpacklo_epi32(y, x);
#endif
}
template <> Vc_INTRINSIC x_i64 Vc_VDECL convert_to<x_i64>(x_u08 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepu8_epi64(v);
#else
    return _mm_unpacklo_epi32(_mm_unpacklo_epi16(_mm_unpacklo_epi8(v, zero<__m128i>()), zero<__m128i>()), zero<__m128i>());
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_f32 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvttps_epi64(v);
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3)};
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm_cvttpd_epi64(v));
#else
    return {v.m(0), v.m(1), 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(y_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvttpd_epi64(v);
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3)};
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_u64 v) { return zeroExtend(v.v()); }
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_i64 v) { return zeroExtend(v.v()); }
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(y_i64 v) { return v; }
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_i32 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepi32_epi64(v);
#else
    return x86::concat(_mm_cvtepi32_epi64(v), _mm_cvtepi32_epi64(_mm_unpackhi_epi64(v, v)));
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_u32 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepu32_epi64(v);
#else
    return x86::concat(_mm_cvtepu32_epi64(v), _mm_cvtepu32_epi64(_mm_unpackhi_epi64(v, v)));
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_i16 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepi16_epi64(v);
#else
    return x86::concat(_mm_cvtepi16_epi64(v), _mm_cvtepi16_epi64(_mm_srli_si128(v, 4)));
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_u16 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepu16_epi64(v);
#else
    return x86::concat(_mm_cvtepu16_epi64(v), _mm_cvtepu16_epi64(_mm_srli_si128(v, 4)));
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_i08 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepi8_epi64(v);
#else
    return x86::concat(_mm_cvtepi8_epi64(v), _mm_cvtepi8_epi64(_mm_srli_si128(v, 2)));
#endif
}
template <> Vc_INTRINSIC y_i64 Vc_VDECL convert_to<y_i64>(x_u08 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepu8_epi64(v);
#else
    return x86::concat(_mm_cvtepu8_epi64(v), _mm_cvtepu8_epi64(_mm_srli_si128(v, 2)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_f32 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm256_cvttps_epi64(v));
#elif defined Vc_HAVE_AVX512DQ
    return _mm512_cvttps_epi64(zeroExtend(v));
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3), 0, 0, 0, 0};
#endif
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(y_f32 v)
{
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_cvttps_epi64(v);
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3), v.m(4), v.m(5), v.m(6), v.m(7)};
#endif
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_f32 v0, x_f32 v1)
{
    return convert_to<z_i64>(detail::concat(v0, v1));
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(zeroExtend(_mm_cvttpd_epi64(v)));
#else
    return {v.m(0), v.m(1), 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(y_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm256_cvttpd_epi64(v));
#elif defined Vc_HAVE_AVX512DQ
    return _mm512_cvttpd_epi64(zeroExtend(v));
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3), 0.f, 0.f, 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(z_f64 v) {
#if defined Vc_HAVE_AVX512DQ
    return _mm512_cvttpd_epi64(v);
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3), v.m(4), v.m(5), v.m(6), v.m(7)};
#endif
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(y_u64 v) { return zeroExtend(v.v()); }
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(y_i64 v) { return zeroExtend(v.v()); }
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(z_i64 v) { return v; }
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(y_i32 v) {
    return _mm512_cvtepi32_epi64(v);
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(y_u32 v) {
    return _mm512_cvtepu32_epi64(v);
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_i16 v) {
    return _mm512_cvtepi16_epi64(v);
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_u16 v) {
    return _mm512_cvtepu16_epi64(v);
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_i08 v) {
    return _mm512_cvtepi8_epi64(v);
}
template <> Vc_INTRINSIC z_i64 Vc_VDECL convert_to<z_i64>(x_u08 v) {
    return _mm512_cvtepu8_epi64(v);
}
#endif
template <> Vc_INTRINSIC x_u64 Vc_VDECL convert_to<x_u64>(x_f32 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvttps_epu64(v);
#else
    return {v.m(0), v.m(1)};
#endif
}
template <> Vc_INTRINSIC x_u64 Vc_VDECL convert_to<x_u64>(x_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvttpd_epu64(v);
#else
    return {v.m(0), v.m(1)};
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC y_u64 Vc_VDECL convert_to<y_u64>(x_f32 v0) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvttps_epu64(v0);
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3)};
#endif
}
template <> Vc_INTRINSIC y_u64 Vc_VDECL convert_to<y_u64>(x_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm_cvttpd_epu64(v));
#else
    return {v.m(0), v.m(1), 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC y_u64 Vc_VDECL convert_to<y_u64>(y_f64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvttpd_epu64(v);
#elif defined Vc_HAVE_AVX512DQ
    return lo256(_mm512_cvttpd_epu64(intrin_cast<__m512d>(v)));
#else
    return {v.m(0), v.m(1), v.m(2), v.m(3)};
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_u64 Vc_VDECL convert_to<z_u64>(y_f32 v0) {
#if defined Vc_HAVE_AVX512DQ
    return _mm512_cvttps_epu64(v0);
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3), v0.m(4), v0.m(5), v0.m(6), v0.m(7)};
#endif
}
template <> Vc_INTRINSIC z_u64 Vc_VDECL convert_to<z_u64>(z_f64 v0) {
#if defined Vc_HAVE_AVX512DQ
    return _mm512_cvttpd_epu64(v0);
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3), v0.m(4), v0.m(5), v0.m(6), v0.m(7)};
#endif
}
#endif
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_f32 v) { return _mm_cvttps_epi32(v); }
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_f64 v) { return _mm_cvttpd_epi32(v); }
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_f64 v0, x_f64 v1)
{
    return _mm_unpacklo_epi64(convert_to<x_i32>(v0), convert_to<x_i32>(v1));
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(y_f64 v)
{
    return _mm256_cvttpd_epi32(v);
}
#endif
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_i64 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepi64_epi32(v);
#else
    return _mm_unpacklo_epi64(_mm_shuffle_epi32(v, 8), _mm_setzero_si128());
#endif
}
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_i64 v0, x_i64 v1)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi64_epi32(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX512F
    return lo128(_mm512_cvtepi64_epi32(intrin_cast<__m512i>(detail::concat(v0, v1))));
#else
    return _mm_unpacklo_epi64(_mm_shuffle_epi32(v0, 8), _mm_shuffle_epi32(v1, 8));
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(y_i64 v0)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi64_epi32(v0);
#elif defined Vc_HAVE_AVX512F
    return lo128(_mm512_cvtepi64_epi32(intrin_cast<__m512i>(v0)));
#elif defined Vc_HAVE_AVX2
    return lo128(_mm256_permute4x64_epi64(_mm256_shuffle_epi32(v0, 8), 0 + 4 * 2));
#else
    return _mm_unpacklo_epi64(_mm_shuffle_epi32(lo128(v0), 8),
                              _mm_shuffle_epi32(hi128(v0), 8));
#endif
}
#endif
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_i32 v) { return v; }
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_i16 v) {
#ifdef Vc_HAVE_SSE4_1
   return _mm_cvtepi16_epi32(v);
#else
   return _mm_srai_epi32(_mm_unpacklo_epi16(v, v), 16);
#endif
}
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_u16 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepu16_epi32(v);
#else
    return _mm_unpacklo_epi16(v, zero<__m128i>());
#endif
}
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_i08 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepi8_epi32(v);
#else
    const auto x = _mm_unpacklo_epi8(v, v);
    return _mm_srai_epi32(_mm_unpacklo_epi16(x, x), 24);
#endif
}
template <> Vc_INTRINSIC x_i32 Vc_VDECL convert_to<x_i32>(x_u08 v) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_cvtepu8_epi32(v);
#else
    return _mm_unpacklo_epi16(_mm_unpacklo_epi8(v, zero<__m128i>()), zero<__m128i>());
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_f32 v)
{
    return zeroExtend(_mm_cvttps_epi32(v));
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_f32 v0)
{
    return _mm256_cvttps_epi32(v0);
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_f64 v)
{
    return zeroExtend(_mm_cvttpd_epi32(v));
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_f64 v)
{
    return zeroExtend(_mm256_cvttpd_epi32(v));
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_f64 v0, y_f64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvttpd_epi32(detail::concat(v0, v1));
#else
    return x86::concat(_mm256_cvttpd_epi32(v0), _mm256_cvttpd_epi32(v1));
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(z_f64 v0)
{
    return _mm512_cvttpd_epi32(v0);
}
#endif
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_i64 v) {
    return zeroExtend(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_i64 v0)
{
#ifdef Vc_HAVE_AVX512VL
    return zeroExtend(_mm256_cvtepi64_epi32(v0));
#elif defined Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi32(zeroExtend(v0));
#elif defined Vc_HAVE_AVX2
    const auto vabxxcdxx = _mm256_shuffle_epi32(v0, 8);
    const auto v00ab00cd = _mm256_srli_si256(vabxxcdxx, 8);
    return _mm256_permute4x64_epi64(v00ab00cd, 1 + 4 * 3);
#else
    return intrin_cast<__m256i>(zeroExtend(
        _mm_shuffle_ps(_mm_castsi128_ps(lo128(v0)), _mm_castsi128_ps(hi128(v0)),
                       0x01 * 0 + 0x04 * 2 + 0x10 * 0 + 0x40 * 2)));
#endif
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_i64 v0, y_i64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi32(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX2
    const auto v0_abxxcdxx = _mm256_shuffle_epi32(v0, 8);
    const auto v1_efxxghxx = _mm256_shuffle_epi32(v1, 8);
    const auto v_abefcdgh = _mm256_unpacklo_epi64(v0_abxxcdxx, v1_efxxghxx);
    return _mm256_permute4x64_epi64(v_abefcdgh, 0x01 * 0 + 0x04 * 2 + 0x10 * 1 + 0x40 * 3);
#else
    return intrin_cast<__m256i>(
        x86::concat(_mm_shuffle_ps(intrin_cast<__m128>(v0), hi128(intrin_cast<__m256>(v0)),
                              0x01 * 0 + 0x04 * 2 + 0x10 * 0 + 0x40 * 2),
               _mm_shuffle_ps(intrin_cast<__m128>(v1), hi128(intrin_cast<__m256>(v1)),
                              0x01 * 0 + 0x04 * 2 + 0x10 * 0 + 0x40 * 2)));
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(z_i64 v0)
{
    return _mm512_cvtepi64_epi32(v0);
}
#endif
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_i32 v) { return zeroExtend(v); }
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_i32 v) { return v; }
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_u32 v) { return zeroExtend(v); }
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_u32 v) { return v.v(); }
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_i16 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepi16_epi32(v);
#else
    return x86::concat(_mm_cvtepi16_epi32(v), _mm_cvtepi16_epi32(shift_right<8>(v)));
#endif
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_i16 v) {
    return convert_to<y_i32>(lo128(v));
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_u16 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepu16_epi32(v);
#else
    return x86::concat(_mm_cvtepu16_epi32(v), _mm_cvtepu16_epi32(shift_right<8>(v)));
#endif
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_i08 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepi8_epi32(v);
#else
    return x86::concat(_mm_cvtepi8_epi32(v), _mm_cvtepi8_epi32(shift_right<4>(v)));
#endif
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_i08 v) {
    return convert_to<y_i32>(lo128(v));
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(x_u08 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepu8_epi32(v);
#else
    return x86::concat(_mm_cvtepu8_epi32(v), _mm_cvtepu8_epi32(shift_right<4>(v)));
#endif
}
template <> Vc_INTRINSIC y_i32 Vc_VDECL convert_to<y_i32>(y_u08 v) {
    return convert_to<y_i32>(lo128(v));
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(z_i64 v0)
{
    return zeroExtend(_mm512_cvtepi64_epi32(v0));
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(z_i64 v0, z_i64 v1)
{
    return x86::concat(_mm512_cvtepi64_epi32(v0), _mm512_cvtepi64_epi32(v1));
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(z_i32 v0) { return v0; }
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(y_i16 v0)
{
    return _mm512_cvtepi16_epi32(v0);
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(y_u16 v0)
{
    return _mm512_cvtepu16_epi32(v0);
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(x_i08 v0)
{
    return _mm512_cvtepi8_epi32(v0);
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(x_u08 v0)
{
    return _mm512_cvtepu8_epi32(v0);
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(z_f64 v0, z_f64 v1)
{
    return x86::concat(_mm512_cvttpd_epi32(v0), _mm512_cvttpd_epi32(v1));
}
template <> Vc_INTRINSIC z_i32 Vc_VDECL convert_to<z_i32>(z_f32 v0)
{
    return _mm512_cvttps_epi32(v0);
}
#endif
template <> Vc_INTRINSIC x_u32 Vc_VDECL convert_to<x_u32>(x_f32 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvttps_epu32(v);
#else
    return _mm_castps_si128(
        blendv_ps(_mm_castsi128_ps(_mm_cvttps_epi32(v)),
                  _mm_castsi128_ps(_mm_xor_si128(
                      _mm_cvttps_epi32(_mm_sub_ps(v, _mm_set1_ps(1u << 31))),
                      _mm_set1_epi32(1 << 31))),
                  _mm_cmpge_ps(v, _mm_set1_ps(1u << 31))));
#endif
}
template <> Vc_INTRINSIC x_u32 Vc_VDECL convert_to<x_u32>(x_f64 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvttpd_epu32(v);
#elif defined Vc_HAVE_SSE4_1
    return _mm_xor_si128(
        _mm_cvttpd_epi32(_mm_sub_pd(_mm_floor_pd(v), _mm_set1_pd(0x80000000u))),
        _mm_loadl_epi64(reinterpret_cast<const __m128i*>(sse_const::signMaskFloat)));
#else
    return {v[0], v[1], 0, 0};
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_u32 Vc_VDECL convert_to<x_u32>(y_f64 v)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvttpd_epu32(v);
#else
    return xor_(_mm256_cvttpd_epi32(
                    _mm256_sub_pd(_mm256_floor_pd(v), _mm256_set1_pd(0x80000000u))),
                intrin_cast<__m128i>(signmask16(float())));
#endif
}
#endif
template <> Vc_INTRINSIC x_u32 Vc_VDECL convert_to<x_u32>(x_f64 v0, x_f64 v1)
{
#ifdef Vc_HAVE_AVX
    return convert_to<x_u32>(y_f64(detail::concat(v0, v1)));
#else
    return _mm_unpacklo_epi64(convert_to<x_u32>(v0), convert_to<x_u32>(v1));
#endif
}
#ifdef Vc_HAVE_AVX2
template <> Vc_INTRINSIC y_u32 Vc_VDECL convert_to<y_u32>(y_f64 v0, y_f64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvttpd_epu32(detail::concat(v0, v1));
#else
    return xor_(x86::concat(_mm256_cvttpd_epi32(
                           _mm256_sub_pd(_mm256_floor_pd(v0), avx_2_pow_31<double>())),
                       _mm256_cvttpd_epi32(
                           _mm256_sub_pd(_mm256_floor_pd(v1), avx_2_pow_31<double>()))),
                avx_2_pow_31<uint>());
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_u32 Vc_VDECL convert_to<y_u32>(z_f64 v0)
{
    return _mm512_cvttpd_epu32(v0);
}
#endif
template <> Vc_INTRINSIC y_u32 Vc_VDECL convert_to<y_u32>(x_f32 v0)
{
    return zeroExtend(convert_to<x_u32>(v0));
}
template <> Vc_INTRINSIC y_u32 Vc_VDECL convert_to<y_u32>(y_f32 v0)
{
#if defined Vc_HAVE_AVX512F && defined Vc_HAVE_AVX512VL
    return _mm256_cvttps_epu32(v0);
#elif defined Vc_HAVE_AVX512F
    return lo256(_mm512_cvttps_epu32(intrin_cast<__m512>(v0)));
#else
    return _mm256_blendv_epi8(
        _mm256_cvttps_epi32(v0),
        _mm256_add_epi32(_mm256_cvttps_epi32(_mm256_sub_ps(v0, avx_2_pow_31<float>())),
                         avx_2_pow_31<uint>()),
        _mm256_castps_si256(_mm256_cmp_ps(v0, avx_2_pow_31<float>(), _CMP_NLT_US)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_u32 Vc_VDECL convert_to<z_u32>(z_f64 v0, z_f64 v1)
{
    return x86::concat(_mm512_cvttpd_epu32(v0), _mm512_cvttpd_epu32(v1));
}
template <> Vc_INTRINSIC z_u32 Vc_VDECL convert_to<z_u32>(z_f32 v0)
{
    return _mm512_cvttps_epu32(v0);
}
#endif
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i64 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepi64_epi16(v);
#elif defined Vc_HAVE_SSSE3
    return _mm_shuffle_epi8(
        v, _mm_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                         -0x80, -0x80, -0x80, -0x80, -0x80));
#else
    return {v.m(0), v.m(1), 0, 0, 0, 0, 0, 0};
#endif
}
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i64 v0, x_i64 v1)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi64_epi16(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi16(x86::concat(x86::concat(v0, v1), zero<__m256i>()));
#elif defined Vc_HAVE_SSE4_1
    return _mm_shuffle_epi8(_mm_blend_epi16(v0, _mm_slli_si128(v1, 4), 0x44),
                            _mm_setr_epi8(0, 1, 8, 9, 4, 5, 12, 13, -0x80, -0x80, -0x80,
                                          -0x80, -0x80, -0x80, -0x80, -0x80));
#else
    return {v0.m(0), v0.m(1), v1.m(0), v1.m(1), 0, 0, 0, 0};
#endif
}
template <>
Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i64 v0, x_i64 v1, x_i64 v2, x_i64 v3)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi16(
        detail::concat(detail::concat(v0, v1), detail::concat(v2, v3)));
#elif defined Vc_HAVE_SSE4_1
    return _mm_shuffle_epi8(
        _mm_blend_epi16(
            _mm_blend_epi16(v0, _mm_slli_si128(v1, 2), 0x22),
            _mm_blend_epi16(_mm_slli_si128(v2, 4), _mm_slli_si128(v3, 6), 0x88),
            0xcc),
        _mm_setr_epi8(0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15));
#else
    return _mm_unpacklo_epi32(convert_to<x_i16>(v0, v2), convert_to<x_i16>(v1, v3));
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(y_i64 v0, y_i64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi16(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX2
    auto a = _mm256_unpacklo_epi16(v0, v1);
    auto b = _mm256_unpackhi_epi16(v0, v1);
    auto c = _mm256_unpacklo_epi16(a, b);
    return _mm_unpacklo_epi32(lo128(c), hi128(c));
#else
    return convert_to<x_i16>(lo128(v0), hi128(v0), lo128(v1), hi128(v1));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(z_i64 v0)
{
    return _mm512_cvtepi64_epi16(v0);
}
#endif
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i32 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepi32_epi16(v);
#else
    auto a = _mm_unpacklo_epi16(v, zero<__m128i>());
    auto b = _mm_unpackhi_epi16(v, zero<__m128i>());
    auto c = _mm_unpacklo_epi16(a, b);
    auto d = _mm_unpackhi_epi16(a, b);
    return _mm_unpacklo_epi16(c, d);
#endif
}
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i32 v0, x_i32 v1)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi32_epi16(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX512F
    return lo128(
        _mm512_cvtepi32_epi16(x86::concat(detail::concat(v0, v1), zero<__m256i>())));
#elif defined Vc_HAVE_SSE4_1
    return _mm_shuffle_epi8(
        _mm_blend_epi16(v0, _mm_slli_si128(v1, 2), 0xaa),
        _mm_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, 2, 3, 6, 7, 10, 11, 14, 15));
#else
    auto a = _mm_unpacklo_epi16(v0, v1);
    auto b = _mm_unpackhi_epi16(v0, v1);
    auto c = _mm_unpacklo_epi16(a, b);
    auto d = _mm_unpackhi_epi16(a, b);
    return _mm_unpacklo_epi16(c, d);
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(y_i32 v0)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi32_epi16(v0);
#elif defined Vc_HAVE_AVX512F
    return lo128(_mm512_cvtepi32_epi16(x86::concat(v0, zero<__m256i>())));
#elif defined Vc_HAVE_AVX2
    auto a = _mm256_shuffle_epi8(
        v0, _mm256_setr_epi8(0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80, -0x80, -0x80, -0x80,
                             -0x80, -0x80, -0x80, 0, 1, 4, 5, 8, 9, 12, 13, -0x80, -0x80,
                             -0x80, -0x80, -0x80, -0x80, -0x80, -0x80));
    return lo128(_mm256_permute4x64_epi64(a, 0xe8));
#else
    return convert_to<x_i16>(lo128(v0), hi128(v0));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(z_u64 v0)
{
    return _mm512_cvtepi64_epi16(v0);
}
#endif
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i16 v) { return v; }
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_i08 v) {
#ifdef Vc_HAVE_SSE4_1
   return _mm_cvtepi8_epi16(v);
#else
    return _mm_srai_epi16(_mm_unpacklo_epi8(v, v), 8);
#endif
}
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_u08 v) {
#ifdef Vc_HAVE_SSE4_1
   return _mm_cvtepu8_epi16(v);
#else
   return _mm_unpacklo_epi8(v, zero<__m128i>());
#endif
}
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_f64 v)
{
    return convert_to<x_i16>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_f64 v0, x_f64 v1)
{
    return convert_to<x_i16>(convert_to<x_i32>(v0, v1));
}
template <>
Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3)
{
    return convert_to<x_i16>(convert_to<x_i32>(v0, v1), convert_to<x_i32>(v2, v3));
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(y_f64 v0, y_f64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return convert_to<x_i16>(y_i32(_mm512_cvttpd_epi32(detail::concat(v0, v1))));
#else
    return convert_to<x_i16>(x_i32(_mm256_cvttpd_epi32(v0)),
                             x_i32(_mm256_cvttpd_epi32(v1)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(z_f64 v0)
{
    return convert_to<x_i16>(y_i32(_mm512_cvttpd_epi32(v0)));
}
#endif
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_f32 v)
{
    return convert_to<x_i16>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(x_f32 v0, x_f32 v1)
{
    return convert_to<x_i16>(convert_to<x_i32>(v0), convert_to<x_i32>(v1));
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i16 Vc_VDECL convert_to<x_i16>(y_f32 v0)
{
    return convert_to<x_i16>(convert_to<y_i32>(v0));
}
#endif
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_i64 v) {
#ifdef Vc_HAVE_AVX512VL
    return zeroExtend(_mm_cvtepi64_epi16(v));
#else
    return zeroExtend(_mm_shuffle_epi8(
        v, _mm_setr_epi8(0, 1, 8, 9, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                         -0x80, -0x80, -0x80, -0x80, -0x80)));
#endif
}
#ifdef Vc_HAVE_AVX2
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i64 v0)
{
#ifdef Vc_HAVE_AVX512F
    return zeroExtend(_mm512_cvtepi64_epi16(x86::concat(v0, zero<__m256i>())));
#else
    auto a = _mm256_unpacklo_epi16(v0, zero<__m256i>());
    auto b = _mm256_unpackhi_epi16(v0, zero<__m256i>());
    auto c = _mm256_unpacklo_epi16(a, b);
    return zeroExtend(_mm_unpacklo_epi32(lo128(c), hi128(c)));
#endif
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i64 v0, y_i64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return zeroExtend(_mm512_cvtepi64_epi16(detail::concat(v0, v1)));
#else
    auto a = _mm256_unpacklo_epi16(v0, v1);
    auto b = _mm256_unpackhi_epi16(v0, v1);
    auto c = _mm256_unpacklo_epi16(a, b);
    return zeroExtend(_mm_unpacklo_epi32(lo128(c), hi128(c)));
#endif
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i64 v0, y_i64 v1, y_i64 v2, y_i64 v3)
{
#ifdef Vc_HAVE_AVX512F
    return x86::concat(_mm512_cvtepi64_epi16(detail::concat(v0, v1)),
                       _mm512_cvtepi64_epi16(detail::concat(v2, v3)));
#else
    auto a = _mm256_unpacklo_epi16(v0, v1);
    auto b = _mm256_unpackhi_epi16(v0, v1);
    auto c = _mm256_unpacklo_epi16(v2, v3);
    auto d = _mm256_unpackhi_epi16(v2, v3);
    auto e = _mm256_unpacklo_epi16(a, b);
    auto f = _mm256_unpacklo_epi16(c, d);
    auto g = _mm256_unpacklo_epi64(e, f);
    return x86::concat(_mm_unpacklo_epi32(lo128(g), hi128(g)),
                       _mm_unpackhi_epi32(lo128(g), hi128(g)));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(z_i64 v0)
{
    return zeroExtend(_mm512_cvtepi64_epi16(v0));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(z_i64 v0, z_i64 v1)
{
    return x86::concat(_mm512_cvtepi64_epi16(v0), _mm512_cvtepi64_epi16(v1));
}
#endif
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_i32 v) {
    return zeroExtend(convert_to<x_i16>(v));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i32 v0)
{
    return zeroExtend(convert_to<x_i16>(v0));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i32 v0, y_i32 v1)
{
#if defined Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi16(detail::concat(v0, v1));
#else
    return detail::concat(convert_to<x_i16>(v0), convert_to<x_i16>(v1));
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(z_i32 v0)
{
    return _mm512_cvtepi32_epi16(v0);
}
#endif
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_i16 v) { return zeroExtend(v); }
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i16 v) { return v; }
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_u16 v) { return zeroExtend(v); }
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_i08 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepi8_epi16(v);
#else
    return x86::concat(_mm_cvtepi8_epi16(v), _mm_cvtepi8_epi16(_mm_unpackhi_epi64(v, v)));
#endif
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_i08 v) {
    return convert_to<y_i16>(lo128(v));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_u08 v) {
#ifdef Vc_HAVE_AVX2
    return _mm256_cvtepu8_epi16(v);
#else
    return x86::concat(_mm_cvtepu8_epi16(v), _mm_cvtepu8_epi16(_mm_unpackhi_epi64(v, v)));
#endif
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_u08 v) {
    return convert_to<y_i16>(lo128(v));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_f64 v)
{
    return convert_to<y_i16>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_f64 v)
{
    return convert_to<y_i16>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_f64 v0, y_f64 v1)
{
    return convert_to<y_i16>(convert_to<y_i32>(v0, v1));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_f64 v0, y_f64 v1, y_f64 v2, y_f64 v3)
{
    return convert_to<y_i16>(convert_to<y_i32>(v0, v1), convert_to<y_i32>(v2, v3));
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(z_f64 v0)
{
    return convert_to<y_i16>(y_i32(_mm512_cvttpd_epi32(v0)));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(z_f64 v0, z_f64 v1)
{
    return _mm512_cvtepi32_epi16(
        x86::concat(_mm512_cvttpd_epi32(v0), _mm512_cvttpd_epi32(v1)));
}
#endif
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(x_f32 v)
{
    return convert_to<y_i16>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_f32 v0)
{
    return convert_to<y_i16>(convert_to<y_i32>(v0));
}
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(y_f32 v0, y_f32 v1)
{
    return convert_to<y_i16>(convert_to<y_i32>(v0), convert_to<y_i32>(v1));
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i16 Vc_VDECL convert_to<y_i16>(z_f32 v0)
{
    return _mm512_cvtepi32_epi16(_mm512_cvttps_epi32(v0));
}
#endif
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_i64 v0)
{
    return zeroExtend(zeroExtend(_mm512_cvtepi64_epi16(v0)));
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_i64 v0, z_i64 v1)
{
    return zeroExtend(x86::concat(_mm512_cvtepi64_epi16(v0), _mm512_cvtepi64_epi16(v1)));
}
template <>
Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_i64 v0, z_i64 v1, z_i64 v2, z_i64 v3)
{
    return x86::concat(x86::concat(_mm512_cvtepi64_epi16(v0), _mm512_cvtepi64_epi16(v1)),
                       x86::concat(_mm512_cvtepi64_epi16(v2), _mm512_cvtepi64_epi16(v3)));
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_i32 v0)
{
    return zeroExtend(_mm512_cvtepi32_epi16(v0));
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_i32 v0, z_i32 v1)
{
    return x86::concat(_mm512_cvtepi32_epi16(v0), _mm512_cvtepi32_epi16(v1));
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_i16 v0) { return v0; }
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(y_i08 v0)
{
#ifdef Vc_HAVE_AVX512BW
    return _mm512_cvtepi8_epi16(v0);
#else
    return x86::concat(_mm256_cvtepi8_epi16(lo128(v0)), _mm256_cvtepi8_epi16(hi128(v0)));
#endif
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(y_u08 v0)
{
#ifdef Vc_HAVE_AVX512BW
    return _mm512_cvtepu8_epi16(v0);
#else
    return x86::concat(_mm256_cvtepu8_epi16(lo128(v0)), _mm256_cvtepu8_epi16(hi128(v0)));
#endif
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_f64 v0, z_f64 v1, z_f64 v2, z_f64 v3)
{
    return convert_to<z_i16>(convert_to<z_i32>(v0, v1), convert_to<z_i32>(v2, v3));
}
template <> Vc_INTRINSIC z_i16 Vc_VDECL convert_to<z_i16>(z_f32 v0, z_f32 v1)
{
    return convert_to<z_i16>(convert_to<z_i32>(v0), convert_to<z_i32>(v1));
}
#endif
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i64 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepi64_epi8(v);
#else
    return {v.m(0), v.m(1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif
}
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i64 v0, x_i64 v1)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi64_epi8(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi8(x86::concat(detail::concat(v0, v1), zero<__m256i>()));
#else
    return {v0.m(0), v0.m(1), v1.m(0), v1.m(1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif
}
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i64 v0, x_i64 v1, x_i64 v2, x_i64 v3)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi64_epi8(
        detail::concat(detail::concat(v0, v1), detail::concat(v2, v3)));
#else
    return {v0.m(0), v0.m(1), v1.m(0), v1.m(1), v2.m(0), v2.m(1), v3.m(0), v3.m(1),
            0, 0, 0, 0, 0, 0, 0, 0};
#endif
}
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i64 v0, x_i64 v1, x_i64 v2, x_i64 v3,
                                         x_i64 v4, x_i64 v5, x_i64 v6, x_i64 v7)
{
#ifdef Vc_HAVE_AVX512F
    return _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(detail::concat(
                                  detail::concat(v0, v1), detail::concat(v2, v3))),
                              _mm512_cvtepi64_epi8(detail::concat(
                                  detail::concat(v4, v5), detail::concat(v6, v7))));
#else
    return _mm_unpacklo_epi8(
        _mm_unpacklo_epi32(
            _mm_unpacklo_epi16(_mm_unpacklo_epi8(v0, v1), _mm_unpacklo_epi8(v2, v3)),
            _mm_unpacklo_epi16(_mm_unpacklo_epi8(v4, v5), _mm_unpacklo_epi8(v6, v7))),
        _mm_unpacklo_epi32(
            _mm_unpacklo_epi16(_mm_unpackhi_epi8(v0, v1), _mm_unpackhi_epi8(v2, v3)),
            _mm_unpacklo_epi16(_mm_unpackhi_epi8(v4, v5), _mm_unpackhi_epi8(v6, v7))));
#endif
}
#ifdef Vc_HAVE_AVX
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(y_i64 v0, y_i64 v1, y_i64 v2, y_i64 v3)
{
#ifdef Vc_HAVE_AVX512F
    return _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(detail::concat(v0, v1)),
                              _mm512_cvtepi64_epi8(detail::concat(v2, v3)));
#elif defined Vc_HAVE_AVX2
    auto a =
        or_(or_(_mm256_srli_epi32(_mm256_slli_epi32(v0, 24), 24),
                _mm256_srli_epi32(_mm256_slli_epi32(v1, 24), 16)),
            or_(_mm256_srli_epi32(_mm256_slli_epi32(v2, 24), 8),
                _mm256_slli_epi32(v3, 24)));
    auto b = _mm256_unpackhi_epi64(a, a);
    auto c = _mm256_unpacklo_epi8(a, b);
    return _mm_unpacklo_epi16(lo128(c), hi128(c));
#else
    return convert_to<x_i08>(lo128(v0), hi128(v0), lo128(v1), hi128(v1), lo128(v2),
                             hi128(v2), lo128(v3), hi128(v3));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(z_i64 v0)
{
    return _mm512_cvtepi64_epi8(v0);
}
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(z_i64 v0, z_i64 v1)
{
    return _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v0), _mm512_cvtepi64_epi8(v1));
}
#endif
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i32 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepi32_epi8(v);
#elif defined Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(
        x86::concat(x86::concat(v, zero<__m128i>()), zero<__m256i>()));
#elif defined Vc_HAVE_SSSE3
    return _mm_shuffle_epi8(
        v, _mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
                         -0x80, -0x80, -0x80, -0x80, -0x80));
#else
    auto a = _mm_unpacklo_epi8(v, v);
    auto b = _mm_unpackhi_epi8(v, v);
    auto c = _mm_unpacklo_epi8(a, b);
    auto d = _mm_unpackhi_epi8(a, b);
    auto e = _mm_unpacklo_epi8(c, d);
    return detail::and_(e, _mm_cvtsi32_si128(-1));
#endif
}
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i32 v0, x_i32 v1)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi32_epi8(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(x86::concat(detail::concat(v0, v1), zero<__m256i>()));
#elif defined Vc_HAVE_SSSE3
    const auto shufmask = _mm_setr_epi8(0, 4, 8, 12, -0x80, -0x80, -0x80, -0x80, -0x80,
                                        -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80);
    return _mm_unpacklo_epi32(_mm_shuffle_epi8(v0, shufmask),
                              _mm_shuffle_epi8(v1, shufmask));
#else
    auto a = _mm_unpacklo_epi8(v0, v1);
    auto b = _mm_unpackhi_epi8(v0, v1);
    auto c = _mm_unpacklo_epi8(a, b);
    auto d = _mm_unpackhi_epi8(a, b);
    auto e = _mm_unpacklo_epi8(c, d);
    return detail::and_(
        e, _mm_loadl_epi64(reinterpret_cast<const __m128i*>(sse_const::AllBitsSet)));
#endif
}
Vc_INTRINSIC x_i08 Vc_VDECL sse2_convert_to_i08(x_i32 v0, x_i32 v1, x_i32 v2, x_i32 v3)
{
    auto a = _mm_unpacklo_epi8(v0, v2);
    auto b = _mm_unpackhi_epi8(v0, v2);
    auto c = _mm_unpacklo_epi8(v1, v3);
    auto d = _mm_unpackhi_epi8(v1, v3);
    auto e = _mm_unpacklo_epi8(a, c);
    auto f = _mm_unpackhi_epi8(a, c);
    auto g = _mm_unpacklo_epi8(b, d);
    auto h = _mm_unpackhi_epi8(b, d);
    return _mm_unpacklo_epi8(_mm_unpacklo_epi8(e, g),
                             _mm_unpacklo_epi8(f, h)
                             );
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(y_i32 v0, y_i32 v1)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX2
    auto a = _mm256_unpacklo_epi8(v0, v1);
    auto b = _mm256_unpackhi_epi8(v0, v1);
    auto c = _mm256_unpacklo_epi8(a, b);
    auto d = _mm256_unpackhi_epi8(a, b);
    auto e = _mm256_unpacklo_epi8(c, d);
    return _mm_unpacklo_epi32(lo128(e), hi128(e));
#else
    return sse2_convert_to_i08(lo128(v0), hi128(v0), lo128(v1), hi128(v1));
#endif
}
#endif
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i32 v0, x_i32 v1, x_i32 v2, x_i32 v3)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(
        detail::concat(detail::concat(v0, v1), detail::concat(v2, v3)));
#elif defined Vc_HAVE_AVX2
    return convert_to<x_i08>(y_i32(detail::concat(v0, v1)),
                             y_i32(detail::concat(v2, v3)));
#else
    return sse2_convert_to_i08(v0, v1, v2, v3);
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(z_i32 v0)
{
    return _mm512_cvtepi32_epi8(v0);
}
#endif
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i16 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    return _mm_cvtepi16_epi8(v);
#elif defined Vc_HAVE_SSSE3
    auto shuf = load16(sse_const::cvti16_i08_shuffle, vector_aligned);
    return _mm_shuffle_epi8(v, shuf);
#else
    auto a = _mm_unpacklo_epi8(v, v);
    auto b = _mm_unpackhi_epi8(v, v);
    auto c = _mm_unpacklo_epi8(a, b);
    auto d = _mm_unpackhi_epi8(a, b);
    auto e = _mm_unpacklo_epi8(c, d);
    auto f = _mm_unpackhi_epi8(c, d);
    return _mm_unpacklo_epi8(e, f);
#endif
}
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i16 v0, x_i16 v1)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    return _mm256_cvtepi16_epi8(detail::concat(v0, v1));
#elif defined Vc_HAVE_SSSE3
    auto shuf = load16(sse_const::cvti16_i08_shuffle, vector_aligned);
    return _mm_unpacklo_epi64(_mm_shuffle_epi8(v0, shuf), _mm_shuffle_epi8(v1, shuf));
#else
    auto a = _mm_unpacklo_epi8(v0, v1);
    auto b = _mm_unpackhi_epi8(v0, v1);
    auto c = _mm_unpacklo_epi8(a, b);
    auto d = _mm_unpackhi_epi8(a, b);
    auto e = _mm_unpacklo_epi8(c, d);
    auto f = _mm_unpackhi_epi8(c, d);
    return _mm_unpacklo_epi8(e, f);
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(y_i16 v0)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    return _mm256_cvtepi16_epi8(v0);
#elif defined Vc_HAVE_AVX2
    auto a = _mm256_shuffle_epi8(
        v0, _mm256_broadcastsi128_si256(
                load16(sse_const::cvti16_i08_shuffle, vector_aligned)));
    return _mm_unpacklo_epi64(lo128(a), hi128(a));
#else
    auto shuf = load16(sse_const::cvti16_i08_shuffle, vector_aligned);
    return _mm_unpacklo_epi64(_mm_shuffle_epi8(lo128(v0), shuf),
                              _mm_shuffle_epi8(hi128(v0), shuf));
#endif
}
#endif
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_i08 v) { return v; }
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_u08 v) { return v.v(); }
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f32 v)
{
    return convert_to<x_i08>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f32 v0, x_f32 v1)
{
    return convert_to<x_i08>(convert_to<x_i32>(v0), convert_to<x_i32>(v1));
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(y_f32 v0, y_f32 v1)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(_mm512_cvttps_epi32(detail::concat(v0, v1)));
#else
    return convert_to<x_i08>(convert_to<y_i32>(v0), convert_to<y_i32>(v1));
#endif
}
#endif
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f32 v0, x_f32 v1, x_f32 v2, x_f32 v3)
{
#ifdef Vc_HAVE_AVX
    return convert_to<x_i08>(y_f32(x86::concat(v0, v1)), y_f32(x86::concat(v2, v3)));
#else
    return convert_to<x_i08>(convert_to<x_i32>(v0), convert_to<x_i32>(v1),
                             convert_to<x_i32>(v2), convert_to<x_i32>(v3));
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(z_f32 v0)
{
    return _mm512_cvtepi32_epi8(_mm512_cvttps_epi32(v0));
}
#endif
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f64 v)
{
    return convert_to<x_i08>(convert_to<x_i32>(v));
}
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f64 v0, x_f64 v1)
{
    return convert_to<x_i08>(convert_to<x_i32>(v0, v1));
}
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3)
{
    return convert_to<x_i08>(convert_to<x_i32>(v0, v1), convert_to<x_i32>(v2, v3));
}
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3,
                                         x_f64 v4, x_f64 v5, x_f64 v6, x_f64 v7)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(
        x86::concat(_mm512_cvttpd_epi32(
                        detail::concat(detail::concat(v0, v1), detail::concat(v2, v3))),
                    _mm512_cvttpd_epi32(
                        detail::concat(detail::concat(v4, v5), detail::concat(v6, v7)))));
#else
    return convert_to<x_i08>(convert_to<x_i32>(v0, v1), convert_to<x_i32>(v2, v3),
                             convert_to<x_i32>(v4, v5), convert_to<x_i32>(v6, v7));
#endif
}
#ifdef Vc_HAVE_AVX
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(y_f64 v0, y_f64 v1, y_f64 v2, y_f64 v3)
{
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvtepi32_epi8(x86::concat(_mm512_cvttpd_epi32(detail::concat(v0, v1)),
                                            _mm512_cvttpd_epi32(detail::concat(v2, v3))));
#else
    return convert_to<x_i08>(convert_to<y_i32>(v0, v1), convert_to<y_i32>(v2, v3));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(z_f64 v0)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepi32_epi8(_mm512_cvttpd_epi32(v0));
#else
    return _mm512_cvtepi32_epi8(zeroExtend(_mm512_cvttpd_epi32(v0)));
#endif
}
template <>
Vc_INTRINSIC x_i08 Vc_VDECL convert_to<x_i08>(z_f64 v0, z_f64 v1)
{
    return _mm512_cvtepi32_epi8(
        x86::concat(_mm512_cvttpd_epi32(v0), _mm512_cvttpd_epi32(v1)));
}
#endif
#ifdef Vc_HAVE_AVX
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_i64 v0)
{
    return zeroExtend(_mm512_cvtepi64_epi8(v0));
}
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_i64 v0, z_i64 v1)
{
    return zeroExtend(_mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v0), _mm512_cvtepi64_epi8(v1)));
}
template <>
Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_i64 v0, z_i64 v1, z_i64 v2, z_i64 v3)
{
    return x86::concat(
        _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v0), _mm512_cvtepi64_epi8(v1)),
        _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v2), _mm512_cvtepi64_epi8(v3)));
}
#endif
template <>
Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_i64 v0, y_i64 v1, y_i64 v2, y_i64 v3)
{
    return zeroExtend(convert_to<x_i08>(v0, v1, v2, v3));
}
template <>
Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_i64 v0, y_i64 v1, y_i64 v2, y_i64 v3,
                                              y_i64 v4, y_i64 v5, y_i64 v6, y_i64 v7)
{
#ifdef Vc_HAVE_AVX512F
    return convert_to<y_i08>(detail::concat(v0, v1), detail::concat(v2, v3),
                             detail::concat(v4, v5), detail::concat(v6, v7));
#elif defined Vc_HAVE_AVX2
    auto a = or_(
        or_(or_(_mm256_srli_epi64(_mm256_slli_epi64(v0, 56), 56),
                _mm256_srli_epi64(_mm256_slli_epi64(v1, 56), 48)),
            or_(_mm256_srli_epi64(_mm256_slli_epi64(v2, 56), 40),
                _mm256_srli_epi64(_mm256_slli_epi64(v3, 56),
                                  32))),
        or_(or_(_mm256_srli_epi64(_mm256_slli_epi64(v4, 56), 24),
                _mm256_srli_epi64(_mm256_slli_epi64(v5, 56), 16)),
            or_(_mm256_srli_epi64(_mm256_slli_epi64(v6, 56), 8),
                _mm256_slli_epi64(v7, 56)))
        );
    auto b = _mm256_unpackhi_epi64(a, a);
    auto c = _mm256_unpacklo_epi8(a, b);
    return x86::concat(_mm_unpacklo_epi16(lo128(c), hi128(c)),
                       _mm_unpackhi_epi16(lo128(c), hi128(c)));
#else
    return generate_from_n_evaluations<32, y_i08>([&](auto i) {
        using namespace Vc::detail;
        switch (i / 4) {
        case 0: return static_cast<schar>(v0[i % 4]); break;
        case 1: return static_cast<schar>(v1[i % 4]); break;
        case 2: return static_cast<schar>(v2[i % 4]); break;
        case 3: return static_cast<schar>(v3[i % 4]); break;
        case 4: return static_cast<schar>(v4[i % 4]); break;
        case 5: return static_cast<schar>(v5[i % 4]); break;
        case 6: return static_cast<schar>(v6[i % 4]); break;
        case 7: return static_cast<schar>(v7[i % 4]); break;
        }
    });
#endif
}
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_i32 v0, y_i32 v1, y_i32 v2, y_i32 v3)
{
#ifdef Vc_HAVE_AVX512F
    return x86::concat(_mm512_cvtepi32_epi8(detail::concat(v0, v1)),
                       _mm512_cvtepi32_epi8(detail::concat(v2, v3)));
#else
    return detail::concat(convert_to<x_i08>(v0, v1), convert_to<x_i08>(v2, v3));
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_i32 v0, z_i32 v1)
{
    return x86::concat(_mm512_cvtepi32_epi8(v0), _mm512_cvtepi32_epi8(v1));
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_i16 v0)
{
#ifdef Vc_HAVE_AVX512BW
    return _mm512_cvtepi16_epi8(v0);
#else
    const auto mask = _mm512_set1_epi32(0x00ff00ff);
    auto a = and_(v0, mask);
    auto l0 = lo256(a);
    auto h0 = hi256(a);
    auto l1 = _mm256_unpacklo_epi8(l0, h0);
    auto h1 = _mm256_unpackhi_epi8(l0, h0);
    l0 = _mm256_unpacklo_epi8(l1, h1);
    h0 = _mm256_unpackhi_epi8(l1, h1);
    l1 = _mm256_unpacklo_epi8(l0, h0);
    h1 = _mm256_unpackhi_epi8(l0, h0);
    l0 = _mm256_unpacklo_epi8(l1, h1);
    return _mm256_permute4x64_epi64(l0, 0xd8);
#endif
}
#endif
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_i16 v0)
{
    return zeroExtend(convert_to<x_i08>(v0));
}
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_i16 v0, y_i16 v1)
{
#ifdef Vc_HAVE_AVX512F
    return convert_to<y_i08>(detail::concat(v0, v1));
#else
    return detail::concat(convert_to<x_i08>(v0), convert_to<x_i08>(v1));
#endif
}
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_i08 v0) { return v0; }
template <>
Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_f64 v0, y_f64 v1, y_f64 v2, y_f64 v3, y_f64 v4,
                                     y_f64 v5, y_f64 v6, y_f64 v7)
{
    return convert_to<y_i08>(convert_to<y_i32>(v0, v1), convert_to<y_i32>(v2, v3),
                             convert_to<y_i32>(v4, v5), convert_to<y_i32>(v6, v7));
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_f64 v0, z_f64 v1, z_f64 v2, z_f64 v3)
{
    return x86::concat(
        _mm512_cvtepi32_epi8(x86::concat(_mm512_cvttpd_epi32(v0), _mm512_cvttpd_epi32(v1))),
        _mm512_cvtepi32_epi8(x86::concat(_mm512_cvttpd_epi32(v2), _mm512_cvttpd_epi32(v3))));
}
#endif
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(y_f32 v0, y_f32 v1, y_f32 v2, y_f32 v3)
{
    return convert_to<y_i08>(convert_to<y_i32>(v0), convert_to<y_i32>(v1),
                             convert_to<y_i32>(v2), convert_to<y_i32>(v3));
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_i08 Vc_VDECL convert_to<y_i08>(z_f32 v0, z_f32 v1)
{
    return x86::concat(_mm512_cvtepi32_epi8(_mm512_cvttps_epi32(v0)),
                       _mm512_cvtepi32_epi8(_mm512_cvttps_epi32(v1)));
}
#endif
#endif
#ifdef Vc_HAVE_AVX512F
template <>
Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i64 v0, z_i64 v1, z_i64 v2, z_i64 v3,
                                              z_i64 v4, z_i64 v5, z_i64 v6, z_i64 v7)
{
    return x86::concat(
        x86::concat(
            _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v0), _mm512_cvtepi64_epi8(v1)),
            _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v2), _mm512_cvtepi64_epi8(v3))),
        x86::concat(
            _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v4), _mm512_cvtepi64_epi8(v5)),
            _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v6), _mm512_cvtepi64_epi8(v7))));
}
template <>
Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i64 v0, z_i64 v1, z_i64 v2, z_i64 v3)
{
    return zeroExtend(x86::concat(
        _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v0), _mm512_cvtepi64_epi8(v1)),
        _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v2), _mm512_cvtepi64_epi8(v3))));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i64 v0, z_i64 v1)
{
    return zeroExtend(zeroExtend(
        _mm_unpacklo_epi64(_mm512_cvtepi64_epi8(v0), _mm512_cvtepi64_epi8(v1))));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i64 v0)
{
    return zeroExtend(zeroExtend(_mm512_cvtepi64_epi8(v0)));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i32 v0, z_i32 v1, z_i32 v2, z_i32 v3)
{
    return x86::concat(x86::concat(_mm512_cvtepi32_epi8(v0), _mm512_cvtepi32_epi8(v1)),
                       x86::concat(_mm512_cvtepi32_epi8(v2), _mm512_cvtepi32_epi8(v3)));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i32 v0, z_i32 v1)
{
    return zeroExtend(x86::concat(_mm512_cvtepi32_epi8(v0), _mm512_cvtepi32_epi8(v1)));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i32 v0)
{
    return zeroExtend(zeroExtend(_mm512_cvtepi32_epi8(v0)));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i16 v0, z_i16 v1)
{
    return x86::concat(_mm512_cvtepi16_epi8(v0), _mm512_cvtepi16_epi8(v1));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i16 v0)
{
    return zeroExtend(_mm512_cvtepi16_epi8(v0));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_i08 v0) { return v0; }
template <>
Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_f64 v0, z_f64 v1, z_f64 v2, z_f64 v3, z_f64 v4,
                                     z_f64 v5, z_f64 v6, z_f64 v7)
{
    return convert_to<z_i08>(convert_to<z_i32>(v0, v1), convert_to<z_i32>(v2, v3),
                             convert_to<z_i32>(v4, v5), convert_to<z_i32>(v6, v7));
}
template <> Vc_INTRINSIC z_i08 Vc_VDECL convert_to<z_i08>(z_f32 v0, z_f32 v1, z_f32 v2, z_f32 v3)
{
    return convert_to<z_i08>(convert_to<z_i32>(v0), convert_to<z_i32>(v1),
                             convert_to<z_i32>(v2), convert_to<z_i32>(v3));
}
#endif
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_f32 v) { return _mm_cvtps_pd(v); }
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_f64 v) { return v; }
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_i64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvtepi64_pd(v);
#else
    return x_f64{v.m(0), v.m(1)};
#endif
}
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_u64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvtepu64_pd(v);
#else
    return x_f64{v.m(0), v.m(1)};
#endif
}
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_i32 v) { return _mm_cvtepi32_pd(v); }
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_u32 v)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepu32_pd(v);
#elif defined Vc_HAVE_AVX512F
    return lo128(_mm512_cvtepu32_pd(intrin_cast<__m256i>(v)));
#else
    return _mm_add_pd(_mm_cvtepi32_pd(_mm_xor_si128(v, lowest16<int>())),
                      _mm_set1_pd(1u << 31));
#endif
}
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_i16 v) { return convert_to<x_f64>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_u16 v) { return convert_to<x_f64>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_i08 v) { return convert_to<x_f64>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC x_f64 Vc_VDECL convert_to<x_f64>(x_u08 v) { return convert_to<x_f64>(convert_to<x_i32>(v)); }
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_f32 v) { return _mm256_cvtps_pd(v); }
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(y_f64 v) { return v; }
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(y_i64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvtepi64_pd(v);
#else
    return y_f64{v.m(0), v.m(1), v.m(2), v.m(3)};
#endif
}
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(y_u64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvtepu64_pd(v);
#else
    return y_f64{v.m(0), v.m(1), v.m(2), v.m(3)};
#endif
}
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_i32 v) { return _mm256_cvtepi32_pd(v); }
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_u32 v)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepu32_pd(v);
#elif defined Vc_HAVE_AVX512F
    return lo256(_mm512_cvtepu32_pd(intrin_cast<__m256i>(v)));
#else
    return _mm256_add_pd(_mm256_cvtepi32_pd(xor_(v, lowest16<int>())),
                         broadcast32(double(1u << 31)));
#endif
}
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_i16 v) { return convert_to<y_f64>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_u16 v) { return convert_to<y_f64>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_i08 v) { return convert_to<y_f64>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC y_f64 Vc_VDECL convert_to<y_f64>(x_u08 v) { return convert_to<y_f64>(convert_to<x_i32>(v)); }
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_f32 v) { return zeroExtend(_mm256_cvtps_pd(v)); }
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(y_f32 v) { return _mm512_cvtps_pd(v); }
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(z_f64 v) { return v; }
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(z_i64 v0) {
#if defined Vc_HAVE_AVX512DQ
    return _mm512_cvtepi64_pd(v0);
#else
    return _mm512_fmadd_pd(
        _mm512_cvtepi32_pd(_mm512_cvtepi64_epi32(_mm512_srai_epi64(v0, 32))),
        _mm512_set1_pd(0x100000000LL), _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(v0)));
#endif
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(z_u64 v0) {
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_cvtepu64_pd(v0);
#else
    return _mm512_fmadd_pd(
        _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(_mm512_srli_epi64(v0, 32))),
        _mm512_set1_pd(0x100000000LL), _mm512_cvtepu32_pd(_mm512_cvtepi64_epi32(v0)));
#endif
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_i32 v)
{
    return zeroExtend(_mm256_cvtepi32_pd(v));
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(y_i32 v)
{
    return _mm512_cvtepi32_pd(v);
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(z_i32 v)
{
    return _mm512_cvtepi32_pd(lo256(v));
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_u32 v)
{
#ifdef Vc_HAVE_AVX512VL
    return zeroExtend(_mm256_cvtepu32_pd(v));
#else
    return _mm512_cvtepu32_pd(zeroExtend(v));
#endif
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(y_u32 v)
{
    return _mm512_cvtepu32_pd(v);
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(z_u32 v)
{
    return _mm512_cvtepu32_pd(lo256(v));
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_i16 v)
{
    return convert_to<z_f64>(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_u16 v)
{
    return convert_to<z_f64>(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_i08 v)
{
    return _mm512_cvtepi32_pd(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC z_f64 Vc_VDECL convert_to<z_f64>(x_u08 v)
{
    return convert_to<z_f64>(convert_to<y_i32>(v));
}
#endif
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_f32 v) { return v; }
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_f64 v) { return _mm_cvtpd_ps(v); }
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_f64 v0, x_f64 v1)
{
#ifdef Vc_HAVE_AVX
    return _mm256_cvtpd_ps(detail::concat(v0, v1));
#else
    return _mm_movelh_ps(_mm_cvtpd_ps(v0), _mm_cvtpd_ps(v1));
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(y_f64 v0)
{
    return _mm256_cvtpd_ps(v0);
}
#endif
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_i64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvtepi64_ps(v);
#else
    return {v.m(0), v.m(1), 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_i64 v0, x_i64 v1)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvtepi64_ps(detail::concat(v0, v1));
#else
    return {v0.m(0), v0.m(1), v1.m(0), v1.m(1)};
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(y_i64 v0)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvtepi64_ps(v0);
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3)};
#endif
}
#endif
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_u64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_cvtepu64_ps(v);
#else
    return {v.m(0), v.m(1), 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_u64 v0, x_u64 v1)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvtepu64_ps(detail::concat(v0, v1));
#else
    return {v0.m(0), v0.m(1), v1.m(0), v1.m(1)};
#endif
}
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(y_u64 v0)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm256_cvtepu64_ps(v0);
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3)};
#endif
}
#endif
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_i32 v) { return _mm_cvtepi32_ps(v); }
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_u32 v) {
#ifdef Vc_HAVE_AVX512VL
    return _mm_cvtepu32_ps(v);
#else
    return blendv_ps(
        _mm_cvtepi32_ps(v),
        _mm_add_ps(
            _mm_cvtepi32_ps(_mm_and_si128(v, _mm_set1_epi32(0x7ffffe00))),
            _mm_add_ps(_mm_set1_ps(1u << 31),
                       _mm_cvtepi32_ps(_mm_and_si128(v, _mm_set1_epi32(0x000001ff))))),
        _mm_castsi128_ps(_mm_cmplt_epi32(v, _mm_setzero_si128())));
#endif
}
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_i16 v) { return convert_to<x_f32>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_u16 v) { return convert_to<x_f32>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_i08 v) { return convert_to<x_f32>(convert_to<x_i32>(v)); }
template <> Vc_INTRINSIC x_f32 Vc_VDECL convert_to<x_f32>(x_u08 v) { return convert_to<x_f32>(convert_to<x_i32>(v)); }
#ifdef Vc_HAVE_AVX
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_f32 v) { return v; }
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_f64 v)
{
    return zeroExtend(_mm_cvtpd_ps(v));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_f64 v0)
{
    return zeroExtend(_mm256_cvtpd_ps(v0));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_f64 v0, y_f64 v1)
{
#if defined Vc_HAVE_AVX512F
    return _mm512_cvtpd_ps(detail::concat(v0, v1));
#else
    return x86::concat(_mm256_cvtpd_ps(v0), _mm256_cvtpd_ps(v1));
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(z_f64 v0)
{
    return _mm512_cvtpd_ps(v0);
}
#endif
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_i64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm_cvtepi64_ps(v));
#else
    return {v.m(0), v.m(1), 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_i64 v0)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm256_cvtepi64_ps(v0));
#elif defined Vc_HAVE_AVX512DQ
    return _mm512_cvtepi64_ps(zeroExtend(v0));
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3), 0.f, 0.f, 0.f, 0.f};
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(z_i64 v0)
{
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_cvtepi64_ps(v0);
#else
    return _mm512_cvtpd_ps(convert_to<z_f64>(v0));
#endif
}
#endif
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_i64 v0, y_i64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return convert_to<y_f32>(detail::concat(v0, v1));
#elif defined Vc_HAVE_AVX2
    auto a = _mm256_unpacklo_epi32(v0, v1);
    auto b = _mm256_unpackhi_epi32(v0, v1);
    y_u32 lo32 = _mm256_unpacklo_epi32(a, b);
    y_f32 hi16 = _mm256_mul_ps(_mm256_set1_ps(0x10000),
                               _mm256_cvtepi32_ps(_mm256_srli_epi32(lo32, 16)));
    y_f32 lo16 = _mm256_cvtepi32_ps(and_(_mm256_set1_epi32(0x0000ffffu), lo32));
    y_f32 hi32 = _mm256_cvtepi32_ps(_mm256_unpackhi_epi32(a, b));
    const y_f32 scale = _mm256_set1_ps(0x100000000LL);
    y_f32 result = _mm256_add_ps(_mm256_fmadd_ps(hi32, scale, hi16), lo16);
    result = _mm256_castpd_ps(x86::concat(
        _mm_unpacklo_pd(_mm_castps_pd(lo128(result)), _mm_castps_pd(hi128(result))),
        _mm_unpackhi_pd(_mm_castps_pd(lo128(result)), _mm_castps_pd(hi128(result)))));
    return result;
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3), v1.m(0), v1.m(1), v1.m(2), v1.m(3)};
#endif
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_u64 v) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm_cvtepu64_ps(v));
#else
    return {v.m(0), v.m(1), 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
#endif
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_u64 v0)
{
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return zeroExtend(_mm256_cvtepu64_ps(v0));
#elif defined Vc_HAVE_AVX512DQ
    return _mm512_cvtepu64_ps(zeroExtend(v0));
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3), 0.f, 0.f, 0.f, 0.f};
#endif
}
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(z_u64 v0)
{
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_cvtepu64_ps(v0);
#else
    return _mm256_fmadd_ps(
        lo256(_mm512_cvtepu32_ps(intrin_cast<__m512i>(_mm512_cvtepi64_epi32(_mm512_srai_epi64(v0, 32))))),
        _mm256_set1_ps(0x100000000LL),
        lo256(_mm512_cvtepu32_ps(intrin_cast<__m512i>(_mm512_cvtepi64_epi32(v0)))));
#endif
}
#endif
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_u64 v0, y_u64 v1)
{
#ifdef Vc_HAVE_AVX512F
    return convert_to<y_f32>(detail::concat(v0, v1));
#else
    return {v0.m(0), v0.m(1), v0.m(2), v0.m(3), v1.m(0), v1.m(1), v1.m(2), v1.m(3)};
#endif
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_i32 v)
{
    return zeroExtend(_mm_cvtepi32_ps(v));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_i32 v)
{
    return _mm256_cvtepi32_ps(v);
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_u32 v)
{
#ifdef Vc_HAVE_AVX512VL
    return zeroExtend(_mm_cvtepu32_ps(v));
#else
    return zeroExtend(blendv_ps(
        _mm_cvtepi32_ps(v),
        _mm_add_ps(
            _mm_cvtepi32_ps(_mm_and_si128(v, _mm_set1_epi32(0x7ffffe00))),
            _mm_add_ps(_mm_set1_ps(1u << 31),
                       _mm_cvtepi32_ps(_mm_and_si128(v, _mm_set1_epi32(0x000001ff))))),
        _mm_castsi128_ps(_mm_cmplt_epi32(v, _mm_setzero_si128()))));
#endif
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_u32 v)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvtepu32_ps(v);
#elif defined Vc_HAVE_AVX512F
    return lo256(_mm512_cvtepu32_ps(intrin_cast<__m512i>(v)));
#else
    return _mm256_blendv_ps(
        _mm256_cvtepi32_ps(v),
        _mm256_add_ps(
            _mm256_cvtepi32_ps(and_(v, broadcast32(0x7ffffe00))),
            _mm256_add_ps(avx_2_pow_31<float>(),
                          _mm256_cvtepi32_ps(and_(v, broadcast32(0x000001ff))))),
        _mm256_castsi256_ps(
#ifdef Vc_HAVE_AVX2
            _mm256_cmpgt_epi32(y_i32(), v)
#else
            x86::concat(_mm_cmpgt_epi32(x_i32(), lo128(v)),
                        _mm_cmpgt_epi32(x_i32(), hi128(v)))
#endif
                ));
#endif
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_i16 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_i16 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(lo128(v)));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_u16 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_u16 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(lo128(v)));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_i08 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_i08 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(lo128(v)));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(x_u08 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(v));
}
template <> Vc_INTRINSIC y_f32 Vc_VDECL convert_to<y_f32>(y_u08 v)
{
    return convert_to<y_f32>(convert_to<y_i32>(v));
}
#endif
#ifdef Vc_HAVE_AVX512F
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(y_f32 v0, y_f32 v1)
{
    return detail::concat(v0, v1);
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_f32 v) { return v; }
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(y_f64 v)
{
    return zeroExtend64(_mm256_cvtpd_ps(v));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(y_f64 v0, y_f64 v1)
{
    return zeroExtend(_mm512_cvtpd_ps(detail::concat(v0, v1)));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(y_f64 v0, y_f64 v1, y_f64 v2, y_f64 v3)
{
    return x86::concat(_mm512_cvtpd_ps(detail::concat(v0, v1)),
                       _mm512_cvtpd_ps(detail::concat(v2, v3)));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_f64 v0)
{
    return zeroExtend(_mm512_cvtpd_ps(v0));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_f64 v0, z_f64 v1)
{
    return x86::concat(_mm512_cvtpd_ps(v0), _mm512_cvtpd_ps(v1));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_i64 v0)
{
    return zeroExtend(convert_to<y_f32>(v0));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_i64 v0, z_i64 v1)
{
#ifdef Vc_HAVE_AVX512DQ
    return x86::concat(_mm512_cvtepi64_ps(v0), _mm512_cvtepi64_ps(v1));
#else
    z_f32 hi32 =
        _mm512_cvtepi32_ps(x86::concat(_mm512_cvtepi64_epi32(_mm512_srai_epi64(v0, 32)),
                                       _mm512_cvtepi64_epi32(_mm512_srai_epi64(v1, 32))));
    const z_u32 lo32 = x86::concat(_mm512_cvtepi64_epi32(v0), _mm512_cvtepi64_epi32(v1));
    z_f32 hi16 = _mm512_cvtepu32_ps(and_(_mm512_set1_epi32(0xffff0000u), lo32));
    z_f32 lo16 = _mm512_cvtepi32_ps(and_(_mm512_set1_epi32(0x0000ffffu), lo32));
    const z_f32 scale = _mm512_set1_ps(0x100000000LL);
    const z_f32 result = _mm512_add_ps(_mm512_fmadd_ps(hi32, scale, hi16), lo16);
    return result;
#endif
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_u64 v0)
{
    return zeroExtend(convert_to<y_f32>(v0));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_u64 v0, z_u64 v1)
{
#ifdef Vc_HAVE_AVX512DQ
    return x86::concat(_mm512_cvtepu64_ps(v0), _mm512_cvtepu64_ps(v1));
#else
    return _mm512_fmadd_ps(
        _mm512_cvtepu32_ps(x86::concat(_mm512_cvtepi64_epi32(_mm512_srai_epi64(v0, 32)),
                                       _mm512_cvtepi64_epi32(_mm512_srai_epi64(v1, 32)))),
        _mm512_set1_ps(0x100000000LL),
        _mm512_cvtepu32_ps(
            x86::concat(_mm512_cvtepi64_epi32(v0), _mm512_cvtepi64_epi32(v1))));
#endif
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_i32 v0)
{
    return _mm512_cvtepi32_ps(v0);
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(z_u32 v0)
{
    return _mm512_cvtepu32_ps(v0);
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(y_i16 v0)
{
    return convert_to<z_f32>(convert_to<z_i32>(v0));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(y_u16 v0)
{
    return convert_to<z_f32>(convert_to<z_i32>(v0));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(x_i08 v0)
{
    return convert_to<z_f32>(convert_to<z_i32>(v0));
}
template <> Vc_INTRINSIC z_f32 Vc_VDECL convert_to<z_f32>(x_u08 v0)
{
    return convert_to<z_f32>(convert_to<z_i32>(v0));
}
#endif
#endif
template <typename To, size_t N> Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v)
{
    return convert_to<To>(Storage<equal_int_type_t<long>, N>(v));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v0, Storage<long, N> v1)
{
    return convert_to<To>(Storage<equal_int_type_t<long>, N>(v0),
                          Storage<equal_int_type_t<long>, N>(v1));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v0, Storage<long, N> v1, Storage<long, N> v2,
                           Storage<long, N> v3)
{
    return convert_to<To>(
        Storage<equal_int_type_t<long>, N>(v0), Storage<equal_int_type_t<long>, N>(v1),
        Storage<equal_int_type_t<long>, N>(v2), Storage<equal_int_type_t<long>, N>(v3));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v0, Storage<long, N> v1, Storage<long, N> v2,
                           Storage<long, N> v3, Storage<long, N> v4, Storage<long, N> v5,
                           Storage<long, N> v6, Storage<long, N> v7)
{
    return convert_to<To>(
        Storage<equal_int_type_t<long>, N>(v0), Storage<equal_int_type_t<long>, N>(v1),
        Storage<equal_int_type_t<long>, N>(v2), Storage<equal_int_type_t<long>, N>(v3),
        Storage<equal_int_type_t<long>, N>(v4), Storage<equal_int_type_t<long>, N>(v5),
        Storage<equal_int_type_t<long>, N>(v6), Storage<equal_int_type_t<long>, N>(v7));
}
template <typename To, size_t N> Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v)
{
    return convert_to<To>(Storage<equal_int_type_t<ulong>, N>(v));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v0, Storage<ulong, N> v1)
{
    return convert_to<To>(Storage<equal_int_type_t<ulong>, N>(v0),
                          Storage<equal_int_type_t<ulong>, N>(v1));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v0, Storage<ulong, N> v1, Storage<ulong, N> v2,
                           Storage<ulong, N> v3)
{
    return convert_to<To>(
        Storage<equal_int_type_t<ulong>, N>(v0), Storage<equal_int_type_t<ulong>, N>(v1),
        Storage<equal_int_type_t<ulong>, N>(v2), Storage<equal_int_type_t<ulong>, N>(v3));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v0, Storage<ulong, N> v1, Storage<ulong, N> v2,
                           Storage<ulong, N> v3, Storage<ulong, N> v4, Storage<ulong, N> v5,
                           Storage<ulong, N> v6, Storage<ulong, N> v7)
{
    return convert_to<To>(
        Storage<equal_int_type_t<ulong>, N>(v0), Storage<equal_int_type_t<ulong>, N>(v1),
        Storage<equal_int_type_t<ulong>, N>(v2), Storage<equal_int_type_t<ulong>, N>(v3),
        Storage<equal_int_type_t<ulong>, N>(v4), Storage<equal_int_type_t<ulong>, N>(v5),
        Storage<equal_int_type_t<ulong>, N>(v6), Storage<equal_int_type_t<ulong>, N>(v7));
}
struct try_fallback_on_argument {};
template <typename T> struct fallback_int_type { using type = try_fallback_on_argument; };
template <> struct fallback_int_type< uchar> { using type = schar; };
template <> struct fallback_int_type<ushort> { using type = short; };
template <> struct fallback_int_type< uint> { using type = int; };
template <> struct fallback_int_type<ullong> { using type = llong; };
template <> struct fallback_int_type< long> { using type = equal_int_type_t< long>; };
template <> struct fallback_int_type< ulong> { using type = equal_int_type_t<ulong>; };
template <typename T>
using equivalent_storage_t =
    Storage<typename fallback_int_type<typename T::EntryType>::type, T::size()>;
template <typename To, typename From>
Vc_INTRINSIC std::conditional_t<
    (std::is_integral<typename To::EntryType>::value &&
     sizeof(typename To::EntryType) <= sizeof(typename From::EntryType)),
    Storage<std::make_signed_t<typename From::EntryType>, From::size()>, From>
    Vc_VDECL maybe_make_signed(From v)
{
    static_assert(
        std::is_unsigned<typename From::EntryType>::value,
        "maybe_make_signed must only be used with unsigned integral Storage types");
    return std::conditional_t<
        (std::is_integral<typename To::EntryType>::value &&
         sizeof(typename To::EntryType) <= sizeof(typename From::EntryType)),
        Storage<std::make_signed_t<typename From::EntryType>, From::size()>, From>{v};
}
template <typename To,
          typename Fallback = typename fallback_int_type<typename To::EntryType>::type>
struct equivalent_conversion {
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<uchar, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<ushort, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<uint, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<ulong, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<ullong, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <typename F0, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(F0 v0, From... vs)
    {
        static_assert(!std::is_unsigned<typename F0::EntryType>::value, "overload error");
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(v0, vs...).v();
    }
};
template <typename To> struct equivalent_conversion<To, try_fallback_on_argument> {
#ifdef Vc_HAVE_AVX
    template <typename From,
              typename = decltype(detail::concat(declval<From>(), declval<From>()))>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(From v0, From v1)
    {
        return convert_to<To>(detail::concat(v0, v1));
    }
    template <typename From,
              typename = decltype(detail::concat(declval<From>(), declval<From>()))>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(From v0, From v1, From v2, From v3)
    {
        return convert_to<To>(detail::concat(v0, v1), detail::concat(v2, v3));
    }
#endif
    template <typename From, typename... Fs>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(From v0, Fs... vs)
    {
        using F = typename From::value_type;
        using Fallback = typename fallback_int_type<F>::type;
        static_assert(!std::is_same<Fallback, try_fallback_on_argument>::value,
                      "The From & To value types are not usable for a fallback "
                      "conversion. There's a missing implementation for "
                      "convert<To>(From, Fs...)");
        using S = Storage<typename fallback_int_type<F>::type, From::size()>;
        return convert_to<To>(S(v0), S(vs)...);
    }
};
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0, x_f32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0, x_f32 v1, x_f32 v2, x_f32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
#ifdef Vc_HAVE_SSE2
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3, x_f64 v4, x_f64 v5, x_f64 v6, x_f64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i08 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u08 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i16 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i16 v0, x_i16 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u16 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u16 v0, x_u16 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i32 v0, x_i32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i32 v0, x_i32 v1, x_i32 v2, x_i32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32 v0, x_u32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32 v0, x_u32 v1, x_u32 v2, x_u32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64 v0, x_i64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64 v0, x_i64 v1, x_i64 v2, x_i64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_i64 v0, x_i64 v1, x_i64 v2, x_i64 v3, x_i64 v4, x_i64 v5, x_i64 v6, x_i64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64 v0, x_u64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64 v0, x_u64 v1, x_u64 v2, x_u64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u64 v0, x_u64 v1, x_u64 v2, x_u64 v3, x_u64 v4, x_u64 v5, x_u64 v6, x_u64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
#endif
#ifdef Vc_HAVE_AVX
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f32 v0, y_f32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f32 v0, y_f32 v1, y_f32 v2, y_f32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64 v0, y_f64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64 v0, y_f64 v1, y_f64 v2, y_f64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_f64 v0, y_f64 v1, y_f64 v2, y_f64 v3, y_f64 v4, y_f64 v5, y_f64 v6, y_f64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i08 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u08 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i16 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i16 v0, y_i16 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u16 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u16 v0, y_u16 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i32 v0, y_i32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i32 v0, y_i32 v1, y_i32 v2, y_i32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u32 v0, y_u32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u32 v0, y_u32 v1, y_u32 v2, y_u32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64 v0, y_i64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64 v0, y_i64 v1, y_i64 v2, y_i64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_i64 v0, y_i64 v1, y_i64 v2, y_i64 v3, y_i64 v4, y_i64 v5, y_i64 v6, y_i64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64 v0, y_u64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64 v0, y_u64 v1, y_u64 v2, y_u64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(y_u64 v0, y_u64 v1, y_u64 v2, y_u64 v3, y_u64 v4, y_u64 v5, y_u64 v6, y_u64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
#endif
#ifdef Vc_HAVE_AVX512F
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f32 v0, z_f32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f32 v0, z_f32 v1, z_f32 v2, z_f32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64 v0, z_f64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64 v0, z_f64 v1, z_f64 v2, z_f64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_f64 v0, z_f64 v1, z_f64 v2, z_f64 v3, z_f64 v4, z_f64 v5, z_f64 v6, z_f64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i08 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u08 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i16 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i16 v0, z_i16 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u16 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u16 v0, z_u16 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i32 v0, z_i32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i32 v0, z_i32 v1, z_i32 v2, z_i32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u32 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u32 v0, z_u32 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u32 v0, z_u32 v1, z_u32 v2, z_u32 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64 v0, z_i64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64 v0, z_i64 v1, z_i64 v2, z_i64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_i64 v0, z_i64 v1, z_i64 v2, z_i64 v3, z_i64 v4, z_i64 v5, z_i64 v6, z_i64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64 v0) { return equivalent_conversion<To>::convert(v0); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64 v0, z_u64 v1) { return equivalent_conversion<To>::convert(v0, v1); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64 v0, z_u64 v1, z_u64 v2, z_u64 v3) { return equivalent_conversion<To>::convert(v0, v1, v2, v3); }
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(z_u64 v0, z_u64 v1, z_u64 v2, z_u64 v3, z_u64 v4, z_u64 v5, z_u64 v6, z_u64 v7) { return equivalent_conversion<To>::convert(v0, v1, v2, v3, v4, v5, v6, v7); }
#endif
template <typename To, typename... From>
Vc_INTRINSIC To Vc_VDECL convert_to(arithmetic<From>... scalars)
{
    return x86::set(static_cast<typename To::value_type>(scalars)...);
}
template <typename From, typename To> Vc_INTRINSIC To Vc_VDECL convert(From v)
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    constexpr auto N = From::size() < To::size() ? From::size() : To::size();
    return convert_builtin<To>(v.builtin(), std::make_index_sequence<N>());
#else
    return convert_to<To>(v);
#endif
}
template <typename From, typename To> Vc_INTRINSIC To Vc_VDECL convert(From v0, From v1)
{
    static_assert(To::size() >= 2 * From::size(),
                  "convert(v0, v1) requires the input to fit into the output");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return convert_builtin<To>(
        v0.builtin(), v1.builtin(), std::make_index_sequence<From::size()>(),
        std::make_index_sequence<To::size() - 2 * From::size()>());
#else
    return convert_to<To>(v0, v1);
#endif
}
template <typename From, typename To>
Vc_INTRINSIC To Vc_VDECL convert(From v0, From v1, From v2, From v3)
{
    static_assert(To::size() >= 4 * From::size(),
                  "convert(v0, v1, v2, v3) requires the input to fit into the output");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return convert_builtin<To>(
        v0.builtin(), v1.builtin(), v2.builtin(), v3.builtin(),
        std::make_index_sequence<From::size()>(),
        std::make_index_sequence<To::size() - 4 * From::size()>());
#else
    return convert_to<To>(v0, v1, v2, v3);
#endif
}
template <typename From, typename To>
Vc_INTRINSIC To Vc_VDECL convert(From v0, From v1, From v2, From v3, From v4, From v5, From v6,
                        From v7)
{
    static_assert(To::size() >= 8 * From::size(),
                  "convert(v0, v1, v2, v3, v4, v5, v6, v7) "
                  "requires the input to fit into the output");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return convert_builtin<To>(
        v0.builtin(), v1.builtin(), v2.builtin(), v3.builtin(), v4.builtin(),
        v5.builtin(), v6.builtin(), v7.builtin(),
        std::make_index_sequence<From::size()>(),
        std::make_index_sequence<To::size() - 8 * From::size()>());
#else
    return convert_to<To>(v0, v1, v2, v3, v4, v5, v6, v7);
#endif
}
template <typename To, typename From>
Vc_INTRINSIC auto Vc_VDECL convert_all_impl(From v, std::true_type)
{
    constexpr size_t N = From::size() / To::size();
    return generate_from_n_evaluations<N, std::array<To, N>>([&](auto i) {
        using namespace Vc::detail::x86;
#ifdef Vc_MSVC
        constexpr size_t N = From::size() / To::size();
#endif
        auto part = x86::extract_part<decltype(i)::value, N>(v);
        return convert<decltype(part), To>(part);
    });
}
template <typename To, typename From>
Vc_INTRINSIC To Vc_VDECL convert_all_impl(From v, std::false_type)
{
    return convert<From, To>(v);
}
template <typename To, typename From> Vc_INTRINSIC auto Vc_VDECL convert_all(From v)
{
    return convert_all_impl<To, From>(
        v, std::integral_constant<bool, (From::size() > To::size())>());
}
}}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_X86_ARITHMETICS_H_
#define VC_SIMD_X86_ARITHMETICS_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace x86
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> plus(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() + b.builtin();
}
#else
Vc_INTRINSIC __m128 Vc_VDECL plus(x_f32 a, x_f32 b) { return _mm_add_ps(a, b); }
Vc_INTRINSIC __m128d Vc_VDECL plus(x_f64 a, x_f64 b) { return _mm_add_pd(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_i64 a, x_i64 b) { return _mm_add_epi64(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_u64 a, x_u64 b) { return _mm_add_epi64(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_i32 a, x_i32 b) { return _mm_add_epi32(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_u32 a, x_u32 b) { return _mm_add_epi32(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_i16 a, x_i16 b) { return _mm_add_epi16(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_u16 a, x_u16 b) { return _mm_add_epi16(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_i08 a, x_i08 b) { return _mm_add_epi8 (a, b); }
Vc_INTRINSIC __m128i Vc_VDECL plus(x_u08 a, x_u08 b) { return _mm_add_epi8 (a, b); }
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 Vc_VDECL plus(y_f32 a, y_f32 b) { return _mm256_add_ps(a, b); }
Vc_INTRINSIC __m256d Vc_VDECL plus(y_f64 a, y_f64 b) { return _mm256_add_pd(a, b); }
#endif
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC __m256i Vc_VDECL plus(y_i64 a, y_i64 b) { return _mm256_add_epi64(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_u64 a, y_u64 b) { return _mm256_add_epi64(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_i32 a, y_i32 b) { return _mm256_add_epi32(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_u32 a, y_u32 b) { return _mm256_add_epi32(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_i16 a, y_i16 b) { return _mm256_add_epi16(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_u16 a, y_u16 b) { return _mm256_add_epi16(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_i08 a, y_i08 b) { return _mm256_add_epi8 (a, b); }
Vc_INTRINSIC __m256i Vc_VDECL plus(y_u08 a, y_u08 b) { return _mm256_add_epi8 (a, b); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 Vc_VDECL plus(z_f32 a, z_f32 b) { return _mm512_add_ps(a, b); }
Vc_INTRINSIC __m512d Vc_VDECL plus(z_f64 a, z_f64 b) { return _mm512_add_pd(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_i64 a, z_i64 b) { return _mm512_add_epi64(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_u64 a, z_u64 b) { return _mm512_add_epi64(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_i32 a, z_i32 b) { return _mm512_add_epi32(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_u32 a, z_u32 b) { return _mm512_add_epi32(a, b); }
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC __m512i Vc_VDECL plus(z_i16 a, z_i16 b) { return _mm512_add_epi16(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_u16 a, z_u16 b) { return _mm512_add_epi16(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_i08 a, z_i08 b) { return _mm512_add_epi8(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL plus(z_u08 a, z_u08 b) { return _mm512_add_epi8(a, b); }
#endif
#endif
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> minus(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() - b.builtin();
}
#else
Vc_INTRINSIC __m128 Vc_VDECL minus(x_f32 a, x_f32 b) { return _mm_sub_ps(a, b); }
Vc_INTRINSIC __m128d Vc_VDECL minus(x_f64 a, x_f64 b) { return _mm_sub_pd(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_i64 a, x_i64 b) { return _mm_sub_epi64(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_u64 a, x_u64 b) { return _mm_sub_epi64(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_i32 a, x_i32 b) { return _mm_sub_epi32(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_u32 a, x_u32 b) { return _mm_sub_epi32(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_i16 a, x_i16 b) { return _mm_sub_epi16(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_u16 a, x_u16 b) { return _mm_sub_epi16(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_i08 a, x_i08 b) { return _mm_sub_epi8 (a, b); }
Vc_INTRINSIC __m128i Vc_VDECL minus(x_u08 a, x_u08 b) { return _mm_sub_epi8 (a, b); }
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 Vc_VDECL minus(y_f32 a, y_f32 b) { return _mm256_sub_ps(a, b); }
Vc_INTRINSIC __m256d Vc_VDECL minus(y_f64 a, y_f64 b) { return _mm256_sub_pd(a, b); }
#endif
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC __m256i Vc_VDECL minus(y_i64 a, y_i64 b) { return _mm256_sub_epi64(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_u64 a, y_u64 b) { return _mm256_sub_epi64(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_i32 a, y_i32 b) { return _mm256_sub_epi32(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_u32 a, y_u32 b) { return _mm256_sub_epi32(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_i16 a, y_i16 b) { return _mm256_sub_epi16(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_u16 a, y_u16 b) { return _mm256_sub_epi16(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_i08 a, y_i08 b) { return _mm256_sub_epi8 (a, b); }
Vc_INTRINSIC __m256i Vc_VDECL minus(y_u08 a, y_u08 b) { return _mm256_sub_epi8 (a, b); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 Vc_VDECL minus(z_f32 a, z_f32 b) { return _mm512_sub_ps(a, b); }
Vc_INTRINSIC __m512d Vc_VDECL minus(z_f64 a, z_f64 b) { return _mm512_sub_pd(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_i64 a, z_i64 b) { return _mm512_sub_epi64(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_u64 a, z_u64 b) { return _mm512_sub_epi64(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_i32 a, z_i32 b) { return _mm512_sub_epi32(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_u32 a, z_u32 b) { return _mm512_sub_epi32(a, b); }
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC __m512i Vc_VDECL minus(z_i16 a, z_i16 b) { return _mm512_sub_epi16(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_u16 a, z_u16 b) { return _mm512_sub_epi16(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_i08 a, z_i08 b) { return _mm512_sub_epi8(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL minus(z_u08 a, z_u08 b) { return _mm512_sub_epi8(a, b); }
#endif
#endif
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> Vc_VDECL multiplies(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() * b.builtin();
}
#else
Vc_INTRINSIC __m128 Vc_VDECL multiplies(x_f32 a, x_f32 b) { return _mm_mul_ps(a, b); }
Vc_INTRINSIC __m128d Vc_VDECL multiplies(x_f64 a, x_f64 b) { return _mm_mul_pd(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_i64 a, x_i64 b) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_mullo_epi64(a, b);
#else
    return x_i64{a[0] * b[0], a[1] * b[1]};
#endif
}
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_u64 a, x_u64 b) {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
    return _mm_mullo_epi64(a, b);
#else
    return x_u64{a[0] * b[0], a[1] * b[1]};
#endif
}
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_i32 a, x_i32 b) {
#ifdef Vc_HAVE_SSE4_1
    return _mm_mullo_epi32(a, b);
#else
    const __m128i aShift = _mm_srli_si128(a, 4);
    const __m128i ab02 = _mm_mul_epu32(a, b);
    const __m128i bShift = _mm_srli_si128(b, 4);
    const __m128i ab13 = _mm_mul_epu32(aShift, bShift);
    return _mm_unpacklo_epi32(_mm_shuffle_epi32(ab02, 8), _mm_shuffle_epi32(ab13, 8));
#endif
}
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_u32 a, x_u32 b) { return multiplies(x_i32(a), x_i32(b)); }
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_i16 a, x_i16 b) { return _mm_mullo_epi16(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_u16 a, x_u16 b) { return _mm_mullo_epi16(a, b); }
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_i08 a, x_i08 b) {
    return or_(
        and_(_mm_mullo_epi16(a, b), srli_epi16<8>(allone<__m128i>())),
        slli_epi16<8>(_mm_mullo_epi16(_mm_srli_si128(a, 1), _mm_srli_si128(b, 1))));
}
Vc_INTRINSIC __m128i Vc_VDECL multiplies(x_u08 a, x_u08 b) { return multiplies(x_i08(a), x_i08(b)); }
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 Vc_VDECL multiplies(y_f32 a, y_f32 b) { return _mm256_mul_ps(a, b); }
Vc_INTRINSIC __m256d Vc_VDECL multiplies(y_f64 a, y_f64 b) { return _mm256_mul_pd(a, b); }
#endif
#ifdef Vc_HAVE_AVX2
#if defined Vc_HAVE_AVX512DQ && defined Vc_HAVE_AVX512VL
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_i64 a, y_i64 b) { return _mm256_mullo_epi64(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_u64 a, y_u64 b) { return _mm256_mullo_epi64(a, b); }
#else
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_i64 a, y_i64 b) { return y_i64{a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]}; }
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_u64 a, y_u64 b) { return y_u64{a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]}; }
#endif
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_i32 a, y_i32 b) { return _mm256_mullo_epi32(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_u32 a, y_u32 b) { return _mm256_mullo_epi32(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_i16 a, y_i16 b) { return _mm256_mullo_epi16(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_u16 a, y_u16 b) { return _mm256_mullo_epi16(a, b); }
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_i08 a, y_i08 b) {
    return or_(and_(_mm256_mullo_epi16(a, b), srli_epi16<8>(allone<__m256i>())),
               slli_epi16<8>(
                   _mm256_mullo_epi16(_mm256_srli_si256(a, 1), _mm256_srli_si256(b, 1))));
}
Vc_INTRINSIC __m256i Vc_VDECL multiplies(y_u08 a, y_u08 b) { return multiplies(y_i08(a), y_i08(b)); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 Vc_VDECL multiplies(z_f32 a, z_f32 b) { return _mm512_mul_ps(a, b); }
Vc_INTRINSIC __m512d Vc_VDECL multiplies(z_f64 a, z_f64 b) { return _mm512_mul_pd(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_i64 a, z_i64 b) {
#ifdef Vc_HAVE_AVX512DQ
    return _mm512_mullo_epi64(a, b);
#else
    const __m512i r0 = _mm512_mul_epu32(a, b);
    const __m512i aShift = _mm512_srli_epi64(a, 32);
    const __m512i bShift = _mm512_srli_epi64(b, 32);
    const __m512i r1 = _mm512_slli_epi64(_mm512_mul_epu32(aShift, b), 32);
    const __m512i r2 = _mm512_slli_epi64(_mm512_mul_epu32(a, bShift), 32);
    return _mm512_add_epi64(_mm512_add_epi64(r0, r1), r2);
#endif
}
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_u64 a, z_u64 b) { return multiplies(z_i64(a),z_i64(b)); }
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_i32 a, z_i32 b) { return _mm512_mullo_epi32(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_u32 a, z_u32 b) { return _mm512_mullo_epi32(a, b); }
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_i16 a, z_i16 b) { return _mm512_mullo_epi16(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_u16 a, z_u16 b) { return _mm512_mullo_epi16(a, b); }
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_i08 a, z_i08 b) {
    return or_(
        and_(_mm512_mullo_epi16(a, b), _mm512_srli_epi16(allone<__m512i>(), 8)),
        _mm512_slli_epi16(_mm512_mullo_epi16(_mm512_srli_epi16(a, 8), _mm512_srli_epi16(b, 8)), 8));
}
Vc_INTRINSIC __m512i Vc_VDECL multiplies(z_u08 a, z_u08 b) { return multiplies(z_i08(a), z_i08(b)); }
#endif
#endif
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> divides(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() / b.builtin();
}
#else
Vc_INTRINSIC x_f32 Vc_VDECL divides(x_f32 a, x_f32 b) { return _mm_div_ps(a, b); }
Vc_INTRINSIC x_f64 Vc_VDECL divides(x_f64 a, x_f64 b) { return _mm_div_pd(a, b); }
Vc_INTRINSIC x_i64 Vc_VDECL divides(x_i64 a, x_i64 b) { return {a[0] / b[0], a[1] / b[1]}; }
Vc_INTRINSIC x_u64 Vc_VDECL divides(x_u64 a, x_u64 b) { return {a[0] / b[0], a[1] / b[1]}; }
Vc_INTRINSIC x_i32 Vc_VDECL divides(x_i32 a, x_i32 b) {
#ifdef Vc_HAVE_AVX
    return _mm256_cvttpd_epi32(
        _mm256_div_pd(_mm256_cvtepi32_pd(a), _mm256_cvtepi32_pd(b)));
#else
    return {a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]};
#endif
}
Vc_INTRINSIC x_u32 Vc_VDECL divides(x_u32 a, x_u32 b) {
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cvttpd_epu32(
        _mm256_div_pd(_mm256_cvtepu32_pd(a), _mm256_cvtepu32_pd(b)));
#else
    return {a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]};
#endif
}
Vc_INTRINSIC x_i16 Vc_VDECL divides(x_i16 a, x_i16 b) {
    const __m128i mask = broadcast16(0x0000ffffu);
    const auto ahi = andnot_(mask, a);
    const auto bhi = andnot_(mask, b);
    const auto alo = _mm_slli_epi32(a, 16);
    const auto blo = _mm_slli_epi32(b, 16);
#ifdef Vc_HAVE_AVX
    __m256i c = _mm256_cvttps_epi32(_mm256_div_ps(_mm256_cvtepi32_ps(concat(ahi, alo)),
                                                  _mm256_cvtepi32_ps(concat(bhi, blo))));
    return or_(_mm_slli_epi32(lo128(c), 16), and_(mask, hi128(c)));
#else
    __m128i c[2] = {
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(ahi), _mm_cvtepi32_ps(bhi))),
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(alo), _mm_cvtepi32_ps(blo)))};
    return or_(_mm_slli_epi32(c[0], 16), and_(mask, c[1]));
#endif
}
Vc_INTRINSIC x_u16 Vc_VDECL divides(x_u16 a, x_u16 b) {
#ifdef Vc_HAVE_AVX
    return convert<y_f32, x_u16>(
        _mm256_div_ps(convert<x_u16, y_f32>(a), convert<x_u16, y_f32>(b)));
#else
    return or_(
        _mm_slli_epi32(
            _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(_mm_srli_epi32(a, 16)),
                                        _mm_cvtepi32_ps(_mm_srli_epi32(b, 16)))),
            16),
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(and_(a, broadcast16(0xffff))),
                                    _mm_cvtepi32_ps(and_(b, broadcast16(0xffff))))));
#endif
}
inline x_i08 Vc_VDECL divides(x_i08 a, x_i08 b) {
#ifdef Vc_HAVE_AVX512F
    return convert<z_f32, x_i08>(
        _mm512_div_ps(convert<x_i08, z_f32>(a), convert<x_i08, z_f32>(b)));
#else
    const __m128i maskhi = broadcast16(0xff000000u);
    const __m128i masklo = _mm_srli_epi32(maskhi, 24);
    __m128i r[4] = {
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps( _mm_slli_epi32(a, 24) ),
                                    _mm_cvtepi32_ps( _mm_slli_epi32(b, 24) ))),
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(and_(_mm_slli_epi32(a, 16), maskhi)),
                                    _mm_cvtepi32_ps(and_(_mm_slli_epi32(b, 16), maskhi)))),
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(and_(_mm_slli_epi32(a, 8), maskhi)),
                                    _mm_cvtepi32_ps(and_(_mm_slli_epi32(b, 8), maskhi)))),
        _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(and_( a , maskhi)),
                                    _mm_cvtepi32_ps(and_( b , maskhi))))
    };
    r[0] = and_(r[0], masklo);
    r[1] = _mm_slli_epi32(and_(r[1], masklo), 8);
    r[2] = _mm_slli_epi32(and_(r[2], masklo), 16);
    r[3] = _mm_slli_epi32(r[3], 24);
    return or_(or_(r[0], r[1]), or_(r[2], r[3]));
#endif
}
inline x_u08 Vc_VDECL divides(x_u08 a, x_u08 b) {
#ifdef Vc_HAVE_AVX512F
    return convert<z_f32, x_u08>(
        _mm512_div_ps(convert<x_u08, z_f32>(a), convert<x_u08, z_f32>(b)));
#else
    const __m128i mask = broadcast16(0xff);
    return or_(
        or_(_mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(and_(a, mask)),
                                        _mm_cvtepi32_ps(and_(b, mask)))),
            _mm_slli_epi32(_mm_cvttps_epi32(_mm_div_ps(
                               _mm_cvtepi32_ps(and_(_mm_srli_epi32(a, 8), mask)),
                               _mm_cvtepi32_ps(and_(_mm_srli_epi32(b, 8), mask)))),
                           8)),
        or_(_mm_slli_epi32(_mm_cvttps_epi32(_mm_div_ps(
                               _mm_cvtepi32_ps(and_(_mm_srli_epi32(a, 16), mask)),
                               _mm_cvtepi32_ps(and_(_mm_srli_epi32(b, 16), mask)))),
                           16),
            _mm_slli_epi32(
                _mm_cvttps_epi32(_mm_div_ps(_mm_cvtepi32_ps(_mm_srli_epi32(a, 24)),
                                            _mm_cvtepi32_ps(_mm_srli_epi32(b, 24)))),
                24)));
#endif
}
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC y_f32 Vc_VDECL divides(y_f32 a, y_f32 b) { return _mm256_div_ps(a, b); }
Vc_INTRINSIC y_f64 Vc_VDECL divides(y_f64 a, y_f64 b) { return _mm256_div_pd(a, b); }
#endif
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC y_i64 Vc_VDECL divides(y_i64 a, y_i64 b) { return {a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]}; }
Vc_INTRINSIC y_u64 Vc_VDECL divides(y_u64 a, y_u64 b) { return {a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]}; }
Vc_INTRINSIC y_i32 Vc_VDECL divides(y_i32 a, y_i32 b) {
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvttpd_epi32(
        _mm512_div_pd(_mm512_cvtepi32_pd(a), _mm512_cvtepi32_pd(b)));
#else
    return concat(_mm256_cvttpd_epi32(_mm256_div_pd(_mm256_cvtepi32_pd(lo128(a)),
                                                    _mm256_cvtepi32_pd(lo128(b)))),
                  _mm256_cvttpd_epi32(_mm256_div_pd(_mm256_cvtepi32_pd(hi128(a)),
                                                    _mm256_cvtepi32_pd(hi128(b)))));
#endif
}
Vc_INTRINSIC y_u32 Vc_VDECL divides(y_u32 a, y_u32 b) {
#ifdef Vc_HAVE_AVX512F
    return _mm512_cvttpd_epu32(
        _mm512_div_pd(_mm512_cvtepu32_pd(a), _mm512_cvtepu32_pd(b)));
#else
    return concat(convert<y_f64, x_u32>(_mm256_div_pd(convert<x_u32, y_f64>(lo128(a)),
                                                      convert<x_u32, y_f64>(lo128(b)))),
                  convert<y_f64, x_u32>(_mm256_div_pd(convert<x_u32, y_f64>(hi128(a)),
                                                      convert<x_u32, y_f64>(hi128(b)))));
#endif
}
Vc_INTRINSIC y_i16 Vc_VDECL divides(y_i16 a, y_i16 b) {
#ifdef Vc_HAVE_AVX512F
    return convert<z_f32, y_i16>(
        _mm512_div_ps(convert<y_i16, z_f32>(a), convert<y_i16, z_f32>(b)));
#else
    return convert<y_f32, y_i16>(
        _mm256_div_ps(convert<x_i16, y_f32>(lo128(a)), convert<x_i16, y_f32>(lo128(b))),
        _mm256_div_ps(convert<x_i16, y_f32>(hi128(a)), convert<x_i16, y_f32>(hi128(b))));
#endif
}
Vc_INTRINSIC y_u16 Vc_VDECL divides(y_u16 a, y_u16 b) {
#ifdef Vc_HAVE_AVX512F
    return convert<z_f32, y_u16>(
        _mm512_div_ps(convert<y_u16, z_f32>(a), convert<y_u16, z_f32>(b)));
#else
    return convert<y_f32, y_u16>(
        _mm256_div_ps(convert<x_u16, y_f32>(lo128(a)), convert<x_u16, y_f32>(lo128(b))),
        _mm256_div_ps(convert<x_u16, y_f32>(hi128(a)), convert<x_u16, y_f32>(hi128(b))));
#endif
}
Vc_INTRINSIC y_i08 Vc_VDECL divides(y_i08 a, y_i08 b) {
#ifdef Vc_HAVE_AVX512F
    return convert<z_f32, y_i08>(
        _mm512_div_ps(convert<x_i08, z_f32>(lo128(a)), convert<x_i08, z_f32>(lo128(b))),
        _mm512_div_ps(convert<x_i08, z_f32>(hi128(a)), convert<x_i08, z_f32>(hi128(b))));
#else
    return convert<y_f32, y_i08>(
        _mm256_div_ps(convert<x_i08, y_f32>(lo128(a)), convert<x_i08, y_f32>(lo128(b))),
        _mm256_div_ps(convert<x_i08, y_f32>(lo128(_mm256_permute4x64_epi64(a, 0x01))),
                      convert<x_i08, y_f32>(lo128(_mm256_permute4x64_epi64(b, 0x01)))),
        _mm256_div_ps(convert<x_i08, y_f32>(lo128(_mm256_permute4x64_epi64(a, 0x02))),
                      convert<x_i08, y_f32>(lo128(_mm256_permute4x64_epi64(b, 0x02)))),
        _mm256_div_ps(convert<x_i08, y_f32>(lo128(_mm256_permute4x64_epi64(a, 0x03))),
                      convert<x_i08, y_f32>(lo128(_mm256_permute4x64_epi64(b, 0x03)))));
#endif
}
Vc_INTRINSIC y_u08 Vc_VDECL divides(y_u08 a, y_u08 b) {
#ifdef Vc_HAVE_AVX512F
    return convert<z_f32, y_u08>(
        _mm512_div_ps(convert<x_u08, z_f32>(lo128(a)), convert<x_u08, z_f32>(lo128(b))),
        _mm512_div_ps(convert<x_u08, z_f32>(hi128(a)), convert<x_u08, z_f32>(hi128(b))));
#else
    return convert<y_f32, y_u08>(
        _mm256_div_ps(convert<x_u08, y_f32>(lo128(a)), convert<x_u08, y_f32>(lo128(b))),
        _mm256_div_ps(convert<x_u08, y_f32>(lo128(_mm256_permute4x64_epi64(a, 0x01))),
                      convert<x_u08, y_f32>(lo128(_mm256_permute4x64_epi64(b, 0x01)))),
        _mm256_div_ps(convert<x_u08, y_f32>(lo128(_mm256_permute4x64_epi64(a, 0x02))),
                      convert<x_u08, y_f32>(lo128(_mm256_permute4x64_epi64(b, 0x02)))),
        _mm256_div_ps(convert<x_u08, y_f32>(lo128(_mm256_permute4x64_epi64(a, 0x03))),
                      convert<x_u08, y_f32>(lo128(_mm256_permute4x64_epi64(b, 0x03)))));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC z_f32 Vc_VDECL divides(z_f32 a, z_f32 b) { return _mm512_div_ps(a, b); }
Vc_INTRINSIC z_f64 Vc_VDECL divides(z_f64 a, z_f64 b) { return _mm512_div_pd(a, b); }
Vc_INTRINSIC z_i64 Vc_VDECL divides(z_i64 a, z_i64 b) {
    return {a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3],
            a[4] / b[4], a[5] / b[5], a[6] / b[6], a[7] / b[7]};
}
Vc_INTRINSIC z_u64 Vc_VDECL divides(z_u64 a, z_u64 b) {
    return {a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3],
            a[4] / b[4], a[5] / b[5], a[6] / b[6], a[7] / b[7]};
}
Vc_INTRINSIC z_i32 Vc_VDECL divides(z_i32 a, z_i32 b) {
    return concat(_mm512_cvttpd_epi32(_mm512_div_pd(_mm512_cvtepi32_pd(lo256(a)),
                                                    _mm512_cvtepi32_pd(lo256(b)))),
                  _mm512_cvttpd_epi32(_mm512_div_pd(_mm512_cvtepi32_pd(hi256(a)),
                                                    _mm512_cvtepi32_pd(hi256(b)))));
}
Vc_INTRINSIC z_u32 Vc_VDECL divides(z_u32 a, z_u32 b) {
    return concat(_mm512_cvttpd_epu32(_mm512_div_pd(_mm512_cvtepu32_pd(lo256(a)),
                                                    _mm512_cvtepu32_pd(lo256(b)))),
                  _mm512_cvttpd_epu32(_mm512_div_pd(_mm512_cvtepu32_pd(hi256(a)),
                                                    _mm512_cvtepu32_pd(hi256(b)))));
}
Vc_INTRINSIC z_i16 Vc_VDECL divides(z_i16 a, z_i16 b) {
    return convert<z_f32, z_i16>(
        _mm512_div_ps(convert<y_i16, z_f32>(lo256(a)), convert<y_i16, z_f32>(lo256(b))),
        _mm512_div_ps(convert<y_i16, z_f32>(hi256(a)), convert<y_i16, z_f32>(hi256(b))));
}
Vc_INTRINSIC z_u16 Vc_VDECL divides(z_u16 a, z_u16 b) {
    return convert<z_f32, z_u16>(
        _mm512_div_ps(convert<y_u16, z_f32>(lo256(a)), convert<y_u16, z_f32>(lo256(b))),
        _mm512_div_ps(convert<y_u16, z_f32>(hi256(a)), convert<y_u16, z_f32>(hi256(b))));
}
Vc_INTRINSIC z_i08 Vc_VDECL divides(z_i08 a, z_i08 b) {
    return convert<z_f32, z_i08>(
        _mm512_div_ps(convert<x_i08, z_f32>(lo128(a)), convert<x_i08, z_f32>(lo128(b))),
        _mm512_div_ps(convert<x_i08, z_f32>(extract128<1>(a)),
                      convert<x_i08, z_f32>(extract128<1>(b))),
        _mm512_div_ps(convert<x_i08, z_f32>(extract128<2>(a)),
                      convert<x_i08, z_f32>(extract128<2>(b))),
        _mm512_div_ps(convert<x_i08, z_f32>(extract128<3>(a)),
                      convert<x_i08, z_f32>(extract128<3>(b))));
}
Vc_INTRINSIC z_u08 Vc_VDECL divides(z_u08 a, z_u08 b) {
    return convert<z_f32, z_u08>(
        _mm512_div_ps(convert<x_u08, z_f32>(lo128(a)), convert<x_u08, z_f32>(lo128(b))),
        _mm512_div_ps(convert<x_u08, z_f32>(extract128<1>(a)),
                      convert<x_u08, z_f32>(extract128<1>(b))),
        _mm512_div_ps(convert<x_u08, z_f32>(extract128<2>(a)),
                      convert<x_u08, z_f32>(extract128<2>(b))),
        _mm512_div_ps(convert<x_u08, z_f32>(extract128<3>(a)),
                      convert<x_u08, z_f32>(extract128<3>(b))));
}
#endif
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> modulus(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "modulus is only supported for integral types");
    return a.builtin() % b.builtin();
}
#else
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> modulus(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "modulus is only supported for integral types");
    return minus(a, multiplies(divides(a, b), b));
}
#endif
template <size_t N>
Vc_INTRINSIC Storage<float, N> bit_and(Storage<float, N> a, Storage<float, N> b)
{
    return and_(a, b);
}
template <size_t N>
Vc_INTRINSIC Storage<double, N> bit_and(Storage<double, N> a, Storage<double, N> b)
{
    return and_(a, b);
}
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_and(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value,
                  "bit_and is only supported for integral types");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return a.builtin() & b.builtin();
#else
    return and_(a, b);
#endif
}
template <size_t N>
Vc_INTRINSIC Storage<float, N> bit_or(Storage<float, N> a, Storage<float, N> b)
{
    return or_(a, b);
}
template <size_t N>
Vc_INTRINSIC Storage<double, N> bit_or(Storage<double, N> a, Storage<double, N> b)
{
    return or_(a, b);
}
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> bit_or(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value,
                  "bit_or is only supported for integral types");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return a.builtin() | b.builtin();
#else
    return or_(a, b);
#endif
}
template <size_t N>
Vc_INTRINSIC Storage<float, N> bit_xor(Storage<float, N> a, Storage<float, N> b)
{
    return xor_(a, b);
}
template <size_t N>
Vc_INTRINSIC Storage<double, N> bit_xor(Storage<double, N> a, Storage<double, N> b)
{
    return xor_(a, b);
}
template <class T, size_t N> Vc_INTRINSIC Storage<T, N> bit_xor(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value,
                  "bit_xor is only supported for integral types");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return a.builtin() ^ b.builtin();
#else
    return xor_(a, b);
#endif
}
#ifdef __GNUC__
#define Vc_SHIFT_LEFT_CONSTEXPR_8(v_,n_) \
    if (__builtin_constant_p(n_)) { \
        if (n_ == 0) { \
            return v_; \
        } else if (n_ == 1) { \
            return plus(v_, v_); \
        } else if (n_ > 1 && n_ < 8) { \
            const uchar mask = (0xff << n_) & 0xff; \
            return and_(bit_shift_left(Storage<ushort, v_.size() / 2>(v_.v()), n_), \
                        broadcast(mask)); \
        } else { \
            return detail::warn_ub(v_); \
        } \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
#else
#define Vc_SHIFT_LEFT_CONSTEXPR_8(v_,n_) Vc_NOTHING_EXPECTING_SEMICOLON
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_left(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value,
                  "bit_shift_left is only supported for integral types");
    return a.builtin() << b.builtin();
}
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_left(Storage<T, N> a, int b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_left is only supported for integral types");
    return a.builtin() << detail::data(simd<T, abi_for_size_t<T, N>>(b)).builtin();
}
#ifdef Vc_GCC
Vc_INTRINSIC Storage<uchar, 16> bit_shift_left(Storage<uchar, 16> a, int b)
{
    Vc_SHIFT_LEFT_CONSTEXPR_8(a, b);
    const auto mask = xor_(_mm_sll_epi16(_mm_set1_epi16(0xff), _mm_cvtsi32_si128(b)),
                           _mm_set1_epi16(ushort(0xff00u)));
    return and_(_mm_sll_epi16(a, _mm_cvtsi32_si128(b)), mask);
}
Vc_INTRINSIC Storage<schar, 16> bit_shift_left(Storage<schar, 16> a, int b)
{
    Vc_SHIFT_LEFT_CONSTEXPR_8(a, b);
    const auto mask = xor_(_mm_sll_epi16(_mm_set1_epi16(0xff), _mm_cvtsi32_si128(b)),
                           _mm_set1_epi16(ushort(0xff00u)));
    return and_(_mm_sll_epi16(a, _mm_cvtsi32_si128(b)), mask);
}
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC Storage<uchar, 32> bit_shift_left(Storage<uchar, 32> a, int b)
{
    Vc_SHIFT_LEFT_CONSTEXPR_8(a, b);
    const auto mask = xor_(_mm256_sll_epi16(_mm256_set1_epi16(0xff), _mm_cvtsi32_si128(b)),
                           _mm256_set1_epi16(ushort(0xff00u)));
    return and_(_mm256_sll_epi16(a, _mm_cvtsi32_si128(b)), mask);
}
Vc_INTRINSIC Storage<schar, 32> bit_shift_left(Storage<schar, 32> a, int b)
{
    Vc_SHIFT_LEFT_CONSTEXPR_8(a, b);
    const auto mask = xor_(_mm256_sll_epi16(_mm256_set1_epi16(0xff), _mm_cvtsi32_si128(b)),
                           _mm256_set1_epi16(ushort(0xff00u)));
    return and_(_mm256_sll_epi16(a, _mm_cvtsi32_si128(b)), mask);
}
#endif
#endif
#else
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_left(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_left is only supported for integral types");
    return generate_from_n_evaluations<N, Storage<T, N>>(
        [&](auto i) { return a[i] << b[i]; });
}
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_left(Storage<T, N> a, int b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_left is only supported for integral types");
    return generate_from_n_evaluations<N, Storage<T, N>>(
        [&](auto i) { return a[i] << b; });
}
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC x_u08 bit_shift_left(x_u08 a, int b)
{
    Vc_SHIFT_LEFT_CONSTEXPR_8(a, b);
    const uchar mask = (0xff << b) & 0xff;
    return and_(_mm_sll_epi16(a, _mm_cvtsi32_si128(b)), broadcast16(mask));
}
Vc_INTRINSIC x_i08 bit_shift_left(x_i08 a, int b)
{
    return x_i08(bit_shift_left(x_u08(a), b));
}
Vc_INTRINSIC x_u16 bit_shift_left(x_u16 a, int b)
{
#ifdef __GNUC__
    if (__builtin_constant_p(b)) {
        return _mm_slli_epi16(a, b);
    }
#endif
    return _mm_sll_epi16(a, _mm_cvtsi32_si128(b));
}
Vc_INTRINSIC x_i16 bit_shift_left(x_i16 a, int b)
{
#ifdef __GNUC__
    if (__builtin_constant_p(b)) {
        return _mm_slli_epi16(a, b);
    }
#endif
    return _mm_sll_epi16(a, _mm_cvtsi32_si128(b));
}
Vc_INTRINSIC x_u32 bit_shift_left(x_u32 a, int b)
{
#ifdef __GNUC__
    if (__builtin_constant_p(b)) {
        return _mm_slli_epi32(a, b);
    }
#endif
    return _mm_sll_epi32(a, _mm_cvtsi32_si128(b));
}
Vc_INTRINSIC x_i32 bit_shift_left(x_i32 a, int b)
{
#ifdef __GNUC__
    if (__builtin_constant_p(b)) {
        return _mm_slli_epi32(a, b);
    }
#endif
    return _mm_sll_epi32(a, _mm_cvtsi32_si128(b));
}
Vc_INTRINSIC x_u64 bit_shift_left(x_u64 a, int b)
{
#ifdef __GNUC__
    if (__builtin_constant_p(b)) {
        return _mm_slli_epi64(a, b);
    }
#endif
    return _mm_sll_epi64(a, _mm_cvtsi32_si128(b));
}
Vc_INTRINSIC x_i64 bit_shift_left(x_i64 a, int b)
{
#ifdef __GNUC__
    if (__builtin_constant_p(b)) {
        return _mm_slli_epi64(a, b);
    }
#endif
    return _mm_sll_epi64(a, _mm_cvtsi32_si128(b));
}
#endif
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC x_i64 bit_shift_left(x_i64 a, x_i64 b) { return _mm_sllv_epi64(a, b); }
Vc_INTRINSIC x_u64 bit_shift_left(x_u64 a, x_u64 b) { return _mm_sllv_epi64(a, b); }
Vc_INTRINSIC x_i32 bit_shift_left(x_i32 a, x_i32 b) { return _mm_sllv_epi32(a, b); }
Vc_INTRINSIC x_u32 bit_shift_left(x_u32 a, x_u32 b) { return _mm_sllv_epi32(a, b); }
Vc_INTRINSIC y_i64 bit_shift_left(y_i64 a, y_i64 b) { return _mm256_sllv_epi64(a, b); }
Vc_INTRINSIC y_u64 bit_shift_left(y_u64 a, y_u64 b) { return _mm256_sllv_epi64(a, b); }
Vc_INTRINSIC y_i32 bit_shift_left(y_i32 a, y_i32 b) { return _mm256_sllv_epi32(a, b); }
Vc_INTRINSIC y_u32 bit_shift_left(y_u32 a, y_u32 b) { return _mm256_sllv_epi32(a, b); }
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC z_i64 bit_shift_left(z_i64 a, z_i64 b) { return _mm512_sllv_epi64(a, b); }
Vc_INTRINSIC z_u64 bit_shift_left(z_u64 a, z_u64 b) { return _mm512_sllv_epi64(a, b); }
Vc_INTRINSIC z_i32 bit_shift_left(z_i32 a, z_i32 b) { return _mm512_sllv_epi32(a, b); }
Vc_INTRINSIC z_u32 bit_shift_left(z_u32 a, z_u32 b) { return _mm512_sllv_epi32(a, b); }
#endif
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC z_i16 bit_shift_left(z_i16 a, z_i16 b) { return _mm512_sllv_epi16(a, b); }
Vc_INTRINSIC z_u16 bit_shift_left(z_u16 a, z_u16 b) { return _mm512_sllv_epi16(a, b); }
Vc_INTRINSIC y_i08 bit_shift_left(y_i08 a, y_i08 b) { return _mm512_cvtepi16_epi8(_mm512_sllv_epi16(_mm512_cvtepi8_epi16(a), _mm512_cvtepi8_epi16(b))); }
Vc_INTRINSIC y_u08 bit_shift_left(y_u08 a, y_u08 b) { return _mm512_cvtepi16_epi8(_mm512_sllv_epi16(_mm512_cvtepi8_epi16(a), _mm512_cvtepi8_epi16(b))); }
Vc_INTRINSIC z_i08 bit_shift_left(z_i08 a, z_i08 b) { return concat(bit_shift_left(lo256(a), lo256(b)), bit_shift_left(hi256(a), hi256(b))); }
Vc_INTRINSIC z_u08 bit_shift_left(z_u08 a, z_u08 b) { return concat(bit_shift_left(lo256(a), lo256(b)), bit_shift_left(hi256(a), hi256(b))); }
#ifdef Vc_HAVE_AVX512VL
Vc_INTRINSIC y_i16 bit_shift_left(y_i16 a, y_i16 b) { return _mm256_sllv_epi16(a, b); }
Vc_INTRINSIC y_u16 bit_shift_left(y_u16 a, y_u16 b) { return _mm256_sllv_epi16(a, b); }
Vc_INTRINSIC x_i16 bit_shift_left(x_i16 a, x_i16 b) { return _mm_sllv_epi16(a, b); }
Vc_INTRINSIC x_u16 bit_shift_left(x_u16 a, x_u16 b) { return _mm_sllv_epi16(a, b); }
Vc_INTRINSIC x_i08 bit_shift_left(x_i08 a, x_i08 b) { return _mm256_cvtepi16_epi8(_mm256_sllv_epi16(_mm256_cvtepi8_epi16(a), _mm256_cvtepi8_epi16(b))); }
Vc_INTRINSIC x_u08 bit_shift_left(x_u08 a, x_u08 b) { return _mm256_cvtepi16_epi8(_mm256_sllv_epi16(_mm256_cvtepi8_epi16(a), _mm256_cvtepi8_epi16(b))); }
#else
Vc_INTRINSIC y_i16 bit_shift_left(y_i16 a, y_i16 b) { return lo256(_mm512_sllv_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)); }
Vc_INTRINSIC y_u16 bit_shift_left(y_u16 a, y_u16 b) { return lo256(_mm512_sllv_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)); }
Vc_INTRINSIC x_i16 bit_shift_left(x_i16 a, x_i16 b) { return lo128(_mm512_sllv_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)); }
Vc_INTRINSIC x_u16 bit_shift_left(x_u16 a, x_u16 b) { return lo128(_mm512_sllv_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)); }
Vc_INTRINSIC x_i08 bit_shift_left(x_i08 a, x_i08 b) { return lo128(bit_shift_left(y_i08(intrin_cast<__m256i>(a)), y_i08(intrin_cast<__m256i>(b)))); }
Vc_INTRINSIC x_u08 bit_shift_left(x_u08 a, x_u08 b) { return lo128(bit_shift_left(y_u08(intrin_cast<__m256i>(a)), y_u08(intrin_cast<__m256i>(b)))); }
#endif
#else
Vc_INTRINSIC x_i16 bit_shift_left(x_i16 a, x_i16 b)
{
    return _mm_blend_epi16(
        _mm_sllv_epi32(a, and_(b, broadcast(0x0000ffffu))),
        _mm_sllv_epi32(and_(a, broadcast(0xffff0000u)), _mm_srli_epi32(b, 16)), 0xaa);
}
Vc_INTRINSIC x_u16 bit_shift_left(x_u16 a, x_u16 b)
{
    return _mm_blend_epi16(
        _mm_sllv_epi32(a, and_(b, broadcast(0x0000ffffu))),
        _mm_sllv_epi32(and_(a, broadcast(0xffff0000u)), _mm_srli_epi32(b, 16)), 0xaa);
}
Vc_INTRINSIC x_i08 bit_shift_left(x_i08 a, x_i08 b)
{
    a = _mm_blendv_epi8(a, slli_epi16<4>(a), slli_epi16<5>(b));
    a = _mm_blendv_epi8(a, slli_epi16<2>(a), slli_epi16<6>(b));
    return _mm_blendv_epi8(a, _mm_add_epi8(a, a), slli_epi16<7>(b));
}
Vc_INTRINSIC x_u08 bit_shift_left(x_u08 a, x_u08 b)
{
    a = _mm_blendv_epi8(a, and_(slli_epi16<4>(a), broadcast(0xf0f0f0f0u)),
                        slli_epi16<5>(b));
    a = _mm_blendv_epi8(a, and_(slli_epi16<2>(a), broadcast(0xfcfcfcfcu)),
                        slli_epi16<6>(b));
    return _mm_blendv_epi8(a, _mm_add_epi8(a, a), slli_epi16<7>(b));
}
Vc_INTRINSIC y_i16 bit_shift_left(y_i16 a, y_i16 b)
{
    return _mm256_blend_epi16(
        _mm256_sllv_epi32(a, and_(b, broadcast32(0x0000ffffu))),
        _mm256_sllv_epi32(and_(a, broadcast32(0xffff0000u)), _mm256_srli_epi32(b, 16)),
        0xaa);
}
Vc_INTRINSIC y_u16 bit_shift_left(y_u16 a, y_u16 b)
{
    return _mm256_blend_epi16(
        _mm256_sllv_epi32(a, and_(b, broadcast32(0x0000ffffu))),
        _mm256_sllv_epi32(and_(a, broadcast32(0xffff0000u)), _mm256_srli_epi32(b, 16)),
        0xaa);
}
Vc_INTRINSIC y_i08 bit_shift_left(y_i08 a, y_i08 b)
{
    a = _mm256_blendv_epi8(a, slli_epi16<4>(a), slli_epi16<5>(b));
    a = _mm256_blendv_epi8(a, slli_epi16<2>(a), slli_epi16<6>(b));
    return _mm256_blendv_epi8(a, _mm256_add_epi8(a, a), slli_epi16<7>(b));
}
Vc_INTRINSIC y_u08 bit_shift_left(y_u08 a, y_u08 b)
{
    a = _mm256_blendv_epi8(a, and_(slli_epi16<4>(a), broadcast32(0xf0f0f0f0u)),
                           slli_epi16<5>(b));
    a = _mm256_blendv_epi8(a, and_(slli_epi16<2>(a), broadcast32(0xfcfcfcfcu)),
                           slli_epi16<6>(b));
    return _mm256_blendv_epi8(a, _mm256_add_epi8(a, a), slli_epi16<7>(b));
}
#endif
#endif
#endif
#undef Vc_SHIFT_LEFT_CONSTEXPR_8
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_right(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_right is only supported for integral types");
    return a.builtin() >> b.builtin();
}
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_right(Storage<T, N> a, int b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_right is only supported for integral types");
    return a.builtin() >> detail::data(simd<T, abi_for_size_t<T, N>>(b)).builtin();
}
#else
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_right(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_right is only supported for integral types");
    return generate_from_n_evaluations<N, Storage<T, N>>(
        [&](auto i) { return a[i] >> b[i]; });
}
template <class T, size_t N>
Vc_INTRINSIC Storage<T, N> bit_shift_right(Storage<T, N> a, int b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_right is only supported for integral types");
    return generate_from_n_evaluations<N, Storage<T, N>>(
        [&](auto i) { return a[i] >> b; });
}
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC x_i32 bit_shift_right(x_i32 a, x_i32 b) { return _mm_srav_epi32(a, b); }
Vc_INTRINSIC x_u32 bit_shift_right(x_u32 a, x_u32 b) { return _mm_srlv_epi32(a, b); }
Vc_INTRINSIC y_i32 bit_shift_right(y_i32 a, y_i32 b) { return _mm256_srav_epi32(a, b); }
Vc_INTRINSIC y_u32 bit_shift_right(y_u32 a, y_u32 b) { return _mm256_srlv_epi32(a, b); }
#ifdef Vc_HAVE_AVX512VL
Vc_INTRINSIC x_i64 bit_shift_right(x_i64 a, x_i64 b) { return _mm_srav_epi64(a, b); }
Vc_INTRINSIC x_u64 bit_shift_right(x_u64 a, x_u64 b) { return _mm_srlv_epi64(a, b); }
Vc_INTRINSIC y_i64 bit_shift_right(y_i64 a, y_i64 b) { return _mm256_srav_epi64(a, b); }
Vc_INTRINSIC y_u64 bit_shift_right(y_u64 a, y_u64 b) { return _mm256_srlv_epi64(a, b); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC z_i64 bit_shift_right(z_i64 a, z_i64 b) { return _mm512_srav_epi64(a, b); }
Vc_INTRINSIC z_u64 bit_shift_right(z_u64 a, z_u64 b) { return _mm512_srlv_epi64(a, b); }
Vc_INTRINSIC z_i32 bit_shift_right(z_i32 a, z_i32 b) { return _mm512_srav_epi32(a, b); }
Vc_INTRINSIC z_u32 bit_shift_right(z_u32 a, z_u32 b) { return _mm512_srlv_epi32(a, b); }
#endif
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC z_i16 bit_shift_right(z_i16 a, z_i16 b) { return _mm512_srav_epi16(a, b); }
Vc_INTRINSIC z_u16 bit_shift_right(z_u16 a, z_u16 b) { return _mm512_srlv_epi16(a, b); }
Vc_INTRINSIC y_i08 bit_shift_right(y_i08 a, y_i08 b) { return _mm512_cvtepi16_epi8(_mm512_srav_epi16(_mm512_cvtepi8_epi16(a), _mm512_cvtepi8_epi16(b))); }
Vc_INTRINSIC y_u08 bit_shift_right(y_u08 a, y_u08 b)
{
    return _mm512_cvtepi16_epi8(
        _mm512_srlv_epi16(_mm512_cvtepu8_epi16(a), _mm512_cvtepu8_epi16(b)));
}
Vc_INTRINSIC z_i08 bit_shift_right(z_i08 a, z_i08 b) { return concat(bit_shift_right(lo256(a), lo256(b)), bit_shift_right(hi256(a), hi256(b))); }
Vc_INTRINSIC z_u08 bit_shift_right(z_u08 a, z_u08 b) { return concat(bit_shift_right(lo256(a), lo256(b)), bit_shift_right(hi256(a), hi256(b))); }
#ifdef Vc_HAVE_AVX512VL
Vc_INTRINSIC y_i16 bit_shift_right(y_i16 a, y_i16 b) { return _mm256_srav_epi16(a, b); }
Vc_INTRINSIC y_u16 bit_shift_right(y_u16 a, y_u16 b) { return _mm256_srlv_epi16(a, b); }
#else
Vc_INTRINSIC y_i16 bit_shift_right(y_i16 a, y_i16 b) { return lo256(_mm512_srav_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)); }
Vc_INTRINSIC y_u16 bit_shift_right(y_u16 a, y_u16 b) { return lo256(_mm512_srlv_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b)); }
#endif
#else
Vc_INTRINSIC y_i16 bit_shift_right(y_i16 a, y_i16 b)
{
    auto lo32 = _mm256_srli_epi32(
        _mm256_srav_epi32(_mm256_unpacklo_epi16(_mm256_setzero_si256(), a),
                          _mm256_unpacklo_epi16(b, _mm256_setzero_si256())),
        16);
    auto hi32 = _mm256_srli_epi32(
        _mm256_srav_epi32(_mm256_unpackhi_epi16(_mm256_setzero_si256(), a),
                          _mm256_unpackhi_epi16(b, _mm256_setzero_si256())),
        16);
    return _mm256_packus_epi32(lo32, hi32);
}
Vc_INTRINSIC y_u16 bit_shift_right(y_u16 a, y_u16 b)
{
    return _mm256_blend_epi16(_mm256_srlv_epi32(and_(a, broadcast32(0x0000ffffu)),
                                                and_(b, broadcast32(0x0000ffffu))),
                              _mm256_srlv_epi32(a, _mm256_srli_epi32(b, 16)), 0xaa);
}
Vc_INTRINSIC y_i08 bit_shift_right(y_i08 a, y_i08 b)
{
    return convert<y_i32, y_i08>(
        _mm256_srav_epi32(_mm256_cvtepi8_epi32(lo128(a)), _mm256_cvtepi8_epi32(lo128(b))),
        _mm256_srav_epi32(_mm256_cvtepi8_epi32(_mm_unpackhi_epi64(lo128(a), lo128(a))),
                          _mm256_cvtepi8_epi32(_mm_unpackhi_epi64(lo128(b), lo128(b)))),
        _mm256_srav_epi32(_mm256_cvtepi8_epi32(hi128(a)), _mm256_cvtepi8_epi32(hi128(b))),
        _mm256_srav_epi32(_mm256_cvtepi8_epi32(_mm_unpackhi_epi64(hi128(a), hi128(a))),
                          _mm256_cvtepi8_epi32(_mm_unpackhi_epi64(hi128(b), hi128(b)))));
}
Vc_INTRINSIC y_u08 bit_shift_right(y_u08 a, y_u08 b)
{
    a = _mm256_blendv_epi8(a, and_(srli_epi16<4>(a), broadcast32(0x0f0f0f0fu)),
                           slli_epi16<5>(b));
    a = _mm256_blendv_epi8(a, and_(srli_epi16<2>(a), broadcast32(0x3f3f3f3fu)),
                           slli_epi16<6>(b));
    return _mm256_blendv_epi8(a, and_(srli_epi16<1>(a), broadcast32(0x7f7f7f7f)),
                              slli_epi16<7>(b));
}
#endif
#else
Vc_INTRINSIC x_i32 bit_shift_right(x_i32 a, x_i32 b)
{
    const auto r0 = _mm_sra_epi32(a, _mm_unpacklo_epi32(b, _mm_setzero_si128()));
    const auto r1 = _mm_sra_epi32(a, _mm_srli_epi64(b, 32));
    const auto r2 = _mm_sra_epi32(a, _mm_unpackhi_epi32(b, _mm_setzero_si128()));
    const auto r3 = _mm_sra_epi32(a, _mm_srli_si128(b, 12));
#ifdef Vc_HAVE_SSE4_1
    return _mm_blend_epi16(_mm_blend_epi16(r1, r0, 0x3), _mm_blend_epi16(r3, r2, 0x30),
                           0xf0);
#else
    return _mm_unpacklo_epi64(_mm_unpacklo_epi32(r0, _mm_srli_si128(r1, 4)),
                              _mm_unpackhi_epi32(r2, _mm_srli_si128(r3, 4)));
#endif
}
Vc_INTRINSIC x_u32 bit_shift_right(x_u32 a, x_u32 b)
{
    const auto r0 = _mm_srl_epi32(a, _mm_unpacklo_epi32(b, _mm_setzero_si128()));
    const auto r1 = _mm_srl_epi32(a, _mm_srli_epi64(b, 32));
    const auto r2 = _mm_srl_epi32(a, _mm_unpackhi_epi32(b, _mm_setzero_si128()));
    const auto r3 = _mm_srl_epi32(a, _mm_srli_si128(b, 12));
#ifdef Vc_HAVE_SSE4_1
    return _mm_blend_epi16(_mm_blend_epi16(r1, r0, 0x3), _mm_blend_epi16(r3, r2, 0x30),
                           0xf0);
#else
    return _mm_unpacklo_epi64(_mm_unpacklo_epi32(r0, _mm_srli_si128(r1, 4)),
                              _mm_unpackhi_epi32(r2, _mm_srli_si128(r3, 4)));
#endif
}
#endif
#if defined Vc_HAVE_AVX512BW && defined Vc_HAVE_AVX512VL
Vc_INTRINSIC x_i16 bit_shift_right(x_i16 a, x_i16 b) { return _mm_srav_epi16(a, b); }
Vc_INTRINSIC x_u16 bit_shift_right(x_u16 a, x_u16 b) { return _mm_srlv_epi16(a, b); }
#elif defined Vc_HAVE_AVX512BW
Vc_INTRINSIC x_i16 bit_shift_right(x_i16 a, x_i16 b)
{
    return lo128(_mm512_srav_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b));
}
Vc_INTRINSIC x_u16 bit_shift_right(x_u16 a, x_u16 b)
{
    return lo128(_mm512_srlv_epi16(intrin_cast<__m512i>(a), intrin_cast<__m512i>(b));
}
#elif defined Vc_HAVE_AVX2
Vc_INTRINSIC x_i16 bit_shift_right(x_i16 a, x_i16 b)
{
    return x86::convert_to<x_i16>(
        y_i32(_mm256_srav_epi32(convert_to<y_i32>(a), convert_to<y_i32>(b))));
}
Vc_INTRINSIC x_u16 bit_shift_right(x_u16 a, x_u16 b)
{
    return x86::convert_to<x_u16>(
        y_u32(_mm256_srlv_epi32(convert_to<y_u32>(a), convert_to<y_u32>(b))));
}
#elif defined Vc_HAVE_SSE4_1
Vc_INTRINSIC x_i16 bit_shift_right(x_i16 a, x_i16 b)
{
    b = or_(_mm_slli_epi32(b, 4), _mm_slli_epi32(b, 12));
    a = _mm_blendv_epi8(a, _mm_srai_epi16(a, 8), b);
    a = _mm_blendv_epi8(a, _mm_srai_epi16(a, 4), b = _mm_add_epi16(b, b));
    a = _mm_blendv_epi8(a, _mm_srai_epi16(a, 2), b = _mm_add_epi16(b, b));
    return _mm_blendv_epi8(a, _mm_srai_epi16(a, 1), _mm_add_epi16(b, b));
}
Vc_INTRINSIC x_u16 bit_shift_right(x_u16 a, x_u16 b)
{
    b = or_(slli_epi16<4>(b), slli_epi16<12>(b));
    a = _mm_blendv_epi8(a, srli_epi16<8>(a), b);
    a = _mm_blendv_epi8(a, srli_epi16<4>(a), b = _mm_add_epi16(b, b));
    a = _mm_blendv_epi8(a, srli_epi16<2>(a), b = _mm_add_epi16(b, b));
    return _mm_blendv_epi8(a, srli_epi16<1>(a), _mm_add_epi16(b, b));
}
#else
Vc_INTRINSIC x_i16 bit_shift_right(x_i16 a, x_i16 b)
{
    a = blendv_epi8(a, _mm_srai_epi16(a, 8), _mm_cmpgt_epi16(b, broadcast16(0x00070007)));
    a = blendv_epi8(
        a, _mm_srai_epi16(a, 4),
        _mm_cmpgt_epi16(and_(b, broadcast16(0x00040004)), _mm_setzero_si128()));
    a = blendv_epi8(
        a, _mm_srai_epi16(a, 2),
        _mm_cmpgt_epi16(and_(b, broadcast16(0x00020002)), _mm_setzero_si128()));
    return blendv_epi8(
        a, _mm_srai_epi16(a, 1),
        _mm_cmpgt_epi16(and_(b, broadcast16(0x00010001)), _mm_setzero_si128()));
}
Vc_INTRINSIC x_u16 bit_shift_right(x_u16 a, x_u16 b)
{
    a = blendv_epi8(a, srli_epi16<8>(a), _mm_cmpgt_epi16(b, broadcast16(0x00070007)));
    a = blendv_epi8(
        a, srli_epi16<4>(a),
        _mm_cmpgt_epi16(and_(b, broadcast16(0x00040004)), _mm_setzero_si128()));
    a = blendv_epi8(
        a, srli_epi16<2>(a),
        _mm_cmpgt_epi16(and_(b, broadcast16(0x00020002)), _mm_setzero_si128()));
    return blendv_epi8(
        a, srli_epi16<1>(a),
        _mm_cmpgt_epi16(and_(b, broadcast16(0x00010001)), _mm_setzero_si128()));
}
#endif
#if defined Vc_HAVE_AVX512BW && defined Vc_HAVE_AVX512VL
Vc_INTRINSIC x_i08 bit_shift_right(x_i08 a, x_i08 b)
{
    return _mm256_cvtepi16_epi8(
        _mm256_srav_epi16(_mm256_cvtepi8_epi16(a), _mm256_cvtepi8_epi16(b)));
}
Vc_INTRINSIC x_u08 bit_shift_right(x_u08 a, x_u08 b)
{
    return _mm256_cvtepi16_epi8(
        _mm256_srlv_epi16(_mm256_cvtepu8_epi16(a), _mm256_cvtepu8_epi16(b)));
}
#elif defined Vc_HAVE_AVX512BW
Vc_INTRINSIC x_i08 bit_shift_right(x_i08 a, x_i08 b)
{
    return lo128(
        bit_shift_right(y_i08(intrin_cast<__m256i>(a)), y_i08(intrin_cast<__m256i>(b))));
}
Vc_INTRINSIC x_u08 bit_shift_right(x_u08 a, x_u08 b)
{
    return lo128(
        bit_shift_right(y_u08(intrin_cast<__m256i>(a)), y_u08(intrin_cast<__m256i>(b))));
}
#elif defined Vc_HAVE_SSE4_1
Vc_INTRINSIC x_i08 bit_shift_right(x_i08 a, x_i08 b)
{
    auto bit7 = and_(a, broadcast16(0x00800080));
    _mm_srai_epi16(slli_epi16<8>(a), 4);
    a = _mm_blendv_epi8(a,
                        _mm_srai_epi16(or_(_mm_sub_epi16(slli_epi16<5>(bit7), bit7),
                                           and_(a, broadcast16(0xf8f8f8f8u))),
                                       4),
                        slli_epi16<5>(b));
    a = _mm_blendv_epi8(a,
                        _mm_srai_epi16(or_(_mm_sub_epi16(slli_epi16<3>(bit7), bit7),
                                           and_(a, broadcast16(0xfcfcfcfcu))),
                                       2),
                        slli_epi16<6>(b));
    return _mm_blendv_epi8(
        a, _mm_srai_epi16(or_(slli_epi16<1>(bit7), and_(a, broadcast16(0xfefefefeu))),
                          1),
        slli_epi16<7>(b));
}
Vc_INTRINSIC x_u08 bit_shift_right(x_u08 a, x_u08 b)
{
    a = _mm_blendv_epi8(a, and_(srli_epi16<4>(a), broadcast16(0x0f0f0f0fu)),
                        slli_epi16<5>(b));
    a = _mm_blendv_epi8(a, and_(srli_epi16<2>(a), broadcast16(0x3f3f3f3fu)),
                        slli_epi16<6>(b));
    return _mm_blendv_epi8(a, and_(srli_epi16<1>(a), broadcast16(0x7f7f7f7f)),
                           slli_epi16<7>(b));
}
#endif
#endif
template <typename T> Vc_INTRINSIC T Vc_VDECL complement(T v) {
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return ~v.builtin();
#else
    return not_(v);
#endif
}
template <typename T> Vc_INTRINSIC T Vc_VDECL unary_minus(T v) { return minus(T{}, v); }
Vc_INTRINSIC __m128 Vc_VDECL unary_minus(x_f32 v) { return xor_(v, signmask16(float())); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d Vc_VDECL unary_minus(x_f64 v) { return xor_(v, signmask16(double())); }
#endif
#ifdef Vc_HAVE_SSSE3
Vc_INTRINSIC __m128i Vc_VDECL unary_minus(x_i32 v) { return _mm_sign_epi32(v, allone<__m128i>()); }
Vc_INTRINSIC __m128i Vc_VDECL unary_minus(x_u32 v) { return _mm_sign_epi32(v, allone<__m128i>()); }
Vc_INTRINSIC __m128i Vc_VDECL unary_minus(x_i16 v) { return _mm_sign_epi16(v, allone<__m128i>()); }
Vc_INTRINSIC __m128i Vc_VDECL unary_minus(x_u16 v) { return _mm_sign_epi16(v, allone<__m128i>()); }
Vc_INTRINSIC __m128i Vc_VDECL unary_minus(x_i08 v) { return _mm_sign_epi8 (v, allone<__m128i>()); }
Vc_INTRINSIC __m128i Vc_VDECL unary_minus(x_u08 v) { return _mm_sign_epi8 (v, allone<__m128i>()); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 Vc_VDECL unary_minus(y_f32 v) { return xor_(v, signmask32(float())); }
Vc_INTRINSIC __m256d Vc_VDECL unary_minus(y_f64 v) { return xor_(v, signmask32(double())); }
#endif
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC __m256i Vc_VDECL unary_minus(y_i32 v) { return _mm256_sign_epi32(v, allone<__m256i>()); }
Vc_INTRINSIC __m256i Vc_VDECL unary_minus(y_u32 v) { return _mm256_sign_epi32(v, allone<__m256i>()); }
Vc_INTRINSIC __m256i Vc_VDECL unary_minus(y_i16 v) { return _mm256_sign_epi16(v, allone<__m256i>()); }
Vc_INTRINSIC __m256i Vc_VDECL unary_minus(y_u16 v) { return _mm256_sign_epi16(v, allone<__m256i>()); }
Vc_INTRINSIC __m256i Vc_VDECL unary_minus(y_i08 v) { return _mm256_sign_epi8 (v, allone<__m256i>()); }
Vc_INTRINSIC __m256i Vc_VDECL unary_minus(y_u08 v) { return _mm256_sign_epi8 (v, allone<__m256i>()); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 Vc_VDECL unary_minus(z_f32 v) { return xor_(v, signmask64(float())); }
Vc_INTRINSIC __m512d Vc_VDECL unary_minus(z_f64 v) { return xor_(v, signmask64(double())); }
#endif
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC Vc_CONST __m128i abs(x_i08 a)
{
#ifdef Vc_HAVE_SSSE3
    return _mm_abs_epi8(a);
#else
    __m128i negative = _mm_cmplt_epi8(a, _mm_setzero_si128());
    return _mm_add_epi8(_mm_xor_si128(a, negative),
                        _mm_and_si128(negative, setone_epi8()));
#endif
}
Vc_INTRINSIC Vc_CONST __m128i abs(x_i16 a)
{
#ifdef Vc_HAVE_SSSE3
    return _mm_abs_epi16(a);
#else
    __m128i negative = _mm_cmplt_epi16(a, _mm_setzero_si128());
    return _mm_add_epi16(_mm_xor_si128(a, negative), srli_epi16<15>(negative));
#endif
}
Vc_INTRINSIC Vc_CONST __m128i abs(x_i32 a)
{
#ifdef Vc_HAVE_SSSE3
    return _mm_abs_epi32(a);
#else
    __m128i negative = _mm_cmplt_epi32(a, _mm_setzero_si128());
    return _mm_add_epi32(_mm_xor_si128(a, negative), _mm_srli_epi32(negative, 31));
#endif
}
Vc_INTRINSIC Vc_CONST __m128i abs(x_i64 a)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm_abs_epi64(a);
#else
#if defined Vc_HAVE_SSE4_2
    __m128i negative = _mm_cmpgt_epi64(_mm_setzero_si128(), a);
#else
    __m128i negative =
        _mm_sub_epi64(xor_(_mm_srli_epi64(a, 63),
                           _mm_set1_epi64x(1)),
                      _mm_set1_epi64x(1));
#endif
    return _mm_add_epi64(xor_(a, negative), _mm_srli_epi64(a, 63));
#endif
}
#endif
Vc_INTRINSIC __m128 abs(x_f32 a) { return and_(a, setabsmask_ps_16()); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d abs(x_f64 a) { return and_(a, setabsmask_pd_16()); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 abs(y_f32 a) { return and_(a, setabsmask_ps_32()); }
Vc_INTRINSIC __m256d abs(y_f64 a) { return and_(a, setabsmask_pd_32()); }
#endif
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC Vc_CONST __m256i abs(y_i08 a) { return _mm256_abs_epi8(a); }
Vc_INTRINSIC Vc_CONST __m256i abs(y_i16 a) { return _mm256_abs_epi16(a); }
Vc_INTRINSIC Vc_CONST __m256i abs(y_i32 a) { return _mm256_abs_epi32(a); }
Vc_INTRINSIC Vc_CONST __m256i abs(y_i64 a)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_abs_epi64(a);
#else
    __m256i negative = _mm256_cmpgt_epi64(_mm256_setzero_si256(), a);
    return _mm256_add_epi64(xor_(a, negative), _mm256_srli_epi64(a, 63));
#endif
}
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 abs(z_f32 a) { return and_(a, setabsmask_ps_64()); }
Vc_INTRINSIC __m512d abs(z_f64 a) { return and_(a, setabsmask_pd_64()); }
#ifdef Vc_HAVE_AVX512BW
Vc_INTRINSIC Vc_CONST __m512i abs(z_i08 a) { return _mm512_abs_epi8(a); }
Vc_INTRINSIC Vc_CONST __m512i abs(z_i16 a) { return _mm512_abs_epi16(a); }
#endif
Vc_INTRINSIC Vc_CONST __m512i abs(z_i32 a) { return _mm512_abs_epi32(a); }
Vc_INTRINSIC Vc_CONST __m512i abs(z_i64 a) { return _mm512_abs_epi64(a); }
#endif
Vc_INTRINSIC __m128 Vc_VDECL sqrt(x_f32 v) { return _mm_sqrt_ps(v); }
#ifdef Vc_HAVE_SSE2
Vc_INTRINSIC __m128d Vc_VDECL sqrt(x_f64 v) { return _mm_sqrt_pd(v); }
#endif
#ifdef Vc_HAVE_AVX
Vc_INTRINSIC __m256 Vc_VDECL sqrt(y_f32 v) { return _mm256_sqrt_ps(v); }
Vc_INTRINSIC __m256d Vc_VDECL sqrt(y_f64 v) { return _mm256_sqrt_pd(v); }
#endif
#ifdef Vc_HAVE_AVX512F
Vc_INTRINSIC __m512 Vc_VDECL sqrt(z_f32 v) { return _mm512_sqrt_ps(v); }
Vc_INTRINSIC __m512d Vc_VDECL sqrt(z_f64 v) { return _mm512_sqrt_pd(v); }
#endif
}}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_MASKBOOL_H_
#define VC_SIMD_MASKBOOL_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace
{
    template<size_t Bytes> struct MaskBoolStorage;
    template<> struct MaskBoolStorage<1> { typedef std::int8_t type; };
    template<> struct MaskBoolStorage<2> { typedef std::int16_t type; };
    template<> struct MaskBoolStorage<4> { typedef std::int32_t type; };
    template<> struct MaskBoolStorage<8> { typedef std::int64_t type; };
}
template<size_t Bytes> class MaskBool
{
    typedef typename MaskBoolStorage<Bytes>::type storage_type Vc_MAY_ALIAS;
    storage_type data;
public:
    constexpr MaskBool(bool x) noexcept : data(x ? -1 : 0) {}
    Vc_ALWAYS_INLINE MaskBool &operator=(bool x) noexcept { data = x ? -1 : 0; return *this; }
    template <typename T, typename = enable_if<(!std::is_same<T, bool>::value &&
                                                std::is_fundamental<T>::value)>>
    Vc_ALWAYS_INLINE MaskBool &operator=(T x) noexcept
    {
        data = reinterpret_cast<const storage_type &>(x);
        return *this;
    }
    Vc_ALWAYS_INLINE MaskBool(const MaskBool &) noexcept = default;
    Vc_ALWAYS_INLINE MaskBool &operator=(const MaskBool &) noexcept = default;
#ifdef Vc_ICC
    template <typename T, typename = enable_if<(std::is_same<T, bool>::value ||
                                                (std::is_fundamental<T>::value &&
                                                 sizeof(storage_type) == sizeof(T)))>>
    constexpr operator T() const noexcept
    {
        return std::is_same<T, bool>::value ? T((data & 1) != 0)
                                            : reinterpret_cast<const may_alias<T> &>(data);
    }
#else
    constexpr operator bool() const noexcept { return (data & 1) != 0; }
    constexpr operator storage_type() const noexcept { return data; }
    template <typename T, typename = enable_if<(std::is_fundamental<T>::value &&
                                                sizeof(storage_type) == sizeof(T))>>
    constexpr operator T() const noexcept
    {
        return reinterpret_cast<const may_alias<T> &>(data);
    }
#endif
#ifdef Vc_MSVC
};
#define friend template<size_t N>
#define MaskBool MaskBool<N>
#endif
    friend constexpr bool operator==(bool a, MaskBool &&b)
    {
        return a == static_cast<bool>(b);
    }
    friend constexpr bool operator==(bool a, const MaskBool &b)
    {
        return a == static_cast<bool>(b);
    }
    friend constexpr bool operator==(MaskBool &&b, bool a)
    {
        return static_cast<bool>(a) == static_cast<bool>(b);
    }
    friend constexpr bool operator==(const MaskBool &b, bool a)
    {
        return static_cast<bool>(a) == static_cast<bool>(b);
    }
    friend constexpr bool operator!=(bool a, MaskBool &&b)
    {
        return a != static_cast<bool>(b);
    }
    friend constexpr bool operator!=(bool a, const MaskBool &b)
    {
        return a != static_cast<bool>(b);
    }
    friend constexpr bool operator!=(MaskBool &&b, bool a)
    {
        return a != static_cast<bool>(b);
    }
    friend constexpr bool operator!=(const MaskBool &b, bool a)
    {
        return a != static_cast<bool>(b);
    }
#ifdef Vc_MSVC
#undef friend
#undef MaskBool
#else
} Vc_MAY_ALIAS;
#endif
static_assert(true == MaskBool<4>(true), "true == MaskBool<4>(true)");
static_assert(MaskBool<4>(true) == true, "true == MaskBool<4>(true)");
static_assert(true != MaskBool<4>(false), "true != MaskBool<4>(false)");
static_assert(MaskBool<4>(false) != true, "true != MaskBool<4>(false)");
namespace tests
{
namespace
{
struct A { constexpr operator int() const { return 1; } };
static_assert(!(A() == 2), "MaskBools operator== was incorrectly found and used");
}
}
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_GENERICIMPL_H_
#define VC_SIMD_GENERICIMPL_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail {
template <class Derived> struct generic_simd_impl {
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T, size_t N>
    static Vc_INTRINSIC auto Vc_VDECL simd(Storage<T, N> x)
    {
        return Derived::make_simd(x);
    }
    template <size_t Size>
    static Vc_INTRINSIC Storage<equal_int_type_t<long>, Size> Vc_VDECL
    adjust_for_long(Storage<long, Size> x)
    {
        return {x.v()};
    }
    template <size_t Size>
    static Vc_INTRINSIC Storage<equal_int_type_t<ulong>, Size> Vc_VDECL
    adjust_for_long(Storage<ulong, Size> x)
    {
        return {x.v()};
    }
    template <class T, size_t Size>
    static Vc_INTRINSIC const Storage<T, Size> &adjust_for_long(const Storage<T, Size> &x)
    {
        return x;
    }
    template <class F, class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> generator(F &&gen, type_tag<T>, size_tag<N>)
    {
        return detail::generate_from_n_evaluations<N, Storage<T, N>>(
            [&gen](auto element_idx_) { return gen(element_idx_); });
    }
    template <class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> complement(Storage<T, N> x) noexcept
    {
        return static_cast<typename Storage<T, N>::VectorType>(
            detail::x86::complement(adjust_for_long(x)));
    }
    template <class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> unary_minus(Storage<T, N> x) noexcept
    {
        using detail::x86::unary_minus;
        return static_cast<typename Storage<T, N>::VectorType>(
            unary_minus(adjust_for_long(x)));
    }
#define Vc_ARITHMETIC_OP_(name_) \
    template <size_t N> \
    static Vc_INTRINSIC Storage<long, N> Vc_VDECL name_(Storage<long, N> x, \
                                                        Storage<long, N> y) \
    { \
        using Adjusted = detail::Storage<equal_int_type_t<long>, N>; \
        return static_cast<typename Adjusted::VectorType>( \
            detail::name_(Adjusted(x.v()), Adjusted(y.v()))); \
    } \
    template <size_t N> \
    static Vc_INTRINSIC Storage<unsigned long, N> Vc_VDECL name_( \
        Storage<unsigned long, N> x, Storage<unsigned long, N> y) \
    { \
        using Adjusted = detail::Storage<equal_int_type_t<unsigned long>, N>; \
        return static_cast<typename Adjusted::VectorType>( \
            detail::name_(Adjusted(x.v()), Adjusted(y.v()))); \
    } \
    template <class T, size_t N> \
    static Vc_INTRINSIC Storage<T, N> Vc_VDECL name_(Storage<T, N> x, Storage<T, N> y) \
    { \
        return detail::name_(x, y); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
        Vc_ARITHMETIC_OP_(plus);
        Vc_ARITHMETIC_OP_(minus);
        Vc_ARITHMETIC_OP_(multiplies);
        Vc_ARITHMETIC_OP_(divides);
        Vc_ARITHMETIC_OP_(modulus);
        Vc_ARITHMETIC_OP_(bit_and);
        Vc_ARITHMETIC_OP_(bit_or);
        Vc_ARITHMETIC_OP_(bit_xor);
        Vc_ARITHMETIC_OP_(bit_shift_left);
        Vc_ARITHMETIC_OP_(bit_shift_right);
#undef Vc_ARITHMETIC_OP_
    template <class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> Vc_VDECL bit_shift_left(Storage<T, N> x, int y)
    {
        return static_cast<typename Storage<T, N>::VectorType>(
            detail::bit_shift_left(adjust_for_long(x), y));
    }
    template <class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> Vc_VDECL bit_shift_right(Storage<T, N> x, int y)
    {
        return static_cast<typename Storage<T, N>::VectorType>(
            detail::bit_shift_right(adjust_for_long(x), y));
    }
    template <class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> sqrt(Storage<T, N> x) noexcept
    {
        using detail::x86::sqrt;
        return sqrt(adjust_for_long(x));
    }
    template <class T, size_t N>
    static Vc_INTRINSIC Storage<T, N> abs(Storage<T, N> x) noexcept
    {
        using detail::x86::abs;
        return abs(adjust_for_long(x));
    }
    template <class T, size_t N> static Vc_INTRINSIC void increment(Storage<T, N> &x)
    {
        x = plus(x, Storage<T, N>(Derived::broadcast(T(1), size_tag<N>())));
    }
    template <class T, size_t N> static Vc_INTRINSIC void decrement(Storage<T, N> &x)
    {
        x = minus(x, Storage<T, N>(Derived::broadcast(T(1), size_tag<N>())));
    }
    template <class T, class K, size_t N>
    static Vc_INTRINSIC void Vc_VDECL masked_assign(Storage<K, N> k, Storage<T, N> &lhs,
                                             detail::id<Storage<T, N>> rhs)
    {
        lhs = detail::x86::blend(k, lhs, rhs);
    }
    template <class T, class K, size_t N>
    static Vc_INTRINSIC void Vc_VDECL masked_assign(Storage<K, N> k, Storage<T, N> &lhs,
                                                    detail::id<T> rhs)
    {
#ifdef __GNUC__
        if (__builtin_constant_p(rhs) && rhs == 0 && std::is_same<K, T>::value) {
            lhs = x86::andnot_(k, lhs);
            return;
        }
#endif
        lhs =
            detail::x86::blend(k, lhs, x86::broadcast(rhs, size_constant<sizeof(lhs)>()));
    }
    template <template <typename> class Op, class T, class K, size_t N>
    static Vc_INTRINSIC void Vc_VDECL masked_cassign(const Storage<K, N> k,
                                                     Storage<T, N> &lhs,
                                                     const detail::id<Storage<T, N>> rhs)
    {
        lhs = detail::x86::blend(k, lhs,
                                 detail::data(Op<void>{}(simd(lhs), simd(rhs))));
    }
    template <template <typename> class Op, class T, class K, size_t N>
    static Vc_INTRINSIC void Vc_VDECL masked_cassign(const Storage<K, N> k,
                                                     Storage<T, N> &lhs,
                                                     const detail::id<T> rhs)
    {
        lhs = detail::x86::blend(
            k, lhs,
            detail::data(Op<void>{}(
                simd(lhs), simd<T, N>(Derived::broadcast(rhs, size_tag<N>())))));
    }
    template <template <typename> class Op, class T, class K, size_t N>
    static Vc_INTRINSIC Storage<T, N> Vc_VDECL masked_unary(const Storage<K, N> k,
                                                            const Storage<T, N> v)
    {
        auto vv = simd(v);
        Op<decltype(vv)> op;
        return detail::x86::blend(k, v, detail::data(op(vv)));
    }
};
template <class abi, template <class> class mask_member_type> struct generic_mask_impl {
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    template <class T, size_t N, class F>
    static inline void Vc_VDECL masked_load(Storage<T, N> &merge, Storage<T, N> mask,
                                            const bool *mem, F) noexcept
    {
        detail::execute_n_times<N>([&](auto i) {
            if (mask[i]) {
                merge.set(i, MaskBool<sizeof(T)>{mem[i]});
            }
        });
    }
    template <class T, size_t N, class F>
    static inline void Vc_VDECL masked_store(const Storage<T, N> v, bool *mem, F,
                                             const Storage<T, N> k) noexcept
    {
        detail::execute_n_times<N>([&](auto i) {
            if (k[i]) {
                mem[i] = v[i];
            }
        });
    }
    template <class T, size_t N>
    static Vc_INTRINSIC std::bitset<N> to_bitset(Storage<T, N> v) noexcept
    {
        static_assert(N <= sizeof(uint) * CHAR_BIT,
                      "Needs missing 64-bit implementation");
        if constexpr (std::is_integral_v<T> == (sizeof(T) == 1)) {
            return x86::movemask(v);
        } else if constexpr (sizeof(T) == 2) {
            return x86::movemask_epi16(v);
        } else {
            static_assert(std::is_integral_v<T>);
            using U = std::conditional_t<sizeof(T) == 4, float, double>;
            return x86::movemask(x86::intrin_cast<detail::intrinsic_type_t<U, N>>(v));
        }
#if 0
            switch (sizeof(T)) {
            case 2: return _pext_u32(x86::movemask(v), 0xaaaaaaaa);
            case 4: return _pext_u32(x86::movemask(v), 0x88888888);
            case 8: return _pext_u32(x86::movemask(v), 0x80808080);
            default: Vc_UNREACHABLE();
            }
#endif
    }
    template <size_t N, class T>
    static Vc_INTRINSIC mask_member_type<T> from_bitset(std::bitset<N> bits, type_tag<T>)
    {
#ifdef Vc_HAVE_AVX512BW
        if (sizeof(T) <= 2u) {
            return detail::intrin_cast<detail::intrinsic_type_t<T, N>>(
                x86::convert_mask<sizeof(T), sizeof(mask_member_type<T>)>(bits));
        }
#endif
#ifdef Vc_HAVE_AVX512DQ
        if (sizeof(T) >= 4u) {
            return detail::intrin_cast<detail::intrinsic_type_t<T, N>>(
                x86::convert_mask<sizeof(T), sizeof(mask_member_type<T>)>(bits));
        }
#endif
        using U = std::conditional_t<sizeof(T) == 8, ullong,
                  std::conditional_t<sizeof(T) == 4, uint,
                  std::conditional_t<sizeof(T) == 2, ushort,
                  std::conditional_t<sizeof(T) == 1, uchar, void>>>>;
        using V = simd<U, abi>;
        constexpr size_t bits_per_element = sizeof(U) * CHAR_BIT;
        if (bits_per_element >= N) {
            V tmp(static_cast<U>(bits.to_ullong()));
            tmp &= V([](auto i) { return static_cast<U>(1ull << i); });
            return detail::intrin_cast<detail::intrinsic_type_t<T, N>>(
                detail::data(tmp != V()));
        } else {
            V tmp([&](auto i) {
                return static_cast<U>(bits.to_ullong() >>
                                      (bits_per_element * (i / bits_per_element)));
            });
            tmp &= V([](auto i) {
#ifdef Vc_MSVC
                constexpr size_t bits_per_element = sizeof(U) * CHAR_BIT;
#endif
                return static_cast<U>(1ull << (i % bits_per_element));
            });
            return detail::intrin_cast<detail::intrinsic_type_t<T, N>>(
                detail::data(tmp != V()));
        }
    }
    template <class T, size_t N>
    static Vc_INTRINSIC void Vc_VDECL masked_assign(Storage<T, N> k, Storage<T, N> &lhs,
                                                    detail::id<Storage<T, N>> rhs)
    {
        lhs = detail::x86::blend(k, lhs, rhs);
    }
    template <class T, size_t N>
    static Vc_INTRINSIC void Vc_VDECL masked_assign(Storage<T, N> k, Storage<T, N> &lhs,
                                                    bool rhs)
    {
#ifdef __GNUC__
        if (__builtin_constant_p(rhs)) {
            if (rhs == false) {
                lhs = x86::andnot_(k, lhs);
            } else {
                lhs = x86::or_(k, lhs);
            }
            return;
        }
#endif
        lhs = detail::x86::blend(k, lhs, detail::data(simd_mask<T>(rhs)));
    }
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
struct sse_mask_impl : public generic_mask_impl<simd_abi::Sse, sse_mask_member_type> {
    using abi = simd_abi::Sse;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using mask_member_type = sse_mask_member_type<T>;
    template <class T> using simd_mask = Vc::simd_mask<T, simd_abi::Sse>;
    template <class T> using mask_bool = MaskBool<sizeof(T)>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T> static Vc_INTRINSIC auto broadcast(bool x, type_tag<T>) noexcept
    {
        return detail::broadcast16(T(mask_bool<T>{x}));
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<4>) noexcept
    {
#ifdef Vc_HAVE_SSE2
        __m128i k = _mm_cvtsi32_si128(*reinterpret_cast<const int *>(mem));
        k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128());
        return intrin_cast<__m128>(_mm_unpacklo_epi16(k, k));
#elif defined Vc_HAVE_MMX
        __m128 k = _mm_cvtpi8_ps(_mm_cvtsi32_si64(*reinterpret_cast<const int *>(mem)));
        _mm_empty();
        return _mm_cmpgt_ps(k, detail::zero<__m128>());
#endif
    }
#ifdef Vc_HAVE_SSE2
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<2>) noexcept
    {
        return _mm_set_epi32(-int(mem[1]), -int(mem[1]), -int(mem[0]), -int(mem[0]));
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<8>) noexcept
    {
#ifdef Vc_IS_AMD64
        __m128i k = _mm_cvtsi64_si128(*reinterpret_cast<const int64_t *>(mem));
#else
        __m128i k = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem));
#endif
        return _mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128());
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F f, size_tag<16>) noexcept
    {
        return _mm_cmpgt_epi8(load16(mem, f), _mm_setzero_si128());
    }
#endif
#if !defined Vc_HAVE_SSE2 && defined Vc_HAVE_MMX
    template <class F>
    static Vc_INTRINSIC void store(mask_member_type<float> v, bool *mem, F,
                                   size_tag<4>) noexcept
    {
        const __m128 k(v);
        const __m64 kk = _mm_cvtps_pi8(and_(k, detail::one16(float())));
        *reinterpret_cast<may_alias<int32_t> *>(mem) = _mm_cvtsi64_si32(kk);
        _mm_empty();
    }
#endif
#ifdef Vc_HAVE_SSE2
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F,
                                            size_tag<2>) noexcept
    {
        const auto k = intrin_cast<__m128i>(v.v());
        mem[0] = -extract_epi32<1>(k);
        mem[1] = -extract_epi32<3>(k);
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F,
                                            size_tag<4>) noexcept
    {
        const auto k = intrin_cast<__m128i>(v.v());
        __m128i k2 = _mm_packs_epi32(k, _mm_setzero_si128());
        *reinterpret_cast<may_alias<int32_t> *>(mem) = _mm_cvtsi128_si32(
            _mm_packs_epi16(x86::srli_epi16<15>(k2), _mm_setzero_si128()));
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F,
                                            size_tag<8>) noexcept
    {
        auto k = intrin_cast<__m128i>(v.v());
        k = x86::srli_epi16<15>(k);
        const auto k2 = _mm_packs_epi16(k, _mm_setzero_si128());
#ifdef Vc_IS_AMD64
        *reinterpret_cast<may_alias<int64_t> *>(mem) = _mm_cvtsi128_si64(k2);
#else
        _mm_store_sd(reinterpret_cast<may_alias<double> *>(mem), _mm_castsi128_pd(k2));
#endif
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F f,
                                            size_tag<16>) noexcept
    {
        auto k = intrin_cast<__m128i>(v.v());
        k = _mm_and_si128(k, _mm_set1_epi32(0x01010101));
        x86::store16(k, mem, f);
    }
#endif
    template <class T, class SizeTag>
    static Vc_INTRINSIC mask_member_type<T> negate(const mask_member_type<T> &x,
                                                   SizeTag) noexcept
    {
#if defined Vc_GCC && defined Vc_USE_BUILTIN_VECTOR_TYPES
        return !x.builtin();
#else
        return detail::not_(x.v());
#endif
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::and_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::or_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::and_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::or_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_xor(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::xor_(x.d, y.d)};
    }
    template <class T> static bool get(const mask_member_type<T> k, int i) noexcept
    {
        return k.m(i);
    }
    template <class T> static void set(mask_member_type<T> &k, int i, bool x) noexcept
    {
        k.set(i, mask_bool<T>(x));
    }
};
}
Vc_ALWAYS_INLINE bool Vc_VDECL all_of(simd_mask<float, simd_abi::Sse> k)
{
    const __m128 d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return _mm_testc_ps(d, detail::allone<__m128>());
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return _mm_testc_si128(dd, detail::allone<__m128i>());
#else
    return _mm_movemask_ps(d) == 0xf;
#endif
}
Vc_ALWAYS_INLINE bool Vc_VDECL any_of(simd_mask<float, simd_abi::Sse> k)
{
    const __m128 d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return 0 == _mm_testz_ps(d, d);
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return 0 == _mm_testz_si128(dd, dd);
#else
    return _mm_movemask_ps(d) != 0;
#endif
}
Vc_ALWAYS_INLINE bool Vc_VDECL none_of(simd_mask<float, simd_abi::Sse> k)
{
    const __m128 d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return 0 != _mm_testz_ps(d, d);
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return 0 != _mm_testz_si128(dd, dd);
#else
    return _mm_movemask_ps(d) == 0;
#endif
}
Vc_ALWAYS_INLINE bool Vc_VDECL some_of(simd_mask<float, simd_abi::Sse> k)
{
    const __m128 d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return _mm_testnzc_ps(d, detail::allone<__m128>());
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return _mm_testnzc_si128(dd, detail::allone<__m128i>());
#else
    const int tmp = _mm_movemask_ps(d);
    return tmp != 0 && (tmp ^ 0xf) != 0;
#endif
}
#ifdef Vc_HAVE_SSE2
Vc_ALWAYS_INLINE bool Vc_VDECL all_of(simd_mask<double, simd_abi::Sse> k)
{
    __m128d d(k);
#ifdef Vc_USE_PTEST
#ifdef Vc_HAVE_AVX
    return _mm_testc_pd(d, detail::allone<__m128d>());
#else
    const auto dd = detail::intrin_cast<__m128i>(d);
    return _mm_testc_si128(dd, detail::allone<__m128i>());
#endif
#else
    return _mm_movemask_pd(d) == 0x3;
#endif
}
Vc_ALWAYS_INLINE bool Vc_VDECL any_of(simd_mask<double, simd_abi::Sse> k)
{
    const __m128d d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return 0 == _mm_testz_pd(d, d);
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return 0 == _mm_testz_si128(dd, dd);
#else
    return _mm_movemask_pd(d) != 0;
#endif
}
Vc_ALWAYS_INLINE bool Vc_VDECL none_of(simd_mask<double, simd_abi::Sse> k)
{
    const __m128d d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return 0 != _mm_testz_pd(d, d);
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return 0 != _mm_testz_si128(dd, dd);
#else
    return _mm_movemask_pd(d) == 0;
#endif
}
Vc_ALWAYS_INLINE bool Vc_VDECL some_of(simd_mask<double, simd_abi::Sse> k)
{
    const __m128d d(k);
#if defined Vc_USE_PTEST && defined Vc_HAVE_AVX
    return _mm_testnzc_pd(d, detail::allone<__m128d>());
#elif defined Vc_USE_PTEST
    const auto dd = detail::intrin_cast<__m128i>(d);
    return _mm_testnzc_si128(dd, detail::allone<__m128i>());
#else
    const int tmp = _mm_movemask_pd(d);
    return tmp == 1 || tmp == 2;
#endif
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL all_of(simd_mask<T, simd_abi::Sse> k)
{
    const __m128i d(k);
#ifdef Vc_USE_PTEST
    return _mm_testc_si128(d, detail::allone<__m128i>());
#else
    return _mm_movemask_epi8(d) == 0xffff;
#endif
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL any_of(simd_mask<T, simd_abi::Sse> k)
{
    const __m128i d(k);
#ifdef Vc_USE_PTEST
    return 0 == _mm_testz_si128(d, d);
#else
    return _mm_movemask_epi8(d) != 0x0000;
#endif
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL none_of(simd_mask<T, simd_abi::Sse> k)
{
    const __m128i d(k);
#ifdef Vc_USE_PTEST
    return 0 != _mm_testz_si128(d, d);
#else
    return _mm_movemask_epi8(d) == 0x0000;
#endif
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL some_of(simd_mask<T, simd_abi::Sse> k)
{
    const __m128i d(k);
#ifdef Vc_USE_PTEST
    return _mm_test_mix_ones_zeros(d, detail::allone<__m128i>());
#else
    const int tmp = _mm_movemask_epi8(d);
    return tmp != 0 && (tmp ^ 0xffff) != 0;
#endif
}
#endif
template <class T> Vc_ALWAYS_INLINE int Vc_VDECL popcount(simd_mask<T, simd_abi::Sse> k)
{
    const auto d = detail::data(k);
    return detail::mask_count<k.size()>(d);
}
template <class T> Vc_ALWAYS_INLINE int Vc_VDECL find_first_set(simd_mask<T, simd_abi::Sse> k)
{
    const auto d = detail::data(k);
    return detail::firstbit(detail::mask_to_int<k.size()>(d));
}
template <class T> Vc_ALWAYS_INLINE int Vc_VDECL find_last_set(simd_mask<T, simd_abi::Sse> k)
{
    const auto d = detail::data(k);
    return detail::lastbit(detail::mask_to_int<k.size()>(d));
}
namespace detail
{
struct sse_simd_impl : public generic_simd_impl<sse_simd_impl> {
    using abi = simd_abi::Sse;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using simd_member_type = sse_simd_member_type<T>;
    template <class T> using intrinsic_type = typename simd_member_type<T>::VectorType;
    template <class T> using mask_member_type = sse_mask_member_type<T>;
    template <class T> using simd = Vc::simd<T, abi>;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T>
    static Vc_INTRINSIC simd<T> make_simd(simd_member_type<T> x)
    {
        return {detail::private_init, x};
    }
    static Vc_INTRINSIC intrinsic_type<float> broadcast(float x, size_tag<4>) noexcept
    {
        return _mm_set1_ps(x);
    }
#ifdef Vc_HAVE_SSE2
    static Vc_INTRINSIC intrinsic_type<double> broadcast(double x, size_tag<2>) noexcept
    {
        return _mm_set1_pd(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<2>) noexcept
    {
        return _mm_set1_epi64x(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<4>) noexcept
    {
        return _mm_set1_epi32(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<8>) noexcept
    {
        return _mm_set1_epi16(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<16>) noexcept
    {
        return _mm_set1_epi8(x);
    }
#endif
    template <class T, class F>
    static Vc_INTRINSIC simd_member_type<T> load(const long double *mem, F,
                                                    type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return generate_from_n_evaluations<size<T>(), simd_member_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
    }
    template <class T, class F>
    static Vc_INTRINSIC simd_member_type<T> load(const T *mem, F f,
                                                    type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return detail::load16(mem, f);
    }
    template <class T, class U, class F>
    static inline simd_member_type<T> load(
        const convertible_memory<U, sizeof(T), T> *mem, F f, type_tag<T>,
        tag<1> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_FULL_SSE_ABI
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            detail::load16(mem, f));
#else
        unused(f);
        return generate_from_n_evaluations<size<T>(), intrinsic_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
#endif
    }
    template <class T, class U, class F>
    static inline simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) / 2, T> *mem, F f, type_tag<T>,
        tag<2> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_FULL_SSE_ABI
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            intrin_cast<detail::intrinsic_type_t<U, size<U>()>>(load8(mem, f)));
#else
        return generate_from_n_evaluations<size<T>(), intrinsic_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
        unused(f);
#endif
    }
    template <class T, class U, class F>
    static inline simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) / 4, T> *mem, F f, type_tag<T>,
        tag<3> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_FULL_SSE_ABI
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            intrin_cast<detail::intrinsic_type_t<U, size<U>()>>(load4(mem, f)));
#else
        return generate_from_n_evaluations<size<T>(), intrinsic_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
        unused(f);
#endif
    }
#ifdef Vc_HAVE_FULL_SSE_ABI
    template <class T, class U>
    static Vc_INTRINSIC simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) / 8, T> *mem,
        when_aligned<alignof(uint16_t)>, type_tag<T>, tag<4> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            intrin_cast<detail::intrinsic_type_t<U, size<U>()>>(
                load2(mem, vector_aligned)));
    }
    template <class T, class U>
    static Vc_INTRINSIC simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) / 8, T> *mem,
        when_unaligned<alignof(uint16_t)>, type_tag<T>,
        tag<4> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return simd_member_type<T>(T(mem[0]), T(mem[1]));
    }
#else
    template <class T, class U, class F>
    static Vc_INTRINSIC simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) / 8, T> *mem, F, type_tag<T>,
        tag<4> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return simd_member_type<T>(T(mem[0]), T(mem[1]));
    }
#endif
    template <class T> using avx_member_type = avx_simd_member_type<T>;
    template <class T> using avx512_member_type = avx512_simd_member_type<T>;
    template <class T, class U, class F>
    static inline simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) * 2, T> *mem, F f, type_tag<T>,
        tag<5> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX
        return x86::convert<avx_member_type<U>, simd_member_type<T>>(
            detail::load32(mem, f));
#elif defined Vc_HAVE_FULL_SSE_ABI
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            load(mem, f, type_tag<U>()), load(mem + size<U>(), f, type_tag<U>()));
#else
        unused(f);
        return generate_from_n_evaluations<size<T>(), intrinsic_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
#endif
    }
    template <class T, class U, class F>
    static inline simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) * 4, T> *mem, F f, type_tag<T>,
        tag<6> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        return x86::convert<avx512_member_type<U>, simd_member_type<T>>(load64(mem, f));
#elif defined Vc_HAVE_AVX
        return x86::convert<avx_member_type<U>, simd_member_type<T>>(
            detail::load32(mem, f), detail::load32(mem + 2 * size<U>(), f));
#else
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            load(mem, f, type_tag<U>()), load(mem + size<U>(), f, type_tag<U>()),
            load(mem + 2 * size<U>(), f, type_tag<U>()),
            load(mem + 3 * size<U>(), f, type_tag<U>()));
#endif
    }
    template <class T, class U, class F>
    static inline simd_member_type<T> load(
        const convertible_memory<U, sizeof(T) * 8, T> *mem, F f, type_tag<T>,
        tag<7> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        return x86::convert<avx512_member_type<U>, simd_member_type<T>>(
            load64(mem, f), load64(mem + 4 * size<U>(), f));
#elif defined Vc_HAVE_AVX
        return x86::convert<avx_member_type<U>, simd_member_type<T>>(
            load32(mem, f), load32(mem + 2 * size<U>(), f), load32(mem + 4 * size<U>(), f),
            load32(mem + 6 * size<U>(), f));
#else
        return x86::convert<simd_member_type<U>, simd_member_type<T>>(
            load16(mem, f), load16(mem + size<U>(), f), load16(mem + 2 * size<U>(), f),
            load16(mem + 3 * size<U>(), f), load16(mem + 4 * size<U>(), f),
            load16(mem + 5 * size<U>(), f), load16(mem + 6 * size<U>(), f),
            load16(mem + 7 * size<U>(), f));
#endif
    }
    template <class T, class U, class F>
    static inline void Vc_VDECL masked_load(simd_member_type<T> &merge,
                                            mask_member_type<T> k, const U *mem,
                                            F) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                merge.set(i, static_cast<T>(mem[i]));
            }
        });
    }
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<schar> &merge,
                                                  mask_member_type<schar> k, const schar *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm_mask_loadu_epi8(merge, _mm_movemask_epi8(k), mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<uchar> &merge,
                                                  mask_member_type<uchar> k, const uchar *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm_mask_loadu_epi8(merge, _mm_movemask_epi8(k), mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<short> &merge,
                                                  mask_member_type<short> k, const short *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm_mask_loadu_epi16(merge, x86::movemask_epi16(k), mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<ushort> &merge,
                                                  mask_member_type<ushort> k, const ushort *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm_mask_loadu_epi16(merge, x86::movemask_epi16(k), mem);
    }
#endif
#ifdef Vc_HAVE_AVX2
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<int> &merge,
                                                  mask_member_type<int> k, const int *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge), _mm_maskload_epi32(mem, k));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<uint> &merge,
                                                  mask_member_type<uint> k, const uint *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge),
                    _mm_maskload_epi32(
                        reinterpret_cast<const detail::may_alias<int> *>(mem), k));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<llong> &merge,
                                                  mask_member_type<llong> k, const llong *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge), _mm_maskload_epi64(mem, k));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<ullong> &merge,
                                                  mask_member_type<ullong> k, const ullong *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge),
                    _mm_maskload_epi64(
                        reinterpret_cast<const may_alias<long long> *>(mem), k));
    }
#endif
#ifdef Vc_HAVE_AVX
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<double> &merge,
                                                  mask_member_type<double> k, const double *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge), _mm_maskload_pd(mem, _mm_castpd_si128(k)));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<float> &merge,
                                                  mask_member_type<float> k,
                                                  const float *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge), _mm_maskload_ps(mem, _mm_castps_si128(k)));
    }
#endif
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(simd_member_type<T> v, long double *mem, F,
                                            type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(simd_member_type<T> v, T *mem, F f,
                                            type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        store16(v, mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U) * 8> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store2(x86::convert<simd_member_type<T>, simd_member_type<U>>(v), mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U) * 4> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_FULL_SSE_ABI
        store4(x86::convert<simd_member_type<T>, simd_member_type<U>>(v), mem, f);
#else
        unused(f);
        execute_n_times<size<T>()>([&](auto i) { mem[i] = static_cast<U>(v[i]); });
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U) * 2> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_FULL_SSE_ABI
        store8(x86::convert<simd_member_type<T>, simd_member_type<U>>(v), mem, f);
#else
        unused(f);
        execute_n_times<size<T>()>([&](auto i) { mem[i] = static_cast<U>(v[i]); });
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_FULL_SSE_ABI
        store16(x86::convert<simd_member_type<T>, simd_member_type<U>>(v), mem, f);
#else
        unused(f);
        execute_n_times<size<T>()>([&](auto i) { mem[i] = static_cast<U>(v[i]); });
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) * 2 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX
        store32(x86::convert<simd_member_type<T>, avx_member_type<U>>(v), mem, f);
#elif defined Vc_HAVE_FULL_SSE_ABI
        const auto tmp = convert_all<simd_member_type<U>>(v);
        store16(tmp[0], mem, f);
        store16(tmp[1], mem + size<T>() / 2, f);
#else
        execute_n_times<size<T>()>([&](auto i) { mem[i] = static_cast<U>(v[i]); });
        detail::unused(f);
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) * 4 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        store64(convert_all<avx512_member_type<U>>(v), mem, f);
#elif defined Vc_HAVE_AVX
        const auto tmp = convert_all<avx_member_type<U>>(v);
        store32(tmp[0], mem, f);
        store32(tmp[1], mem + size<T>() / 2, f);
#else
        const auto tmp = convert_all<simd_member_type<U>>(v);
        store16(tmp[0], mem, f);
        store16(tmp[1], mem + size<T>() * 1 / 4, f);
        store16(tmp[2], mem + size<T>() * 2 / 4, f);
        store16(tmp[3], mem + size<T>() * 3 / 4, f);
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
          enable_if<sizeof(T) * 8 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        const auto tmp = convert_all<avx512_member_type<U>>(v);
        store64(tmp[0], mem, f);
        store64(tmp[1], mem + size<T>() / 2, f);
#elif defined Vc_HAVE_AVX
        const auto tmp = convert_all<avx_member_type<U>>(v);
        store32(tmp[0], mem, f);
        store32(tmp[1], mem + size<T>() * 1 / 4, f);
        store32(tmp[2], mem + size<T>() * 2 / 4, f);
        store32(tmp[3], mem + size<T>() * 3 / 4, f);
#else
        const auto tmp = convert_all<simd_member_type<U>>(v);
        store16(tmp[0], mem, f);
        store16(tmp[1], mem + size<T>() * 1 / 8, f);
        store16(tmp[2], mem + size<T>() * 2 / 8, f);
        store16(tmp[3], mem + size<T>() * 3 / 8, f);
        store16(tmp[4], mem + size<T>() * 4 / 8, f);
        store16(tmp[5], mem + size<T>() * 5 / 8, f);
        store16(tmp[6], mem + size<T>() * 6 / 8, f);
        store16(tmp[7], mem + size<T>() * 7 / 8, f);
#endif
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL
    masked_store(const simd_member_type<T> v, long double *mem, F,
                 const mask_member_type<T> k) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                mem[i] = v.m(i);
            }
        });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL masked_store(const simd_member_type<T> v, U *mem,
                                                   F, const mask_member_type<T> k)
        Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                mem[i] = static_cast<T>(v.m(i));
            }
        });
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> Vc_VDECL
    negate(simd_member_type<T> x) noexcept
    {
#if defined Vc_GCC && defined Vc_USE_BUILTIN_VECTOR_TYPES
        return !x.builtin();
#else
        return equal_to(x, simd_member_type<T>(x86::zero<intrinsic_type<T>>()));
#endif
    }
    template <class BinaryOperation>
    static Vc_INTRINSIC double Vc_VDECL reduce(size_tag<2>, simd<double> x,
                                               BinaryOperation &binary_op)
    {
        using V = simd<double>;
        auto intrin_ = data(x);
        intrin_ = data(
            binary_op(x, V(detail::private_init, _mm_unpackhi_pd(intrin_, intrin_))));
        return _mm_cvtsd_f64(intrin_);
    }
    template <class BinaryOperation>
    static Vc_INTRINSIC float Vc_VDECL reduce(size_tag<4>, simd<float> x,
                                              BinaryOperation &binary_op)
    {
        using V = simd<float>;
        auto intrin_ = data(x);
        intrin_ = data(
            binary_op(x, V(detail::private_init,
                           _mm_shuffle_ps(intrin_, intrin_, _MM_SHUFFLE(0, 1, 2, 3)))));
        intrin_ =
            data(binary_op(V(detail::private_init, intrin_),
                           V(detail::private_init, _mm_unpackhi_ps(intrin_, intrin_))));
        return _mm_cvtss_f32(intrin_);
    }
    template <class T, class BinaryOperation>
    static Vc_INTRINSIC T Vc_VDECL reduce(size_tag<2>, const simd<T> x,
                                          BinaryOperation &binary_op)
    {
        return binary_op(x[0], x[1]);
    }
    template <class T, class BinaryOperation>
    static Vc_INTRINSIC T Vc_VDECL reduce(size_tag<4>, simd<T> x,
                                          BinaryOperation &binary_op)
    {
        using V = simd<T>;
        auto intrin_ = data(x);
        intrin_ =
            data(binary_op(x, V(detail::private_init,
                                _mm_shuffle_epi32(intrin_, _MM_SHUFFLE(0, 1, 2, 3)))));
        intrin_ = data(
            binary_op(V(detail::private_init, intrin_),
                      V(detail::private_init, _mm_unpackhi_epi64(intrin_, intrin_))));
        return _mm_cvtsi128_si32(intrin_);
    }
    template <class T, class BinaryOperation>
    static Vc_INTRINSIC T Vc_VDECL reduce(size_tag<8>, simd<T> x,
                                          BinaryOperation &binary_op)
    {
        using V = simd<T>;
        auto intrin_ = data(x);
        intrin_ = data(
            binary_op(V(detail::private_init, _mm_unpacklo_epi16(intrin_, intrin_)),
                      V(detail::private_init, _mm_unpackhi_epi16(intrin_, intrin_))));
        intrin_ = data(
            binary_op(V(detail::private_init, _mm_unpacklo_epi32(intrin_, intrin_)),
                      V(detail::private_init, _mm_unpackhi_epi32(intrin_, intrin_))));
        return binary_op(
            V(detail::private_init, intrin_),
            V(detail::private_init, _mm_unpackhi_epi64(intrin_, intrin_)))[0];
    }
    template <class T, class BinaryOperation>
    static Vc_INTRINSIC T Vc_VDECL reduce(size_tag<16>, simd<T> x,
                                          BinaryOperation &binary_op)
    {
        using V = simd<T>;
        auto intrin_ = data(x);
        intrin_ =
            data(binary_op(V(detail::private_init, _mm_unpacklo_epi8(intrin_, intrin_)),
                           V(detail::private_init, _mm_unpackhi_epi8(intrin_, intrin_))));
        intrin_ = data(
            binary_op(V(detail::private_init, _mm_unpacklo_epi16(intrin_, intrin_)),
                      V(detail::private_init, _mm_unpackhi_epi16(intrin_, intrin_))));
        intrin_ = data(
            binary_op(V(detail::private_init, _mm_unpacklo_epi32(intrin_, intrin_)),
                      V(detail::private_init, _mm_unpackhi_epi32(intrin_, intrin_))));
        return binary_op(
            V(detail::private_init, intrin_),
            V(detail::private_init, _mm_unpackhi_epi64(intrin_, intrin_)))[0];
    }
    static Vc_INTRINSIC simd_member_type<double> min(simd_member_type<double> a,
                                                        simd_member_type<double> b)
    {
        return _mm_min_pd(a, b);
    }
    static Vc_INTRINSIC simd_member_type<float> min(simd_member_type<float> a,
                                                       simd_member_type<float> b)
    {
        return _mm_min_ps(a, b);
    }
    static Vc_INTRINSIC simd_member_type<llong> min(simd_member_type<llong> a,
                                                       simd_member_type<llong> b)
    {
#if defined Vc_HAVE_AVX512F && defined Vc_HAVE_AVX512VL
        return _mm_min_epi64(a, b);
#else
        return blendv_epi8(a, b, cmpgt_epi64(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<ullong> min(simd_member_type<ullong> a,
                                                        simd_member_type<ullong> b)
    {
#if defined Vc_HAVE_AVX512F && defined Vc_HAVE_AVX512VL
        return _mm_min_epu64(a, b);
#else
        return blendv_epi8(a, b, cmpgt_epu64(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<int> min(simd_member_type<int> a,
                                                     simd_member_type<int> b)
    {
#ifdef Vc_HAVE_SSE4_1
        return _mm_min_epi32(a, b);
#else
        return blendv_epi8(a, b, _mm_cmpgt_epi32(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<uint> min(simd_member_type<uint> a,
                                                      simd_member_type<uint> b)
    {
#ifdef Vc_HAVE_SSE4_1
        return _mm_min_epu32(a, b);
#else
        return blendv_epi8(a, b, cmpgt_epu32(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<short> min(simd_member_type<short> a,
                                                       simd_member_type<short> b)
    {
        return _mm_min_epi16(a, b);
    }
    static Vc_INTRINSIC simd_member_type<ushort> min(simd_member_type<ushort> a,
                                                        simd_member_type<ushort> b)
    {
#ifdef Vc_HAVE_SSE4_1
        return _mm_min_epu16(a, b);
#else
        return blendv_epi8(a, b, cmpgt_epu16(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<schar> min(simd_member_type<schar> a,
                                                       simd_member_type<schar> b)
    {
#ifdef Vc_HAVE_SSE4_1
        return _mm_min_epi8(a, b);
#else
        return blendv_epi8(a, b, _mm_cmpgt_epi8(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<uchar> min(simd_member_type<uchar> a,
                                                       simd_member_type<uchar> b)
    {
        return _mm_min_epu8(a, b);
    }
    static Vc_INTRINSIC simd_member_type<double> max(simd_member_type<double> a,
                                                        simd_member_type<double> b)
    {
        return _mm_max_pd(a, b);
    }
    static Vc_INTRINSIC simd_member_type<float> max(simd_member_type<float> a,
                                                       simd_member_type<float> b)
    {
        return _mm_max_ps(a, b);
    }
    static Vc_INTRINSIC simd_member_type<llong> max(simd_member_type<llong> a,
                                                       simd_member_type<llong> b)
    {
#if defined Vc_HAVE_AVX512F && defined Vc_HAVE_AVX512VL
        return _mm_max_epi64(a, b);
#else
        return blendv_epi8(b, a, cmpgt_epi64(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<ullong> max(simd_member_type<ullong> a,
                                                        simd_member_type<ullong> b)
    {
#if defined Vc_HAVE_AVX512F && defined Vc_HAVE_AVX512VL
        return _mm_max_epu64(a, b);
#else
        return blendv_epi8(b, a, cmpgt_epu64(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<int> max(simd_member_type<int> a,
                                                     simd_member_type<int> b){
#ifdef Vc_HAVE_SSE4_1
        return _mm_max_epi32(a, b);
#else
        return blendv_epi8(b, a, _mm_cmpgt_epi32(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<uint> max(simd_member_type<uint> a,
                                                      simd_member_type<uint> b){
#ifdef Vc_HAVE_SSE4_1
        return _mm_max_epu32(a, b);
#else
        return blendv_epi8(b, a, cmpgt_epu32(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<short> max(simd_member_type<short> a,
                                                       simd_member_type<short> b)
    {
        return _mm_max_epi16(a, b);
    }
    static Vc_INTRINSIC simd_member_type<ushort> max(simd_member_type<ushort> a,
                                                        simd_member_type<ushort> b)
    {
#ifdef Vc_HAVE_SSE4_1
        return _mm_max_epu16(a, b);
#else
        return blendv_epi8(b, a, cmpgt_epu16(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<schar> max(simd_member_type<schar> a,
                                                       simd_member_type<schar> b)
    {
#ifdef Vc_HAVE_SSE4_1
        return _mm_max_epi8(a, b);
#else
        return blendv_epi8(b, a, _mm_cmpgt_epi8(a, b));
#endif
    }
    static Vc_INTRINSIC simd_member_type<uchar> max(simd_member_type<uchar> a,
                                                       simd_member_type<uchar> b)
    {
        return _mm_max_epu8(a, b);
    }
    static Vc_INTRINSIC simd_member_type<long> min(simd_member_type<long> a,
                                                      simd_member_type<long> b)
    {
        return min(simd_member_type<equal_int_type_t<long>>(a.v()),
                   simd_member_type<equal_int_type_t<long>>(b.v()))
            .v();
    }
    static Vc_INTRINSIC simd_member_type<long> max(simd_member_type<long> a,
                                                      simd_member_type<long> b)
    {
        return max(simd_member_type<equal_int_type_t<long>>(a.v()),
                   simd_member_type<equal_int_type_t<long>>(b.v()))
            .v();
    }
    static Vc_INTRINSIC simd_member_type<ulong> min(simd_member_type<ulong> a,
                                                       simd_member_type<ulong> b)
    {
        return min(simd_member_type<equal_int_type_t<ulong>>(a.v()),
                   simd_member_type<equal_int_type_t<ulong>>(b.v()))
            .v();
    }
    static Vc_INTRINSIC simd_member_type<ulong> max(simd_member_type<ulong> a,
                                                       simd_member_type<ulong> b)
    {
        return max(simd_member_type<equal_int_type_t<ulong>>(a.v()),
                   simd_member_type<equal_int_type_t<ulong>>(b.v()))
            .v();
    }
    template <class T>
    static Vc_INTRINSIC std::pair<simd_member_type<T>, simd_member_type<T>> minmax(
        simd_member_type<T> a, simd_member_type<T> b)
    {
        return {min(a, b), max(a, b)};
    }
#if defined Vc_USE_BUILTIN_VECTOR_TYPES
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> equal_to(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() == y.builtin();
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> not_equal_to(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() != y.builtin();
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> less(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() < y.builtin();
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> less_equal(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() <= y.builtin();
    }
#else
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL equal_to(simd_member_type<double> x, simd_member_type<double> y) { return _mm_cmpeq_pd(x, y); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL equal_to(simd_member_type< float> x, simd_member_type< float> y) { return _mm_cmpeq_ps(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL equal_to(simd_member_type< llong> x, simd_member_type< llong> y) { return cmpeq_epi64(x, y); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL equal_to(simd_member_type<ullong> x, simd_member_type<ullong> y) { return cmpeq_epi64(x, y); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL equal_to(simd_member_type< long> x, simd_member_type< long> y) { return sizeof(long) == 8 ? cmpeq_epi64(x, y) : _mm_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL equal_to(simd_member_type< ulong> x, simd_member_type< ulong> y) { return sizeof(long) == 8 ? cmpeq_epi64(x, y) : _mm_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL equal_to(simd_member_type< int> x, simd_member_type< int> y) { return _mm_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL equal_to(simd_member_type< uint> x, simd_member_type< uint> y) { return _mm_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL equal_to(simd_member_type< short> x, simd_member_type< short> y) { return _mm_cmpeq_epi16(x, y); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL equal_to(simd_member_type<ushort> x, simd_member_type<ushort> y) { return _mm_cmpeq_epi16(x, y); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL equal_to(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm_cmpeq_epi8(x, y); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL equal_to(simd_member_type< uchar> x, simd_member_type< uchar> y) { return _mm_cmpeq_epi8(x, y); }
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL not_equal_to(simd_member_type<double> x, simd_member_type<double> y) { return _mm_cmpneq_pd(x, y); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL not_equal_to(simd_member_type< float> x, simd_member_type< float> y) { return _mm_cmpneq_ps(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL not_equal_to(simd_member_type< llong> x, simd_member_type< llong> y) { return detail::not_(cmpeq_epi64(x, y)); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL not_equal_to(simd_member_type<ullong> x, simd_member_type<ullong> y) { return detail::not_(cmpeq_epi64(x, y)); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL not_equal_to(simd_member_type< long> x, simd_member_type< long> y) { return detail::not_(sizeof(long) == 8 ? cmpeq_epi64(x, y) : _mm_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL not_equal_to(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::not_(sizeof(long) == 8 ? cmpeq_epi64(x, y) : _mm_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL not_equal_to(simd_member_type< int> x, simd_member_type< int> y) { return detail::not_(_mm_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL not_equal_to(simd_member_type< uint> x, simd_member_type< uint> y) { return detail::not_(_mm_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL not_equal_to(simd_member_type< short> x, simd_member_type< short> y) { return detail::not_(_mm_cmpeq_epi16(x, y)); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL not_equal_to(simd_member_type<ushort> x, simd_member_type<ushort> y) { return detail::not_(_mm_cmpeq_epi16(x, y)); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL not_equal_to(simd_member_type< schar> x, simd_member_type< schar> y) { return detail::not_(_mm_cmpeq_epi8(x, y)); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL not_equal_to(simd_member_type< uchar> x, simd_member_type< uchar> y) { return detail::not_(_mm_cmpeq_epi8(x, y)); }
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL less(simd_member_type<double> x, simd_member_type<double> y) { return _mm_cmplt_pd(x, y); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL less(simd_member_type< float> x, simd_member_type< float> y) { return _mm_cmplt_ps(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL less(simd_member_type< llong> x, simd_member_type< llong> y) { return cmpgt_epi64(y, x); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL less(simd_member_type<ullong> x, simd_member_type<ullong> y) { return cmpgt_epu64(y, x); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL less(simd_member_type< long> x, simd_member_type< long> y) { return sizeof(long) == 8 ? cmpgt_epi64(y, x) : _mm_cmpgt_epi32(y, x); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL less(simd_member_type< ulong> x, simd_member_type< ulong> y) { return sizeof(long) == 8 ? cmpgt_epu64(y, x) : cmpgt_epu32(y, x); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL less(simd_member_type< int> x, simd_member_type< int> y) { return _mm_cmpgt_epi32(y, x); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL less(simd_member_type< uint> x, simd_member_type< uint> y) { return cmpgt_epu32(y, x); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL less(simd_member_type< short> x, simd_member_type< short> y) { return _mm_cmpgt_epi16(y, x); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL less(simd_member_type<ushort> x, simd_member_type<ushort> y) { return cmpgt_epu16(y, x); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL less(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm_cmpgt_epi8 (y, x); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL less(simd_member_type< uchar> x, simd_member_type< uchar> y) { return cmpgt_epu8 (y, x); }
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL less_equal(simd_member_type<double> x, simd_member_type<double> y) { return _mm_cmple_pd(x, y); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL less_equal(simd_member_type< float> x, simd_member_type< float> y) { return _mm_cmple_ps(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL less_equal(simd_member_type< llong> x, simd_member_type< llong> y) { return detail::not_(cmpgt_epi64(x, y)); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL less_equal(simd_member_type<ullong> x, simd_member_type<ullong> y) { return detail::not_(cmpgt_epu64(x, y)); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL less_equal(simd_member_type< long> x, simd_member_type< long> y) { return detail::not_(sizeof(long) == 8 ? cmpgt_epi64(x, y) : _mm_cmpgt_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL less_equal(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::not_(sizeof(long) == 8 ? cmpgt_epu64(x, y) : cmpgt_epu32(x, y)); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL less_equal(simd_member_type< int> x, simd_member_type< int> y) { return detail::not_( _mm_cmpgt_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL less_equal(simd_member_type< uint> x, simd_member_type< uint> y) { return detail::not_(cmpgt_epu32(x, y)); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL less_equal(simd_member_type< short> x, simd_member_type< short> y) { return detail::not_( _mm_cmpgt_epi16(x, y)); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL less_equal(simd_member_type<ushort> x, simd_member_type<ushort> y) { return detail::not_(cmpgt_epu16(x, y)); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL less_equal(simd_member_type< schar> x, simd_member_type< schar> y) { return detail::not_( _mm_cmpgt_epi8 (x, y)); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL less_equal(simd_member_type< uchar> x, simd_member_type< uchar> y) { return detail::not_(cmpgt_epu8 (x, y)); }
#endif
    static Vc_INTRINSIC simd_member_type<float> sqrt(simd_member_type<float> x)
    {
        return _mm_sqrt_ps(x);
    }
    static Vc_INTRINSIC simd_member_type<double> sqrt(simd_member_type<double> x)
    {
        return _mm_sqrt_pd(x);
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<float> logb_positive(simd_member_type<float> v)
    {
#ifdef Vc_HAVE_AVX512VL
        return _mm_getexp_ps(v);
#else
        __m128i tmp = _mm_srli_epi32(_mm_castps_si128(v), 23);
        tmp = _mm_sub_epi32(tmp, _mm_set1_epi32(0x7f));
        return _mm_cvtepi32_ps(tmp);
#endif
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<double> logb_positive(simd_member_type<double> v)
    {
#ifdef Vc_HAVE_AVX512VL
        return _mm_getexp_pd(v);
#else
        __m128i tmp = _mm_srli_epi64(_mm_castpd_si128(v), 52);
        tmp = _mm_sub_epi32(tmp, _mm_set1_epi32(0x3ff));
        return _mm_cvtepi32_pd(_mm_shuffle_epi32(tmp, 0x08));
#endif
    }
#ifdef Vc_HAVE_AVX512VL
    static Vc_INTRINSIC Vc_CONST simd_member_type<float> logb(simd_member_type<float> v)
    {
        return _mm_fixupimm_ps(_mm_getexp_ps(abs(v)), v, broadcast16(0x00550433), 0x00);
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<double> logb(simd_member_type<double> v)
    {
        return _mm_fixupimm_pd(_mm_getexp_pd(abs(v)), v, broadcast16(0x00550433), 0x00);
    }
#endif
#ifdef Vc_HAVE_SSE4_1
    static Vc_INTRINSIC simd_member_type<float> trunc(simd_member_type<float> x)
    {
        return _mm_round_ps(x, 0x3);
    }
    static Vc_INTRINSIC simd_member_type<double> trunc(simd_member_type<double> x)
    {
        return _mm_round_pd(x, 0x3);
    }
#else
    static Vc_INTRINSIC simd_member_type<float> trunc(simd_member_type<float> x)
    {
        auto truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(x));
        auto mask = intrin_cast<__m128>(_mm_cmplt_epi32(
            and_(intrin_cast<__m128i>(x), broadcast16(0x7f800000u)),
            broadcast16(0x4b000000)));
        return blendv_ps(x, truncated, mask);
    }
    static Vc_INTRINSIC simd_member_type<double> trunc(simd_member_type<double> x)
    {
        const auto abs_x = abs(x);
        const auto min_no_fractional_bits = intrin_cast<__m128d>(
            broadcast16(0x4330'0000'0000'0000ull));  // 0x3ff + 52 = 0x433
        simd_member_type<double> truncated =
            _mm_sub_pd(_mm_add_pd(abs_x, min_no_fractional_bits), min_no_fractional_bits);
        truncated = _mm_sub_pd(truncated, and_(less(abs_x, truncated), broadcast16(1.)));
        return or_(and_(intrin_cast<__m128d>(broadcast16(0x8000'0000'0000'0000ull)), x),
                   truncated);
    }
#endif
#ifdef Vc_HAVE_SSE4_1
    static Vc_INTRINSIC simd_member_type<float> floor(simd_member_type<float> x)
    {
        return _mm_floor_ps(x);
    }
    static Vc_INTRINSIC simd_member_type<double> floor(simd_member_type<double> x)
    {
        return _mm_floor_pd(x);
    }
#else
    template<class T>
    static Vc_INTRINSIC simd_member_type<T> floor(simd_member_type<T> x)
    {
        auto y = trunc(x);
        const auto negative_input = less(x, simd_member_type<T>(broadcast16(T(0))));
        const auto mask = andnot_(equal_to(y, x), negative_input);
        return or_(andnot_(mask, y),
                   and_(mask, minus(y, simd_member_type<T>(broadcast16(T(1))))));
    }
#endif
#ifdef Vc_HAVE_SSE4_1
    static Vc_INTRINSIC simd_member_type<float> ceil(simd_member_type<float> x)
    {
        return _mm_ceil_ps(x);
    }
    static Vc_INTRINSIC simd_member_type<double> ceil(simd_member_type<double> x)
    {
        return _mm_ceil_pd(x);
    }
#else
    template<class T>
    static Vc_INTRINSIC simd_member_type<T> ceil(simd_member_type<T> x)
    {
        auto y = trunc(x);
        const auto negative_input = less(x, simd_member_type<T>(broadcast16(T(0))));
        const auto inv_mask = or_(equal_to(y, x), negative_input);
        return or_(and_(inv_mask, y),
                   andnot_(inv_mask, plus(y, simd_member_type<T>(broadcast16(T(1))))));
    }
#endif
#ifdef Vc_HAVE_AVX512VL
    static inline simd_member_type<double> frexp(
        simd_member_type<double> v,
        simd_tuple<int, simd_abi::scalar, simd_abi::scalar> &exp)
    {
        const __mmask8 isnonzerovalue = _mm_cmp_pd_mask(
            _mm_mul_pd(broadcast16(std::numeric_limits<double>::infinity()),
                       v),
            _mm_mul_pd(_mm_setzero_pd(), v), _CMP_ORD_Q);
        if (Vc_IS_LIKELY(isnonzerovalue == 0x03)) {
            const x_i32 e =
                _mm_add_epi32(broadcast16(1), _mm_cvttpd_epi32(_mm_getexp_pd(v)));
            exp.first = e[0];
            exp.second.first = e[1];
            return _mm_getmant_pd(v, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
        }
        const x_i32 e =
            _mm_mask_add_epi32(_mm_setzero_si128(), isnonzerovalue, broadcast16(1),
                               _mm_cvttpd_epi32(_mm_getexp_pd(v)));
        exp.first = e[0];
        exp.second.first = e[1];
        return _mm_mask_getmant_pd(v, isnonzerovalue, v, _MM_MANT_NORM_p5_1,
                                   _MM_MANT_SIGN_src);
    }
    static inline simd_member_type<float> frexp(simd_member_type<float> v,
                                                simd_member_type<int> &exp)
    {
        const __mmask8 isnonzerovalue = _mm_cmp_ps_mask(
            _mm_mul_ps(broadcast16(std::numeric_limits<float>::infinity()),
                       v),
            _mm_mul_ps(_mm_setzero_ps(), v), _CMP_ORD_Q);
        if (Vc_IS_LIKELY(isnonzerovalue == 0x0f)) {
            exp = _mm_add_epi32(broadcast16(1), _mm_cvttps_epi32(_mm_getexp_ps(v)));
            return _mm_getmant_ps(v, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
        }
        exp = _mm_mask_add_epi32(_mm_setzero_si128(), isnonzerovalue, broadcast16(1),
                                 _mm_cvttps_epi32(_mm_getexp_ps(v)));
        return _mm_mask_getmant_ps(v, isnonzerovalue, v, _MM_MANT_NORM_p5_1,
                                   _MM_MANT_SIGN_src);
    }
    static Vc_INTRINSIC simd_member_type<float> frexp(simd_member_type<float> v,
                                                simd_tuple<int, simd_abi::Sse> &exp)
    {
        return frexp(v, exp.first);
    }
#endif
    static Vc_INTRINSIC mask_member_type<float> isnan(simd_member_type<float> x)
    {
        return _mm_cmpunord_ps(x, x);
    }
    static Vc_INTRINSIC mask_member_type<double> isnan(simd_member_type<double> x)
    {
        return _mm_cmpunord_pd(x, x);
    }
    static Vc_INTRINSIC mask_member_type<float> isfinite(simd_member_type<float> x)
    {
        return _mm_cmpord_ps(x, _mm_mul_ps(_mm_setzero_ps(), x));
    }
    static Vc_INTRINSIC mask_member_type<double> isfinite(simd_member_type<double> x)
    {
        return _mm_cmpord_pd(x, _mm_mul_pd(_mm_setzero_pd(), x));
    }
    static Vc_INTRINSIC mask_member_type<float> isinf(simd_member_type<float> x)
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
        return __mmask8(_mm_fpclass_ps_mask(x, 0x08) | _mm_fpclass_ps_mask(x, 0x10));
#else
        return intrin_cast<__m128>(
            _mm_cmpeq_epi32(_mm_castps_si128(abs(x)), broadcast16(0x7f800000u)));
#endif
    }
    static Vc_INTRINSIC mask_member_type<double> isinf(simd_member_type<double> x)
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
        return __mmask8(_mm_fpclass_pd_mask(x, 0x08) | _mm_fpclass_pd_mask(x, 0x10));
#else
        return intrin_cast<__m128d>(
            equal_to(simd_member_type<llong>(abs(x)),
                     simd_member_type<llong>(broadcast16(0x7ff0000000000000ull))));
#endif
    }
    static Vc_INTRINSIC mask_member_type<float> isnormal(simd_member_type<float> x)
    {
        const auto tmp =
            and_(x, intrin_cast<__m128>(broadcast16(0x7f800000u)));
        return _mm_cmpord_ps(
            _mm_mul_ps(broadcast16(std::numeric_limits<float>::infinity()),
                       tmp),
            _mm_mul_ps(_mm_setzero_ps(), tmp));
    }
    static Vc_INTRINSIC mask_member_type<double> isnormal(simd_member_type<double> x)
    {
        const auto tmp =
            and_(x, intrin_cast<__m128d>(broadcast16(0x7ff0'0000'0000'0000ull)));
        return _mm_cmpord_pd(
            _mm_mul_pd(broadcast16(std::numeric_limits<double>::infinity()),
                       tmp),
            _mm_mul_pd(_mm_setzero_pd(), tmp));
    }
    static Vc_INTRINSIC mask_member_type<float> signbit(simd_member_type<float> x)
    {
        return _mm_castsi128_ps(
            _mm_srai_epi32(and_(intrin_cast<__m128i>(x), broadcast16(0x80000000u)), 31));
    }
    static Vc_INTRINSIC mask_member_type<double> signbit(simd_member_type<double> x)
    {
        const auto signbit = broadcast16(0x8000000000000000ull);
#ifdef Vc_HAVE_AVX512VL
        return _mm_castsi128_pd(
            _mm_srai_epi64(and_(intrin_cast<__m128i>(x), signbit), 63));
#elif defined Vc_HAVE_SSSE3
        return _mm_castsi128_pd(
            _mm_cmpeq_epi64(and_(intrin_cast<__m128i>(x), signbit), signbit));
#else
        return _mm_cmpneq_pd(or_(and_(intrin_cast<__m128d>(signbit), x), broadcast16(1.)),
                             broadcast16(1.));
#endif
    }
    static Vc_INTRINSIC mask_member_type<float> isunordered(simd_member_type<float> x,
                                                            simd_member_type<float> y)
    {
        return _mm_cmpunord_ps(x, y);
    }
    static Vc_INTRINSIC mask_member_type<double> isunordered(simd_member_type<double> x,
                                                             simd_member_type<double> y)
    {
        return _mm_cmpunord_pd(x, y);
    }
    static Vc_INTRINSIC simd_tuple<int, simd_abi::Sse> fpclassify(
        simd_member_type<float> x)
    {
        auto &&b = [](int y) { return intrin_cast<__m128>(broadcast16(y)); };
        return {_mm_castps_si128(blendv_ps(
            blendv_ps(blendv_ps(b(FP_NORMAL), b(FP_NAN), isnan(x)), b(FP_INFINITE),
                      isinf(x)),
            blendv_ps(b(FP_SUBNORMAL), b(FP_ZERO), _mm_cmpeq_ps(x, _mm_setzero_ps())),
            _mm_cmplt_ps(abs(x), broadcast16(std::numeric_limits<float>::min()))))};
    }
    static Vc_INTRINSIC simd_tuple<int, simd_abi::scalar, simd_abi::scalar> fpclassify(
        simd_member_type<double> x)
    {
        auto &&b = [](llong y) { return intrin_cast<__m128d>(broadcast16(y)); };
        const __m128i tmp = intrin_cast<__m128i>(blendv_pd(
            blendv_pd(blendv_pd(b(FP_NORMAL), b(FP_NAN), isnan(x)), b(FP_INFINITE),
                      isinf(x)),
            blendv_pd(b(FP_SUBNORMAL), b(FP_ZERO), _mm_cmpeq_pd(x, _mm_setzero_pd())),
            _mm_cmplt_pd(abs(x), broadcast16(std::numeric_limits<double>::min()))));
        return {_mm_cvtsi128_si32(tmp), {_mm_cvtsi128_si32(_mm_unpackhi_epi64(tmp, tmp))}};
    }
    template <class T>
    static Vc_INTRINSIC T Vc_VDECL get(simd_member_type<T> v, int i) noexcept
    {
        return v.m(i);
    }
    template <class T, class U>
    static Vc_INTRINSIC void set(simd_member_type<T> &v, int i, U &&x) noexcept
    {
        v.set(i, std::forward<U>(x));
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Sse, To, simd_abi::scalar> {
    using Arg = sse_simd_member_type<From>;
    Vc_INTRINSIC std::array<To, Arg::size()> operator()(Arg a)
    {
        return impl(std::make_index_sequence<Arg::size()>(), a);
    }
    template <size_t... Indexes>
    Vc_INTRINSIC std::array<To, Arg::size()> impl(std::index_sequence<Indexes...>, Arg a)
    {
        return {static_cast<To>(a[Indexes])...};
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::scalar, To, simd_abi::Sse> {
    using R = sse_simd_member_type<To>;
    Vc_INTRINSIC R operator()(From a)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        return r;
    }
    Vc_INTRINSIC R operator()(From a, From b)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        r.set(1, static_cast<To>(b));
        return r;
    }
    Vc_INTRINSIC R operator()(From a, From b, From c, From d)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        r.set(1, static_cast<To>(b));
        r.set(2, static_cast<To>(c));
        r.set(3, static_cast<To>(d));
        return r;
    }
    Vc_INTRINSIC R operator()(From a, From b, From c, From d, From e, From f, From g,
                              From h)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        r.set(1, static_cast<To>(b));
        r.set(2, static_cast<To>(c));
        r.set(3, static_cast<To>(d));
        r.set(4, static_cast<To>(e));
        r.set(5, static_cast<To>(f));
        r.set(6, static_cast<To>(g));
        r.set(7, static_cast<To>(h));
        return r;
    }
    Vc_INTRINSIC R operator()(From x0, From x1, From x2, From x3, From x4, From x5,
                              From x6, From x7, From x8, From x9, From x10, From x11,
                              From x12, From x13, From x14, From x15)
    {
        return R(static_cast<To>(x0), static_cast<To>(x1), static_cast<To>(x2),
                 static_cast<To>(x3), static_cast<To>(x4), static_cast<To>(x5),
                 static_cast<To>(x6), static_cast<To>(x7), static_cast<To>(x8),
                 static_cast<To>(x9), static_cast<To>(x10), static_cast<To>(x11),
                 static_cast<To>(x12), static_cast<To>(x13), static_cast<To>(x14),
                 static_cast<To>(x15));
    }
};
template <class T> struct simd_converter<T, simd_abi::Sse, T, simd_abi::Sse> {
    using Arg = sse_simd_member_type<T>;
    Vc_INTRINSIC const Arg &operator()(const Arg &x) { return x; }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Sse, To, simd_abi::Sse> {
    using Arg = sse_simd_member_type<From>;
    Vc_INTRINSIC auto operator()(Arg a)
    {
        return x86::convert_all<sse_simd_member_type<To>>(a);
    }
    Vc_INTRINSIC sse_simd_member_type<To> operator()(Arg a, Arg b)
    {
        static_assert(sizeof(From) >= 2 * sizeof(To), "");
        return x86::convert<Arg, sse_simd_member_type<To>>(a, b);
    }
    Vc_INTRINSIC sse_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
    {
        static_assert(sizeof(From) >= 4 * sizeof(To), "");
        return x86::convert<Arg, sse_simd_member_type<To>>(a, b, c, d);
    }
    Vc_INTRINSIC sse_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d, Arg e,
                                                     Arg f, Arg g, Arg h)
    {
        static_assert(sizeof(From) >= 8 * sizeof(To), "");
        return x86::convert<Arg, sse_simd_member_type<To>>(a, b, c, d, e, f, g, h);
    }
};
}
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#ifndef VC_SIMD_AVX_H_
#define VC_SIMD_AVX_H_ 
#ifdef Vc_HAVE_AVX_ABI
#ifndef VC_SIMD_X86_COMPARES_H_
#define VC_SIMD_X86_COMPARES_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace x86
{
#ifdef Vc_HAVE_AVX2
Vc_INTRINSIC Vc_CONST y_u64 Vc_VDECL cmpgt(y_u64 x, y_u64 y)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cmpgt_epu64_mask(x, y);
#elif defined Vc_HAVE_XOP
    return concat(_mm256_comgt_epu64(lo128(x), lo128(y)),
                  _mm256_comgt_epu64(hi128(x), hi128(y)));
#else
    return _mm256_cmpgt_epi64(xor_(x, lowest32<llong>()), xor_(y, lowest32<llong>()));
#endif
}
Vc_INTRINSIC Vc_CONST y_u32 Vc_VDECL cmpgt(y_u32 x, y_u32 y)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cmpgt_epu32_mask(x, y);
#elif defined Vc_HAVE_XOP
    return concat(_mm256_comgt_epu32(lo128(x), lo128(y)),
                  _mm256_comgt_epu32(hi128(x), hi128(y)));
#else
    return _mm256_cmpgt_epi32(xor_(x, lowest32<int>()), xor_(y, lowest32<int>()));
#endif
}
Vc_INTRINSIC Vc_CONST y_u16 Vc_VDECL cmpgt(y_u16 x, y_u16 y)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cmpgt_epu16_mask(x, y);
#elif defined Vc_HAVE_XOP
    return concat(_mm256_comgt_epu16(lo128(x), lo128(y)),
                  _mm256_comgt_epu16(hi128(x), hi128(y)));
#else
    return _mm256_cmpgt_epi16(xor_(x, lowest32<short>()), xor_(y, lowest32<short>()));
#endif
}
Vc_INTRINSIC Vc_CONST y_u08 Vc_VDECL cmpgt(y_u08 x, y_u08 y)
{
#ifdef Vc_HAVE_AVX512VL
    return _mm256_cmpgt_epu8_mask(x, y);
#elif defined Vc_HAVE_XOP
    return concat(_mm256_comgt_epu8(lo128(x), lo128(y)),
                  _mm256_comgt_epu8(hi128(x), hi128(y)));
#else
    return _mm256_cmpgt_epi8(xor_(x, lowest32<schar>()), xor_(y, lowest32<schar>()));
#endif
}
Vc_INTRINSIC Vc_CONST y_ulong Vc_VDECL cmpgt(y_ulong x, y_ulong y)
{
    return cmpgt(y_ulong_equiv(x), y_ulong_equiv(y)).v();
}
#endif
}}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
struct avx_mask_impl : public generic_mask_impl<simd_abi::Avx, avx_mask_member_type> {
    using abi = simd_abi::Avx;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using mask_member_type = avx_mask_member_type<T>;
    template <class T> using simd_mask = Vc::simd_mask<T, simd_abi::Avx>;
    template <class T> using mask_bool = MaskBool<sizeof(T)>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <typename T> static Vc_INTRINSIC auto broadcast(bool x, type_tag<T>) noexcept
    {
        return detail::broadcast32(T(mask_bool<T>{x}));
    }
    using generic_mask_impl<abi, avx_mask_member_type>::from_bitset;
    static Vc_INTRINSIC mask_member_type<float> from_bitset(std::bitset<8> bits,
                                                            type_tag<float>)
    {
        return _mm256_cmp_ps(
            _mm256_and_ps(_mm256_castsi256_ps(_mm256_set1_epi32(bits.to_ulong())),
                          _mm256_castsi256_ps(_mm256_setr_epi32(0x01, 0x02, 0x04, 0x08,
                                                                0x10, 0x20, 0x40, 0x80))),
            _mm256_setzero_ps(), _CMP_NEQ_UQ);
    }
    static Vc_INTRINSIC mask_member_type<double> from_bitset(std::bitset<4> bits,
                                                            type_tag<double>)
    {
        return _mm256_cmp_pd(
            _mm256_and_pd(
                _mm256_castsi256_pd(_mm256_set1_epi64x(bits.to_ulong())),
                _mm256_castsi256_pd(_mm256_setr_epi64x(0x01, 0x02, 0x04, 0x08))),
            _mm256_setzero_pd(), _CMP_NEQ_UQ);
    }
    template <class F>
    static Vc_INTRINSIC __m256 load(const bool *mem, F, size_tag<4>) noexcept
    {
#ifdef Vc_MSVC
        return intrin_cast<__m256>(x86::set(mem[0] ? 0xffffffffffffffffULL : 0ULL,
                                            mem[1] ? 0xffffffffffffffffULL : 0ULL,
                                            mem[2] ? 0xffffffffffffffffULL : 0ULL,
                                            mem[3] ? 0xffffffffffffffffULL : 0ULL));
#else
        __m128i k = intrin_cast<__m128i>(_mm_and_ps(
            _mm_set1_ps(*reinterpret_cast<const may_alias<float> *>(mem)),
            intrin_cast<__m128>(_mm_setr_epi32(0x1, 0x100, 0x10000, 0x1000000))));
        k = _mm_cmpgt_epi32(k, _mm_setzero_si128());
        return intrin_cast<__m256>(
            concat(_mm_unpacklo_epi32(k, k), _mm_unpackhi_epi32(k, k)));
#endif
    }
    template <class F>
    static Vc_INTRINSIC __m256 load(const bool *mem, F, size_tag<8>) noexcept
    {
#ifdef Vc_IS_AMD64
        __m128i k = _mm_cvtsi64_si128(*reinterpret_cast<const may_alias<int64_t> *>(mem));
#else
        __m128i k = _mm_castpd_si128(
            _mm_load_sd(reinterpret_cast<const may_alias<double> *>(mem)));
#endif
        k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128());
        return intrin_cast<__m256>(
            concat(_mm_unpacklo_epi16(k, k), _mm_unpackhi_epi16(k, k)));
    }
    template <class F>
    static Vc_INTRINSIC __m256i load(const bool *mem, F f, size_tag<16>) noexcept
    {
        const auto k128 = _mm_cmpgt_epi8(load16(mem, f), zero<__m128i>());
        return concat(_mm_unpacklo_epi8(k128, k128), _mm_unpackhi_epi8(k128, k128));
    }
    template <class F>
    static Vc_INTRINSIC __m256i load(const bool *mem, F f, size_tag<32>) noexcept
    {
        return _mm256_cmpgt_epi8(load32(mem, f), zero<__m256i>());
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F,
                                            size_tag<4>) noexcept
    {
        auto k = intrin_cast<__m256i>(v.v());
#ifdef Vc_HAVE_AVX2
        *reinterpret_cast<may_alias<int32_t> *>(mem) = _mm256_movemask_epi8(k) & 0x01010101;
#else
        *reinterpret_cast<may_alias<int32_t> *>(mem) =
            (_mm_movemask_epi8(lo128(k)) |
             (_mm_movemask_epi8(hi128(k)) << 16)) &
            0x01010101;
#endif
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F,
                                            size_tag<8>) noexcept
    {
        const auto k = intrin_cast<__m256i>(v.v());
        const auto k2 = x86::srli_epi16<15>(_mm_packs_epi16(lo128(k), hi128(k)));
        const auto k3 = _mm_packs_epi16(k2, _mm_setzero_si128());
#ifdef Vc_IS_AMD64
        *reinterpret_cast<may_alias<int64_t> *>(mem) = _mm_cvtsi128_si64(k3);
#else
        *reinterpret_cast<may_alias<int32_t> *>(mem) = _mm_cvtsi128_si32(k3);
        *reinterpret_cast<may_alias<int32_t> *>(mem + 4) = _mm_extract_epi32(k3, 1);
#endif
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F f,
                                            size_tag<16>) noexcept
    {
#ifdef Vc_HAVE_AVX2
        const auto x = x86::srli_epi16<15>(v);
        const auto bools = _mm_packs_epi16(lo128(x), hi128(x));
#else
        const auto bools =
            detail::and_(one16(uchar()), _mm_packs_epi16(lo128(v.v()), hi128(v.v())));
#endif
        store16(bools, mem, f);
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(mask_member_type<T> v, bool *mem, F f,
                                            size_tag<32>) noexcept
    {
        const auto bools = detail::and_(one32(uchar()), v.v());
        store32(bools, mem, f);
    }
    template <class T, class SizeTag>
    static Vc_INTRINSIC mask_member_type<T> negate(const mask_member_type<T> &x,
                                                   SizeTag) noexcept
    {
#if defined Vc_GCC && defined Vc_USE_BUILTIN_VECTOR_TYPES
        return !x.builtin();
#else
        return detail::not_(x.v());
#endif
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::and_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::or_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::and_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::or_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_xor(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::xor_(x.d, y.d)};
    }
    template <class T> static bool get(const mask_member_type<T> k, int i) noexcept
    {
        return k.m(i);
    }
    template <class T> static void set(mask_member_type<T> &k, int i, bool x) noexcept
    {
        k.set(i, mask_bool<T>(x));
    }
};
constexpr struct {
    template <class T> operator T() const { return detail::allone<T>(); }
} allone_poly = {};
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL all_of(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    return 0 != detail::testc(d, detail::allone_poly);
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL any_of(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    return 0 == detail::testz(d, d);
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL none_of(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    return 0 != detail::testz(d, d);
}
template <class T> Vc_ALWAYS_INLINE bool Vc_VDECL some_of(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    return 0 != detail::testnzc(d, detail::allone_poly);
}
template <class T> Vc_ALWAYS_INLINE int Vc_VDECL popcount(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    switch (k.size()) {
    case 4:
        return detail::popcnt4(detail::mask_to_int<k.size()>(d));
    case 8:
        return detail::popcnt8(detail::mask_to_int<k.size()>(d));
    case 16:
        return detail::popcnt32(detail::mask_to_int<32>(d)) / 2;
    case 32:
        return detail::popcnt32(detail::mask_to_int<k.size()>(d));
    default:
        Vc_UNREACHABLE();
        return 0;
    }
}
template <class T> Vc_ALWAYS_INLINE int Vc_VDECL find_first_set(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    return detail::firstbit(detail::mask_to_int<k.size()>(d));
}
template <class T> Vc_ALWAYS_INLINE int Vc_VDECL find_last_set(simd_mask<T, simd_abi::Avx> k)
{
    const auto d = detail::data(k);
    if (k.size() == 16) {
        return detail::lastbit(detail::mask_to_int<32>(d)) / 2;
    }
    return detail::lastbit(detail::mask_to_int<k.size()>(d));
}
namespace detail
{
struct avx_simd_impl : public generic_simd_impl<avx_simd_impl> {
    using abi = simd_abi::Avx;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using simd_member_type = avx_simd_member_type<T>;
    template <class T> using intrinsic_type = typename simd_member_type<T>::VectorType;
    template <class T> using mask_member_type = avx_mask_member_type<T>;
    template <class T> using simd = Vc::simd<T, abi>;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T>
    static Vc_INTRINSIC simd<T> make_simd(simd_member_type<T> x)
    {
        return {detail::private_init, x};
    }
    static Vc_INTRINSIC intrinsic_type<double> broadcast(double x, size_tag<4>) noexcept
    {
        return _mm256_set1_pd(x);
    }
    static Vc_INTRINSIC intrinsic_type<float> broadcast(float x, size_tag<8>) noexcept
    {
        return _mm256_set1_ps(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<4>) noexcept
    {
        return _mm256_set1_epi64x(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<8>) noexcept
    {
        return _mm256_set1_epi32(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<16>) noexcept
    {
        return _mm256_set1_epi16(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<32>) noexcept
    {
        return _mm256_set1_epi8(x);
    }
    template <class T, class F>
    static Vc_INTRINSIC simd_member_type<T> load(const long double *mem, F,
                                                    type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return generate_from_n_evaluations<size<T>(), simd_member_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
    }
    template <class T, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(const T *mem, F f, type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return detail::load32(mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T), T> *mem, F f, type_tag<T>,
        tag<1> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<simd_member_type<U>, simd_member_type<T>>(load32(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T) / 2, T> *mem, F f, type_tag<T>,
        tag<2> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<sse_simd_member_type<U>, simd_member_type<T>>(
            load16(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T) / 4, T> *mem, F f, type_tag<T>,
        tag<3> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<sse_simd_member_type<U>, simd_member_type<T>>(load8(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T) / 8, T> *mem, F f, type_tag<T>,
        tag<4> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<sse_simd_member_type<U>, simd_member_type<T>>(load4(mem, f));
    }
    template <class T> using avx512_member_type = avx512_simd_member_type<T>;
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T) * 2, T> *mem, F f, type_tag<T>,
        tag<5> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        return convert<avx512_member_type<U>, simd_member_type<T>>(
            load64(mem, f));
#else
        return convert<simd_member_type<U>, simd_member_type<T>>(
            load32(mem, f), load32(mem + size<U>(), f));
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T) * 4, T> *mem, F f, type_tag<T>,
        tag<6> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        using LoadT = avx512_member_type<U>;
        constexpr auto N = LoadT::size();
        return convert<LoadT, simd_member_type<T>>(load64(mem, f), load64(mem + N, f));
#else
        return convert<simd_member_type<U>, simd_member_type<T>>(
            load32(mem, f), load32(mem + size<U>(), f), load32(mem + 2 * size<U>(), f),
            load32(mem + 3 * size<U>(), f));
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const convertible_memory<U, sizeof(T) * 8, T> *mem, F f, type_tag<T>,
        tag<7> = {}) Vc_NOEXCEPT_OR_IN_TEST
    {
#ifdef Vc_HAVE_AVX512F
        using LoadT = avx512_member_type<U>;
        constexpr auto N = LoadT::size();
        return convert<LoadT, simd_member_type<T>>(load64(mem, f), load64(mem + N, f),
                                                      load64(mem + 2 * N, f),
                                                      load64(mem + 3 * N, f));
#else
        using LoadT = simd_member_type<U>;
        constexpr auto N = LoadT::size();
        return convert<simd_member_type<U>, simd_member_type<T>>(
            load32(mem, f), load32(mem + N, f), load32(mem + 2 * N, f),
            load32(mem + 3 * N, f), load32(mem + 4 * N, f), load32(mem + 5 * N, f),
            load32(mem + 6 * N, f), load32(mem + 7 * N, f));
#endif
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<T> &merge, mask_member_type<T> k,
                                                  const U *mem, F) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                merge.set(i, static_cast<T>(mem[i]));
            }
        });
    }
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<schar> &merge,
                                                  mask_member_type<schar> k, const schar *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm256_mask_loadu_epi8(merge, _mm256_movemask_epi8(k), mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<uchar> &merge,
                                                  mask_member_type<uchar> k, const uchar *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm256_mask_loadu_epi8(merge, _mm256_movemask_epi8(k), mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<short> &merge,
                                                  mask_member_type<short> k, const short *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm256_mask_loadu_epi16(merge, x86::movemask_epi16(k), mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<ushort> &merge,
                                                  mask_member_type<ushort> k, const ushort *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm256_mask_loadu_epi16(merge, x86::movemask_epi16(k), mem);
    }
#endif
#ifdef Vc_HAVE_AVX2
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<int> &merge,
                                                  mask_member_type<int> k, const int *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge), _mm256_maskload_epi32(mem, k));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<uint> &merge,
                                                  mask_member_type<uint> k, const uint *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge),
                    _mm256_maskload_epi32(
                        reinterpret_cast<const detail::may_alias<int> *>(mem), k));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<llong> &merge,
                                                  mask_member_type<llong> k, const llong *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge), _mm256_maskload_epi64(mem, k));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<ullong> &merge,
                                                  mask_member_type<ullong> k, const ullong *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge),
                    _mm256_maskload_epi64(
                        reinterpret_cast<const may_alias<long long> *>(mem), k));
    }
#endif
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<double> &merge,
                                                  mask_member_type<double> k, const double *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge),
                    _mm256_maskload_pd(mem, _mm256_castpd_si256(k)));
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<float> &merge,
                                                  mask_member_type<float> k, const float *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = or_(andnot_(k, merge),
                    _mm256_maskload_ps(mem, _mm256_castps_si256(k)));
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(simd_member_type<T> v, long double *mem, F,
                                            type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL store(simd_member_type<T> v, T *mem, F f,
                                            type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        store32(v, mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U) * 8> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U) * 4> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U) * 2> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) * 2 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) * 4 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL
    store(simd_member_type<T> v, U *mem, F, type_tag<T>,
          enable_if<sizeof(T) * 8 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class F>
    static Vc_INTRINSIC void Vc_VDECL
    masked_store(simd_member_type<T> v, long double *mem, F,
                 mask_member_type<T> k) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                mem[i] = v.m(i);
            }
        });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void Vc_VDECL masked_store(
        simd_member_type<T> v, U *mem, F, mask_member_type<T> k) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                mem[i] = static_cast<T>(v.m(i));
            }
        });
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> Vc_VDECL
    negate(simd_member_type<T> x) noexcept
    {
#if defined Vc_GCC && defined Vc_USE_BUILTIN_VECTOR_TYPES
        return !x.builtin();
#else
        return equal_to(x, simd_member_type<T>(x86::zero<intrinsic_type<T>>()));
#endif
    }
    template <class T, class BinaryOperation, size_t N>
    static Vc_INTRINSIC T Vc_VDECL reduce(size_tag<N>, simd<T> x,
                                          BinaryOperation &binary_op)
    {
        using V = Vc::simd<T, simd_abi::Sse>;
        return sse_simd_impl::reduce(size_tag<N / 2>(),
                                     binary_op(V(detail::private_init, lo128(data(x))),
                                               V(detail::private_init, hi128(data(x)))),
                                     binary_op);
    }
#define Vc_MINMAX_(T_,suffix_) \
    static Vc_INTRINSIC simd_member_type<T_> min(simd_member_type<T_> a, \
                                                    simd_member_type<T_> b) \
    { \
        return _mm256_min_##suffix_(a, b); \
    } \
    static Vc_INTRINSIC simd_member_type<T_> max(simd_member_type<T_> a, \
                                                    simd_member_type<T_> b) \
    { \
        return _mm256_max_##suffix_(a, b); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
    Vc_MINMAX_(double, pd);
    Vc_MINMAX_( float, ps);
#ifdef Vc_HAVE_AVX2
    Vc_MINMAX_( int, epi32);
    Vc_MINMAX_( uint, epu32);
    Vc_MINMAX_( short, epi16);
    Vc_MINMAX_(ushort, epu16);
    Vc_MINMAX_( schar, epi8);
    Vc_MINMAX_( uchar, epu8);
#endif
#ifdef Vc_HAVE_AVX512VL
    Vc_MINMAX_( llong, epi64);
    Vc_MINMAX_(ullong, epu64);
#elif defined Vc_HAVE_AVX2
    static Vc_INTRINSIC simd_member_type<llong> min(simd_member_type<llong> a,
                                                       simd_member_type<llong> b)
    {
        return _mm256_blendv_epi8(a, b, _mm256_cmpgt_epi64(a, b));
    }
    static Vc_INTRINSIC simd_member_type<llong> max(simd_member_type<llong> a,
                                                       simd_member_type<llong> b)
    {
        return _mm256_blendv_epi8(b, a, _mm256_cmpgt_epi64(a, b));
    } static Vc_INTRINSIC simd_member_type<ullong> min(simd_member_type<ullong> a,
                                                          simd_member_type<ullong> b)
    {
        return _mm256_blendv_epi8(a, b, cmpgt(a, b));
    }
    static Vc_INTRINSIC simd_member_type<ullong> max(simd_member_type<ullong> a,
                                                        simd_member_type<ullong> b)
    {
        return _mm256_blendv_epi8(b, a, cmpgt(a, b));
    }
#endif
#undef Vc_MINMAX_
#if defined Vc_HAVE_AVX2
    static Vc_INTRINSIC simd_member_type<long> min(simd_member_type<long> a,
                                                      simd_member_type<long> b)
    {
        return min(simd_member_type<equal_int_type_t<long>>(a.v()),
                   simd_member_type<equal_int_type_t<long>>(b.v()))
            .v();
    }
    static Vc_INTRINSIC simd_member_type<long> max(simd_member_type<long> a,
                                                      simd_member_type<long> b)
    {
        return max(simd_member_type<equal_int_type_t<long>>(a.v()),
                   simd_member_type<equal_int_type_t<long>>(b.v()))
            .v();
    }
    static Vc_INTRINSIC simd_member_type<ulong> min(simd_member_type<ulong> a,
                                                       simd_member_type<ulong> b)
    {
        return min(simd_member_type<equal_int_type_t<ulong>>(a.v()),
                   simd_member_type<equal_int_type_t<ulong>>(b.v()))
            .v();
    }
    static Vc_INTRINSIC simd_member_type<ulong> max(simd_member_type<ulong> a,
                                                       simd_member_type<ulong> b)
    {
        return max(simd_member_type<equal_int_type_t<ulong>>(a.v()),
                   simd_member_type<equal_int_type_t<ulong>>(b.v()))
            .v();
    }
#endif
    template <class T>
    static Vc_INTRINSIC std::pair<simd_member_type<T>, simd_member_type<T>> minmax(
        simd_member_type<T> a, simd_member_type<T> b)
    {
        return {min(a, b), max(a, b)};
    }
#if defined Vc_USE_BUILTIN_VECTOR_TYPES
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> equal_to(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() == y.builtin();
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> not_equal_to(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() != y.builtin();
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> less(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() < y.builtin();
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> less_equal(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() <= y.builtin();
    }
#else
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL equal_to (simd_member_type<double> x, simd_member_type<double> y) { return _mm256_cmp_pd(x, y, _CMP_EQ_OQ); }
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL not_equal_to(simd_member_type<double> x, simd_member_type<double> y) { return _mm256_cmp_pd(x, y, _CMP_NEQ_UQ); }
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL less (simd_member_type<double> x, simd_member_type<double> y) { return _mm256_cmp_pd(x, y, _CMP_LT_OS); }
    static Vc_INTRINSIC mask_member_type<double> Vc_VDECL less_equal (simd_member_type<double> x, simd_member_type<double> y) { return _mm256_cmp_pd(x, y, _CMP_LE_OS); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL equal_to (simd_member_type< float> x, simd_member_type< float> y) { return _mm256_cmp_ps(x, y, _CMP_EQ_OQ); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL not_equal_to(simd_member_type< float> x, simd_member_type< float> y) { return _mm256_cmp_ps(x, y, _CMP_NEQ_UQ); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL less (simd_member_type< float> x, simd_member_type< float> y) { return _mm256_cmp_ps(x, y, _CMP_LT_OS); }
    static Vc_INTRINSIC mask_member_type< float> Vc_VDECL less_equal (simd_member_type< float> x, simd_member_type< float> y) { return _mm256_cmp_ps(x, y, _CMP_LE_OS); }
#ifdef Vc_HAVE_FULL_AVX_ABI
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL equal_to(simd_member_type< llong> x, simd_member_type< llong> y) { return _mm256_cmpeq_epi64(x, y); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL equal_to(simd_member_type<ullong> x, simd_member_type<ullong> y) { return _mm256_cmpeq_epi64(x, y); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL equal_to(simd_member_type< long> x, simd_member_type< long> y) { return sizeof(long) == 8 ? _mm256_cmpeq_epi64(x, y) : _mm256_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL equal_to(simd_member_type< ulong> x, simd_member_type< ulong> y) { return sizeof(long) == 8 ? _mm256_cmpeq_epi64(x, y) : _mm256_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL equal_to(simd_member_type< int> x, simd_member_type< int> y) { return _mm256_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL equal_to(simd_member_type< uint> x, simd_member_type< uint> y) { return _mm256_cmpeq_epi32(x, y); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL equal_to(simd_member_type< short> x, simd_member_type< short> y) { return _mm256_cmpeq_epi16(x, y); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL equal_to(simd_member_type<ushort> x, simd_member_type<ushort> y) { return _mm256_cmpeq_epi16(x, y); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL equal_to(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm256_cmpeq_epi8(x, y); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL equal_to(simd_member_type< uchar> x, simd_member_type< uchar> y) { return _mm256_cmpeq_epi8(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL not_equal_to(simd_member_type< llong> x, simd_member_type< llong> y) { return detail::not_(_mm256_cmpeq_epi64(x, y)); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL not_equal_to(simd_member_type<ullong> x, simd_member_type<ullong> y) { return detail::not_(_mm256_cmpeq_epi64(x, y)); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL not_equal_to(simd_member_type< long> x, simd_member_type< long> y) { return detail::not_(sizeof(long) == 8 ? _mm256_cmpeq_epi64(x, y) : _mm256_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL not_equal_to(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::not_(sizeof(long) == 8 ? _mm256_cmpeq_epi64(x, y) : _mm256_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL not_equal_to(simd_member_type< int> x, simd_member_type< int> y) { return detail::not_(_mm256_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL not_equal_to(simd_member_type< uint> x, simd_member_type< uint> y) { return detail::not_(_mm256_cmpeq_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL not_equal_to(simd_member_type< short> x, simd_member_type< short> y) { return detail::not_(_mm256_cmpeq_epi16(x, y)); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL not_equal_to(simd_member_type<ushort> x, simd_member_type<ushort> y) { return detail::not_(_mm256_cmpeq_epi16(x, y)); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL not_equal_to(simd_member_type< schar> x, simd_member_type< schar> y) { return detail::not_(_mm256_cmpeq_epi8(x, y)); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL not_equal_to(simd_member_type< uchar> x, simd_member_type< uchar> y) { return detail::not_(_mm256_cmpeq_epi8(x, y)); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL less(simd_member_type< llong> x, simd_member_type< llong> y) { return _mm256_cmpgt_epi64(y, x); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL less(simd_member_type<ullong> x, simd_member_type<ullong> y) { return cmpgt(y, x); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL less(simd_member_type< long> x, simd_member_type< long> y) { return sizeof(long) == 8 ? _mm256_cmpgt_epi64(y, x) : _mm256_cmpgt_epi32(y, x); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL less(simd_member_type< ulong> x, simd_member_type< ulong> y) { return cmpgt(y, x); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL less(simd_member_type< int> x, simd_member_type< int> y) { return _mm256_cmpgt_epi32(y, x); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL less(simd_member_type< uint> x, simd_member_type< uint> y) { return cmpgt(y, x); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL less(simd_member_type< short> x, simd_member_type< short> y) { return _mm256_cmpgt_epi16(y, x); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL less(simd_member_type<ushort> x, simd_member_type<ushort> y) { return cmpgt(y, x); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL less(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm256_cmpgt_epi8 (y, x); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL less(simd_member_type< uchar> x, simd_member_type< uchar> y) { return cmpgt(y, x); }
    static Vc_INTRINSIC mask_member_type< llong> Vc_VDECL less_equal(simd_member_type< llong> x, simd_member_type< llong> y) { return detail::not_(_mm256_cmpgt_epi64(x, y)); }
    static Vc_INTRINSIC mask_member_type<ullong> Vc_VDECL less_equal(simd_member_type<ullong> x, simd_member_type<ullong> y) { return detail::not_(cmpgt(x, y)); }
    static Vc_INTRINSIC mask_member_type< long> Vc_VDECL less_equal(simd_member_type< long> x, simd_member_type< long> y) { return detail::not_(sizeof(long) == 8 ? _mm256_cmpgt_epi64(x, y) : _mm256_cmpgt_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< ulong> Vc_VDECL less_equal(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::not_(cmpgt(x, y)); }
    static Vc_INTRINSIC mask_member_type< int> Vc_VDECL less_equal(simd_member_type< int> x, simd_member_type< int> y) { return detail::not_(_mm256_cmpgt_epi32(x, y)); }
    static Vc_INTRINSIC mask_member_type< uint> Vc_VDECL less_equal(simd_member_type< uint> x, simd_member_type< uint> y) { return detail::not_(cmpgt(x, y)); }
    static Vc_INTRINSIC mask_member_type< short> Vc_VDECL less_equal(simd_member_type< short> x, simd_member_type< short> y) { return detail::not_(_mm256_cmpgt_epi16(x, y)); }
    static Vc_INTRINSIC mask_member_type<ushort> Vc_VDECL less_equal(simd_member_type<ushort> x, simd_member_type<ushort> y) { return detail::not_(cmpgt(x, y)); }
    static Vc_INTRINSIC mask_member_type< schar> Vc_VDECL less_equal(simd_member_type< schar> x, simd_member_type< schar> y) { return detail::not_(_mm256_cmpgt_epi8 (x, y)); }
    static Vc_INTRINSIC mask_member_type< uchar> Vc_VDECL less_equal(simd_member_type< uchar> x, simd_member_type< uchar> y) { return detail::not_(cmpgt (x, y)); }
#endif
#endif
    static Vc_INTRINSIC simd_member_type<float> sqrt(simd_member_type<float> x)
    {
        return _mm256_sqrt_ps(x);
    }
    static Vc_INTRINSIC simd_member_type<double> sqrt(simd_member_type<double> x)
    {
        return _mm256_sqrt_pd(x);
    }
#ifdef Vc_HAVE_AVX512F
    static Vc_INTRINSIC Vc_CONST simd_member_type<float> logb(simd_member_type<float> v)
    {
#ifdef Vc_HAVE_AVX512VL
        return _mm256_fixupimm_ps(_mm256_getexp_ps(abs(v)), v, broadcast32(0x00550433),
                                  0x00);
#else
        const __m512 vv = intrin_cast<__m512>(v);
        return lo256(_mm512_fixupimm_ps(_mm512_getexp_ps(_mm512_abs_ps(vv)), vv,
                                        broadcast64(0x00550433), 0x00));
#endif
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<double> logb(simd_member_type<double> v)
    {
#ifdef Vc_HAVE_AVX512VL
        return _mm256_fixupimm_pd(_mm256_getexp_pd(abs(v)), v, broadcast32(0x00550433),
                                  0x00);
#else
        const auto vv = intrin_cast<__m512d>(v);
        return lo256(_mm512_fixupimm_pd(_mm512_getexp_pd(_mm512_abs_pd(auto_cvt(v))), vv,
                                        broadcast64(0x00550433), 0x00));
#endif
    }
#endif
    static Vc_INTRINSIC simd_member_type<float> trunc(simd_member_type<float> x)
    {
        return _mm256_round_ps(x, 0x3);
    }
    static Vc_INTRINSIC simd_member_type<double> trunc(simd_member_type<double> x)
    {
        return _mm256_round_pd(x, 0x3);
    }
    static Vc_INTRINSIC simd_member_type<float> floor(simd_member_type<float> x)
    {
        return _mm256_round_ps(x, 0x1);
    }
    static Vc_INTRINSIC simd_member_type<double> floor(simd_member_type<double> x)
    {
        return _mm256_round_pd(x, 0x1);
    }
    static Vc_INTRINSIC simd_member_type<float> ceil(simd_member_type<float> x)
    {
        return _mm256_round_ps(x, 0x2);
    }
    static Vc_INTRINSIC simd_member_type<double> ceil(simd_member_type<double> x)
    {
        return _mm256_round_pd(x, 0x2);
    }
#ifdef Vc_HAVE_AVX512VL
    static inline simd_member_type<double> frexp(simd_member_type<double> v,
                                                 sse_simd_member_type<int> &exp)
    {
        const __mmask8 isnonzerovalue = _mm256_cmp_pd_mask(
            _mm256_mul_pd(broadcast32(std::numeric_limits<double>::infinity()),
                          v),
            _mm256_mul_pd(_mm256_setzero_pd(), v), _CMP_ORD_Q);
        if (Vc_IS_LIKELY(isnonzerovalue == 0xf)) {
            exp = _mm_add_epi32(broadcast16(1), _mm256_cvttpd_epi32(_mm256_getexp_pd(v)));
            return _mm256_getmant_pd(v, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
        }
        exp = _mm_mask_add_epi32(_mm_setzero_si128(), isnonzerovalue, broadcast16(1),
                                 _mm256_cvttpd_epi32(_mm256_getexp_pd(v)));
        return _mm256_mask_getmant_pd(v, isnonzerovalue, v, _MM_MANT_NORM_p5_1,
                                      _MM_MANT_SIGN_src);
    }
    static Vc_INTRINSIC simd_member_type<double> frexp(
        simd_member_type<double> v, simd_tuple<int, simd_abi::Sse> &exp)
    {
        return frexp(v, exp.first);
    }
    static inline simd_member_type<float> frexp(simd_member_type<float> v,
                                                avx_simd_member_type<int> &exp)
    {
        const __mmask8 isnonzerovalue = _mm256_cmp_ps_mask(
            _mm256_mul_ps(broadcast32(std::numeric_limits<float>::infinity()),
                          v),
            _mm256_mul_ps(_mm256_setzero_ps(), v), _CMP_ORD_Q);
        if (Vc_IS_LIKELY(isnonzerovalue == 0xff)) {
            exp = _mm256_add_epi32(broadcast32(1),
                                   _mm256_cvttps_epi32(_mm256_getexp_ps(v)));
            return _mm256_getmant_ps(v, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
        }
        exp =
            _mm256_mask_add_epi32(_mm256_setzero_si256(), isnonzerovalue, broadcast32(1),
                                  _mm256_cvttps_epi32(_mm256_getexp_ps(v)));
        return _mm256_mask_getmant_ps(v, isnonzerovalue, v, _MM_MANT_NORM_p5_1,
                                      _MM_MANT_SIGN_src);
    }
    static Vc_INTRINSIC simd_member_type<float> frexp(simd_member_type<float> v,
                                                      simd_tuple<int, simd_abi::Avx> &exp)
    {
        return frexp(v, exp.first);
    }
#endif
    static Vc_INTRINSIC mask_member_type<float> isfinite(simd_member_type<float> x)
    {
        return _mm256_cmp_ps(x, _mm256_mul_ps(_mm256_setzero_ps(), x), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isfinite(simd_member_type<double> x)
    {
        return _mm256_cmp_pd(x, _mm256_mul_pd(_mm256_setzero_pd(), x), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<float> isinf(simd_member_type<float> x)
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
        return __mmask8(_mm256_fpclass_ps_mask(x, 0x08) |
                        _mm256_fpclass_ps_mask(x, 0x10));
#else
        return less(y_f32(broadcast32(std::numeric_limits<float>::max())), abs(x));
#endif
    }
    static Vc_INTRINSIC mask_member_type<double> isinf(simd_member_type<double> x)
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512DQ
        return __mmask8(_mm256_fpclass_pd_mask(x, 0x08) |
                        _mm256_fpclass_pd_mask(x, 0x10));
#else
        return less(y_f64(broadcast32(std::numeric_limits<double>::max())), abs(x));
#endif
    }
    static Vc_INTRINSIC mask_member_type<float> isnan(simd_member_type<float> x)
    {
        return _mm256_cmp_ps(x, x, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isnan(simd_member_type<double> x)
    {
        return _mm256_cmp_pd(x, x, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<float> isnormal(simd_member_type<float> x)
    {
        const auto tmp =
            and_(x, intrin_cast<__m256>(broadcast32(0x7f800000u)));
        return _mm256_cmp_ps(
            _mm256_mul_ps(broadcast32(std::numeric_limits<float>::infinity()),
                          tmp),
            _mm256_mul_ps(_mm256_setzero_ps(), tmp), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isnormal(simd_member_type<double> x)
    {
        const auto tmp =
            and_(x, intrin_cast<__m256d>(broadcast32(0x7ff0'0000'0000'0000ull)));
        return _mm256_cmp_pd(
            _mm256_mul_pd(broadcast32(std::numeric_limits<double>::infinity()),
                          tmp),
            _mm256_mul_pd(_mm256_setzero_pd(), tmp), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<float> signbit(simd_member_type<float> x)
    {
        const auto signbit = broadcast32(0x80000000u);
#ifdef Vc_HAVE_AVX2
        return _mm256_castsi256_ps(
            _mm256_srai_epi32(and_(intrin_cast<__m256i>(x), signbit), 31));
#else
        return not_equal_to(
            y_f32(or_(and_(x, _mm256_castsi256_ps(signbit)), broadcast32(1.f))),
            y_f32(broadcast32(1.f)));
#endif
    }
    static Vc_INTRINSIC mask_member_type<double> signbit(simd_member_type<double> x)
    {
        const auto signbit = broadcast32(0x8000000000000000ull);
#ifdef Vc_HAVE_AVX512VL
        return _mm256_castsi256_pd(
            _mm256_srai_epi64(and_(intrin_cast<__m256i>(x), signbit), 63));
#elif defined Vc_HAVE_AVX2
        return _mm256_castsi256_pd(
            _mm256_cmpeq_epi64(and_(intrin_cast<__m256i>(x), signbit), signbit));
#else
        return not_equal_to(
            y_f64(or_(and_(x, _mm256_castsi256_pd(signbit)), broadcast32(1.))),
            y_f64(broadcast32(1.)));
#endif
    }
    static Vc_INTRINSIC mask_member_type<float> isunordered(simd_member_type<float> x,
                                                            simd_member_type<float> y)
    {
        return _mm256_cmp_ps(x, y, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isunordered(simd_member_type<double> x,
                                                             simd_member_type<double> y)
    {
        return _mm256_cmp_pd(x, y, _CMP_UNORD_Q);
    }
#ifdef Vc_HAVE_AVX2
    static Vc_INTRINSIC simd_tuple<int, simd_abi::Avx> fpclassify(
        simd_member_type<float> x)
    {
        auto &&b = [](int y) { return intrin_cast<__m256>(broadcast32(y)); };
        return {_mm256_castps_si256(_mm256_blendv_ps(
            _mm256_blendv_ps(_mm256_blendv_ps(b(FP_NORMAL), b(FP_NAN), isnan(x)),
                             b(FP_INFINITE), isinf(x)),
            _mm256_blendv_ps(b(FP_SUBNORMAL), b(FP_ZERO),
                             _mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_EQ_OQ)),
            _mm256_cmp_ps(abs(x), broadcast32(std::numeric_limits<float>::min()),
                          _CMP_LT_OS)))};
    }
#else
    static Vc_INTRINSIC simd_tuple<int, simd_abi::Sse, simd_abi::Sse> fpclassify(
        simd_member_type<float> x)
    {
        auto &&b = [](int y) { return intrin_cast<__m256>(broadcast32(y)); };
        const auto tmp = _mm256_castps_si256(_mm256_blendv_ps(
            _mm256_blendv_ps(_mm256_blendv_ps(b(FP_NORMAL), b(FP_NAN), isnan(x)),
                             b(FP_INFINITE), isinf(x)),
            _mm256_blendv_ps(b(FP_SUBNORMAL), b(FP_ZERO),
                             _mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_EQ_OQ)),
            _mm256_cmp_ps(abs(x), broadcast32(std::numeric_limits<float>::min()),
                          _CMP_LT_OS)));
        return {lo128(tmp), hi128(tmp)};
    }
#endif
    static Vc_INTRINSIC simd_tuple<int, simd_abi::Sse> fpclassify(
        simd_member_type<double> x)
    {
        auto &&b = [](llong y) { return intrin_cast<__m256d>(broadcast32(y)); };
        const __m256i tmp = intrin_cast<__m256i>(_mm256_blendv_pd(
            _mm256_blendv_pd(_mm256_blendv_pd(b(FP_NORMAL), b(FP_NAN), isnan(x)),
                             b(FP_INFINITE), isinf(x)),
            _mm256_blendv_pd(b(FP_SUBNORMAL), b(FP_ZERO),
                             _mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_EQ_OQ)),
            _mm256_cmp_pd(abs(x), broadcast32(std::numeric_limits<double>::min()),
                          _CMP_LT_OS)));
        return {_mm_packs_epi32(lo128(tmp), hi128(tmp))};
    }
    template <class T>
    static Vc_INTRINSIC T Vc_VDECL get(simd_member_type<T> v, int i) noexcept
    {
        return v.m(i);
    }
    template <class T, class U>
    static Vc_INTRINSIC void set(simd_member_type<T> &v, int i, U &&x) noexcept
    {
        v.set(i, std::forward<U>(x));
    }
    };
    template <class From, class To>
    struct simd_converter<From, simd_abi::Avx, To, simd_abi::scalar> {
        using Arg = avx_simd_member_type<From>;
        Vc_INTRINSIC std::array<To, Arg::size()> operator()(Arg a)
        {
            return impl(std::make_index_sequence<Arg::size()>(), a);
        }
        template <size_t... Indexes>
        Vc_INTRINSIC std::array<To, Arg::size()> impl(std::index_sequence<Indexes...>,
                                                      Arg a)
        {
            return {static_cast<To>(a[Indexes])...};
        }
    };
    template <class From, class To>
    struct simd_converter<From, simd_abi::scalar, To, simd_abi::Avx> {
        using R = avx_simd_member_type<To>;
        Vc_INTRINSIC R operator()(From a)
        {
            R r{};
            r.set(0, static_cast<To>(a));
            return r;
        }
        Vc_INTRINSIC R operator()(From a, From b)
        {
            R r{};
            r.set(0, static_cast<To>(a));
            r.set(1, static_cast<To>(b));
            return r;
        }
        Vc_INTRINSIC R operator()(From a, From b, From c, From d)
        {
            R r{};
            r.set(0, static_cast<To>(a));
            r.set(1, static_cast<To>(b));
            r.set(2, static_cast<To>(c));
            r.set(3, static_cast<To>(d));
            return r;
        }
        Vc_INTRINSIC R operator()(From a, From b, From c, From d, From e, From f, From g,
                                  From h)
        {
            R r{};
            r.set(0, static_cast<To>(a));
            r.set(1, static_cast<To>(b));
            r.set(2, static_cast<To>(c));
            r.set(3, static_cast<To>(d));
            r.set(4, static_cast<To>(e));
            r.set(5, static_cast<To>(f));
            r.set(6, static_cast<To>(g));
            r.set(7, static_cast<To>(h));
            return r;
        }
        Vc_INTRINSIC R operator()(From x0, From x1, From x2, From x3, From x4, From x5,
                                  From x6, From x7, From x8, From x9, From x10, From x11,
                                  From x12, From x13, From x14, From x15)
        {
            R r{};
            r.set(0, static_cast<To>(x0));
            r.set(1, static_cast<To>(x1));
            r.set(2, static_cast<To>(x2));
            r.set(3, static_cast<To>(x3));
            r.set(4, static_cast<To>(x4));
            r.set(5, static_cast<To>(x5));
            r.set(6, static_cast<To>(x6));
            r.set(7, static_cast<To>(x7));
            r.set(8, static_cast<To>(x8));
            r.set(9, static_cast<To>(x9));
            r.set(10, static_cast<To>(x10));
            r.set(11, static_cast<To>(x11));
            r.set(12, static_cast<To>(x12));
            r.set(13, static_cast<To>(x13));
            r.set(14, static_cast<To>(x14));
            r.set(15, static_cast<To>(x15));
            return r;
        }
        Vc_INTRINSIC R operator()(From x0, From x1, From x2, From x3, From x4, From x5,
                                  From x6, From x7, From x8, From x9, From x10, From x11,
                                  From x12, From x13, From x14, From x15, From x16,
                                  From x17, From x18, From x19, From x20, From x21,
                                  From x22, From x23, From x24, From x25, From x26,
                                  From x27, From x28, From x29, From x30, From x31)
        {
            return R(static_cast<To>(x0), static_cast<To>(x1), static_cast<To>(x2),
                     static_cast<To>(x3), static_cast<To>(x4), static_cast<To>(x5),
                     static_cast<To>(x6), static_cast<To>(x7), static_cast<To>(x8),
                     static_cast<To>(x9), static_cast<To>(x10), static_cast<To>(x11),
                     static_cast<To>(x12), static_cast<To>(x13), static_cast<To>(x14),
                     static_cast<To>(x15), static_cast<To>(x16), static_cast<To>(x17),
                     static_cast<To>(x18), static_cast<To>(x19), static_cast<To>(x20),
                     static_cast<To>(x21), static_cast<To>(x22), static_cast<To>(x23),
                     static_cast<To>(x24), static_cast<To>(x25), static_cast<To>(x26),
                     static_cast<To>(x27), static_cast<To>(x28), static_cast<To>(x29),
                     static_cast<To>(x30), static_cast<To>(x31));
        }
    };
    template <class From, class To>
    struct simd_converter<From, simd_abi::Sse, To, simd_abi::Avx> {
        using Arg = sse_simd_member_type<From>;
        Vc_INTRINSIC auto operator()(Arg a)
        {
            return x86::convert_all<avx_simd_member_type<To>>(a);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b)
        {
            static_assert(sizeof(From) >= 1 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(a, b);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
        {
            static_assert(sizeof(From) >= 2 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(a, b, c, d);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg x0, Arg x1, Arg x2, Arg x3,
                                                         Arg x4, Arg x5, Arg x6, Arg x7)
        {
            static_assert(sizeof(From) >= 4 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(x0, x1, x2, x3, x4, x5, x6,
                                                               x7);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg x0, Arg x1, Arg x2, Arg x3,
                                                         Arg x4, Arg x5, Arg x6, Arg x7,
                                                         Arg x8, Arg x9, Arg x10, Arg x11,
                                                         Arg x12, Arg x13, Arg x14,
                                                         Arg x15)
        {
            static_assert(sizeof(From) >= 8 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(
                x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
        }
    };
    template <class From, class To>
    struct simd_converter<From, simd_abi::Avx, To, simd_abi::Sse> {
        using Arg = avx_simd_member_type<From>;
        Vc_INTRINSIC auto operator()(Arg a)
        {
            return x86::convert_all<sse_simd_member_type<To>>(a);
        }
        Vc_INTRINSIC sse_simd_member_type<To> operator()(Arg a, Arg b)
        {
            static_assert(sizeof(From) >= 4 * sizeof(To), "");
            return x86::convert<Arg, sse_simd_member_type<To>>(a, b);
        }
        Vc_INTRINSIC sse_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
        {
            static_assert(sizeof(From) >= 8 * sizeof(To), "");
            return x86::convert<Arg, sse_simd_member_type<To>>(a, b, c, d);
        }
    };
    template <class T> struct simd_converter<T, simd_abi::Avx, T, simd_abi::Avx> {
        using Arg = avx_simd_member_type<T>;
        Vc_INTRINSIC const Arg &operator()(const Arg &x) { return x; }
    };
    template <class From, class To>
    struct simd_converter<From, simd_abi::Avx, To, simd_abi::Avx> {
        using Arg = avx_simd_member_type<From>;
        Vc_INTRINSIC auto operator()(Arg a)
        {
            return x86::convert_all<avx_simd_member_type<To>>(a);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b)
        {
            static_assert(sizeof(From) >= 2 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(a, b);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
        {
            static_assert(sizeof(From) >= 4 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(a, b, c, d);
        }
        Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d,
                                                         Arg e, Arg f, Arg g, Arg h)
        {
            static_assert(sizeof(From) >= 8 * sizeof(To), "");
            return x86::convert<Arg, avx_simd_member_type<To>>(a, b, c, d, e, f, g, h);
        }
    };
    template <class T> struct split_to_array<simd<T, simd_abi::Sse>, 2> {
        using V = simd<T, simd_abi::Sse>;
        std::array<V, 2> operator()(simd<T, simd_abi::Avx> x, std::index_sequence<0, 1>)
        {
            const auto xx = detail::data(x);
            return {V(detail::private_init, lo128(xx)),
                    V(detail::private_init, hi128(xx))};
        }
    };
    template <class T>
    struct split_to_tuple<std::tuple<simd<T, simd_abi::Sse>, simd<T, simd_abi::Sse>>,
                          simd_abi::Avx> {
        using V = simd<T, simd_abi::Sse>;
        std::tuple<V, V> operator()(simd<T, simd_abi::Avx> x)
        {
            const auto xx = detail::data(x);
            return {V(detail::private_init, lo128(xx)),
                    V(detail::private_init, hi128(xx))};
        }
    };
    }
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#ifndef VC_SIMD_AVX512_H_
#define VC_SIMD_AVX512_H_ 
#ifdef Vc_HAVE_AVX512_ABI
#ifndef _MM_CMPINT_EQ
#define _MM_CMPINT_EQ 0x0
#endif
#ifndef _MM_CMPINT_LT
#define _MM_CMPINT_LT 0x1
#endif
#ifndef _MM_CMPINT_LE
#define _MM_CMPINT_LE 0x2
#endif
#ifndef _MM_CMPINT_UNUSED
#define _MM_CMPINT_UNUSED 0x3
#endif
#ifndef _MM_CMPINT_NE
#define _MM_CMPINT_NE 0x4
#endif
#ifndef _MM_CMPINT_NLT
#define _MM_CMPINT_NLT 0x5
#endif
#ifndef _MM_CMPINT_GE
#define _MM_CMPINT_GE 0x5
#endif
#ifndef _MM_CMPINT_NLE
#define _MM_CMPINT_NLE 0x6
#endif
#ifndef _MM_CMPINT_GT
#define _MM_CMPINT_GT 0x6
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
struct avx512_simd_impl : public generic_simd_impl<avx512_simd_impl> {
    using abi = simd_abi::Avx512;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using simd_member_type = avx512_simd_member_type<T>;
    template <class T> using intrinsic_type = typename simd_member_type<T>::VectorType;
    template <class T> using mask_member_type = avx512_mask_member_type<T>;
    template <class T> using simd = Vc::simd<T, abi>;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T>
    static Vc_INTRINSIC simd<T> make_simd(simd_member_type<T> x)
    {
        return {detail::private_init, x};
    }
    static Vc_INTRINSIC intrinsic_type<double> broadcast(double x, size_tag<8>) noexcept
    {
        return _mm512_set1_pd(x);
    }
    static Vc_INTRINSIC intrinsic_type<float> broadcast(float x, size_tag<16>) noexcept
    {
        return _mm512_set1_ps(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<8>) noexcept
    {
        return _mm512_set1_epi64(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<16>) noexcept
    {
        return _mm512_set1_epi32(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<32>) noexcept
    {
        return _mm512_set1_epi16(x);
    }
    template <class T>
    static Vc_INTRINSIC intrinsic_type<T> broadcast(T x, size_tag<64>) noexcept
    {
        return _mm512_set1_epi8(x);
    }
    template <class T, class F>
    static Vc_INTRINSIC simd_member_type<T> load(const long double *mem, F,
                                                    type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
#if defined Vc_GCC && Vc_GCC < 0x60000
        alignas(sizeof(T) * size<T>()) T tmp[size<T>()];
        for (size_t i = 0; i < size<T>(); ++i) {
            tmp[i] = static_cast<T>(mem[i]);
        }
        return load(&tmp[0], vector_aligned, type_tag<T>());
#else
        return generate_from_n_evaluations<size<T>(), simd_member_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
#endif
    }
    template <class T, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(const T *mem, F f, type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return detail::load64(mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<simd_member_type<U>, simd_member_type<T>>(load64(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U) * 2> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<avx_simd_member_type<U>, simd_member_type<T>>(load32(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U) * 4> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<sse_simd_member_type<U>, simd_member_type<T>>(load16(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U) * 8> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<sse_simd_member_type<U>, simd_member_type<T>>(load8(mem, f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) * 2 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<simd_member_type<U>, simd_member_type<T>>(
            load64(mem, f), load64(mem + size<U>(), f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) * 4 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<simd_member_type<U>, simd_member_type<T>>(
            load64(mem, f), load64(mem + size<U>(), f), load64(mem + 2 * size<U>(), f),
            load64(mem + 3 * size<U>(), f));
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(
        const U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) * 8 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        return convert<simd_member_type<U>, simd_member_type<T>>(
            load64(mem, f), load64(mem + size<U>(), f), load64(mem + 2 * size<U>(), f),
            load64(mem + 3 * size<U>(), f), load64(mem + 4 * size<U>(), f),
            load64(mem + 5 * size<U>(), f), load64(mem + 6 * size<U>(), f),
            load64(mem + 7 * size<U>(), f));
    }
    template <class T, class U, class... Abis, size_t... Indexes>
    static Vc_INTRINSIC simd_member_type<T> convert_helper(
        const simd_tuple<U, Abis...> &uncvted, std::index_sequence<Indexes...>)
    {
        return x86::convert_to<simd_member_type<T>>(detail::get<Indexes>(uncvted)...);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void masked_load(simd_member_type<T> &merge, mask_member_type<T> k,
                                         const U *mem, F f) Vc_NOEXCEPT_OR_IN_TEST
    {
        static_assert(!std::is_same<T, U>::value, "");
        using fixed_traits = detail::traits<U, simd_abi::fixed_size<size<T>()>>;
        using fixed_impl = typename fixed_traits::simd_impl_type;
        typename fixed_traits::simd_member_type uncvted{};
        fixed_impl::masked_load(uncvted, static_cast<ullong>(k), mem, f);
        masked_assign(
            k, merge,
            convert_helper<T>(uncvted, std::make_index_sequence<uncvted.tuple_size>()));
    }
    template <class T, class F>
    static Vc_INTRINSIC void masked_load(simd_member_type<T> &merge, mask_member_type<T> k,
                                         const T *mem, F) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                merge.set(i, static_cast<T>(mem[i]));
            }
        });
    }
#if defined Vc_HAVE_AVX512BW
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<schar> &merge,
                                                  mask_member_type<schar> k, const schar *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi8(merge, k, mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<uchar> &merge,
                                                  mask_member_type<uchar> k, const uchar *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi8(merge, k, mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<short> &merge,
                                                  mask_member_type<short> k, const short *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi16(merge, k, mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<ushort> &merge,
                                                  mask_member_type<ushort> k, const ushort *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi16(merge, k, mem);
    }
#endif
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<int> &merge,
                                                  mask_member_type<int> k, const int *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi32(merge, k, mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<uint> &merge,
                                                  mask_member_type<uint> k, const uint *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi32(merge, k, mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<llong> &merge,
                                                  mask_member_type<llong> k, const llong *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi64(merge, k, mem);
    }
    template <class F>
    static Vc_INTRINSIC void Vc_VDECL masked_load(simd_member_type<ullong> &merge,
                                                  mask_member_type<ullong> k, const ullong *mem,
                                                  F) Vc_NOEXCEPT_OR_IN_TEST
    {
        merge = _mm512_mask_loadu_epi64(merge, k, mem);
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(simd_member_type<T> v, long double *mem, F,
                                   type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(simd_member_type<T> v, T *mem, F f,
                                   type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        store64(v, mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(
        simd_member_type<T> v, U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U) * 8> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store8(convert<simd_member_type<T>, sse_simd_member_type<U>>(v), mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(
        simd_member_type<T> v, U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U) * 4> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store16(convert<simd_member_type<T>, sse_simd_member_type<U>>(v), mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(
        simd_member_type<T> v, U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) == sizeof(U) * 2> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store32(convert<simd_member_type<T>, avx_simd_member_type<U>>(v), mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(simd_member_type<T> v, U *mem, F f, type_tag<T>,
                                   enable_if<sizeof(T) == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store64(convert<simd_member_type<T>, simd_member_type<U>>(v), mem, f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(
        simd_member_type<T> v, U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) * 2 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store64(convert<avx_simd_member_type<T>, simd_member_type<U>>(lo256(v)), mem, f);
        store64(convert<avx_simd_member_type<T>, simd_member_type<U>>(hi256(v)),
                mem + size<U>(), f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(
        simd_member_type<T> v, U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) * 4 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(lo128(v)), mem, f);
        store64(
            convert<sse_simd_member_type<T>, simd_member_type<U>>(extract128<1>(v)),
            mem + size<U>(), f);
        store64(
            convert<sse_simd_member_type<T>, simd_member_type<U>>(extract128<2>(v)),
            mem + 2 * size<U>(), f);
        store64(
            convert<sse_simd_member_type<T>, simd_member_type<U>>(extract128<3>(v)),
            mem + 3 * size<U>(), f);
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void store(
        simd_member_type<T> v, U *mem, F f, type_tag<T>,
        enable_if<sizeof(T) * 8 == sizeof(U)> = nullarg) Vc_NOEXCEPT_OR_IN_TEST
    {
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(lo128(v)), mem, f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(x86::shift_right<8>(lo128(v))), mem + 1 * size<U>(), f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(extract128<1>(v)), mem + 2 * size<U>(), f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(x86::shift_right<8>(extract128<1>(v))), mem + 3 * size<U>(), f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(extract128<2>(v)), mem + 4 * size<U>(), f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(x86::shift_right<8>(extract128<2>(v))), mem + 5 * size<U>(), f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(extract128<3>(v)), mem + 6 * size<U>(), f);
        store64(convert<sse_simd_member_type<T>, simd_member_type<U>>(x86::shift_right<8>(extract128<3>(v))), mem + 7 * size<U>(), f);
    }
    template <class T, class F>
    static Vc_INTRINSIC void masked_store(simd_member_type<T> v, long double *mem, F,
                                          mask_member_type<T> k) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                mem[i] = v.m(i);
            }
        });
    }
    template <class T, class U, class F>
    static Vc_INTRINSIC void masked_store(simd_member_type<T> v, U *mem, F,
                                          mask_member_type<T> k) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) {
            if (k.m(i)) {
                mem[i] = static_cast<T>(v.m(i));
            }
        });
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type<T> negate(simd_member_type<T> x) noexcept
    {
        return equal_to(x, x86::zero<typename simd_member_type<T>::VectorType>());
    }
    template <class T, class BinaryOperation, size_t N>
    static Vc_INTRINSIC T Vc_VDECL reduce(size_tag<N>, simd<T> x,
                                          BinaryOperation &binary_op)
    {
        using V = Vc::simd<T, simd_abi::Avx>;
        return avx_simd_impl::reduce(size_tag<N / 2>(),
                                     binary_op(V(detail::private_init, lo256(data(x))),
                                               V(detail::private_init, hi256(data(x)))),
                                     binary_op);
    }
#define Vc_MINMAX_(T_,suffix_) \
    static Vc_INTRINSIC simd_member_type<T_> min(simd_member_type<T_> a, \
                                                    simd_member_type<T_> b) \
    { \
        return _mm512_min_##suffix_(a, b); \
    } \
    static Vc_INTRINSIC simd_member_type<T_> max(simd_member_type<T_> a, \
                                                    simd_member_type<T_> b) \
    { \
        return _mm512_max_##suffix_(a, b); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
    Vc_MINMAX_(double, pd);
    Vc_MINMAX_( float, ps);
    Vc_MINMAX_( llong, epi64);
    Vc_MINMAX_(ullong, epu64);
    Vc_MINMAX_( int, epi32);
    Vc_MINMAX_( uint, epu32);
#ifdef Vc_HAVE_FULL_AVX512_ABI
    Vc_MINMAX_( short, epi16);
    Vc_MINMAX_(ushort, epu16);
    Vc_MINMAX_( schar, epi8);
    Vc_MINMAX_( uchar, epu8);
#endif
#undef Vc_MINMAX_
    static Vc_INTRINSIC __m512i min(simd_member_type<long> a,
                                    simd_member_type<long> b)
    {
        return min(simd_member_type<equal_int_type_t<long>>(a),
                   simd_member_type<equal_int_type_t<long>>(b));
    }
    static Vc_INTRINSIC __m512i max(simd_member_type<long> a,
                                    simd_member_type<long> b)
    {
        return max(simd_member_type<equal_int_type_t<long>>(a),
                   simd_member_type<equal_int_type_t<long>>(b));
    }
    static Vc_INTRINSIC __m512i min(simd_member_type<ulong> a,
                                    simd_member_type<ulong> b)
    {
        return min(simd_member_type<equal_int_type_t<ulong>>(a),
                   simd_member_type<equal_int_type_t<ulong>>(b));
    }
    static Vc_INTRINSIC __m512i max(simd_member_type<ulong> a,
                                    simd_member_type<ulong> b)
    {
        return max(simd_member_type<equal_int_type_t<ulong>>(a),
                   simd_member_type<equal_int_type_t<ulong>>(b));
    }
    template <class T>
    static Vc_INTRINSIC std::pair<simd_member_type<T>, simd_member_type<T>> minmax(
        simd_member_type<T> a, simd_member_type<T> b)
    {
        return {min(a, b), max(a, b)};
    }
#if 0
    template <class T>
    static Vc_INTRINSIC simd_mask<T> equal_to(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() == y.builtin()};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> not_equal_to(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() != y.builtin()};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> less(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() < y.builtin()};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> less_equal(simd_member_type<T> x, simd_member_type<T> y)
    {
        return x.builtin() <= y.builtin()};
    }
#else
    static Vc_INTRINSIC mask_member_type<double> equal_to (simd_member_type<double> x, simd_member_type<double> y) { return _mm512_cmp_pd_mask(x, y, _MM_CMPINT_EQ); }
    static Vc_INTRINSIC mask_member_type<double> not_equal_to(simd_member_type<double> x, simd_member_type<double> y) { return _mm512_cmp_pd_mask(x, y, _MM_CMPINT_NE); }
    static Vc_INTRINSIC mask_member_type<double> less (simd_member_type<double> x, simd_member_type<double> y) { return _mm512_cmp_pd_mask(x, y, _MM_CMPINT_LT); }
    static Vc_INTRINSIC mask_member_type<double> less_equal (simd_member_type<double> x, simd_member_type<double> y) { return _mm512_cmp_pd_mask(x, y, _MM_CMPINT_LE); }
    static Vc_INTRINSIC mask_member_type< float> equal_to (simd_member_type< float> x, simd_member_type< float> y) { return _mm512_cmp_ps_mask(x, y, _MM_CMPINT_EQ); }
    static Vc_INTRINSIC mask_member_type< float> not_equal_to(simd_member_type< float> x, simd_member_type< float> y) { return _mm512_cmp_ps_mask(x, y, _MM_CMPINT_NE); }
    static Vc_INTRINSIC mask_member_type< float> less (simd_member_type< float> x, simd_member_type< float> y) { return _mm512_cmp_ps_mask(x, y, _MM_CMPINT_LT); }
    static Vc_INTRINSIC mask_member_type< float> less_equal (simd_member_type< float> x, simd_member_type< float> y) { return _mm512_cmp_ps_mask(x, y, _MM_CMPINT_LE); }
    static Vc_INTRINSIC mask_member_type< llong> equal_to(simd_member_type< llong> x, simd_member_type< llong> y) { return _mm512_cmpeq_epi64_mask(x, y); }
    static Vc_INTRINSIC mask_member_type<ullong> equal_to(simd_member_type<ullong> x, simd_member_type<ullong> y) { return _mm512_cmpeq_epi64_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< long> equal_to(simd_member_type< long> x, simd_member_type< long> y) { return detail::cmpeq_long_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< ulong> equal_to(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::cmpeq_long_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< int> equal_to(simd_member_type< int> x, simd_member_type< int> y) { return _mm512_cmpeq_epi32_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< uint> equal_to(simd_member_type< uint> x, simd_member_type< uint> y) { return _mm512_cmpeq_epi32_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> not_equal_to(simd_member_type< llong> x, simd_member_type< llong> y) { return detail::not_(_mm512_cmpeq_epi64_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type<ullong> not_equal_to(simd_member_type<ullong> x, simd_member_type<ullong> y) { return detail::not_(_mm512_cmpeq_epi64_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< long> not_equal_to(simd_member_type< long> x, simd_member_type< long> y) { return detail::not_(detail::cmpeq_long_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< ulong> not_equal_to(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::not_(detail::cmpeq_long_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< int> not_equal_to(simd_member_type< int> x, simd_member_type< int> y) { return detail::not_(_mm512_cmpeq_epi32_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< uint> not_equal_to(simd_member_type< uint> x, simd_member_type< uint> y) { return detail::not_(_mm512_cmpeq_epi32_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< llong> less(simd_member_type< llong> x, simd_member_type< llong> y) { return _mm512_cmplt_epi64_mask(x, y); }
    static Vc_INTRINSIC mask_member_type<ullong> less(simd_member_type<ullong> x, simd_member_type<ullong> y) { return _mm512_cmplt_epu64_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< long> less(simd_member_type< long> x, simd_member_type< long> y) { return detail::cmplt_long_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< ulong> less(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::cmplt_ulong_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< int> less(simd_member_type< int> x, simd_member_type< int> y) { return _mm512_cmplt_epi32_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< uint> less(simd_member_type< uint> x, simd_member_type< uint> y) { return _mm512_cmplt_epu32_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< llong> less_equal(simd_member_type< llong> x, simd_member_type< llong> y) { return _mm512_cmple_epi64_mask(x, y); }
    static Vc_INTRINSIC mask_member_type<ullong> less_equal(simd_member_type<ullong> x, simd_member_type<ullong> y) { return _mm512_cmple_epu64_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< long> less_equal(simd_member_type< long> x, simd_member_type< long> y) { return detail::cmple_long_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< ulong> less_equal(simd_member_type< ulong> x, simd_member_type< ulong> y) { return detail::cmple_ulong_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< int> less_equal(simd_member_type< int> x, simd_member_type< int> y) { return _mm512_cmple_epi32_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< uint> less_equal(simd_member_type< uint> x, simd_member_type< uint> y) { return _mm512_cmple_epu32_mask(x, y); }
#ifdef Vc_HAVE_FULL_AVX512_ABI
    static Vc_INTRINSIC mask_member_type< short> equal_to(simd_member_type< short> x, simd_member_type< short> y) { return _mm512_cmpeq_epi16_mask(x, y); }
    static Vc_INTRINSIC mask_member_type<ushort> equal_to(simd_member_type<ushort> x, simd_member_type<ushort> y) { return _mm512_cmpeq_epi16_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< schar> equal_to(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm512_cmpeq_epi8_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< uchar> equal_to(simd_member_type< uchar> x, simd_member_type< uchar> y) { return _mm512_cmpeq_epi8_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< short> not_equal_to(simd_member_type< short> x, simd_member_type< short> y) { return detail::not_(_mm512_cmpeq_epi16_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type<ushort> not_equal_to(simd_member_type<ushort> x, simd_member_type<ushort> y) { return detail::not_(_mm512_cmpeq_epi16_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< schar> not_equal_to(simd_member_type< schar> x, simd_member_type< schar> y) { return detail::not_(_mm512_cmpeq_epi8_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< uchar> not_equal_to(simd_member_type< uchar> x, simd_member_type< uchar> y) { return detail::not_(_mm512_cmpeq_epi8_mask(x, y)); }
    static Vc_INTRINSIC mask_member_type< short> less(simd_member_type< short> x, simd_member_type< short> y) { return _mm512_cmplt_epi16_mask(x, y); }
    static Vc_INTRINSIC mask_member_type<ushort> less(simd_member_type<ushort> x, simd_member_type<ushort> y) { return _mm512_cmplt_epu16_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< schar> less(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm512_cmplt_epi8_mask (x, y); }
    static Vc_INTRINSIC mask_member_type< uchar> less(simd_member_type< uchar> x, simd_member_type< uchar> y) { return _mm512_cmplt_epu8_mask (x, y); }
    static Vc_INTRINSIC mask_member_type< short> less_equal(simd_member_type< short> x, simd_member_type< short> y) { return _mm512_cmple_epi16_mask(x, y); }
    static Vc_INTRINSIC mask_member_type<ushort> less_equal(simd_member_type<ushort> x, simd_member_type<ushort> y) { return _mm512_cmple_epu16_mask(x, y); }
    static Vc_INTRINSIC mask_member_type< schar> less_equal(simd_member_type< schar> x, simd_member_type< schar> y) { return _mm512_cmple_epi8_mask (x, y); }
    static Vc_INTRINSIC mask_member_type< uchar> less_equal(simd_member_type< uchar> x, simd_member_type< uchar> y) { return _mm512_cmple_epu8_mask (x, y); }
#endif
#endif
    static Vc_INTRINSIC simd_member_type<float> sqrt(simd_member_type<float> x)
    {
        return _mm512_sqrt_ps(x);
    }
    static Vc_INTRINSIC simd_member_type<double> sqrt(simd_member_type<double> x)
    {
        return _mm512_sqrt_pd(x);
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<float> logb_positive(simd_member_type<float> v)
    {
        return _mm512_getexp_ps(v);
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<double> logb_positive(simd_member_type<double> v)
    {
        return _mm512_getexp_pd(v);
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<float> logb(simd_member_type<float> v)
    {
        return _mm512_fixupimm_ps(logb_positive(abs(v)), v, broadcast64(0x00550433),
                                  0x00);
    }
    static Vc_INTRINSIC Vc_CONST simd_member_type<double> logb(simd_member_type<double> v)
    {
        return _mm512_fixupimm_pd(logb_positive(abs(v)), v, broadcast64(0x00550433),
                                  0x00);
    }
    static Vc_INTRINSIC simd_member_type<float> trunc(simd_member_type<float> x)
    {
        return _mm512_roundscale_round_ps(x, 0x03, _MM_FROUND_CUR_DIRECTION);
    }
    static Vc_INTRINSIC simd_member_type<double> trunc(simd_member_type<double> x)
    {
        return _mm512_roundscale_round_pd(x, 0x03, _MM_FROUND_CUR_DIRECTION);
    }
    static Vc_INTRINSIC simd_member_type<float> floor(simd_member_type<float> x)
    {
        return _mm512_roundscale_round_ps(x, 0x01, _MM_FROUND_CUR_DIRECTION);
    }
    static Vc_INTRINSIC simd_member_type<double> floor(simd_member_type<double> x)
    {
        return _mm512_roundscale_round_pd(x, 0x01, _MM_FROUND_CUR_DIRECTION);
    }
    static Vc_INTRINSIC simd_member_type<float> ceil(simd_member_type<float> x)
    {
        return _mm512_roundscale_round_ps(x, 0x02, _MM_FROUND_CUR_DIRECTION);
    }
    static Vc_INTRINSIC simd_member_type<double> ceil(simd_member_type<double> x)
    {
        return _mm512_roundscale_round_pd(x, 0x02, _MM_FROUND_CUR_DIRECTION);
    }
    static inline simd_member_type<double> frexp(simd_member_type<double> v,
                                                 avx_simd_member_type<int> &exp)
    {
        if (Vc_IS_LIKELY(detail::testallset(isnonzerovalue(v)))) {
            exp = _mm256_add_epi32(broadcast32(1),
                                   _mm512_cvttpd_epi32(_mm512_getexp_pd(v)));
            return _mm512_getmant_pd(v, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
        }
        exp = _mm256_add_epi32(
            broadcast32(1), _mm512_mask_cvttpd_epi32(broadcast32(-1), isnonzerovalue(v),
                                                     _mm512_getexp_pd(v)));
        return _mm512_mask_getmant_pd(v, isnonzerovalue(v), v, _MM_MANT_NORM_p5_1,
                                      _MM_MANT_SIGN_src);
    }
    static Vc_ALWAYS_INLINE simd_member_type<double> frexp(
        simd_member_type<double> v, simd_tuple<int, simd_abi::Avx> &exp)
    {
        return frexp(v, exp.first);
    }
    static inline simd_member_type<float> frexp(simd_member_type<float> v,
                                                simd_member_type<int> &exp)
    {
        if (Vc_IS_LIKELY(detail::testallset(isnonzerovalue(v)))) {
            exp = _mm512_add_epi32(broadcast64(1),
                                   _mm512_cvttps_epi32(_mm512_getexp_ps(v)));
            return _mm512_getmant_ps(v, _MM_MANT_NORM_p5_1, _MM_MANT_SIGN_src);
        }
        exp = _mm512_mask_add_epi32(_mm512_setzero_si512(), isnonzerovalue(v), broadcast64(1),
                                    _mm512_cvttps_epi32(_mm512_getexp_ps(v)));
        return _mm512_mask_getmant_ps(v, isnonzerovalue(v), v, _MM_MANT_NORM_p5_1,
                                      _MM_MANT_SIGN_src);
    }
    static Vc_ALWAYS_INLINE simd_member_type<float> frexp(
        simd_member_type<float> v, simd_tuple<int, simd_abi::Avx512> &exp)
    {
        return frexp(v, exp.first);
    }
    static Vc_INTRINSIC mask_member_type<float> isfinite(simd_member_type<float> x)
    {
        return _mm512_cmp_ps_mask(x, _mm512_mul_ps(_mm512_setzero_ps(), x), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isfinite(simd_member_type<double> x)
    {
        return _mm512_cmp_pd_mask(x, _mm512_mul_pd(_mm512_setzero_pd(), x), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<float> isinf(simd_member_type<float> x)
    {
#if defined Vc_HAVE_AVX512DQ
        return _mm512_fpclass_ps_mask(x, 0x08) | _mm512_fpclass_ps_mask(x, 0x10);
#else
        return _mm512_cmp_epi32_mask(
            _mm512_castps_si512(abs(x)), broadcast64(0x7f800000u), _CMP_EQ_OQ);
#endif
    }
    static Vc_INTRINSIC mask_member_type<double> isinf(simd_member_type<double> x)
    {
#if defined Vc_HAVE_AVX512DQ
        return _mm512_fpclass_pd_mask(x, 0x08) | _mm512_fpclass_pd_mask(x, 0x10);
#else
        return _mm512_cmp_epi64_mask(_mm512_castpd_si512(abs(x)),
                                     broadcast64(0x7ff0000000000000ull), _CMP_EQ_OQ);
#endif
    }
    static Vc_INTRINSIC mask_member_type<float> isnan(simd_member_type<float> x)
    {
        return _mm512_cmp_ps_mask(x, x, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isnan(simd_member_type<double> x)
    {
        return _mm512_cmp_pd_mask(x, x, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<float> isnonzerovalue(simd_member_type<float> x)
    {
        return _mm512_cmp_ps_mask(
            _mm512_mul_ps(broadcast64(std::numeric_limits<float>::infinity()),
                          x),
            _mm512_mul_ps(_mm512_setzero_ps(), x), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isnonzerovalue(
        simd_member_type<double> x)
    {
        return _mm512_cmp_pd_mask(
            _mm512_mul_pd(broadcast64(std::numeric_limits<double>::infinity()),
                          x),
            _mm512_mul_pd(_mm512_setzero_pd(), x), _CMP_ORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<float> isnormal(simd_member_type<float> x)
    {
        return isnonzerovalue(
            z_f32(and_(x, intrin_cast<__m512>(broadcast64(0x7f800000u)))));
    }
    static Vc_INTRINSIC mask_member_type<double> isnormal(simd_member_type<double> x)
    {
        return isnonzerovalue(
            z_f64(and_(x, intrin_cast<__m512d>(broadcast64(0x7ff0'0000'0000'0000ull)))));
    }
    static Vc_INTRINSIC mask_member_type<float> signbit(simd_member_type<float> x)
    {
#ifdef Vc_HAVE_AVX512DQ
        return _mm512_movepi32_mask(_mm512_castps_si512(x));
#else
        const auto signbit = broadcast64(0x80000000u);
        return _mm512_cmpeq_epi32_mask(and_(intrin_cast<__m512i>(x), signbit), signbit);
#endif
    }
    static Vc_INTRINSIC mask_member_type<double> signbit(simd_member_type<double> x)
    {
#ifdef Vc_HAVE_AVX512DQ
        return _mm512_movepi64_mask(_mm512_castpd_si512(x));
#else
        const auto signbit = broadcast64(0x8000000000000000ull);
        return _mm512_cmpeq_epi64_mask(and_(intrin_cast<__m512i>(x), signbit), signbit);
#endif
    }
    static Vc_INTRINSIC mask_member_type<float> isunordered(simd_member_type<float> x,
                                                            simd_member_type<float> y)
    {
        return _mm512_cmp_ps_mask(x, y, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC mask_member_type<double> isunordered(simd_member_type<double> x,
                                                             simd_member_type<double> y)
    {
        return _mm512_cmp_pd_mask(x, y, _CMP_UNORD_Q);
    }
    static Vc_INTRINSIC simd_tuple<int, simd_abi::Avx512> fpclassify(
        simd_member_type<float> x)
    {
        auto &&b = [](int y) { return broadcast64(y); };
        return {_mm512_mask_mov_epi32(
            _mm512_mask_mov_epi32(
                _mm512_mask_mov_epi32(b(FP_NORMAL), isnan(x), b(FP_NAN)), isinf(x),
                b(FP_INFINITE)),
            _mm512_cmp_ps_mask(abs(x), broadcast64(std::numeric_limits<float>::min()),
                               _CMP_LT_OS),
            _mm512_mask_mov_epi32(b(FP_SUBNORMAL),
                                  _mm512_cmp_ps_mask(x, _mm512_setzero_ps(), _CMP_EQ_OQ),
                                  b(FP_ZERO)))};
    }
    static Vc_INTRINSIC simd_tuple<int, simd_abi::Avx> fpclassify(
        simd_member_type<double> x)
    {
#ifdef Vc_HAVE_AVX512VL
        auto &&b = [](int y) { return broadcast32(y); };
        return {_mm256_mask_mov_epi32(
            _mm256_mask_mov_epi32(
                _mm256_mask_mov_epi32(b(FP_NORMAL), isnan(x), b(FP_NAN)), isinf(x),
                b(FP_INFINITE)),
            _mm512_cmp_pd_mask(abs(x), broadcast64(std::numeric_limits<double>::min()),
                               _CMP_LT_OS),
            _mm256_mask_mov_epi32(b(FP_SUBNORMAL),
                                  _mm512_cmp_pd_mask(x, _mm512_setzero_pd(), _CMP_EQ_OQ),
                                  b(FP_ZERO)))};
#else
        auto &&b = [](int y) { return broadcast64(y); };
        return {lo256(_mm512_mask_mov_epi32(
            _mm512_mask_mov_epi32(
                _mm512_mask_mov_epi32(b(FP_NORMAL), isnan(x), b(FP_NAN)), isinf(x),
                b(FP_INFINITE)),
            _mm512_cmp_pd_mask(abs(x), broadcast64(std::numeric_limits<double>::min()),
                               _CMP_LT_OS),
            _mm512_mask_mov_epi32(b(FP_SUBNORMAL),
                                  _mm512_cmp_pd_mask(x, _mm512_setzero_pd(), _CMP_EQ_OQ),
                                  b(FP_ZERO))))};
#endif
    }
    template <class T> static Vc_INTRINSIC T get(simd_member_type<T> v, int i) noexcept
    {
        return v.m(i);
    }
    template <class T, class U>
    static Vc_INTRINSIC void set(simd_member_type<T> &v, int i, U &&x) noexcept
    {
        v.set(i, std::forward<U>(x));
    }
};
struct avx512_mask_impl
    : public generic_mask_impl<simd_abi::Avx512, avx512_mask_member_type> {
    using abi = simd_abi::Avx512;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <size_t N> using mask_member_type = avx512_mask_member_type_n<N>;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    template <class T> using mask_bool = MaskBool<sizeof(T)>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <size_t N>
    static Vc_INTRINSIC std::bitset<N> to_bitset(mask_member_type<N> v) noexcept
    {
        return v.v();
    }
    template <size_t N, class T>
    static Vc_INTRINSIC mask_member_type<N> from_bitset(std::bitset<N> bits, type_tag<T>)
    {
        return bits.to_ullong();
    }
    static Vc_INTRINSIC __mmask8 broadcast_impl(bool x, size_tag<8>) noexcept
    {
        return static_cast<__mmask8>(x) * ~__mmask8();
    }
    static Vc_INTRINSIC __mmask16 broadcast_impl(bool x, size_tag<16>) noexcept
    {
        return static_cast<__mmask16>(x) * ~__mmask16();
    }
    static Vc_INTRINSIC __mmask32 broadcast_impl(bool x, size_tag<32>) noexcept
    {
        return static_cast<__mmask32>(x) * ~__mmask32();
    }
    static Vc_INTRINSIC __mmask64 broadcast_impl(bool x, size_tag<64>) noexcept
    {
        return static_cast<__mmask64>(x) * ~__mmask64();
    }
    template <typename T> static Vc_INTRINSIC auto broadcast(bool x, type_tag<T>) noexcept
    {
        return broadcast_impl(x, size_tag<size<T>()>());
    }
    template <class F>
    static Vc_INTRINSIC __mmask8 load(const bool *mem, F, size_tag<8>) noexcept
    {
        const auto a = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem));
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
        return _mm_test_epi8_mask(a, a);
#else
        const auto b = _mm512_cvtepi8_epi64(a);
        return _mm512_test_epi64_mask(b, b);
#endif
    }
    template <class F>
    static Vc_INTRINSIC __mmask16 load(const bool *mem, F f, size_tag<16>) noexcept
    {
        const auto a = load16(mem, f);
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
        return _mm_test_epi8_mask(a, a);
#else
        const auto b = _mm512_cvtepi8_epi32(a);
        return _mm512_test_epi32_mask(b, b);
#endif
    }
    template <class F>
    static Vc_INTRINSIC __mmask32 load(const bool *mem, F f, size_tag<32>) noexcept
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
        const auto a = load32(mem, f);
        return _mm256_test_epi8_mask(a, a);
#else
        const auto a = _mm512_cvtepi8_epi32(load16(mem, f));
        const auto b = _mm512_cvtepi8_epi32(load16(mem + 16, f));
        return _mm512_test_epi32_mask(a, a) | (_mm512_test_epi32_mask(b, b) << 16);
#endif
    }
    template <class F>
    static Vc_INTRINSIC __mmask64 load(const bool *mem, F f, size_tag<64>) noexcept
    {
#ifdef Vc_HAVE_AVX512BW
        const auto a = load64(mem, f);
        return _mm512_test_epi8_mask(a, a);
#else
        const auto a = _mm512_cvtepi8_epi32(load16(mem, f));
        const auto b = _mm512_cvtepi8_epi32(load16(mem + 16, f));
        const auto c = _mm512_cvtepi8_epi32(load16(mem + 32, f));
        const auto d = _mm512_cvtepi8_epi32(load16(mem + 48, f));
        return _mm512_test_epi32_mask(a, a) | (_mm512_test_epi32_mask(b, b) << 16) |
               (_mm512_test_epi32_mask(b, b) << 32) | (_mm512_test_epi32_mask(b, b) << 48);
#endif
    }
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
    template <class F>
    static Vc_INTRINSIC void masked_load(mask_member_type<8> &merge,
                                         mask_member_type<8> mask, const bool *mem,
                                         F) noexcept
    {
        const auto a = _mm_mask_loadu_epi8(zero<__m128i>(), mask.v(), mem);
        merge = (merge & ~mask) | _mm_test_epi8_mask(a, a);
    }
    template <class F>
    static Vc_INTRINSIC void masked_load(mask_member_type<16> &merge,
                                         mask_member_type<16> mask, const bool *mem,
                                         F) noexcept
    {
        const auto a = _mm_mask_loadu_epi8(zero<__m128i>(), mask.v(), mem);
        merge = (merge & ~mask) | _mm_test_epi8_mask(a, a);
    }
    template <class F>
    static Vc_INTRINSIC void masked_load(mask_member_type<32> &merge,
                                         mask_member_type<32> mask, const bool *mem,
                                         F) noexcept
    {
        const auto a = _mm256_mask_loadu_epi8(zero<__m256i>(), mask.v(), mem);
        merge = (merge & ~mask) | _mm256_test_epi8_mask(a, a);
    }
    template <class F>
    static Vc_INTRINSIC void masked_load(mask_member_type<64> &merge,
                                         mask_member_type<64> mask, const bool *mem,
                                         F) noexcept
    {
        const auto a = _mm512_mask_loadu_epi8(zero<__m512i>(), mask.v(), mem);
        merge = (merge & ~mask) | _mm512_test_epi8_mask(a, a);
    }
#else
    template <size_t N, class F>
    static Vc_INTRINSIC void masked_load(mask_member_type<N> &merge,
                                         const mask_member_type<N> mask, const bool *mem,
                                         F) noexcept
    {
        detail::execute_n_times<N>([&](auto i) {
            if (mask[i]) {
                merge.set(i, mem[i]);
            }
        });
    }
#endif
    template <class F>
    static Vc_INTRINSIC void store(mask_member_type<8> v, bool *mem, F,
                                   size_tag<8>) noexcept
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
        _mm_storel_epi64(reinterpret_cast<__m128i *>(mem),
                         and_(one16(uchar()), _mm_movm_epi8(v.v())));
#elif defined Vc_HAVE_AVX512DQ
        _mm_storel_epi64(
            reinterpret_cast<__m128i *>(mem),
            _mm512_cvtepi64_epi8(_mm512_srli_epi64(_mm512_movm_epi64(v.v()), 63)));
#elif defined Vc_IS_AMD64
        *reinterpret_cast<may_alias<ullong> *>(mem) =
            _pdep_u64(v.v(), 0x0101010101010101ULL);
#else
        *reinterpret_cast<may_alias<uint> *>(mem) =
            _pdep_u32(v.v(), 0x01010101U);
        *reinterpret_cast<may_alias<uint> *>(mem + 4) =
            _pdep_u32(v.v() >> 4, 0x01010101U);
#endif
    }
    template <class F>
    static Vc_INTRINSIC void store(mask_member_type<16> v, bool *mem, F f,
                                   size_tag<16>) noexcept
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
        x86::store16(and_(one16(uchar()), _mm_movm_epi8(v.v())), mem, f);
#elif defined Vc_HAVE_AVX512DQ
        store16(_mm512_cvtepi32_epi8(_mm512_srli_epi32(_mm512_movm_epi32(v.v()), 31)),
                mem, f);
#elif defined Vc_IS_AMD64
        *reinterpret_cast<may_alias<ullong> *>(mem) =
            _pdep_u64(v.v(), 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 8) =
            _pdep_u64(v.v() >> 8, 0x0101010101010101ULL);
        unused(f);
#else
        execute_n_times<4>([&](auto i) {
            using namespace Vc::detail;
            constexpr uint offset = 4u * i;
            *reinterpret_cast<may_alias<uint> *>(mem + offset) =
                _pdep_u32(v.v() >> offset, 0x01010101U);
        });
        unused(f);
#endif
    }
    template <class F>
    static Vc_INTRINSIC void store(mask_member_type<32> v, bool *mem, F f,
                                   size_tag<32>) noexcept
    {
#if defined Vc_HAVE_AVX512VL && defined Vc_HAVE_AVX512BW
        store32(and_(one32(uchar()), _mm256_movm_epi8(v.v())), mem, f);
#elif defined Vc_HAVE_AVX512DQ
        store32(
            concat(_mm512_cvtepi32_epi8(_mm512_srli_epi32(_mm512_movm_epi32(v.v()), 31)),
                   _mm512_cvtepi32_epi8(
                       _mm512_srli_epi32(_mm512_movm_epi32(v.v() >> 16), 31))),
            mem, f);
#elif defined Vc_IS_AMD64
        *reinterpret_cast<may_alias<ullong> *>(mem) =
            _pdep_u64(v.v(), 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 8) =
            _pdep_u64(v.v() >> 8, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 16) =
            _pdep_u64(v.v() >> 16, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 24) =
            _pdep_u64(v.v() >> 24, 0x0101010101010101ULL);
        unused(f);
#else
        execute_n_times<8>([&](auto i) {
            using namespace Vc::detail;
            constexpr uint offset = 4u * i;
            *reinterpret_cast<may_alias<uint> *>(mem + offset) =
                _pdep_u32(v.v() >> offset, 0x01010101U);
        });
        unused(f);
#endif
    }
    template <class F>
    static Vc_INTRINSIC void store(mask_member_type<64> v, bool *mem, F f,
                                   size_tag<64>) noexcept
    {
#if defined Vc_HAVE_AVX512BW
        store64(and_(one64(uchar()), _mm512_movm_epi8(v.v())), mem, f);
#elif defined Vc_HAVE_AVX512DQ
        store64(concat(concat(_mm512_cvtepi32_epi8(
                                  _mm512_srli_epi32(_mm512_movm_epi32(v.v()), 31)),
                              _mm512_cvtepi32_epi8(
                                  _mm512_srli_epi32(_mm512_movm_epi32(v.v() >> 16), 31))),
                       concat(_mm512_cvtepi32_epi8(
                                  _mm512_srli_epi32(_mm512_movm_epi32(v.v() >> 32), 31)),
                              _mm512_cvtepi32_epi8(
                                  _mm512_srli_epi32(_mm512_movm_epi32(v.v() >> 48), 31)))),
                mem, f);
#elif defined Vc_IS_AMD64
        *reinterpret_cast<may_alias<ullong> *>(mem) =
            _pdep_u64(v.v(), 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 8) =
            _pdep_u64(v.v() >> 8, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 16) =
            _pdep_u64(v.v() >> 16, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 24) =
            _pdep_u64(v.v() >> 24, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 32) =
            _pdep_u64(v.v() >> 32, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 40) =
            _pdep_u64(v.v() >> 40, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 48) =
            _pdep_u64(v.v() >> 48, 0x0101010101010101ULL);
        *reinterpret_cast<may_alias<ullong> *>(mem + 56) =
            _pdep_u64(v.v() >> 56, 0x0101010101010101ULL);
        unused(f);
#else
        execute_n_times<16>([&](auto i) {
            using namespace Vc::detail;
            constexpr uint offset = 4u * i;
            *reinterpret_cast<may_alias<uint> *>(mem + offset) =
                _pdep_u32(v.v() >> offset, 0x01010101U);
        });
        unused(f);
#endif
    }
#if defined Vc_HAVE_AVX512BW && defined Vc_HAVE_AVX512VL
    template <class F>
    static Vc_INTRINSIC void masked_store(mask_member_type<8> v, bool *mem, F,
                                          mask_member_type<8> k) noexcept
    {
        _mm_mask_storeu_epi8(mem, k.v(), and_(one16(uchar()), _mm_movm_epi8(v.v())));
    }
    template <class F>
    static Vc_INTRINSIC void masked_store(mask_member_type<16> v, bool *mem, F,
                                          mask_member_type<16> k) noexcept
    {
        _mm_mask_storeu_epi8(mem, k.v(), and_(one16(uchar()), _mm_movm_epi8(v.v())));
    }
    template <class F>
    static Vc_INTRINSIC void masked_store(mask_member_type<32> v, bool *mem, F,
                                          mask_member_type<32> k) noexcept
    {
        _mm256_mask_storeu_epi8(mem, k.v(), and_(one32(uchar()), _mm256_movm_epi8(v.v())));
    }
    template <class F>
    static Vc_INTRINSIC void masked_store(mask_member_type<64> v, bool *mem, F,
                                          mask_member_type<64> k) noexcept
    {
        _mm512_mask_storeu_epi8(mem, k.v(), and_(one64(uchar()), _mm512_movm_epi8(v.v())));
    }
#else
    template <size_t N, class F>
    static Vc_INTRINSIC void masked_store(mask_member_type<N> v, bool *mem, F,
                                          mask_member_type<N> k) noexcept
    {
        detail::execute_n_times<N>([&](auto i) {
            if (k[i]) {
                mem[i] = v[i];
            }
        });
    }
#endif
    template <class T, class SizeTag>
    static Vc_INTRINSIC T negate(const T &x, SizeTag) noexcept
    {
        return ~x.v();
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, mask_member_type<size<T>()>(x.d & y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, mask_member_type<size<T>()>(x.d | y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, mask_member_type<size<T>()>(x.d & y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, mask_member_type<size<T>()>(x.d | y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_xor(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, mask_member_type<size<T>()>(x.d ^ y.d)};
    }
    template <size_t N>
    static Vc_INTRINSIC bool get(mask_member_type<N> k, int i) noexcept
    {
        return k.m(i);
    }
    template <size_t N>
    static Vc_INTRINSIC void set(mask_member_type<N> &k, int i, bool x) noexcept
    {
        k.set(i, x);
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Avx512, To, simd_abi::scalar> {
    using Arg = avx512_simd_member_type<From>;
    Vc_INTRINSIC std::array<To, Arg::size()> operator()(Arg a)
    {
        return impl(std::make_index_sequence<Arg::size()>(), a);
    }
    template <size_t... Indexes>
    Vc_INTRINSIC std::array<To, Arg::size()> impl(std::index_sequence<Indexes...>, Arg a)
    {
        return {static_cast<To>(a[Indexes])...};
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::scalar, To, simd_abi::Avx512> {
    using R = avx512_simd_member_type<To>;
    Vc_INTRINSIC R operator()(From a)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        return r;
    }
    Vc_INTRINSIC R operator()(From a, From b)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        r.set(1, static_cast<To>(b));
        return r;
    }
    Vc_INTRINSIC R operator()(From a, From b, From c, From d)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        r.set(1, static_cast<To>(b));
        r.set(2, static_cast<To>(c));
        r.set(3, static_cast<To>(d));
        return r;
    }
    Vc_INTRINSIC R operator()(From a, From b, From c, From d, From e, From f, From g,
                              From h)
    {
        R r{};
        r.set(0, static_cast<To>(a));
        r.set(1, static_cast<To>(b));
        r.set(2, static_cast<To>(c));
        r.set(3, static_cast<To>(d));
        r.set(4, static_cast<To>(e));
        r.set(5, static_cast<To>(f));
        r.set(6, static_cast<To>(g));
        r.set(7, static_cast<To>(h));
        return r;
    }
    Vc_INTRINSIC R operator()(From x0, From x1, From x2, From x3, From x4, From x5,
                              From x6, From x7, From x8, From x9, From x10, From x11,
                              From x12, From x13, From x14, From x15)
    {
        R r{};
        r.set(0, static_cast<To>(x0));
        r.set(1, static_cast<To>(x1));
        r.set(2, static_cast<To>(x2));
        r.set(3, static_cast<To>(x3));
        r.set(4, static_cast<To>(x4));
        r.set(5, static_cast<To>(x5));
        r.set(6, static_cast<To>(x6));
        r.set(7, static_cast<To>(x7));
        r.set(8, static_cast<To>(x8));
        r.set(9, static_cast<To>(x9));
        r.set(10, static_cast<To>(x10));
        r.set(11, static_cast<To>(x11));
        r.set(12, static_cast<To>(x12));
        r.set(13, static_cast<To>(x13));
        r.set(14, static_cast<To>(x14));
        r.set(15, static_cast<To>(x15));
        return r;
    }
    Vc_INTRINSIC R operator()(From x0, From x1, From x2, From x3, From x4, From x5,
                              From x6, From x7, From x8, From x9, From x10, From x11,
                              From x12, From x13, From x14, From x15, From x16, From x17,
                              From x18, From x19, From x20, From x21, From x22, From x23,
                              From x24, From x25, From x26, From x27, From x28, From x29,
                              From x30, From x31)
    {
        R r{};
        r.set(0, static_cast<To>(x0));
        r.set(1, static_cast<To>(x1));
        r.set(2, static_cast<To>(x2));
        r.set(3, static_cast<To>(x3));
        r.set(4, static_cast<To>(x4));
        r.set(5, static_cast<To>(x5));
        r.set(6, static_cast<To>(x6));
        r.set(7, static_cast<To>(x7));
        r.set(8, static_cast<To>(x8));
        r.set(9, static_cast<To>(x9));
        r.set(10, static_cast<To>(x10));
        r.set(11, static_cast<To>(x11));
        r.set(12, static_cast<To>(x12));
        r.set(13, static_cast<To>(x13));
        r.set(14, static_cast<To>(x14));
        r.set(15, static_cast<To>(x15));
        r.set(16, static_cast<To>(x16));
        r.set(17, static_cast<To>(x17));
        r.set(18, static_cast<To>(x18));
        r.set(19, static_cast<To>(x19));
        r.set(20, static_cast<To>(x20));
        r.set(21, static_cast<To>(x21));
        r.set(22, static_cast<To>(x22));
        r.set(23, static_cast<To>(x23));
        r.set(24, static_cast<To>(x24));
        r.set(25, static_cast<To>(x25));
        r.set(26, static_cast<To>(x26));
        r.set(27, static_cast<To>(x27));
        r.set(28, static_cast<To>(x28));
        r.set(29, static_cast<To>(x29));
        r.set(30, static_cast<To>(x30));
        r.set(31, static_cast<To>(x31));
        return r;
    }
    Vc_INTRINSIC R operator()(From x0, From x1, From x2, From x3, From x4, From x5,
                              From x6, From x7, From x8, From x9, From x10, From x11,
                              From x12, From x13, From x14, From x15, From x16, From x17,
                              From x18, From x19, From x20, From x21, From x22, From x23,
                              From x24, From x25, From x26, From x27, From x28, From x29,
                              From x30, From x31, From x32, From x33, From x34, From x35,
                              From x36, From x37, From x38, From x39, From x40, From x41,
                              From x42, From x43, From x44, From x45, From x46, From x47,
                              From x48, From x49, From x50, From x51, From x52, From x53,
                              From x54, From x55, From x56, From x57, From x58, From x59,
                              From x60, From x61, From x62, From x63)
    {
        return R(static_cast<To>(x0), static_cast<To>(x1), static_cast<To>(x2),
                 static_cast<To>(x3), static_cast<To>(x4), static_cast<To>(x5),
                 static_cast<To>(x6), static_cast<To>(x7), static_cast<To>(x8),
                 static_cast<To>(x9), static_cast<To>(x10), static_cast<To>(x11),
                 static_cast<To>(x12), static_cast<To>(x13), static_cast<To>(x14),
                 static_cast<To>(x15), static_cast<To>(x16), static_cast<To>(x17),
                 static_cast<To>(x18), static_cast<To>(x19), static_cast<To>(x20),
                 static_cast<To>(x21), static_cast<To>(x22), static_cast<To>(x23),
                 static_cast<To>(x24), static_cast<To>(x25), static_cast<To>(x26),
                 static_cast<To>(x27), static_cast<To>(x28), static_cast<To>(x29),
                 static_cast<To>(x30), static_cast<To>(x31), static_cast<To>(x32),
                 static_cast<To>(x33), static_cast<To>(x34), static_cast<To>(x35),
                 static_cast<To>(x36), static_cast<To>(x37), static_cast<To>(x38),
                 static_cast<To>(x39), static_cast<To>(x40), static_cast<To>(x41),
                 static_cast<To>(x42), static_cast<To>(x43), static_cast<To>(x44),
                 static_cast<To>(x45), static_cast<To>(x46), static_cast<To>(x47),
                 static_cast<To>(x48), static_cast<To>(x49), static_cast<To>(x50),
                 static_cast<To>(x51), static_cast<To>(x52), static_cast<To>(x53),
                 static_cast<To>(x54), static_cast<To>(x55), static_cast<To>(x56),
                 static_cast<To>(x57), static_cast<To>(x58), static_cast<To>(x59),
                 static_cast<To>(x60), static_cast<To>(x61), static_cast<To>(x62),
                 static_cast<To>(x63));
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Sse, To, simd_abi::Avx512> {
    using Arg = sse_simd_member_type<From>;
    Vc_INTRINSIC auto operator()(Arg a)
    {
        return x86::convert_all<avx512_simd_member_type<To>>(a);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b)
    {
        static_assert(2 * sizeof(From) >= sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
    {
        static_assert(sizeof(From) >= 1 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b, c, d);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg x0, Arg x1, Arg x2, Arg x3,
                                                     Arg x4, Arg x5, Arg x6, Arg x7)
    {
        static_assert(sizeof(From) >= 2 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(x0, x1, x2, x3, x4, x5, x6,
                                                           x7);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg x0, Arg x1, Arg x2, Arg x3,
                                                     Arg x4, Arg x5, Arg x6, Arg x7,
                                                     Arg x8, Arg x9, Arg x10, Arg x11,
                                                     Arg x12, Arg x13, Arg x14, Arg x15)
    {
        static_assert(sizeof(From) >= 4 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(
            x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(
        Arg x0, Arg x1, Arg x2, Arg x3, Arg x4, Arg x5, Arg x6, Arg x7, Arg x8, Arg x9,
        Arg x10, Arg x11, Arg x12, Arg x13, Arg x14, Arg x15, Arg x16, Arg x17, Arg x18,
        Arg x19, Arg x20, Arg x21, Arg x22, Arg x23, Arg x24, Arg x25, Arg x26, Arg x27,
        Arg x28, Arg x29, Arg x30, Arg x31)
    {
        static_assert(sizeof(From) >= 8 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(
            x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16,
            x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31);
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Avx512, To, simd_abi::Sse> {
    using Arg = avx512_simd_member_type<From>;
    Vc_INTRINSIC auto operator()(Arg a)
    {
        return x86::convert_all<sse_simd_member_type<To>>(a);
    }
    Vc_INTRINSIC sse_simd_member_type<To> operator()(Arg a, Arg b)
    {
        static_assert(sizeof(From) >= 8 * sizeof(To), "");
        return x86::convert<Arg, sse_simd_member_type<To>>(a, b);
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Avx, To, simd_abi::Avx512> {
    using Arg = avx_simd_member_type<From>;
    Vc_INTRINSIC auto operator()(Arg a)
    {
        return x86::convert_all<avx512_simd_member_type<To>>(a);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b)
    {
        static_assert(sizeof(From) >= 1 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
    {
        static_assert(sizeof(From) >= 2 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b, c, d);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg x0, Arg x1, Arg x2, Arg x3,
                                                     Arg x4, Arg x5, Arg x6, Arg x7)
    {
        static_assert(sizeof(From) >= 4 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(x0, x1, x2, x3, x4, x5, x6,
                                                           x7);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg x0, Arg x1, Arg x2, Arg x3,
                                                     Arg x4, Arg x5, Arg x6, Arg x7,
                                                     Arg x8, Arg x9, Arg x10, Arg x11,
                                                     Arg x12, Arg x13, Arg x14, Arg x15)
    {
        static_assert(sizeof(From) >= 8 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(
            x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Avx512, To, simd_abi::Avx> {
    using Arg = avx512_simd_member_type<From>;
    Vc_INTRINSIC auto operator()(Arg a)
    {
        return x86::convert_all<avx_simd_member_type<To>>(a);
    }
    Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b)
    {
        static_assert(sizeof(From) >= 4 * sizeof(To), "");
        return x86::convert<Arg, avx_simd_member_type<To>>(a, b);
    }
    Vc_INTRINSIC avx_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
    {
        static_assert(sizeof(From) >= 8 * sizeof(To), "");
        return x86::convert<Arg, avx_simd_member_type<To>>(a, b, c, d);
    }
};
template <class T> struct simd_converter<T, simd_abi::Avx512, T, simd_abi::Avx512> {
    using Arg = avx512_simd_member_type<T>;
    Vc_INTRINSIC const Arg &operator()(const Arg &x) { return x; }
};
template <class From, class To>
struct simd_converter<From, simd_abi::Avx512, To, simd_abi::Avx512> {
    using Arg = avx512_simd_member_type<From>;
    Vc_INTRINSIC auto operator()(Arg a)
    {
        return x86::convert_all<avx512_simd_member_type<To>>(a);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b)
    {
        static_assert(sizeof(From) >= 2 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d)
    {
        static_assert(sizeof(From) >= 4 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b, c, d);
    }
    Vc_INTRINSIC avx512_simd_member_type<To> operator()(Arg a, Arg b, Arg c, Arg d, Arg e,
                                                     Arg f, Arg g, Arg h)
    {
        static_assert(sizeof(From) >= 8 * sizeof(To), "");
        return x86::convert<Arg, avx512_simd_member_type<To>>(a, b, c, d, e, f, g, h);
    }
};
template <class T> struct split_to_array<simd<T, simd_abi::Avx>, 2> {
    using V = simd<T, simd_abi::Avx>;
    std::array<V, 2> operator()(simd<T, simd_abi::Avx512> x, std::index_sequence<0, 1>)
    {
        const auto xx = detail::data(x);
        return {V(detail::private_init, lo256(xx)), V(detail::private_init, hi256(xx))};
    }
};
template <class T> struct split_to_array<simd<T, simd_abi::Sse>, 4> {
    using V = simd<T, simd_abi::Sse>;
    std::array<V, 4> operator()(simd<T, simd_abi::Avx512> x,
                                std::index_sequence<0, 1, 2, 3>)
    {
        const auto xx = detail::data(x);
        return {V(detail::private_init, lo128(xx)),
                V(detail::private_init, extract128<1>(xx)),
                V(detail::private_init, extract128<2>(xx)),
                V(detail::private_init, extract128<3>(xx))};
    }
};
template <class T>
struct split_to_tuple<std::tuple<simd<T, simd_abi::Avx>, simd<T, simd_abi::Avx>>,
                      simd_abi::Avx512> {
    using V = simd<T, simd_abi::Avx>;
    std::tuple<V, V> operator()(simd<T, simd_abi::Avx512> x)
    {
        const auto xx = detail::data(x);
        return {V(detail::private_init, lo256(xx)), V(detail::private_init, hi256(xx))};
    }
};
template <class T>
struct split_to_tuple<std::tuple<simd<T, simd_abi::Sse>, simd<T, simd_abi::Sse>,
                                 simd<T, simd_abi::Sse>, simd<T, simd_abi::Sse>>,
                      simd_abi::Avx512> {
    using V = simd<T, simd_abi::Sse>;
    std::tuple<V, V, V, V> operator()(simd<T, simd_abi::Avx512> x)
    {
        const auto xx = detail::data(x);
        return {V(detail::private_init, lo128(xx)),
                V(detail::private_init, extract128<1>(xx)),
                V(detail::private_init, extract128<2>(xx)),
                V(detail::private_init, extract128<3>(xx))};
    }
};
template <class T>
struct split_to_tuple<
    std::tuple<simd<T, simd_abi::Avx>, simd<T, simd_abi::Sse>, simd<T, simd_abi::Sse>>,
    simd_abi::Avx512> {
    using V0 = simd<T, simd_abi::Avx>;
    using V1 = simd<T, simd_abi::Sse>;
    std::tuple<V0, V1, V1> operator()(simd<T, simd_abi::Avx512> x)
    {
        const auto xx = detail::data(x);
        return {V0(detail::private_init, lo256(xx)),
                V1(detail::private_init, extract128<2>(xx)),
                V1(detail::private_init, extract128<3>(xx))};
    }
};
template <class T>
struct split_to_tuple<
    std::tuple<simd<T, simd_abi::Sse>, simd<T, simd_abi::Sse>, simd<T, simd_abi::Avx>>,
    simd_abi::Avx512> {
    using V0 = simd<T, simd_abi::Sse>;
    using V1 = simd<T, simd_abi::Avx>;
    std::tuple<V0, V0, V1> operator()(simd<T, simd_abi::Avx512> x)
    {
        const auto xx = detail::data(x);
        return {V0(detail::private_init, lo128(xx)),
                V0(detail::private_init, extract128<1>(xx)),
                V1(detail::private_init, hi256(xx))};
    }
};
template <class T>
struct split_to_tuple<
    std::tuple<simd<T, simd_abi::Sse>, simd<T, simd_abi::Avx>, simd<T, simd_abi::Sse>>,
    simd_abi::Avx512> {
    using V0 = simd<T, simd_abi::Sse>;
    using V1 = simd<T, simd_abi::Avx>;
    std::tuple<V0, V1, V0> operator()(simd<T, simd_abi::Avx512> x)
    {
        const auto xx = detail::data(x);
        return {V0(detail::private_init, lo128(xx)),
                V1(detail::private_init, extract256_center(xx)),
                V0(detail::private_init, extract128<3>(xx))};
    }
};
#define Vc_MASKED_CASSIGN_SPECIALIZATION(TYPE_,TYPE_SUFFIX_,OP_,OP_NAME_) \
    template <> \
    template <> \
    Vc_INTRINSIC void Vc_VDECL \
    generic_simd_impl<avx512_simd_impl>::masked_cassign<OP_, TYPE_, bool, \
                                                              64 / sizeof(TYPE_)>( \
        const Storage<bool, 64 / sizeof(TYPE_)> k, \
        Storage<TYPE_, 64 / sizeof(TYPE_)> &lhs, \
        const detail::id<Storage<TYPE_, 64 / sizeof(TYPE_)>> rhs) \
    { \
        lhs = _mm512_mask_##OP_NAME_##_##TYPE_SUFFIX_(lhs, k, lhs, rhs); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
Vc_MASKED_CASSIGN_SPECIALIZATION( double, pd , std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION( float, ps , std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: llong, epi64, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail::ullong, epi64, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION( long, epi64, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: ulong, epi64, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION( int, epi32, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: uint, epi32, std::plus, add);
#ifdef Vc_HAVE_FULL_AVX512_ABI
Vc_MASKED_CASSIGN_SPECIALIZATION( short, epi16, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail::ushort, epi16, std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: schar, epi8 , std::plus, add);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: uchar, epi8 , std::plus, add);
#endif
Vc_MASKED_CASSIGN_SPECIALIZATION( double, pd , std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION( float, ps , std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: llong, epi64, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail::ullong, epi64, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION( long, epi64, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: ulong, epi64, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION( int, epi32, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: uint, epi32, std::minus, sub);
#ifdef Vc_HAVE_FULL_AVX512_ABI
Vc_MASKED_CASSIGN_SPECIALIZATION( short, epi16, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail::ushort, epi16, std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: schar, epi8 , std::minus, sub);
Vc_MASKED_CASSIGN_SPECIALIZATION(detail:: uchar, epi8 , std::minus, sub);
#endif
#undef Vc_MASKED_CASSIGN_SPECIALIZATION
}
template <class T> Vc_ALWAYS_INLINE bool all_of(simd_mask<T, simd_abi::Avx512> k)
{
    const auto v = detail::data(k);
    return detail::x86::testallset(v);
}
template <class T> Vc_ALWAYS_INLINE bool any_of(simd_mask<T, simd_abi::Avx512> k)
{
    const auto v = detail::data(k);
    return v != 0U;
}
template <class T> Vc_ALWAYS_INLINE bool none_of(simd_mask<T, simd_abi::Avx512> k)
{
    const auto v = detail::data(k);
    return v == 0U;
}
template <class T> Vc_ALWAYS_INLINE bool some_of(simd_mask<T, simd_abi::Avx512> k)
{
    const auto v = detail::data(k);
    return v != 0 && !all_of(k);
}
template <class T> Vc_ALWAYS_INLINE int popcount(simd_mask<T, simd_abi::Avx512> k)
{
    const auto v = detail::data(k);
    switch (k.size()) {
    case 8: return detail::popcnt8(v);
    case 16: return detail::popcnt16(v);
    case 32: return detail::popcnt32(v);
    case 64: return detail::popcnt64(v);
    default: Vc_UNREACHABLE();
    }
}
template <class T> Vc_ALWAYS_INLINE int find_first_set(simd_mask<T, simd_abi::Avx512> k)
{
    const auto v = detail::data(k);
    return _tzcnt_u32(v);
}
#ifdef Vc_HAVE_FULL_AVX512_ABI
Vc_ALWAYS_INLINE int find_first_set(simd_mask<signed char, simd_abi::Avx512> k)
{
    const __mmask64 v = detail::data(k);
    return detail::firstbit(v);
}
Vc_ALWAYS_INLINE int find_first_set(simd_mask<unsigned char, simd_abi::Avx512> k)
{
    const __mmask64 v = detail::data(k);
    return detail::firstbit(v);
}
#endif
template <class T> Vc_ALWAYS_INLINE int find_last_set(simd_mask<T, simd_abi::Avx512> k)
{
    return 31 - _lzcnt_u32(detail::data(k));
}
#ifdef Vc_HAVE_FULL_AVX512_ABI
Vc_ALWAYS_INLINE int find_last_set(simd_mask<signed char, simd_abi::Avx512> k)
{
    const __mmask64 v = detail::data(k);
    return detail::lastbit(v);
}
Vc_ALWAYS_INLINE int find_last_set(simd_mask<unsigned char, simd_abi::Avx512> k)
{
    const __mmask64 v = detail::data(k);
    return detail::lastbit(v);
}
#endif
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#ifndef VC_SIMD_NEON_H_
#define VC_SIMD_NEON_H_ 
#ifdef Vc_HAVE_NEON
#ifndef VC_SIMD_AARCH_CONVERT_H_
#define VC_SIMD_AARCH_CONVERT_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace aarch
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])...};
}
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, From v1, std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])..., static_cast<T>(v1[I])...};
}
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3,
                                std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])..., static_cast<T>(v1[I])...,
                                static_cast<T>(v2[I])..., static_cast<T>(v3[I])...};
}
template <typename To, typename From, size_t... I>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3, From v4, From v5,
                                From v6, From v7, std::index_sequence<I...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I])..., static_cast<T>(v1[I])...,
                                static_cast<T>(v2[I])..., static_cast<T>(v3[I])...,
                                static_cast<T>(v4[I])..., static_cast<T>(v5[I])...,
                                static_cast<T>(v6[I])..., static_cast<T>(v7[I])...};
}
template <typename To, typename From, size_t... I0, size_t... I1>
Vc_INTRINSIC To convert_builtin(From v0, From v1, std::index_sequence<I0...>,
                                std::index_sequence<I1...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I0])..., static_cast<T>(v1[I0])...,
                                (I1, T{})...};
}
template <typename To, typename From, size_t... I0, size_t... I1>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3,
                                std::index_sequence<I0...>, std::index_sequence<I1...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{static_cast<T>(v0[I0])..., static_cast<T>(v1[I0])...,
                                static_cast<T>(v2[I0])..., static_cast<T>(v3[I0])...,
                                (I1, T{})...};
}
template <typename To, typename From, size_t... I0, size_t... I1>
Vc_INTRINSIC To convert_builtin(From v0, From v1, From v2, From v3, From v4, From v5,
                                From v6, From v7, std::index_sequence<I0...>,
                                std::index_sequence<I1...>)
{
    using T = typename To::EntryType;
    return typename To::Builtin{
        static_cast<T>(v0[I0])..., static_cast<T>(v1[I0])..., static_cast<T>(v2[I0])...,
        static_cast<T>(v3[I0])..., static_cast<T>(v4[I0])..., static_cast<T>(v5[I0])...,
        static_cast<T>(v6[I0])..., static_cast<T>(v7[I0])..., (I1, T{})...};
}
#endif
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0, x_f32 v1);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f32 v0, x_f32 v1, x_f32 v2, x_f32 v3);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_f64 v0, x_f64 v1, x_f64 v2, x_f64 v3, x_f64 v4, x_f64 v5, x_f64 v6, x_f64 v7);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_s08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u08);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_s16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_s16, x_s16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u16, x_u16);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_s32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_s32, x_s32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_s32, x_s32, x_s32, x_s32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32, x_u32);
template <typename To> Vc_INTRINSIC To Vc_VDECL convert_to(x_u32, x_u32, x_u32, x_u32);
template <typename To, size_t N> Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v)
{
    return convert_to<To>(Storage<equal_int_type_t<long>, N>(v));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v0, Storage<long, N> v1)
{
    return convert_to<To>(Storage<equal_int_type_t<long>, N>(v0),
                          Storage<equal_int_type_t<long>, N>(v1));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v0, Storage<long, N> v1, Storage<long, N> v2,
                           Storage<long, N> v3)
{
    return convert_to<To>(
        Storage<equal_int_type_t<long>, N>(v0), Storage<equal_int_type_t<long>, N>(v1),
        Storage<equal_int_type_t<long>, N>(v2), Storage<equal_int_type_t<long>, N>(v3));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<long, N> v0, Storage<long, N> v1, Storage<long, N> v2,
                           Storage<long, N> v3, Storage<long, N> v4, Storage<long, N> v5,
                           Storage<long, N> v6, Storage<long, N> v7)
{
    return convert_to<To>(
        Storage<equal_int_type_t<long>, N>(v0), Storage<equal_int_type_t<long>, N>(v1),
        Storage<equal_int_type_t<long>, N>(v2), Storage<equal_int_type_t<long>, N>(v3),
        Storage<equal_int_type_t<long>, N>(v4), Storage<equal_int_type_t<long>, N>(v5),
        Storage<equal_int_type_t<long>, N>(v6), Storage<equal_int_type_t<long>, N>(v7));
}
template <typename To, size_t N> Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v)
{
    return convert_to<To>(Storage<equal_int_type_t<ulong>, N>(v));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v0, Storage<ulong, N> v1)
{
    return convert_to<To>(Storage<equal_int_type_t<ulong>, N>(v0),
                          Storage<equal_int_type_t<ulong>, N>(v1));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v0, Storage<ulong, N> v1, Storage<ulong, N> v2,
                           Storage<ulong, N> v3)
{
    return convert_to<To>(
        Storage<equal_int_type_t<ulong>, N>(v0), Storage<equal_int_type_t<ulong>, N>(v1),
        Storage<equal_int_type_t<ulong>, N>(v2), Storage<equal_int_type_t<ulong>, N>(v3));
}
template <typename To, size_t N>
Vc_INTRINSIC To Vc_VDECL convert_to(Storage<ulong, N> v0, Storage<ulong, N> v1, Storage<ulong, N> v2,
                           Storage<ulong, N> v3, Storage<ulong, N> v4, Storage<ulong, N> v5,
                           Storage<ulong, N> v6, Storage<ulong, N> v7)
{
    return convert_to<To>(
        Storage<equal_int_type_t<ulong>, N>(v0), Storage<equal_int_type_t<ulong>, N>(v1),
        Storage<equal_int_type_t<ulong>, N>(v2), Storage<equal_int_type_t<ulong>, N>(v3),
        Storage<equal_int_type_t<ulong>, N>(v4), Storage<equal_int_type_t<ulong>, N>(v5),
        Storage<equal_int_type_t<ulong>, N>(v6), Storage<equal_int_type_t<ulong>, N>(v7));
}
struct scalar_conversion_fallback_tag {};
template <typename T> struct fallback_int_type { using type = scalar_conversion_fallback_tag; };
template <> struct fallback_int_type< uchar> { using type = schar; };
template <> struct fallback_int_type<ushort> { using type = short; };
template <> struct fallback_int_type< uint> { using type = int; };
template <typename T>
using equivalent_storage_t =
    Storage<typename fallback_int_type<typename T::EntryType>::type, T::size()>;
template <typename To, typename From>
Vc_INTRINSIC std::conditional_t<
    (std::is_integral<typename To::EntryType>::value &&
     sizeof(typename To::EntryType) <= sizeof(typename From::EntryType)),
    Storage<std::make_signed_t<typename From::EntryType>, From::size()>, From>
    Vc_VDECL maybe_make_signed(From v)
{
    static_assert(
        std::is_unsigned<typename From::EntryType>::value,
        "maybe_make_signed must only be used with unsigned integral Storage types");
    return std::conditional_t<
        (std::is_integral<typename To::EntryType>::value &&
         sizeof(typename To::EntryType) <= sizeof(typename From::EntryType)),
        Storage<std::make_signed_t<typename From::EntryType>, From::size()>, From>{v};
}
template <typename To,
          typename Fallback = typename fallback_int_type<typename To::EntryType>::type>
struct equivalent_conversion {
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<uchar, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<ushort, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<uint, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<ulong, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <size_t N, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(Storage<ullong, N> v0, From... vs)
    {
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(maybe_make_signed<To>(v0), maybe_make_signed<To>(vs)...).v();
    }
    template <typename F0, typename... From>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(F0 v0, From... vs)
    {
        static_assert(!std::is_unsigned<typename F0::EntryType>::value, "overload error");
        using S = Storage<Fallback, To::size()>;
        return convert_to<S>(v0, vs...).v();
    }
};
template <typename To> struct equivalent_conversion<To, scalar_conversion_fallback_tag> {
    template <typename From, typename... Fs>
    static Vc_INTRINSIC Vc_CONST To Vc_VDECL convert(From v0, Fs... vs)
    {
        using F = typename From::value_type;
        using T = typename To::value_type;
        static_assert(sizeof(F) >= sizeof(T) && std::is_integral<T>::value &&
                          std::is_unsigned<F>::value,
                      "missing an implementation for convert<To>(From, Fs...)");
        using S = Storage<typename fallback_int_type<F>::type, From::size()>;
        return convert_to<To>(S(v0), S(vs)...);
    }
};
template <typename From, typename To> Vc_INTRINSIC To Vc_VDECL convert(From v)
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    constexpr auto N = From::size() < To::size() ? From::size() : To::size();
    return convert_builtin<To>(v.builtin(), std::make_index_sequence<N>());
#else
    return convert_to<To>(v);
#endif
}
template <typename From, typename To> Vc_INTRINSIC To Vc_VDECL convert(From v0, From v1)
{
    static_assert(To::size() >= 2 * From::size(),
                  "convert(v0, v1) requires the input to fit into the output");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return convert_builtin<To>(
        v0.builtin(), v1.builtin(), std::make_index_sequence<From::size()>(),
        std::make_index_sequence<To::size() - 2 * From::size()>());
#else
    return convert_to<To>(v0, v1);
#endif
}
template <typename From, typename To>
Vc_INTRINSIC To Vc_VDECL convert(From v0, From v1, From v2, From v3)
{
    static_assert(To::size() >= 4 * From::size(),
                  "convert(v0, v1, v2, v3) requires the input to fit into the output");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return convert_builtin<To>(
        v0.builtin(), v1.builtin(), v2.builtin(), v3.builtin(),
        std::make_index_sequence<From::size()>(),
        std::make_index_sequence<To::size() - 4 * From::size()>());
#else
    return convert_to<To>(v0, v1, v2, v3);
#endif
}
template <typename From, typename To>
Vc_INTRINSIC To Vc_VDECL convert(From v0, From v1, From v2, From v3, From v4, From v5, From v6,
                        From v7)
{
    static_assert(To::size() >= 8 * From::size(),
                  "convert(v0, v1, v2, v3, v4, v5, v6, v7) "
                  "requires the input to fit into the output");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return convert_builtin<To>(
        v0.builtin(), v1.builtin(), v2.builtin(), v3.builtin(), v4.builtin(),
        v5.builtin(), v6.builtin(), v7.builtin(),
        std::make_index_sequence<From::size()>(),
        std::make_index_sequence<To::size() - 8 * From::size()>());
#else
    return convert_to<To>(v0, v1, v2, v3, v4, v5, v6, v7);
#endif
}
template <typename To, typename From>
Vc_INTRINSIC To Vc_VDECL convert_all_impl(From v, std::false_type)
{
    return convert<From, To>(v);
}
template <typename To, typename From> Vc_INTRINSIC auto Vc_VDECL convert_all(From v)
{
    return convert_all_impl<To, From>(
        v, std::integral_constant<bool, (From::size() > To::size())>());
}
}}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_AARCH_ARITHMETICS_H_
#define VC_SIMD_AARCH_ARITHMETICS_H_ 
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
namespace aarch
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto plus(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() + b.builtin();
}
#else
Vc_INTRINSIC float32x4_t Vc_VDECL plus(x_f32 a, x_f32 b) { }
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto minus(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() - b.builtin();
}
#else
Vc_INTRINSIC float32x4_t Vc_VDECL minus(x_f32 a, x_f32 b) { }
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto multiplies(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() * b.builtin();
}
#else
Vc_INTRINSIC float32x4_t Vc_VDECL multiplies(x_f32 a, x_f32 b) { }
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto divides(Storage<T, N> a, Storage<T, N> b)
{
    return a.builtin() / b.builtin();
}
#else
Vc_INTRINSIC x_f32 Vc_VDECL divides(x_f32 a, x_f32 b) {}
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto modulus(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "modulus is only supported for integral types");
    return a.builtin() % b.builtin();
}
#else
template <class T, size_t N> Vc_INTRINSIC auto modulus(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "modulus is only supported for integral types");
    return minus(a, multiplies(divides(a, b), b));
}
#endif
template <class T, size_t N> Vc_INTRINSIC auto bit_and(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_and is only supported for integral types");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return a.builtin() & b.builtin();
#else
    return and_(a, b);
#endif
}
template <class T, size_t N> Vc_INTRINSIC auto bit_or(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_or is only supported for integral types");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return a.builtin() | b.builtin();
#else
    return or_(a, b);
#endif
}
template <class T, size_t N> Vc_INTRINSIC auto bit_xor(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_xor is only supported for integral types");
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return a.builtin() ^ b.builtin();
#else
    return xor_(a, b);
#endif
}
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto bit_shift_left(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_left is only supported for integral types");
    return a.builtin() << b.builtin();
}
#else
template <class T, size_t N> Vc_INTRINSIC auto bit_shift_left(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_left is only supported for integral types");
    return generate_from_n_evaluations<N, Storage<T, N>>(
        [&](auto i) { return a[i] << b[i]; });
}
#endif
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template <class T, size_t N> Vc_INTRINSIC auto bit_shift_right(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_right is only supported for integral types");
    return a.builtin() >> b.builtin();
}
#else
template <class T, size_t N> Vc_INTRINSIC auto bit_shift_right(Storage<T, N> a, Storage<T, N> b)
{
    static_assert(std::is_integral<T>::value, "bit_shift_right is only supported for integral types");
    return generate_from_n_evaluations<N, Storage<T, N>>(
        [&](auto i) { return a[i] >> b[i]; });
}
#endif
template <typename T> Vc_INTRINSIC auto Vc_VDECL complement(T v) {
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
    return ~v.builtin();
#else
    return not_(v);
#endif
}
template <typename T> Vc_INTRINSIC auto Vc_VDECL unary_minus(T v) { return minus(T{}, v); }
Vc_INTRINSIC float32x4_t Vc_VDECL unary_minus(x_f32 v) {}
Vc_INTRINSIC float64x2_t Vc_VDECL unary_minus(x_f64 v) {}
Vc_INTRINSIC int32x4_t Vc_VDECL unary_minus(x_s32 v) {}
Vc_INTRINSIC int32x4_t Vc_VDECL unary_minus(x_u32 v) {}
Vc_INTRINSIC int32x4_t Vc_VDECL unary_minus(x_s16 v) {}
Vc_INTRINSIC int32x4_t Vc_VDECL unary_minus(x_u16 v) {}
Vc_INTRINSIC int32x4_t Vc_VDECL unary_minus(x_s08 v) {}
Vc_INTRINSIC int32x4_t Vc_VDECL unary_minus(x_u08 v) {}
}
}
Vc_VERSIONED_NAMESPACE_END
#endif
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
struct neon_mask_impl;
struct neon_simd_impl;
template <class T> using neon_simd_member_type = Storage<T, 16 / sizeof(T)>;
template <class T> using neon_mask_member_type = Storage<T, 16 / sizeof(T)>;
template <class T> struct traits<T, simd_abi::neon> {
    static_assert(sizeof(T) <= 8,
                  "NEON can only implement operations on element types with sizeof <= 8");
    using simd_member_type = neon_simd_member_type<T>;
    using simd_impl_type = neon_simd_impl;
    static constexpr size_t simd_member_alignment = alignof(simd_member_type);
    using simd_cast_type = typename simd_member_type::VectorType;
    struct simd_base {
        explicit operator simd_cast_type() const
        {
            return data(*static_cast<const simd<T, simd_abi::neon> *>(this));
        }
    };
    using mask_member_type = neon_mask_member_type<T>;
    using mask_impl_type = neon_mask_impl;
    static constexpr size_t mask_member_alignment = alignof(mask_member_type);
    using mask_cast_type = typename mask_member_type::VectorType;
    struct mask_base {
        explicit operator typename mask_member_type::VectorType() const
        {
            return data(*static_cast<const simd_mask<T, simd_abi::neon> *>(this));
        }
    };
};
}
Vc_VERSIONED_NAMESPACE_END
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail {
template <class Derived> struct generic_simd_impl {
    template <size_t N> using size_tag = std::integral_constant<size_t, N>;
    template <size_t Size>
    static Vc_INTRINSIC Storage<equal_int_type_t<long>, Size> Vc_VDECL
    adjust_for_long(Storage<long, Size> x)
    {
        return {x.v()};
    }
    template <size_t Size>
    static Vc_INTRINSIC Storage<equal_int_type_t<ulong>, Size> Vc_VDECL
    adjust_for_long(Storage<ulong, Size> x)
    {
        return {x.v()};
    }
    template <class T, size_t Size>
    static Vc_INTRINSIC const Storage<T, Size> &adjust_for_long(const Storage<T, Size> &x)
    {
        return x;
    }
    template <class T, class A, class U>
    static Vc_INTRINSIC Vc::simd<T, A> make_simd(const U &x)
    {
        using traits = typename Vc::simd<T, A>::traits;
        using V = typename traits::simd_member_type;
        return {private_init, static_cast<V>(x)};
    }
    template <class T, class A>
    static Vc_INTRINSIC Vc::simd<T, A> complement(const Vc::simd<T, A> &x) noexcept
    {
        using detail::aarch::complement;
        return make_simd<T, A>(complement(adjust_for_long(detail::data(x))));
    }
    template <class T, class A>
    static Vc_INTRINSIC Vc::simd<T, A> unary_minus(const Vc::simd<T, A> &x) noexcept
    {
        using detail::aarch::unary_minus;
        return make_simd<T, A>(unary_minus(adjust_for_long(detail::data(x))));
    }
#define Vc_ARITHMETIC_OP_(name_) \
    template <class T, class A> \
    static Vc_INTRINSIC simd<T, A> Vc_VDECL name_(simd<T, A> x, simd<T, A> y) \
    { \
        return make_simd<T, A>( \
            detail::name_(adjust_for_long(x.d), adjust_for_long(y.d))); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
    Vc_ARITHMETIC_OP_(plus);
    Vc_ARITHMETIC_OP_(minus);
    Vc_ARITHMETIC_OP_(multiplies);
    Vc_ARITHMETIC_OP_(divides);
    Vc_ARITHMETIC_OP_(modulus);
    Vc_ARITHMETIC_OP_(bit_and);
    Vc_ARITHMETIC_OP_(bit_or);
    Vc_ARITHMETIC_OP_(bit_xor);
    Vc_ARITHMETIC_OP_(bit_shift_left);
    Vc_ARITHMETIC_OP_(bit_shift_right);
#undef Vc_ARITHMETIC_OP_
    template <class T, size_t N> static Vc_INTRINSIC void increment(Storage<T, N> &x)
    {
        x = detail::plus(x, Storage<T, N>(Derived::broadcast(T(1), size_tag<N>())));
    }
    template <size_t N> static Vc_INTRINSIC void increment(Storage<long, N> &x)
    {
        x = detail::plus(adjust_for_long(x), Storage<equal_int_type_t<long>, N>(
                                                 Derived::broadcast(1L, size_tag<N>())));
    }
    template <size_t N> static Vc_INTRINSIC void increment(Storage<ulong, N> &x)
    {
        x = detail::plus(adjust_for_long(x), Storage<equal_int_type_t<ulong>, N>(
                                                 Derived::broadcast(1L, size_tag<N>())));
    }
    template <class T, size_t N> static Vc_INTRINSIC void decrement(Storage<T, N> &x)
    {
        x = detail::minus(x, Storage<T, N>(Derived::broadcast(T(1), size_tag<N>())));
    }
    template <size_t N> static Vc_INTRINSIC void decrement(Storage<long, N> &x)
    {
        x = detail::minus(adjust_for_long(x), Storage<equal_int_type_t<long>, N>(
                                                  Derived::broadcast(1L, size_tag<N>())));
    }
    template <size_t N> static Vc_INTRINSIC void decrement(Storage<ulong, N> &x)
    {
        x = detail::minus(adjust_for_long(x), Storage<equal_int_type_t<ulong>, N>(
                                                  Derived::broadcast(1L, size_tag<N>())));
    }
};
}
template <class T, class A>
inline void Vc_VDECL masked_assign(simd_mask<T, A> k, simd<T, A> &lhs,
                                   const detail::id<simd<T, A>> &rhs)
{
    lhs = static_cast<simd<T, A>>(
        detail::aarch::blend(detail::data(k), detail::data(lhs), detail::data(rhs)));
}
template <class T, class A>
inline void Vc_VDECL masked_assign(simd_mask<T, A> k, simd_mask<T, A> &lhs,
                                   const detail::id<simd_mask<T, A>> &rhs)
{
    lhs = static_cast<simd_mask<T, A>>(
        detail::aarch::blend(detail::data(k), detail::data(lhs), detail::data(rhs)));
}
template <template <typename> class Op, typename T, class A,
          int = 1>
inline void Vc_VDECL masked_cassign(simd_mask<T, A> k, simd<T, A> &lhs,
                                    const simd<T, A> &rhs)
{
    lhs = static_cast<simd<T, A>>(detail::aarch::blend(
        detail::data(k), detail::data(lhs), detail::data(Op<void>{}(lhs, rhs))));
}
template <template <typename> class Op, typename T, class A, class U>
inline enable_if<std::is_convertible<U, simd<T, A>>::value, void> Vc_VDECL
masked_cassign(simd_mask<T, A> k, simd<T, A> &lhs, const U &rhs)
{
    masked_cassign<Op>(k, lhs, simd<T, A>(rhs));
}
template <template <typename> class Op, typename T, class A,
          int = 1>
inline simd<T, A> Vc_VDECL masked_unary(simd_mask<T, A> k, simd<T, A> v)
{
    Op<simd<T, A>> op;
    return static_cast<simd<T, A>>(
        detail::aarch::blend(detail::data(k), detail::data(v), detail::data(op(v))));
}
Vc_VERSIONED_NAMESPACE_END
#ifdef Vc_HAVE_NEON_ABI
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
struct neon_simd_impl : public generic_simd_impl<neon_simd_impl> {
    using abi = simd_abi::neon;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using simd_member_type = neon_simd_member_type<T>;
    template <class T> using intrinsic_type = typename simd_member_type<T>::VectorType;
    template <class T> using mask_member_type = neon_mask_member_type<T>;
    template <class T> using simd = Vc::simd<T, abi>;
    template <class T> using simd_mask = Vc::simd_mask<T, abi>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T, class F>
    static Vc_INTRINSIC simd_member_type<T> load(const long double *mem, F,
                                                    type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return generate_from_n_evaluations<size<T>(), simd_member_type<T>>(
            [&](auto i) { return static_cast<T>(mem[i]); });
    }
    template <class T, class F>
    static Vc_INTRINSIC intrinsic_type<T> load(const T *mem, F f, type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return detail::load16(mem, f);
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(simd_member_type<T> v, long double *mem, F,
                                   type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        execute_n_times<size<T>()>([&](auto i) { mem[i] = v.m(i); });
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(simd_member_type<T> v, T *mem, F f,
                                   type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        store16(v, mem, f);
    }
};
struct neon_mask_impl {
    using abi = simd_abi::neon;
    template <class T> static constexpr size_t size() { return simd_size_v<T, abi>; }
    template <class T> using mask_member_type = neon_mask_member_type<T>;
    template <class T> using simd_mask = Vc::simd_mask<T, simd_abi::neon>;
    template <class T> using mask_bool = MaskBool<sizeof(T)>;
    template <size_t N> using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T> static Vc_INTRINSIC auto broadcast(bool x, type_tag<T>) noexcept
    {
        return detail::aarch::broadcast16(T(mask_bool<T>{x}));
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<4>) noexcept
    {
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<2>) noexcept
    {
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<8>) noexcept
    {
    }
    template <class F>
    static Vc_INTRINSIC auto load(const bool *mem, F, size_tag<16>) noexcept
    {
    }
    template <class T, class F, class SizeTag>
    static Vc_INTRINSIC void masked_load(mask_member_type<T> &merge,
                                         mask_member_type<T> mask, const bool *mem, F,
                                         SizeTag s) noexcept
    {
        for (std::size_t i = 0; i < s; ++i) {
            if (mask.m(i)) {
                merge.set(i, mask_bool<T>{mem[i]});
            }
        }
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(mask_member_type<T> v, bool *mem, F,
                                   size_tag<2>) noexcept
    {
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(mask_member_type<T> v, bool *mem, F,
                                   size_tag<4>) noexcept
    {
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(mask_member_type<T> v, bool *mem, F,
                                   size_tag<8>) noexcept
    {
    }
    template <class T, class F>
    static Vc_INTRINSIC void store(mask_member_type<T> v, bool *mem, F,
                                   size_tag<16>) noexcept
    {
    }
    template <class T, class F, class SizeTag>
    static Vc_INTRINSIC void masked_store(mask_member_type<T> v, bool *mem, F,
                                          mask_member_type<T> k, SizeTag) noexcept
    {
        for (std::size_t i = 0; i < size<T>(); ++i) {
            if (k.m(i)) {
                mem[i] = v.m(i);
            }
        }
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::or_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_and(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::and_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_or(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::or_(x.d, y.d)};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_xor(const simd_mask<T> &x, const simd_mask<T> &y)
    {
        return {private_init, detail::xor_(x.d, y.d)};
    }
    template <class T> static bool get(const simd_mask<T> &k, int i) noexcept
    {
        return k.d.m(i);
    }
    template <class T> static void set(simd_mask<T> &k, int i, bool x) noexcept
    {
        k.d.set(i, mask_bool<T>(x));
    }
};
}
Vc_VERSIONED_NAMESPACE_END
Vc_VERSIONED_NAMESPACE_BEGIN
Vc_VERSIONED_NAMESPACE_END
#endif
#endif
#endif
#ifndef VC_DETAIL_MATH_H_
#define VC_DETAIL_MATH_H_ 
#include <utility>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail
{
template <class Abi> using scharv = simd<signed char, Abi>;
template <class Abi> using shortv = simd<short, Abi>;
template <class Abi> using intv = simd<int, Abi>;
template <class Abi> using longv = simd<long int, Abi>;
template <class Abi> using llongv = simd<long long int, Abi>;
template <class Abi> using floatv = simd<float, Abi>;
template <class Abi> using doublev = simd<double, Abi>;
template <class Abi> using ldoublev = simd<long double, Abi>;
template <class T, class V>
using samesize = fixed_size_simd<T, V::size()>;
#define Vc_MATH_CALL_(name_) \
    template <class Abi> Vc::detail::floatv<Abi> name_(Vc::detail::floatv<Abi> x) \
    { \
        return Vc::detail::impl_or_fallback( \
            [](const auto &xx) -> decltype(Vc::detail::floatv<Abi>( \
                Vc::detail::private_init, \
                Vc::detail::get_impl_t<decltype(xx)>::name_(Vc::detail::data(xx)))) { \
                return { \
                    Vc::detail::private_init, \
                    Vc::detail::get_impl_t<decltype(xx)>::name_(Vc::detail::data(xx))}; \
            }, \
            [](const Vc::detail::floatv<Abi> &xx) { \
                return Vc::detail::floatv<Abi>( \
                    [&](auto i) { return std::name_(xx[i]); }); \
            }, \
            x); \
    } \
    template <class Abi> Vc::detail::doublev<Abi> name_(Vc::detail::doublev<Abi> x) \
    { \
        return Vc::detail::impl_or_fallback( \
            [](const auto &xx) -> decltype(Vc::detail::doublev<Abi>( \
                Vc::detail::private_init, \
                Vc::detail::get_impl_t<decltype(xx)>::name_(Vc::detail::data(xx)))) { \
                return { \
                    Vc::detail::private_init, \
                    Vc::detail::get_impl_t<decltype(xx)>::name_(Vc::detail::data(xx))}; \
            }, \
            [](const Vc::detail::doublev<Abi> &xx) { \
                return Vc::detail::doublev<Abi>( \
                    [&](auto i) { return std::name_(xx[i]); }); \
            }, \
            x); \
    } \
    template <class Abi> Vc::detail::ldoublev<Abi> name_(Vc::detail::ldoublev<Abi> x) \
    { \
        return Vc::detail::impl_or_fallback( \
            [](const auto &xx) -> decltype(Vc::detail::ldoublev<Abi>( \
                Vc::detail::private_init, \
                Vc::detail::get_impl_t<decltype(xx)>::name_(Vc::detail::data(xx)))) { \
                return { \
                    Vc::detail::private_init, \
                    Vc::detail::get_impl_t<decltype(xx)>::name_(Vc::detail::data(xx))}; \
            }, \
            [](const Vc::detail::ldoublev<Abi> &xx) { \
                return Vc::detail::ldoublev<Abi>( \
                    [&](auto i) { return std::name_(xx[i]); }); \
            }, \
            x); \
    }
#define Vc_ARG_SAMESIZE_INT(arg1_) Vc::detail::samesize<int, arg1_>
#define Vc_ARG_SAMESIZE_LONG(arg1_) Vc::detail::samesize<long, arg1_>
#define Vc_ARG_AS_ARG1(arg1_) arg1_
#define Vc_MATH_CALL2_(name_,arg2_) \
    template <class Abi> \
    detail::floatv<Abi> name_(Vc::detail::floatv<Abi> x_, \
                              arg2_(Vc::detail::floatv<Abi>) y_) \
    { \
        return Vc::detail::impl_or_fallback( \
            [](const auto &x, const auto &y) -> decltype(Vc::detail::floatv<Abi>( \
                Vc::detail::private_init, \
                Vc::detail::get_impl_t<decltype(x)>::name_(Vc::detail::data(x), \
                                                           Vc::detail::data(y)))) { \
                return {Vc::detail::private_init, \
                        Vc::detail::get_impl_t<decltype(x)>::name_( \
                            Vc::detail::data(x), Vc::detail::data(y))}; \
            }, \
            [](const Vc::detail::floatv<Abi> &x, const auto &y) { \
                return Vc::detail::floatv<Abi>( \
                    [&](auto i) { return std::name_(x[i], y[i]); }); \
            }, \
            x_, y_); \
    } \
    template <class Abi> \
    detail::doublev<Abi> name_(Vc::detail::doublev<Abi> x_, \
                               arg2_(Vc::detail::doublev<Abi>) y_) \
    { \
        return Vc::detail::impl_or_fallback( \
            [](const auto &x, const auto &y) -> decltype(Vc::detail::doublev<Abi>( \
                Vc::detail::private_init, \
                Vc::detail::get_impl_t<decltype(x)>::name_(Vc::detail::data(x), \
                                                           Vc::detail::data(y)))) { \
                return {Vc::detail::private_init, \
                        Vc::detail::get_impl_t<decltype(x)>::name_( \
                            Vc::detail::data(x), Vc::detail::data(y))}; \
            }, \
            [](const Vc::detail::doublev<Abi> &x, const auto &y) { \
                return Vc::detail::doublev<Abi>( \
                    [&](auto i) { return std::name_(x[i], y[i]); }); \
            }, \
            x_, y_); \
    } \
    template <class Abi> \
    detail::ldoublev<Abi> name_(Vc::detail::ldoublev<Abi> x_, \
                                arg2_(Vc::detail::ldoublev<Abi>) y_) \
    { \
        return Vc::detail::impl_or_fallback( \
            [](const auto &x, const auto &y) -> decltype(Vc::detail::ldoublev<Abi>( \
                Vc::detail::private_init, \
                Vc::detail::get_impl_t<decltype(x)>::name_(Vc::detail::data(x), \
                                                           Vc::detail::data(y)))) { \
                return {Vc::detail::private_init, \
                        Vc::detail::get_impl_t<decltype(x)>::name_( \
                            Vc::detail::data(x), Vc::detail::data(y))}; \
            }, \
            [](const Vc::detail::ldoublev<Abi> &x, const auto &y) { \
                return Vc::detail::ldoublev<Abi>( \
                    [&](auto i) { return std::name_(x[i], y[i]); }); \
            }, \
            x_, y_); \
    }
template < typename Abi>
static Vc_ALWAYS_INLINE floatv<Abi> cosSeries(const floatv<Abi> &x)
{
    using C = detail::trig<Abi, float>;
    const floatv<Abi> x2 = x * x;
    return ((C::cos_c2() * x2 +
             C::cos_c1()) * x2 +
             C::cos_c0()) * (x2 * x2)
        - .5f * x2 + 1.f;
}
template <typename Abi>
static Vc_ALWAYS_INLINE doublev<Abi> cosSeries(const doublev<Abi> &x)
{
    using C = detail::trig<Abi, double>;
    const doublev<Abi> x2 = x * x;
    return (((((C::cos_c5() * x2 +
                C::cos_c4()) * x2 +
                C::cos_c3()) * x2 +
                C::cos_c2()) * x2 +
                C::cos_c1()) * x2 +
                C::cos_c0()) * (x2 * x2)
        - .5 * x2 + 1.;
}
template <typename Abi>
static Vc_ALWAYS_INLINE floatv<Abi> sinSeries(const floatv<Abi>& x)
{
    using C = detail::trig<Abi, float>;
    const floatv<Abi> x2 = x * x;
    return ((C::sin_c2() * x2 +
             C::sin_c1()) * x2 +
             C::sin_c0()) * (x2 * x)
        + x;
}
template <typename Abi>
static Vc_ALWAYS_INLINE doublev<Abi> sinSeries(const doublev<Abi> &x)
{
    using C = detail::trig<Abi, double>;
    const doublev<Abi> x2 = x * x;
    return (((((C::sin_c5() * x2 +
                C::sin_c4()) * x2 +
                C::sin_c3()) * x2 +
                C::sin_c2()) * x2 +
                C::sin_c1()) * x2 +
                C::sin_c0()) * (x2 * x)
        + x;
}
template <class Abi>
Vc_ALWAYS_INLINE std::pair<floatv<Abi>, rebind_simd_t<int, floatv<Abi>>> foldInput(
    floatv<Abi> x)
{
    using V = floatv<Abi>;
    using C = detail::trig<Abi, float>;
    using IV = rebind_simd_t<int, V>;
    x = abs(x);
#if defined(Vc_HAVE_FMA4) || defined(Vc_HAVE_FMA)
    rebind_simd_t<int, V> quadrant =
        static_simd_cast<IV>(x * C::_4_pi() + 1.f);
    quadrant &= ~1;
#else
    rebind_simd_t<int, V> quadrant = static_simd_cast<IV>(x * C::_4_pi());
    quadrant += quadrant & 1;
#endif
    const V y = static_simd_cast<V>(quadrant);
    quadrant &= 7;
    return {((x - y * C::pi_4_hi()) - y * C::pi_4_rem1()) - y * C::pi_4_rem2(), quadrant};
}
template <typename Abi>
static Vc_ALWAYS_INLINE std::pair<doublev<Abi>, rebind_simd_t<int, doublev<Abi>>>
foldInput(doublev<Abi> x)
{
    using V = doublev<Abi>;
    using C = detail::trig<Abi, double>;
    using IV = rebind_simd_t<int, V>;
    x = abs(x);
    V y = trunc(x / C::pi_4());
    V z = y - trunc(y * C::_1_16()) * C::_16();
    IV quadrant = static_simd_cast<IV>(z);
    const auto mask = (quadrant & 1) != 0;
    ++where(mask, quadrant);
    where(static_simd_cast<typename V::mask_type>(mask), y) += V(1);
    quadrant &= 7;
    return {((x - y * C::pi_4_hi()) - y * C::pi_4_rem1()) - y * C::pi_4_rem2(), quadrant};
}
template <class Abi>
samesize<int, doublev<Abi>> extract_exponent_bits(const doublev<Abi> &v)
{
    const doublev<Abi> exponent_mask =
        std::numeric_limits<double>::infinity();
    constexpr auto N = simd_size_v<double, Abi> * 2;
    constexpr auto Max = simd_abi::max_fixed_size<int>;
    Vc_CONSTEXPR_IF_RETURNING (N > Max)
    {
        using namespace Vc::experimental;
        using namespace Vc::experimental::float_bitwise_operators;
        const auto tup = split<Max / 2, (N - Max) / 2>(v & exponent_mask);
        return concat(
            shuffle<strided<2, 1>>(
                simd_reinterpret_cast<fixed_size_simd<int, Max>>(std::get<0>(tup))),
            shuffle<strided<2, 1>>(
                simd_reinterpret_cast<fixed_size_simd<int, N - Max>>(std::get<1>(tup))));
    }
    Vc_CONSTEXPR_ELSE
    {
        using namespace Vc::experimental;
        using namespace Vc::experimental::float_bitwise_operators;
        return shuffle<strided<2, 1>>(
            simd_reinterpret_cast<fixed_size_simd<int, 2 * simd_size_v<double, Abi>>>(
                v & exponent_mask));
    }
    Vc_CONSTEXPR_ENDIF
}
template <class ImplFun, class FallbackFun, class... Args>
Vc_INTRINSIC auto impl_or_fallback_dispatch(int, ImplFun &&impl_fun, FallbackFun &&,
                                            Args &&... args)
    -> decltype(impl_fun(std::forward<Args>(args)...))
{
    return impl_fun(std::forward<Args>(args)...);
}
template <class ImplFun, class FallbackFun, class... Args>
inline auto impl_or_fallback_dispatch(float, ImplFun &&, FallbackFun &&fallback_fun,
                                      Args &&... args)
    -> decltype(fallback_fun(std::forward<Args>(args)...))
{
    return fallback_fun(std::forward<Args>(args)...);
}
template <class... Args> Vc_INTRINSIC auto impl_or_fallback(Args &&... args)
{
    return impl_or_fallback_dispatch(int(), std::forward<Args>(args)...);
}
}
Vc_MATH_CALL_(acos)
Vc_MATH_CALL_(asin)
Vc_MATH_CALL_(atan)
Vc_MATH_CALL2_(atan2, Vc_ARG_AS_ARG1)
template <class T, class Abi, class = std::enable_if_t<std::is_floating_point<T>::value>>
simd<T, Abi> cos(simd<T, Abi> x)
{
    using V = simd<T, Abi>;
    using M = typename V::mask_type;
    auto folded = foldInput(x);
    const V &z = folded.first;
    auto &quadrant = folded.second;
    M sign = static_simd_cast<M>(quadrant > 3);
    where(quadrant > 3, quadrant) -= 4;
    sign ^= static_simd_cast<M>(quadrant > 1);
    V y = cosSeries(z);
    where(static_simd_cast<M>(quadrant == 1 || quadrant == 2), y) = sinSeries(z);
    where(sign, y) = -y;
    Vc_DEBUG(cosine)
        (Vc_PRETTY_PRINT(x))
        (Vc_PRETTY_PRINT(sign))
        (Vc_PRETTY_PRINT(z))
        (Vc_PRETTY_PRINT(folded.second))
        (Vc_PRETTY_PRINT(quadrant))
        (Vc_PRETTY_PRINT(y));
    return y;
}
template <class T, class Abi, class = std::enable_if_t<std::is_floating_point<T>::value>>
simd<T, Abi> sin(simd<T, Abi> x)
{
    using V = simd<T, Abi>;
    using M = typename V::mask_type;
    auto folded = foldInput(x);
    const V &z = folded.first;
    auto &quadrant = folded.second;
    const M sign = (x < 0) ^ static_simd_cast<M>(quadrant > 3);
    where(quadrant > 3, quadrant) -= 4;
    V y = sinSeries(z);
    where(static_simd_cast<M>(quadrant == 1 || quadrant == 2), y) = cosSeries(z);
    where(sign, y) = -y;
    Vc_DEBUG(sine)
        (Vc_PRETTY_PRINT(x))
        (Vc_PRETTY_PRINT(sign))
        (Vc_PRETTY_PRINT(z))
        (Vc_PRETTY_PRINT(folded.second))
        (Vc_PRETTY_PRINT(quadrant))
        (Vc_PRETTY_PRINT(y));
    return y;
}
template <>
Vc_ALWAYS_INLINE detail::floatv<simd_abi::scalar> sin(detail::floatv<simd_abi::scalar> x)
{
    return std::sin(detail::data(x));
}
template <>
Vc_ALWAYS_INLINE detail::doublev<simd_abi::scalar> sin(
    detail::doublev<simd_abi::scalar> x)
{
    return std::sin(detail::data(x));
}
template <>
Vc_ALWAYS_INLINE detail::ldoublev<simd_abi::scalar> sin(
    detail::ldoublev<simd_abi::scalar> x)
{
    return std::sin(detail::data(x));
}
Vc_MATH_CALL_(tan)
Vc_MATH_CALL_(acosh)
Vc_MATH_CALL_(asinh)
Vc_MATH_CALL_(atanh)
Vc_MATH_CALL_(cosh)
Vc_MATH_CALL_(sinh)
Vc_MATH_CALL_(tanh)
Vc_MATH_CALL_(exp)
Vc_MATH_CALL_(exp2)
Vc_MATH_CALL_(expm1)
template <class Abi>
detail::floatv<Abi> frexp(detail::floatv<Abi> value_,
                          detail::samesize<int, detail::floatv<Abi>> * exp_)
{
    return {detail::private_init,
            detail::impl_or_fallback(
                [](auto value, auto *exp) -> decltype(
                    detail::get_impl_t<decltype(value)>::frexp(detail::data(value),
                                                               detail::data(*exp))) {
                    return detail::get_impl_t<decltype(value)>::frexp(detail::data(value),
                                                                      detail::data(*exp));
                },
                [](auto value, auto *exp) {
                    using FV = detail::floatv<Abi>;
                    using IV = detail::samesize<int, FV>;
                    using IM = typename IV::mask_type;
                    using limits = std::numeric_limits<float>;
                    using namespace Vc::experimental;
                    using namespace Vc::experimental::float_bitwise_operators;
                    const FV exponent_mask = limits::infinity();
                    const FV p5_1_exponent = detail::float_const<-1, 0x007fffffu, -1>;
                    FV mant = p5_1_exponent & (exponent_mask | value);
                    const IV exponent_bits =
                        simd_reinterpret_cast<IV>(value & exponent_mask);
                    if (Vc_IS_LIKELY(all_of(isnormal(value)))) {
                        *exp = (exponent_bits >> 23) - 0x7e;
                        return detail::data(mant);
                    }
                    const auto iszero_inf_nan =
                        isunordered(value * limits::infinity(), value * FV());
                    const FV scaled_subnormal = value * detail::float_const<1, 0, 0x70>;
                    const FV mant_subnormal =
                        p5_1_exponent & (exponent_mask | scaled_subnormal);
                    where(!isnormal(value), mant) = mant_subnormal;
                    where(iszero_inf_nan, mant) = value;
                    IV e = simd_reinterpret_cast<IV>(scaled_subnormal & exponent_mask);
                    const IM value_isnormal = static_simd_cast<IM>(isnormal(value));
                    where(value_isnormal, e) = exponent_bits;
                    const IV offset =
                        (simd_reinterpret_cast<IV>(value_isnormal) & IV(0x7e)) |
                        (simd_reinterpret_cast<IV>((exponent_bits == 0) &
                                                   (static_simd_cast<IM>(value != 0))) &
                         IV(0xee));
                    *exp = (e >> 23) - offset;
                    return detail::data(mant);
                },
                value_, exp_)};
}
template <class Abi>
detail::doublev<Abi> frexp(detail::doublev<Abi> value_,
                           detail::samesize<int, detail::doublev<Abi>> * exp_)
{
    *exp_ = 0xdead;
    return {detail::private_init,
            detail::impl_or_fallback(
                [](auto value, auto *exp) -> decltype(
                    detail::get_impl_t<decltype(value)>::frexp(detail::data(value),
                                                               detail::data(*exp))) {
                    return detail::get_impl_t<decltype(value)>::frexp(detail::data(value),
                                                                      detail::data(*exp));
                },
                [](auto value, auto *exp) {
                    using DV = detail::doublev<Abi>;
                    using IV = detail::samesize<int, DV>;
                    using IM = typename IV::mask_type;
                    using limits = std::numeric_limits<double>;
                    using namespace Vc::experimental;
                    using namespace Vc::experimental::float_bitwise_operators;
                    const DV exponent_mask = limits::infinity();
                    const DV p5_1_exponent =
                        detail::double_const<-1, 0x000fffffffffffffull, -1>;
                    DV mant = p5_1_exponent & (exponent_mask | value);
                    const IV exponent_bits = extract_exponent_bits(value);
                    if (Vc_IS_LIKELY(all_of(isnormal(value)))) {
                        *exp = (exponent_bits >> 20) - 0x3fe;
                        return detail::data(mant);
                    }
                    const auto iszero_inf_nan =
                        isunordered(value * limits::infinity(), value * DV());
                    const DV scaled_subnormal = value * detail::double_const<1, 0, 0x200>;
                    const DV mant_subnormal =
                        p5_1_exponent & (exponent_mask | scaled_subnormal);
                    where(!isnormal(value), mant) = mant_subnormal;
                    where(iszero_inf_nan, mant) = value;
                    IV e = extract_exponent_bits(scaled_subnormal);
                    const IM value_isnormal = static_simd_cast<IM>(isnormal(value));
                    where(value_isnormal, e) = exponent_bits;
                    const IV offset =
                        (simd_reinterpret_cast<IV>(value_isnormal) & IV(0x3fe)) |
                        (simd_reinterpret_cast<IV>((exponent_bits == 0) &
                                                   (static_simd_cast<IM>(value != 0))) &
                         IV(0x5fe));
                    *exp = (e >> 20) - offset;
                    return detail::data(mant);
                },
                value_, exp_)};
}
template <class Abi>
detail::ldoublev<Abi> frexp(detail::ldoublev<Abi> value,
                            detail::samesize<int, detail::ldoublev<Abi>> * exp)
{
    return {detail::private_init, detail::get_impl_t<decltype(value)>::frexp(
                                      detail::data(value), detail::data(*exp))};
}
template <class Abi>
detail::samesize<int, detail::floatv<Abi>> ilogb(detail::floatv<Abi> x);
template <class Abi>
detail::samesize<int, detail::doublev<Abi>> ilogb(detail::doublev<Abi> x);
template <class Abi>
detail::samesize<int, detail::ldoublev<Abi>> ilogb(detail::ldoublev<Abi> x);
Vc_MATH_CALL2_(ldexp, Vc_ARG_SAMESIZE_INT)
Vc_MATH_CALL_(log)
Vc_MATH_CALL_(log10)
Vc_MATH_CALL_(log1p)
Vc_MATH_CALL_(log2)
static_assert(true, "");
template <class T, class Abi, class = std::enable_if_t<std::is_floating_point<T>::value>>
simd<T, Abi> logb(const simd<T, Abi> &x_)
{
    using V = simd<T, Abi>;
    return Vc::detail::impl_or_fallback(
        [](const auto &x) -> decltype(
            V(Vc::detail::private_init,
              Vc::detail::get_impl_t<decltype(x)>::logb(Vc::detail::data(x)))) {
            return {Vc::detail::private_init,
                    Vc::detail::get_impl_t<decltype(x)>::logb(Vc::detail::data(x))};
        },
        [](const V &x) -> V {
            using namespace Vc::experimental;
            using namespace Vc::detail;
            auto is_normal = isnormal(x);
            const V abs_x = abs(x);
            auto &&exponent = [](const V &v) {
                using namespace Vc::experimental;
                using IV = rebind_simd_t<
                    std::conditional_t<sizeof(T) == sizeof(llong), llong, int>, V>;
                return (simd_reinterpret_cast<IV>(v) >>
                        (std::numeric_limits<T>::digits - 1)) -
                       (std::numeric_limits<T>::max_exponent - 1);
            };
            V r = static_simd_cast<V>(exponent(abs_x));
            if (Vc_IS_LIKELY(all_of(is_normal))) {
                return r;
            }
            const auto is_zero = x == 0;
            const auto is_nan = isnan(x);
            const auto is_inf = isinf(x);
            where(is_zero, r) = -std::numeric_limits<T>::infinity();
            where(is_nan, r) = x;
            where(is_inf, r) = std::numeric_limits<T>::infinity();
            is_normal |= is_zero || is_nan || is_inf;
            if (all_of(is_normal)) {
                return r;
            }
            const V scaled = abs_x * T(std::is_same<T, float>::value
                                           ? detail::float_const<1, 0, 0x70>
                                           : detail::double_const<1, 0, 0x70>);
            V scaled_exp = static_simd_cast<V>(exponent(scaled) - 0x70);
            Vc_DEBUG(logarithm)(x, scaled)(is_normal)(r, scaled_exp);
            where(is_normal, scaled_exp) = r;
            return scaled_exp;
        },
        x_);
}
template <class Abi>
detail::floatv<Abi> modf(detail::floatv<Abi> value, detail::floatv<Abi> * iptr);
template <class Abi>
detail::doublev<Abi> modf(detail::doublev<Abi> value, detail::doublev<Abi> * iptr);
template <class Abi>
detail::ldoublev<Abi> modf(detail::ldoublev<Abi> value, detail::ldoublev<Abi> * iptr);
Vc_MATH_CALL2_(scalbn, Vc_ARG_SAMESIZE_INT)
Vc_MATH_CALL2_(scalbln, Vc_ARG_SAMESIZE_LONG)
Vc_MATH_CALL_(cbrt)
template <class Abi> detail::scharv<Abi> abs(detail::scharv<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::shortv<Abi> abs(detail::shortv<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::intv<Abi> abs(detail::intv<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::longv<Abi> abs(detail::longv<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::llongv<Abi> abs(detail::llongv<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::floatv<Abi> abs(detail::floatv<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::doublev<Abi> abs(detail::doublev<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
template <class Abi> detail::ldoublev<Abi> abs(detail::ldoublev<Abi> j)
{
    return {detail::private_init, detail::get_impl_t<decltype(j)>::abs(detail::data(j))};
}
Vc_MATH_CALL2_(hypot, Vc_ARG_AS_ARG1)
template <class Abi>
detail::floatv<Abi> hypot(detail::floatv<Abi> x, detail::floatv<Abi> y,
                          detail::floatv<Abi> z);
template <class Abi>
detail::doublev<Abi> hypot(detail::doublev<Abi> x, detail::doublev<Abi> y,
                           detail::doublev<Abi> z);
template <class Abi>
detail::ldoublev<Abi> hypot(detail::ldoublev<Abi> x, detail::ldoublev<Abi> y,
                            detail::ldoublev<Abi> z);
Vc_MATH_CALL2_(pow, Vc_ARG_AS_ARG1)
Vc_MATH_CALL_(sqrt)
Vc_MATH_CALL_(erf)
Vc_MATH_CALL_(erfc)
Vc_MATH_CALL_(lgamma)
Vc_MATH_CALL_(tgamma)
Vc_MATH_CALL_(ceil)
Vc_MATH_CALL_(floor)
Vc_MATH_CALL_(nearbyint)
Vc_MATH_CALL_(rint)
template <class Abi>
detail::samesize<long int, detail::floatv<Abi>> lrint(detail::floatv<Abi> x);
template <class Abi>
detail::samesize<long int, detail::doublev<Abi>> lrint(detail::doublev<Abi> x);
template <class Abi>
detail::samesize<long int, detail::ldoublev<Abi>> lrint(detail::ldoublev<Abi> x);
template <class Abi>
detail::samesize<long long int, detail::floatv<Abi>> llrint(detail::floatv<Abi> x);
template <class Abi>
detail::samesize<long long int, detail::doublev<Abi>> llrint(detail::doublev<Abi> x);
template <class Abi>
detail::samesize<long long int, detail::ldoublev<Abi>> llrint(detail::ldoublev<Abi> x);
Vc_MATH_CALL_(round)
template <class Abi>
detail::samesize<long int, detail::floatv<Abi>> lround(detail::floatv<Abi> x);
template <class Abi>
detail::samesize<long int, detail::doublev<Abi>> lround(detail::doublev<Abi> x);
template <class Abi>
detail::samesize<long int, detail::ldoublev<Abi>> lround(detail::ldoublev<Abi> x);
template <class Abi>
detail::samesize<long long int, detail::floatv<Abi>> llround(detail::floatv<Abi> x);
template <class Abi>
detail::samesize<long long int, detail::doublev<Abi>> llround(detail::doublev<Abi> x);
template <class Abi>
detail::samesize<long long int, detail::ldoublev<Abi>> llround(detail::ldoublev<Abi> x);
Vc_MATH_CALL_(trunc)
Vc_MATH_CALL2_(fmod, Vc_ARG_AS_ARG1)
Vc_MATH_CALL2_(remainder, Vc_ARG_AS_ARG1)
template <class Abi>
detail::floatv<Abi> remquo(detail::floatv<Abi> x, detail::floatv<Abi> y,
                           detail::samesize<int, detail::floatv<Abi>> * quo);
template <class Abi>
detail::doublev<Abi> remquo(detail::doublev<Abi> x, detail::doublev<Abi> y,
                            detail::samesize<int, detail::doublev<Abi>> * quo);
template <class Abi>
detail::ldoublev<Abi> remquo(detail::ldoublev<Abi> x, detail::ldoublev<Abi> y,
                             detail::samesize<int, detail::ldoublev<Abi>> * quo);
Vc_MATH_CALL2_(copysign, Vc_ARG_AS_ARG1)
template <class Abi> detail::doublev<Abi> nan(const char* tagp);
template <class Abi> detail::floatv<Abi> nanf(const char* tagp);
template <class Abi> detail::ldoublev<Abi> nanl(const char* tagp);
Vc_MATH_CALL2_(nextafter, Vc_ARG_AS_ARG1)
Vc_MATH_CALL2_(nexttoward, Vc_ARG_AS_ARG1)
Vc_MATH_CALL2_(fdim, Vc_ARG_AS_ARG1)
Vc_MATH_CALL2_(fmax, Vc_ARG_AS_ARG1)
Vc_MATH_CALL2_(fmin, Vc_ARG_AS_ARG1)
template <class Abi>
detail::floatv<Abi> fma(detail::floatv<Abi> x, detail::floatv<Abi> y,
                        detail::floatv<Abi> z);
template <class Abi>
detail::doublev<Abi> fma(detail::doublev<Abi> x, detail::doublev<Abi> y,
                         detail::doublev<Abi> z);
template <class Abi>
detail::ldoublev<Abi> fma(detail::ldoublev<Abi> x, detail::ldoublev<Abi> y,
                          detail::ldoublev<Abi> z);
template <class Abi>
detail::samesize<int, detail::floatv<Abi>> fpclassify(detail::floatv<Abi> x)
{
    return {detail::private_init,
            detail::get_impl_t<decltype(x)>::fpclassify(detail::data(x))};
}
template <class Abi>
detail::samesize<int, detail::doublev<Abi>> fpclassify(detail::doublev<Abi> x)
{
    return {detail::private_init,
            detail::get_impl_t<decltype(x)>::fpclassify(detail::data(x))};
}
template <class Abi>
detail::samesize<int, detail::ldoublev<Abi>> fpclassify(detail::ldoublev<Abi> x)
{
    return {detail::private_init,
            detail::get_impl_t<decltype(x)>::fpclassify(detail::data(x))};
}
#define Vc_MATH_CLASS_(name_) \
    template <class Abi> simd_mask<float, Abi> name_(detail::floatv<Abi> x) \
    { \
        return {detail::private_init, \
                detail::get_impl_t<decltype(x)>::name_(detail::data(x))}; \
    } \
    template <class Abi> simd_mask<double, Abi> name_(detail::doublev<Abi> x) \
    { \
        return {detail::private_init, \
                detail::get_impl_t<decltype(x)>::name_(detail::data(x))}; \
    } \
    template <class Abi> simd_mask<long double, Abi> name_(detail::ldoublev<Abi> x) \
    { \
        return {detail::private_init, \
                detail::get_impl_t<decltype(x)>::name_(detail::data(x))}; \
    }
Vc_MATH_CLASS_(isfinite)
Vc_MATH_CLASS_(isinf)
Vc_MATH_CLASS_(isnan)
Vc_MATH_CLASS_(isnormal)
Vc_MATH_CLASS_(signbit)
#undef Vc_MATH_CLASS_
#define Vc_MATH_CMP_(name_) \
    template <class Abi> \
    simd_mask<float, Abi> name_(detail::floatv<Abi> x, detail::floatv<Abi> y) \
    { \
        return {detail::private_init, detail::get_impl_t<decltype(x)>::name_( \
                                          detail::data(x), detail::data(y))}; \
    } \
    template <class Abi> \
    simd_mask<double, Abi> name_(detail::doublev<Abi> x, detail::doublev<Abi> y) \
    { \
        return {detail::private_init, detail::get_impl_t<decltype(x)>::name_( \
                                          detail::data(x), detail::data(y))}; \
    } \
    template <class Abi> \
    simd_mask<long double, Abi> name_(detail::ldoublev<Abi> x, detail::ldoublev<Abi> y) \
    { \
        return {detail::private_init, detail::get_impl_t<decltype(x)>::name_( \
                                          detail::data(x), detail::data(y))}; \
    }
Vc_MATH_CMP_(isgreater)
Vc_MATH_CMP_(isgreaterequal)
Vc_MATH_CMP_(isless)
Vc_MATH_CMP_(islessequal)
Vc_MATH_CMP_(islessgreater)
Vc_MATH_CMP_(isunordered)
#undef Vc_MATH_CMP_
template <class V> struct simd_div_t {
    V quot, rem;
};
template <class Abi>
simd_div_t<detail::scharv<Abi>> div(detail::scharv<Abi> numer,
                                         detail::scharv<Abi> denom);
template <class Abi>
simd_div_t<detail::shortv<Abi>> div(detail::shortv<Abi> numer,
                                         detail::shortv<Abi> denom);
template <class Abi>
simd_div_t<detail::intv<Abi>> div(detail::intv<Abi> numer, detail::intv<Abi> denom);
template <class Abi>
simd_div_t<detail::longv<Abi>> div(detail::longv<Abi> numer,
                                        detail::longv<Abi> denom);
template <class Abi>
simd_div_t<detail::llongv<Abi>> div(detail::llongv<Abi> numer,
                                         detail::llongv<Abi> denom);
#undef Vc_MATH_CALL_
namespace detail
{
template <class T, bool = std::is_arithmetic<std::decay_t<T>>::value>
struct autocvt_to_simd {
    T d;
    using TT = std::decay_t<T>;
    operator TT() { return d; }
    operator TT &()
    {
        static_assert(std::is_lvalue_reference<T>::value, "");
        static_assert(!std::is_const<T>::value, "");
        return d;
    }
    operator TT *()
    {
        static_assert(std::is_lvalue_reference<T>::value, "");
        static_assert(!std::is_const<T>::value, "");
        return &d;
    }
    template <class Abi> operator simd<typename TT::value_type, Abi>()
    {
        return {detail::private_init, d};
    }
    template <class Abi> operator simd<typename TT::value_type, Abi> *()
    {
        return reinterpret_cast<simd<typename TT::value_type, Abi> *>(&d);
    }
};
template <class T> struct autocvt_to_simd<T, true> {
    using TT = std::decay_t<T>;
    T d;
    fixed_size_simd<TT, 1> fd;
    autocvt_to_simd(T dd) : d(dd), fd(d) {}
    ~autocvt_to_simd()
    {
        d = detail::data(fd).first;
    }
    operator fixed_size_simd<TT, 1>()
    {
        return fd;
    }
    operator fixed_size_simd<TT, 1> *()
    {
        static_assert(std::is_lvalue_reference<T>::value, "");
        static_assert(!std::is_const<T>::value, "");
        return &fd;
    }
};
#define Vc_FIXED_SIZE_FWD_(name_) \
    struct name_##_fwd { \
        template <class Impl, class Arg0, class... Args> \
        Vc_INTRINSIC_L auto operator()(Impl impl, Arg0 &&arg0, \
                                       Args &&... args) noexcept Vc_INTRINSIC_R; \
    }; \
    template <class Impl, class Arg0, class... Args> \
    Vc_INTRINSIC auto name_##_fwd::operator()(Impl, Arg0 &&arg0, \
                                              Args &&... args) noexcept \
    { \
        auto ret = detail::data(Vc::name_<typename Impl::abi_type>( \
            typename Impl::simd_type{detail::private_init, std::forward<Arg0>(arg0)}, \
            autocvt_to_simd<Args>{std::forward<Args>(args)}...)); \
                                                                                         \
        return ret; \
    }
Vc_FIXED_SIZE_FWD_(frexp)
Vc_FIXED_SIZE_FWD_(sin)
Vc_FIXED_SIZE_FWD_(cos)
#undef Vc_FIXED_SIZE_FWD_
}
Vc_VERSIONED_NAMESPACE_END
#endif
#ifndef VC_SIMD_FIXED_SIZE_H_
#define VC_SIMD_FIXED_SIZE_H_ 
#include <array>
#include <climits>
Vc_VERSIONED_NAMESPACE_BEGIN
namespace detail {
struct dummy : public size_constant<~size_t()> {
};
template <class T, int N, class A, class... More>
struct select_best_vector_type {
    using V = std::conditional_t<std::is_destructible<simd<T, A>>::value,
                                 simd_size<T, A>, dummy>;
    using type =
        std::conditional_t<(N >= V::value), simd<T, A>,
                           typename select_best_vector_type<T, N, More...>::type>;
};
template <class T, int N, class A> struct select_best_vector_type<T, N, A> {
    using type = simd<T, A>;
};
template <class T, int N>
using select_best_vector_type_t = typename select_best_vector_type<T, N,
      simd_abi::Avx512,
      simd_abi::Avx,
      simd_abi::Neon,
      simd_abi::Sse,
      simd_abi::scalar
      >::type;
template <class T, int N, class Tuple, class Next = select_best_vector_type_t<T, N>,
          int Remain = N - int(Next::size())>
struct fixed_size_storage_builder;
template <class T, int N>
struct fixed_size_storage_builder_wrapper
    : public fixed_size_storage_builder<T, N, simd_tuple<T>> {
};
template <class T, int N, class... As, class Next>
struct fixed_size_storage_builder<T, N, simd_tuple<T, As...>, Next, 0> {
    using type = simd_tuple<T, As..., typename Next::abi_type>;
};
template <class T, int N, class... As, class Next, int Remain>
struct fixed_size_storage_builder<T, N, simd_tuple<T, As...>, Next, Remain> {
    using type = typename fixed_size_storage_builder<
        T, Remain, simd_tuple<T, As..., typename Next::abi_type>>::type;
};
namespace tests {
using simd_abi::scalar;
using simd_abi::Sse;
using simd_abi::Avx;
using simd_abi::Avx512;
static_assert(
    std::is_same<fixed_size_storage<float, 1>, simd_tuple<float, scalar>>::value,
    "fixed_size_storage failure");
static_assert(std::is_same<fixed_size_storage<float, 2>,
                           simd_tuple<float, scalar, scalar>>::value,
              "fixed_size_storage failure");
static_assert(std::is_same<fixed_size_storage<float, 3>,
                           simd_tuple<float, scalar, scalar, scalar>>::value,
              "fixed_size_storage failure");
#ifdef Vc_HAVE_SSE_ABI
static_assert(
    std::is_same<fixed_size_storage<float, 4>, simd_tuple<float, Sse>>::value,
    "fixed_size_storage failure");
static_assert(
    std::is_same<fixed_size_storage<float, 5>, simd_tuple<float, Sse, scalar>>::value,
    "fixed_size_storage failure");
#endif
#ifdef Vc_HAVE_AVX_ABI
static_assert(
    std::is_same<fixed_size_storage<float, 8>, simd_tuple<float, Avx>>::value,
    "fixed_size_storage failure");
static_assert(
    std::is_same<fixed_size_storage<float, 12>, simd_tuple<float, Avx, Sse>>::value,
    "fixed_size_storage failure");
static_assert(std::is_same<fixed_size_storage<float, 13>,
                           simd_tuple<float, Avx, Sse, scalar>>::value,
              "fixed_size_storage failure");
#endif
}
template <class T> struct seq_op;
template <size_t I0, size_t... Is> struct seq_op<std::index_sequence<I0, Is...>> {
    using first_plus_one = std::index_sequence<I0 + 1, Is...>;
    using notfirst_plus_one = std::index_sequence<I0, (Is + 1)...>;
    template <size_t First, size_t Add>
    using prepend = std::index_sequence<First, I0 + Add, (Is + Add)...>;
};
template <class T> struct n_abis_in_tuple;
template <class T> struct n_abis_in_tuple<simd_tuple<T>> {
    using counts = std::index_sequence<0>;
    using begins = std::index_sequence<0>;
};
template <class T, class A> struct n_abis_in_tuple<simd_tuple<T, A>> {
    using counts = std::index_sequence<1>;
    using begins = std::index_sequence<0>;
};
template <class T, class A0, class... As>
struct n_abis_in_tuple<simd_tuple<T, A0, A0, As...>> {
    using counts = typename seq_op<
        typename n_abis_in_tuple<simd_tuple<T, A0, As...>>::counts>::first_plus_one;
    using begins = typename seq_op<typename n_abis_in_tuple<
        simd_tuple<T, A0, As...>>::begins>::notfirst_plus_one;
};
template <class T, class A0, class A1, class... As>
struct n_abis_in_tuple<simd_tuple<T, A0, A1, As...>> {
    using counts = typename seq_op<typename n_abis_in_tuple<
        simd_tuple<T, A1, As...>>::counts>::template prepend<1, 0>;
    using begins = typename seq_op<typename n_abis_in_tuple<
        simd_tuple<T, A1, As...>>::begins>::template prepend<0, 1>;
};
namespace tests
{
static_assert(
    std::is_same<n_abis_in_tuple<simd_tuple<int, simd_abi::Sse, simd_abi::Sse,
                                                simd_abi::scalar, simd_abi::scalar,
                                                simd_abi::scalar>>::counts,
                 std::index_sequence<2, 3>>::value,
    "");
static_assert(
    std::is_same<n_abis_in_tuple<simd_tuple<int, simd_abi::Sse, simd_abi::Sse,
                                                simd_abi::scalar, simd_abi::scalar,
                                                simd_abi::scalar>>::begins,
                 std::index_sequence<0, 2>>::value,
    "");
}
template <size_t Count, size_t Begin> struct tree_reduction {
    static_assert(Count > 0,
                  "tree_reduction requires at least one simd object to work with");
    template <class T, class... As, class BinaryOperation>
    auto operator()(const simd_tuple<T, As...> &tup,
                    const BinaryOperation &binary_op) const noexcept
    {
        constexpr size_t left = next_power_of_2(Count) / 2;
        constexpr size_t right = Count - left;
        return binary_op(tree_reduction<left, Begin>()(tup, binary_op),
                         tree_reduction<right, Begin + left>()(tup, binary_op));
    }
};
template <size_t Begin> struct tree_reduction<1, Begin> {
    template <class T, class... As, class BinaryOperation>
    auto operator()(const simd_tuple<T, As...> &tup, const BinaryOperation &) const
        noexcept
    {
        return detail::get_simd<Begin>(tup);
    }
};
template <size_t Begin> struct tree_reduction<2, Begin> {
    template <class T, class... As, class BinaryOperation>
    auto operator()(const simd_tuple<T, As...> &tup,
                    const BinaryOperation &binary_op) const noexcept
    {
        return binary_op(detail::get_simd<Begin>(tup),
                         detail::get_simd<Begin + 1>(tup));
    }
};
template <class T, class A0, class A1, class BinaryOperation>
Vc_INTRINSIC simd<T, A1> vec_to_scalar_reduction_first_pair(
    const simd<T, A0> left, const simd<T, A1> right, const BinaryOperation &binary_op,
    size_constant<2>) noexcept
{
    const std::array<simd<T, A1>, 2> splitted = split<simd<T, A1>>(left);
    return binary_op(binary_op(splitted[0], right), splitted[1]);
}
template <class T, class A0, class A1, class BinaryOperation>
Vc_INTRINSIC simd<T, A1> vec_to_scalar_reduction_first_pair(
    const simd<T, A0> left, const simd<T, A1> right, const BinaryOperation &binary_op,
    size_constant<4>) noexcept
{
    constexpr auto N0 = simd_size_v<T, A0> / 2;
    const auto left2 = split<simd<T, abi_for_size_t<T, N0>>>(left);
    const std::array<simd<T, A1>, 2> splitted =
        split<simd<T, A1>>(binary_op(left2[0], left2[1]));
    return binary_op(binary_op(splitted[0], right), splitted[1]);
}
template <class T, class A0, class A1, class BinaryOperation, size_t Factor>
Vc_INTRINSIC simd<T, simd_abi::scalar> vec_to_scalar_reduction_first_pair(
    const simd<T, A0> left, const simd<T, A1> right, const BinaryOperation &binary_op,
    size_constant<Factor>) noexcept
{
    return binary_op(Vc::reduce(left, binary_op), Vc::reduce(right, binary_op));
}
template <class T, class A0, class BinaryOperation>
Vc_INTRINSIC T vec_to_scalar_reduction(const simd_tuple<T, A0> &tup,
                                       const BinaryOperation &binary_op) noexcept
{
    return Vc::reduce(simd<T, A0>(detail::private_init, tup.first), binary_op);
}
template <class T, class A0, class A1, class... As, class BinaryOperation>
Vc_INTRINSIC T vec_to_scalar_reduction(const simd_tuple<T, A0, A1, As...> &tup,
                                       const BinaryOperation &binary_op) noexcept
{
    return vec_to_scalar_reduction(
        detail::tuple_concat(
            detail::make_tuple(
                vec_to_scalar_reduction_first_pair<T, A0, A1, BinaryOperation>(
                    {private_init, tup.first}, {private_init, tup.second.first},
                    binary_op, size_constant<simd_size_v<T, A0> / simd_size_v<T, A1>>())),
            tup.second.second),
        binary_op);
}
template <class V, size_t N>
Vc_INTRINSIC auto partial_bitset_to_member_type(std::bitset<N> shifted_bits)
{
    static_assert(V::size() <= N, "");
    using M = typename V::mask_type;
    using T = typename V::value_type;
    constexpr T *type_tag = nullptr;
    return detail::get_impl_t<M>::from_bitset(
        std::bitset<V::size()>(shifted_bits.to_ullong()), type_tag);
}
template <int N> struct fixed_size_simd_impl {
    using mask_member_type = std::bitset<N>;
    template <class T> using simd_member_type = fixed_size_storage<T, N>;
    template <class T>
    static constexpr std::size_t tuple_size = simd_member_type<T>::tuple_size;
    template <class T>
    static constexpr std::make_index_sequence<simd_member_type<T>::tuple_size> index_seq = {};
    template <class T> using simd = Vc::simd<T, simd_abi::fixed_size<N>>;
    template <class T> using simd_mask = Vc::simd_mask<T, simd_abi::fixed_size<N>>;
    using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    template <class T>
    static inline simd_member_type<T> broadcast(T x, size_tag) noexcept
    {
#ifdef Vc_ICC
        simd_member_type<T> r;
        execute_n_times<N>([&](auto i_) { r.set(i_, x); });
        return r;
#else
        return simd_member_type<T>::generate(
            [&](auto meta) { return meta.broadcast(x, size_constant<meta.size()>()); });
#endif
    }
    template <class F, class T>
    static Vc_INTRINSIC simd_member_type<T> generator(F &&gen, type_tag<T>, size_tag)
    {
#ifdef Vc_ICC
        simd_member_type<T> r;
        execute_n_times<N>([&](auto i_) { r.set(i_, gen(i_)); });
        return r;
#else
        return simd_member_type<T>::generate([&gen](auto meta) {
            return meta.generator(
                [&](auto i_) {
                    return gen(size_constant<meta.offset + decltype(i_)::value>());
                },
                type_tag<T>(), size_constant<meta.size()>());
        });
#endif
    }
    template <class T, class U, class F>
    static inline simd_member_type<T> load(const U *mem, F f,
                                              type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        return simd_member_type<T>::generate(
            [&](auto meta) { return meta.load(&mem[meta.offset], f, type_tag<T>()); });
    }
    template <class T, class... As, class U, class F>
    static inline void masked_load(simd_tuple<T, As...> &merge,
                                   const mask_member_type bits, const U *mem,
                                   F f) Vc_NOEXCEPT_OR_IN_TEST
    {
        detail::for_each(merge, [&](auto meta, auto &native) {
            meta.masked_load(native, meta.make_mask(bits), &mem[meta.offset], f);
        });
    }
    template <class T, class U, class F>
    static inline void store(const simd_member_type<T> v, U *mem, F f,
                             type_tag<T>) Vc_NOEXCEPT_OR_IN_TEST
    {
        detail::for_each(v, [&](auto meta, auto native) {
            meta.store(native, &mem[meta.offset], f, type_tag<T>());
        });
    }
    template <class T, class... As, class U, class F>
    static inline void masked_store(const simd_tuple<T, As...> v, U *mem, F f,
                                    const mask_member_type bits) Vc_NOEXCEPT_OR_IN_TEST
    {
        detail::for_each(v, [&](auto meta, auto native) {
            meta.masked_store(native, &mem[meta.offset], f, meta.make_mask(bits));
        });
    }
    template <class T, class... As>
    static inline mask_member_type negate(simd_tuple<T, As...> x) noexcept
    {
        mask_member_type bits = 0;
        for_each(x, [&bits](auto meta, auto native) {
            bits |= meta.mask_to_shifted_ullong(meta.negate(native));
        });
        return bits;
    }
private:
    template <class T, class... As, class BinaryOperation, size_t... Counts,
              size_t... Begins>
    static inline T reduce(const simd_tuple<T, As...> &tup,
                           const BinaryOperation &binary_op,
                           std::index_sequence<Counts...>, std::index_sequence<Begins...>)
    {
        const auto reduced_vec = detail::make_tuple(detail::tree_reduction<Counts, Begins>()(tup, binary_op)...);
        return detail::vec_to_scalar_reduction(reduced_vec, binary_op);
    }
public:
    template <class T, class BinaryOperation>
    static inline T reduce(size_tag, const simd<T> &x, const BinaryOperation &binary_op)
    {
        using ranges = n_abis_in_tuple<simd_member_type<T>>;
        return fixed_size_simd_impl::reduce(x.d, binary_op, typename ranges::counts(),
                                               typename ranges::begins());
    }
    template <class T, class... As>
    static inline simd_tuple<T, As...> min(const simd_tuple<T, As...> a,
                                              const simd_tuple<T, As...> b)
    {
        return apply([](auto impl, auto aa, auto bb) { return impl.min(aa, bb); }, a, b);
    }
    template <class T, class... As>
    static inline simd_tuple<T, As...> max(const simd_tuple<T, As...> a,
                                              const simd_tuple<T, As...> b)
    {
        return apply([](auto impl, auto aa, auto bb) { return impl.max(aa, bb); }, a, b);
    }
    template <class T, class... As>
    static inline simd_tuple<T, As...> complement(simd_tuple<T, As...> x) noexcept
    {
        return apply([](auto impl, auto xx) { return impl.complement(xx); }, x);
    }
    template <class T, class... As>
    static inline simd_tuple<T, As...> unary_minus(simd_tuple<T, As...> x) noexcept
    {
        return apply([](auto impl, auto xx) { return impl.unary_minus(xx); }, x);
    }
#define Vc_FIXED_OP(name_,op_) \
    template <class T, class... As> \
    static inline simd_tuple<T, As...> name_(simd_tuple<T, As...> x, \
                                                simd_tuple<T, As...> y) \
    { \
        return apply([](auto impl, auto xx, auto yy) { return impl.name_(xx, yy); }, x, \
                     y); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
        Vc_FIXED_OP(plus, +);
        Vc_FIXED_OP(minus, -);
        Vc_FIXED_OP(multiplies, *);
        Vc_FIXED_OP(divides, /);
        Vc_FIXED_OP(modulus, %);
        Vc_FIXED_OP(bit_and, &);
        Vc_FIXED_OP(bit_or, |);
        Vc_FIXED_OP(bit_xor, ^);
        Vc_FIXED_OP(bit_shift_left, <<);
        Vc_FIXED_OP(bit_shift_right, >>);
#undef Vc_FIXED_OP
    template <class T, class... As>
    static inline simd_tuple<T, As...> bit_shift_left(simd_tuple<T, As...> x, int y)
    {
        return apply([y](auto impl, auto xx) { return impl.bit_shift_left(xx, y); }, x);
    }
    template <class T, class... As>
    static inline simd_tuple<T, As...> bit_shift_right(simd_tuple<T, As...> x,
                                                          int y)
    {
        return apply([y](auto impl, auto xx) { return impl.bit_shift_right(xx, y); }, x);
    }
#define Vc_APPLY_ON_TUPLE_(name_) \
    template <class T, class... As> \
    static inline simd_tuple<T, As...> name_(simd_tuple<T, As...> x) noexcept \
    { \
        return apply( \
            [](auto impl, auto xx) { \
                using Vc::name_; \
                using V = typename decltype(impl)::simd_type; \
                return detail::data(name_(V(detail::private_init, xx))); \
            }, \
            x); \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
        Vc_APPLY_ON_TUPLE_(sqrt);
        Vc_APPLY_ON_TUPLE_(abs);
        Vc_APPLY_ON_TUPLE_(logb);
        Vc_APPLY_ON_TUPLE_(trunc);
        Vc_APPLY_ON_TUPLE_(floor);
        Vc_APPLY_ON_TUPLE_(ceil);
#undef Vc_APPLY_ON_TUPLE_
    template <class T, class... As>
    static inline simd_tuple<T, As...> frexp(const simd_tuple<T, As...> &x,
                                             fixed_size_storage<int, N> &exp) noexcept
    {
        return apply(frexp_fwd(), x, exp);
    }
    template <class T, class... As>
    static inline fixed_size_storage<int, N> fpclassify(simd_tuple<T, As...> x) noexcept
    {
        return detail::optimize_tuple(x.template apply_r<int>(
            [](auto impl, auto xx) { return impl.fpclassify(xx); }));
    }
#define Vc_TEST_ON_TUPLE_(name_) \
    template <class T, class... As> \
    static inline mask_member_type name_(simd_tuple<T, As...> x) noexcept \
    { \
        return test([](auto impl, auto xx) { return impl.name_(xx); }, x); \
    }
    Vc_TEST_ON_TUPLE_(isinf)
    Vc_TEST_ON_TUPLE_(isfinite)
    Vc_TEST_ON_TUPLE_(isnan)
    Vc_TEST_ON_TUPLE_(isnormal)
    Vc_TEST_ON_TUPLE_(signbit)
#undef Vc_TEST_ON_TUPLE_
    template <class... Ts> static inline void increment(simd_tuple<Ts...> &x)
    {
        for_each(x, [](auto meta, auto &native) { meta.increment(native); });
    }
    template <class... Ts> static inline void decrement(simd_tuple<Ts...> &x)
    {
        for_each(x, [](auto meta, auto &native) { meta.decrement(native); });
    }
#define Vc_CMP_OPERATIONS(cmp_) \
    template <class T, class... As> \
    static inline mask_member_type cmp_(const simd_tuple<T, As...> &x, \
                                        const simd_tuple<T, As...> &y) \
    { \
        mask_member_type bits = 0; \
        detail::for_each(x, y, [&bits](auto meta, auto native_x, auto native_y) { \
            bits |= meta.mask_to_shifted_ullong(meta.cmp_(native_x, native_y)); \
        }); \
        return bits; \
    } \
    Vc_NOTHING_EXPECTING_SEMICOLON
        Vc_CMP_OPERATIONS(equal_to);
        Vc_CMP_OPERATIONS(not_equal_to);
        Vc_CMP_OPERATIONS(less);
        Vc_CMP_OPERATIONS(greater);
        Vc_CMP_OPERATIONS(less_equal);
        Vc_CMP_OPERATIONS(greater_equal);
        Vc_CMP_OPERATIONS(isunordered);
#undef Vc_CMP_OPERATIONS
    template <class T, class... As>
    static Vc_INTRINSIC T get(const simd_tuple<T, As...> &v, int i) noexcept
    {
        return v[i];
    }
    template <class T, class... As, class U>
    static Vc_INTRINSIC void set(simd_tuple<T, As...> &v, int i, U &&x) noexcept
    {
        v.set(i, std::forward<U>(x));
    }
    template <typename T, class... As>
    static Vc_INTRINSIC void masked_assign(
        const mask_member_type bits, detail::simd_tuple<T, As...> &lhs,
        const detail::id<detail::simd_tuple<T, As...>> rhs)
    {
        detail::for_each(lhs, rhs, [&](auto meta, auto &native_lhs, auto native_rhs) {
            meta.masked_assign(meta.make_mask(bits), native_lhs, native_rhs);
        });
    }
    template <typename T, class... As>
    static Vc_INTRINSIC void masked_assign(const mask_member_type bits,
                                           detail::simd_tuple<T, As...> &lhs,
                                           const detail::id<T> rhs)
    {
        detail::for_each(lhs, [&](auto meta, auto &native_lhs) {
            meta.masked_assign(meta.make_mask(bits), native_lhs, rhs);
        });
    }
    template <template <typename> class Op, typename T, class... As>
    static inline void masked_cassign(const mask_member_type bits,
                                      detail::simd_tuple<T, As...> &lhs,
                                      const detail::simd_tuple<T, As...> rhs)
    {
        detail::for_each(lhs, rhs, [&](auto meta, auto &native_lhs, auto native_rhs) {
            meta.template masked_cassign<Op>(meta.make_mask(bits), native_lhs,
                                             native_rhs);
        });
    }
    template <template <typename> class Op, typename T, class... As>
    static inline void masked_cassign(const mask_member_type bits,
                                      detail::simd_tuple<T, As...> &lhs, const T rhs)
    {
        detail::for_each(lhs, [&](auto meta, auto &native_lhs) {
            meta.template masked_cassign<Op>(meta.make_mask(bits), native_lhs, rhs);
        });
    }
    template <template <typename> class Op, class T, class... As>
    static inline detail::simd_tuple<T, As...> masked_unary(
        const mask_member_type bits,
        const detail::simd_tuple<T, As...> v)
    {
#ifdef Vc_ICC
        detail::simd_tuple<T, As...> r;
        execute_n_times<N>(
            [&](auto i_) { r.set(i_, bits[i_] ? Op<T>{}(v[i_]) : v[i_]); });
        return r;
#else
        return v.apply_wrapped([&bits](auto meta, auto native) {
            return meta.template masked_unary<Op>(meta.make_mask(bits), native);
        });
#endif
    }
};
template <int N> struct fixed_size_mask_impl {
    static_assert(sizeof(ullong) * CHAR_BIT >= N,
                  "The fixed_size implementation relies on one "
                  "ullong being able to store all boolean "
                  "elements.");
    static constexpr std::make_index_sequence<N> index_seq = {};
    using mask_member_type = std::bitset<N>;
    template <class T> using simd_mask = Vc::simd_mask<T, simd_abi::fixed_size<N>>;
    using size_tag = size_constant<N>;
    template <class T> using type_tag = T *;
    static Vc_INTRINSIC mask_member_type to_bitset(const mask_member_type &bs) noexcept
    {
        return bs;
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type from_bitset(const mask_member_type &bs,
                                                     type_tag<T>) noexcept
    {
        return bs;
    }
    template <class T>
    static Vc_INTRINSIC mask_member_type broadcast(bool x, type_tag<T>) noexcept
    {
        return ullong(x) * ((1llu << N) - 1llu);
    }
    template <class F>
    static inline mask_member_type load(const bool *mem, F f, size_tag) noexcept
    {
        ullong r = 0;
        using Vs = fixed_size_storage<uchar, N>;
        detail::for_each(Vs{}, [&](auto meta, auto) {
            r |= meta.mask_to_shifted_ullong(
                meta.simd_mask.load(&mem[meta.offset], f, size_constant<meta.size()>()));
        });
        return r;
    }
    template <class F>
    static inline void masked_load(mask_member_type &merge, mask_member_type mask,
                                   const bool *mem, F) noexcept
    {
        execute_n_times<N>([&](auto i) {
            if (mask[i]) {
                merge[i] = mem[i];
            }
        });
    }
    template <class F>
    static inline void store(mask_member_type bs, bool *mem, F f, size_tag) noexcept
    {
#ifdef Vc_HAVE_AVX512BW
        const __m512i bool64 =
            and_(_mm512_movm_epi8(bs.to_ullong()), x86::one64(uchar()));
        detail::x86::store_n_bytes(size_constant<N>(), bool64, mem, f);
#elif defined Vc_HAVE_BMI2
#ifdef Vc_IS_AMD64
        unused(f);
        execute_n_times<N / 8>([&](auto i) {
            constexpr size_t offset = i * 8;
            const ullong bool8 =
                _pdep_u64(bs.to_ullong() >> offset, 0x0101010101010101ULL);
            std::memcpy(&mem[offset], &bool8, 8);
        });
        if (N % 8 > 0) {
            constexpr size_t offset = (N / 8) * 8;
            const ullong bool8 =
                _pdep_u64(bs.to_ullong() >> offset, 0x0101010101010101ULL);
            std::memcpy(&mem[offset], &bool8, N % 8);
        }
#else
        unused(f);
        execute_n_times<N / 4>([&](auto i) {
            constexpr size_t offset = i * 4;
            const ullong bool4 =
                _pdep_u32(bs.to_ullong() >> offset, 0x01010101U);
            std::memcpy(&mem[offset], &bool4, 4);
        });
        if (N % 4 > 0) {
            constexpr size_t offset = (N / 4) * 4;
            const ullong bool4 =
                _pdep_u32(bs.to_ullong() >> offset, 0x01010101U);
            std::memcpy(&mem[offset], &bool4, N % 4);
        }
#endif
#elif defined Vc_HAVE_SSE2
        using V = simd<uchar, simd_abi::Sse>;
        ullong bits = bs.to_ullong();
        execute_n_times<(N + 15) / 16>([&](auto i) {
            constexpr size_t offset = i * 16;
            constexpr size_t remaining = N - offset;
            if (remaining == 1) {
                mem[offset] = static_cast<bool>(bits >> offset);
            } else if (remaining <= 4) {
                const uint bool4 = ((bits >> offset) * 0x00204081U) & 0x01010101U;
                std::memcpy(&mem[offset], &bool4, remaining);
            } else if (remaining <= 7) {
                const ullong bool8 =
                    ((bits >> offset) * 0x40810204081ULL) & 0x0101010101010101ULL;
                std::memcpy(&mem[offset], &bool8, remaining);
            } else {
                auto tmp = _mm_cvtsi32_si128(bits >> offset);
                tmp = _mm_unpacklo_epi8(tmp, tmp);
                tmp = _mm_unpacklo_epi16(tmp, tmp);
                tmp = _mm_unpacklo_epi32(tmp, tmp);
                V tmp2(tmp);
                tmp2 &= V([](auto j) {
                    return static_cast<uchar>(1 << (j % CHAR_BIT));
                });
                const __m128i bool16 =
                    _mm_add_epi8(data(tmp2 == V()),
                                 x86::one16(uchar()));
                if (remaining >= 16) {
                    x86::store16(bool16, &mem[offset], f);
                } else if (remaining & 3) {
                    constexpr int to_shift = 16 - int(remaining);
                    _mm_maskmoveu_si128(bool16,
                                        _mm_srli_si128(allone<__m128i>(), to_shift),
                                        reinterpret_cast<char *>(&mem[offset]));
                } else
                    if (remaining >= 8) {
                    x86::store8(bool16, &mem[offset], f);
                    if (remaining == 12) {
                        x86::store4(_mm_unpackhi_epi64(bool16, bool16), &mem[offset + 8],
                                    f);
                    }
                }
            }
        });
#else
        using Vs = fixed_size_storage<uchar, N>;
        detail::for_each(Vs{}, [&](auto meta, auto) {
            meta.store(meta.make_mask(bs), &mem[meta.offset], f, meta.size_tag);
        });
#endif
    }
    template <class F>
    static inline void masked_store(const mask_member_type v, bool *mem, F,
                                    const mask_member_type k) noexcept
    {
        execute_n_times<N>([&](auto i) {
            if (k[i]) {
                mem[i] = v[i];
            }
        });
    }
    static Vc_INTRINSIC mask_member_type negate(const mask_member_type &x,
                                                size_tag) noexcept
    {
        return ~x;
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_and(const simd_mask<T> &x, const simd_mask<T> &y) noexcept
    {
        return {bitset_init, x.d & y.d};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> logical_or(const simd_mask<T> &x, const simd_mask<T> &y) noexcept
    {
        return {bitset_init, x.d | y.d};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_and(const simd_mask<T> &x, const simd_mask<T> &y) noexcept
    {
        return {bitset_init, x.d & y.d};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_or(const simd_mask<T> &x, const simd_mask<T> &y) noexcept
    {
        return {bitset_init, x.d | y.d};
    }
    template <class T>
    static Vc_INTRINSIC simd_mask<T> bit_xor(const simd_mask<T> &x, const simd_mask<T> &y) noexcept
    {
        return {bitset_init, x.d ^ y.d};
    }
    static Vc_INTRINSIC bool get(const mask_member_type k, int i) noexcept
    {
        return k[i];
    }
    static Vc_INTRINSIC void set(mask_member_type &k, int i, bool x) noexcept
    {
        k.set(i, x);
    }
    static Vc_INTRINSIC void masked_assign(const mask_member_type k,
                                           mask_member_type &lhs,
                                           const mask_member_type rhs)
    {
        lhs = (lhs & ~k) | (rhs & k);
    }
    static Vc_INTRINSIC void masked_assign(const mask_member_type k,
                                           mask_member_type &lhs, const bool rhs)
    {
        if (rhs) {
            lhs |= k;
        } else {
            lhs &= ~k;
        }
    }
};
template <class From, class To>
struct simd_converter<From, simd_abi::scalar, To, simd_abi::fixed_size<1>> {
    simd_tuple<To, simd_abi::scalar> operator()(From x) { return {static_cast<To>(x)}; }
};
template <class From, class To>
struct simd_converter<From, simd_abi::fixed_size<1>, To, simd_abi::scalar> {
    Vc_INTRINSIC To operator()(simd_tuple<From, simd_abi::scalar> x)
    {
        return {static_cast<To>(x.first)};
    }
};
template <class T, int N>
struct simd_converter<T, simd_abi::fixed_size<N>, T, simd_abi::fixed_size<N>> {
    using arg = fixed_size_storage<T, N>;
    Vc_INTRINSIC const arg &operator()(const arg &x) { return x; }
};
template <size_t ChunkSize, class T> struct determine_required_input_chunks;
template <class T, class... Abis>
struct determine_required_input_chunks<0, simd_tuple<T, Abis...>>
    : public std::integral_constant<size_t, 0> {
};
template <size_t ChunkSize, class T, class Abi0, class... Abis>
struct determine_required_input_chunks<ChunkSize, simd_tuple<T, Abi0, Abis...>>
    : public std::integral_constant<
          size_t, determine_required_input_chunks<ChunkSize - simd_size_v<T, Abi0>,
                                                  simd_tuple<T, Abis...>>::value> {
};
template <class From, class To> struct fixed_size_converter {
    struct OneToMultipleChunks {
    };
    template <int N> struct MultipleToOneChunk {
    };
    struct EqualChunks {
    };
    template <class FromAbi, class ToAbi, size_t ToSize = simd_size_v<To, ToAbi>,
              size_t FromSize = simd_size_v<From, FromAbi>>
    using ChunkRelation = std::conditional_t<
        (ToSize < FromSize), OneToMultipleChunks,
        std::conditional_t<(ToSize == FromSize), EqualChunks,
                           MultipleToOneChunk<int(ToSize / FromSize)>>>;
    template <class... Abis>
    using return_type = fixed_size_storage<To, simd_tuple<From, Abis...>::size_v>;
protected:
    template <class A0>
    Vc_INTRINSIC return_type<A0> impl(OneToMultipleChunks, const simd_tuple<From, A0> &x)
    {
        using R = return_type<A0>;
        simd_converter<From, A0, To, typename R::first_abi> native_cvt;
        auto &&multiple_return_chunks = native_cvt(x.first);
        return detail::to_tuple<To, typename R::first_abi>(multiple_return_chunks);
    }
    template <class... Abis>
    Vc_INTRINSIC return_type<Abis...> impl(OneToMultipleChunks,
                                           const simd_tuple<From, Abis...> &x)
    {
        using R = return_type<Abis...>;
        using arg = simd_tuple<From, Abis...>;
        constexpr size_t first_chunk = simd_size_v<From, typename arg::first_abi>;
        simd_converter<From, typename arg::first_abi, To, typename R::first_abi>
            native_cvt;
        auto &&multiple_return_chunks = native_cvt(x.first);
        constexpr size_t n_output_chunks =
            first_chunk / simd_size_v<To, typename R::first_abi>;
        return detail::tuple_concat(
            detail::to_tuple<To, typename R::first_abi>(multiple_return_chunks),
            impl(ChunkRelation<typename arg::second_type::first_abi,
                               typename tuple_element<n_output_chunks, R>::type::abi_type>(),
                 x.second));
    }
    template <int N, class A0, class... Abis>
    Vc_INTRINSIC return_type<A0, Abis...> impl(MultipleToOneChunk<N>,
                                               const simd_tuple<From, A0, Abis...> &x)
    {
        return impl_mto(std::integral_constant<bool, sizeof...(Abis) + 1 == N>(),
                        std::make_index_sequence<N>(), x);
    }
    template <size_t... Indexes, class A0, class... Abis>
    Vc_INTRINSIC return_type<A0, Abis...> impl_mto(std::true_type,
                                                   std::index_sequence<Indexes...>,
                                                   const simd_tuple<From, A0, Abis...> &x)
    {
        using R = return_type<A0, Abis...>;
        simd_converter<From, A0, To, typename R::first_abi> native_cvt;
        return {native_cvt(detail::get<Indexes>(x)...)};
    }
    template <size_t... Indexes, class A0, class... Abis>
    Vc_INTRINSIC return_type<A0, Abis...> impl_mto(std::false_type,
                                                   std::index_sequence<Indexes...>,
                                                   const simd_tuple<From, A0, Abis...> &x)
    {
        using R = return_type<A0, Abis...>;
        simd_converter<From, A0, To, typename R::first_abi> native_cvt;
        return {
            native_cvt(detail::get<Indexes>(x)...),
            impl(
                ChunkRelation<
                    typename tuple_element<sizeof...(Indexes),
                                           simd_tuple<From, A0, Abis...>>::type::abi_type,
                    typename R::second_type::first_abi>(),
                tuple_pop_front(size_constant<sizeof...(Indexes)>(), x))};
    }
    template <class A0>
    Vc_INTRINSIC return_type<A0> impl(EqualChunks, const simd_tuple<From, A0> &x)
    {
        simd_converter<From, A0, To, typename return_type<A0>::first_abi> native_cvt;
        return {native_cvt(x.first)};
    }
    template <class A0, class A1, class... Abis>
    Vc_INTRINSIC return_type<A0, A1, Abis...> impl(
        EqualChunks, const simd_tuple<From, A0, A1, Abis...> &x)
    {
        using R = return_type<A0, A1, Abis...>;
        using Rem = typename R::second_type;
        simd_converter<From, A0, To, typename R::first_abi> native_cvt;
        return {native_cvt(x.first),
                impl(ChunkRelation<A1, typename Rem::first_abi>(), x.second)};
    }
};
template <class From, class To, int N>
struct simd_converter<From, simd_abi::fixed_size<N>, To, simd_abi::fixed_size<N>>
    : public fixed_size_converter<From, To> {
    using base = fixed_size_converter<From, To>;
    using return_type = fixed_size_storage<To, N>;
    using arg = fixed_size_storage<From, N>;
    Vc_INTRINSIC return_type operator()(const arg &x)
    {
        using CR = typename base::template ChunkRelation<typename arg::first_abi,
                                                         typename return_type::first_abi>;
        return base::impl(CR(), x);
    }
};
template <class From, class A, class To, int N>
struct simd_converter<From, A, To, simd_abi::fixed_size<N>> {
    using traits = detail::traits<From, A>;
    using arg = typename traits::simd_member_type;
    using return_type = fixed_size_storage<To, N>;
    static_assert(N == simd_size_v<From, A>,
                  "simd_converter to fixed_size only works for equal element counts");
    Vc_INTRINSIC return_type operator()(arg x)
    {
        return impl(std::make_index_sequence<return_type::tuple_size>(), x);
    }
private:
    return_type impl(std::index_sequence<0>, arg x)
    {
        simd_converter<From, A, To, typename return_type::first_abi> native_cvt;
        return {native_cvt(x)};
    }
    template <size_t... Indexes> return_type impl(std::index_sequence<Indexes...>, arg x)
    {
        simd_converter<From, A, To, typename return_type::first_abi> native_cvt;
        const auto &tmp = native_cvt(x);
        return {tmp[Indexes]...};
    }
};
template <class From, int N, class To, class A>
struct simd_converter<From, simd_abi::fixed_size<N>, To, A> {
    using traits = detail::traits<To, A>;
    using return_type = typename traits::simd_member_type;
    using arg = fixed_size_storage<From, N>;
    static_assert(N == simd_size_v<To, A>,
                  "simd_converter to fixed_size only works for equal element counts");
    Vc_INTRINSIC return_type operator()(arg x)
    {
        return impl(std::make_index_sequence<arg::tuple_size>(), x);
    }
private:
    return_type impl(std::index_sequence<0>, arg x)
    {
        simd_converter<From, typename arg::first_abi, To, A> native_cvt;
        return {native_cvt(x.first)};
    }
    template <size_t... Indexes> return_type impl(std::index_sequence<Indexes...>, arg x)
    {
        simd_converter<From, typename arg::first_abi, To, A> native_cvt;
        return native_cvt(detail::get<Indexes>(x)...);
    }
};
template <class T, class A0, class... As, int N>
struct split_to_tuple<std::tuple<simd<T, A0>, simd<T, As>...>, simd_abi::fixed_size<N>> {
    template <class A> using V = simd<T, A>;
    std::tuple<V<A0>, V<As>...> operator()(const simd<T, simd_abi::fixed_size<N>> &x)
    {
        using STup = fixed_size_storage<T, N>;
        return impl(A0(), detail::data(x), std::make_index_sequence<1 + sizeof...(As)>(),
                    std::make_index_sequence<STup::tuple_size>());
    }
private:
    template <int N0> using Stor = fixed_size_storage<T, N0>;
    template <std::size_t I, int N0>
    using tuple_abi = typename tuple_element<I, Stor<N0>>::abi_type;
    template <int N0, class... Bs, size_t... Indexes>
    std::tuple<V<A0>, V<As>...> impl2(
        const detail::simd_tuple<T, tuple_abi<Indexes, N0>..., Bs...> &x,
        std::index_sequence<Indexes...>)
    {
        return std::tuple_cat(
            std::tuple<V<A0>>(
                {private_init, detail::make_tuple(detail::get_simd<Indexes>(x)...)}),
            split_to_tuple<std::tuple<V<As>...>, simd_abi::fixed_size<N - N0>>()(
                {private_init, tuple_pop_front(size_constant<sizeof...(Indexes)>(), x)}));
    }
    template <int N0, size_t... Indexes0, size_t... Indexes1>
    std::tuple<V<A0>, V<As>...> impl(simd_abi::fixed_size<N0>,
                                     const detail::simd_tuple<T, A0, As...> &x,
                                     std::index_sequence<Indexes0...>,
                                     std::index_sequence<Indexes1...>)
    {
        return impl2<N0>(x, std::make_index_sequence<Stor<N0>::tuple_size>());
    }
    template <class NotFixedAbi, size_t... Indexes>
    std::tuple<V<A0>, V<As>...> impl(NotFixedAbi,
                                     const detail::simd_tuple<T, A0, As...> &x,
                                     std::index_sequence<Indexes...>,
                                     std::index_sequence<Indexes...>)
    {
        return {detail::get_simd<Indexes>(x)...};
    }
    template <class NotFixedAbi, class... Bs, size_t... Indexes0, size_t... Indexes1>
    std::tuple<V<A0>, V<As>...> impl(NotFixedAbi, const detail::simd_tuple<T, Bs...> &x,
                                     std::index_sequence<Indexes0...>,
                                     std::index_sequence<Indexes1...>)
    {
        std::size_t offset = V<A0>::size();
        std::size_t tmp;
        return {V<A0>(reinterpret_cast<const detail::may_alias<T> *>(&x), vector_aligned),
                V<As>(reinterpret_cast<const detail::may_alias<T> *>(&x) +
                          (tmp = offset, offset += V<As>::size(), tmp),
                      element_aligned)...};
    }
    template <class NotFixedAbi, class... Bs, size_t... Indexes0, size_t... Indexes1>
    std::tuple<V<A0>, V<As>...> impl(NotFixedAbi,
                                     const detail::simd_tuple<T, A0, Bs...> &x,
                                     std::index_sequence<Indexes0...>,
                                     std::index_sequence<Indexes1...>)
    {
        return std::tuple_cat(std::tuple<V<A0>>({private_init, x.first}),
                              split_to_tuple<std::tuple<V<As>...>,
                                             simd_abi::fixed_size<N - V<A0>::size()>>()(
                                  {private_init, x.second}));
    }
};
}
template <class T, int N> inline bool all_of(const fixed_size_mask<T, N> &k)
{
    return data(k).all();
}
template <class T, int N> inline bool any_of(const fixed_size_mask<T, N> &k)
{
    return data(k).any();
}
template <class T, int N> inline bool none_of(const fixed_size_mask<T, N> &k)
{
    return data(k).none();
}
template <class T, int N> inline bool some_of(const fixed_size_mask<T, N> &k)
{
    for (int i = 1; i < N; ++i) {
        if (k[i] != k[i - 1]) {
            return true;
        }
    }
    return false;
}
template <class T, int N> inline int popcount(const fixed_size_mask<T, N> &k)
{
    return data(k).count();
}
template <class T, int N> inline int find_first_set(const fixed_size_mask<T, N> &k)
{
    for (int i = 0; i < N; ++i) {
        if (k[i]) {
            return i;
        }
    }
    return -1;
}
template <class T, int N> inline int find_last_set(const fixed_size_mask<T, N> &k)
{
    for (int i = N - 1; i >= 0; --i) {
        if (k[i]) {
            return i;
        }
    }
    return -1;
}
Vc_VERSIONED_NAMESPACE_END
namespace std
{
template <class T, int N>
struct equal_to<Vc::simd_mask<T, Vc::simd_abi::fixed_size<N>>> {
private:
    using M = Vc::simd_mask<T, Vc::simd_abi::fixed_size<N>>;
public:
    bool operator()(const M &x, const M &y) const
    {
        bool r = x[0] == y[0];
        for (int i = 1; i < N; ++i) {
            r = r && x[i] == y[i];
        }
        return r;
    }
};
}
#endif
#if defined Vc_GCC && Vc_GCC >= 0x60000
#pragma GCC diagnostic pop
#endif
