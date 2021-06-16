/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/16 18:50:12 by cassassi         ###   ########.fr       */
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
		return (-1);
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
	
	data->mapi.get_size = 0;
	line = NULL;
	if (ft_parsing(data, line, file) < 0)
		return (-1);
	data->mapi.get_size = 1;
	data->parse.map = 0;
	data->map = (char **)malloc(sizeof(char *) * (data->mapi.size_y + 1));
	if (!data->map)
		return (-1);
	data->mapi.size_y = 0;
	if (ft_parsing(data, line, file) < 0)
		return (-1);
	data->map[data->mapi.size_y] = NULL;
	if (ft_check_map_validity(data) < 0)
		return (-1);
	return (0);
}

int	ft_parsing(t_data *data, char *line, char *file)
{
	int	gnl;
	int	is_map;
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	gnl = 1;
	is_map = 0;
	while (gnl > 0 && data->parsing >= 0)
	{
		gnl = get_next_line(fd, &line);
		is_map = ft_check_if_map(data, line);
		ft_deal_with_is_map(data, line, is_map);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	if (close(fd) < 0 || gnl < 0 || data->parsing < 0)
		return (-1);
	return (0);
}
