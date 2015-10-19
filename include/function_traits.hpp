/**
 * @brief
 * 
 * @author Daniil Smirnov
 *
 */

#ifndef META_FUNCTION_TRAITS_HPP
#define META_FUNCTION_TRAITS_HPP

#include <tuple>
#include "commons.hpp"

BEGIN_META_NS

template<class F>
struct function_traits;
 
// function pointer
template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)>
{};
 
template<class R, class... Args>
struct function_traits<R(Args...)>
{
    using return_type = R;
    using args = std::tuple<Args...>;
    
    static constexpr std::size_t arity = sizeof...(Args);
 
    template <std::size_t N>
    struct arg
    {
        static_assert(N < arity, "EPIC INDEX FAIL");
        using type = typename std::tuple_element<N,std::tuple<Args...>>::type;
    };
};

// member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...)> : public function_traits<R(Args...)>
{};

// const member function pointer
template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...) const> : public function_traits<R(Args...)>
{};

// functor
template<class F>
struct function_traits
{
    private:
        using call_type = function_traits<decltype(&F::operator())>;
    public:
        using return_type = typename call_type::return_type;
        using args = typename call_type::args;
        static constexpr std::size_t arity = call_type::arity;
 
        template <std::size_t N>
        struct arg
        {
            static_assert(N < arity, "EPIC INDEX FAIL");
            using type = typename call_type::template arg<N>::type;
        };
};

/* ----------------8<---------[ cut here ]----------------------------------- */

template<typename T>
struct is_callable {
private:
    typedef char(&yes)[1];
    typedef char(&no)[2];

    struct fallback { void operator()(); };
    struct derived : T, fallback { };

    template<typename U, U> struct Check;

    template<typename>
    static yes test(...);

    template<typename C>
    static no test(check<void (fallback::*)(), &C::operator()>*);

public:
    static const bool value = sizeof(test<derived>(0)) == sizeof(yes);
};

END_META_NS

#endif //META_FUNCTION_TRAITS_HPP
