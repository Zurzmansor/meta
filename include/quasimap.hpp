/**
 * @brief
 * 
 * @author Daniil Smirnov
 *
 */

#ifndef META_QUASIMAP_HPP
#define META_QUASIMAP_HPP

#include "commons.hpp"

BEGIN_META_NS

namespace details {
template<typename T, std::size_t I>
struct quasimapnode
{
    T v{};
};
} // details::

template <typename T, std::size_t ... Is>
struct quasimap : details::quasimapnode<T, Is> ...
{
    template <std::size_t I>
    T& get()
    {
        return details::quasimapnode<T, I>::v;
    };

    template <std::size_t I>
    const T& get() const
    {
        return details::quasimapnode<T, I>::v;
    };
};

END_META_NS

#endif //META_QUASIMAP_HPP
