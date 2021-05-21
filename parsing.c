/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/21 17:46:01 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../get_next_line/get_next_line.h"

int	ft_parse_cub(char *file, t_data *data)
{
	int fd;
	int ret;
	char *line;
	int	i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("erreur open\n");
		return (1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("gnl success %d ", i);
		printf("line =\"%s\"\n\n", line);
		free(line);
		line = NULL;
		i++;
	}
	if (ret == 0)
	{
		printf("gnl success %d ", i);
		printf("line =\"%s\"\n\n", line);
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
