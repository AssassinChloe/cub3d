/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:15:18 by cassassi          #+#    #+#             */
/*   Updated: 2021/04/20 20:51:52 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_wall(t_data *data)
{
	if (data->hit == 1)
		return (LEFT_PIXEL);
	if (data->hit == 2)
		return (RIGHT_PIXEL);
	if (data->hit == 3)
		return (BOT_PIXEL);
	if (data->hit == 4)
		return (TOP_PIXEL);
	return (0);
}

int	img_pix_get(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len) + x * (img->bpp / 8)));
}

int ft_texture(t_data *data, t_img tex, t_cross wall, int i)
{	
	int	stripe;
	double ratio;
	int	start_h; 
	int	j;
	int 	y;
	
	j = 0;
	start_h = (int)((WIN_HEIGHT/2) - (data->wall_size/2));
	if (start_h < 0)
	{
		start_h = 0;
		data->wall_size = WIN_HEIGHT;
	}
	ratio = data->wall_size / 64;
	if (data->hit == 1 || data->hit == 2)	
		stripe = floor((wall.cross.y - (floor(wall.cross.y / GRID) * GRID))/ratio) ;
	else
		stripe = floor((wall.cross.x - (floor(wall.cross.x / GRID) * GRID))/ratio) ;
	printf("hit %d, wall_cross x: %f, y: %f, stripe: %d", data->hit, wall.cross.x, wall.cross.y, stripe);	
	while (j < data->wall_size)
	{
		y = (int)(j / ratio);
		img_pix_put(&data->img, i, (start_h + j), img_pix_get(&tex, stripe, y));
		j++;
	}
	return (0);
}
