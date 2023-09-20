#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>
# include "Channel.hpp"
#include <netinet/in.h>


class Server;

class Client
{
private:
	int						fd_;
	std::string				userName_;
	std::string				nickname_;
	int						role_;
	std::vector<Channel>	joinedChannel_;

public:

	// 下記prvmsgで、欲しいメンバ関数
	Client* user_find(const std::string& username);
    // // ユーザー名から該当するユーザーを検索する処理を実装
    // // 例: ユーザー名をキーとして、ユーザーオブジェクトを格納したデータ構造を検索
    // // 見つかった場合はそのユーザーオブジェクトへのポインタを返し、見つからなければ nullptr を返す
    // // ここでは簡単な例を示していますが、実際の実装はデータの管理方法により異なります
	void new_client(int client_fd, sockaddr_in client_address);

	//上記lee 追加。

	Client(int fd, const std::string& userName, const std::string& nickname, int role);
	Client(const Client& src);
	Client(int client_fd, sockaddr_in client_address);

	Client&			operator=(const Client& rhs);
	~Client();
	int				getFd(void) const;
	const std::string&	getUserName(void) const;
	const std::string&	getNickname(void) const;
	int				getRole(void) const;
	const Channel*	findJoinedChannel(std::string channelName) const;
	void			setFd(int fd);
	void			setUserName(const std::string& userName);
	void			setNickname(const std::string& nickname);
	void			setRole(int role);
	void			joinChannel(Channel& channel);
	void			leaveChannel(Channel& channel);
	// void			distributeMessage(Server server, const std::string& message);
};

#endif
