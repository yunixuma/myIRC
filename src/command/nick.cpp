#include "Command.hpp"

Server::nick(User user, const Message& msg, const std::string& nickname, int role) \
	: fd_(fd), userName_(userName), nickname_(nickname), role_(role), joinedChannel_(NULL) {
	std::clog << "\033[36;2;3m[" << this \
		<< "]<Command> nick called (" << this->username_ << ")\033[m" << std::endl;
}
