#ifndef METALIVECODE_NONTEMPLATES_POWER_HPP
#define METALIVECODE_NONTEMPLATES_POWER_HPP

#include "metalivecode/nontemplates/MathStrategy.h"

namespace metalivecode::nontemplates {

/// @brief 
struct Power final : public MathStrategy {
    /// @brief 
    Power();

    /// @brief 
    /// @param a 
    /// @param b 
    /// @return 
    int algorithm(const int a, const int b) const override;
};

} // namespace metalivecode::nontemplates

#endif // METALIVECODE_NONTEMPLATES_POWER_HPP
