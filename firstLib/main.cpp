#include <iostream>
#include "libProst.h"

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "Usage: func(1/2) ∂x or 2*∂x" << std::endl;
	}
	else if (std::atoi(argv[1]) == 1)
	{
		std::cout << "First way to find derivative. Result: " << firstWayToFindDerivative(std::atof(argv[2]), std::atof(argv[3])) << "\n";
	}
	else if (std::atol(argv[1]) == 2)
	{
		std::cout << "Second way to find derivative. Result: " << secondWayToFindDerivative(std::atof(argv[2]), std::atof(argv[3])) << "\n";
	}
	else
	{
		std::cout << "Unknown command"
							<< "\n";
	}
}