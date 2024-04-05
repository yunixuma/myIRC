#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include "debugMessage.hpp"

class Command {
public:
	// CONSTRUCT
	Command();
	// DESTRUCT
	virtual ~Command();
	// METHOD
	void	responseMessage(const std::string& message);
};

#endif
