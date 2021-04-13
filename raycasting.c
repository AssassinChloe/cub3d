/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:04:37 by cassassi          #+#    #+#             */
/*   Updated: 2021/04/13 18:08:12 by cassassi         ###   ########.fr       */
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
	int map[8][8] ={{1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1}};

	ray_angle = ((data->dir - 30) + (window.sub_ray_angle * ray_nb));
	if (ray_angle >= 360)
		ray_angle -= 360;
	if (ray_angle < 0)
		ray_angle += 360;
	d_i_l = ft_check_intersect_line(data, ray_angle, map);
	d_i_c = ft_check_intersect_column(data, ray_angle, map);
	if (d_i_l > d_i_c)
		wall_size = floor(GRID * window.dpp / d_i_c);
	else
		wall_size = floor(GRID * window.dpp / d_i_l); 
	return (wall_size);

}

double ft_check_intersect_line(t_data *data, double ray_angle, int map[8][8])
{
	t_point A;
	double dist;
	double 	yA;
	double	xA;
	int i;
	yA = GRID;
	if (ray_angle == 0 || ray_angle == 180)
		return (10000);
	else if (ray_angle > 0 && ray_angle < 180)
	{
		A.y = (floor((data->P.y/GRID)) * GRID) - 0.0001;
		yA = -yA;
	}
	else if (ray_angle > 180 && ray_angle < 360)
		A.y = (floor((data->P.y/GRID)) * GRID) + GRID;
	else 
		printf("error ray_angle: %f\n", ray_angle);
	if (ray_angle == 90 || ray_angle == 270)
	{
		A.x = data->P.x;
		xA = 0;
	}
	else
	{
		A.x = data->P.x + ((data->P.y - A.y) / (tan(ray_angle * DEG_CONV)));
		xA = GRID * tan(ray_angle * DEG_CONV);
	}
	i = 0;
	while ((A.x/GRID < 8) && (A.y/GRID > 8) && map[(int)floor(A.y/GRID)][(int)floor(A.x/GRID)] == 0)
	{
		A.x = A.x + xA;
		A.y = A.y + yA;
		i++;
	}
	dist = fabs(cos(ray_angle * DEG_CONV) / (data->P.x - A.x) * (cos((ray_angle - data->dir) * DEG_CONV)));
	return (dist);

}

double ft_check_intersect_column(t_data *data, double ray_angle, int map[8][8])
{
	t_point B;
	double dist;
	double  yB;
	double  xB;
	int i;

	xB = GRID;
	if (ray_angle == 90 || ray_angle == 270)
		return (10000);
	else if ((ray_angle >= 0 && ray_angle < 90) || (ray_angle > 270 && ray_angle < 360))
		B.x = (floor((data->P.x/GRID)) * GRID) - 0.0001;
	else if (ray_angle > 90  && ray_angle <= 270 )
	{
		B.x = (floor((data->P.x/GRID)) * GRID) + GRID;
		xB = -xB;
	}
	else
		printf("Error wrong angle (%f) of camera", ray_angle);
	if (ray_angle == 0 || ray_angle == 180)
	{
		B.y = data->P.y;
		yB = 0;
	}
	else
	{	
		yB = GRID * fabs(tan(ray_angle * DEG_CONV));
		B.y = floor(data->P.y + ((data->P.x - B.x) * fabs(tan(ray_angle * DEG_CONV))));
	}
	i = 0;
	while (map[(int)floor(B.y/GRID)][(int)floor(B.x/GRID)] == 0 || i < 6)
	{
		B.x = B.x + xB;
		B.y = B.y + yB;
		i++;
	}
	dist = fabs(cos(ray_angle * DEG_CONV) / (data->P.x - B.x) * (cos((ray_angle - data->dir) * DEG_CONV)));
	return (dist);
}
