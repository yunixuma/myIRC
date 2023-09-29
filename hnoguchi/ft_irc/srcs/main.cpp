#include "Server.hpp"

void	construct_test_env(Server& server)
{
	server.pushClient(1);
	server.pushClient(2);
	server.pushClient(3);
	server.searchClient(1)->setUserName("user_1");
	server.searchClient(2)->setUserName("user_2");
	server.searchClient(3)->setUserName("user_3");
	server.pushChannel("sample_1");
	server.pushChannel("sample_2");
}

void	destruct_test_env(Server& server)
{
	server.eraseClient(1);
	server.eraseClient(2);
	server.eraseClient(3);
	server.eraseChannel("sample_1");
	server.eraseChannel("sample_2");
}

int	main()
{
	Server		server(8080);

	construct_test_env(server);
	server.run();
	destruct_test_env(server);
#ifdef LEAKS
	system("leaks -q ircserv");
#endif
}

// using namespace std;
// 
// int main()
// {
//     Server	server(8080); // ポート8080でサーバーを起動します。
// 
//     if (!server.start()) {
//         std::cerr << "Failed to start the server" << std::endl;
//         return 1;
//     }
// 
//     server.run(); // サーバーを実行します。
// 
//     return 0;
// }
