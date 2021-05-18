/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:04:37 by cassassi          #+#    #+#             */
/*   Updated: 2021/05/12 18:42:05 by cassassi         ###   ########.fr       */
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

void	ft_get_hit(t_data *data, double ray_angle, t_cross *d_i_l, t_cross *d_i_c)
{
	if (d_i_l->dist > d_i_c->dist)
	{
		if (ray_angle < 90 || ray_angle > 270)
			data->hit = 0;
		if (ray_angle > 90 && ray_angle < 270)
			data->hit = 1;
	}
	else
	{
		if (ray_angle > 0 && ray_angle < 180)
			data->hit = 2;
		if (ray_angle > 180 && ray_angle < 360)
			data->hit = 3;
	}
}

void ft_ray_lenght(t_window window, int ray_nb, t_data *data, t_cross *cross)
{
	double ray_angle;
	t_cross d_i_l;
	t_cross d_i_c;
	/*int	i;
	int	j;
	int	k;
	int sdir;
	double sray;
	i = 0;
	j = 0;
	k = 0;*/
	ray_angle = ((data->dir + 30) - (window.sub_ray_angle * ray_nb));
	if (ray_angle >= 360)
		ray_angle -= 360;
	if (ray_angle < 0)
		ray_angle += 360;
	ft_check_intersect_line(data, ray_angle, &d_i_l);
	ft_check_intersect_column(data, ray_angle, &d_i_c);
	ft_get_hit(data, ray_angle, &d_i_l, &d_i_c);	
	if (d_i_l.dist > d_i_c.dist)
	{
		cross->cross = d_i_c.cross;
		cross->dist = d_i_c.dist;
	}
	else
	{
		cross->cross = d_i_l.cross;
		cross->dist = d_i_l.dist;
	}

/*	while (i < d_i_l.i && j < d_i_c.i)
	{
		if (d_i_l.sprite[i].dist > d_i_c.sprite[j].dist && ((int)(d_i_l.sprite[i].coord.x/GRID) == (int)(d_i_c.sprite[j].coord.x/GRID) && (int)(d_i_l.sprite[i].coord.y/GRID) == (int)(d_i_c.sprite[j].coord.y/GRID)))
		{
			cross->sprite[k].dist = d_i_c.sprite[j].dist;
			cross->sprite[k].coord = d_i_c.sprite[j].coord;
			if (ray_angle < 90 || ray_angle > 270)
				cross->sprite[k].hit = 0;
			if (ray_angle > 90 && ray_angle < 270)
				cross->sprite[k].hit = 1;
			i++;
			j++;
			k++;
		}
		else if (d_i_l.sprite[i].dist < d_i_c.sprite[j].dist && ((int)(d_i_l.sprite[i].coord.x/GRID) == (int)(d_i_c.sprite[j].coord.x/GRID) && (int)(d_i_l.sprite[i].coord.y/GRID) == (int)(d_i_c.sprite[j].coord.y/GRID)))
		{
			cross->sprite[k].dist = d_i_l.sprite[i].dist;
			cross->sprite[k].coord = d_i_l.sprite[i].coord;
			if (ray_angle > 0 && ray_angle < 180)
				cross->sprite[k].hit = 2;
			if (ray_angle > 180 && ray_angle < 360)
				cross->sprite[k].hit = 3;
			i++;
			j++;
			k++;
		}
		else
		{
			if (d_i_l.sprite[i].dist > d_i_c.sprite[j].dist)
			{
				cross->sprite[k].dist = d_i_c.sprite[j].dist;
				cross->sprite[k].coord = d_i_c.sprite[j].coord;
				if (ray_angle < 90 || ray_angle > 270)
					cross->sprite[k].hit = 0;
				if (ray_angle > 90 && ray_angle < 270)
					cross->sprite[k].hit = 1;
				j++;
				k++;
			}
			else
			{
				cross->sprite[k].dist = d_i_l.sprite[i].dist;
				cross->sprite[k].coord = d_i_l.sprite[i].coord;
				if (ray_angle > 0 && ray_angle < 180)
					cross->sprite[k].hit = 2;
				if (ray_angle > 180 && ray_angle < 360)
					cross->sprite[k].hit = 3;
				i++;
				k++;
			}

		}
	}
	while (i < d_i_l.i)
	{
		cross->sprite[k].dist = d_i_l.sprite[i].dist;
		cross->sprite[k].coord = d_i_l.sprite[i].coord;
		if (ray_angle > 0 && ray_angle < 180)
			cross->sprite[k].hit = 2;
		if (ray_angle > 180 && ray_angle < 360)
			cross->sprite[k].hit = 3;
		i++;
		k++;
	}
	while (j < d_i_c.i)
	{
		cross->sprite[k].dist = d_i_c.sprite[j].dist;
		cross->sprite[k].coord = d_i_c.sprite[j].coord;
		if (ray_angle < 90 || ray_angle > 270)
			cross->sprite[k].hit = 0;
		if (ray_angle > 90 && ray_angle < 270)
			cross->sprite[k].hit = 1;
		j++;
		k++;
	}
	cross->i = k;
	i = 0;
	while (i < cross->i)
	{
		cross->sprite[i].dist = sqrt(((data->Px - cross->sprite[i].coord.x)*(data->Px - cross->sprite[i].coord.x))+((data->Py - cross->sprite[i].coord.y)*(data->Py - cross->sprite[i].coord.y)));
		i++;
	}*/
}

