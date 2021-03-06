#ifndef TEXT_BOOST_CONTAINER_STATIC_VECTOR_HPP
#define TEXT_BOOST_CONTAINER_STATIC_VECTOR_HPP

#include <vector>

namespace boost {
namespace container {
template <typename T, size_t>
using static_vector = std::vector<T>;
}
}

#endif  // TEXT_BOOST_CONTAINER_STATIC_VECTOR_HPP

