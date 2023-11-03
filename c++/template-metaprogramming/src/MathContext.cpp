#include <cstdio>
#include <stdexcept>
#include "metalivecode/nontemplates/MathStrategy.h"
#include "metalivecode/nontemplates/MathContext.h"

namespace metalivecode::nontemplates {

/// @brief 
/// @param strategy 
MathContext::MathContext(std::shared_ptr<MathStrategy> strategy) : strategy(strategy)
{
    if (!this->strategy)
        throw std::runtime_error("MathStrategy pointer cannot be null");
}

/// @brief 
/// @param a 
/// @param b 
/// @param explain 
/// @return 
int MathContext::do_math(const int a, const int b, const bool explain) const
{
    int result;

    std::printf("Strategy currently set to '%s'\n", this->get_strategy()->get_name());
    std::printf("Inputs: a=%d b=%d\n", a, b);
    result = this->strategy->algorithm(a, b);

    if (explain)
        explain_math(a, b, result);
    
    return result;
}

/// @brief 
/// @return 
const std::shared_ptr<MathStrategy> MathContext::get_strategy() const
{
    return this->strategy;
}

void MathContext::set_strategy(std::shared_ptr<MathStrategy> strategy)
{
    if (!strategy)
        throw std::runtime_error("MathStrategy pointer cannot be null");
    
    this->strategy = strategy;
}

/// @brief 
/// @param a 
/// @param b 
/// @param result 
void MathContext::explain_math(const int a, const int b, const int result) const
{
    const char * op = this->strategy->get_op(); 
    std::fprintf(stderr, "Explanation: %d %s %d = %d\n", a, op, b, result);
}

} // namespace metalivecode::nontemplates
