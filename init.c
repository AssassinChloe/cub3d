/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:47:59 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/15 18:04:01 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_data(t_data *data)
{

	data->Px = 197;
	data->Py = 294;
	data->dir = 235;
	data->hit = 0;
	data->mlx_ptr = mlx_init();
	ft_init_map(data);

}

void	ft_init_map(t_data *data)
{
	int i;
	int j;
	int initmap[MAPY][MAPX] = {{1,1,1,1,1,1,1,1,1,1,1,1,1},
                                   {1,2,1,2,0,0,0,0,0,2,1,2,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,2,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,2,1,2,0,0,0,0,0,2,1,2,1},
                                   {1,1,1,1,1,1,1,1,1,1,1,1,1}};
	int k;
	j = 0;
	k = 0;
	while (j < MAPX)
	{
		i = 0;
		while (i < MAPY)
		{
			data->map[i][j] = initmap[i][j];
			if (data->map[i][j] == 2)
			{
				data->spritel[k].coord.x = (j * 64) + 32;
				data->spritel[k].coord.y = (i * 64) + 32;
				data->spritel[k].is_visible = 0;
				data->spritel[k].dist = -1;
				data->spritel[k].size = -1;
				k++;
			}
			i++;
		}
		j++; 
	}
	data->nbs = k;
}
