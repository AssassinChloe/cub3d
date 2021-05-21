# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/05/21 15:51:29 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	=  main.c keypress.c parsing.c render.c init.c raycasting.c sprite.c\
	texture.c get_next_line.c get_next_line_utils.c parsing.c

CC	= clang

FLAGS 	= -c -Wall -Wextra -Werror

INC	= -I cub3d.h get_next_line.h 

LIB	= -lm -lX11 -lXext -lmlx

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
			$(CC) -o $(NAME) $(OBJS) $(LIB)
all : 		$(NAME)

clean :
			rm -rf $(OBJS)

fclean : 	clean
			rm -rf $(NAME)

re : 		fclean all
