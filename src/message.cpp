#include "message.h"

#include <sstream>

using namespace std;

// PRIVMSG #channel :Hello, everyone!
// 上記rawMessage の例

using std::vector;

string Message::getCommand() const {
    return command;
}

vector<string> Message::getParameters() const {
    return parameters;
}

Message::Message(const string& rawMessage) {
    vector<string> tokens = tokenize(rawMessage);
    command = tokens[0];
    tokens.erase(tokens.begin());
    parameters = tokens;
}


vector<string> Message::tokenize(const string& message) {
    stringstream ss(message);
    string token;
    vector<string> tokens;

    while (ss >> token) {
		if (token[0] == ':')
			{
			string rest_of_line;
			getline(ss, rest_of_line);
			tokens.push_back(token + rest_of_line);
			break;
			}
		tokens.push_back(token);
		}

    return tokens;
}
// 上記rawMessageをスペースが現れるまでの最初のトークンを抽出しているだけ。
// ss >> token は入力ストリームからスペースで区切られたトークンを一つずつ読み取ります。
