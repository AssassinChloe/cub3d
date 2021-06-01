/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/01 18:27:50 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
       	int	i;

	ft_init_data(&data);
	mlx_get_screen_size(data.mlx_ptr, &data.win.screenw, &data.win.screenh);
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	printf("parsing\n");
	i = ft_check_arg(argc, argv);
	if (i != 0)
		return (0);
	i = ft_parse_cub(argv[1], &data);
	if (i != 0)
		return (0);
	ft_init_win(&data);
	printf("initialisation\n");
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.win.width, data.win.height, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.win.width, data.win.height);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &ft_render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(data.mlx_ptr, data.tab[i].img.mlx_img);
		i++;
	}
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	printf("fermeture\n");
}
