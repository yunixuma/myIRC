/* 
RFC 2813 - Internet Relay Chat: Server Protocol
https://tex2e.github.io/rfc-translater/html/rfc2813.html

4.    Message Details
4.2.1 Join message

   Command: JOIN
Parameters: <channel>[ %x7 <modes> ] *( "," <channel>[ %x7 <modes> ] )


Numeric Replies:
ERR_NEEDMOREPARAMS		ERR_BANNEDFROMCHAN
ERR_INVITEONLYCHAN		ERR_BADCHANNELKEY
ERR_CHANNELISFULL		ERR_BADCHANMASK
ERR_NOSUCHCHANNEL		ERR_TOOMANYCHANNELS
ERR_TOOMANYTARGETS		ERR_UNAVAILRESOURCE
RPL_TOPIC

Examples:
:WiZ JOIN #Twilight_zone        ; JOIN message from WiZ

JOINコマンドは、クライアントが特定のチャネルのリスニングを開始するために使用します。
クライアントがチャネルに参加できるかどうかは、クライアントが接続しているローカルサーバのみがチェックします。
他のすべてのサーバは、他のサーバからコマンドを受け取ると、そのユーザを自動的にチャネルに追加します。

オプションとして、コントロールG(^GまたはASCII 7)をセパレータとして、
チャネルのユーザーステータス(チャネルモード「O」、「o」、「v」)をチャネル名に付加することができる。

[MUST]
そのようなデータは、メッセージがサーバーから受信されたものでない場合、無視されなければならない。
JOINコマンドはすべてのサーバーにブロードキャストされなければならない。
そうすることで、各サーバーはチャンネルに参加しているユーザーがどこにいるかを知ることができる。
これにより、PRIVMSGとNOTICEメッセージをチャンネルに最適に配送することができる。

[MUST NOT]
オプションとして、コントロールG(^GまたはASCII 7)をセパレータとして、
チャネルのユーザーステータス(チャネルモード「O」、「o」、「v」)をチャネル名に付加することができるが、
このフォーマットはクライアントに送ってはならない。

*/

#ifndef JOIN_HPP
# define JOIN_HPP

#include <iostream>
#include <vector>
#include <map>
#include "server.h"
#include "Channel.hpp"

class Channel;

class Join : public Server {
	public:
		// CONSTRUCTER
		Join();

		// METHOD
		// bool	joinChannel();
		bool	isChannelName(const std::string& name);												// channel nameが正しいか調べる。
		bool	isExistChannel(std::map<std::string, Channel *> channelList, const std::string& name); // channel nameが既にあるか調べる。
		bool	isJoinedChannel(int client, std::map<std::string, Channel *> channelList, const std::string& name);	// ある。既に参加しているか調べる。
		Channel*	createChannel(const std::string& name);	// ない。チャンネルを作成する。
		void	addClient(Channel& channel, int& client);		// チャンネルクラスに、クライアントデータを追加する。

		// DESTRUCTER
		~Join();

};

#endif
