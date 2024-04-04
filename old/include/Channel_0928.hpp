#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "Client.hpp"

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
		std::string	name_;
		// std::string	prefix_;
		std::string	topic_;
		ChannelMode	mode_;
		// std::vector<Client *> clientList_;
		// std::vector<Client *> operatorList_;
		std::vector<Client *> clientList_;
		std::vector<Client *> operatorList_;

	public:
		// CONSTRUCTER
		Channel();
		Channel(const std::string& name);
		Channel(const Channel& src);
		Channel(const std::string& channelName, const std::string& topic);
		Channel&	operator=(const Channel& rhs);

		// DESTRUCTER
		~Channel();

		// Setters
		void	setName(std::string& name);
		void	setTopic(std::string& topic);

		// void	setPrefix(std::string &name);
		void	setChannelMode(ChannelMode mode);
		void	addListClient(Client& client);
		void	addListOperator(Client& ope);

		// Getter
		const std::string&				getName() const;
		const std::string&				getTopic() const;

		// const std::string&			getPrefix() const;
		const ChannelMode&				getChannelMode() const;
		const std::vector<Client *>&	getClientList() const;
		const std::vector<Client *>&	getOperatorList() const;
};

#endif
