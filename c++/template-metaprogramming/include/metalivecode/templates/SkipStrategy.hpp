#ifndef METALIVECODE_TEMPLATES_SKIPSTRATEGY_HPP
#define METALIVECODE_TEMPLATES_SKIPSTRATEGY_HPP

#include <algorithm>
#include <cstddef>
#include "metalivecode/templates/VectorStrategy.hpp"

namespace metalivecode::templates {

/// @brief
/// @tparam T
template <typename T, std::size_t N>
class SkipStrategy : public VectorStrategy<T> {
public:
	/// @brief
	SkipStrategy() : VectorStrategy<T>("SkipStrategy")
	{
	}

	/// @brief
	/// @param vector
	void algorithm(std::vector<T> &vector) const override
	{
		if (N >= vector.size())
		{
			vector.clear();
			return;
		}

		vector.erase(vector.begin(), vector.begin() + N);
	}
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_SKIPSTRATEGY_HPP
