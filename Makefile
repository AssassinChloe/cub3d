# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 15:07:28 by cassassi          #+#    #+#              #
#    Updated: 2021/06/28 19:13:23 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

BNAME	= cub3D_bonus

SRCS	= main.c keypress.c parsing.c render.c init.c raycasting.c\
	  raycasting_2.c texture.c parsing_texture.c keypress_utils.c\
	  map.c utils.c error.c closing.c

BONUS	= keypress_utils_bonus.c main_bonus.c keypress_bonus.c\
	  parsing_bonus.c render_bonus.c init_bonus.c error_bonus.c\
	  raycasting_bonus.c raycasting_2_bonus.c texture_bonus.c map_bonus.c\
	  parsing_texture_bonus.c utils_bonus.c closing_bonus.c

CC	= clang

FLAGS 	= -Wall -Wextra -Werror

INC	= -I cub3d.h

BINC	= -I bonus/cub3d.h

LIB	= -lm -lX11 -lXext miniLibX/libmlx.a libft/libft.a

OBJSD	= mandatory/.obj/

OBJS	= $(addprefix $(OBJSD), $(SRCS:%.c=%.o))

BOBJSD	= bonus/.obj/

BOBJS 	= $(addprefix $(BOBJSD), $(BONUS:%.c=%.o))

all : 		$(NAME)

bonus :		$(BNAME)

clean :
			$(MAKE) clean -C libft
			$(MAKE) clean -C miniLibX
			rm -rf $(OBJSD) 

fclean : 	clean
			$(MAKE) fclean -C libft
			rm -f $(NAME)


$(NAME):	$(OBJS)
			$(MAKE) -C libft
			$(MAKE) -C miniLibX
			$(CC) -o $(NAME) $(OBJS) $(LIB)
	
$(BNAME):	$(BOBJS)
			$(MAKE) -C libft
			$(MAKE) -C miniLibX
			$(CC) -o $(BNAME) $(BOBJS) $(LIB) 

cleanbonus :	
			$(MAKE) clean -C libft
			$(MAKE) clean -C miniLibX
			rm -rf $(BOBJSD) 

fcleanbonus :	cleanbonus
			$(MAKE) fclean -C libft
			rm -f $(BNAME)

re : 		fclean all

rebonus	:	fcleanbonus bonus

$(BOBJSD)%.o:bonus/%.c
		@mkdir -p $(BOBJSD)
		$(CC) $(FLAGS) $(BINC) -o $@ -c $<
$(OBJSD)%.o:mandatory/%.c
		@mkdir -p $(OBJSD) 
		$(CC) $(FLAGS) $(INC) -o $@ -c $<

