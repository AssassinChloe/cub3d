/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:04:37 by cassassi          #+#    #+#             */
/*   Updated: 2021/04/20 20:05:53 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_init_window(t_window *window)
{
	window->width = WIN_WIDTH;
	window->height = WIN_HEIGHT;
	window->fov_angle = 60;
	window->dpp = ((window->width/2) / (tan((window->fov_angle/2)*DEG_CONV)));
	window->sub_ray_angle = (window->fov_angle / window->width);
}

t_cross ft_ray_lenght(t_window window, int ray_nb, t_data *data)
{
	double ray_angle;
	t_cross d_i_l;
	t_cross d_i_c;

	ray_angle = ((data->dir + 30) - (window.sub_ray_angle * ray_nb));
	if (ray_angle >= 360)
		ray_angle -= 360;
	if (ray_angle < 0)
		ray_angle += 360;
	d_i_l = ft_check_intersect_line(data, ray_angle);
	d_i_c = ft_check_intersect_column(data, ray_angle);
	if (floor(ray_angle) == 0)
		data->hit = 1;
	if (floor(ray_angle) == 180)
		data->hit = 2;
	if (floor(ray_angle) == 90)
		data->hit = 3;
	if (floor(ray_angle) == 270)
		data->hit = 4;	
	if (d_i_l.dist > d_i_c.dist)
	{
		data->wall_size = floor(GRID * window.dpp / d_i_c.dist);
		if (ray_angle < 90 || ray_angle > 270)
			data->hit = 1;
		if (ray_angle > 90 && ray_angle < 270)
			data->hit = 2;
		return (d_i_c);
	}
	else
	{
		data->wall_size = floor(GRID * window.dpp / d_i_l.dist);
		if (ray_angle > 0 && ray_angle < 180)
			data->hit = 3;
		if (ray_angle > 180 && ray_angle < 360)
			data->hit = 4;
		return (d_i_l);
	}
}

t_cross ft_check_intersect_line(t_data *data, double ray_angle)
{
	t_cross A;

	A.delta.y = GRID;
	if (ray_angle >= 359 || ray_angle <= 1 || (ray_angle >= 179 && ray_angle <= 181))
	{
		A.dist = 10000;
		return (A);
	}
	else if (ray_angle > 1 && ray_angle < 179)
	{
		A.cross.y = (floor(data->Py/GRID) * GRID) - 0.001;
		A.delta.y = -A.delta.y;
	}
	else if (ray_angle > 181 && ray_angle < 359)
		A.cross.y = (floor(data->Py/GRID) * GRID) + GRID;
	else 
		printf("error ray_angle: %f\n", ray_angle);
	A.cross.x = data->Px + (((data->Py - A.cross.y) / sin(ray_angle * DEG_CONV)) * cos(ray_angle * DEG_CONV));
	A.delta.x = -cos(ray_angle * DEG_CONV) * (A.delta.y / sin(ray_angle * DEG_CONV));
	while (data->map[(int)floor(A.cross.y/GRID)][(int)floor(A.cross.x/GRID)] == 0)
	{
		if (A.cross.x < 0 || A.cross.y < 0)
		{
			A.dist = 10000;
			return (A);
		}
		A.cross.x = A.cross.x + A.delta.x;
		A.cross.y = A.cross.y + A.delta.y;
	}
	A.dist = fabs(((data->Py - A.cross.y) / sin(ray_angle * DEG_CONV)) * cos((data->dir - ray_angle) * DEG_CONV));
	return (A);
}

t_cross ft_check_intersect_column(t_data *data, double ray_angle)
{
	t_cross B;

	B.delta.x = GRID;
	if ((ray_angle >= 89 && ray_angle <= 91) || (ray_angle <= 271 && ray_angle >= 269))
	{
		B.dist = 10000;
		return (B);
	}
	else if ((ray_angle >= 0 && ray_angle < 89) || (ray_angle > 271 && ray_angle < 360))
	{
		B.cross.x = (floor(data->Px/GRID) * GRID) + GRID;
	}
	else if (ray_angle > 91  && ray_angle < 269 )
	{
		B.cross.x = (floor(data->Px/GRID) * GRID) - 0.001;
		B.delta.x = -B.delta.x;
	}
	else
		printf("Error wrong angle (%f) of camera", ray_angle);
	B.cross.y = data->Py + (((data->Px - B.cross.x) / cos(ray_angle * DEG_CONV)) * sin(ray_angle * DEG_CONV));
	B.delta.y = -sin(ray_angle * DEG_CONV) * (B.delta.x /cos(ray_angle * DEG_CONV));
	while (data->map[(int)(B.cross.y/GRID)][(int)(B.cross.x/GRID)] == 0)
	{
		if (B.cross.x < 0 || B.cross.y < 0)  
		{
			B.dist = 10000;
			return (B);
		}
		B.cross.x = B.cross.x + B.delta.x;
		B.cross.y = B.cross.y + B.delta.y;
	}
	B.dist = fabs(((data->Px - B.cross.x) / cos(ray_angle * DEG_CONV)) * cos((data->dir - ray_angle) * DEG_CONV));
	return (B);
}
