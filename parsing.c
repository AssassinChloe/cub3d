/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/31 16:49:14 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../get_next_line/get_next_line.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}


void	ft_free_info(char **info, int i)
{
	while (i >= 0)
	{
		free(info[i]);
		i--;
	}
	free(info);
}

int	ft_check_line(t_data *data, char *line)
{
	char	**info;
	char	**rgb;
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	info = ft_split(line, ' ');
	if (!(info))
		return (-1);
	while (info[i])
		i++;
	if (i == 3 && ft_strncmp(info[0], "R", 2) == 0 && data->parse.res == 0)
	{
		data->win.width = ft_atoi(info[1]);
		if (data->win.width <= 0 || data->win.width >= 1000 )
			return (-1);
		data->win.height = ft_atoi(info[2]);
		if (data->win.height <= 0 || data->win.height >= 900)
			return (-1);
		data->parse.res = 1;
		ft_free_info(info, i);
	}
	else if (i == 2 && ft_strncmp(info[0], "EA", 3) == 0
			&& data->parse.east == 0)
	{
		data->tab[0] = ft_init_texture(data, info[1]);
		data->parse.east = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "WE", 3) == 0
			&& data->parse.west == 0)
	{
		data->tab[1] = ft_init_texture(data, info[1]);
		data->parse.west = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "NO", 3) == 0
			&& data->parse.north == 0)
	{
		data->tab[2] = ft_init_texture(data, info[1]);
		data->parse.north = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "SO", 3) == 0
			&& data->parse.south == 0)
	{
		data->tab[3] = ft_init_texture(data, info[1]);
		data->parse.south = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "S", 2) == 0
			&& data->parse.sprite == 0)
	{
		data->tab[4] = ft_init_texture(data, info[1]);
		data->parse.sprite = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "F", 2) == 0
			&& data->parse.floor == 0)
	{
		rgb = ft_split(info[1], ',');
		if (!(rgb))
			return (-1);
		i = 0;
		while (rgb[i])
			i++;
		if (i != 3)
			return (-1);
		r = ft_atoi(rgb[0]);
		if (r < 0 || r > 255)
			return (-1);
		g = ft_atoi(rgb[1]);
		if (g < 0 || g > 255)
			return (-1);
		b = ft_atoi(rgb[2]);
		if (b < 0 || b > 255)
			return (-1);
		data->parse.floor_color = create_rgb(r, g, b);
		data->parse.floor = 1;
	}
	else if (i == 2 && ft_strncmp(info[0], "C", 2) == 0
			&& data->parse.ceil == 0)
	{
		rgb = ft_split(info[1], ',');
		if (!(rgb))
			return (-1);
		i = 0;
		while (rgb[i])
			i++;
		if (i != 3)
			return (-1);
		r = ft_atoi(rgb[0]);
		if (r < 0 || r > 255)
			return (-1);
		g = ft_atoi(rgb[1]);
		if (g < 0 || g > 255)
			return (-1);
		b = ft_atoi(rgb[2]);
		if (b < 0 || b > 255)
			return (-1);
		data->parse.ceil_color = create_rgb(r, g, b);
		data->parse.ceil = 1;
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
