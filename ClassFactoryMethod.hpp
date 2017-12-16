//
// Created by Serhii Protsenko on 11/20/17.
//

#ifndef ABSTRACTVM_CLASSFACTORYMETHOD_HPP
#define ABSTRACTVM_CLASSFACTORYMETHOD_HPP


#include "ClassIOperand.hpp"

class FactoryMethod {

private:

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	FactoryMethod(FactoryMethod const &);
	FactoryMethod &operator=(FactoryMethod const &);

public:
	~FactoryMethod();
	FactoryMethod();

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

};


#endif //ABSTRACTVM_CLASSFACTORYMETHOD_HPP
