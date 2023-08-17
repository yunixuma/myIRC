
read_fd
int i = FD_ISSET(sockfd_,&read_fds);
// FD_ISSET(sockfd_ , &read_fds); 
int new client_fd = accept(sockfd_, nullptr,nullptr,);
{
	clients_.push_back(client_fd)
}

// ; このチェックが真である場合、通常、その後のコードは accept 関数を使用して新しいクライアントの接続を受け入れ、その接続に関連する新しいファイルディスクリプタを取得することを期待しています。