#ifndef METALIVECODE_TEMPLATES_PRINTVECTOR_HPP
#define METALIVECODE_TEMPLATES_PRINTVECTOR_HPP

#include <vector>

namespace metalivecode::templates {

/// @brief 
/// @tparam T 
/// @param v 
template <typename T>
void print_vector(const std::vector<T>& v)
{
	for (auto x : v)
		std::cout << x << ", ";
	
	std::cout << "\b\b \b" << std::endl;
}

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_PRINTVECTOR_HPP
