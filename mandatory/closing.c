/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:45:10 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/24 15:45:52 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_quit(t_data *data)
{
	return (mlx_loop_end(data->mlx_ptr));
}

int	ft_destroy(t_data *data)
{
	if (data->mlx_img.img)
	{
		mlx_destroy_image(data->mlx_ptr, data->mlx_img.img);
		data->mlx_img.img = NULL;
	}
	if (data->map)
		ft_free_tab(data->map, data->mapi.size_y);
	ft_destroy_texture(data);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	return (-1);
}

void	ft_destroy_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].xpm.img)
		{
			mlx_destroy_image(data->mlx_ptr, data->tex[i].xpm.img);
			data->tex[i].xpm.img = NULL;
		}
		if (data->parse.tex_path[i])
		{
			free(data->parse.tex_path[i]);
			data->parse.tex_path[i] = NULL;
		}
		i++;
	}
}
