/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/21 14:26:51 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_data	data;
       	int i = 0;	
	t_tex *tab;
	
	tab = (t_tex *)malloc(sizeof(t_tex) * 6);
	ft_init_data(&data);
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	tab[0] = ft_init_texture(&data, "img/east.xpm");
	tab[1] = ft_init_texture(&data, "img/west.xpm");
	tab[2] = ft_init_texture(&data, "img/north.xpm");
	tab[3] = ft_init_texture(&data, "img/south.xpm");
	tab[4] = ft_init_texture(&data, "img/sprite.xpm");
	tab[5] = ft_init_texture(&data, "img/other.xpm");

	while (i < 6)
	{
		data.tab[i] = tab[i];
		i++;
	}
	printf("initialisation\n");
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &ft_render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	i = 0;
	while (i < 6)
	{
		mlx_destroy_image(data.mlx_ptr, data.tab[i].img.mlx_img);
		i++;
	}
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	printf("fermeture\n");
}
