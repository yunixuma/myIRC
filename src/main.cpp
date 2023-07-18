#include "server.h"

using namespace std;
int main() {
    Server server(8080); // ポート8080でサーバーを起動します。

    if (!server.start()) {
        std::cerr << "Failed to start the server" << std::endl;
        return 1;
    }

    server.run(); // サーバーを実行します。

    return 0;
}

