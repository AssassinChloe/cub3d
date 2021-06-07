/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/07 14:56:55 by cassassi         ###   ########.fr       */
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

int	ft_parse_cub(t_data *data, int fd)
{
	int gnl;
	int ret;
	char *line;
	int	is_map;
	int map_y;
	char **map;
	gnl = 1;
	is_map = 0;
	map_y = 0;
	map = (char **)malloc(sizeof(char *) * 20);
	ft_init_parse(data);
	while (gnl > 0)
	{
		is_map = 2;
		gnl = get_next_line(fd, &line);
		is_map = ft_check_if_map(data, line, map_y);
		if (is_map == 0 && data->parse.map == 0)
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
		else if (is_map == 1)
		{
			data->parse.map = 1;
			map[map_y] = ft_strdup(line);
			map_y++;
		}
		else
		{
			printf("something went wrong");
			free(line);
			line = NULL;
			if (close(fd) < 0)
				printf("close error\n");
			return (-1);
		}
		free(line);
		line = NULL;
	}
	map[map_y] = NULL;
	map_y = 0;
	while (map[map_y] != NULL)
	{
		printf("%s\n", map[map_y]);
		map_y++;
	}
	if (gnl < 0)
		printf("erreur gnl \n");
	if (close(fd) < 0)
		return (-1);
	return (0);
}

int 	ft_check_if_map(t_data *data, char *line, int y)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ' || line[i] == '0')
			i++;
		else if ((line[i] == 'W' || line[i] == 'S' || line[i] == 'E' ||
			  line[i] == 'N') && data->parse.map == 1)
		{
			if (data->dir < 0)
				ft_init_player(data, line[i], i, y);
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
