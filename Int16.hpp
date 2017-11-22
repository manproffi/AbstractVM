//
// Created by Serhii Protsenko on 11/22/17.
//

#ifndef ABSTRACTVM_INT16_HPP
#define ABSTRACTVM_INT16_HPP


#include <string>
#include "ClassIOperand.hpp"

class Int16 : public IOperand
{

private:
	short			_value;
	eOperandType	eType;
	std::string 	data;

	Int16();
	Int16 (Int16 const & rhs);
	Int16 operator= (Int16 const & rhs);

public:

	class OverflowException: public std::exception
	{
	public:
		const char* what() const throw();
	};

	class UnderflowException: public std::exception
	{
	public:
		const char* what() const throw();
	};

	class IncorrectInputException: public std::exception
	{
	public:
		const char* what() const throw();
	};


	explicit Int16(short a);
	explicit Int16(std::string const & str);
	~Int16();

	short				getValue() const;

	int 			getPrecision(void) const;
	eOperandType 	getType(void) const;

	IOperand const * operator + (IOperand const & rhs) const;
	// IOperand const * operator - (IOperand const & rhs) const;
	// IOperand const * operator * (IOperand const & rhs) const;
	// IOperand const * operator / (IOperand const & rhs) const;
	// IOperand const * operator % (IOperand const & rhs) const;

	std::string const & toString(void) const;

};



#endif //ABSTRACTVM_INT16_HPP
