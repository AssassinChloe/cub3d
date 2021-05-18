/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:05:58 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/15 18:02:31 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <string.h>
# define MLX_ERROR 1

# ifndef WIN_WIDTH
#  define WIN_WIDTH  1000
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 800 
# endif
# define PI 3.14159265
# define GRID 64 
# define DEG_CONV PI/180
# define SKY_PIXEL 0x00BBE8FF
# define LEFT_PIXEL 0x005E6F6A
# define RIGHT_PIXEL 0x008B6F6A
# define BOT_PIXEL 0x007F6F6A
# define TOP_PIXEL 0x008D6F5A
# define FLOOR_PIXEL 0x001A6927
# define MAPX 13
# define MAPY 11

typedef struct	s_window
{
	double	width;
	double 	height;
	double 	fov_angle;
	double 	dpp;
	double 	sub_ray_angle;
}		t_window;

typedef struct	s_point
{
	double 	x;
	double 	y;
}		t_point;

typedef struct	s_sprite
{
	t_point	coord;
	int	is_visible;
	double	dist;
	double	size;
	double	angle;
}		t_sprite;

typedef struct		s_cross
{
	t_point		cross;
	t_point		delta;
	double		dist;
}			t_cross;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int	bpp;
	int	line_len;
	int	endian;
} t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
} t_rect;

typedef struct	s_tex
{
	int	width;
	int	height;
	t_img	img;
	char	*path;
}		t_tex;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int	cur_img;
	double	Px;
	double	Py;
	int	dir;
	int	hit;
	int	map[MAPY][MAPX];
	t_sprite spritel[(MAPY - 2) * (MAPX - 2)];
	int	nbs;
	double	wall_size;
	t_tex	tab[6];
} t_data;


void	ft_init_window(t_window *window);
void	ft_ray_lenght(t_window window, int ray_nb, t_data *data, t_cross *cross);
void	ft_check_intersect_line(t_data *data, double ray_angle, t_cross *A);
void	ft_check_intersect_column(t_data *data, double ray_angle, t_cross *B);
int	ft_get_wall(t_data *data);
int	handle_keypress(int keysym, t_data *data);
void	ft_init_data(t_data *data);
void	ft_init_map(t_data *data);
int	img_pix_get(t_img *img, int x, int y);
t_tex	*ft_get_tex(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
int	ft_texture(t_data *data, t_tex *tex, t_cross wall, int i);
int	ft_quit(t_data *data);
t_tex	ft_init_texture(t_data *data, char *relative_path);
int	ft_sprite(t_data *data, int i);
void	ft_sort_sprite(t_data *data);
#endif
