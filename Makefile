# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 16:04:06 by ael-hadd          #+#    #+#              #
#    Updated: 2022/08/16 16:16:46 by ael-hadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_containers

HEADERS	=	vector.hpp map.hpp stack.hpp

SRCS		=	test.cpp

all	:	$(SRCS) $(HEADERS)
	c++ -Wall -Werror -Wextra -std=c++98 $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean:	clean

re	:	fclean all

.PHONY : all clean fclean re