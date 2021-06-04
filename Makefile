# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/06/04 14:22:12 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	=  main.c keypress.c parsing.c render.c init.c raycasting.c\
	texture.c parsing_setup.c\
       ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c\
       ../libft/ft_split.c ../libft/ft_atoi.c ../libft/ft_strncmp.c ../libft/ft_strdup.c ../libft/ft_strlen.c 

CC	= clang

FLAGS 	= -c -Wall -Wextra -Werror

INC	= -I cub3d.h ../get_next_line/get_next_line.h 

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
