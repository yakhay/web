#include "request.hpp"

std::string request::get_method() const
{
    return (this->method);
}

std::string request::get_path() const
{
    return (this->path);
}

std::string request::get_version() const
{
    return (this->version);
}

std::string request::get_body() const
{
    return (this->body);
}

std::string request::get_header(const std::string& key) const
{
    try
    {
        return (headers.at(key));
    }
    catch(const std::exception& e)
    {
        return ("");
    }
}

bool    request::check_path(std::string url)
{
    if (url.length() >= URL_MAX)
        return (false);
    for (size_t i = 0; i < url.length(); i++)
        if (!std::string(URL_CHARACTERS).find(url[i]))
            return (false);
    return (true);
}

bool    request::check_method(std::string method)
{
    if (method.empty())
        return (false);
    return (true);
}

void    request::request_line_parse(std::string req_line)
{
    size_t      ispace;
    std::string method;

    ispace = req_line.find(" ");
    if (ispace == std::string::npos)
        throw (400); // ERROR METHOD TOO LONG AND (PATH & VERSION) NOT FOUND
    method = req_line.substr(0, ispace);
    if (!check_method(method))
        throw (400); // ERROR METHOD IS EMTY OR TOO LONG
    this->method = method;
    req_line = req_line.substr(ispace);
    req_line = req_line.substr(req_line.find_first_not_of(" "));
    //------------------------------
    std::string path;

    ispace = req_line.find(" ");
    if (ispace == std::string::npos)
        throw (400); // ERROR VERSION NOT FOUND LONG
    path = req_line.substr(0, ispace);
    std::cout<<"path : "<<path<<std::endl;
    if (!check_path(path))
        throw (400); // ERROR PATH IS EMTY OR CONTENT NOT ALLOWED CHARACTER OR TOO LONG
    this->path = path;
    req_line = req_line.substr(ispace);
    req_line = req_line.substr(req_line.find_first_not_of(" "));
    //---------------------------------
    std::string version;

    version = req_line.substr(0, req_line.find(" "));
    if (version != HTTP_VERSION)
        throw (400);
    this->version = version;
}

void    request::headers_parse(std::string header)
{
    std::string key;
    std::string value;
    size_t      colone;

    colone = header.find(HEDER_SEPARATOR);
    if (colone == std::string::npos)
        throw (400); // ERROR ":" NOT FOUND
    key = header.substr(0, colone);
    value = header.substr(colone + strlen(HEDER_SEPARATOR));
    // std::cout<<"key ="<<key<<"|value ="<<value<<std::endl;
    if (key.empty())
        throw (400); // ERROR KEY OF HEADER IS WRONG
    if (value.empty())
        throw (400); // ERROR VALUE OF HEADER IS WRONG
    this->headers[key] = value;
}

bool    request::parse_request(std::string buffer)
{
    std::string line;
    size_t      start_body;
    size_t      end_line;

    if (this->start_read)
        return (this->body = buffer, this->start_read);
    start_body = buffer.find(BODY_SEPARATOR);
    if (start_body != std::string::npos)
    {
        this->body = buffer.substr(start_body + strlen(BODY_SEPARATOR));
        buffer = buffer.substr(0, start_body + strlen(LINE_SEPARATOR));
        this->start_read = true;
    }
    while ((end_line = buffer.find(LINE_SEPARATOR)) != std::string::npos)
    {
        line = this->rest + buffer.substr(0, end_line);
        if (this->index_line == 0)
            this->request_line_parse(line);
        else
            this->headers_parse(line);
        buffer = buffer.substr(end_line + strlen(LINE_SEPARATOR));
        this->index_line++;
        this->rest = "";
    }
    this->rest = buffer;
    return (this->start_read);
}