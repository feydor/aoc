/* aoc.hpp - useful functions for aoc */
#pragma once
#include <string>
#include <ranges>
#include <vector>

namespace aoc {
/* split a string into tokens using an optional delimiter */
std::vector<std::string_view> split(std::string_view s, char delimiter = ' ') {
	std::vector<std::string_view> result;
	auto split = s
		| std::ranges::views::split(delimiter)
		| std::ranges::views::transform([](auto&& str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); });
	for (const auto word : split)
		result.push_back(word);
	return result;
}

}
