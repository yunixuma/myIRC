

bool start() {
        // Create a socket
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd_ < 0) {
            return false;
        }

        // Bind the socket to the port
        sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port_);

        if (bind(sockfd_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            return false;
        }

        // Listen for connections
        listen(sockfd_, 5);
		// 具体的には、listen(sockfd_, 5);というコードでは、システムが一度に保持できる、まだaccept()
		// によって受け付けられていない接続要求の最大数が5であることを示しています。この数を超えた接続要求が来た場合、新たな接続要求は拒否されます。

        // Set the socket to non-blocking
        fcntl(sockfd_, F_SETFL, O_NONBLOCK);

        running_ = true;
        return true;
    }

    void stop() {
        running_ = false;
    }

    void run() 
	{
        while (running_) {
            // Accept new client connections
            sockaddr_in cli_addr;
            socklen_t clilen = sizeof(cli_addr);
            int newsockfd = accept(sockfd_, (struct sockaddr *) &cli_addr, &clilen);

            // If a valid client connection was made, add it to the clients list
            if (newsockfd >= 0) {
                clients_.push_back(newsockfd);
            }

            // Handle client messages...
            // In a real implementation, we would use a non-blocking read and parse
            // the incoming messages according to the IRC protocol, but we'll skip that
            // for this simplified example.
        }
    }