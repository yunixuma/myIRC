#include "server.h"

	void Server::privmsg(const std::vector<std::string>& parameters)
	{
		 std::cout << "join has called" << std::endl;
    for(std::vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {
        std::cout << *it << std::endl;
    }
	}
