#ifndef METALIVECODE_NONTEMPLATES_MULTIPLY_HPP
#define METALIVECODE_NONTEMPLATES_MULTIPLY_HPP

#include "metalivecode/nontemplates/MathStrategy.h"

namespace metalivecode::nontemplates {

/// @brief 
struct Multiply final : public MathStrategy {
    /// @brief 
    Multiply();

    /// @brief 
    /// @param a 
    /// @param b 
    /// @return 
    int algorithm(const int a, const int b) const override;
};

} // namespace metalivecode::nontemplates

#endif // METALIVECODE_NONTEMPLATES_MULTIPLY_HPP
