//
// Created by Serhii Protsenko on 11/18/17.
//

#ifndef ABSTRACTVM_CLASSIOPERAND_HPP
#define ABSTRACTVM_CLASSIOPERAND_HPP

#include <iostream>

enum eOperandType { Int8, Int16, Int32, Float, Double };

typedef struct limits
{
	double max[5];
	double min[5];
}			t_type;

class IOperand {

public:
	virtual int 			getPrecision( void ) const = 0;
	virtual eOperandType 	getType( void ) const = 0;

	virtual	IOperand 	const * operator+(IOperand const & ref) const = 0;
	virtual	IOperand 	const * operator-(IOperand const & ref) const = 0;
	virtual	IOperand 	const * operator*(IOperand const & ref) const = 0;
	virtual	IOperand 	const * operator/(IOperand const & ref) const = 0;
	virtual	IOperand 	const * operator%(IOperand const & ref) const = 0;

	virtual std::string const & toString( void ) const = 0;

	virtual ~IOperand( void ) {}

};


#endif //ABSTRACTVM_CLASSIOPERAND_HPP

