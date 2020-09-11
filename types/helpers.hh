#ifndef __YAAL_TYPES__HELPERS__
#define __YAAL_TYPES__HELPERS__ 1
#include "../requirements.hh"
#ifdef __YAAL__

namespace yaal {

    namespace internal {

        /*! TypeIf template struct can be used to select type
         * using boolean expression at compile time
         * result is in member named type
         */
        template<bool, typename true_type, typename false_type>
        struct TypeIf {
            typedef false_type type;
        };
        template<typename true_type, typename false_type>
        struct TypeIf<true, true_type, false_type> {
            typedef true_type type;
        };

        template<bool b, typename ...Ts>
        struct enable_if {};

        template<typename ...Args>
        struct pack { };
        template<typename ...Ts>
        struct enable_if<true, Ts...> { typedef pack<Ts...> type; };

        template<bool b, typename ...Ts>
        using enable_if_t = typename enable_if<b, Ts...>::type;

        // Typeof stuff.
        template<typename T>
        struct typeof_foo {
            using type = T;
            type val;
            typeof_foo() {}
        } __attribute__((packed));

        template<typename T>
        struct typeof_foo<T&> {
            using type = typename typeof_foo<T>::type;
            type val;
            typeof_foo() {}
        };

        template<typename T>
        struct typeof_foo<T&&> {
            using type = typename typeof_foo<T>::type;
            type val;
            typeof_foo() {}
        };

        template<typename T>
        constexpr bool nonref_type = true;
        template<typename T>
        constexpr bool nonref_type<T&> = false;
        template<typename T>
        constexpr bool nonref_type<T&&> = false;

        template<typename T>
        constexpr bool ref_type = !nonref_type<T>;

        //template<typename T, enable_if_t<nonref_type<T>, T>* = nullptr>
        //constexpr T typeof_func(T);
        template<typename T /*, enable_if_t<nonref_type<T>, T>* = nullptr*/>
        constexpr T typeof_func(T&);
        template<typename T /*, enable_if_t<nonref_type<T>, T>* = nullptr*/>
        constexpr T typeof_func(T&&);

        template<typename T>
        using typeof_t =
            decltype(typeof_func(typeof_foo<T>().val));

        template<typename T, typename S>
        constexpr bool is_same_type = false;

        template<typename T>
        constexpr bool is_same_type<T, T> = true;

        static_assert(is_same_type<int, int>, "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int>, int>, "Type mismatch. :(");
        static_assert(is_same_type<int, typeof_t<int>>, "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int>, typeof_t<int>>,
            "Type mismatch. :(");

        static_assert(is_same_type<int&, int&>, "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int&>, int>, "Type mismatch. :(");
        static_assert(is_same_type<int, typeof_t<int&>>, "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int&>, typeof_t<int>>,
            "Type mismatch. :(");

        static_assert(is_same_type<int&&, int&&>, "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int&&>, int>, "Type mismatch. :(");
        static_assert(is_same_type<int, typeof_t<int&&>>, "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int&&>, typeof_t<int>>,
            "Type mismatch. :(");

        static_assert(is_same_type<typeof_t<int&&>, typeof_t<int&>>,
            "Type mismatch. :(");
        static_assert(is_same_type<typeof_t<int&>, typeof_t<int&&>>,
            "Type mismatch. :(");

        static_assert(!is_same_type<int, char>, "Bad type match. :(");
        static_assert(!is_same_type<typeof_t<int>, char>, "Bad type match. :(");
        namespace {
            struct char_s { char c; };
            static_assert(!is_same_type<char_s, char>,
                "Bad type match. :(");
            static_assert(is_same_type<typeof_t<decltype(char_s().c)>, char>,
                "Type mismatch. :(");
        }
    }

}

#endif
#endif
