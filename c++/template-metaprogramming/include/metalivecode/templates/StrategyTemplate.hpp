#ifndef METALIVECODE_TEMPLATES_STRATEGYTEMPLATE_HPP
#define METALIVECODE_TEMPLATES_STRATEGYTEMPLATE_HPP

namespace metalivecode::templates {

/// @brief 
/// @tparam TReturn 
/// @tparam ...Args 
template <typename TReturn, typename... TArgs>
class StrategyTemplate {
public:
    /// @brief 
    /// @param name 
    StrategyTemplate(const char * name) : name(name) { }
    
    /// @brief 
    /// @param ...args 
    /// @return 
    virtual TReturn algorithm(TArgs&&... args) const = 0;

    /// @brief 
    /// @return 
    const char * get_name() const
    {
        return this->name;
    }

protected:
    /// @brief 
    const char * name;
};

} // namespace metalivecode::templates

#endif // METALIVECODE_TEMPLATES_STRATEGYTEMPLATE_HPP
