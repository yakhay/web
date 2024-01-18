# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakhay <yakhay@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 22:08:42 by wbouwach          #+#    #+#              #
#    Updated: 2024/01/07 15:56:35 by yakhay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

SRC = configFile.cpp   ../get_method/main.cpp \
	../req_res_post/post.cpp ../req_res_post/request.cpp ../req_res_post/respons.cpp ../get_method/getMethod.cpp 
	
OBJ = $(SRC:.cpp=.o)

CPPFLAGS =  -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all