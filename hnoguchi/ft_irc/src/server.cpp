#include "Server.hpp"
// #include "Message.hpp"
// #include "Client.hpp"
// #include <iostream>

// using std::vector;
// using std::string;
// using std::cout;
// using std::endl;
// using std::cerr;

Server::Server(){};

Server::Server(int port) : sockfd_(-1), running_(false), port_(port) {
	// userCommands["JOIN"] = &Server::join;
	// userCommands["PRIVMSG"] = &Server::privmsg;
	// userCommands["QUIT"] =&Server::quit;
}

// Server::Server(Client &user, Channel &channel);
// {
// 	if(is_user())
// 		user.set_user();
	
// }

// void Server::addClient(int client_fd, const sockaddr_in& client_address) {
//     Client new_client(client_fd, client_address);
//     clients_.push_back(new_client);
// }

// void removeClient(int client_fd) {
//     clients_.erase(
//         std::remove_if(clients_.begin(), clients_.end(),
//                        [client_fd](const Client& c) { return c.getFD() == client_fd; }),
//         clients_.end()
//     );
// }


Server::~Server() {
    if (sockfd_ >= 0) {
        if (close(sockfd_) < 0) {
			std::cerr << "Error closing socket" << std::endl;
        }
    }
}


// void Server::join(const std::vector<std::string>& parameters)
// {
//     std::cout << "join has called" << std::endl;
//     for(std::vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {
//         std::cout << *it << std::endl;
//     }
// }
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
		std::cerr << "Error binding socket" << std::endl;
	    return false;
	}

	// Listen for connections
	listen(sockfd_, 5);
	// 具体的には、listen(sockfd_, 5);というコードでは、システムが一度に保持できる、
	// まだaccept()
	// によって受け付けられていない接続要求の最大数が5であることを示しています。
	// この数を超えた接続要求が来た場合、新たな接続要求は拒否されます。

	// Set the socket to non-blocking
	fcntl(sockfd_, F_SETFL, O_NONBLOCK);

	running_ = true;
	return true;
}

// 下記の行は、新しいクライアント接続をサーバのクライアントリストに追加しています。
// newsockfdはaccept()関数から返された新しいソケットファイルディスクリプタを保持しています。
// clients_はサーバクラス内にあるvectorで、サーバが接続を許可したすべての
// クライアントのソケットファイルディスクリプタを保持します。

void Server::run()
{
    fd_set read_fds;
	// ファイルディスクリプタの集合を保持。
	// fd_set型の変数read_fdsは、select()関数で監視したい
    int max_fd;
	// max_fd;: select()関数を呼び出す際、
	// ファイルディスクリプタの集合の中で最大のディスクリプタの値を知っておく必要
	// があります。max_fdはその目的で使用される変数です。

    while (running_) {
        FD_ZERO(&read_fds);
        FD_SET(sockfd_, &read_fds);
		
        max_fd = sockfd_;

		// for(std::vector<Client>::iterator it = clients_.begin(); it != clients_.end(); ++it) {
		for(int i = 0; i < clients_.size(); i++) {
			// int client_fd = it->getFd();
			int	client_fd = clients_[i];
			FD_SET(client_fd, &read_fds);
			if (client_fd > max_fd) {
				max_fd = client_fd;
			}
		}
        struct timeval timeout;
        timeout.tv_sec = 10; 

		int activity = select(max_fd + 1, &read_fds, nullptr, nullptr, &timeout);

		// 	select()関数の返り値は以下の通りです：

		// > 0: これは、準備ができているファイル記述子の数を示します。
		// この場合、関連するファイル記述子

		// （fd_setの中のもの）をチェックして、どのものがアクティブであるかを判断する必要があります。
		// アクティブなファイル記述子に対して、読み取り、書き込み、またはエラー処理などの操作を実行できます。
		
		// 0: 指定されたタイムアウト期間が経過したが、準備ができているファイル記述子はないことを示します。
		// これは、select()呼び出しにタイムアウトが指定され、その期間中に監視されている
		// ファイル記述子にアクティビティがなかった場合に発生します。
		
		// -1: エラーが発生しました。具体的なエラー原因はerrno変数を確認することで知ることができます。

        if (activity < 0) {
            std::cerr << "select error" << std::endl;
        }
		// この行は、select システムコールの後に特定のファイルディスクリプタ
		//（この場合は sockfd_）が読み取りのためにアクティブすなわち、読み取り可能）
		// かどうかを確認しています。
		
		// sockfd: 既にbind()およびlisten()で設定された、
		// 新しい接続要求を待機しているソケットのファイルディスクリプタ。

        if (FD_ISSET(sockfd_, &read_fds)) {
            sockaddr_in cli_addr;
            socklen_t clilen = sizeof(cli_addr);

            int newsockfd = accept(sockfd_, (struct sockaddr *) &cli_addr, &clilen);
            if (newsockfd >= 0) {
				;
				// addClient(newsockfd, cli_addr);

				// accept()関数は、成功すると新しく確立された接続のファイルディスクリプタを返します。
				// エラーが発生した場合は、-1を返します。
				// したがって、このif文はaccept()が成功した場合にのみ内部のコードを実行します。
		    }
        }

		for (size_t i = 0; i < clients_.size(); i++) {
			// int client_fd = clients_[i].getFd();
			int client_fd = clients_[i];
			
			int res = 0;

			if (FD_ISSET(client_fd, &read_fds)) {
				;
			// int res = handleClientMessage(client_fd);
			}
			
			if (res < 0) {
				;
				// removeClients(client_fd); // クライアントを削除
				continue; // 次のクライアントへ
			}
		}
	}
}


