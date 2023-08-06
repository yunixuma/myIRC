#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <set>
#include <vector>
#include <algorithm>

constexpr int MAX_BUFFER_SIZE = 1024;


// fcntlを使った簡単な実装例

// #include <fcntl.h>
// //...
// int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
// //...

// // Set the socket to non-blocking mode
// int flags = fcntl(socket_fd, F_GETFL, 0);
// fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
// //...
つまり、socket_fdは一般的なファイルディスクリプタ（fd）であり、その背後にあるリソースがネットワークソケットであるという点で特殊です。

int main() {
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set socket options
    int optval = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(listen_sock, 5);

    std::set<int> client_socks;
    while (true) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(listen_sock, &fds);
        for (std::set<int>::iterator it = client_socks.begin(); it != client_socks.end(); ++it)
            FD_SET(*it, &fds);
        
        select(*std::max_element(client_socks.begin(), client_socks.end()) + 1, &fds, NULL, NULL, NULL);

        if (FD_ISSET(listen_sock, &fds)) {
            struct sockaddr_in client_addr;
            socklen_t len = sizeof(client_addr);
            int client_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &len);
            if (client_sock < 0) {
                perror("accept failed");
                continue;
            }
            client_socks.insert(client_sock);
        }

        std::vector<int> closed_socks;
        for (std::set<int>::iterator it = client_socks.begin(); it != client_socks.end(); ++it) {
            if (FD_ISSET(*it, &fds)) {
                char buffer[MAX_BUFFER_SIZE];
                int len = recv(*it, buffer, sizeof(buffer), 0);
                if (len <= 0) {
                    close(*it);
                    closed_socks.push_back(*it);
                } else {
                    send(*it, buffer, len, 0);
                }
            }
        }

        for (std::vector<int>::iterator it = closed_socks.begin(); it != closed_socks.end(); ++it)
            client_socks.erase(*it);
    }

    return 0;
}
