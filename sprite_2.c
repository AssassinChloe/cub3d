/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:36:03 by cassassi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/15 17:44:09 by cassassi         ###   ########.fr       */
=======
/*   Updated: 2021/05/11 12:30:53 by cassassi         ###   ########.fr       */
>>>>>>> feda2d0f43242c00106bdbe7eb610967d23d08cf
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_sprite(t_data *data, t_cross S, int i)
{	
	int	stripe;
<<<<<<< HEAD
	double ratio;
	double	ratio_w;
=======
	double ratio_h;
	double ratio_w;
>>>>>>> feda2d0f43242c00106bdbe7eb610967d23d08cf
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
<<<<<<< HEAD
	ratio = S.sprite[S.i].size / data->tab[4].height;
	ratio_w = GRID / data->tab[4].width;
	if (S.sprite[S.i].hit == 0 || S.sprite[S.i].hit == 1)
	{
		stripe = floor(((S.sprite[S.i].coord.y - (floor(S.sprite[S.i].coord.y / GRID) * GRID)) + (S.sprite[S.i].coord.x - (floor(S.sprite[S.i].coord.x / GRID) * GRID))) * ratio_w);
	/*	stripe = floor(S.sprite[S.i].coord.y - (floor(S.sprite[S.i].coord.y / GRID) * GRID));
	else
		 stripe = floor(S.sprite[S.i].coord.x - (floor(S.sprite[S.i].coord.x / GRID) * GRID));
	*/
=======
	ratio_h = S.sprite[S.i].size / data->tab[4].height;
	ratio_w = GRID / data->tab[4].width;
	stripe = floor(((S.sprite[S.i].coord.y - (floor(S.sprite[S.i].coord.y / GRID) * GRID)) + (S.sprite[S.i].coord.x - (floor(S.sprite[S.i].coord.x / GRID) * GRID))) / ratio_w);

>>>>>>> feda2d0f43242c00106bdbe7eb610967d23d08cf
		while (j < S.sprite[S.i].size && k < WIN_HEIGHT)
		{
			y = (int)(j / ratio_h);
			color = img_pix_get(&data->tab[4].img, stripe, y);
			if (color != 0)
				img_pix_put(&data->img, i, (start_h + k), color);
			j++;
			k++;
		}
	}
	return (0);
}
<<<<<<< HEAD

void	ft_visible_sprite()
=======
>>>>>>> feda2d0f43242c00106bdbe7eb610967d23d08cf
