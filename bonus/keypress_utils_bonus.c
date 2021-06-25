/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:05:21 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/25 12:23:45 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_movement(t_data *data)
{
	ft_rotate(data);
	ft_move(data);
}

void	ft_rotate(t_data *data)
{
	if (data->key.rot_left == 1)
	{
		data->dir = data->dir + SPEED ;
		if (data->dir >= 360)
			data->dir -= 360;
	}
	if (data->key.rot_right == 1)
	{
		data->dir = data->dir - SPEED;
		if (data->dir < 0)
			data->dir += 360;
	}
}

void	ft_move(t_data *data)
{
	double	delta_x;
	double	delta_y;

	delta_x = cos(data->dir * DEG) * SPEED;
	delta_y = -sin(data->dir * DEG) * SPEED;
	if (data->key.forward == 1
		&& data->map[(int)(data->pos.y + delta_y) / GRID]
			[(int)(data->pos.x + delta_x) / GRID] == 'X')
	{
		data->pos.x += delta_x;
		data->pos.y += delta_y;
	}
	if (data->key.backward == 1
		&& data->map[(int)(data->pos.y - delta_y) / GRID]
			[(int)(data->pos.x - delta_x) / GRID] == 'X')
	{
		data->pos.x -= delta_x;
		data->pos.y -= delta_y;
	}
	ft_lateral(data, delta_x, delta_y);
}

void	ft_lateral(t_data *data, double delta_x, double delta_y)
{
	if (data->key.left == 1
		&& data->map[(int)(data->pos.y - delta_x) / GRID]
			[(int)(data->pos.x + delta_y) / GRID] == 'X')
	{
		data->pos.x += delta_y;
		data->pos.y -= delta_x;
	}
	if (data->key.right == 1
		&& data->map[(int)(data->pos.y + delta_x) / GRID]
			[(int)(data->pos.x - delta_y) / GRID] == 'X')
	{
		data->pos.x -= delta_y;
		data->pos.y += delta_x;
	}
}
