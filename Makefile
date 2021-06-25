# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/06/25 15:03:43 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= main.c keypress.c parsing.c render.c init.c raycasting.c\
	  raycasting_2.c texture.c parsing_texture.c keypress_utils.c\
	  map.c utils.c error.c closing.c

BONUS	= bonus/keypress_utils.c bonus/main.c bonus/keypress.c\
	  bonus/parsing.c bonus/render.c bonus/init.c bonus/error.c\
	  bonus/raycasting.c bonus/raycasting_2.c bonus/texture.c bonus/map.c\
	  bonus/parsing_texture.c bonus/utils.c  bonus/closing.c

CC	= clang

FLAGS 	= -c -Wall -Wextra -Werror

INC	= -I cub3d.h

BINC	= -I bonus/cub3d.h

LIB	= -lm -lX11 -lXext miniLibX/libmlx.a libft/libft.a

OBJS	= $(SRCS:.c=.o)

BOBJS	= $(BONUS:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C libft
			$(MAKE) -C miniLibX
			$(CC) $(FLAGS) $(INC) $(SRCS)
			$(CC) -o $(NAME) $(OBJS) $(LIB)
all : 		$(NAME)

clean :
			$(MAKE) clean -C libft
			$(MAKE) clean -C miniLibX
			rm -f $(OBJS) 

fclean : 	clean
			$(MAKE) fclean -C libft
			rm -rf $(NAME)

re : 		fclean all

bonus :		$(BOBJS)
			$(MAKE) -C libft
			$(MAKE) -C miniLibX
			$(CC) $(FLAGS) $(BINC) $(BONUS)
			$(CC) -o $(NAME) $(BOBJS) $(LIB)

cleanbonus :	
			$(MAKE) clean -C libft
			$(MAKE) clean -C miniLibX
			rm -f $(BOBJS) 

fcleanbonus :	cleanbonus
			$(MAKE) fclean -C libft
			rm -rf $(NAME)
rebonus	:	fcleanbonus bonus