void	Server::stop() {
        running_ = false;
}

// void Server::handleClientMessage(int client_fd) {
//     char buffer[256];
//     bzero(buffer, 256);
// 
//     int bytes = recv(client_fd, buffer, 255, 0);
//             
// 	if (bytes < 0) {
// 		if (errno == EAGAIN || errno == EWOULDBLOCK) {
//             // Resource temporarily unavailable, just continue with the next iteration
//             return;
//         } else {
//             std::cerr << "ERROR reading from socket: " << strerror(errno) << std::endl;
//         }
// 
//     } else if (bytes == 0) {
//         close(client_fd);
//         clients_.erase(std::remove(clients_.begin(), clients_.end(), client_fd), clients_.end());
// 
//     } else {
//         buffer[bytes] = '\0';
//         std::string message(buffer);
//         
//         if (!message.empty() && message[message.length()-1] == '\n') {
//             message.erase(message.length()-1);
//         }
//         if (!message.empty() && message[message.length()-1] == '\r') {
//             message.erase(message.length()-1);
//         }
// 
//         if(message == "exit") {
//             close(client_fd);
//             clients_.erase(std::remove(clients_.begin(), clients_.end(), client_fd), clients_.end());
// 
//         } else {
//             handleIncomingMessage(message);
//         }
//     }
// }

// void Server::executeCommand(Client &user_, Channel &channel_, const Message &message_) {
// 	// "JOIN" や "PING" などのIRCコマンドを取得
//     string command = message_.getCommand();
//     std::map<string, CommandFunction>::iterator it = userCommands.find(command);
//     // "join" join(channel, user, message);
//     if (it != userCommands.end()) {
//     // 見つかった関数をuser_、channel_、message_とともに実行。
//         (this->*(it->second))(user_, channel_, message_);
//     } else {
//         // handle unknown command...
//     }
// }

// void Server::handleIncomingMessage(const std::string& rawMessage, int client_fd) {
//     // メッセージをパースしてMessageオブジェクトを作成
//     Message message = parseMessage(rawMessage);
// 
//     // client_fd（クライアントのファイルディスクリプタ）からClientオブジェクトを検索・取得
//     Client& user = getClientByFD(client_fd);
// 
//     // メッセージからコマンドを取得
//     std::string command = message.getCommand();
// 
//     if (command == "JOIN") {
//         std::string channelName = message.getChannelName();
// 		 if (!channelExists(channelName)) {
//         addChannel(channelName);  // チャンネルがなければ新しく作成
//     }
//     
//     	Channel& channel = getChannelByName(channelName);
//         join(user, channel, message);
// 
//     } else if (command == "PING") {
//         ping(user, message);
// 
//     } else if (command == "LEAVE") {
//         std::string channelName = message.getChannelName();
//         Channel& channel = getChannelByName(channelName);
//         leaveChannel(user, channel, message);
// 
//     } else {
//         // その他の未知のコマンドに対する処理
//     }
// }

// void Server::addChannel(const std::string& name) {
//     // 名前が既に存在するか確認
//     if (channels_.find(name) != channels_.end()) {
//         // エラーハンドリング
//         return;
//     }
// 
//     // 名前が有効か確認（例）
//     if (!isValidChannelName(name)) {
//         // エラーハンドリング
//         return;
//     }
// 
//     Channel newChannel(name);
//     channels_[name] = newChannel;
// }

// void Server::removeChannel(const std::string& name) {
//     // 名前が存在するか確認
//     auto it = channels_.find(name);
//     if (it != channels_.end()) {
//         // チャンネルを削除
//         channels_.erase(it);
//     } else {
//         // エラーハンドリング（例：ログ出力、例外を投げる、等）
//     }
// }

// 下記コードの説明

// run() メソッドが呼び出されると、サーバーはクライアントからの
// 新しい接続を非同期に受け入れ、
// それらの接続をクライアントリストに追加します。
// 同時に、すでに接続されているすべてのクライアントからのメッセージをチェックします。
// メッセージは非同期に読み込まれ、それぞれのメッセージは個別に処理されます。

// クライアントから "exit" メッセージが送信されると、そのクライアントの接続は閉じられ、
// クライアントリストから削除されます。
// クライアントがソケットを閉じて接続が切断されると、
// そのクライアントもリストから削除されます。

// このプロセスは running_ 変数が false に設定されるまで、
// つまり stop() メソッドが呼び出されるまで続きます。
// その時点で、サーバーは新しい接続の受け入れを停止し、
// 既存のすべての接続を閉じます。
