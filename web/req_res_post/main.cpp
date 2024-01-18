#include "request.hpp"
// #include "respons.hpp"
#include "post.hpp"


// #include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <cstring>
// #include <fstream>
#include <sys/types.h>
#include <fcntl.h>
int main(int c, char **v)
{
    // int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // if (server_socket == -1)
    // {
    //     std::cerr << "Error: Socket creation failed\n";
    //     return 1;
    // }

    // sockaddr_in server_address;
    // server_address.sin_family = AF_INET;       // IPv4
    // server_address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    // server_address.sin_port = htons(8080);    // Port to listen on (in network byte order)

    // if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    // {
    //     std::cerr << "Error: Binding failed\n";
    //     return 1;
    // }

    // if (listen(server_socket, 5) < 0) {
    //     std::cerr << "Error: Listen failed\n";
    //     return 1;
    // }

    // std::cout << "Server is listening on port 8080...\n";

    // int client_socket;
    // sockaddr_in client_address;
    // socklen_t client_addr_size = sizeof(client_address);
    // client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_size);
    // std::cout << "Connection established with a client\n";
    // if (client_socket < 0)
    // {
    //     std::cerr << "Error: Accept failed\n";
    //     return 1;
    // }
    // std::cout << "Connected to the server\n";
    // std::string req;

    int client_socket;
    client_socket = open("socket", O_RDONLY);
    size_t  size = 1024;
    char    buffer[size + 1];
    size_t  x;
    request var;
    std::cout<<"-------------"<<std::endl;
    try
    {
        do
        {
            memset(buffer, 0, size + 1);
            x = read(client_socket, buffer, size);
            if (var.parse_request(buffer))
            {
                std::cout<<var.get_body();
                if (var.get_method() == "POST")
                    post::post_request(var);
                // else if (var.get_method() == "GET")
                // else if (var.get_method() == "DELETE")
                // else
                //     throw (405);
            }
            // std::cout<<"version ==>"<<var.get_body()<<"$"<<std::endl;
        }while (x == size);
    }
    catch(int status)
    {
        std::cout<<"status : "<<status<<std::endl;
        // res.set_Status(std::pair<int, std::string>(status, "Bad request"));
    }
    std::cout<<"-------------"<<std::endl;
    // std::cout<<res.prepare_respons()<<std::endl;
    // close(client_socket);
    // close(server_socket);

    return 0;
}
