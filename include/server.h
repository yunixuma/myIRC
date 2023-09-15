#ifndef SERVER_H
#define SERVER_H

#include "message.h"
#include "Client.hpp"
#include "Channel.hpp"

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
	

	// void join(const std::vector<std::string>& parameters);
	// void cap(const std::vector<std::string>& parameters);
	
	void privmsg(Client &user_, Channel &channel_, const Message &message_);
	int quit(Client &user_, Channel &channel_, const Message &message_);

private:
    int sockfd_;
    bool running_;
	
    int port_;

    std::vector<Client> clients_;
    std::vector<Channel> channel_;
	
};

#endif // SERVER_H
