/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:05:21 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/11 18:34:37 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_movement(t_data *data)
{
	ft_rotate(data);
	ft_move(data);
}

void	ft_rotate(t_data *data)
{
	if (data->key.rot_left == 1)
	{
		data->dir += 1;
		if (data->dir >= 360)
			data->dir -= 360;
	}
	if (data->key.rot_right == 1)
	{
		data->dir -= 1;
		if (data->dir < 0)
			data->dir += 360;
	}
}

void	ft_move(t_data *data)
{
	double	delta_x;
	double	delta_y;

	delta_x = cos(data->dir * DEG) * 3;
	delta_y = -sin(data->dir * DEG) * 3;
	if (data->key.forward == 1)
	{
		data->pos.x += floor(delta_x);
		data->pos.y += floor(delta_y);
	}
	if (data->key.backward == 1)
	{
		data->pos.x -= floor(delta_x);
		data->pos.y -= floor(delta_y);
	}
	if (data->key.left == 1)
	{
		data->pos.x += floor(delta_y);
		data->pos.y -= floor(delta_x);
	}
	if (data->key.right == 1)
	{
		data->pos.x -= floor(delta_y);
		data->pos.y += floor(delta_x);
	}
}