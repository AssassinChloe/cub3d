# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/06/24 15:46:24 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	=  main.c keypress.c parsing.c render.c init.c raycasting.c\
	raycasting_2.c texture.c parsing_texture.c keypress_utils.c\
	map.c utils.c error.c closing.c

CC	= clang

FLAGS 	= -c -Wall -Wextra -Werror

INC	= -I cub3d.h 

LIB	= -lm -lX11 -lXext -lmlx libft/libft.a

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C libft
			$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
			$(CC) -o $(NAME) $(OBJS) $(LIB)
all : 		$(NAME)

clean :
			$(MAKE) clean -C libft
			rm -rf $(OBJS)

fclean : 	clean
			$(MAKE) fclean -C libft
			rm -rf $(NAME)

re : 		fclean all
