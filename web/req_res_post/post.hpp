#ifndef POST_HPP
#define POST_HPP

#include "macro.hpp"
#include <sys/time.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include "request.hpp"

class post
{
private:
    static std::string    create_file_name(const std::string& extension);
public:
    static void post_request(const request& req);
};

#endif