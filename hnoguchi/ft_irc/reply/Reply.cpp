#include "./Reply.hpp"
#include "../parser/Parser.hpp"
#include "../error/error.hpp"

// CONSTRUCTOR
// DESTRUCTOR
Reply::Reply() : delimiter_("\r\n") {}
Reply::~Reply() {}

std::string	Reply::createMessage(int num, const User& user, const Info& info, const ParsedMessage& parsedMsg) {
	if (num <= 0) {
		return ("");
	}
	try {
		// TODO(hnoguchi): Check num.
		// std::string	msg = ":" + user.getNickName();
		std::string	msg = ":" + info.getConfig().getServerName() + " ";
		if (num == kRPL_WELCOME) {
			msg += "001 " + user.getNickName() + " :Welcome to the Internet Relay Network " + user.getNickName() + "!" + user.getUserName() + "@" + user.getServerName();
			msg += this->delimiter_;
			msg += ":" + info.getConfig().getServerName() + " ";
			std::ostringstream	oss;
			oss << info.getConfig().getVersion();
			msg += "002 " + user.getNickName() + " :Your host is " + info.getConfig().getServerName() + ", running version " + oss.str();
			msg += this->delimiter_;
			msg += ":" + info.getConfig().getServerName() + " ";
			std::string	date = std::asctime(std::localtime(&(info.getConfig().getCreatedData())));
			if (!date.empty() && date[date.size() - 1] == '\n') {
				date.erase(date.size() - 1);
			}
			msg += "003 " + user.getNickName() + " :This server was created " + date;
			msg += this->delimiter_;
			msg += ":" + info.getConfig().getServerName() + " ";
			msg += "004 " + user.getNickName() + " :" + info.getConfig().getServerName() + " " + oss.str() + " " + info.getConfig().getUserModes() + " " +  info.getConfig().getChannelModes();
			msg += this->delimiter_;
			msg += ":" + user.getNickName() + " NICK :" + user.getNickName();
		} else if (num < 100  || (num >= 200 && num < 400)) {
			if (num == kRPL_UMODEIS) {
				msg += "221 " + user.getNickName();
				if (user.getModes() & kAway) {
					msg += " +a";
				} else if (user.getModes() & kOperator) {
					msg += " +o";
				} else if (user.getModes() & kRestrict) {
					msg += " +r";
				}
			} else if (num == kRPL_YOUREOPER) {
				msg += "381 " + user.getNickName() + " :You are now an IRC operator";
			}
		} else if (num >= 400 && num < 600) {
			if (num == kERR_NOSUCHNICK) {
				msg += "401 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :No such nick/channel";
			} else if (num == kERR_NOSUCHSERVER) {
				msg += "402 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :No such server";
			} else if (num == kERR_NOSUCHCHANNEL) {
				// msg += "403 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :No such channel";
				msg += "403 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue();
			} else if (num == kERR_NORECIPIENT) {
				msg += "411 " + user.getNickName() + " :No recipient given (" + parsedMsg.getCommand() + ")";
			} else if (num == kERR_NOTEXTTOSEND) {
				msg += "412 " + user.getNickName() + " :No text to send";
			} else if (num == kERR_UNKNOWNCOMMAND) {
				msg += "421 " + user.getNickName() + " :" + parsedMsg.getCommand() + " :Unknown command";
			} else if (num == kERR_NONICKNAMEGIVEN) {
				msg += "431 " + user.getNickName() + " :No nickname given";
			} else if (num == kERR_ERRONEUSNICKNAME) {
				msg += "432 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :Erroneous nickname";
			} else if (num == kERR_NICKNAMEINUSE) {
				// msg += "433 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :Nickname is already in use";
				msg += "433 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue();
			} else if (num == kERR_NOTONCHANNEL) {
				msg += "442 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :You're not on that channel";
			} else if (num == kERR_NOTREGISTERED) {
				msg += "451 * :You have not registered";
			} else if (num == kERR_NEEDMOREPARAMS) {
				msg += "461 " + user.getNickName() + " :" + parsedMsg.getCommand() + " :Not enough parameters";
			} else if (num == kERR_ALREADYREGISTRED) {
				msg += "462 " +  user.getNickName() +  " :Unauthorized command (already registered)";
			} else if (num == kERR_PASSWDMISMATCH) {
				msg += "464 " +  user.getNickName() +  " :Password incorrect";
			} else if (num == kERR_RESTRICTED) {
				msg += "484 " + user.getNickName() + " :Your connection is restricted!";
			} else if (num == kERR_UMODEUNKNOWNFLAG) {
				msg += "501 " + user.getNickName() + " :Unknown MODE flag";
			} else if (num == kERR_USERSDONTMATCH) {
				msg += "502 " + user.getNickName() + " :Cannot change mode for other users";
			}
		}
		msg += this->delimiter_;
		return (msg);
	} catch (const std::exception& e) {
		printErrorMessage(e.what());
		return ("");
	}
}


// SETTER
// void Reply::setMessage(const std::string& message) {
// 	if (message.empty()) {
// 		printErrorMessage("Reply::setMessage is empty argument.");
// 		return;
// 	}
// 	this->message_ = message;
// 	return;
// }

// void Reply::setNumeric(const std::string& num) {
// 	if (num.empty()) {
// 		printErrorMessage("Reply::setNumeric is empty argument.");
// 		return;
// 	}
// 	this->numeric_ = num;
// 	return;
// }

// GETTER
// const std::string&	Reply::getMessage() const {
// 	return (this->message_);
// }

// const std::string&	Reply::getNumeric() const {
// 	return (this->numeric_);
// }

// debug
// void	Reply::printReply() const {
// 	std::cout << "[" << this->numeric_ << "]: [" \
// 		<< this->message_ << "]" << std::endl;
// }
