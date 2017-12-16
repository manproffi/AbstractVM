//
// Created by Serhii Protsenko on 11/23/17.
//

#ifndef ABSTRACTVM_OPERAND_HPP
#define ABSTRACTVM_OPERAND_HPP


#include "ClassIOperand.hpp"
#include "ClassFactoryMethod.hpp"
#include <cfloat>


class Operand : public IOperand {

private:

	static FactoryMethod	FACTORY_METHOD;
	static const t_type		LIMITS;

	eOperandType 			_eType;
	std::string 			_data;
	Operand();
	Operand & operator= (Operand const & rhs);
	Operand(Operand const & rhs);

public:
	explicit Operand(const std::string &data);
	Operand(eOperandType eType, const std::string &data);


	~Operand() override;

	IOperand const * operator + (IOperand const & rhs) const override;
	IOperand const * operator - (IOperand const & rhs) const override;
	IOperand const * operator * (IOperand const & rhs) const override;
	IOperand const * operator / (IOperand const & rhs) const override;
	IOperand const * operator % (IOperand const & rhs) const override;

	int 			getPrecision(void) const override;
	eOperandType 	getType(void) const override;

	std::string const & toString(void) const override;

	class OverflowException_res: public std::exception
	{
	public:
		const char* what() const throw();
	};

	class UnderflowException_res: public std::exception
	{
	public:
		const char* what() const throw();
	};
	class OverflowException_val: public std::exception
	{
	public:
		const char* what() const throw();
	};

	class UnderflowException_val: public std::exception
	{
	public:
		const char* what() const throw();
	};

};


#endif //ABSTRACTVM_OPERAND_HPP
