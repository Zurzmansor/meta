/**
 * @brief
 * 
 * @author Daniil Smirnov
 *
 */

#ifndef META_AND_HPP
#define META_AND_HPP

#include <type_traits>
#include "commons.hpp"

BEGIN_META_NS

namespace details {

template<bool ...>
struct bool_pack;

} // details::

template<bool ... Bs>
using static_and = std::is_same<details::bool_pack<Bs ..., true>,
                                details::bool_pack<true, Bs ...>>;


/* ----------------8<---------[ cut here ]----------------------------------- */

template <bool ... Args>
struct static_or;

template <bool ... Args>
struct static_or<true, Args ...> : std::true_type
{ };

template <bool ... Args>
struct static_or<false, Args ...> : static_or<Args ...>
{ };

template <>
struct static_or<> : std::false_type
{ };

END_META_NS

#endif //META_AND_HPP
