// 認証: クライアントがサーバーに接続するためのパスワード認証機能がありません。この機能は、仕様書に記載されている通り必須です。

// IRC プロトコルは、接続、認証、チャネルの作成、メッセージの送信など、クライアントとサーバー間の通信を規定しています。

// チャネル: クライアントがメッセージを交換するためのチャネルの作成と管理がありません。野口さん担当

// プライベートメッセージ: 現在の実装では、クライアント間でプライベートメッセージを送受信する機能がありません。

// 運用者とユーザーの管理: 現在の実装では、IRC チャネルの運用者と通常のユーザーを区別する機能がありません。
// また、運用者がチャネルの設定を変更したり、ユーザーをキックしたり、招待したりする機能もありません。
#include "server.h"
#include "message.h"

#include <iostream>


using std::vector;
using std::string;
using std::cout;
using std::endl;

Server::Server(int port) : sockfd_(-1), running_(false), port_(port) {
	userCommands["JOIN"] = &Server::join;
	userCommands["PRMSG"] = &Server::privmsg;
}

Server::~Server() {
    if(sockfd_ >= 0)
	{
        close(sockfd_);
    }
}

void Server::join(const std::vector<std::string>& parameters)
{
    std::cout << "join has called" << std::endl;
    for(std::vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

// start() メソッドが呼び出されると、新しいソケットが作成され、指定されたポートにバインドされ、
// クライアントからの接続を待ちます。
bool Server::start() 
{
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
		// によって受け付けられていない接続要求の最大数が5であることを示しています。
		// この数を超えた接続要求が来た場合、新たな接続要求は拒否されます。

        // Set the socket to non-blocking
        fcntl(sockfd_, F_SETFL, O_NONBLOCK);

        running_ = true;
        return true;
    }

    void Server::stop() {
        running_ = false;
    }


	// 下記の行は、新しいクライアント接続をサーバのクライアントリストに追加しています。
	// 詳しく説明すると：
	// newsockfdはaccept()関数から返された新しいソケットファイルディスクリプタを保持しています。
	// これは新しいクライアント接続を表しています。
	// clients_はサーバクラス内にあるvectorで、サーバが接続を許可したすべての
	// クライアントのソケットファイルディスクリプタを保持します。
	// push_back()はC++のvectorに要素を追加するための関数です。
	// したがって、clients_.push_back(newsockfd);は新しいクライアント接続
	//（newsockfd）をクライアントリスト（clients_）に追加する操作を実行しています。

        // Handle client messages...
        // In a real implementation, we would use a non-blocking read and parse
        // the incoming messages according to the IRC protocol, but we'll skip that
        // for this simplified example.

void Server::run()
{
    while (running_) {
        sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        int newsockfd = accept(sockfd_, (struct sockaddr *) &cli_addr, &clilen);
        
        if (newsockfd >= 0) {
            clients_.push_back(newsockfd);
        }

        for(size_t i = 0; i < clients_.size(); i++) {
            handleClientMessage(clients_[i]);
        }
    }
}

void Server::handleClientMessage(int client_fd) {
    char buffer[256];
    bzero(buffer, 256);

    int bytes = recv(client_fd, buffer, 255, 0);
            
    if (bytes < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // Resource temporarily unavailable, just continue with the next iteration
            return;
        } else {
            std::cerr << "ERROR reading from socket: " << strerror(errno) << std::endl;
        }

    } else if (bytes == 0) {
        close(client_fd);
        clients_.erase(std::remove(clients_.begin(), clients_.end(), client_fd), clients_.end());

    } else {
        buffer[bytes] = '\0';
        std::string message(buffer);
        
        if (!message.empty() && message[message.length()-1] == '\n') {
            message.erase(message.length()-1);
        }
        if (!message.empty() && message[message.length()-1] == '\r') {
            message.erase(message.length()-1);
        }

        if(message == "exit") {
            close(client_fd);
            clients_.erase(std::remove(clients_.begin(), clients_.end(), client_fd), clients_.end());

        } else {
            handleIncomingMessage(message);
        }
    }
}

void Server::handleIncomingMessage(const std::string& rawMessage) {
    Message message(rawMessage);
    executeCommand(message);
}

void Server::executeCommand(const Message& message) {
	// "JOIN" や "PING" などのIRCコマンドを取得
    string command = message.getCommand();
    std::map<string, CommandFunction>::iterator it = userCommands.find(command);
    
    if (it != userCommands.end()) {
        // execute the corresponding method with parameters from the message
        (this->*(it->second))(message.getParameters());
    } else {
        // handle unknown command...
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