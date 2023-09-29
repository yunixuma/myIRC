#include "Client.hpp"

// constructor
Client::Client(int client_fd, sockaddr_in client_address)
    : fd_(client_fd), addr_(&client_address) {
}

void Client::closeSocket() 
{
		close(getFd());
}

// 上記lee追加

Client::Client(int fd, const std::string& userName, const std::string& nickname, int role) \
	: fd_(fd), userName_(userName), nickname_(nickname), role_(role) {
	std::clog << "\033[36;2;3m[" << this \
		<< "]<Client> Constructor called (" << this->userName_ << ")\033[m" << std::endl;
}


Client::Client(const Client& src) {
	std::clog << "\033[36;2;3m[" << this << "<-" << &src \
		<< "]<Client> Copy constructor called (" << this->userName_ << ")\033[m" << std::endl;
	*this = src;
}


Client&	Client::operator=(const Client& rhs) {
	std::clog << "\033[35;2;3m[" << this << "<-" << &rhs \
		<< "]<Client> Copy assignment operator called (" \
		<< rhs.userName_ << " -> " << this->userName_ << ")\033[m" << std::endl;
	this->fd_ = rhs.fd_;
	this->userName_ = rhs.userName_;
	this->nickname_ = rhs.nickname_;
	this->role_ = rhs.role_;
	if (!this->joinedChannel_.empty())
		this->joinedChannel_.clear();
	std::vector<Channel>::iterator	itr;
	for (itr = this->joinedChannel_.begin(); itr != this->joinedChannel_.end(); itr++)
	{
		this->joinedChannel_.push_back(*itr);
	}
	return (*this);
}

Client::~Client(void) {
	std::clog << "\033[31;2;3m[" << this \
		<< "]<Client> Destructor called (" << this->userName_ << ")\033[m" << std::endl;
	if (!this->joinedChannel_.empty())
		this->joinedChannel_.clear();
}

int	Client::getFd(void) const {
	return (this->fd_);
}

const sockaddr_in*	Client::getAddr(void) const {
	return (this->addr_);
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

const Channel*	Client::findJoinedChannel(std::string channelName) const {
	std::vector<Channel>::const_iterator	itr;
	for (itr = this->joinedChannel_.begin(); itr != this->joinedChannel_.end(); itr++)
	{
		if (itr->getName() == channelName)
			return (&(*itr));
	}
	return (NULL);
}

void	Client::setFd(int fd) {
	this->fd_ = fd;
}

void	Client::setUserName(const std::string& userName) {
	this->userName_ = userName;
}

void	Client::setNickname(const std::string& nickname) {
	this->nickname_ = nickname;
}

void	Client::setRole(int role) {
	this->role_ = role;
}

void	Client::joinChannel(Channel& channel) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> joinChannel(" << channel.getName() \
		<< ") called (" << this->userName_ << ")\033[m" << std::endl;
	this->joinedChannel_.push_back(channel);
}

void	Client::leaveChannel(Channel& channel) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> leaveChannel(" << channel.getName() \
		<< ") called (" << this->userName_ << ")\033[m" << std::endl;
	std::vector<Channel>::iterator	itr;
	for (itr = this->joinedChannel_.begin(); itr != this->joinedChannel_.end(); itr++)
	{
		if (&(*itr) == &channel)
		{
			this->joinedChannel_.erase(itr);
			return ;
		}
	}
}
/*
void	Client::distributeMessage(Server server, const std::string& message) {
	std::clog << "\033[2;3m[" << this \
		<< "]<Client> distributeChannel(" << message \
		<< ") called (" << this->userName_ << ")\033[m" << std::endl;
	server.send(this->fd_, message);
}
*/

// Client* Client::user_find(const std::string& username) {
//     // ユーザー名から該当するユーザーを検索する処理を実装
//     // 例: ユーザー名をキーとして、ユーザーオブジェクトを格納したデータ構造を検索
//     // 見つかった場合はそのユーザーオブジェクトへのポインタを返し、見つからなければ nullptr を返す
//     // ここでは簡単な例を示していますが、実際の実装はデータの管理方法により異なります
// }
