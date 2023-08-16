#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>

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
	OPERATOR		// operator
};

class Channel
{
	private:
		std::string	name_;
		ChannelMode	mode_;
		// topic_;
	public:
		std::vector<Client *> clientList_;
		std::vector<Client *> operatorList_;
		// CONSTRUCTER
		Channel(std::string &name);

		// Setters
		void	setName(std::string &name);
		void	setChannelMode(ChannelMode mode);

		// Getter
		std::string &getName(void) const;
		ChannelMode &getChannelMode(void) const;
}

#endif
