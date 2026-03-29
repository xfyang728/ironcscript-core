#ifndef CSE_FFI_H
#define CSE_FFI_H

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <cstring>
#include <iostream>
#include <array>

namespace cse {

enum class FFIType : uint8_t {
    Void = 0,
    Int8,
    Int16,
    Int32,
    Int64,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    Float,
    Double,
    Pointer
};

struct TypeDescriptor {
    FFIType type;
    size_t size;
    size_t alignment;
    bool isFloat;
};

constexpr TypeDescriptor g_TypeDescriptors[] = {
    {FFIType::Void,    0,  0, false},
    {FFIType::Int8,    1,  1, false},
    {FFIType::Int16,   2,  2, false},
    {FFIType::Int32,   4,  4, false},
    {FFIType::Int64,   8,  8, false},
    {FFIType::UInt8,   1,  1, false},
    {FFIType::UInt16,  2,  2, false},
    {FFIType::UInt32,  4,  4, false},
    {FFIType::UInt64,  8,  8, false},
    {FFIType::Float,   4,  4, true},
    {FFIType::Double,  8,  8, true},
    {FFIType::Pointer, 8,  8, false},
};

template<typename T>
struct FFIMypeOf;

#define FFI_TYPE_MAPPING(CPP_TYPE, FFI_TYPE_ENUM)          \
    template<> struct FFIMypeOf<CPP_TYPE> {                \
        static constexpr FFIType type = FFI_TYPE_ENUM;     \
    };

FFI_TYPE_MAPPING(int8_t,   FFIType::Int8)
FFI_TYPE_MAPPING(int16_t,  FFIType::Int16)
FFI_TYPE_MAPPING(int32_t,  FFIType::Int32)
FFI_TYPE_MAPPING(int64_t,  FFIType::Int64)
FFI_TYPE_MAPPING(uint8_t,   FFIType::UInt8)
FFI_TYPE_MAPPING(uint16_t, FFIType::UInt16)
FFI_TYPE_MAPPING(uint32_t, FFIType::UInt32)
FFI_TYPE_MAPPING(uint64_t, FFIType::UInt64)
FFI_TYPE_MAPPING(float,    FFIType::Float)
FFI_TYPE_MAPPING(double,   FFIType::Double)
FFI_TYPE_MAPPING(void*,    FFIType::Pointer)

template<typename T>
constexpr bool IsFloatType = std::is_floating_point<T>::value;

constexpr size_t MaxFFIArgs = 8;
constexpr size_t FFIBufferSize = MaxFFIArgs * 16;

class FFICallConductor {
public:
    template<typename Ret>
    Ret call(void* funcPtr) {
        using FuncType = Ret(*)();
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func();
    }

    template<typename Ret, typename A0>
    Ret call(void* funcPtr, A0 a0) {
        try {
            return callInt<Ret>(funcPtr, a0);
        } catch (const std::exception& e) {
            // 处理 C++ 异常，将其转换为 IronCS 可以处理的形式
            // 这里简单处理，返回一个特殊值
            std::cerr << "Caught C++ exception: " << e.what() << std::endl;
            return getDefaultValue<Ret>();
        }
    }

    template<typename Ret, typename A0, typename A1>
    Ret call(void* funcPtr, A0 a0, A1 a1) {
        try {
            return callInt<Ret>(funcPtr, a0, a1);
        } catch (const std::exception& e) {
            std::cerr << "Caught C++ exception: " << e.what() << std::endl;
            return getDefaultValue<Ret>();
        }
    }

    template<typename Ret, typename A0, typename A1, typename A2>
    Ret call(void* funcPtr, A0 a0, A1 a1, A2 a2) {
        try {
            return callInt<Ret>(funcPtr, a0, a1, a2);
        } catch (const std::exception& e) {
            std::cerr << "Caught C++ exception: " << e.what() << std::endl;
            return getDefaultValue<Ret>();
        }
    }

    template<typename Ret, typename A0, typename A1, typename A2, typename A3>
    Ret call(void* funcPtr, A0 a0, A1 a1, A2 a2, A3 a3) {
        try {
            return callInt<Ret>(funcPtr, a0, a1, a2, a3);
        } catch (const std::exception& e) {
            std::cerr << "Caught C++ exception: " << e.what() << std::endl;
            return getDefaultValue<Ret>();
        }
    }

private:
    template<typename Ret>
    typename std::enable_if<std::is_integral<Ret>::value, Ret>::type
    getDefaultValue() {
        return static_cast<Ret>(-1);
    }

    template<typename Ret>
    typename std::enable_if<std::is_floating_point<Ret>::value, Ret>::type
    getDefaultValue() {
        return static_cast<Ret>(-1.0);
    }

    template<typename Ret>
    typename std::enable_if<!std::is_integral<Ret>::value && !std::is_floating_point<Ret>::value, Ret>::type
    getDefaultValue() {
        return Ret();
    }

    template<typename Ret>
    Ret callInt(void* funcPtr) {
        using FuncType = Ret(*)();
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func();
    }

    template<typename Ret, typename A0>
    Ret callInt(void* funcPtr, A0 a0) {
        using FuncType = Ret(*)(A0);
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func(a0);
    }

    template<typename Ret, typename A0, typename A1>
    Ret callInt(void* funcPtr, A0 a0, A1 a1) {
        using FuncType = Ret(*)(A0, A1);
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func(a0, a1);
    }

    template<typename Ret, typename A0, typename A1, typename A2>
    Ret callInt(void* funcPtr, A0 a0, A1 a1, A2 a2) {
        using FuncType = Ret(*)(A0, A1, A2);
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func(a0, a1, a2);
    }

    template<typename Ret, typename A0, typename A1, typename A2, typename A3>
    Ret callInt(void* funcPtr, A0 a0, A1 a1, A2 a2, A3 a3) {
        using FuncType = Ret(*)(A0, A1, A2, A3);
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func(a0, a1, a2, a3);
    }

    template<typename Ret, typename A0>
    Ret callFloatDouble(void* funcPtr, A0 a0) {
        using FuncType = Ret(*)(A0);
        FuncType func = reinterpret_cast<FuncType>(funcPtr);
        return func(a0);
    }
};

union ReturnStorage {
    int64_t asInt;
    double asDouble;
    float asFloat;
    void* asPointer;
    char bytes[16];
};

template<typename T>
T unpackReturnValue(int64_t rawValue);

template<>
inline int32_t unpackReturnValue<int32_t>(int64_t rawValue) {
    return static_cast<int32_t>(rawValue);
}

template<>
inline int64_t unpackReturnValue<int64_t>(int64_t rawValue) {
    return rawValue;
}

template<>
inline double unpackReturnValue<double>(int64_t /*rawValue*/) {
    double result;
#if defined(_WIN64)
    __asm__ volatile ("movsd %%xmm0, %0" : "=m"(result));
#else
    __asm__ volatile ("movd %%xmm0, %0" : "=r"(result));
#endif
    return result;
}

template<>
inline float unpackReturnValue<float>(int64_t /*rawValue*/) {
    float result;
    __asm__ volatile ("movd %%xmm0, %0" : "=r"(result));
    return result;
}

} // namespace cse

#endif // CSE_FFI_H
