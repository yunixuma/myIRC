#include "Channel.hpp"

Channel::Channel(const std::string &name)
{
	debugMessage("Channel", DEFAULT_CONSTRUCT);
	this->name_ = name;
	this->topic_ = "";
	this->mode_ = NOT_MODE;
}

Channel::Channel(const Channel& src)
{
	debugMessage("Channel", COPY_CONSTRUCT);
	this->operator=(src);
}

Channel&	Channel::operator=(const Channel& rhs)
{
	debugMessage("Channel", COPY_OPERATOR);
	this->name_ = rhs.getName();
	this->topic_ = rhs.getTopic();
	this->mode_ = rhs.getMode();
	for (std::vector<Client *>::const_iterator it = rhs.clientList_.begin(); it != rhs.clientList_.end(); it++) {
		this->clientList_.push_back(*it);
	}
	for (std::vector<Client *>::const_iterator it = rhs.operatorList_.begin(); it != rhs.operatorList_.end(); it++) {
		this->operatorList_.push_back(*it);
	}
	return (*this);
}

Channel::~Channel()
{
	debugMessage("Channel", DESTRUCT);
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

void	Channel::setMode(ChannelMode mode)
{
	this->mode_ = mode;
}

void	Channel::pushClientList(Client& client)
{
	this->clientList_.push_back(&client);
}

void	Channel::pushOperatorList(Client& ope)
{
	this->operatorList_.push_back(&ope);
}

void	Channel::eraseClientList(Client& client)
{
	std::vector<Client *>::iterator	itr = std::find(this->clientList_.begin(), this->clientList_.end(), &client);

	if (itr == this->clientList_.end()) {
		return ;
	}
	this->clientList_.erase(itr);
}

void	Channel::eraseOperatorList(Client& ope)
{
	std::vector<Client *>::iterator	itr = std::find(this->clientList_.begin(), this->clientList_.end(), &ope);

	if (itr == this->operatorList_.end()) {
		return ;
	}
	this->operatorList_.erase(itr);
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

const int&	Channel::getMode() const
{
	return (this->mode_);
}

const std::vector<Client *>&	Channel::getClientList() const
{
	return (this->clientList_);
}

const std::vector<Client *>&	Channel::getOperatorList() const
{
	return (this->operatorList_);
}
