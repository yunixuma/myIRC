#include "Command.hpp"

// CONSTRUCT
Command::Command()
{
	debugMessage("Command", DEFAULT_CONSTRUCT);
}

// DESTRUCT
Command::~Command()
{
	debugMessage("Command", DESTRUCT);
}

// METHOD
void	Command::responseMessage(const std::string& message)
{
	std::cout << message << std::endl;
}
