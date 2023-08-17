#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
// #include "Client.hpp"

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
		std::string	topic_;
		ChannelMode	mode_;
		// std::vector<Client *> clientList_;
		// std::vector<Client *> operatorList_;
		std::vector<int> clientList_;
		std::vector<int> operatorList_;

	public:
		// CONSTRUCTER
		Channel(std::string& name);
		Channel(Channel& src);
		Channel&	operator=(const Channel& rhs);

		// Setters
		void	setName(std::string& name);
		void	setTopic(std::string& topic);
		void	setChannelMode(ChannelMode mode);
		void	addListClient(int& client);
		void	addListOperator(int& ope);

		// Getter
		const std::string&		getName() const;
		const std::string& 		getTopic() const;
		const ChannelMode& 		getChannelMode() const;
		const std::vector<int>&	getClientList() const;
		const std::vector<int>&	getOperatorList() const;

		// DESTRUCTER
		~Channel();
};

#endif
