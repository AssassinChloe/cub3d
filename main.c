/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/21 10:31:39 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_setup_params(t_data *data, int ac, char **av)
{
	if (ft_check_arg(ac, av) < 0)
		return (-1);
	if (ft_init_data(data, av[1]) < 0)
		return (ft_destroy(data));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (ft_setup_params(&data, argc, argv) < 0)
		return (-1);
	if (ft_init_texture(&data) < 0)
		return (ft_destroy(&data));
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &keypress, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_render, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &keyrelease, &data);
	mlx_hook(data.win_ptr, 33, 0L, &ft_quit, &data);
	mlx_loop(data.mlx_ptr);
	ft_destroy(&data);
	return (0);
}

int	ft_quit(t_data *data)
{
	return (mlx_loop_end(data->mlx_ptr));
}

int	ft_destroy(t_data *data)
{
	int i = 0;
	printf("destroy %d\n", i++);
	if (data->mlx_img.img)
	{
		mlx_destroy_image(data->mlx_ptr, data->mlx_img.img);
		data->mlx_img.img = NULL;
	}
	printf("destroy %d\n", i++);
	if (data->map)
		ft_free_tab(data->map, data->mapi.size_y);
	printf("destroy %d\n", i++);
	ft_destroy_texture(data);
	printf("destroy %d\n", i++);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	printf("destroy %d\n", i++);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	printf("destroy %d\n", i++);
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
