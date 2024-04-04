#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "server.h"
#include "Client.hpp"
#include "debugMessage.hpp"

class Server;
class Client;

enum ChannelMode
{
	NOT_MODE,
	INVITE_ONLY,				//+i
	TOPIC_BY_CHANNEL_OPERATOR,	//+t
	PASSWORD_KEY,				//+k
	OPERATOR,					//+o
	USER_LIMIT					//+l
};

enum ClientMode
{
	REGULAR_USERS,	// regular users
	OPERATOR_USERS		// operator
};

class Channel
{
private:
	std::string				name_;
	// std::string			prefix_;
	std::string				topic_;
	int						mode_;
	std::vector<Client *>	clientList_;
	std::vector<Client *>	operatorList_;

public:
	// CONSTRUCTER
	Channel(const std::string& name = "");
	Channel(const Channel& src);
	Channel&	operator=(const Channel& rhs);

	// DESTRUCTER
	~Channel();

	// Setters
	void	setName(std::string& name);
	void	setTopic(std::string& topic);
	// void	setPrefix(std::string &name);
	void	setMode(ChannelMode mode);
	void	pushClientList(Client& client);
	Client*	searchClientList(const int& fd);
	void	eraseClientList(Client& client);
	void	pushOperatorList(Client& ope);
	Client*	searchOperatorList(const int& fd);
	void	eraseClientList(Client& client);
	void	eraseOperatorList(Client& ope);

	// Getter
	const std::string&				getName() const;
	const std::string&				getTopic() const;
	// const std::string&			getPrefix() const;
	const int&						getMode() const;
	const std::vector<Client *>&	getClientList() const;
	const std::vector<Client *>&	getOperatorList() const;

	// DEBUG
	void	debugData();
};

#endif
