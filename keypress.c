/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:45:15 by cassassi          #+#    #+#             */
/*   Updated: 2021/04/27 16:59:34 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*int	ft_player_move(t_key *key)
{
	double delta_x;
	double delta_y;
	
	}
	if (keysym == XK_Right)
	{
		data->dir -= 5;
		if (data->dir < 0)
			data->dir += 360;
	}
	if (keysym == XK_Left)
	{
		data->dir += 5;
		if (data->dir >= 360)
			data->dir -= 360;
	}
	delta_x = (cos(data->dir * DEG_CONV) * 5);
	delta_y = (-sin(data->dir * DEG_CONV) * 5);
	if (keysym == XK_z && data->map[(int)(data->Py + floor(delta_y))/GRID][(int)(data->Px + floor(delta_x))/GRID] == 0)
	{ 
		data->Px += floor(delta_x);
		data->Py += floor(delta_y);
	}
	if (keysym == XK_s && data->map[(int)(data->Py - floor(delta_y))/GRID][(int)(data->Px - floor(delta_x))/GRID] == 0)
	{
		data->Px -= floor(delta_x);
		data->Py -= floor(delta_y);
	}
	if (keysym == XK_q && data->map[(int)(data->Py - floor(delta_x))/GRID][(int)(data->Px + floor(delta_y))/GRID] == 0)
	{
		data->Px += floor(delta_y);
		data->Py -= floor(delta_x);
	}
	if (keysym == XK_d && data->map[(int)(data->Py + floor(delta_x))/GRID][(int)(data->Px - floor(delta_y))/GRID] == 0)
	{
		data->Px -= floor(delta_y);
		data->Py += floor(delta_x);
	}
	printf("dir: %d\n", data->dir);
	return (0);

}*/
int	ft_quit(t_data *data)
{

	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	double delta_x;
	double delta_y;
	
	if (keysym == XK_Escape)
	{
		ft_quit(data);
	}
	if (keysym == XK_Right)
	{
		data->dir -= 5;
		if (data->dir < 0)
			data->dir += 360;
	}
	if (keysym == XK_Left)
	{
		data->dir += 5;
		if (data->dir >= 360)
			data->dir -= 360;
	}
	delta_x = (cos(data->dir * DEG_CONV) * 5);
	delta_y = (-sin(data->dir * DEG_CONV) * 5);
	if (keysym == XK_z && data->map[(int)(data->Py + floor(delta_y))/GRID][(int)(data->Px + floor(delta_x))/GRID] == 0)
	{ 
		data->Px += floor(delta_x);
		data->Py += floor(delta_y);
	}
	if (keysym == XK_s && data->map[(int)(data->Py - floor(delta_y))/GRID][(int)(data->Px - floor(delta_x))/GRID] == 0)
	{
		data->Px -= floor(delta_x);
		data->Py -= floor(delta_y);
	}
	if (keysym == XK_q && data->map[(int)(data->Py - floor(delta_x))/GRID][(int)(data->Px + floor(delta_y))/GRID] == 0)
	{
		data->Px += floor(delta_y);
		data->Py -= floor(delta_x);
	}
	if (keysym == XK_d && data->map[(int)(data->Py + floor(delta_x))/GRID][(int)(data->Px - floor(delta_y))/GRID] == 0)
	{
		data->Px -= floor(delta_y);
		data->Py += floor(delta_x);
	}
	return (0);
}
