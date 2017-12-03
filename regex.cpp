/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprotsen <sprotsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:48:19 by sprotsen          #+#    #+#             */
/*   Updated: 2017/12/03 15:48:21 by sprotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <regex>
#include <map>


//(push int(8|16|32)|float|double)[(]([-]?[0-9]+)|([-]?[0-9]+[.][0-9]+)[)](push int(8|16|32)|float|double)[(]([-]?[0-9]+)|([-]?[0-9]+[.][0-9]+)[)]


// int		main()
// {
// 	std::string target[] = {"push int8(12)", "push int16(142)", "push int32(142)", "push float(4234.0)", "push float(342.44"};
	
// 	std::smatch	sm;

// 	// std::regex re("push int(8|16|32)|float|double");
// 	std::regex re("[a-z]+");

// 	for (const auto &target : target)
// 	{
//         if (std::regex_match(target, sm, re))
//         {
//         	std::cout << target << std::endl;
//         }
//     }

// 	return 0;
// }


int main()
{
    // Simple regular expression matching
    std::string fnames[] = {"push int8(12) ;dfsa", "push int16(142);;;sdfg", "push int32(142);34", "push float(4234.0)", "push double(342.44)    ; d",\
    						"pop", "mod", "print ;asdf"};
   
 	std::cout << "============================" << std::endl;
    // Extraction of several sub-matches
    std::regex pieces_regex("((push|assert) ((int8|int16|int32)[(]([-]?[0-9]+)[)]|(float|double)[(]([-]?[0-9]+[.][0-9]+)[)])|"\
    						"(pop|dump|add|sub|mul|div|mod|print|exit))\\s*(;.*)?");
    std::smatch pieces_match;
 
    // std::string s = "push int8(8)";
    // std::cout << std::regex_match(s, pieces_match, pieces_regex) << " " << pieces_match[1].str() << std::endl;

    for (const auto &fname : fnames) {
        if (std::regex_match(fname, pieces_match, pieces_regex)) {
            std::cout << fname << '\n';
            for (size_t i = 0; i < pieces_match.size(); ++i) {
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }   
        }   
    }


    // std::string new_search[] = {"blabla", "assert", "pop", "push int8 sf"};

    // std::regex re("assert|pop|push");

    // std::smatch res;

    // std::cout << std::regex_search(new_search[3], res, re) << " " << res[0] << std::endl;



    return 0;   
}
// (push|assert) ((int8|int16|int32)[]([-]?[0-9]+)[]|(float|double)[][-]?[0-9]+[.][0-9]+[])


	
// (push) ((int8|int16|int32)['(']([-]?[0-9]+)[')']|(float|double)['(']()[')']) (.*)
// std::regex pieces_regex("(push) ((int8|int16|int32)[(]([-]?[0-9]+)[)]|(float|double)[(]([-]?[0-9]+[.][0-9]+)[)]).*");