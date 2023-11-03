#ifndef METALIVECODE_NONTEMPLATES_MATHSTRATEGY_HPP
#define METALIVECODE_NONTEMPLATES_MATHSTRATEGY_HPP

namespace metalivecode::nontemplates {

/// @brief 
class MathStrategy {
public:
	/// @brief 
	/// @param a 
	/// @param b 
	/// @return 
	virtual int algorithm(const int a, const int b) const = 0;

    /// @brief 
    /// @return 
    const char * get_name() const;

    /// @brief 
    /// @return 
    const char * get_op() const;

protected:
    /// @brief 
    /// @param algo_name 
    /// @param op_str 
    MathStrategy(const char * algo_name, const char * op_str);

    /// @brief 
    const char * algo_name, * op_str;
};

} // namespace metalivecode::nontemplates

#endif // METALIVECODE_NONTEMPLATES_MATHSTRATEGY_HPP