void ft_check_intersect_line(t_data *data, double ray_angle, t_cross *A)
{
	int i;

	//A->i = 0;
	A->delta.y = GRID;
	if (ray_angle >= 359 || ray_angle <= 1 || (ray_angle >= 179 && ray_angle <= 181))
	{
		A->dist = 10000;
		return ;
	}
	else if (ray_angle > 1 && ray_angle < 179)
	{
		A->cross.y = (floor(data->Py/GRID) * GRID) - 0.001;
		A->delta.y = -A->delta.y;
	}
	else if (ray_angle > 181 && ray_angle < 359)
		A->cross.y = (floor(data->Py/GRID) * GRID) + GRID;
	else 
		printf("error ray_angle: %f\n", ray_angle);
	A->cross.x = data->Px + (((data->Py - A->cross.y) / sin(ray_angle * DEG_CONV)) * cos(ray_angle * DEG_CONV));
	A->delta.x = -cos(ray_angle * DEG_CONV) * (A->delta.y / sin(ray_angle * DEG_CONV));
	while (data->map[(int)(A->cross.y/GRID)][(int)(A->cross.x/GRID)] == 0 ||
			data->map[(int)(A->cross.y/GRID)][(int)(A->cross.x/GRID)] == 2)
	{
		if (A->cross.x < 0 || A->cross.y < 0 || A->cross.x > ((MAPX + 1) * GRID) || A->cross.y > ((MAPY + 1) * GRID))
		{
			A->dist = 10000;
			return ;
		}
		if (data->map[(int)(A->cross.y/GRID)][(int)(A->cross.x/GRID)] == 2)
		{
			i = 0;
			while (i < data->nbs)
			{
				if (data->spritel[i].coord.x == ((floor(A->cross.x/GRID) * GRID) + (GRID/2)) && data->spritel[i].coord.y == ((floor(A->cross.y/GRID) * GRID) + (GRID/2)))
					data->spritel[i].is_visible = 1;
				i++;
			}
			/*A->sprite[A->i].coord.x = A->cross.x;
			A->sprite[A->i].coord.y = A->cross.y;
			A->sprite[A->i].dist = fabs(((data->Py - A->sprite[A->i].coord.y) / sin(ray_angle * DEG_CONV)) * cos((data->dir - ray_angle) * DEG_CONV));
			A->i++;*/

		}
		A->cross.x = A->cross.x + A->delta.x;
		A->cross.y = A->cross.y + A->delta.y;
	}
	A->dist = fabs(((data->Py - A->cross.y) / sin(ray_angle * DEG_CONV)) * cos((data->dir - ray_angle) * DEG_CONV));
}

void ft_check_intersect_column(t_data *data, double ray_angle, t_cross *B)
{
	int i;
	
	//B->i = 0;
	B->delta.x = GRID;
	if ((ray_angle >= 89 && ray_angle <= 91) || (ray_angle <= 271 && ray_angle >= 269))
	{
		B->dist = 10000;
		return ;
	}
	else if ((ray_angle >= 0 && ray_angle < 89) || (ray_angle > 271 && ray_angle < 360))
	{
		B->cross.x = (floor(data->Px/GRID) * GRID) + GRID;
	}
	else if (ray_angle > 91  && ray_angle < 269 )
	{
		B->cross.x = (floor(data->Px/GRID) * GRID) - 0.001;
		B->delta.x = -B->delta.x;
	}
	else
		printf("Error wrong angle (%f) of camera", ray_angle);
	B->cross.y = data->Py + (((data->Px - B->cross.x) / cos(ray_angle * DEG_CONV)) * sin(ray_angle * DEG_CONV));
	B->delta.y = -sin(ray_angle * DEG_CONV) * (B->delta.x /cos(ray_angle * DEG_CONV));
	while (data->map[(int)(B->cross.y/GRID)][(int)(B->cross.x/GRID)] == 0 
			|| data->map[(int)(B->cross.y/GRID)][(int)(B->cross.x/GRID)] == 2)
	{
		if (B->cross.x < 0 || B->cross.y < 0 || B->cross.x > ((MAPX + 1) * GRID) || B->cross.y > ((MAPY + 1) * GRID))
		{
			B->dist = 10000;
			return ;
		}
		if (data->map[(int)(B->cross.y/GRID)][(int)(B->cross.x/GRID)] == 2)
		{
			i = 0;
			while (i < data->nbs)
			{
				if (data->spritel[i].coord.x == ((floor(B->cross.x/GRID) * GRID) + (GRID/2)) && data->spritel[i].coord.y == ((floor(B->cross.y/GRID) * GRID) + (GRID/2)))
				data->spritel[i].is_visible = 1;
				i++;
			}
			/*B->sprite[B->i].coord.x = B->cross.x;
			B->sprite[B->i].coord.y = B->cross.y;

			B->sprite[B->i].dist = fabs(((data->Px - B->sprite[B->i].coord.x) / cos(ray_angle * DEG_CONV)) * cos((data->dir - ray_angle) * DEG_CONV));
			B->i++;*/
		}
		B->cross.x = B->cross.x + B->delta.x;
		B->cross.y = B->cross.y + B->delta.y;
	}
	B->dist = fabs(((data->Px - B->cross.x) / cos(ray_angle * DEG_CONV)) * cos((data->dir - ray_angle) * DEG_CONV));
}
