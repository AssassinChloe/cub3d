/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 19:00:11 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_setup_params(t_data *data, int ac, char **av)
{
	int	fd;

	fd = ft_check_arg(ac, av);
	if (fd < 0)
		return (-1);
	if (ft_init_data(data, fd) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_setup_params(&data, argc, argv) < 0)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win.width,
			data.win.height, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.mlx_img.img = mlx_new_image(data.mlx_ptr, data.win.width,
			data.win.height);
	data.mlx_img.addr = mlx_get_data_addr(data.mlx_img.img,
			&data.mlx_img.bpp, &data.mlx_img.line_len,
			&data.mlx_img.endian);
	ft_init_texture(&data);
	mlx_loop_hook(data.mlx_ptr, &ft_render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	ft_destroy(&data);
	free(data.mlx_ptr);
	return (0);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->tex[i].xpm.img);
		free(data->parse.tex_path[i]);
		i++;
	}
	mlx_destroy_image(data->mlx_ptr, data->mlx_img.img);
	mlx_destroy_display(data->mlx_ptr);
}
