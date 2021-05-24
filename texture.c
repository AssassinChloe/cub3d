/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:15:18 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/24 17:33:13 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	ft_init_texture(t_data *data, char *path)
{
	t_tex tex;
       	tex.img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &tex.width, &tex.height);
	tex.img.addr = mlx_get_data_addr(tex.img.mlx_img, &tex.img.bpp, &tex.img.line_len, &tex.img.endian);
	return (tex);
}

t_tex	*ft_get_tex(t_data *data)
{
	if (data->hit == 0)
		return (&data->tab[0]);
	if (data->hit == 1)
		return (&data->tab[1]);
	if (data->hit == 2)
		return (&data->tab[2]);
	else 
	//if (data->hit == 3)
		return (&data->tab[3]);
	/*else
		return (&data->tab[5]);*/
}

int	img_pix_get(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len) + x * (img->bpp / 8)));
}

int ft_texture(t_data *data, t_tex *tex, t_cross wall, int i)
{	
	int	stripe;
	double ratio;
	int	start_h; 
	int	j;
	int 	y;
	int	k;

	k = 0;
	j = 0;
	start_h = ((WIN_HEIGHT/2) - (data->wall_size/2));
	if (start_h < 0)
	{
		j = -start_h;
		start_h = 0;
	}
	ratio = data->wall_size / tex->height;
	if (data->hit == 0 || data->hit == 1)	
		stripe = floor(wall.cross.y - (floor(wall.cross.y / GRID) * GRID));
	else
		stripe = floor(wall.cross.x - (floor(wall.cross.x / GRID) * GRID));
	while (j <= data->wall_size && k <= WIN_HEIGHT)
	{
		y = (int)(j / ratio);
		ft_pix_to_img(&data->img, i, (start_h + k), img_pix_get(&tex->img, stripe, y));
		j++;
		k++;
	}
	return (0);
}
