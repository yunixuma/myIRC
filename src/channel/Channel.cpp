#include "Channel.hpp"

Channel::Channel(std::string &name) :
	name_(name), normal_clients_(NULL), operator_clients_(NULL)
{
}

// SETTER
void	Channel::setName(std::string &name)
{
	this->name_ = name;
}

void	Channel::setChannelMode(ChannelMode mode)
{
	this->mode_ = mode;
/* 	switch(mode) {
		case INVITE_ONLY:
			this->mode_ = INVITE_ONLY;
			break;
		case TOPIC_BY_CHANNEL_OPERATOR:
			this->mode_ = TOPIC_BY_CHANNEL_OPERATOR;
			break;
		case PASSWORD_KEY:
			this->mode_ = PASSWORD_KEY;
			break;
		case OPERATOR:
			this->mode_ = OPERATOR;
			break;
		case USER_LIMIT:
			this->mode_ = USER_LIMIT;
			break;
		default:
			break;
	}
 */
}

// GETTER
std::string &Channel::getName(void)
{
	return (this->name_);
}

ChannelMode &Channel::getChannelMode(void) const
{
	return (this->mode_);
}

Channel::~Channel()
{
}