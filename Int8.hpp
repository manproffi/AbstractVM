//
// Created by Serhii Protsenko on 11/20/17.
//

#ifndef ABSTRACTVM_INT8_HPP
#define ABSTRACTVM_INT8_HPP


#include "ClassIOperand.hpp"


class Int8 : public IOperand
{

private:
	char			_value;
	eOperandType	eType;

	Int8();
	Int8 (Int8 const & rhs);
	Int8 operator= (Int8 const & rhs);

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


	explicit Int8(char a);
	~Int8();

	char				getValue() const;

	int 			getPrecision(void) const;
	eOperandType 	getType(void) const;

	IOperand const * operator + (IOperand const & rhs) const;
	// IOperand const * operator - (IOperand const & rhs) const;
	// IOperand const * operator * (IOperand const & rhs) const;
	// IOperand const * operator / (IOperand const & rhs) const;
	// IOperand const * operator % (IOperand const & rhs) const;

	 std::string const & toString(void) const;

};


#endif //ABSTRACTVM_INT8_HPP
