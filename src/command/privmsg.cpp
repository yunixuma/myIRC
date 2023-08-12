
#include "server.h"

	// privmsg関数内で、parametersベクトルの中身を調べ、
	// 	チャンネルへのメッセージ：PRIVMSG #channel :Hello, everyone!
	// 個人へのメッセージ：PRIVMSG nickname :Hello, how are you?

	void Server::privmsg(const std::vector<std::string>& parameters)
	{
		using std::string;
		using std::cout;
		using std::endl;

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
      
		// この部分では、指定されたユーザー名でユーザーを検索し、そのユーザーにメッセージを送信するロジックを実装する
    
	}
}
	// #があった場合は、チャンネルのユーザー向けにメッセージを送り、
	// なかった場合は個人にメッセージを送る

	// 宛先とメッセージ本文を適切に処理するロジックが必要になるでしょう。

