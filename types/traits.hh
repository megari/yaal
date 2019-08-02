#ifndef __YAAL_TYPES__TRAITS__
#define __YAAL_TYPES__TRAITS__ 1
#include "../requirements.hh"
#ifdef __YAAL__

#include "../types/autounion.hh"

namespace yaal {

    namespace internal {
        // base_type_traits contains everything about all types
        // this struct's values should be overwritten when known better
        template<typename T>
        struct base_type_traits {
            typedef T bigger;
            typedef T smaller;
            static constexpr bool biggest = false;
            static constexpr bool smallest = false;
            static constexpr unsigned char bits = sizeof(T) * 8;
            static constexpr bool is_signed = ((T)-1) < 0;
        };

        // helps us to define all primitive types
        template<typename T>
        struct primitive_type_traits : public base_type_traits<T> {
            typedef T as_arg;
        };
    }

    // generic base struct for all types.
    template<typename T>
    struct type_traits : public internal::base_type_traits<T> {
        typedef T& as_arg;
    };


#   define YAAL_TRAIT_H(_type) template<> \
        struct type_traits<_type> : \
            public internal::primitive_type_traits<_type>

#   define YAAL_TRAIT(_type, _bigger, _smaller, _bits) \
        YAAL_TRAIT_H(_type) \
        { \
            typedef _bigger bigger; \
            typedef _smaller smaller; \
            static constexpr uint8_t bits = _bits; \
        };

#   define YAAL_TRAIT_S(_type, _bigger, _bits) \
        YAAL_TRAIT_H(_type) \
        { \
            typedef _bigger bigger; \
            static constexpr bool smallest = true; \
            static constexpr uint8_t bits = _bits; \
        };

#   define YAAL_TRAIT_B(_type, _smaller, _bits) \
        YAAL_TRAIT_H(_type) \
        { \
            typedef _smaller smaller; \
            static constexpr bool biggest = true; \
            static constexpr uint8_t bits = _bits; \
        };


    // FIXME: these only applies on 8bit avr when int is 16bit

    YAAL_TRAIT_S(unsigned char, unsigned int, 8);
    YAAL_TRAIT(unsigned int, unsigned long, unsigned char, 16);
    YAAL_TRAIT(unsigned short, unsigned long, unsigned char, 16);
    YAAL_TRAIT(unsigned long, unsigned long long, unsigned int, 32);
    YAAL_TRAIT_B(unsigned long long, unsigned long, 64);

    YAAL_TRAIT_S(signed char, signed int, 8);
    YAAL_TRAIT(signed int, signed long, signed char, 16);
    YAAL_TRAIT(signed short, signed long, signed char, 16);
    YAAL_TRAIT(signed long, signed long long, signed int, 32);
    YAAL_TRAIT_B(signed long long, signed long, 64);

    YAAL_TRAIT_H(double) { };
    YAAL_TRAIT_H(float) { };

#   undef YAAL_TRAIT_H
#   undef YAAL_TRAIT
#   undef YAAL_TRAIT_S
#   undef YAAL_TRAIT_B

    template<typename T>
    constexpr bool integer_type = false;

    template<>
    constexpr bool integer_type<char> = true;
    template<>
    constexpr bool integer_type<signed char> = true;
    template<>
    constexpr bool integer_type<unsigned char> = true;
    template<>
    constexpr bool integer_type<signed short> = true;
    template<>
    constexpr bool integer_type<unsigned short> = true;
    template<>
    constexpr bool integer_type<signed int> = true;
    template<>
    constexpr bool integer_type<unsigned int> = true;
    template<>
    constexpr bool integer_type<signed long> = true;
    template<>
    constexpr bool integer_type<unsigned long> = true;
    template<>
    constexpr bool integer_type<signed long long> = true;
    template<>
    constexpr bool integer_type<unsigned long long> = true;

    template<typename T, typename ...Ts>
    constexpr bool integer_types = integer_type<T> && integer_types<Ts...>;

    template<typename T>
    constexpr bool integer_types<T> = integer_type<T>;

