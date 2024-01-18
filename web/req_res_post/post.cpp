#include "post.hpp"

std::string    post::create_file_name(const std::string& extension)
{
    std::string     file_name;
    struct timeval  Now;

    // do
    // {
        gettimeofday(&Now, NULL);
        file_name = POST_PATH + std::to_string(Now.tv_sec) + "-" + std::to_string(Now.tv_usec) + "." + extension;
    // } while (access(file_name.c_str(), F_OK) == -1);
    return (file_name);
}

void post::post_request(const request& req)
{
    std::string content_type = req.get_header(CONTENT_TYPE);
    std::string transfer_encoding = req.get_header(TRANSFER_ENCODING);
    std::string extension = content_type.substr(content_type.find("/") + 1/*, content_type.find(";|,")*/);//iportant => multi extensions
    std::string file_name = create_file_name(extension);
    if (transfer_encoding == "chunked")
    {
        std::fstream    out(file_name, std::ios::out);
    }
    else if (!transfer_encoding.empty())
        throw (501);
    else if (!content_type.empty())
    {
        std::fstream    out(file_name, std::ios::out);
        out<<req.get_body();
    }
    else
        throw (400);
}