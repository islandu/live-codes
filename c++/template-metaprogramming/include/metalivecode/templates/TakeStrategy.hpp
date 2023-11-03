#ifndef METALIVECODE_TEMPLATES_TAKESTRATEGY_HPP
#define METALIVECODE_TEMPLATES_TAKESTRATEGY_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include "metalivecode/templates/VectorStrategy.hpp"

namespace metalivecode::templates {

/// @brief
/// @tparam T
template <typename T, std::size_t N>
class TakeStrategy : public VectorStrategy<T> {
public:
	/// @brief
	TakeStrategy() : VectorStrategy<T>("TakeStrategy")
	{
	}

	/// @brief
	/// @param vector
	void algorithm(std::vector<T> &vector) const override
	{
		if (N >= vector.size())
			return;

		vector.resize(N);
	}
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_TAKESTRATEGY_HPP
