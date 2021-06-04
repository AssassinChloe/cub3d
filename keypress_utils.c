/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:05:21 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/04 15:22:16 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_turn_right(t_data *data)
{
	data->dir -= 5;
	if (data->dir < 0)
		data->dir += 360;
}

void	ft_turn_left(t_data *data)
{
	data->dir += 5;
	if (data->dir >= 360)
		data->dir -= 360;
}

void	ft_go_front(t_data *data, double delta_x, double delta_y)
{
	data->Px += floor(delta_x);
	data->Py += floor(delta_y);
}

void	ft_go_back(t_data *data, double delta_x, double delta_y)
{
	data->Px -= floor(delta_x);
	data->Py -= floor(delta_y);
}
	
void	ft_go_left(t_data *data, double delta_x, double delta_y)
{
	data->Px += floor(delta_y);
	data->Py -= floor(delta_x);
}

void	ft_go_right(t_data *data, double delta_x, double delta_y)
{
	data->Px -= floor(delta_y);
	data->Py += floor(delta_x);
}
