//
// Created by Serhii Protsenko on 12/2/17.
//

#ifndef ABSTRACTVM_CLASSREADER_HPP
#define ABSTRACTVM_CLASSREADER_HPP


#include <string>
#include <vector>
#include <regex>
#include "ClassIOperand.hpp"

class Reader {

private:
	bool _flag;
	bool _flag_work_prog;

	std::vector<std::string> 	inputData;

	Reader& operator= (Reader const & rhs);
	Reader(Reader const & rhs);

public:

	Reader();
	~Reader();

	void 	read_from_file(std::string);
	void 	read_from_stdin();
	bool 	is_flag_work_prog() const;
	std::vector<std::string> const & getVector() const;
	void 	error_manager(std::string &);
	void	validation(std::string & , int &);

	class ExitException: public std::exception
	{
	public:
		const char* what() const throw();
	};

	class lex_syn_error: public std::exception
	{
	public:
		const char* what() const throw();
	};
	class unknown_ins: public std::exception
	{
	public:
		const char* what() const throw();
	};

};


#endif //ABSTRACTVM_CLASSREADER_HPP
