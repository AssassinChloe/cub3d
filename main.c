/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/12 13:10:02 by cassassi         ###   ########.fr       */
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
	int	i = 0;
	printf("test_main %d\n", i++);
	if (ft_setup_params(&data, argc, argv) < 0)
		return (-1);
	printf("test_main %d\n", i++);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win.width,
			data.win.height, "my window");
	if (data.win_ptr == NULL)
		return (MLX_ERROR);
	printf("test_main %d\n", i++);
	data.mlx_img.img = mlx_new_image(data.mlx_ptr, data.win.width,
			data.win.height);
	data.mlx_img.addr = mlx_get_data_addr(data.mlx_img.img,
			&data.mlx_img.bpp, &data.mlx_img.line_len,
			&data.mlx_img.endian);
	printf("test_main %d\n", i++);
	ft_init_texture(&data);
	printf("test_main %d\n", i++);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &keypress, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_render, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &keyrelease, &data);
	printf("test_main %d\n", i++);
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
