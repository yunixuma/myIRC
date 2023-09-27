#include <iostream>

class Server;

typedef void (Server::*commandFn)();

class Server {
	public:
		void	sampleFunc() {
			std::cout << "Call sampleFunc();" << std::endl;
		}
};

int	main() {
	Server		server;
	// メンバ関数ポインタの宣言
	commandFn	ptr = &Server::sampleFunc;
	// メンバ関数ポインタを使ってメンバ関数を呼び出す
	(server.*ptr)();
}
