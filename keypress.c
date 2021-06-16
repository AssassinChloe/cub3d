/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:45:15 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/16 13:55:01 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	init_keys(t_data *data)
{
	data->key.forward = 0;
	data->key.backward = 0;
	data->key.left = 0;
	data->key.right = 0;
	data->key.rot_left = 0;
	data->key.rot_right = 0;
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == XK_Right)
		data->key.rot_right = 1;
	if (keycode == XK_Left)
		data->key.rot_left = 1;
	if (keycode == XK_z || keycode == XK_w)
		data->key.forward = 1;
	if (keycode == XK_s)
		data->key.backward = 1;
	if (keycode == XK_q || keycode == XK_a)
		data->key.left = 1;
	if (keycode == XK_d)
		data->key.right = 1;
	return (0);
}

int	keyrelease(int keycode, t_data *data)
{
	if (keycode == XK_Right)
		data->key.rot_right = 0;
	if (keycode == XK_Left)
		data->key.rot_left = 0;
	if (keycode == XK_z || keycode == XK_w)
		data->key.forward = 0;
	if (keycode == XK_s)
		data->key.backward = 0;
	if (keycode == XK_q || keycode == XK_a)
		data->key.left = 0;
	if (keycode == XK_d)
		data->key.right = 0;
	return (0);
}
