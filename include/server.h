#ifndef SERVER_H
#define SERVER_H

#include "message.h"
#include "Client.hpp"

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

	typedef void (Server::*commandFn)(const std::vector<std::string>& parameters);
	std::map<std::string, commandFn> userCommands;
	
	void parseIRCMessage(const std::string& message);
	void handleClientMessage(int client_fd);
	void handleIncomingMessage(const std::string& rawMessage);
	void executeCommand(const Message& message);

	void join(const std::vector<std::string>& parameters);
	// void cap(const std::vector<std::string>& parameters);
	
	void privmsg(Client &user_, Channel &channel_, const Message &message_);
	int quit(Client &user_, Channel &channel_, const Message &message_);

private:
    int sockfd_;
    bool running_;
    int port_;
    std::vector<int> clients_;
	
	typedef void (Server::*CommandFunction)(const std::vector<std::string>&);
	// 上記関数ポインタに対して、別名を定義している。
	// Server::*は、Serverクラスのメンバ関数へのポインタを示します
	// const std::vector<std::string>&: 関数の引数の型です。
	// この関数は、constなstd::vector<std::string>の参照を引数として取ります。
	// 	std::map<std::string, CommandFunction> userCommands;
};

#endif // SERVER_H
