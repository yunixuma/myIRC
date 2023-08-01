#include "Config.h"

int main()
{
    Config config("config.txt");

    std::string portNumber = config.get("port");

    std::cout << "Port number: " << portNumber << std::endl;

    return 0;
}
