#include "./Reply.hpp"
#include "../parser/Parser.hpp"
#include "../debug/debug.hpp"

const std::string	Reply::delimiter_ = "\r\n";

// CONSTRUCTOR & DESTRUCTOR
// Reply::Reply() {}
// Reply::~Reply() {}

const std::string&	Reply::getDelimiter() {
	return (Reply::delimiter_);
}

std::string	Reply::rplFromName(const std::string& from) {
	try {
		std::string	message = ":" + from + " ";
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplCmdToName(int num, const std::string& toName) {
	try {
		std::stringstream	ss;
		ss << num;
		// std::string	message = ss.str() + " " + toName + " :";
		std::string	message = ss.str() + " " + toName + " ";
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplYourHost(const std::string& toName, const std::string& serverName, const std::string& version) {
	try {
		std::string	message = "002 " + toName + " :Your host is " + serverName + ", running version " + version;
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplCreated(const std::string& toName, const time_t& createdDate) {
	try {
		std::string	date = std::asctime(std::localtime(&(createdDate)));
		if (!date.empty() && date[date.size() - 1] == '\n') {
			date.erase(date.size() - 1);
		}
		std::string	message = "003 " + toName + " :This server was created " + date;
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplMyInfo(const std::string& toName, const Info& info) {
	try {
		std::string	message = "004 " + toName + " :" + info.getServerName() + " " + info.getVersion() + " " + info.getUserModes() + " " +  info.getChannelModes();
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}


std::string	Reply::rplWelcome(const Info& info, const User& user) {
	try {
		std::string	message = "001 " + user.getNickName() + " :Welcome to the Internet Relay Network " + user.getPrefixName();
		message += Reply::delimiter_;
		message += Reply::rplFromName(info.getServerName());
		message += Reply::rplYourHost(user.getPrefixName(), info.getServerName(), info.getVersion());
		message += Reply::rplFromName(info.getServerName());
		message += Reply::rplCreated(user.getPrefixName(), info.getCreatedDate());
		message += Reply::rplFromName(info.getServerName());
		message += Reply::rplMyInfo(user.getPrefixName(), info);
		message += Reply::rplFromName(user.getPrefixName());
		message += "NICK :" + user.getNickName() + Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplUModeIs(int num, const std::string& toName, const User& user) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		if (user.getModes() & kOperator) {
			if (message.size() > 0) {
				message += " ";
			}
			message += "+o";
		}
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

// 324	RPL_CHANNELMODEIS	<channel> <mode> <mode params>
std::string	Reply::rplChannelModeIs(int num, const std::string& toName, const Channel& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel.getName() + " +";
		if (channel.getModes() & kInviteOnly) {
			message += "i";
		}
		if (channel.getModes() & kKeySet) {
			message += "k";
		}
		if (channel.getModes() & kLimit) {
			message += "l";
		}
		if (channel.getModes() & kRestrictTopicSetting) {
			message += "t";
		}
		if (channel.getModes() & kKeySet) {
			message += " " + channel.getKey();
		}
		if (channel.getModes() & kLimit) {
			std::stringstream	ss;
			ss << channel.getLimit();
			message += " " + ss.str();
		}
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplNoTopic(int num, const std::string& toName, const std::string& channel) {
	try {
		// std::string	message = "331 " + channel + " :No topic is set";
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " :No topic is set";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplTopic(int num, const std::string& toName, const std::string& channel, const std::string& topic) {
	try {
		// std::string	message = "332 " + channel + " :" + topic;
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " " + topic;
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplInviting(int num, const std::string& toName, const std::string& channel, const std::string& nickName) {
	try {
		// std::string	message = "341 " + channel + " " + nickName;
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " " + nickName;
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

// 353	RPL_NAMREPLY	"( "=" / "*" / "@" ) <channel> :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )"
std::string	Reply::rplNamReply(int num, const std::string& toName, const Channel& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		if (channel.getName()[0] == '#') {
			// message += "= " + channel.getName() + " :";
			message += "= " + channel.getName() + " :";
		}
		for (std::vector<User*>::const_iterator it = channel.getMembers().begin(); it != channel.getMembers().end(); ++it) {
			if (channel.isOperator((*it)->getNickName())) {
				message += "@" + (*it)->getNickName() + " ";
			} else {
				message += (*it)->getNickName() + " ";
			}
		}
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

// 366	RPL_ENDOFNAMES	"<channel> :End of NAMES list"
std::string	Reply::rplEndOfNames(int num, const std::string& toName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName) + channel + " :End of NAMES list" + Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::rplYourOper(int num, const std::string& toName, const std::string& nickName) {
	try {
		// std::string	message = "381 " + nickName + " :You are now an IRC operator";
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " :You are now an IRC operator";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNoSuchNick(int num, const std::string& toName, const std::string& nickName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " :No such nick/channel";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNoSuchServer(int num, const std::string& toName, const std::string& serverName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += serverName + " :No such server";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNoSuchChannel(int num, const std::string& toName, const std::string& channelName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channelName + " :No such channel";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errCanNotSendToChan(int num, const std::string& toName, const std::string& channelName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channelName + " :Cannot send to channel";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNoOrigin(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "No origin specified";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNoRecipient(int num, const std::string& toName, const std::string& command) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "No recipient given (" + command + ")";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNoTextToSend(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "No text to send";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errUnknownCommand(int num, const std::string& toName, const std::string& command) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += command + " :Unknown command";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}
std::string	Reply::errNoNickNameGiven(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "No nickname given";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errErroneusNickName(int num, const std::string& toName, const std::string& nickName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " :Erroneous nickname";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNickNameInUse(int num, const std::string& toName, const std::string& nickName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " :Nickname is already in use";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errUserNotInChannel(int num, const std::string& toName, const std::string& nickName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " " + channel + " :They aren't on that channel";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNotOnChannel(int num, const std::string& toName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " :You're not on that channel";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errUserOnChannel(int num, const std::string& toName, const std::string& nickName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " " + channel + " :is already on channel";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNotRegistered(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "You have not registered";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errNeedMoreParams(int num, const std::string& toName, const std::string& command) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += command + " :Not enough parameters";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errAlreadyRegistered(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "Unauthorized command (already registered)";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errPasswordMisMatch(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "Password incorrect";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errKeySet(int num, const std::string& toName, const std::string& nickName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " " + channel + " :Channel key already set";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errChannelIsFull(int num, const std::string& toName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " :Cannot join channel (+l)";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errUnknownMode(int num, const std::string& toName, const std::string& mode, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += mode + " :is unknown mode char to me for " + channel;
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errInviteOnlyChan(int num, const std::string& toName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " :Cannot join channel (+i)";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errBadChannelKey(int num, const std::string& toName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " :Cannot join channel (+k)";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

// 477	ERR_NOCHANMODES	"<channel> :Channel doesn't support modes"
std::string	Reply::errNoChanModes(int num, const std::string& toName, const std::string& nickName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += nickName + " " + channel + " :Channel doesn't support modes";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errChanOprivsNeeded(int num, const std::string& toName, const std::string& channel) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += channel + " :You're not channel operator";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errRestricted(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "Your connection is restricted!";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errUModeUnknownFlag(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "Unknown MODE flag";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

std::string	Reply::errUsersDontMatch(int num, const std::string& toName) {
	try {
		std::string	message = Reply::rplCmdToName(num, toName);

		message += "Cannot change mode for other users";
		message += Reply::delimiter_;
		return (message);
	} catch (const std::exception& e) {
		debugPrintErrorMessage(e.what());
		return ("");
	}
}

// std::string	Reply::createMessage(int num, const User& user, const Info& info, const ParsedMsg& parsedMsg) {
// 	if (num <= 0) {
// 		return ("");
// 	}
// 	try {
// 		std::string	msg;
// 		if (num == kRPL_WELCOME) {
// 			msg += this->rplFromName(info.getServerName());
// 			msg += this->rplWelcome(info, user);
// 		} else if (num < 100  || (num >= 200 && num < 400)) {
// 			if (num == kRPL_UMODEIS) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->rplUModeIs(kRPL_UMODEIS, user.getNickName(), user);
// 			} else if (num == kRPL_CHANNELMODEIS) {
// 				msg += this->rplFromName(info.getServerName());
// 				if (parsedMsg.getParams().size() > 2) {
// 					msg += this->rplChannelModeIs(kRPL_CHANNELMODEIS, user.getNickName(), parsedMsg.getParams()[0].getValue(), parsedMsg.getParams()[1].getValue()[1], parsedMsg.getParams()[2].getValue());
// 				} else {
// 					msg += this->rplChannelModeIs(kRPL_CHANNELMODEIS, user.getNickName(), parsedMsg.getParams()[0].getValue(), parsedMsg.getParams()[1].getValue()[1], "");
// 				}
// 			} else if (num == kRPL_NOTOPIC) {
// 				// TOPIC
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->rplNoTopic(kRPL_NOTOPIC, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kRPL_TOPIC) {
// 				// JOIN, TOPIC
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->rplTopic(kRPL_TOPIC, user.getNickName(), parsedMsg.getParams()[0].getValue(), parsedMsg.getParams()[1].getValue());
// 			} else if (num == kRPL_INVITING) {
// 				// INVITE
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->rplInviting(kRPL_INVITING, user.getNickName(), parsedMsg.getParams()[1].getValue(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kRPL_YOUREOPER) {
// 				// OPER
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->rplYourOper(kRPL_YOUREOPER, user.getNickName(), user.getNickName());
// 			}
// 		} else if (num >= 400 && num < 600) {
// 			if (num == kERR_NOSUCHNICK) {
// 				// PRIVMSG, INVITE
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoSuchNick(kERR_NOSUCHNICK, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_NOSUCHSERVER) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoSuchServer(kERR_NOSUCHSERVER, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_NOSUCHCHANNEL) {
// 				// JOIN, KICK, PART
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoSuchChannel(kERR_NOSUCHCHANNEL, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_NOORIGIN) {
// 				// PONG
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoOrigin(kERR_NOORIGIN, user.getNickName());
// 			} else if (num == kERR_NORECIPIENT) {
// 				// NOTICE, PRIVMSG
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoRecipient(kERR_NORECIPIENT, user.getNickName(), parsedMsg.getCommand());
// 			} else if (num == kERR_NOTEXTTOSEND) {
// 				// NOTICE, PRIVMSG
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoTextToSend(kERR_NOTEXTTOSEND, user.getNickName());
// 			} else if (num == kERR_UNKNOWNCOMMAND) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errUnknownCommand(kERR_UNKNOWNCOMMAND, user.getNickName(), parsedMsg.getCommand());
// 			} else if (num == kERR_NONICKNAMEGIVEN) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoNickNameGiven(kERR_NONICKNAMEGIVEN, user.getNickName());
// 			} else if (num == kERR_ERRONEUSNICKNAME) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errOneUsNickName(kERR_ERRONEUSNICKNAME, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_NICKNAMEINUSE) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNickNameInUse(kERR_NICKNAMEINUSE, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_USERNOTINCHANNEL) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errUserNotInChannel(kERR_USERNOTINCHANNEL, user.getNickName(), user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_NOTONCHANNEL) {
// 				msg += this->rplFromName(info.getServerName());
// 				// TODO(hnoguchi): INVITEコマンドの場合、parsedMsg.getParams()[1].getValue()がchannel名
// 				// msg += "442 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :You're not on that channel";
// 				// msg += "442 " + user.getNickName() + " :" + parsedMsg.getParams()[0].getValue() + " :You're not on that channel";
// 				msg += this->errNotOnChannel(kERR_NOTONCHANNEL, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_USERONCHANNEL) {
// 				// INVITE
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errUserOnChannel(kERR_USERONCHANNEL, user.getNickName(), user.getNickName(), parsedMsg.getParams()[1].getValue());
// 			} else if (num == kERR_NOTREGISTERED) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNotRegistered(kERR_NOTREGISTERED, "*");
// 			} else if (num == kERR_NEEDMOREPARAMS) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNeedMoreParams(kERR_NEEDMOREPARAMS, user.getNickName(), parsedMsg.getCommand());
// 			} else if (num == kERR_ALREADYREGISTRED) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errAlreadyRegistered(kERR_ALREADYREGISTRED, user.getNickName());
// 			} else if (num == kERR_PASSWDMISMATCH) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errPasswordMisMatch(kERR_PASSWDMISMATCH, user.getNickName());
// 			} else if (num == kERR_KEYSET) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errKeySet(kERR_KEYSET, user.getNickName(), user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_CHANNELISFULL) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errChannelIsFull(kERR_CHANNELISFULL, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_UNKNOWNMODE) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errUnknownMode(kERR_UNKNOWNMODE, user.getNickName(), parsedMsg.getParams()[1].getValue(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_INVITEONLYCHAN) {
// 				// JOIN
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errInviteOnlyChan(kERR_INVITEONLYCHAN, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_BADCHANNELKEY) {
// 				// JOIN
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errBadChannelKey(kERR_INVITEONLYCHAN, user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_NOCHANMODES) {
// 				// MODE(channel), TOPIC
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errNoChanModes(kERR_NOCHANMODES, user.getNickName(), user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_CHANOPRIVSNEEDED) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errChanOprivsNeeded(kERR_CHANOPRIVSNEEDED, user.getNickName(), user.getNickName(), parsedMsg.getParams()[0].getValue());
// 			} else if (num == kERR_RESTRICTED) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errRestricted(kERR_RESTRICTED, user.getNickName());
// 			} else if (num == kERR_UMODEUNKNOWNFLAG) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errUModeUnknownFlag(kERR_UMODEUNKNOWNFLAG, user.getNickName());
// 			} else if (num == kERR_USERSDONTMATCH) {
// 				msg += this->rplFromName(info.getServerName());
// 				msg += this->errUsersDontMatch(kERR_USERSDONTMATCH, user.getNickName());
// 			}
// 		}
// 		return (msg);
// 	} catch (const std::exception& e) {
// 		debugPrintErrorMessage(e.what());
// 		return ("");
// 	}
// }
