#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1) {
        perror("socket error");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind error");
        close(listen_sock);
        return 1;
    }

    if (listen(listen_sock, 5) == -1) {
        perror("listen error");
        close(listen_sock);
        return 1;
    }

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &client_len);
		
		// int client_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &client_len);

        if (client_sock == -1) {
            perror("accept error");
            continue;
        }

        char buffer[BUFFER_SIZE];

// int bytes = recv(clinet_sock, buff, BUFFER_SIZE, 0);
// 	recv関数は、ソケットからデータを受信するための関数です。特に、ストリームソケット（TCPなど）からデータを読み取るために使用されます。関数のプロトタイプは以下の通りです：
// ssize_t recv(int sockfd, void *buf, size_t len, int flags);
// sockfd: データを受信するソケットのファイルディスクリプタ。
// buf: 受信データを格納するためのバッファへのポインタ。
// len: bufの最大サイズ。
// flags: さまざまな操作オプションを指定するフラグ。通常、このフラグは0に設定されます。
// 返り値：

// 正の値: 実際に受信したバイト数。
// 0: ソケットが閉じられていることを示します。これは通常、接続が終了したことを示すものです。
// -1: エラーが発生した場合。

        int bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            send(client_sock, buffer, bytes_received, 0);
        }
        close(client_sock);
    }

    close(listen_sock);
    return 0;
}
