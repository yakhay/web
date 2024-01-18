#include "webserv.hpp"

int Handle::driver(char *requested_data, int bytesreceived,int active_clt)
{
    request req;
    req.parse_request(requested_data);
    // std::cout << "Method: " << req.get_method() << std::endl;
    //std::cout << "Path: " << req.get_path() << std::endl;
    // std::cout << "Version: " << req.get_version() << std::endl;
    // std::cout << "body: " << req.get_body() << std::endl;
    if (req.get_method() == "GET")
    {
       const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
        
        // Send the response to the client using the active_clt parameter
        send(active_clt, response, strlen(response), 0);
    }
    return (1);
}