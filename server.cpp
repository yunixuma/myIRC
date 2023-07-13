// ユーザー(User): ユーザーはIRCクライアントを使用してIRCサーバーに接続する個々の人々を指します。
// ユーザーは一つ以上のチャネルに参加し、
// 他のユーザーとメッセージを交換することができます。ユーザーは一般的にニックネームで識別され、パスワードで認証されます。

class User {
public:
    User(std::string username, std::string nickname, std::string password);
    std::string getUsername();
    std::string getNickname();
    bool checkPassword(std::string password);
    // その他の必要なメソッド

private:
    std::string username;
    std::string nickname;
    std::string password;
};

// オペレータ(Operator): オペレータは特殊な種類のユーザーであり、
// 特定のチャネルまたはサーバー全体の管理者としての権限を持っています。
// オペレータはチャネルのモードを設定したり、ユーザーをキックしたり（チャネルから強制的に退出させる）、新しいユーザーを招待したりする能力を持っています。
// これらの機能は通常のユーザーには利用できません。

class Operator : public User {
public:
    Operator(std::string username, std::string nickname, std::string password);
    // オペレータ特有の機能を追加
};

// クライアント(Client): IRCクライアントは、ユーザーがIRCサーバーと対話するためのソフトウェアまたはアプリケーションを指します。
// クライアントはサーバーに接続し、ユーザーにメッセージの送受信やチャネルの管理などの操作を可能にします。
// クライアントはユーザーのインターフェイスであり、サーバーとの通信を管理します。
class Client {
public:
    Client(int socket, User* user); 
    int getSocket();
    User* getUser();
    // その他の必要なメソッド

private:
    int socket;
    User* user;
};

// チャネル(Channel): チャネルはIRCの主要な概念であり、ユーザーがメッセージを交換する場所を提供します。
// チャネルはテーマや目的によって異なることが多く、
// 一つのサーバー上には多数のチャネルが存在します。ユーザーは複数のチャネルに参加することができ、
// メッセージは参加しているチャネルのメンバー全員に配信されます。
class Channel {
public:
    Channel(std::string name);
    std::string getName();
    void addUser(User* user);
    void removeUser(User* user);
    std::vector<User*> getUsers();
    // その他の必要なメソッド

private:
    std::string name;
    std::vector<User*> users;
};

// サーバー(Server): IRCサーバーは、クライアントが接続するための中心的なエンティティです。
// サーバーはユーザーからの接続要求を受け付け、ユーザーがチャネルに参加したり、他のユーザーとメッセージを交換したりするための基盤を提供します。
// サーバーは接続されている全てのクライアントを管理し、チャネル間でのメッセージ配信を行います。
// サーバーはまた、セキュリティと認証（ユーザーが正しいパスワードを提供しているかどうかを確認する等）を管理します。
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

class Server {
public:
    Server(int port) : port_(port), running_(false) {}

private:
    int port_;
    int sockfd_;
    bool running_;
    std::vector<int> clients_;
};




// クライアント(Client)、チャネル(Channel)、そしてユーザー(User)です。
// ここではオペレータ(Operator)も特別な種類のユーザーとして扱います。
// これらを表すための基本的なクラス設計を以下に示します。

// IRCクライアントからの接続要求を受け付け、クライアントとして追跡（Clientクラス）
// ユーザーとオペレーターの認証（UserおよびOperatorクラス）
// ユーザーのチャネルへの参加および退出（Channelクラス）
// ユーザー間でのメッセージの送受信（すべてのクラス）






