#include "respons.hpp"

respons::respons()
{
    this->Status = std::pair<int, std::string>(200, "OK");
    set_header(SERVER, SERVER_NAME);
}

void    respons::set_header(std::string key, std::string value)
{
    this->headers[key] = value;
}

void    respons::set_Date()
{
    time_t now = time(NULL);
    struct tm *gmNow = gmtime(&now);

    char dateStr[100];
    strftime(dateStr, sizeof(dateStr), "%a, %d %b %Y %H:%M:%S GMT", gmNow);
    set_header(DATE, dateStr);
}

void    respons::set_Body(std::string body)
{
    this->Body = body;
    set_header(CONTENT_LENGTH, std::to_string(this->Body.length()));
}

void    respons::set_Status(std::pair<int, std::string> st)
{
    std::string     line;
    std::fstream    error_page(std::string("./error_pages/error").append(std::to_string(st.first)).append(".html").c_str());
    this->Status = st;
    if (!error_page.is_open())
    {
        std::cout<<"ERRoooooor"<<std::endl;
        return ;
    }
    while (!error_page.eof())
    {
        std::getline(error_page, line);
        this->Body.append(line + LINE_SEPARATOR);
    }
    set_header(CONTENT_TYPE, "text/html");
    set_header(CONTENT_LENGTH, std::to_string(this->Body.length()));
}

std::string respons::prepare_respons()
{
    std::string respons;

    //respens line
    respons = HTTP_VERSION;
    respons += " " + std::to_string(this->Status.first);
    respons += " " + this->Status.second;
    //heders
    set_Date();
    std::map<std::string, std::string>::iterator  it = this->headers.begin();
    std::map<std::string, std::string>::iterator  eit = this->headers.end();
    while (it != eit)
    {
        respons += std::string(LINE_SEPARATOR) + it->first + HEDER_SEPARATOR + it->second;
        it++;
    }
    //body
    respons += BODY_SEPARATOR + this->Body;
    return (respons);
}

respons::~respons(){}