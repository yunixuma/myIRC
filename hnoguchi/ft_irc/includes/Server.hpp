#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
// #include "Message.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Join.hpp"
#include "debugMessage.hpp"

class Client;
class Channel;
class Join;

class Server {
private:
	int								sockfd_;
	bool							running_;
	int								port_;
	std::vector<Client*>			clients_;
	std::vector<Channel*>			channels_;

public:
	std::map<std::string, void *>	commandList_;
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

	// GETTER
	// const int&				getSockfd() const;
	const bool&				getRunning() const;
	// const int&				getPort() const;
	std::vector<Client *>	getClients() const;
	std::vector<Channel *>	getChannels() const;
	// const void*				getCommand(const std::string& command) const;

	// SETTER
	// void		setSockfd(const int& fd);
	// void		setRunning(const bool& running);
	// void		setPort(const int& port);

	// CLIENT
	// void		pushClient(int client_fd, sockaddr_in& client_address);
	void		pushClient(int fd);
	Client*		searchClient(int fd);
    void		eraseClient(int fd);
	// CHANNEL
	void		pushChannel(const std::string& name);
	Channel*	searchChannel(const std::string& name);
	void		eraseChannel(const std::string& name);
	// COMMAND
	// void join(const std::vector<std::string>& parameters);
	// void cap(const std::vector<std::string>& parameters);
	// void privmsg(Client &user_, Channel &channel_, const Message &message_);
	// int quit(Client &user_, Channel &channel_, const Message &message_);
	// DEBUG
	void		debugList();
};

#endif // SERVER_HPP
