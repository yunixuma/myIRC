#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
class Server {
public:
	using std::vector;
	using std::map;

    Server(int port);
    ~Server();
    
	bool start();
    void run();
    void stop();

	typedef void (Server::*commandFn)(const std::vector<std::string>& parameters);
	map<string, commandFn> userCommands;
	
	void parseIRCMessage(const std::string& message);


private:
    int sockfd_;
    bool running_;
    int port_;
    std::vector<int> clients_;
	
	userCommands["JOIN"] = &Server::join;

};

#endif // SERVER_H
