/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:50:09 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/11 19:13:33 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_validity(t_data *data, char **map)
{
	int	x;
	int	y;

	ft_map_size(data, map);
	y = data->mapi.player.y;
	x = data->mapi.player.x;
	if (flood(data, x, y, map) < 0)
	{
		printf("invalid map");
		return (-1);
	}
	return (0);
}

void 	ft_map_size(t_data *data, char **map)
{
	int	len;
	int	i;

	i = 0;
	data->mapi.size_x = 0;
	while (i < data->mapi.size_y)
	{
		len = ft_strlen(map[i]);
		if (len > data->mapi.size_x)
			data->mapi.size_x = len;
		i++;
	}
}

int	flood(t_data *data, int x, int y, char **map)
{
	if (x < 0 || x > data->mapi.size_x || y < 0 || y > data->mapi.size_y)
		return (-1);
	if ((int)map[y][x] == 48)
	{
		map[y][x] = map[y][x] + 40;
		if (flood(data, x + 1, y, map) < 0)
			return (-1);
		if (flood(data, x - 1, y, map) < 0)
			return (-1);
		if (flood(data, x, y + 1, map) < 0)
			return (-1);
		if (flood(data, x, y - 1, map) < 0)
			return (-1);
	}
	return (0);
}

char	*ft_deal_with_is_map(t_data *data, char *line, int is_map)
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
		data->mapi.size_y++;
		return (ft_strdup(line));
	}
	else
		data->parsing = -1;
	return (NULL);
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
