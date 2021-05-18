/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:36:03 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/15 17:44:09 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_sprite(t_data *data, int i)
{	
	int	stripe;
	double ratio;
	double	ratio_w;
	int	start_h; 
	int	start_w;
	int	j;
	int 	y;
	int	k;
	int	l;
	int 	x;
	int color;

	stripe = 0;
	l = 0;
	start_w = 0;
	ratio = data->spritel[i].size / data->tab[4].height;
	ratio_w = data->spritel[i].size / data->tab[4].width;
	l = data->dir - data->spritel[i].angle;
	if (l >= 60)
		l = data->dir + data->spritel[i].angle - 360;
	start_w = ((WIN_WIDTH / 60) * (l + 30)) - (data->spritel[i].size / 2);
	l = 0;
	if (start_w < 0)
	{
		stripe = -start_w;
		start_w = 0;	
	}
	while (stripe < data->spritel[i].size && l < WIN_WIDTH)
	{
		x = (int)(stripe / ratio_w);
		k = 0;
		j = 0;	
		start_h = (int)((WIN_HEIGHT/2) - (data->spritel[i].size/2));
		if (start_h < 0)
		{
			j = -start_h;
			start_h = 0;
		}
		while (j < data->spritel[i].size && k < WIN_HEIGHT)
		{
			y = (int)(j / ratio);
			color = img_pix_get(&data->tab[4].img, x, y);
			if (color != 0)
				img_pix_put(&data->img, (start_w + l) , (start_h + k), color);
			j++;
			k++;
		}
		stripe++;
		l++;
	}
	return (0);
}

