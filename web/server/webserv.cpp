#include "webserv.hpp"
#include "socketServer.hpp"

webserv::webserv(manyServer* servers)
{
    int i = 1;
    this->max_fds = 0;
    FD_ZERO(&read_fds);
    this->servers = servers;
    for (int i = 0; i < 4; i++)
    {
        std::cout << this->servers->_name_server[i]._Host << std::endl;
        Socket socket(this->servers->_name_server[i].listen, this->servers->_name_server[i]._Host);
        this->sockets.push_back(socket);
    }
    
}

void webserv::setReadSet(int socket, fd_set &set)
{
    FD_SET(socket, &set);
    if (socket > this->max_fds) // to do
        this->max_fds = socket;
    // std::cout << "max_fds : " << this->max_fds << std::endl;
    // std::cout << this->clients.size() << std::endl;
}

void webserv::proccessClient()
{
    fd_set read, write;
    FD_ZERO(&read);
    FD_ZERO(&write);
    int i = 0;
    while (i < this->sockets.size())
    {
        setReadSet(this->sockets[i].getSocket(), read);
        if (i < this->clients.size())
            setReadSet(this->clients[i].getClientSocket(), read);
        i++;
    }
}

void webserv::createClient(){
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int i = 0;
    FD_ZERO(&read_fds);
    for (size_t i = 0; i < sockets.size(); i++) {
        setReadSet(sockets[i].getSocket(), read_fds);
    }
    result = select(max_fds + 1, &read_fds, NULL, NULL, NULL);

    if (result < 0) {
        perror("select error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < sockets.size(); i++) {
        if (FD_ISSET(sockets[i].getSocket(), &read_fds)) {
            int client_socket = accept(sockets[i].getSocket(), (struct sockaddr *)&client_addr, &client_len);
            if (client_socket < 0)
                perror("accept error:");
            std::cout << "client accepted" << std::endl;
            Client client(client_socket, i);
            this->clients.push_back(client);
            std::cout << "client pushed " << this->clients.size() << std::endl;
        }
    }
}

void webserv::sendError(Client client, int err)
{
    std::cout << "Error : " << err << std::endl;
}

void webserv::deleteClient(Client client)
{
    close(client.getClientSocket());
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].getClientSocket() == client.getClientSocket())
        {
            clients.erase(clients.begin() + i);
            break;
        }
    }
}

void webserv::sendErrorAndRemove(Client client, int err)
{
    sendError(client, err);
    deleteClient(client);
}

int webserv::checkReqErrors(Client client,request req,int size)
{
    if (size < 0)
    {
        sendErrorAndRemove(client, 413);
        return 1;
    }
    if (req.get_method() != "GET" && req.get_method() != "POST" && req.get_method() != "DELETE")
    {
        sendErrorAndRemove(client, 405);
        return 1;
    }
    if (req.get_version() != "HTTP/1.1")
    {
        sendErrorAndRemove(client, 505);
        return 1;
    }
    std::cout << "hi from checkReqErrors" << std::endl;
    return 0;
}

int webserv::locationExist(std::string path, Client client)
{
    if (path == "/")
        return 1;
    int serverId = client.getIdServerConnectedTo();
    std::vector<Location> locations = servers->_name_server[serverId]._location;
    std::cout << "------------------------------" << std::endl;
    std::cout << "path : " << path << std::endl;
    path = path.substr(1);
    path = path.substr(0, path.find("/"));
    for (int i = 0; i < locations.size(); i++)
    {
    //    std::cout << path << " => " << locations[i]._name_Location.substr(1) << std::endl;
        if (path == locations[i]._name_Location.substr(1))
            return 1; 
    }
    std::cout << "------------------------------" << std::endl;
    return 0; 
}

int webserv::isAllowedTo(Client client, std::string path, std::string method)
{
    if (locationExist(path, client) == 0) // url == / or /feed
        return 1;
    std::cout << "im here" << std::endl;
    int serverId = client.getIdServerConnectedTo();
    std::vector<Location> locations = servers->_name_server[serverId]._location;
    std::cout << path << std::endl;
    path = path.substr(1);
    path = path.substr(0, path.find("/"));
    for (int i = 0; i < locations.size(); i++)
    {
        // std::cout << "method " << method << std::endl;
        // std::cout << "locations[i]._name_Location : " << locations[i]._name_Location << std::endl;
        // std::vector<std::string> allow_methods = locations[i]._allow_methods;
        // for (int j = 0; j < allow_methods.size(); j++)
        // {
        //     if (allow_methods[j] == method)
        //         return 1;
        // }
        // std::cout << "cutted path " << path << std::endl;
        // std::cout << "locations[i]._name_Location " << locations[i]._name_Location.substr(1) << std::endl;
        if (path == locations[i]._name_Location.substr(1))
        {
            std::cout << locations[i]._name_Location.substr(1) << std::endl;
            for (int j = 0; j < locations[i]._allow_methods.size(); j++)
            {
                std::cout << "locations[i]._allow_methods[j] : " << locations[i]._allow_methods[j] << std::endl;
                std::cout << "method : " << method << std::endl;
                if (locations[i]._allow_methods[j] == method)
                    return 1;
            }
        }
    }
    std::cout << "is not allowed to" << std::endl;
    return 0;
}


void webserv::runMethod(Client client, std::string path, request req)
{
    std::cout << "*********************" << std::endl;
    std::cout << "runMethod" << std::endl;
    if (req.get_method() == "GET" && isAllowedTo(client,path,"GET"))
    {
        std::cout << "GET" << std::endl;
        // call mafyouzi get method
    }
    // else if (req.get_method() == "POST" && isAllowedTo(client,path,"POST"))
    // {
    //     // call kamel post method
    // }
    // else if (req.get_method() == "DELETE" && isAllowedTo(client,path,"DELETE"))
    // {
    //     // call ana delete method
    // }
}



void webserv::manageClient()
{
    
    std::cout << "clients.size() : " << clients.size() << std::endl;
    for(int i = 0; i < clients.size();i++)
    {
        std::cout << "clients[i].getClientSocket() : " << clients[i].getClientSocket() << std::endl;
        if (FD_ISSET(clients[i].getClientSocket(), &read_fds) == false)
        {
            std::cout << "FD_ISSET" << std::endl;
            int RequestSize = recv(clients[i].getClientSocket(), clients[i].buffer, 65536, 0);
            if (RequestSize == -1)
                exit(1);
            clients[i].buffer[RequestSize] = '\0';
            std::cout << "RequestSize : " << RequestSize << std::endl;  
            clients[i].size = RequestSize;
            std::string tmp = clients[i].buffer;
            request req;
            if (req.parse_request(tmp))
            {
                std::cout << "haniiiiii" << std::endl;
                std::cout << "Request : " << req.get_method() << std::endl;
                /*
                try{
                    int body_size = req.getBodySize();
                }
                body size is not in the header
                */
                if (checkReqErrors(clients[i], req, req.get_body().length()))
                    continue;
                
                std::cout << "haniiiiii2" << std::endl;
                std::string path = req.get_path();
                runMethod(clients[i],path,req);
            }
        }
    }
}


void webserv::runServer()
{
    std::cout << this->sockets.size() << std::endl;
    while(1)
    {
        proccessClient();
        //std::cout << "proccessClient" << std::endl;
        createClient();
        manageClient();
    }
}