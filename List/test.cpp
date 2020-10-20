#include <iostream>
#include <string>
#include "List.h"

int main()
{
	List<std::string> list;
	for (int i = 0; i < 10; ++i)
		list.push_back(std::to_string(i));
	for (const auto& x : list)
		std::cout << x << " ";
	std::cout << std::endl;

	for (int i = 0; i < 10; ++i)
		list.push_back(std::string(i + 1, '*'));

	for (const auto& x : list)
		std::cout << x << "\n";

	return 0;
}