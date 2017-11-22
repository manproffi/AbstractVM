//
// Created by Serhii Protsenko on 11/22/17.
//

#include <sstream>
#include "Int16.hpp"
#include "ClassFactoryMethod.hpp"


const char* Int16::OverflowException::what() const throw()
{
	return ("overflow Int16");
}

const char* Int16::UnderflowException::what() const throw()
{
	return ("underflow Int16");
}

const char* Int16::IncorrectInputException::what() const throw()
{
	return ("\n****** Incorrect input data Int16\n");
}

Int16::Int16(short a) : _value(a), eType(eOperandType::Int16)
{
	std::stringstream ss;

	ss << static_cast<int>(a);
	data = ss.str();
}

Int16::Int16(std::string const &value) : eType(eOperandType::Int16) {

	try {

		int a = std::stoi(value);

		if (a >= std::numeric_limits<short>::min() && a <= std::numeric_limits<short>::max())
			_value = static_cast<short>(std::stoi(value));
		else
			throw Int16::IncorrectInputException();
		data = std::to_string(a);
	}
	catch (Int16::IncorrectInputException &e)
	{
		std::cout << e.what() << std::endl;
		exit(0);
	}
	catch (std::invalid_argument &inv_a)
	{
		std::cout << "Incorrect data " << inv_a.what() << std::endl;
		exit(0);
	}
	catch (std::out_of_range &range)
	{
		std::cout  << "Incorrect data " << range.what() << std::endl;
		exit(0);
	}
}

Int16::Int16() {}

Int16::~Int16() {}

short			Int16::getValue() const { return _value; }

int 			Int16::getPrecision(void) const { return eOperandType::Int16; }

eOperandType 	Int16::getType(void) const { return eType; }



IOperand const * Int16::operator + (IOperand const & rhs) const
{
	std::cout << "=========== Int16 operator+ START" << std::endl;
	eOperandType 	type;
	IOperand const	*newObj = nullptr;
	FactoryMethod	factoryMethod;

	type = getType() > rhs.getType() ? getType() : rhs.getType();

	if (type == getType())
	{
		std::cout << "=========== Int16 operator+ Short " << std::endl;
		if ( _value > 0 && dynamic_cast<Int16 const &>(rhs).getValue() > std::numeric_limits<short>::max() - _value)
			throw Int16::OverflowException();

		if (_value < 0 && dynamic_cast<Int16 const &>(rhs).getValue() <  std::numeric_limits<short>::min() - _value)
			throw Int16::UnderflowException();

		newObj = new Int16(_value + dynamic_cast<Int16 const &>(rhs).getValue());

		return newObj;
	}
	else
	{
		std::cout << "=========== Int16 operator+ Any" << std::endl;
		newObj = factoryMethod.createOperand(type, data);

		newObj = *newObj + rhs;
		return newObj;
	}

}

std::string const &		Int16::toString(void) const { return data; }
