#include <cmath>
#include "metalivecode/nontemplates/MathStrategy.h"

namespace metalivecode::nontemplates {

/// @section MathStrategy Definitions

/// @brief 
/// @param op_str 
MathStrategy::MathStrategy(const char * algo_name, const char * op_str)
    : algo_name(algo_name),
      op_str(op_str)
{
}

/// @brief 
/// @return 
const char * MathStrategy::get_name() const
{
    return this->algo_name;
}

/// @brief 
/// @return 
const char * MathStrategy::get_op() const
{
    return this->op_str;
}

} // namespace metalivecode::nontemplates
