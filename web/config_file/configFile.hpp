# ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>


class Location
{
    public :
        int _autoindex;
        std::string  _name_Location;
        std::string  _root;
        int _upload;
        char *upload_path;
        char *index;
        char *_return;
        std::map<std::string, std::string> cgi;
        std::vector<std::string> _allow_methods;
        Location(std::string location);
};

class one_server
{
    public :
        int                                 listen;
        std::string                         _Host;
        std::string                         _server_name;
        std::string                          client_body_size;
        std::map<std::string, std::string>  error_page;
        
        std::vector<class Location>         _location;
    
        one_server(std::string string_to_pars);
};

class manyServer
{
    public :
        std::vector<class one_server> _name_server;
        int _count_server;
        std::string *par;
        manyServer();
        manyServer(std::string file);

};
#endif