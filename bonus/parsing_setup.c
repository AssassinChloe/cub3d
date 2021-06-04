/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:35:08 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/03 17:04:48 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_res(t_data *data, char **info)
{
	int j;

	j = ft_atoi(info[1]);
	if (j <= 0)
		return (-1);
	else if (j > data->win.screenw)
		data->win.width = data->win.screenw;
	else
		data->win.width = j;
	j = ft_atoi(info[2]);
	if (j <= 0 )
		return (-1);
	else if (j >= data->win.screenh)
		data->win.height = data->win.screenh;
	else
		data->win.height = j;
	data->parse.res = 1;
	return (0);
}

int	ft_check_for_tex(t_data *data, char **info)
{
	int ret;
	
	if (ft_strncmp(info[0], "EA", 3) == 0 && data->parse.tex[0] == 0)
		ret = ft_set_tex(data, info);
	else if (ft_strncmp(info[0], "WE", 3) == 0 && data->parse.tex[1] == 0)
		ret = ft_set_tex(data, info);
	else if (ft_strncmp(info[0], "NO", 3) == 0 && data->parse.tex[2] == 0)
		ret = ft_set_tex(data, info);
	else if (ft_strncmp(info[0], "SO", 3) == 0 && data->parse.tex[3] == 0)
		ret = ft_set_tex(data, info);
	else if (ft_strncmp(info[0], "S", 2) == 0 && data->parse.tex[4] == 0)
		ret = ft_set_tex(data, info);
	else if (ft_strncmp(info[0], "F", 2) == 0 && data->parse.floor == 0)
		ret = ft_set_color(data, info);
	else if (ft_strncmp(info[0], "C", 2) == 0 && data->parse.ceil == 0)
		ret = ft_set_color(data, info);
	else
		ret = -1;
	return (ret);
}

int	ft_set_color(t_data *data, char **info)
{
	int ret;

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

int	ft_set_tex(t_data *data, char **info)
{
	if (ft_strncmp(info[0], "EA", 3) == 0)
	{
		data->parse.tex_path[0] = ft_strdup(info[1]);	
		data->parse.tex[0] = 1;
	}
	else if (ft_strncmp(info[0], "WE", 3) == 0)
	{
		data->parse.tex_path[1] = ft_strdup(info[1]);	
		data->parse.tex[1] = 1;
	}
	else if (ft_strncmp(info[0], "NO", 3) == 0)
	{
		data->parse.tex_path[2] = ft_strdup(info[1]);	
		data->parse.tex[2] = 1;
	}
	else if (ft_strncmp(info[0], "SO", 3) == 0)
	{
		data->parse.tex_path[3] = ft_strdup(info[1]);	
		data->parse.tex[3] = 1;
	}
	else
	{
		data->parse.tex_path[4] = ft_strdup(info[1]);	
		data->parse.tex[4] = 1;
	}
	return (0);
}
