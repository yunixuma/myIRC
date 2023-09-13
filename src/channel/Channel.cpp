#include "Channel.hpp"

Channel::Channel(const std::string &name)
{
	this->name_ = name;
	this->topic_ = "";
	this->mode_ = NOT_MODE;
}

Channel::Channel(const Channel& src)
{
	this->operator=(src);
}

Channel&	Channel::operator=(const Channel& rhs)
{
	this->name_ = rhs.getName();
	this->topic_ = rhs.getTopic();
	this->mode_ = rhs.getChannelMode();
	for (std::vector<int>::const_iterator it = rhs.clientList_.begin(); it != rhs.clientList_.end(); it++) {
		this->clientList_.push_back(*it);
	}
	for (std::vector<int>::const_iterator it = rhs.operatorList_.begin(); it != rhs.operatorList_.end(); it++) {
		this->operatorList_.push_back(*it);
	}
	return (*this);
}

Channel::~Channel()
{
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

// void	Channel::setPrefix(std::string &name)
// {
// 	// TODO: プレフィックスがない場合について考える。
// 	if (name[0] != '&') {
// 		this->prefix_ = name[0];
// 	}
// 	else if (name[0] != '#') {
// 		this->prefix_ = name[0];
// 	}
// 	else if (name[0] != '+') {
// 		this->prefix_ = name[0];
// 	}
// 	else {
// 		this->prefix_ = "#";
// 	}
// }

void	Channel::setChannelMode(ChannelMode mode)
{
	this->mode_ = mode;
}

void	Channel::addListClient(int& client)
{
	this->clientList_.push_back(client);
}

void	Channel::addListOperator(int& ope)
{
	this->operatorList_.push_back(ope);
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

// const std::string&	Channel::getPrefix() const
// {
// 	return (this->prefix_);
// }

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
