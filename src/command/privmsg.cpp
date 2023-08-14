
#include "server.h"
#include "Client.hpp"

	// privmsg関数内で、parametersベクトルの中身を調べ、
	// 	チャンネルへのメッセージ：PRIVMSG #channel :Hello, everyone!
	// 個人へのメッセージ：PRIVMSG nickname :Hello, how are you?
		using std::string;
		using std::cout;
		using std::endl;

	void Server::privmsg(const std::vector<std::string>& parameters)
	{
	if (parameters.size() < 2) {
    // エラーメッセージを返すなど、パラメータが不足している場合の処理
    	return;
    }

    const std::string& destination = parameters[0];
	cout << "destination = " << destination << endl;
    const std::string& message = parameters[1]; // メッセージの内容
	cout << "message = " << message << endl;

    if (destination[0] == '#') {
        // チャンネルへのメッセージの処理
		// この部分では、チャンネルの全てのメンバーにメッセージを送信するロジックを実装する
        // 例えば、findChannelByName関数でチャンネルを検索し、そのメンバーにメッセージをループで送信するなど
    } else {
        // 個人へのメッセージの処理
        std::string targetUsername = destination; // 送信先のユーザー名

        // ログインしたユーザーを管理する vector から該当するユーザーを検索
        for (std::vector<Client>::const_iterator it = loggedInUsers.begin(); it != loggedInUsers.end(); ++it) {
    const Client& user = *it; {
            if (user.getUserName() == targetUsername) {
                // ユーザーにメッセージを送信するロジックを実装
                user.distributeMessage(*this, message); // Serverインスタンスを渡す例
                break; // ユーザーを見つけたらループを終了
            }
        }
    }
}