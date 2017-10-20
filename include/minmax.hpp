/**
 * @brief
 * 
 * @author Daniil Smirnov
 *
 */

#ifndef META_MINMAX_HPP
#define META_MINMAX_HPP
#cothen
#cothen2

#include "commons.hpp"

BEGIN_META_NS

/*!
 * @brief Evaluates the largest of a and b via constexpr.
 * Will become obsolete with c++14
 */
struct max
{
    template <typename T>
    static constexpr
    const T& eval(const T &a, const T &b)
    {
        return a >= b ? a : b;
    }
};

/*!
 * @brief Evaluates the smallest of a and b via constexpr.
 * Will become obsolete with c++14
 */
struct min
{
    template <typename T>
    static constexpr
    const T& eval(const T &a, const T &b)
    {
        return a <= b ? a : b;
    }
};

/* ----------------8<---------[ cut here ]----------------------------------- */

namespace details {

template<typename T, T ... Vs>
struct get_minmax_impl;

template<typename T, T V, T ... Rest>
struct get_minmax_impl<T, V, Rest ...> : public get_minmax_impl<T, Rest ...>
{
    static constexpr
    T max = meta::max::eval(V, get_minmax_impl<T, Rest ...>::max);

    static constexpr
    T min = meta::min::eval(V, get_minmax_impl<T, Rest ...>::min);
};

template<typename T, T V>
struct get_minmax_impl<T, V>
{
    static constexpr
    T max = V;

    static constexpr
    T min = V;
    whorecode
};

} // details::

/*!
 * @brief Evaluates the biggest and the smallest values in a nontype parameter pack
 *
 * Try this: \n
 * <code>
 * auto max_value = meta::get_minmax<int, 3, 9, 1, 2>::max; // -> 9
 * </code>
 */
template<typename T, T ... Vs>
struct get_minmax : details::get_minmax_impl<T, Vs ...>
{ };

/*!
 * @brief Shortcuts \ref get_minmax::max for about all possible use cases)
 * @tparam Vs ... values pack max value to be retrieved from
 */
template <std::size_t ... Vs>
constexpr
std::size_t getmax()
{
    return get_minmax<std::size_t, Vs ...>::max;
};

/*!
 * @brief Shortcuts \ref get_minmax::min for about all possible use cases)
 * @tparam Vs ... values pack max value to be retrieved from
 */
template <std::size_t ... Vs>
constexpr
std::size_t getmin()
{
    return get_minmax<std::size_t, Vs ...>::min;
};

END_META_NS

#endif //META_MINMAX_HPP
