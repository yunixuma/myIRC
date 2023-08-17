fd_set read_fds;


fd_set read_fds;
int sockfd; // 仮定: sockfdは適切に初期化されている

FD_ZERO(&read_fds);           // read_fdsを初期化
FD_SET(sockfd, &read_fds);    // sockfdをread_fdsに追加

// selectを使用してアクティビティを監視
select(sockfd + 1, &read_fds, NULL, NULL, NULL);

if (FD_ISSET(sockfd, &read_fds)) {
    // sockfdが読み取りのためにアクティブである
}
