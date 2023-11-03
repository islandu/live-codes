#ifndef METALIVECODE_TEMPLATES_VECTORCONTEXT_HPP
#define METALIVECODE_TEMPLATES_VECTORCONTEXT_HPP

#include "metalivecode/templates/ContextTemplate.hpp"
#include "metalivecode/templates/VectorStrategy.hpp"

namespace metalivecode::templates {

/// @brief 
/// @tparam T 
template <typename T>
struct VectorContext : ContextTemplate<void, std::vector<T>&> {
	/// @brief 
	/// @param strategy 
	VectorContext(std::shared_ptr<VectorStrategy<T>> strategy)
		: ContextTemplate<void, std::vector<T>&>(strategy)
	
	{
	}
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_VECTORCONTEXT_HPP
