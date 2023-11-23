#include "libProst.h"
#include <vector>
#include "cmath"

float firstWayToFindDerivative(float a, float deltaX)
{
	return (cos(a + deltaX) - cos(a)) / deltaX;
}

float secondWayToFindDerivative(float a, float deltaX)
{
	return (cos(a + deltaX) - cos(a - deltaX)) / 2 * deltaX;
}

int simple(int a, int b)
{
	int res = 0;
	for (int i = a; i <= b; ++i)
	{
		bool flag = 1;
		for (int d = 2; d < i; ++d)
		{
			if (i == 2)
			{
				break;
			}
			if (i % d == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			res += 1;
		}
	}
	return res;
}