//
// Created by Semyon Tikhonenko on 5/26/21.
// Copyright (c) 2021 Semyon Tikhonenko. All rights reserved.
//

#ifndef VOCALTRAINER_TYPETRAITS_H
#define VOCALTRAINER_TYPETRAITS_H

#include <type_traits>

#define GENERATE_HAS_METHOD_TYPE_TRAIT(methodName) \
 \
template<typename, typename T>  \
struct has_ ## methodName {  \
    static_assert(  \
            std::integral_constant<T, false>::value,  \
            "Second template parameter needs to be of function type.");  \
};  \
 \
 \
template<typename C, typename Ret, typename... Args>  \
struct has_ ## methodName<C, Ret(Args...)> {  \
private:  \
    template<typename T>  \
    static constexpr auto check(T*)  \
    -> typename  \
    std::is_same<  \
            decltype( std::declval<T>().methodName( std::declval<Args>()... ) ), \
            Ret \
    >::type;  \
\
    template<typename>  \
    static constexpr std::false_type check(...);  \
\
    typedef decltype(check<C>(0)) type;  \
\
public:  \
    static constexpr bool value = type::value;  \
};

namespace CppUtils {
    template<typename T>
    struct has_const_iterator
    {
    private:
        typedef char                      yes;
        typedef struct { char array[2]; } no;

        template<typename C> static yes test(typename C::const_iterator*);
        template<typename C> static no  test(...);
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(yes);
        typedef T type;
    };

    template <typename T>
    struct has_begin_end
    {
        template<typename C> static char (&f(typename std::enable_if<
                std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::begin)),
                typename C::const_iterator(C::*)() const>::value, void>::type*))[1];

        template<typename C> static char (&f(...))[2];

        template<typename C> static char (&g(typename std::enable_if<
                std::is_same<decltype(static_cast<typename C::const_iterator (C::*)() const>(&C::end)),
                typename C::const_iterator(C::*)() const>::value, void>::type*))[1];

        template<typename C> static char (&g(...))[2];

        static bool const beg_value = sizeof(f<T>(0)) == 1;
        static bool const end_value = sizeof(g<T>(0)) == 1;
    };

    template<typename T>
    struct is_container : std::integral_constant<bool, has_const_iterator<T>::value && has_begin_end<T>::beg_value && has_begin_end<T>::end_value>
    { };

    GENERATE_HAS_METHOD_TYPE_TRAIT(saveOrLoad)
}


#endif //VOCALTRAINER_TYPETRAITS_H
