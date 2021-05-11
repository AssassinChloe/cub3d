/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:36:03 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/11 12:30:53 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_sprite(t_data *data, t_cross S, int i)
{	
	int	stripe;
	double ratio_h;
	double ratio_w;
	int	start_h; 
	int	j;
	int 	y;
	int	k;
	int color;

	k = 0;
	j = 0;
	start_h = (int)((WIN_HEIGHT/2) - (S.sprite[S.i].size/2));
	if (start_h < 0)
	{
		j = -start_h;
		start_h = 0;
	}
	ratio_h = S.sprite[S.i].size / data->tab[4].height;
	ratio_w = GRID / data->tab[4].width;
	stripe = floor(((S.sprite[S.i].coord.y - (floor(S.sprite[S.i].coord.y / GRID) * GRID)) + (S.sprite[S.i].coord.x - (floor(S.sprite[S.i].coord.x / GRID) * GRID))) / ratio_w);

		while (j < S.sprite[S.i].size && k < WIN_HEIGHT)
		{
			y = (int)(j / ratio_h);
			color = img_pix_get(&data->tab[4].img, stripe, y);
			if (color != 0)
				img_pix_put(&data->img, i, (start_h + k), color);
			j++;
			k++;
		}
	return (0);
}
