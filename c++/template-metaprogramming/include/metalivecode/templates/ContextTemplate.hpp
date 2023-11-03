#ifndef METALIVECODE_TEMPLATES_CONTEXTTEMPLATE_HPP
#define METALIVECODE_TEMPLATES_CONTEXTTEMPLATE_HPP

#include <cstdio>
#include <memory>
#include <stdexcept>
#include "metalivecode/templates/StrategyTemplate.hpp"

namespace metalivecode::templates {

/// @brief 
/// @tparam TReturn 
/// @tparam ...TArgs 
template <typename TReturn, typename... TArgs>
class ContextTemplate {
public:
    /// @brief 
    using StrategyPtr = std::shared_ptr<StrategyTemplate<TReturn, TArgs...>>;

    /// @brief 
    /// @param strategy 
    ContextTemplate(StrategyPtr strategy) : strategy(strategy)
    {
        if (!strategy)
            throw std::logic_error("Strategy pointer cannot be null");
    }

    /// @brief 
    /// @param ...args 
    /// @return 
    TReturn execute(TArgs... args) const
    {
        std::printf("Running strategy %s...\n", this->strategy->get_name());
        return this->strategy->algorithm(std::forward<TArgs>(args)...);
    }

    /// @brief 
    /// @return 
    const StrategyPtr get_strategy() const
    {
        return this->strategy;
    }

    /// @brief 
    /// @param strategy 
    void set_strategy(StrategyPtr strategy)
    {
        if (!strategy)
            throw std::logic_error("Strategy pointer cannot be null");
        
        this->strategy = strategy;
    }

protected:
    /// @brief 
    StrategyPtr strategy;
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_CONTEXTTEMPLATE_HPP
