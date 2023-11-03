#include <cmath>
#include "metalivecode/nontemplates/Power.h"

/// @brief Multiply Definitions

namespace metalivecode::nontemplates {

/// @brief 
Power::Power() : MathStrategy("Power", "**")
{
}

/// @brief 
/// @param a 
/// @param b 
/// @return 
int Power::algorithm(const int a, const int b) const
{
    return (int)std::pow(a, b);
}

} // namespace metalivecode::nontemplates
