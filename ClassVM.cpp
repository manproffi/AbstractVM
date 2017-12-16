//
// Created by Serhii Protsenko on 12/8/17.
//

#include <regex>
#include <cfloat>
#include "ClassVM.hpp"



FactoryMethod	VM::FM;

VM::VM()
{
	myMap = {
			{"push", &VM::push},
			{"assert", &VM::assert},
			{"pop", &VM::pop},
			{"dump", &VM::dump},
			{"add", &VM::add},
			{"sub", &VM::sub},
			{"mul", &VM::mul},
			{"div", &VM::div},
			{"mod", &VM::mod},
			{"print", &VM::print}
	};

	myOperations = {
			{"int8", eOperandType::Int8},
			{"int16", eOperandType::Int16},
			{"int32", eOperandType::Int32},
			{"float", eOperandType::Float},
			{"double", eOperandType::Double},
	};
}

VM::~VM()
{
	for (std::vector<IOperand const *>::const_iterator it = myStack.begin(); it != myStack.end(); ++it)
	{
		delete (*it);
	}
}


void	VM::push(std::string const & str) {

	std::regex re("(int8|int16|int32|float|double)[(](.*)[)](.*)");
	std::smatch sm;
	std::regex_match(str, sm, re);

	myStack.push_back(FM.createOperand(myOperations[sm[1].str()], sm[2].str()));
}

void VM::assert(std::string const & str) {
	std::regex re("(int8|int16|int32|float|double)[(](.*)[)](.*)");
	std::smatch sm;
	std::regex_match(str, sm, re);

	IOperand const *a = FM.createOperand(myOperations[sm[1].str()], sm[2].str());

	if (myStack.empty())
		throw VM::assertInstruction();
	if (a->getType() != myStack.back()->getType() || a->toString() != myStack.back()->toString())
	{
		delete a;
		throw VM::assertInstruction();
	}
	delete a;
}

void VM::pop(std::string const & str) {
	(void)str;
	if (myStack.empty())
		throw VM::emptystack();
	delete myStack.back();
	myStack.pop_back();
}

void VM::dump(std::string const& str) {
	(void)str;
	for (auto it = myStack.crbegin(); it != myStack.crend(); ++it )
	{
		std::cout << (*it)->toString() <<  std::endl;
	}
}

void VM::add(std::string const & str) {
	(void)str;
	if (myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = myStack.end() - 2;

		auto c = (**a + **b);

		delete(*a);
		delete(*b);

		myStack.pop_back();
		myStack.pop_back();
		myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::sub(std::string const & str) {
	(void)str;
	if (myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = myStack.end() - 2;

		auto c = (**b - **a);

		delete(*a);
		delete(*b);

		myStack.pop_back();
		myStack.pop_back();
		myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::mul(std::string const & str) {
	(void)str;
	if (myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = myStack.end() - 2;

		auto c = (**b * **a);

		delete(*a);
		delete(*b);

		myStack.pop_back();
		myStack.pop_back();
		myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::div(std::string const & str) {
	(void)str;
	if (myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = myStack.end() - 2;
		auto aa = std::stold((*a)->toString().c_str());
		if (aa >= 0 && aa <= FLT_MIN)
			throw VM::division_modulo();

		auto c = (**b / **a);

		delete(*a);
		delete(*b);

		myStack.pop_back();
		myStack.pop_back();
		myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::mod(std::string const & str) {
	(void)str;
	if (myStack.size() > 1)
	{
		std::vector<IOperand const *>::const_iterator a = myStack.end() - 1;
		std::vector<IOperand const *>::const_iterator b = myStack.end() - 2;
		auto aa = std::stold((*a)->toString().c_str());
		if (aa >= 0 && aa < 1)
			throw VM::division_modulo();

		auto c = (**b % **a);

		delete(*a);
		delete(*b);

		myStack.pop_back();
		myStack.pop_back();
		myStack.push_back(c);
	}
	else
		throw VM::less_than_two_instruction();
}

void VM::print(std::string const & str) {
	(void)str;
	if (myStack.empty())
		throw VM::print_exception();
	if (eOperandType::Int8 == myStack.back()->getType())
	{
		int a = atoi(myStack.back()->toString().c_str());
		if (isprint(a))
			std::cout << static_cast<char>(a) << std::endl;
	} else
		throw VM::print_exception();
}

void VM::find_command(std::vector<std::string> const & ref) {

	std::regex re("(push|assert|pop|dump|add|sub|mul|div|mod|print)[\\s+]?(.*)");
	std::smatch sm;


	for (auto it = ref.begin() ; it != ref.end(); ++it)
	{
		if (std::regex_match((*it), sm, re))
		{
			(this->*(myMap[sm[1].str()]))(sm[2].str());

		}
	}


}

/***********************************/
/********* block error *************/
/***********************************/

const char* VM::emptystack::what() const throw() {
	return ("\033[31;1mError: Instruction pop on an empty stack\033[0m");
}

const char* VM::assertInstruction::what() const throw() {
	return ("\033[31;1mError: An assert instruction is not true\033[0m");
}

const char* VM::less_than_two_instruction::what() const throw() {
	return ("\033[31;1mError: The stack is composed of strictly less that two values when an arithmetic instruction is executed\033[0m");
}

const char* VM::division_modulo::what() const throw() {
	return ("\033[31;1mError: Division/modulo by 0\033[0m");
}

const char* VM::print_exception::what() const throw() {
	return ("\033[31;1mError: An print instruction is not true\033[0m");
}