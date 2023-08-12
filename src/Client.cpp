#include "Client.hpp"

Client(int fd, const std::string& userName, const std::string& nickname, int role) \
	: fd_(fd), userName_(userName), nickname_(nickname), role_(role), joinedChannel_(NULL) {
	std::clog << "\033[36;2;3m[" << this \
		<< "]<Client> Constructor called (" << this->username_ << ")\033[m" << std::endl;
}

Client::Client(const Client& src) {
	std::clog << "\033[36;2;3m[" << this << "<-" << &src \
		<< "]<Client> Copy constructor called (" << this->username_ << ")\033[m" << std::endl;
	*this = src;
}

Client&	Client::operator=(const Client& rhs) {
	std::clog << "\033[35;2;3m[" << this << "<-" << &rhs \
		<< "]<Client> Copy assignment operator called (" \
		<< rhs.username_ << " -> " << this->username_ << ")\033[m" << std::endl;
	this->fd_ = rhs.fd_;
	this->userName_ = rhs.userName_;
	this->nickname_ = rhs.nickname_;
	this->role_ = rhs.role_;
	if (this->joinedChannel_)
		this->joinedChannel_.clear();
	for (itr = this->joinedChannel_.begin(); itr != this->joinedChannel_.end(); itr++)
	{
		this->joinedChannel_.push_back(*itr);
	}
	return (*this);
}

Client::~Client(void) {
	std::clog << "\033[31;2;3m[" << this \
		<< "]<Client> Destructor called (" << this->username_ << ")\033[m" << std::endl;
	if (this->joinedChannel_)
		this->joinedChannel_.clear();
}

int	Client::getFd(void) const {
	return (this->fd_);
}

const std::string&	Client::getUserName(void) const {
	return (this->userName_);
}

const std::string&	Client::getNickname(void) const {
	return (this->nickname_);
}

int	Client::getRole(void) const {
	return (this->role_);
}

Channel*	findJoinedChannel(std::string channelName) const {
	std::vector<Channel>::iterator	itr;
	for (itr = this->joinedChannel_.begin(); itr != this->joinedChannel_.end(); itr++)
	{
		if (itr->getName() == channelName)
			return (itr);
	}
	return (NULL);
}

void	setFd(int fd) {
	this->fd_ = fd;
}

void	setUserName(const std::string& userName) {
	this->userName_ = userName;
}

void	setNickname(const std::string& nickname) {
	this->nickname_ = nickname;
}

void	setRole(int role) {
	this->role_ = role;
}

void	joinChannel(Channel& channel) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> joinChannel(" << channel.getName \
		<< ") called (" << this->username_ << ")\033[m" << std::endl;
	this->joinedChannel_.push_back(channel);
}

void	leaveChannel(Channel& channel) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> leaveChannel(" << channel.getName \
		<< ") called (" << this->username_ << ")\033[m" << std::endl;
	std::vector<Channel>::iterator	itr;
	for (itr = this->joinedChannel_.begin(); itr != this->joinedChannel_.end(); itr++)
	{
		if (itr == channel)
		{
			this->joinedChannel_.erase(itr);
			return ;
		}
	}
}

void	distributeMessage(Server server, const std::string& message) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> distributeChannel(" << message \
		<< ") called (" << this->username_ << ")\033[m" << std::endl;
	server.send(this->fd_, message);
}
