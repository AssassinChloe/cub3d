/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:57:29 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/21 16:04:14 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(int errnb)
{
	printf("Error\n");
	if (errnb == 1)
		printf("Wrong number of argument\n");
	else if (errnb == 2)
		printf("Not a .cub file\n");
	else if (errnb == 3)
		printf("Missing map\n");
	else if (errnb == 4)
		printf("Strdup fail\n");
	else if (errnb == 5)
		printf("Failure initating texture, check your path file\n");
	else if (errnb == -1)
		printf("Malloc failure\n");
	else if (errnb == -2)
		printf("Error open\n");
	else if (errnb == -3)
		printf("Error close\n");
	else if (errnb == -4)
		printf("Missing or wrong data for color/texture\n");
	else
		ft_error_2(errnb);
	return (-1);
}

void	ft_error_2(int errnb)
{
	if (errnb == -5)
		printf("Invalid Map\n");
	else if (errnb == -6)
		printf("MLX error\n");
	else if (errnb == -7)
		printf("Failure to read .cub file\n");
	else if (errnb == -8)
		printf("Too many player\n");
	else if (errnb == -9)
		printf("No starting position for the player\n");
	else
		printf("error %d \n", errnb);
}

int	ft_parsing_error(int gnl)
{
	if (gnl < 0)
		return (ft_error(-7));
	else
		return (-1);
}

int	ft_error_if_map(t_data *data)
{
	if (data->parse.map == 0)
		return (0);
	else
		return (ft_error(-5));
}
