# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 16:04:06 by ael-hadd          #+#    #+#              #
#    Updated: 2022/09/11 16:40:05 by ael-hadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_containers


CFLAGS	=	-Wall -Werror -Wextra -std=c++98

HEADERS	=	vector.hpp map.hpp stack.hpp red_black.hpp algorithm.hpp \
			functional.hpp iterators.hpp type_traits.hpp set.hpp

all	:	./tests/main.cpp $(HEADERS)
	c++ $(CFLAGS) ./tests/main.cpp -D STL=0 -o $(NAME)

STL	:	./tests/main.cpp $(HEADERS)
	c++ $(CFLAGS) ./tests/main.cpp -D STL=1 -o stl_containers

vector:	./tests/vector.cpp vector.hpp
	c++ $(CFLAGS) ./tests/vector.cpp -D STL=0 -o vector && ./vector  > FT_vector
	c++ $(CFLAGS) ./tests/vector.cpp -D STL=1 -o vector && ./vector  > STL_vector
	diff STL_vector FT_vector


map:	./tests/map.cpp map.hpp
	c++ $(CFLAGS) ./tests/map.cpp -D STL=0 -o map && ./map  > FT_map
	c++ $(CFLAGS) ./tests/map.cpp -D STL=1 -o map && ./map  > STL_map
	diff STL_map FT_map
	
stack:	./tests/stack.cpp stack.hpp
	c++ $(CFLAGS) ./tests/stack.cpp -D STL=0 -o stack && ./stack  > FT_stack
	c++ $(CFLAGS) ./tests/stack.cpp -D STL=1 -o stack && ./stack  > STL_stack
	diff STL_stack FT_stack
	
set:	./tests/set.cpp set.hpp
	c++ $(CFLAGS) ./tests/set.cpp -D STL=0 -o set && ./set  > FT_set
	c++ $(CFLAGS) ./tests/set.cpp -D STL=1 -o set && ./set  > STL_set
	diff STL_set FT_set

clean:
	rm -rf FT_* STL_*

fclean:	clean
	rm -f $(NAME)
	rm -f vector map stack set

re	:	fclean all

.PHONY : all clean fclean re vector map stack set