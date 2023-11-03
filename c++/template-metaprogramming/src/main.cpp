#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "metalivecode/nontemplates/MathContext.h"
#include "metalivecode/nontemplates/MathStrategy.h"
#include "metalivecode/nontemplates/Multiply.h"
#include "metalivecode/nontemplates/Power.h"
#include "metalivecode/templates/VectorContext.hpp"
#include "metalivecode/templates/VectorStrategy.hpp"
#include "metalivecode/templates/TakeStrategy.hpp"
#include "metalivecode/templates/SkipStrategy.hpp"
#include "metalivecode/templates/SortStrategy.hpp"
#include "metalivecode/templates/print_vector.hpp"

using metalivecode::nontemplates::MathContext;
using metalivecode::nontemplates::MathStrategy;
using metalivecode::nontemplates::Multiply;
using metalivecode::nontemplates::Power;
using metalivecode::templates::VectorContext;
using metalivecode::templates::VectorStrategy;
using metalivecode::templates::TakeStrategy;
using metalivecode::templates::SkipStrategy;
using metalivecode::templates::SortStrategy;
using metalivecode::templates::print_vector;

int main(void)
{
	// Algorithm input
	std::vector<std::string> illest_and_chillest {
		"x86_64ASM", "Rust", "C", "C++"
	};

	// Shared pointer to algorithm instance
	auto strategy = std::make_shared<SortStrategy<std::string>>();

	// Context constructed with sort algorithm
	VectorContext<std::string> context(strategy);

	std::printf("Original data: ");
	print_vector(illest_and_chillest);

	// Run algorithm
	context.execute(illest_and_chillest);

	// Display result
	std::printf("Altered data: ");
	print_vector(illest_and_chillest);

	// Substitute strategy
	context.set_strategy(std::make_shared<TakeStrategy<std::string, 2>>());

	// Run algorithm
	context.execute(illest_and_chillest);

	// Display result
	std::printf("Altered data: ");
	print_vector(illest_and_chillest);

	// Substitute strategy again
	context.set_strategy(std::make_shared<SkipStrategy<std::string, 1>>());

	// Run algorithm
	context.execute(illest_and_chillest);

	// Display result
	std::printf("Altered data: ");
	print_vector(illest_and_chillest);

	return 0;
}

// Non-template strategy pattern
int main_basic_strategy_pattern(void)
{
	int result;

	std::puts("Constructing MathContext object...\n");
	MathContext context(std::make_shared<Multiply>());

	result = context.do_math(12, 37, true);
	std::printf("Result: %d\n\n", result);

	std::puts("Substituting strategy...\n");
	context.set_strategy(std::make_shared<Power>());

	result = context.do_math(2, 8, true);
	std::printf("Result: %d\n", result);

	return 0;
}
