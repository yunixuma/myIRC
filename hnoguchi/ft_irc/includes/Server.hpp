#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "debugMessage.hpp"
// #include "Message.hpp"
// #include "Client.hpp"
// #include "Channel.hpp"

class Server {
public:
    Server();
    Server(int port);
    // Server(Client &user, Channel &channel);

    ~Server();

	// bool start();
    void run();
    void stop();

	// void new_client(int client_fd, sockaddr_in client_address);
	// typedef void (Server::*CommandFunction)(Client &user_, Channel &channel_, const Message &message_);
	// std::map<std::string, CommandFunction> userCommands;
	// void parseIRCMessage(const std::string& message);
	// void handleClientMessage(int client_fd);
	// void handleIncomingMessage(const std::string& rawMessage);
	// void executeCommand(Client &user_, Channel &channel_, const Message &message_);
	
	// CLIENT
	// void addClient(int client_fd, const sockaddr_in& client_address);
    // void removeClient(int client_fd);
	// channel
	// void addChannel(const std::string& name);
	// void removeChannel(const std::string& name);
	// void join(const std::vector<std::string>& parameters);
	// void cap(const std::vector<std::string>& parameters);
	// void privmsg(Client &user_, Channel &channel_, const Message &message_);
	// int quit(Client &user_, Channel &channel_, const Message &message_);

	const bool&	getRunning() const;
private:
    int									sockfd_;
    bool								running_;
    int									port_;
    // std::vector<Client *>				clients_;
	// std::map<std::string, Channel *>	channels_;
	
};

#endif // SERVER_HPP
