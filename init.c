/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:47:59 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 14:59:59 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_arg(int argc, char**argv)
{
	int i;
	int j;
	int fd;
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
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	ft_init_parse(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
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

int	ft_init_data(t_data *data, int fd)
{
	data->Px = 0;
	data->Py = 0;
	data->dir = -1;
	data->hit = 0;
	data->parsing = 0;
	data->mapi.size_y = 0;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (-1);
	if (ft_parse_cub(data, fd) < 0)
		return (-1);
	ft_init_win(data);
	ft_init_map(data);
	return (0);
}

void	ft_init_win(t_data *data)
{	
	data->win.width = WIN_WIDTH;
	data->win.height = WIN_HEIGHT;
	data->win.dpp = ((data->win.width/2) / (tan((FOV/2)*DEG)));
	data->win.sub_ray_angle = (FOV / data->win.width);
}

void	ft_init_player(t_data *data, char dir, int x)
{
	if (dir == 'E')
		data->dir = 0;
	else if (dir == 'N')
		data->dir = 90;
	else if (dir == 'W')
		data->dir = 180;
	else
		data->dir = 270;
	data->mapi.player.x = x;
	data->mapi.player.y = data->mapi.size_y;
	data->Px = (data->mapi.player.x / GRID) + (GRID/2);
	data->Py = (data->mapi.player.y / GRID) + (GRID/2);
}

void	ft_init_map(t_data *data)
{
	int i;
	int j;
	int initmap[MAPY][MAPX] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
                                   {1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1},
                                   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
                                   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
	j = 0;
	while (j < MAPX)
	{
		i = 0;
		while (i < MAPY)
		{
			data->map[i][j] = initmap[i][j];
			i++;
		}
		j++; 
	}
}
