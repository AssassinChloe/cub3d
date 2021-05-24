/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/24 17:52:22 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../get_next_line/get_next_line.h"

void	ft_free_info(char **info, int i)
{
	while (i >= 0)
	{
		free(info[i]);
		i--;
	}
	free(info);
}

int	ft_check_line(t_data *data, char *line, t_parse *parse)
{
	char	**info;
	t_tex	tex[5];
	int	i;
	int	j;

	i = 0;
	info = ft_split(line, ' ');
	if (!(info))
		return (-1);
	while (info[i])
	{
		printf("i : %d, %s\n", i, info[i]);
		i++;
	}
	if (i == 3 && ft_strncmp(info[0], "R", 2) == 0)
	{
		if (parse->res == 1)
			return (-1);
		data->win.width = ft_atoi(info[1]);
		if (data->win.width <= 0 || data->win.width >= 1000 )
			return (-1);
		data->win.height = ft_atoi(info[2]);
		if (data->win.height <= 0 || data->win.height >= 900)
			return (-1);
		parse->res = 1;
		ft_free_info(info, i);
	}
	else if (i == 2 && ft_strncmp(info[0], "EA", 3) == 0 && parse->east == 0)
	{
		parse->ea = ft_strdup(info[1]);
		parse->east = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "WE", 3) == 0 && parse->west == 0)
	{
		parse->we = ft_strdup(info[1]);
		parse->west = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "NO", 3) == 0 && parse->north == 0)
	{
		parse->no = ft_strdup(info[1]);
		parse->north = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "SO", 3) == 0 && parse->south == 0)
	{
		parse->so = ft_strdup(info[1]);
		parse->south = 1;
		ft_free_info(info, i);
		return (0);
	}
	else if (i == 2 && ft_strncmp(info[0], "S", 2) == 0 && parse->sprite == 0)
	{
		parse->sp = ft_strdup(info[1]);
		parse->sprite = 1;
		ft_free_info(info, i);
		return (0);
	}
	else
	{
		printf("parsing tbc\n");
	}
	if (parse->south == 1 && parse->east == 1 && parse->west == 1 && parse->north == 1 && parse->sprite == 1)
	{
		tex[0] = ft_init_texture(data, parse->ea);
		free (parse->ea);
		tex[1] = ft_init_texture(data, parse->we);
		free (parse->we);
		tex[2] = ft_init_texture(data, parse->no);
		free (parse->no);
		tex[3] = ft_init_texture(data, parse->so);
		free (parse->so);
		tex[4] = ft_init_texture(data, parse->sp);
		free (parse->sp);
		j = 0;
		while (j < 5)
		{
			data->tab[j] = tex[j];
			j++;
		}
		parse->south = 2;
	}
	return (0);
}

int	ft_parse_cub(char *file, t_data *data, t_parse *parse)
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
	ft_init_parse(parse);
	while (buf > 0)
	{
		buf = get_next_line(fd, &line);
		ret = ft_check_line(data, line, parse);
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
