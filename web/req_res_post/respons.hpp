#ifndef RESPONS_HPP
#define RESPONS_HPP

#include "macro.hpp"
#include <fstream>
#include "request.hpp"

class respons
{
private:
    std::pair<int, std::string> Status;
    std::string                 Body;
    std::map<std::string, std::string>  headers;
public:
    void    set_Date();
    void    set_Body(std::string body);
    void    set_header(std::string key, std::string value);
    respons();
    void    set_Status(std::pair<int, std::string> st);
    std::string prepare_respons();
    ~respons();
};

#endif