# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/06/04 17:36:30 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBFT	= ../../libft

SRCS	=  main.c keypress.c parsing.c render.c init.c raycasting.c\
	texture.c parsing_setup.c sprite.c\

CC	= clang

FLAGS 	= -c -Wall -Wextra -Werror

INC	= -I cub3d.h 

LIB	= -lm -lX11 -lXext -lmlx $(LIBFT)/libft.a

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT)
			$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
			$(CC) -o $(NAME) $(OBJS) $(LIB)
all : 		$(NAME)

clean :
			$(MAKE) clean -C $(LIBFT)
			rm -rf $(OBJS)

fclean : 	clean
			$(MAKE) fclean -C $(LIBFT)
			rm -rf $(NAME)

re : 		fclean all
