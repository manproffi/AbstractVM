//
// Created by Serhii Protsenko on 11/20/17.
//

#include <sstream>
#include "Int8.hpp"
#include "ClassFactoryMethod.hpp"


const char* Int8::OverflowException::what() const throw()
{
    return ("overflow Int8");  
}

const char* Int8::UnderflowException::what() const throw()
{
    return ("underflow Int8");  
}

const char* Int8::IncorrectInputException::what() const throw()
{
	return ("\n****** Incorrect input data Int8\n");
}

Int8::Int8(char a) : _value(a), eType(eOperandType::Int8) {}

Int8::Int8() {}

Int8::~Int8() {}

char			Int8::getValue() const { return _value; }

int 			Int8::getPrecision(void) const { return eOperandType::Int8; }

eOperandType 	Int8::getType(void) const { return eType; }



IOperand const * Int8::operator + (IOperand const & rhs) const
{
	std::cout << "=========== Int8 operator+ START" << std::endl;
	eOperandType 	type;
	IOperand const	*newObj = nullptr;
	FactoryMethod	factoryMethod;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	
	if (type == getType())
	{
		std::cout << "=========== Int8 operator+ Char " << std::endl;
		if ( _value > 0 && dynamic_cast<Int8 const &>(rhs).getValue() > std::numeric_limits<char>::max() - _value)
			throw Int8::OverflowException(); 

		if (_value < 0 && dynamic_cast<Int8 const &>(rhs).getValue() <  std::numeric_limits<char>::min() - _value)
			throw Int8::UnderflowException();
		
		newObj = new Int8(_value + dynamic_cast<Int8 const &>(rhs).getValue());
		
		return newObj;
	}
	else
	{
		std::cout << "=========== Int8 operator+ Any" << std::endl;
		
		newObj = factoryMethod.createOperand(type, std::to_string(static_cast<int>(getValue())));


//		newObj = newObj + rhs;
		return newObj;
	}

}

std::string const &		Int8::toString(void) const {

	std::stringstream ss;

	ss << static_cast<int>(_value);

	return ss.str();
}
