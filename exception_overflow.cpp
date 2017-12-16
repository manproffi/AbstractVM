#pragma STDC FENV_ACCESS on
#include <iostream>
#include <cfenv>
#include <cmath>
#include <float.h>


int		main(int argc, char const *argv[])
{
	std::feclearexcept(FE_ALL_EXCEPT);
	float z = 12345678901234567890123456789012345678.f * 100;
	std::cout << FLT_MAX << std::endl;
	if (std::fetestexcept(FE_OVERFLOW))
		std::cout << "Overflow" << std::endl;
	else if (std::fetestexcept(FE_DIVBYZERO))
		std::cout << "div zero" << std::endl;
	else if (std::fetestexcept(FE_UNDERFLOW))
		std::cout << "div zero" << std::endl;
	else
	{

		std::cout << "OK" << std::endl;
		std::cout << z << std::endl;
	}
	std::cout << z << std::endl;
	return 0;
}