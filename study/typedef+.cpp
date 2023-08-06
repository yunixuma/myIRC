#include <iostream>
#include <vector>
#include <string>
#include <map>

class Server {
public:
    typedef void (Server::*CommandFunction)(const std::vector<std::string>&);
	// void (Server::*)(const std::vector<std::string>&)
	// 上記typedefを使わなかったパターン。	
    void executeCommand(const std::string& command, const std::vector<std::string>& args) {
        auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            CommandFunction func = it->second;
            (this->*func)(args);
        }
    }
	void executeCommand(const string & command, vector<string>& str)
	{
		commandmap.find(command)
	}

    void registerCommands() {
        commandMap["SAY"] = &Server::say;
        commandMap["SHOUT"] = &Server::shout;
    }

    void say(const std::vector<std::string>& args) {
        std::cout << "Saying: " << args[0] << "\n";
    }

    void shout(const std::vector<std::string>& args) {
        std::cout << "SHOUTING: " << args[0] << "!!!\n";
    }

private:
    std::map<std::string, CommandFunction> commandMap;
};

int main() {
    Server server;
    server.registerCommands();
    server.executeCommand("SAY", {"Hello, World"});
    server.executeCommand("SHOUT", {"HELLO, WORLD"});
    return 0;
}

int main(){
	Server server;
	server.registerCommands();
	 

}
