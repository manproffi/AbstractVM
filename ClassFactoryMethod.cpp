//
// Created by Serhii Protsenko on 11/20/17.
//

#include "ClassFactoryMethod.hpp"
#include "Int8.hpp"
#include <stdexcept>




IOperand const * FactoryMethod::createOperand(eOperandType type, std::string const &value) const {

	typedef IOperand const * (FactoryMethod::*myFunType)(std::string const & value) const;

	myFunType myArray[5];

	myArray[eOperandType::Int8] = &FactoryMethod::createInt8;
//	myArray[eOperandType::Int16] = &FactoryMethod::createInt16;
//	myArray[eOperandType::Int32] = &FactoryMethod::createInt32;
//	myArray[eOperandType::Float] = &FactoryMethod::createFloat;
//	myArray[eOperandType::Double] = &FactoryMethod::createDouble;

	return dynamic_cast<const IOperand *>((this->*myArray[type])(value));

}


IOperand const * FactoryMethod::createInt8(std::string const &value) const {

	std::cout << "======  Create Int8" << std::endl;

	/************************/
	/* 	Validation 	*/
	/************************/

	IOperand	*newObj = nullptr;

//	try {
//		int a = stoi(value);
//	}
//	catch (std::exception &e)
//	{
//		std::cout << e.what() << std::endl;
//	}

	try {

		int a = stoi(value);
		if (a >= std::numeric_limits<char>::min() && a <= std::numeric_limits<char>::max())
			newObj = new class Int8(stoi(value));
		else
			throw Int8::IncorrectInputException();
	}
	catch (Int8::IncorrectInputException &e)
	{
		std::cout << e.what() << std::endl;
	}

	return newObj;
}