    static_assert(!integer_type<float>, "integer_type fail!");
    static_assert(!integer_type<double>, "integer_type fail!");
    namespace {
        struct foo_ { int foo; };
        static_assert(!integer_type<foo_>, "integer_type fail!");
        static_assert(!integer_type<autounion<foo_>>, "integer_type fail!");
        static_assert(!integer_types<uint8_t, foo_>, "integer_types fail!");
        static_assert(!integer_types<uint8_t, foo_, foo_>, "integer_types fail!");
        static_assert(!integer_types<uint8_t, foo_, foo_, foo_>, "integer_types fail!");

        static_assert(!integer_types<uint8_t, foo_, uint8_t, foo_>, "integer_types fail!");
        static_assert(!integer_types<foo_, uint8_t, foo_, uint8_t>, "integer_types fail!");
    }
    static_assert(integer_type<char>, "integer_type fail!");
    static_assert(integer_type<signed char>, "integer_type fail!");
    static_assert(integer_type<unsigned char>, "integer_type fail!");
    static_assert(integer_type<short>, "integer_type fail!");
    static_assert(integer_type<signed short>, "integer_type fail!");
    static_assert(integer_type<unsigned short>, "integer_type fail!");
    static_assert(integer_type<int>, "integer_type fail!");
    static_assert(integer_type<signed int>, "integer_type fail!");
    static_assert(integer_type<unsigned int>, "integer_type fail!");
    static_assert(integer_type<long>, "integer_type fail!");
    static_assert(integer_type<signed long>, "integer_type fail!");
    static_assert(integer_type<unsigned long>, "integer_type fail!");
    static_assert(integer_type<long long>, "integer_type fail!");
    static_assert(integer_type<signed long long>, "integer_type fail!");
    static_assert(integer_type<unsigned long long>, "integer_type fail!");
    static_assert(integer_type<int8_t>, "integer_type fail!");
    static_assert(integer_type<uint8_t>, "integer_type fail!");
    static_assert(integer_type<int16_t>, "integer_type fail!");
    static_assert(integer_type<uint16_t>, "integer_type fail!");
    static_assert(integer_type<int32_t>, "integer_type fail!");
    static_assert(integer_type<uint32_t>, "integer_type fail!");
    static_assert(integer_type<int64_t>, "integer_type fail!");
    static_assert(integer_type<uint64_t>, "integer_type fail!");

    static_assert(integer_types<char>, "integer_types fail!");
    static_assert(integer_types<signed char>, "integer_types fail!");
    static_assert(integer_types<unsigned char>, "integer_types fail!");
    static_assert(integer_types<short>, "integer_types fail!");
    static_assert(integer_types<signed short>, "integer_types fail!");
    static_assert(integer_types<unsigned short>, "integer_types fail!");
    static_assert(integer_types<int>, "integer_types fail!");
    static_assert(integer_types<signed int>, "integer_types fail!");
    static_assert(integer_types<unsigned int>, "integer_types fail!");
    static_assert(integer_types<long>, "integer_types fail!");
    static_assert(integer_types<signed long>, "integer_types fail!");
    static_assert(integer_types<unsigned long>, "integer_types fail!");
    static_assert(integer_types<long long>, "integer_types fail!");
    static_assert(integer_types<signed long long>, "integer_types fail!");
    static_assert(integer_types<unsigned long long>, "integer_types fail!");
    static_assert(integer_types<int8_t>, "integer_types fail!");
    static_assert(integer_types<uint8_t>, "integer_types fail!");
    static_assert(integer_types<int16_t>, "integer_types fail!");
    static_assert(integer_types<uint16_t>, "integer_types fail!");
    static_assert(integer_types<int32_t>, "integer_types fail!");
    static_assert(integer_types<uint32_t>, "integer_types fail!");
    static_assert(integer_types<int64_t>, "integer_types fail!");
    static_assert(integer_types<uint64_t>, "integer_types fail!");
    static_assert(integer_types<uint8_t,  uint32_t, uint64_t, uint16_t>, "integer_types fail!");
    static_assert(integer_types<uint16_t, uint64_t, uint32_t, uint8_t>, "integer_types fail!");
    static_assert(integer_types<uint32_t, uint16_t, uint8_t, uint64_t>, "integer_types fail!");
    static_assert(integer_types<uint64_t, uint8_t,  uint16_t, uint32_t>, "integer_types fail!");

}

#endif
#endif
