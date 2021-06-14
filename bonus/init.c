/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:47:59 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/03 17:10:17 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_arg(int argc, char**argv)
{
	int i;
	int j;
	if (argc != 2)
	{
		printf("mauvais nombre d'argument\n");
		return (-1);
	}
	j = 0;
	while (argv[1][j])
		j++;
	i = ft_strncmp(".cub", (argv[1] + (j - 4)), 5); 
	if (i != 0)
	{
		printf("mauvais argument\n");
		return (-1);
	}
	return (0);
}

void	ft_init_parse(t_data *data)
{
	int i;

	i = 0;
	data->parse.res = 0;
	while (i < 5)
	{
		data->parse.tex[i] = 0;
		data->parse.tex_path[i] = NULL;
		i++;
	}
	data->parse.ceil = 0;
	data->parse.ceil_color = 0;
	data->parse.floor = 0;
	data->parse.floor_color = 0;
	data->parse.map = 0;
}

int	ft_init_data(t_data *data, char *arg)
{
	data->Px = 200;
	data->Py = 200;
	data->dir = 0;
	data->hit = 0;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (-1);
	mlx_get_screen_size(data->mlx_ptr, &data->win.screenw, &data->win.screenh);
	if (ft_parse_cub(arg, data) < 0)
		return (-1);
	ft_init_win(data);
	ft_init_map(data);
	return (0);

}

void	ft_init_win(t_data *data)
{
	data->win.fov_angle = 60;
	data->win.dpp = ((data->win.width/2) / (tan((data->win.fov_angle/2)*DEG_CONV)));
	data->win.sub_ray_angle = (data->win.fov_angle / data->win.width);
	
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