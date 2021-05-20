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
	double	stripe;
	double ratio;
	double	ratio_w;
	int	start_h; 
	double	start_w;
	int	j;
	int 	y;
	int	k;
	int	l;
	int 	x;
	int color;
	int color2;
	double deltaa;

	stripe = 0;
	l = 0;
	start_w = 0;
	ratio = data->spritel[i].size / data->tab[4].height;
	ratio_w = data->spritel[i].size / data->tab[4].width;
	deltaa = data->dir - data->spritel[i].angle;
	if (deltaa >= 60)
		deltaa = deltaa - 360;
	if (deltaa <= -60)
		deltaa = 360 + deltaa;
	start_w = ((WIN_WIDTH / 60) * (deltaa + 30))  - (data->spritel[i].size / 2);
	printf("I = %d : start_x %.1f, dir %d, s_ang %.1f, l %.2f\n", i, start_w, data->dir, data->spritel[i].angle, deltaa);
	l = 0;
	if (start_w < 0)
	{
		stripe = -start_w;
		start_w = 0;	
	}
	while (stripe < data->spritel[i].size && (start_w + l) <= WIN_WIDTH)
	{
		x = (int)(stripe / ratio_w);
		k = 0;
		j = 0;	
		start_h = (((WIN_HEIGHT/2) - (data->spritel[i].size/2) + 10));
		if (start_h < 0)
		{
			j = -start_h;
			start_h = 15;
		}
		color2 = img_pix_get(&data->img, (start_w +l), ((start_h - 15) + k));
		if (color2 == SKY_PIXEL)
		{
			while (j < data->spritel[i].size && k < (WIN_HEIGHT - 15))
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
		else
		{
			stripe++;
			l++;
		}
	}
	return (0);
}

void	ft_sort_sprite(t_data *data)
{
	int i;
	int j;
	t_sprite swp;

	i = 0;
	while (i < data->nbs)
	{
		j = 0;
		while (j < data->nbs)
		{
			if (data->spritel[i].dist > data->spritel[j].dist)
			{
				swp = data->spritel[i];
				data->spritel[i] = data->spritel[j];
				data->spritel[j] = swp;
			}
			j++;
		}
		i++;
	}


}
