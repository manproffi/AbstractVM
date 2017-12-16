//
// Created by Serhii Protsenko on 12/2/17.
//

#include "ClassReader.hpp"
#include <fstream>
#include <regex>
#include <CoreFoundation/CoreFoundation.h>

void	Reader::read_from_file(std::string nameFile) {

	std::string buff;
	std::ifstream input(nameFile);
	int line = 0;
	if (input.is_open() && input.good())
	{
		while (getline(input, buff))
		{
			if (std::regex_match(buff, std::regex("(exit)\\s*(;.*)?")))
			{
				_flag = true;
				break;
			}
			else if (buff.empty())
				 continue ;
			else if (std::regex_match(buff, std::regex("\\s*[;].*")))
				continue ;
			++line;
			validation(buff, line);

			inputData.emplace_back(buff);
		}

		if (!_flag)
			throw Reader::ExitException();
	}
	else
	{
		std::cout << "Error: File is not available" << std::endl;
	}
	input.close();
}

void	Reader::read_from_stdin() {

	std::string buff;
	int line = 0;
	while (getline(std::cin, buff))
	{
		if (std::regex_match(buff, std::regex("(exit)\\s*(;.*)?")))
			_flag = true;
		if (buff == ";;")
		{
			if (_flag) 	break;
			else 		throw Reader::ExitException();
		}
		else if (std::regex_match(buff, std::regex("\\s*[;].*")))
			continue ;

		++line;
		validation(buff, line);
		inputData.emplace_back(buff);
	}
}


void	Reader::validation(std::string & str, int & line) {

	std::regex pieces_regex("((push|assert) ((int8|int16|int32)[(]([-]?[0-9]+)[)]|"\
							"(float|double)[(]([-]?[0-9]+[.][0-9]+)[)])|"\
    						"(pop|dump|add|sub|mul|div|mod|print|exit))\\s*(;.*)?");

	if (std::regex_match(str, pieces_regex))
	{
		;
	}
	else
	{
		std::cout << "Line "<< line << ": " << str << std::endl;
		_flag_work_prog = false;
		error_manager(str);
	}
}

Reader::~Reader() {}

Reader::Reader() : _flag(false), _flag_work_prog(true) {}

std::vector<std::string> const & Reader::getVector() const { return inputData; }

bool Reader::is_flag_work_prog() const {
	return _flag_work_prog;
}

void Reader::error_manager(std::string & str) {
	std::regex re("(push|assert|pop|dump|add|sub|mul|div|mod|print|exit).*");
	try {
		if (std::regex_match(str, re))
			throw Reader::lex_syn_error();
		else
			throw Reader::unknown_ins();
	}
	catch (Reader::unknown_ins & e) { std::cout << e.what() << std::endl; }
	catch (Reader::lex_syn_error & e) { std::cout << e.what() << std::endl; }
}

const char* Reader::ExitException::what() const throw() {
	return ("\033[31;1mError: The program doesn't have an exit instruction\033[0m");
}

const char* Reader::lex_syn_error::what() const throw() {
	return ("\033[31;1mError: lexical errors\033[0m");
}

const char* Reader::unknown_ins::what() const throw() {
	return ("\033[31;1mError: An instruction is unknown\033[0m");
}