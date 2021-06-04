/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/04 16:19:46 by cassassi         ###   ########.fr       */
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

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_rgb(char *str)
{
	int	i;
	int	rgb[3];
	char	**color;

	color = ft_split(str, ',');
	if (!(color))
		return (-1);
	i = ft_tab_len(color); 
	if (i != 3)
	{
		ft_free_tab(color, i);
		return (-1);
	}
	while (i > 0)
	{
		i--;
		rgb[i] = ft_atoi(color[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_free_tab(color, 3);
			return (-1);
		}
	}
	ft_free_tab(color, 3);
	return (create_rgb(rgb[0], rgb[1], rgb[2]));
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
	if (i == 3 && ft_strncmp(info[0], "R", 2) == 0 && data->parse.res == 0)
		ret = ft_get_res(data, info);
	if (i == 2)
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

	gnl = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	ft_init_parse(data);
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		ret = ft_check_line(data, line);
		if (ret == -1)
		{
			printf("invalid data in .cub file\n");
			if (close(fd) < 0)
				printf("close error\n");
			return (-1);
		}
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	if (gnl < 0)
		printf("erreur gnl \n");
	if (close(fd) < 0)
		return (-1);
	return (0);
}
