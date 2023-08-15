#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // ソケットの作成
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Failed to create socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // ソケットにアドレスをバインド
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to bind");
        close(sockfd);
        return 1;
    }

    // リスニング開始
    if (listen(sockfd, 10) == -1) {
        perror("Failed to listen");
        close(sockfd);
        return 1;
    }

    printf("Server listening on port 8080...\n");


	while (1) {
		fd_set fds;
		

		FS_ZERO(&rfds);
		FS_SET(socketfd,&rfds);

		struct timeval t;
		t.tv sec = 0;
		t.tv usec = 0;

		int val = select(sockfd +1, &readfds, NULL, NULL, &t)
		
	}
    while (1) {
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        int retval = select(sockfd + 1, &readfds, NULL, NULL, &tv);
        if (retval == -1) {
            perror("select()");
            break;
        } else if (retval) {
            if (FD_ISSET(sockfd, &readfds)) {
                int new_socket = accept(sockfd, NULL, NULL);
                if (new_socket == -1) {
                    perror("Failed to accept");
                    continue;
                }
                // 何かの処理を行う。ここでは受信データをエコーする。
                recv(new_socket, buffer, sizeof(buffer), 0);
                send(new_socket, buffer, strlen(buffer), 0);
                close(new_socket);
            }
        }
    }

    close(sockfd);
    return 0;
}
