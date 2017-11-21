#include <iostream>
#include "ClassIOperand.hpp"
#include "ClassFactoryMethod.hpp"

int main() {
//	std::cout << "Hello, World!" << std::endl;

	IOperand const	* a;
	IOperand const	* b;
//	IOperand const	* c;


	FactoryMethod	factoryMethod;
	try {
		a = factoryMethod.createOperand(Int8, "42");
		b = factoryMethod.createOperand(Int8, "jh");
		std::cout << (*a + *b)->toString() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}





	return 0;
}