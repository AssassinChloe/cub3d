/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:50:09 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/14 12:59:14 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_validity(t_data *data)
{
	int	x;
	int	y;

	data->floodfill = 0;
	ft_map_size(data);
	y = data->mapi.player.y;
	x = data->mapi.player.x;
	data->map[y][x] = '0';
	flood(data, x, y);
	if (data->floodfill < 0)
	{
		printf("invalid map\n");
		return (-1);
	}
	return (0);
}

void 	ft_map_size(t_data *data)
{
	int	len;
	int	i;

	i = 0;
	data->mapi.size_x = 0;
	while (i < data->mapi.size_y)
	{
		len = ft_strlen(data->map[i]);
		if (len > data->mapi.size_x)
			data->mapi.size_x = len;
		i++;
	}
}

void	flood(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || (data->map[y][x] != '1' && data->map[y][x] != '0'
				&& data->map[y][x] != 'X'))
		data->floodfill = -1;
	if (data->floodfill == -1)
		return ;
	if (data->map[y][x] == '0')
	{
		data->map[y][x] = 'X';
		flood(data, (x + 1), y);
		flood(data, (x - 1), y);
		flood(data, x, (y + 1));
		flood(data, x, (y - 1));
	}
}

void	ft_deal_with_is_map(t_data *data, char *line, int is_map)
{
	int	ret;

	ret = 0;
	if (is_map == 0 && data->parse.map == 0)
	{
		ret = ft_check_line(data, line);
		if (ret == -1)
			data->parsing = -1;
	}
	else if (is_map == 1)
	{
		data->parse.map = 1;
		data->map[data->mapi.size_y] = ft_strdup(line);
		data->mapi.size_y++;
		return ;
	}
	else
		data->parsing = -1;
	return ;
}

int 	ft_check_if_map(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0')
			i++;
		else if ((line[i] == 'W' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'N') && data->parse.map == 1)
		{
			if (data->dir < 0)
				ft_init_player(data, line[i], i);
			else
			{
				printf("multiple players\n");
				return (-1);
			}
			i++;
		}
		else
			return (0);
	}
	return (1);
}
