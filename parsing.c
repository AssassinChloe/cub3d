/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/21 14:37:23 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_line(t_data *data, char *line)
{
	char	**info;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	info = ft_split(line, ' ');
	if (!(info))
		return (ft_error(-1));
	while (info[i])
		i++;
	if (i == 2 )
		ret = ft_check_for_tex(data, info);
	ft_free_tab(info, i);
	return (ret);
}

int	ft_parse_cub(t_data *data, char *file)
{
	char	*line;
	int		i;

	data->mapi.get_size = 0;
	line = NULL;
	if (ft_parsing(data, line, file) < 0)
		return (-1);
	if (ft_check_config(data) < 0)
		return (-1);
	data->mapi.get_size = 1;
	data->parse.map = 0;
	data->map = (char **)malloc(sizeof(char *) * (data->mapi.size_y + 1));
	if (!data->map)
		return (ft_error(-1));
	data->mapi.size_y = 0;
	if (ft_parsing(data, line, file) < 0)
		return (-1);
	data->map[data->mapi.size_y] = NULL;
	if (ft_check_map_validity(data) < 0)
		return (-1);
	i = 0;
	while (data->map[i] != NULL)
		printf("%s\n", data->map[i++]);
	return (0);
}

int	ft_parsing(t_data *data, char *line, char *file)
{
	int	gnl;
	int	is_map;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_error(-2));
	gnl = 1;
	is_map = 0;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		if (data->parsing >= 0 && is_map >= 0)
		{
			is_map = ft_check_if_map(data, line);
			data->parsing = ft_deal_with_is_map(data, line, is_map);
		}
		free(line);
		line = NULL;
	}
	if (gnl < 0 || data->parsing < 0)
		return (ft_parsing_error(gnl));
	if (close(fd) < 0)
		return (ft_error(-3));
	return (0);
}

int	ft_check_config(t_data *data)
{
	int	i;

	i = 0;
	if (data->parse.ceil == 0 || data->parse.floor == 0)
		return (ft_error(-4));
	while (i < 4)
	{
		if (data->parse.tex[i] == 0)
			return (ft_error(-4));
		i++;
	}
	if (data->parse.map == 0)
		return (ft_error(3));
	if (data->dir < 0)
		return (ft_error(-9));
	return (0);
}

char	*ft_fill_the_blank(t_data *data, int y)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(data->mapi.size_x + 1);
	if (!(tmp))
		return (NULL);
	while (data->map[y][i])
	{
		tmp[i] = data->map[y][i];
		i++;
	}
	free(data->map[y]);
	data->map[y] = NULL;
	while (i < data->mapi.size_x)
	{
		tmp[i] = ' ';
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
