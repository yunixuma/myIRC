#include "Join.hpp"

Join::Join() { debugMessage("Join", DEFAULT_CONSTRUCT); }

Join::~Join() { debugMessage("Join", DESTRUCT); }

bool	Join::validateChannelName(const std::string& name)
{
	(void)name;
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
	(void)client;
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

// #include "Join.hpp"
// 
// Join::Join() {}
// 
// Join::~Join() {}
// 
// // std::map<std::string, Channel *>	channelList;
// // bool	Join::joinChannel();
// 
// /*
//  * Validation rule (Channel name)
//  * ・channel nameが正しいか調べる。
//  * ・50文字以内
//  * ・space, Ctrl+G(ascii code 7), comma, colon, は、含めてはならない。
//  * ・prefixは、&, #, !, または、なし
//  */
// 
// /*
//  * Prefixe rule
//  * . &, Standard channel, [local channel], チャンネルを作成したユーザーがチャンネルオペレータになる。
//  * . #, Standard channel, チャンネルを作成したユーザーがチャンネルオペレータになる。
//  * . +, Standard channel,
//  * . !, Safe channel,
//  */
// // TODO: Channel class にする。
// bool	Join::isChannelName(const std::string& name)
// {
// 	if (50 < name.size()) {
// 		return (false);
// 	}
// 	if (name.find(" ") != std::string::npos \
// 			|| name.find(",") != std::string::npos \
// 			|| name.find(":") != std::string::npos) {
// 		return (false);
// 	}
// 	return (true);
// }
// 
// // channelが既にあるか調べる。
// // TODO: channel class にする。
// bool	Join::isExistChannel(std::map<std::string, Channel *> channelList, const std::string& name)
// {
// 	if (0 < channelList.count(name)) {
// 		return (true);
// 	}
// 	return (false);
// }
// 
// // 既に参加しているか調べる。
// bool	Join::isJoinedChannel(Client* client, std::map<std::string, Channel*> channelList, const std::string& name)
// {
// 	std::map<std::string, Channel*>::iterator	it = channelList.find("name");
// 	std::vector<Client *>							clients = it->second->getClientList();
// 
// 	for (std::vector<Client *>::iterator iter = clients.begin(); iter != clients.end(); iter++) {
// 		// if (name == iter.getName()) {
// 		// 	return (true);
// 		// }
// 	}
// 	return (false);
// }
// 
// // ない。チャンネルを作成する。
// Channel*	Join::createChannel(const std::string& name)
// {
// 	return (new Channel(name));
// }
// 
// // チャンネルクラスに、クライアントデータを追加する。
// void	Join::addClient(Channel& channel, Client& client)
// {
// 	channel.addListClient(client);
// }
