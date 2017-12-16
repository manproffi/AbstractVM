//
// Created by Serhii Protsenko on 11/23/17.
//


#include "ClassOperand.hpp"
#include "ClassFactoryMethod.hpp"
#include "ClassIOperand.hpp"
#include <cfenv>


Operand::Operand() {}

Operand::Operand(const std::string &data) : _data(data) {}


Operand::Operand(eOperandType eType, const std::string &data) : _eType(eType), _data(data) {}

Operand::~Operand() {}

int Operand::getPrecision(void) const { return _eType; }

eOperandType Operand::getType(void) const { return _eType; }



std::string const &Operand::toString(void) const { return _data; }


IOperand const *Operand::operator+(IOperand const &rhs) const {

	eOperandType 	type;

	type = std::max(getType(), rhs.getType());

	if (type <=eOperandType::Int32)
	{
		auto res = std::stoll(_data) + std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else
	{
		auto res = std::stold(_data) + std::stold(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}

IOperand const *Operand::operator-(IOperand const &rhs) const {

	eOperandType 	type;

	type = std::max(getType(), rhs.getType());
	if (type <=eOperandType::Int32)
	{
		auto res = std::stoll(_data) - std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else
	{
		auto res = std::stold(_data) - std::stold(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}


IOperand const *Operand::operator*(IOperand const &rhs) const {

	eOperandType 	type;

	type = std::max(getType(), rhs.getType());
	if (type <=eOperandType::Int32)
	{
		auto res = std::stoll(_data) * std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else
	{
		auto res = std::stold(_data) * std::stold(rhs.toString());

		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}





const char *Operand::OverflowException_res::what() const throw() {
	return ("\033[31;1mOverflow on the result of an operation\033[0m");
}

const char *Operand::UnderflowException_res::what() const throw() {
	return ("\033[31;1mUnderflow on the result of an operation\033[0m");
}

const char *Operand::OverflowException_val::what() const throw() {
	return ("\033[31;1mOverflow on a value\033[0m");
}

const char *Operand::UnderflowException_val::what() const throw() {
	return ("\033[31;1mUnderflow on a value\033[0m");
}

const t_type Operand::LIMITS = {{INT8_MAX, INT16_MAX, INT32_MAX, FLT_MAX, DBL_MAX},
				   {INT8_MIN, INT16_MIN, INT32_MIN, -FLT_MAX, -DBL_MAX}};

IOperand const *Operand::operator/(IOperand const &rhs) const {
	eOperandType 	type;

	type = std::max(getType(), rhs.getType());
	if (type <=eOperandType::Int32)
	{
		auto res = std::stoll(_data) / std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else
	{
		auto res = std::stold(_data) / std::stold(rhs.toString());

		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}

const IOperand *Operand::operator%(const IOperand &rhs) const {
	eOperandType 	type;

	type = std::max(getType(), rhs.getType());
	if (type <=eOperandType::Int32)
	{
		auto res = std::stoll(_data) % std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else
	{
		auto res = static_cast<int64_t >(std::stold(_data)) % static_cast<int64_t >(std::stold(rhs.toString()));

		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}

FactoryMethod	Operand::FACTORY_METHOD;