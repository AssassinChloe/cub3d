/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:15:18 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/17 18:05:50 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->tex[i].xpm.img = mlx_xpm_file_to_image(data->mlx_ptr,
				data->parse.tex_path[i],
				&data->tex[i].width,
				&data->tex[i].height);
		if (data->tex[i].xpm.img == NULL)
			return (ft_error(5));
		data->tex[i].xpm.addr = mlx_get_data_addr(data->tex[i].xpm.img,
				&data->tex[i].xpm.bpp,
				&data->tex[i].xpm.line_len,
				&data->tex[i].xpm.endian);
		if (data->tex[i].xpm.addr == NULL)
			return (ft_error(5));
		i++;
	}
	return (0);
}

t_tex	*ft_get_tex(t_data *data)
{
	if (data->hit == 0)
		return (&data->tex[0]);
	if (data->hit == 1)
		return (&data->tex[1]);
	if (data->hit == 2)
		return (&data->tex[2]);
	else
		return (&data->tex[3]);
}

int	img_pix_get(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len) + x * (img->bpp / 8)));
}

static int	ft_get_stripe(t_data *data, t_cross *wall)
{
	int	stripe;

	if (data->hit == 0 || data->hit == 1)
		stripe = floor(wall->cross.y - (floor(wall->cross.y / GRID) * GRID));
	else
		stripe = floor(wall->cross.x - (floor(wall->cross.x / GRID) * GRID));
	return (stripe);
}

int	ft_texture(t_data *data, t_tex *tex, t_cross wall, int i)
{
	int	stripe;
	int	start_h;
	int	j;
	int	y;
	int	k;

	k = 0;
	j = 0;
	start_h = ((data->win.height / 2) - (data->wall_size / 2));
	if (start_h < 0)
	{
		j = -start_h;
		start_h = 0;
	}
	stripe = ft_get_stripe(data, &wall);
	while (j <= data->wall_size && k <= data->win.height)
	{
		y = (int)(j / (data->wall_size / tex->height));
		ft_pix_to_img(&data->mlx_img, i, (start_h + k),
			img_pix_get(&tex->xpm, stripe, y));
		j++;
		k++;
	}
	return (0);
}
