#include "metalivecode/nontemplates/Multiply.h"

/// @brief Multiply Definitions

namespace metalivecode::nontemplates {

/// @brief 
Multiply::Multiply() : MathStrategy("Multiply", "*")
{
}

/// @brief 
/// @param a 
/// @param b 
/// @return 
int Multiply::algorithm(const int a, const int b) const
{
    return a * b;
}

} // namespace metalivecode::nontemplates
