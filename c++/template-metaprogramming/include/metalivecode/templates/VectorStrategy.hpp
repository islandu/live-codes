#ifndef METALIVECODE_TEMPLATES_VECTORSTRATEGY_HPP
#define METALIVECODE_TEMPLATES_VECTORSTRATEGY_HPP

#include <vector>
#include "metalivecode/templates/StrategyTemplate.hpp"

namespace metalivecode::templates {

/// @brief 
/// @tparam T 
template <typename T>
struct VectorStrategy : StrategyTemplate<void, std::vector<T>&> {
	/// @brief 
	/// @param name 
	VectorStrategy(const char * name)
		: StrategyTemplate<void, std::vector<T>&>(name)
	{
	}
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_VECTORSTRATEGY_HPP
