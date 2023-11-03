#ifndef METALIVECODE_TEMPLATES_SORTSTRATEGY_HPP
#define METALIVECODE_TEMPLATES_SORTSTRATEGY_HPP

#include <algorithm>
#include "metalivecode/templates/VectorStrategy.hpp"

namespace metalivecode::templates {

/// @brief
/// @tparam T
template <typename T>
class SortStrategy : public VectorStrategy<T> {
public:
	/// @brief
	SortStrategy(const bool descending = false)
		: VectorStrategy<T>("SortStrategy"), descending(descending)
	{
	}

	/// @brief
	/// @param vector
	void algorithm(std::vector<T> &vector) const override
	{
		if (descending)
			std::sort(vector.begin(), vector.end(), std::greater<T>());
		else
			std::sort(vector.begin(), vector.end());
	}

private:
	const bool descending;
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_SORTSTRATEGY_HPP
