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

int	main()
{
	Server		server(8080);
	std::string	message;

	server.run();
	while (server.getRunning()) {
		if (getline_prompt("Message: ", &message) < 0) {
			server.stop();
		}
		if (message == "QUIT") {
			server.stop();
		}
		else {
			std::cout << message << std::endl;
		}
	}
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
