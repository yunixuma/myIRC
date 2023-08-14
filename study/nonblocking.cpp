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

// つまり、socket_fdは一般的なファイルディスクリプタ（fd）であり、
// その背後にあるリソースがネットワークソケットであるという点で特殊です。

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
            int client_sock = accept(listen_sock, (stあruct sockaddr*)&client_addr, &len);
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

// ソケットのノンブロッキング化：
// コードの冒頭で示されている fcntl の使用により、
// ソケットのファイルディスクリプタ（socket_fdやclient_sock）
// がノンブロッキングモードに設定されています。これにより、
// ソケットへの読み書き操作が非同期的に行われるようになります。

// イベントループ内の非同期処理：
// メインのイベントループ（while (true) ブロック）内で、ソケットの読み書きや接続の監視が行われています。select 関数を使用して、ソケットとクライアントのファイルディスクリプタの状態変化を監視しています。

// クライアントの接続待ち：FD_SET(listen_sock, &fds) によって、新しいクライアントの接続を待ちます。新しいクライアントの接続が検出されると、ソケットが読み書き可能な状態になり、それに対応して accept 関数でクライアントの接続を受け入れ、クライアントのファイルディスクリプタを client_socks に追加します。

// クライアントからのデータ読み書き：クライアントのファイルディスクリプタが読み書き可能な状態になると、FD_SET(*it, &fds) によってその状態変化を監視します。この部分で、ソケットからデータの読み取りや送信が非同期に行われています。クライアントからのデータが到着した場合は、それに応じてデータの送信やソケットのクローズが行われます。

// クライアントソケットのセット管理：
// client_socks というセットを使用して、現在接続されているクライアントのファイルディスクリプタを管理しています。新しいクライアントの接続やソケットのクローズ時に適切な管理が行われています。
