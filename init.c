/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:47:59 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/24 17:41:13 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_arg(int argc, char**argv)
{
	int i;
	int j;
	if (argc > 3 || argc < 2)
	{
		printf("mauvais nombre d'argument\n");
		return (1);
	}
	j = 0;
	while (argv[1][j])
		j++;
	i = ft_strncmp(".cub", (argv[1] + (j - 4)), 5); 
	if (argc == 3 && i == 0)
		i = ft_strncmp("--save", argv[2], 7);
	if (i != 0)
	{
		printf("mauvais argument\n");
		return (1);
	}
	return (0);
}

void	ft_init_parse(t_parse *parse)
{
	parse->res = 0;
	parse->south = 0;
	parse->west = 0;
	parse->east = 0;
	parse->north = 0;
	parse->ceil = 0;
	parse->floor = 0;
	parse->sprite = 0;
	parse->map = 0;

}
void	ft_init_data(t_data *data)
{
	data->Px = 197;
	data->Py = 294;
	data->dir = 235;
	data->hit = 0;
	data->mlx_ptr = mlx_init();
	data->win.width = WIN_WIDTH;
	data->win.height = WIN_HEIGHT;
	data->win.fov_angle = 60;
	data->win.dpp = ((data->win.width/2) / (tan((data->win.fov_angle/2)*DEG_CONV)));
	data->win.sub_ray_angle = (data->win.fov_angle / data->win.width);
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
