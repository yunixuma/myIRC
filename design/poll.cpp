fd_set read_fds;
struct timeval timeout;

// ...

while (running_) {
  FD_ZERO(&read_fds);
  FD_SET(sockfd_, &read_fds);
  for (int client_fd : clients_) {
    FD_SET(client_fd, &read_fds);
  }

  timeout.tv_sec = 1; // 1秒タイムアウト
  timeout.tv_usec = 0;

select は複数のfdの（ソケット）を監視して
  int activity = select(FD_SETSIZE, &read_fds, nullptr, nullptr, &timeout);

  if (activity < 0 && errno != EINTR) {
    // エラー処理
  }

  if (activity > 0) {
    // 新しいクライアント接続の処理
    if (FD_ISSET(sockfd_, &read_fds)) {
      // ...
    }

    // 既存のクライアントからのメッセージの処理
    for (int client_fd : clients_) {
      if (FD_ISSET(client_fd, &read_fds)) {
        handleClientMessage(client_fd);
      }
    }
  }
}
