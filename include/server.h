#ifndef SERVER_H
#define SERVER_H

#include "message.h"

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
	// std:: map<std::string, commandFn> userCommands;
	
	void parseIRCMessage(const std::string& message);
	void handleClientMessage(int client_fd);
	void handleIncomingMessage(const std::string& rawMessage);
	void executeCommand(const Message& message);

	void join(const std::vector<std::string>& parameters);


private:
    int sockfd_;
    bool running_;
    int port_;
    std::vector<int> clients_;
	
	typedef void (Server::*CommandFunction)(const std::vector<std::string>&);

	std::map<std::string, CommandFunction> userCommands;
	// void join(const std::vector<std::string> & parameters);
	// userCommands["JOIN"] = &Server::join;


};

#endif // SERVER_H
