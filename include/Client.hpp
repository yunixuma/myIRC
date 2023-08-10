#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
private:
	int						fd_;
	std::string				userName_;
	std::string				nickname_;
	int						role_;
	std::vector<Channel>	joinedChannel_;
public:
	Client(int fd, const std::string& userName, const std::string& nickname, const int role);
	Client(const Client& src);
	Client&			operator=(const Client& rhs);
	~Client();
	int				getFd(void) const;
	std::string&	getUserName(void) const;
	std::string&	getNickname(void) const;
	int				getRole(void) const;
	Channel*		findJoinedChannel(std::string channelName) const;
	void			setFd(int fd);
	void			setUserName(const std::string& userName);
	void			setNickname(const std::string& nickname);
	void			setRole(int role);
	void			joinChannel(Channel& channel);
	void			leaveChannel(Channel& channel);
	void			distributeMessage(Server server, const std::string& message);
};

#endif
