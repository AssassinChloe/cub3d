/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/24 01:22:59 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../get_next_line/get_next_line.h"

int	ft_check_line(t_data *data, char *line)
{
	char	**info;
	int	i;

	i = 0;
	info = ft_split(line, ' ');
	while (info[i])
		i++;
	if (ft_strncmp(info[0], "R", 2) == 0 && i == 3)
	{
		data->win.width = ft_atoi(info[1]);
		if (data->win.width <= 0 || data->win.width >= 1000 )
			return (-1);
		data->win.height = ft_atoi(info[2]);
		if (data->win.height <= 0 || data->win.height >= 900)
			return (-1);
	}
	return (0);
}

int	ft_parse_cub(char *file, t_data *data)
{
	int fd;
	int ret;
	char *line;
	int	i;

	i = 0;
	ret = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("erreur open\n");
		return (1);
	}
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		ft_check_line(data, line);
		free(line);
		line = NULL;
		i++;
	}
	if (ret == 0)
	{
		free(line);
		line = NULL;
	}
	if (ret < 0)
	{
		printf("erreur gnl %d\n", i);
	}

	if ((ret = close(fd)) < 0)
	{
		printf("erreur close\n");
		return (1);
	}
	data->test = i;
	return (0);
}
