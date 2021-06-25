/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:05:58 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/25 14:53:07 by cassassi         ###   ########.fr       */
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

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 60
# define GRID 64 
# define DEG 0.01745329
# define SPEED 5 

typedef struct s_parse
{
	int		tex[4];
	char	*tex_path[4];
	int		ceil;
	int		ceil_color;
	int		floor;
	int		floor_color;
	int		map;
}		t_parse;

typedef struct s_window
{
	double	width;
	double	height;
	double	dpp;
	double	sub_ray_angle;
}		t_window;

typedef struct s_point
{
	double	x;
	double	y;
}		t_point;

typedef struct s_cross
{
	t_point	cross;
	t_point	delta;
	double	dist;
}		t_cross;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_rect;

typedef struct s_tex
{
	int		width;
	int		height;
	t_img	xpm;
	char	*path;
}		t_tex;

typedef struct s_map
{
	int		get_size;
	int		size_x;
	int		size_y;
	t_point	player;
}		t_map;

typedef struct s_key
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rot_left;
	int	rot_right;
}	t_key;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		mlx_img;
	t_window	win;
	t_point		pos;
	int			dir;
	int			hit;
	int			parsing;
	int			floodfill;
	double		wall_size;
	t_tex		tex[4];
	t_parse		parse;
	t_map		mapi;
	char		**map;
	t_key		key;
}	t_data;

int		ft_setup_params(t_data *data, int ac, char **av);
int		ft_check_arg(int argc, char **argv);
int		ft_init_data(t_data *data, char *file);
void	ft_init_keys(t_data *data);
void	ft_init_parse(t_data *data);
void	ft_init_win(t_data *data);
int		ft_parse_cub(t_data *data, char *file);
int		ft_parsing(t_data *data, char *line, char *file);
int		ft_check_if_map(t_data *data, char *line);
void	ft_init_player(t_data *data, char dir, int x);
int		ft_deal_with_is_map(t_data *data, char *line, int is_map);
int		ft_check_line(t_data *data, char *line);
int		ft_tab_len(char **tab);
int		ft_check_for_comas(char *str);
int		ft_check_cf(t_data *data, char *line, char **tab, int i);
int		ft_set_tex(t_data *data, char *info, int i);
int		ft_set_color(t_data *data, char **info);
int		ft_check_for_tex(t_data *data, char **info);
int		ft_get_rgb(char **str);
int		ft_check_config(t_data *data);
int		ft_check_map_validity(t_data *data);
void	ft_map_size(t_data *data);
void	ft_flood(t_data *data, int x, int y);
char	*ft_fill_the_blank(t_data *data, int y);
int		ft_init_mlx(t_data *data);
int		ft_init_texture(t_data *data);
int		ft_keypress(int keycode, t_data *data);
int		ft_keyrelease(int keycode, t_data *data);
void	ft_movement(t_data *data);
void	ft_rotate(t_data *data);
void	ft_move(t_data *data);
void	ft_lateral(t_data *data, double delta_x, double delta_y);
int		ft_render(t_data *data);
int		ft_render_rect(t_img *img, t_rect rect);
void	ft_ray_lenght(int ray_nb, t_data *data, t_cross *cross);
void	ft_init_t_cross(t_cross *ray);
void	ft_check_intersect_line(t_data *data, double r_a, t_cross *dil);
int		ft_set_params_dil(t_data *data, double r_a, t_cross *dil);
void	ft_check_intersect_column(t_data *data, double r_a, t_cross *dic);
int		ft_set_params_dic(t_data *data, double r_a, t_cross *dic);
void	ft_get_hit(t_data *data, double r_a, t_cross *d_i_l, t_cross *d_i_c);
int		ft_texture(t_data *data, t_tex *tex, t_cross wall, int i);
t_tex	*ft_get_tex(t_data *data);
int		ft_img_pix_get(t_img *img, int x, int y);
void	ft_pix_to_img(t_img *img, int x, int y, int color);
int		ft_error(int errnb);
void	ft_error_2(int errnb);
int		ft_parsing_error(int gnl);
int		ft_error_if_map(t_data *data);
int		ft_quit(t_data *data);
void	ft_free_tab(char **tab, int i);
int		ft_destroy(t_data *data);
void	ft_destroy_texture(t_data *data);
#endif
