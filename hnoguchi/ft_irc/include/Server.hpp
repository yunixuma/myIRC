#ifndef SERVER_HPP
# define SERVER_HPP

// #include "message.h"
// #include "Client.hpp"
// #include "Channel.hpp"

#include <netinet/in.h>

#include <vector>
#include <map>

#include <iostream>
#include <string>

#include <fcntl.h>
#include <unistd.h>



class Server {
public:
	
    Server(int port);
    ~Server();
    
	bool start();
    void run();
    void stop();

	typedef void (Server::*CommandFunction)(Client &user_, Channel &channel_, const Message &message_);
	std::map<std::string, CommandFunction> userCommands;
	
	void parseIRCMessage(const std::string& message);
	void handleClientMessage(int client_fd);
	void handleIncomingMessage(const std::string& rawMessage);
	void executeCommand(Client &user_, Channel &channel_, const Message &message_);

	// connection registration
	// void	pass(Client &user_, Channel &channel_, const Message &message_);
	// void	nick(Client &user_, Channel &channel_, const Message &message_);
	// void	user(Client &user_, Channel &channel_, const Message &message_);
	// void	oper(Client &user_, Channel &channel_, const Message &message_);
	// void	mode(Client &user_, Channel &channel_, const Message &message_);
	void	quit(Client &user_, Channel &channel_, const Message &message_);

	// Channel operations
	// void	join(Client &user_, Channel &channel_, const Message &message_);
	// void	part(Client &user_, Channel &channel_, const Message &message_);
	// void	mode(Client &user_, Channel &channel_, const Message &message_);
	// void	topic(Client &user_, Channel &channel_, const Message &message_);
	// void	invite(Client &user_, Channel &channel_, const Message &message_);
	// void	kick(Client &user_, Channel &channel_, const Message &message_);

	// Sending message
	void privmsg(Client &user_, Channel &channel_, const Message &message_);
	// void notice(Client &user_, Channel &channel_, const Message &message_);

	// Miscellaneous message
	// void kill(Client &user_, Channel &channel_, const Message &message_);
	// void error(Client &user_, Channel &channel_, const Message &message_);
	
private:
    int sockfd_;
    bool running_;
    int port_;
    std::vector<int> clients_;
    std::vector<int> channels_;
	
	// 上記関数ポインタに対して、別名を定義している。
	// Server::*は、Serverクラスのメンバ関数へのポインタを示します
	// const std::vector<std::string>&: 関数の引数の型です。
	// この関数は、constなstd::vector<std::string>の参照を引数として取ります。
	// 	std::map<std::string, CommandFunction> userCommands;
};

#endif // SERVER_H
