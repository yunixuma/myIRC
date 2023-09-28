#include "Join.hpp"

Join::Join() { debugMessage("Join", DEFAULT_CONSTRUCT); };

Join::~Join() { debugMessage("Join", DESTRUCT); };

bool	Join::validateChannelName(const std::string& name)
{
	return (true);
}

bool	Join::isExistChannel(const Channel* channel)
{
	if (channel == NULL) {
		return (false);
	}
	return (true);
}

bool	Join::isJoinedChannel(const Client* client)
{
	return (true);
}

void	Join::pushClient(Channel& channel, Client& client)
{
	channel.pushClientList(client);
}

void	Join::pushOperator(Channel& channel, Client& client)
{
	channel.pushOperatorList(client);
}
