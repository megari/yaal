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

    }

}

#endif
#endif
