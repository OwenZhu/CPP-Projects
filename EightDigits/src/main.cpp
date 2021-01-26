#include <iostream>
#include <array>

#include "a_star.h"


int main()
{
	//std::array<int, 9> digits = { 3, 1, 2, 0, 4, 5, 6, 7, 8 };
	std::array<int, 9> digits = { 4, 0, 1, 2, 5, 8, 7, 6, 3 };
	//std::array<int, 9> digits = { 3, 0, 2, 4, 1, 5, 6, 7, 8 };
	
	AStarAlgorithm(digits).Run();
	
	std::cin.get();
	return 0;
}
