#include "Channel.hpp"

Channel::Channel(std::string &name)
{
	this->name_ = name;
	this->topic_ = "";
	this->mode_ = NOT_MODE;
}

Channel::Channel(Channel& src)
{
	this->name_ = src.getName();
	this->topic_ = src.getTopic();
	this->mode_ = src.getChannelMode();
	for (std::vector<int>::iterator it = src.clientList_.begin(); it != src.clientList_.end(); it++) {
		this->clientList_.push_back(*it);
	}
	for (std::vector<int>::iterator it = src.operatorList_.begin(); it != src.operatorList_.end(); it++) {
		this->operatorList_.push_back(*it);
	}
}

// SETTER
void	Channel::setName(std::string &name)
{
	this->name_ = name;
}

void	Channel::setTopic(std::string& topic)
{
	this->topic_ = topic;
}

void	Channel::setChannelMode(ChannelMode mode)
{
	this->mode_ = mode;
}

// GETTER
const std::string&	Channel::getName() const
{
	return (this->name_);
}

const std::string&	Channel::getTopic() const
{
	return (this->topic_);
}

const ChannelMode&	Channel::getChannelMode() const
{
	return (this->mode_);
}

const std::vector<int>&	Channel::getClientList() const
{
	return (this->clientList_);
}

const std::vector<int>&	Channel::getOperatorList() const
{
	return (this->operatorList_);
}

Channel::~Channel()
{
}
