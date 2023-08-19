#include <map>
#include <string>
#include <unistd.h> // for write()

class User {
public:
    std::string username;
    int sockfd; // このユーザーに関連するソケットのファイルディスクリプタ
};


string user;

class Server {
private:
    std::map<std::string, User> users; // key: username, value: User object

public:
    User* user_find(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    User* user_find(const std::string& username) {
	for(it.begin(); it.end();it++)
	{
		it++;
	}

    void send_message(User* user, const std::string& message) {
        if (user && user->sockfd > 0) {
            write(user->sockfd, message.c_str(), message.size());
        }
    }

    void process_private_message(const std::string& username, const std::string& message) {
        User* user = user_find(username);
        if (user) {
            send_message(user, message);
        } else {
            // ユーザーが見つからない場合の処理（エラーメッセージの送信など）
        }
    }
};

int main() {
    Server server;

    // テスト用のデータ
    User testUser;
    testUser.username = "destanation[1]";
    testUser.sockfd = 5; // 仮のソケットディスクリプタ番号

    // 実際の実装では、ユーザーが接続するたびにこのリストに追加する必要がある
    server.process_private_message("destanation[1]", "Hello, this is a private message!");
    
    return 0;
}