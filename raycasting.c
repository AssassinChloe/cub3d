/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:04:37 by cassassi          #+#    #+#             */
/*   Updated: 2021/04/16 21:53:17 by cassassi         ###   ########.fr       */
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



double ft_ray_lenght(t_window window, int ray_nb, t_data *data)
{
	double ray_angle;
	double d_i_l;
	double d_i_c;
	double wall_size;
	int tabmap[MAPY][MAPX] = {{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}};

	ray_angle = ((data->dir + 30) - (window.sub_ray_angle * ray_nb));
	if (ray_angle >= 360)
		ray_angle -= 360;
	if (ray_angle < 0)
		ray_angle += 360;
	d_i_l = ft_check_intersect_line(data, floor(ray_angle), tabmap);
	d_i_c = ft_check_intersect_column(data, floor(ray_angle), tabmap);
	if (d_i_l > d_i_c)
	{
		wall_size = floor(GRID * window.dpp / d_i_c);
		if (ray_angle < 90 || ray_angle > 270)
			data->hit = 1;
		if (ray_angle > 90 && ray_angle < 270)
			data->hit = 2;
	}
	else
	{
		wall_size = floor(GRID * window.dpp / d_i_l);
		if (ray_angle > 0 && ray_angle < 180)
			data->hit = 3;
		if (ray_angle > 180 && ray_angle < 360)
			data->hit = 4;
	}
	if (floor(ray_angle) == 0)
		data->hit = 1;
	if (floor(ray_angle) == 180)
		data->hit = 2;
	if (floor(ray_angle) == 90)
		data->hit = 3;
	if (floor(ray_angle) == 270)
		data->hit = 4;	
	printf ("wall_size %.2f\n", wall_size);
	return (wall_size);

}

double ft_check_intersect_line(t_data *data, double ray_angle, int tabmap[MAPY][MAPX])
{
	t_point A;
	double dist;
	double 	yA;
	double	xA;

	yA = GRID;
	if (ray_angle == 0 || ray_angle == 180)
		return (10000);
	else if (ray_angle > 0 && ray_angle < 180)
	{
		A.y = (floor(data->Py/GRID) * GRID) - 1;
		yA = -yA;
	}
	else if (ray_angle > 180 && ray_angle < 360)
		A.y = (floor(data->Py/GRID) * GRID) + GRID;
	else 
		printf("error ray_angle: %f\n", ray_angle);
	A.x = data->Px + (((data->Py - A.y) / sin(ray_angle * DEG_CONV)) * cos(ray_angle * DEG_CONV));
	xA = -floor(cos(ray_angle * DEG_CONV) * (yA / sin(ray_angle * DEG_CONV)));
	while (tabmap[(int)floor(A.y/GRID)][(int)floor(A.x/GRID)] == 0)
	{
		if (A.x < 0 || A.y < 0)
			return (10000);
		A.x = A.x + xA;
		A.y = A.y + yA;
	}

	printf("Px %.2f, Py%.2f, RA %.3f, DIL A.x : %.1f, A.y : %.1f, xA %.1f, yA %.1f -> ", data->Px, data->Py, ray_angle, A.x, A.y, xA, yA);
	dist = fabs(((data->Py - A.y) / (sin(ray_angle * DEG_CONV))) * cos((data->dir - ray_angle) * DEG_CONV));
	printf("dil %.f\n", dist);
	return (dist);

}

double ft_check_intersect_column(t_data *data, double ray_angle, int tabmap[MAPY][MAPX])
{
	t_point B;
	double dist;
	double  yB;
	double  xB;

	xB = GRID;
	if (ray_angle == 90 || ray_angle == 270)
		return (10000);
	else if ((ray_angle >= 0 && ray_angle < 90) || (ray_angle > 270 && ray_angle < 360))
		B.x = (floor((data->Px/GRID)) * GRID) + GRID;
	else if (ray_angle > 90  && ray_angle < 270 )
	{
		B.x = (floor((data->Px/GRID)) * GRID) - 1;
		xB = -xB;
	}
	else
		printf("Error wrong angle (%f) of camera", ray_angle);
	yB = -floor(sin(ray_angle * DEG_CONV) * (xB /cos(ray_angle * DEG_CONV)));
	B.y = data->Py + (((data->Px - B.x) / cos(ray_angle * DEG_CONV)) * sin(ray_angle * DEG_CONV));
	while (tabmap[(int)(B.y/GRID)][(int)(B.x/GRID)] == 0)
	{
		if (B.x < 0 || B.y < 0)
			return (10000);
		B.x = B.x + xB;
		B.y = B.y + yB;
	}
	printf("Px %.2f, Py %.2f RA %.3f, DIC B.x : %.1f, B.y : %.1f, xB %.1f, yB %.1f ->",data->Px, data->Py, ray_angle, B.x, B.y, xB, yB);
	dist = fabs(((data->Px - B.x) / cos((ray_angle * DEG_CONV))) * cos((data->dir - ray_angle) * DEG_CONV));
	printf("dic %.f\n", dist);
	return (dist);
}

int	ft_get_wall(t_data *data)
{
	if (data->hit == 1)
		return (LEFT_PIXEL);
	if (data->hit == 2)
		return (RIGHT_PIXEL);
	if (data->hit == 3)
		return (BOT_PIXEL);
	if (data->hit == 4)
		return (TOP_PIXEL);
	return (0);
}
