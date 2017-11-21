#include <iostream>
#include <limits.h>

class Int16 : public IOperand
{

private:
	short			_value;
	eOperandType	eType;

	Int16();
	Int16 (Int16 const & rhs);
	Int16 operator= (Int16 const & rhs);

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


	explicit Int16(char a);
	~Int16();

	short			getValue(void) const;

	int 			getPrecision(void) const;
	eOperandType 	getType(void) const;

	IOperand const * operator + (IOperand const & rhs) const;
	// IOperand const * operator - (IOperand const & rhs) const;
	// IOperand const * operator * (IOperand const & rhs) const;
	// IOperand const * operator / (IOperand const & rhs) const;
	// IOperand const * operator % (IOperand const & rhs) const;

	std::string const & toString(void) const;

};

const char* Int16::OverflowException::what() const throw()
{
    return ("overflow Int16");  
}

const char* Int16::UnderflowException::what() const throw()
{
    return ("underflow Int16");  
}

Int16::Int16(char a) : _value(a), eType(Int16) {}

Int16::~Int16() {}

short			Int16::getValue(void) const { return _value; }

int 			Int16::getPrecision(void) const { return eOperandType::Int16; }

eOperandType 	Int16::getType(void) const { return eType; }

IOperand const * Int16::operator + (IOperand const & rhs) const
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

	std::cout << "=========== Int16 operator+ START" << std::endl;
	eOperandType 	type;
	IOperand		*newObj = nullptr;

	type = getType() > rhs.getType() ? getType() : rhs.getType();
	
	if (type == getType())
	{
		if ( _value > 0 && static_cast<short>(rhs.getValue()) > std::numeric_limits<short>::max() - _value)
			throw Int16::OverflowException(); 

		if (_value < 0 && static_cast<short>(rhs.getValue()) <  std::numeric_limits<short>::min() - _value)
			throw Int16::UnderflowException();
		
		newObj = new Int16(_value + static_cast<short>(rhs.getValue()));
		
		return newObj;
	}
	else
	{
		std::cout << "=========== Int16 operator+ " << std::endl;
		
		newObj = FactoryMethod.createOperand(type, std::to_string(static_cast<int>(getValue())));
		newObj = newObj + rhs;
		return newObj;
	}

}