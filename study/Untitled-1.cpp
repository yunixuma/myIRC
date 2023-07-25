// Create a sockaddr_in structure and set the IP and port
struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(port_);

// Convert the IP from string format to a binary format
if(inet_pton(AF_INET, "192.168.1.5", &(serv_addr.sin_addr)) <= 0) {
    printf("\n inet_pton error occured\n");
    return 1;
}

// Bind the socket to the IP and port
if (bind(sockfd_, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    return false;
}
