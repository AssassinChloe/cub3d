/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:47:59 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/21 10:33:57 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_init_parse(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->parse.tex[i] = 0;
		data->tex[i].xpm.img = NULL;
		data->parse.tex_path[i] = NULL;
		i++;
	}
	data->parse.ceil = 0;
	data->parse.ceil_color = 0;
	data->parse.floor = 0;
	data->parse.floor_color = 0;
	data->parse.map = 0;
	data->map = NULL;
}

int	ft_init_data(t_data *data, char *file)
{
	data->pos.x = 0;
	data->pos.y = 0;
	data->dir = -1;
	data->hit = 0;
	data->parsing = 0;
	data->floodfill = 0;
	data->mapi.size_x = 0;
	data->mapi.size_y = 0;
	data->mapi.player.x = 0;
	data->mapi.player.y = 0;
	data->wall_size = 1;
	ft_init_keys(data);
	ft_init_parse(data);
	ft_init_win(data);
	if (ft_parse_cub(data, file) < 0)
		return (-1);
	if (ft_init_mlx(data) < 0)
		return (ft_error(-6));
	return (0);
}

int	ft_init_mlx(t_data *data)
{	
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (-1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win.width,
			data->win.height, "my window");
	if (!data->win_ptr)
		return (-1);
	data->mlx_img.img = mlx_new_image(data->mlx_ptr, data->win.width,
			data->win.height);
	if (data->mlx_img.img == NULL)
		return (-1);
	data->mlx_img.addr = mlx_get_data_addr(data->mlx_img.img,
			&data->mlx_img.bpp, &data->mlx_img.line_len,
			&data->mlx_img.endian);
	if (data->mlx_img.addr == NULL)
		return (-1);
	return (0);
}

void	ft_init_win(t_data *data)
{	
	data->win.width = WIN_WIDTH;
	data->win.height = WIN_HEIGHT;
	data->win.dpp = ((data->win.width / 2) / (tan((FOV / 2) * DEG)));
	data->win.sub_ray_angle = (FOV / data->win.width);
	data->mlx_img.img = NULL;
	data->win_ptr = NULL;
	data->mlx_ptr = NULL;
}

void	ft_init_player(t_data *data, char dir, int x)
{
	if (dir == 'E')
		data->dir = 0;
	else if (dir == 'N')
		data->dir = 90;
	else if (dir == 'W')
		data->dir = 180;
	else
		data->dir = 270;
	data->mapi.player.x = x;
	data->mapi.player.y = data->mapi.size_y;
	data->pos.x = (data->mapi.player.x * GRID) + (GRID / 2);
	data->pos.y = (data->mapi.player.y * GRID) + (GRID / 2);
}
