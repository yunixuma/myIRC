/* 
   channel nameをチェックする		isChannelName();
   channel nameが既にあるか調べる。	isExistChannel();
   ある。既に参加しているか調べる。		isJoinedChannel();
   ない。チャンネルを作成する。			createChannel();
   チャンネルクラスに、クライアントデータを追加する。	addClient();

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
クライアントがチャネルに参加できるかどうかは、クライアントが接続しているローカルサーバのみがチェックします；
他のすべてのサーバは、他のサーバからコマンドを受け取ると、そのユーザを自動的にチャネルに追加します。

オプションとして、コントロールG(^GまたはASCII 7)をセパレータとして、チャネルのユーザーステータス(チャネルモード「O」、「o」、「v」)をチャネル名に付加することができる。
そのようなデータは、メッセージがサーバーから受信されたものでない場合、無視されなければならない[MUST]。
このフォーマットはクライアントに送ってはならない[MUST NOT]。

JOINコマンドはすべてのサーバーにブロードキャストされなければならない[MUST]。そうすることで、各サーバーはチャンネルに参加しているユーザーがどこにいるかを知ることができる。
これにより、PRIVMSGとNOTICEメッセージをチャンネルに最適に配送することができる。
*/
#ifndef JOIN_HPP
# define JOIN_HPP

class Join {
	public:

};

#endif