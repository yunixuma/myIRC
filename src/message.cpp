#include "Message.h"
#include <sstream>

using namespace std;

// PRIVMSG #channel :Hello, everyone!
// 上記rawMessage の例
// #channelはパラメータの一部（メッセージが送信される先）、そして:Hello, everyone!が実際のメッセージ内容です。

Message::Message(const string& rawMessage) {
    vector<string> tokens = tokenize(rawMessage);
    command = tokens[0];
    tokens.erase(tokens.begin());
    parameters = tokens;
}

string Message::getCommand() const {
    return command;
}

vector<string> Message::getParameters() const {
    return parameters;
}

vector<string> Message::tokenize(const string& message) {
    stringstream ss(message);
    string token;
    vector<string> tokens;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
