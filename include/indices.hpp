/**
 * @brief
 * 
 * @author Daniil Smirnov
 *
 */

#ifndef META_INDICES_HPP
#define META_INDICES_HPP

#include "commons.hpp"

BEGIN_META_NS

template <std::size_t ... Is>
struct indices {};

template <std::size_t N, std::size_t ... Is>
struct build_indices : build_indices<N-1, N-1, Is...>
{ };

template <std::size_t ... Is>
struct build_indices<0, Is...> : indices<Is...>
{ };

END_META_NS

#endif //META_INDICES_HPP
