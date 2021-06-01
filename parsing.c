/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/01 16:40:29 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../get_next_line/get_next_line.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_rgb(char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;
	char	**rgb;
	rgb = ft_split(str, ',');
	if (!(rgb))
		return (-1);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		ft_free_tab(rgb, 3);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	if (r < 0 || r > 255)
	{
		ft_free_tab(rgb, 3);
		return (-1);
	}
	g = ft_atoi(rgb[1]);
	if (g < 0 || g > 255)
	{
		ft_free_tab(rgb, 3);
		return (-1);
	}
	b = ft_atoi(rgb[2]);
	if (b < 0 || b > 255)
	{
		ft_free_tab(rgb, 3);
		return (-1);
	}
	ft_free_tab(rgb, 3);
	return (create_rgb(r, g, b));
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

	i = 0;
	info = ft_split(line, ' ');
	if (!(info))
		return (-1);
	while (info[i])
		i++;
	if (i == 3 && ft_strncmp(info[0], "R", 2) == 0 && data->parse.res == 0)
	{
		data->win.width = ft_atoi(info[1]);
		if (data->win.width <= 0 || data->win.width >= 1920)
		{
			ft_free_tab(info, i);
			return (-1);
		}
		data->win.height = ft_atoi(info[2]);
		if (data->win.height <= 0 || data->win.height >= 1080)
		{
			ft_free_tab(info, i);
			return (-1);
		}
		data->parse.res = 1;
		ft_free_tab(info, i);
	}
	else if (i == 2 && ft_strncmp(info[0], "EA", 3) == 0
			&& data->parse.east == 0)
	{
		data->tab[0] = ft_init_texture(data, info[1]);
		data->parse.east = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "WE", 3) == 0
			&& data->parse.west == 0)
	{
		data->tab[1] = ft_init_texture(data, info[1]);
		data->parse.west = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "NO", 3) == 0
			&& data->parse.north == 0)
	{
		data->tab[2] = ft_init_texture(data, info[1]);
		data->parse.north = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "SO", 3) == 0
			&& data->parse.south == 0)
	{
		data->tab[3] = ft_init_texture(data, info[1]);
		data->parse.south = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "S", 2) == 0
			&& data->parse.sprite == 0)
	{
		data->tab[4] = ft_init_texture(data, info[1]);
		data->parse.sprite = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "F", 2) == 0
			&& data->parse.floor == 0)
	{
		data->parse.floor_color = get_rgb(info[1]);
		if (data->parse.floor_color < 0)
		{
			ft_free_tab(info, i);
			return (-1);
		}
		data->parse.floor = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "C", 2) == 0
			&& data->parse.ceil == 0)
	{
		data->parse.ceil_color = get_rgb(info[1]);
		if (data->parse.ceil_color < 0)
		{
			ft_free_tab(info, i);
			return (-1);
		}
		data->parse.ceil = 1;
		ft_free_tab(info, i);
		return (0);
	}
	else
		printf("parsing tbc\n");
	return (0);
}

int	ft_parse_cub(char *file, t_data *data)
{
	int fd;
	int buf;
	int ret;
	char *line;

	buf = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("erreur open\n");
		return (1);
	}
	ft_init_parse(data);
	while (buf > 0)
	{
		buf = get_next_line(fd, &line);
		ret = ft_check_line(data, line);
		if (ret == -1)
		{
			printf("invalid data in .cub file\n");
			return (-1);
		}
		free(line);
		line = NULL;
	}
	if (ret == 0)
	{
		free(line);
		line = NULL;
	}
	if (ret < 0)
		printf("erreur gnl \n");
	if ((ret = close(fd)) < 0)
	{
		printf("erreur close\n");
		return (1);
	}
	return (0);
}
