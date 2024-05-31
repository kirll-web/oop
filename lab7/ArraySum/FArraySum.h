#pragma once
#include <vector>
#include <iostream>

template <typename T>
T ArraySum(std::vector<T> const& arr)
{
	T sum = T();

	if (arr.empty()) sum;

	for (const auto& element : arr) {
		sum += element;
	}

	return sum;
}