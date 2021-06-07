/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:05:58 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/07 14:56:34 by cassassi         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/get_next_line.h"
# include "../libft/libft.h"

# define MLX_ERROR 1
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 60
# define PI 3.14159265
# define GRID 64 
# define DEG PI/180
# define MAPX 18
# define MAPY 11

typedef struct	s_parse
{
	int	tex[4];
	char	*tex_path[4];
	int	ceil;
	int	ceil_color;
	int	floor;
	int	floor_color;
	int	map;
}		t_parse;

typedef struct	s_window
{
	double	width;
	double 	height;
	double 	dpp;
	double 	sub_ray_angle;
}		t_window;

typedef struct	s_point
{
	double 	x;
	double 	y;
}		t_point;

typedef struct	s_cross
{
	t_point	cross;
	t_point	delta;
	double	dist;
}		t_cross;

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int	bpp;
	int	line_len;
	int	endian;
} 		t_img;

typedef struct	s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_rect;

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
	t_window win;
	double	Px;
	double	Py;
	int	dir;
	int	hit;
	int	map[MAPY][MAPX];
	double	wall_size;
	t_tex	tex[4];
	t_parse	parse;
} t_data;

int	ft_check_arg(int argc, char **argv);
int	ft_parse_cub(t_data *data, int fd);
void	ft_ray_lenght(int ray_nb, t_data *data, t_cross *cross);
void	ft_check_intersect_line(t_data *data, double r_a, t_cross *dil);
int	set_params_dil(t_data *data, double r_a, t_cross *dil);
void	ft_check_intersect_column(t_data *data, double r_a, t_cross *dic);
int	set_params_dic(t_data *data, double r_a, t_cross *dic);
int	ft_get_wall(t_data *data);
int	handle_keypress(int keysym, t_data *data);
int	ft_init_data(t_data *data, int fd);
void	ft_init_map(t_data *data);
void	ft_init_player(t_data *data, char dir, int x, int y);
int	img_pix_get(t_img *img, int x, int y);
t_tex	*ft_get_tex(t_data *data);
void	ft_pix_to_img(t_img *img, int x, int y, int color);
int	ft_texture(t_data *data, t_tex *tex, t_cross wall, int i);
int	ft_quit(t_data *data);
void	ft_init_texture(t_data *data);
int	ft_check_for_wall(t_data *data, int start_w, int l, int start_h, int i);
int	ft_render(t_data *data);
int	ft_render_rect(t_img *img, t_rect rect);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_init_parse(t_data *data);
void	ft_free_tab(char **tab, int i);
void	ft_init_win(t_data *data);
int	ft_set_tex(t_data *data, char **info);
int	ft_set_color(t_data *data, char **info);
int	ft_check_for_tex(t_data *data, char **info);
int	ft_get_res(t_data *data, char **info);
int	ft_tab_len(char **tab);
int	get_rgb(char *str);
void    ft_destroy(t_data *data);
void	ft_turn_right(t_data *data);
void	ft_turn_left(t_data *data);
void	ft_go_front(t_data *data, double delta_x, double delta_y);
void	ft_go_back(t_data *data, double delta_x, double delta_y);
void	ft_go_left(t_data *data, double delta_x, double delta_y);
void	ft_go_right(t_data *data, double delta_x, double delta_y);
int	ft_check_if_map(t_data *data, char *line, int y);
#endif
