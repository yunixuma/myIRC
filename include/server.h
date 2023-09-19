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
    Server();
    Server(int port);
    Server(Client &user, Channel &channel);

    ~Server();
    
	bool start();
    void run();
    void stop();

	void new_client(int client_fd, sockaddr_in client_address);

	// typedef void (Server::*CommandFunction)(Client &user_, Channel &channel_, const Message &message_);
	// std::map<std::string, CommandFunction> userCommands;
	

	void parseIRCMessage(const std::string& message);
	void handleClientMessage(int client_fd);
	void handleIncomingMessage(const std::string& rawMessage);
	void executeCommand(Client &user_, Channel &channel_, const Message &message_);
	
	void addClient(int client_fd, const sockaddr_in& client_address);
    void removeClient(int client_fd);

	// void join(const std::vector<std::string>& parameters);
	// void cap(const std::vector<std::string>& parameters);
	
	void privmsg(Client &user_, Channel &channel_, const Message &message_);
	int quit(Client &user_, Channel &channel_, const Message &message_);

private:
    int sockfd_;
    bool running_;
	
    int port_;
    std::vector<Client> clients_;
	std::map<std::string, Channel> channels_;

	
};

#endif // SERVER_H
