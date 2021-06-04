/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/04 18:45:00 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_tab_len(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}

void	ft_free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

int	ft_check_line(t_data *data, char *line)
{
	char	**info;
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	info = ft_split(line, ' ');
	if (!(info))
		return (-1);
	while (info[i])
		i++;
	if (i == 2 )
		ret = ft_check_for_tex(data, info);
	ft_free_tab(info, i);
	return (ret);
}

int	ft_parse_cub(char *file, t_data *data)
{
	int fd;
	int gnl;
	int ret;
	char *line;
	int	is_map;
	int map_y;
	char **map;
	gnl = 1;
	is_map = 0;
	map_y = 0;
	map = (char **)malloc(sizeof(char *) * 50);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	ft_init_parse(data);
	while (gnl > 0 && is_map == 0)
	{
		gnl = get_next_line(fd, &line);
		is_map = ft_check_if_map(data, line);
		if (is_map == 0)
		{
			ret = ft_check_line(data, line);
			if (ret == -1)
			{
				printf("invalid data in .cub file\n");
				free(line);
				line = NULL;
				if (close(fd) < 0)
					printf("close error\n");
				return (-1);
			}
		}
		free(line);
		line = NULL;
	}
	while (gnl > 0 && is_map == 1)
	{
		map[map_y] = ft_strdup(line);
		printf("map %2d = %s\n", map_y, map[map_y]);
		gnl = get_next_line(fd, &line);
		is_map = ft_check_if_map(data, line);
		map_y++;

	}
	free(line);
	line = NULL;
	if (gnl < 0)
		printf("erreur gnl \n");
	if (close(fd) < 0)
		return (-1);
	return (0);
}

int 	ft_check_if_map(t_data *data, char *line)
{
	int	i;

	i = 0;
	data->dir = 90;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == 0)
			i++;
	/*	else if (line[i] == 'W' || line[i] == 'S' || line[i] == 'E' || line[i] == 'N')
		{
			if (data->dir < 0)
			{
				printf("set player dir here\n");
				data->dir = 90;
			}
			else
				return (-1);
			i++;
		}*/
		else
			return (0);
	}
	return (1);
}
