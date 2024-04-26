#ifndef ERROR_HPP
# define ERROR_HPP

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdio>

void	debugPrintSendMessage(const std::string& prefix, const std::string &message);
void	printErrorMessage(const std::string &message);
void	fatalError(const std::string &message);

#endif  // ERROR_HPP

