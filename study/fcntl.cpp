// fcntlを使った簡単な実装例

// #include <fcntl.h>
// //...
// int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
// //...

// // Set the socket to non-blocking mode
// int flags = fcntl(socket_fd, F_GETFL, 0);
// fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);
// //...
// つまり、socket_fdは一般的なファイルディスクリプタ（fd）であり、その背後にあるリソースがネットワークソケットであるという点で特殊です