//
// Created by Serhii Protsenko on 11/20/17.
//

#include "ClassFactoryMethod.hpp"
#include "Int8.hpp"
#include "Int16.hpp"

#include <stdexcept>




IOperand const * FactoryMethod::createOperand(eOperandType type, std::string const &value) const {

	typedef IOperand const * (FactoryMethod::*myFunType)(std::string const & value) const;

	myFunType myArray[5];

	myArray[eOperandType::Int8] = &FactoryMethod::createInt8;
	myArray[eOperandType::Int16] = &FactoryMethod::createInt16;
//	myArray[eOperandType::Int32] = &FactoryMethod::createInt32;
//	myArray[eOperandType::Float] = &FactoryMethod::createFloat;
//	myArray[eOperandType::Double] = &FactoryMethod::createDouble;

	return dynamic_cast<const IOperand *>((this->*myArray[type])(value));

}


IOperand const * FactoryMethod::createInt8(std::string const &value) const {

	std::cout << "======  Create Int8" << std::endl;
	return new class Int8(value);
}

IOperand const * FactoryMethod::createInt16(std::string const &value) const {

	std::cout << "======  Create Int16" << std::endl;
	return new class Int16(value);
}
