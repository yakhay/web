#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <istream>
#include <fcntl.h>
#include <stdio.h>
#include <vector>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket{
    public :
        Socket(int port, std::string ip);
        int getSocket();
    private :
        int socket_fd;

};

#endif