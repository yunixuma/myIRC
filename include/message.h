#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>


using namespace std::string;
using namespace std::vector;

class Message {
public:
    Message(const string& command, const vector<string>& parameters);
    string getCommand() const;
    vector<string> getParameters() const;
private:
    string command;
    vector<string> parameters;

};

#endif // MESSAGE_H
