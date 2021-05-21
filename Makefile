# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/05/21 15:29:35 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	=  main.c keypress.c parsing.c render.c init.c raycasting.c sprite.c\
	texture.c

CC	= clang

FLAGS 	= -c -Wall -Wextra -Werror

INC	= -I cub3d.h -lm -lX11 -lXext -lmlx

LIB	= -lm -lX11 -lXext -lmlx

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
			$(CC) -o $(NAME) $(OBJS) $(LIB)
all : 		$(NAME)

clean :
			$(MAKE) clean -C ./libft
			rm -rf $(OBJS)

fclean : 	clean
			$(MAKE) fclean -C ./libft
			rm -rf $(NAME)

re : 		fclean all
