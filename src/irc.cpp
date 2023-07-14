#include "server.h"

Server::Server(int port) : sockfd_(-1), running_(false), port_(port) {}

Server::~Server() {
    if(sockfd_ >= 0) {
        close(sockfd_);
    }
}


// start() メソッドが呼び出されると、新しいソケットが作成され、指定されたポートにバインドされ、
// クライアントからの接続を待ちます。
bool Server::start() {
        // Create a socket
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd_ < 0) 
		{
            return false;
        }

        // Bind the socket to the port
        sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port_);

        if (bind(sockfd_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            return false;
        }

        // Listen for connections
        listen(sockfd_, 5);
		// 具体的には、listen(sockfd_, 5);というコードでは、システムが一度に保持できる、まだaccept()
		// によって受け付けられていない接続要求の最大数が5であることを示しています。この数を超えた接続要求が来た場合、新たな接続要求は拒否されます。

        // Set the socket to non-blocking
        fcntl(sockfd_, F_SETFL, O_NONBLOCK);

        running_ = true;
        return true;
    }

    void Server::stop() {
        running_ = false;
    }

	// 上記の行は、新しいクライアント接続をサーバのクライアントリストに追加しています。
	// 詳しく説明すると：
	// newsockfdはaccept()関数から返された新しいソケットファイルディスクリプタを保持しています。これは新しいクライアント接続を表しています。
	// clients_はサーバクラス内にあるvectorで、サーバが接続を許可したすべての
	// クライアントのソケットファイルディスクリプタを保持します。
	// push_back()はC++のvectorに要素を追加するための関数です。
	// したがって、clients_.push_back(newsockfd);は新しいクライアント接続
	// （newsockfd）をクライアントリスト（clients_）に追加する操作を実行しています。


        // Handle client messages...
        // In a real implementation, we would use a non-blocking read and parse
        // the incoming messages according to the IRC protocol, but we'll skip that
        // for this simplified example.

void Server::run()
{
    while (running_) {
        // Accept new client connections
        sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        int newsockfd = accept(sockfd_, (struct sockaddr *) &cli_addr, &clilen);
		
        // If a valid client connection was made, add it to the clients list
        if (newsockfd >= 0) {
            clients_.push_back(newsockfd);
        }

        // Handle client messages
        for(size_t i = 0; i < clients_.size(); i++) {
            char buffer[256];
            bzero(buffer, 256);

            int n = recv(clients_[i], buffer, 255, 0);
			printf("%s", buffer);
            if (n < 0) {
                // handle error
                std::cerr << "ERROR reading from socket" << std::endl;
            }
            else if (n == 0) {
                // client has disconnected
                close(clients_[i]);
                clients_.erase(clients_.begin() + i);
            }
            else {
                // process message
                std::string message(buffer);
                if(message == "exit") {
                    close(clients_[i]);
                    clients_.erase(clients_.begin() + i);
                }
                else {
                    // process other messages...
                }
            }
        }
    }
}

// 下記コードの説明

// run() メソッドが呼び出されると、サーバーはクライアントからの新しい接続を非同期に受け入れ、
// それらの接続をクライアントリストに追加します。
// 同時に、すでに接続されているすべてのクライアントからのメッセージをチェックします。
// メッセージは非同期に読み込まれ、それぞれのメッセージは個別に処理されます。
// クライアントから "exit" メッセージが送信されると、そのクライアントの接続は閉じられ、
// クライアントリストから削除されます。
// クライアントがソケットを閉じて接続が切断されると、そのクライアントもリストから削除されます。
// このプロセスは running_ 変数が false に設定されるまで、
// つまり stop() メソッドが呼び出されるまで続きます。その時点で、サーバーは新しい接続の受け入れを停止し、
// 既存のすべての接続を閉じます。