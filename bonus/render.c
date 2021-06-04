/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:03:42 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/01 18:37:42 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pix_to_img(t_img *img, int x, int y, int color)
{
	char    *pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int 	ft_render_rect(t_img *img, t_rect rect)
{
	int i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			ft_pix_to_img(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	ft_render(t_data *data)
{
	int i;
	t_cross cross;
	double deltax;
	double deltay;

	i = 0;
	if (data->win_ptr == NULL)
		return (1);
	ft_render_rect(&data->img, (t_rect){0, 0, data->win.width, (data->win.height/2), data->parse.ceil_color});
	ft_render_rect(&data->img, (t_rect){0, (data->win.height/2), data->win.width, (data->win.height/2), data->parse.floor_color});
	while (i < data->win.width)
	{
		ft_ray_lenght(i, data, &cross);
		data->wall_size = floor(GRID * data->win.dpp / cross.dist);
		ft_texture(data, ft_get_tex(data), cross, i);
		i++;
	}
	i = 0;
	while(i < data->nbs)
	{
		if (data->spritel[i].is_visible == 1)
		{
			deltax = data->Px - data->spritel[i].coord.x;
			deltay = data->Py - data->spritel[i].coord.y;
			data->spritel[i].angle = (atan(fabs(deltay / deltax)) * (180 / PI));
			if (deltax < 0 && deltay >= 0)
				data->spritel[i].angle = 0 + data->spritel[i].angle;
			else if (deltax >= 0 && deltay >= 0)
				data->spritel[i].angle = 180 - data->spritel[i].angle;
			else if (deltax >= 0 && deltay < 0)
				data->spritel[i].angle = 180 + data->spritel[i].angle;
			else
				data->spritel[i].angle = 360 - data->spritel[i].angle;
			data->spritel[i].dist = hypot(deltax, deltay);
			data->spritel[i].size = floor(GRID * data->win.dpp / data->spritel[i].dist);
		}
		i++;
	}
	ft_sort_sprite(data);
	i = 0;
	while (i < data->nbs)
	{
		if (data->spritel[i].is_visible == 1)
		{
			ft_sprite(data, i);
			data->spritel[i].is_visible = 0;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}
