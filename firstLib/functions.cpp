#include "libProst.h"
#include <vector>
#include "cmath"

float firstWayToFindDerivative(float a, float deltaX)
{
	return (cos(a + deltaX) - cos(a)) / deltaX;
}

float secondWayToFindDerivative(float a, float deltaX)
{
	return (cos(a + deltaX) - cos(a - deltaX)) / (2 * deltaX);
}