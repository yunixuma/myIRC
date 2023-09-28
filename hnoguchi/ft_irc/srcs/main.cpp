#include "Server.hpp"

int	getline_prompt(std::string prompt, std::string *line)
{
	char	buffer[111];

	std::cout << prompt;
	std::cin.clear(std::ios::goodbit);
	std::cin.width(110);
	std::cin.getline(buffer, 110);
	if (std::cin.eof() == true) {
		std::cout << "\nlog out." << std::endl;
		return (-1);
	} else if (std::cin.fail() == true) {
		std::cout << "\nPhoneBook: Fatal error: std::cin" << std::endl;
		return (-1);
	}
	*line = buffer;
	return (0);
}

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
	std::string	message;

	server.run();
	construct_test_env(server);
	while (server.getRunning()) {
		if (getline_prompt("Message: ", &message) < 0) {
			server.stop();
		}
		if (message == "QUIT") {
			server.stop();
		}
		if (message == "JOIN") {
			static_cast<Join*>(server.commandList["JOIN"])->pushClient(*(server.searchChannel("sample_1")), *(server.searchClient(1)));
			static_cast<Join*>(server.commandList["JOIN"])->pushClient(*(server.searchChannel("sample_1")), *(server.searchClient(2)));
			static_cast<Join*>(server.commandList["JOIN"])->pushClient(*(server.searchChannel("sample_1")), *(server.searchClient(3)));
		}
		else {
			std::cout << message << std::endl;
		}
		server.debugList();
	}
	destruct_test_env(server);
	system("leaks -q ircserv");
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
