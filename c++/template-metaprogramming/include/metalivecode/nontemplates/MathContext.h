#ifndef METALIVECODE_NONTEMPLATES_MATHCONTEXT_HPP
#define METALIVECODE_NONTEMPLATES_MATHCONTEXT_HPP

#include <memory>
#include "metalivecode/nontemplates/MathStrategy.h"

namespace metalivecode::nontemplates {

class MathContext {
public:
	/// @brief 
	/// @param strategy 
	MathContext(std::shared_ptr<MathStrategy> strategy);

	/// @brief 
	/// @param a 
	/// @param b 
	/// @param explain 
	/// @return 
	int do_math(const int a, const int b, const bool explain = false) const;

	/// @brief 
	/// @return 
	const std::shared_ptr<MathStrategy> get_strategy() const;

	/// @brief 
	/// @param strategy 
	void set_strategy(std::shared_ptr<MathStrategy> strategy);

protected:
	/// @brief 
	/// @param a 
	/// @param b 
	/// @param result 
	inline void explain_math(const int a, const int b, const int result) const;

	/// @brief 
	std::shared_ptr<MathStrategy> strategy;
};

} // namespace metalivecode::nontemplates

#endif // METALIVECODE_NONTEMPLATES_MATHCONTEXT_HPP
