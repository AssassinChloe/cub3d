/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:35:08 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/21 10:37:11 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_for_tex(t_data *data, char **info)
{
	int	ret;

	if (ft_strncmp(info[0], "EA", 3) == 0 && data->parse.tex[0] == 0)
		ret = ft_set_tex(data, info[1], 0);
	else if (ft_strncmp(info[0], "WE", 3) == 0 && data->parse.tex[1] == 0)
		ret = ft_set_tex(data, info[1], 1);
	else if (ft_strncmp(info[0], "NO", 3) == 0 && data->parse.tex[2] == 0)
		ret = ft_set_tex(data, info[1], 2);
	else if (ft_strncmp(info[0], "SO", 3) == 0 && data->parse.tex[3] == 0)
		ret = ft_set_tex(data, info[1], 3);
	else if (ft_strncmp(info[0], "F", 2) == 0 && data->parse.floor == 0)
		ret = ft_set_color(data, info);
	else if (ft_strncmp(info[0], "C", 2) == 0 && data->parse.ceil == 0)
		ret = ft_set_color(data, info);
	else
		ret = -1;
	return (ret);
}

int	get_rgb(char *str)
{
	int		i;
	int		rgb[3];
	char	**color;

	color = ft_split(str, ',');
	if (!(color))
		return (ft_error(-1));
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
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	ft_set_color(t_data *data, char **info)
{
	int	ret;

	ret = get_rgb(info[1]);
	if (ret >= 0 && ft_strncmp(info[0], "C", 2) == 0)
	{
		data->parse.ceil_color = ret;
		ret = 0;
		data->parse.ceil = 1;
	}
	else if (ret >= 0 && ft_strncmp(info[0], "F", 2) == 0)
	{
		data->parse.floor_color = ret;
		ret = 0;
		data->parse.floor = 1;
	}
	else
		ret = -1;
	return (ret);
}

int	ft_set_tex(t_data *data, char *info, int i)
{
	data->parse.tex_path[i] = ft_strdup(info);
	if (data->parse.tex_path[i] == NULL)
		return (ft_error(4));
	data->parse.tex[i] = 1;
	return (0);
}
