#include "Command.hpp"

int	Command::nick(Client& client, Channe& channel, const Message& msg) {
	std::clog << "\033[36;2;3m[" << this \
		<< "]<Command> nick called (" << client->username_ << ")\033[m" << std::endl;
	std::vector<std::string>	params = msg.getParameters();
	if (!params)
		return (1);
	client.setNickname(*params[0]);
	return (0);
	(void)channel;
}
