#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
class Server {
public:
    Server(int port);
    ~Server();
    bool start();
    void stop();
    void run();

private:
    int sockfd_;
    bool running_;
    int port_;
    std::vector<int> clients_;
};

#endif // SERVER_H
