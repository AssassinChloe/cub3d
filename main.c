/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/07 14:55:22 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int fd;
	fd = ft_check_arg(argc, argv);
	if (fd < 0)
		return (-1);
	if (ft_init_data(&data, fd) < 0)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win.width, data.win.height, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.win.width, data.win.height);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
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
	int i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->tex[i].img.mlx_img);
		free(data->parse.tex_path[i]);
		i++;
	}
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
}
