#include <iostream>
#include <limits.h>

class Int8 : public IOperand
{

private:
	char			_value;
	eOperandType	eType;

	Int8();
	Int8 (Int8 const & rhs);
	Int8 operator= (Int8 const & rhs);

public:
	class OverflowException(): public std::exception
	{
	public:
		const char* what() const throw();
	};

	class UnderflowException(): public std::exception
	{
	public:
		const char* what() const throw();
	};


	explicit Int8(char a);
	~Int8();

	char			getValue(void) const;

	int 			getPrecision(void) const;
	eOperandType 	getType(void) const;

	IOperand const * operator + (IOperand const & rhs) const;
	// IOperand const * operator - (IOperand const & rhs) const;
	// IOperand const * operator * (IOperand const & rhs) const;
	// IOperand const * operator / (IOperand const & rhs) const;
	// IOperand const * operator % (IOperand const & rhs) const;

	std::string const & toString(void) const;

};

const char* Int8::OverflowException::what() const throw()
{
    return ("overflow Int8");  
}

const char* Int8::UnderflowException::what() const throw()
{
    return ("underflow Int8");  
}

Int8::Int8(char a) : _value(a), eType(Int8) {}

Int8::~Int8() {}

char			Int8::getValue(void) const { return _value; }

int 	Int8::getPrecision(void) const { return eOperandType::Int8; }

eOperandType Int8::getType(void) const { return eType; }

IOperand const * Int8::operator + (IOperand const & rhs) const
{
	// int_type a = 12356, b = 98765432;
	// if ( b > 0 && a > std::numeric_limits< int_type >::max() - b )
	//     throw std::range_error( "adding a and b would cause overflow" );

	// if ( b < 0 && a < std::numeric_limits< int_type >::min() - b )
	//     throw std::range_error( "adding a and b would cause underflow" );

	// int_type c = a + b;

/*	if (this->getType() == rhs.getType())
	{
		if ( _value > 0 && rhs.getValue() > std::numeric_limits<char>::max() - _value)
			throw Int8::OverflowException(); 

		if (_value < 0 && rhs.getValue() <  std::numeric_limits<char>::min() - _value)
			throw Int8::UnderflowException();

		return new Int8(_value + rhs.getValue());
	}
	else if (this->getType() < rhs.getType())
	{
		;
	}*/


	eOperandType 	type;
	IOperand		*newObj = nullptr;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	
	if (type == getType())
	{
		if ( _value > 0 && rhs.getValue() > std::numeric_limits<char>::max() - _value)
			throw Int8::OverflowException(); 

		if (_value < 0 && rhs.getValue() <  std::numeric_limits<char>::min() - _value)
			throw Int8::UnderflowException();
		
		newObj = new Int8(_value + rhs.getValue());
		
		return newObj;
	}
	else
	{
		newObj = FactoryMethod.createOperand(type, std::to_string(static_cast<int>(getValue())));
		newObj = newObj + rhs;
		std::cout << "=========== Int8 operator+ " << std::endl;
		return newObj;
	}

}