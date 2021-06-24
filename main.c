/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:02:24 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/24 15:47:23 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_setup_params(t_data *data, int ac, char **av)
{
	if (ft_check_arg(ac, av) < 0)
		return (-1);
	if (ft_init_data(data, av[1]) < 0)
		return (ft_destroy(data));
	return (0);
}

int	ft_check_arg(int argc, char**argv)
{
	int	i;
	int	j;
	int	fd;

	if (argc != 2)
		return (ft_error(1));
	j = 0;
	while (argv[1][j])
		j++;
	i = ft_strncmp(".cub", (argv[1] + (j - 4)), 5);
	if (i != 0)
		return (ft_error(2));
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (ft_error(7));
	}
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
