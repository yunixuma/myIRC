#include "Join.hpp"

Join::Join() {}

Join::~Join() {}

// std::map<std::string, Channel *>	channelList;
// bool	Join::joinChannel();

// channel nameが正しいか調べる。
bool	Join::isChannelName(const std::string& name)
{
	if (name.)
	return (true);
}

// channelが既にあるか調べる。
bool	Join::isExistChannel(std::map<std::string, Channel *> channelList, const std::string& name)
{
	if (0 < channelList.count(name)) {
		return (true);
	}
	return (false);
}

// 既に参加しているか調べる。
bool	Join::isJoinedChannel(int client, std::map<std::string, Channel*> channelList, const std::string& name)
{
	std::map<std::string, Channel*>::iterator	it = channelList.find("name");
	std::vector<int>							clients = it->second->getClientList();

	for (std::vector<int>::iterator iter = clients.begin(); iter != clients.end(); iter++) {
		// if (name == iter.getName()) {
		// 	return (true);
		// }
	}
	return (false);
}

// ない。チャンネルを作成する。
Channel*	Join::createChannel(const std::string& name)
{
	return (new Channel(name));
}

// チャンネルクラスに、クライアントデータを追加する。
void	Join::addClient(Channel& channel, int& client)
{
	channel.addListClient(client);
}
