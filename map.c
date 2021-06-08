/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:50:09 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/08 14:39:29 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_validity(t_data *data, char **map)
{
	int	x;
	t_pos	*tab;



	
	x = 0;
	
}

int 	ft_map_size(t_data *data, char **map)
{
	int len;
	int i;

	i = 0;
	data->map.size_x = 0;
	while (i < data->map.size_y)
	{
		len = ft_strlen(map[i]);
		if (len > data->map.size_x)
			data->map.size_x = len;
		i++;
	}
	return (data->map.size_x * data->map.size_y);
}
