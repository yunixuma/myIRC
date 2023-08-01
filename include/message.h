#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>


class Message {
public:
    Message(const std::string& command, const std::vector<std::string>& parameters);
	Message(const std::string& rawMessage);
	
	std::string getCommand() const;
	std::vector<std::string> getParameters() const;
	std::vector<std::string> tokenize(const std::string& message);

private:
    std::string command;
    std::vector<std::string> parameters;

};

#endif // MESSAGE_H
