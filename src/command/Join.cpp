Join::Join(int client, std::map<std::string, int> channelList, const std::string& name)
{

}

// std::map<std::string, Channel *>	channelList;
bool	Join::joinChannel()

// channel nameが既にあるか調べる。
bool	Join::isExistChannel(std::map<std::string, int> channelList, const std::string& name)
{
	if (0 < channelList->count(name)) {
		return (true);
	}
	return (false);
}

// ある。既に参加しているか調べる。
bool	Join::isJoinedChannel(int client, std::map<std::string, int> channelList, const std::string& name);

// ない。チャンネルを作成する。
bool	Join::createChannel();

// チャンネルクラスに、クライアントデータを追加する。
bool	Join::addClient();
