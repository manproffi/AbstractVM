#include <iostream>
#include <regex>
#include <vector>

int 	main(int argc, char const *argv[])
{
	std::regex re("(push) (int(8|16|32))[(](.*)[)]");
	std::smatch result;
	std::string target("push int8(32)");

	std::vector<std::smatch>	vec;

 // std::regex_match ( s, m, e );
	if (std::regex_match(target, result, re))
	{
		// std::cout << result[0] << std::endl;
		vec.push_back(result);
		for (std::smatch::iterator it = result.begin(); it != result.end(); ++it)
			std::cout << *it << std::endl;
	}
	else
		std::cout << "Dno" << std::endl;

	std::cout << vec[0][0] << std::endl;
	std::cout << vec[0][1] << std::endl;
	std::cout << vec[0][2] << std::endl;
	



	return 0;
}