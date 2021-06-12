/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:00:28 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/12 13:55:26 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
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

int	ft_parsing_error(t_data *data, char **map)
{
	printf("something went wrong");
	ft_free_tab(map, data->mapi.size_y);
	return (-1);
}

int	ft_parse_cub(t_data *data, int fd)
{
	int		gnl;
	char	*line;
	int		is_map;
	char	**map;

	gnl = 1;
	map = (char **)malloc(sizeof(char *) * 20);
	if (!map)
		return (-1);
	ft_init_parse(data);
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		is_map = ft_check_if_map(data, line);
		ft_deal_with_is_map(data, line, &map, is_map);
		free(line);
		line = NULL;
	}
	map[data->mapi.size_y] = NULL;
	free(line);
	line = NULL;
	if (gnl < 0 || data->parsing < 0 || close(fd) < 0)
		return (ft_parsing_error(data, map));
	ft_check_map_validity(data, &map);
	int i = 0;
	while (map[i] != NULL)
		printf("%s\n", map[i++]);
	return (0);
}
