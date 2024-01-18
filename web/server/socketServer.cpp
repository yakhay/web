#include "socketServer.hpp"
#include "webserv.hpp"

Socket::Socket(int port, std::string ip)
{
    int val = 1;
    int port_int = port;
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port_int);
    if((this->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("socket error:");
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1)
        perror("setsocketopt :");
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    if((bind(this->socket_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
        perror("binding error:");
    if (listen(this->socket_fd, 40) != 0)
        perror("listening error:");
}

int Socket::getSocket()
{
    return this->socket_fd;
}