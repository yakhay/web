/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethod.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhay <yakhay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:40:54 by wbouwach          #+#    #+#             */
/*   Updated: 2024/01/12 16:51:16 by yakhay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETMETHOD_HPP
# define GETMETHOD_HPP

# include "../req_res_post/request.hpp"
# include "../req_res_post/respons.hpp"
# include "../req_res_post/post.hpp"
# include "../req_res_post/macro.hpp"

# include "../config_file/configFile.hpp"
# include <sys/stat.h>
# include <sstream>
# include <fstream>
#include <filesystem>
# include <sys/socket.h>
#include <fcntl.h>
#include <filesystem>


void get_method(request &req, manyServer *server, int newsockfd);
#endif