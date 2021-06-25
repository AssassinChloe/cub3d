/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:50:09 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/25 11:24:42 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_validity(t_data *data)
{
	int	x;
	int	y;
	int	i;

	data->floodfill = 0;
	i = 0;
	ft_map_size(data);
	y = data->mapi.player.y;
	x = data->mapi.player.x;
	data->map[y][x] = '0';
	ft_flood(data, x, y);
	if (data->floodfill < 0)
		return (ft_error(-5));
	while (i < data->mapi.size_y)
	{
		if ((int)ft_strlen(data->map[i]) < data->mapi.size_x)
			data->map[i] = ft_fill_the_blank(data, i);
		if (data->map[i] == NULL)
			return (ft_error(-1));
		i++;
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

void	ft_flood(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || (data->map[y][x] != '1' && data->map[y][x] != '0'
				&& data->map[y][x] != 'X'))
		data->floodfill = -1;
	if (data->floodfill == -1)
		return ;
	if (data->map[y][x] == '0')
	{
		data->map[y][x] = 'X';
		ft_flood(data, (x + 1), y);
		ft_flood(data, (x - 1), y);
		ft_flood(data, x, (y + 1));
		ft_flood(data, x, (y - 1));
	}
}

int	ft_deal_with_is_map(t_data *data, char *line, int is_map)
{
	if (is_map == 0 && data->parse.map == 0)
	{
		if (data->mapi.get_size == 0)
		{
			if (ft_check_line(data, line) < 0)
				return (-1);
		}
	}
	else if (is_map == 1)
	{
		data->parse.map = 1;
		if (data->mapi.get_size == 1)
		{
			data->map[data->mapi.size_y] = ft_strdup(line);
			if (data->map[data->mapi.size_y] == NULL)
				return (ft_error(4));
		}
		data->mapi.size_y++;
	}
	else
		return (-1);
	return (0);
}

int 	ft_check_if_map(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		return (ft_error_if_map(data));
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0')
			i++;
		else if ((line[i] == 'W' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'N') && data->parse.map == 1)
		{
			if (data->mapi.get_size == 0)
			{
				if (data->dir < 0)
					ft_init_player(data, line[i], i);
				else
					return (ft_error(-5));
			}
			i++;
		}
		else
			return (ft_error_if_map(data));
	}
	return (1);
}
