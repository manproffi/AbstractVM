#include <iostream>
#include <regex>
#include <zconf.h>
#include "ClassIOperand.hpp"
#include "ClassFactoryMethod.hpp"

#include "ClassReader.hpp"
#include "ClassVM.hpp"
#include "ClassOperand.hpp"


int main(int argc, char *argv[]) {

	Reader 	reader;
	VM 		vm;

	if (argc == 2)
	{
		try { reader.read_from_file(argv[1]); }
		catch (Reader::ExitException & e)
		{
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	else if (argc == 1)
	{
		try { reader.read_from_stdin(); }
		catch (Reader::ExitException & e)
		{
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	else
		std::cout << "usage: ./avm <file> or ./avm" << std::endl;

	if (!reader.is_flag_work_prog())
		exit(1);

	try { vm.find_command(reader.getVector());}
	catch (VM::emptystack & e) 					{ std::cout << e.what() << std::endl; }
	catch (VM::assertInstruction & e) 			{ std::cout << e.what() << std::endl; }
	catch (Operand::OverflowException_res & e) 	{ std::cout << e.what() << std::endl; }
	catch (Operand::UnderflowException_res & e) { std::cout << e.what() << std::endl; }
	catch (Operand::OverflowException_val & e) 	{ std::cout << e.what() << std::endl; }
	catch (Operand::UnderflowException_val & e) { std::cout << e.what() << std::endl; }
	catch (VM::less_than_two_instruction & e) 	{ std::cout << e.what() << std::endl; }
	catch (VM::division_modulo & e)				{ std::cout << e.what() << std::endl; }
	catch (VM::print_exception & e)				{ std::cout << e.what() << std::endl; }


	return 0;
}



/************/
//  [-]?[0-9]+ 				// int
//  [-]?[0-9]+[.][0-9]+ 	//float + double