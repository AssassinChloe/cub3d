/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:45:15 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/11 18:33:57 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_quit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_quit(data);
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
