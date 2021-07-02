/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:04:37 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/25 11:43:21 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_hit(t_data *data, double r_a, t_cross *d_i_l, t_cross *d_i_c)
{
	if (d_i_l->dist > d_i_c->dist)
	{
		if (r_a < 90 || r_a > 270)
			data->hit = 0;
		if (r_a > 90 && r_a < 270)
			data->hit = 1;
	}
	else
	{
		if (r_a > 0 && r_a < 180)
			data->hit = 2;
		if (r_a > 180 && r_a < 360)
			data->hit = 3;
	}
}

void	ft_ray_lenght(int ray_nb, t_data *data, t_cross *cross)
{
	double	r_a;
	t_cross	d_i_l;
	t_cross	d_i_c;

	ft_init_t_cross(cross);
	r_a = ((data->dir + 30) - (data->win.sub_ray_angle * ray_nb));
	if (r_a >= 360)
		r_a -= 360;
	if (r_a < 0)
		r_a += 360;
	ft_check_intersect_line(data, r_a, &d_i_l);
	ft_check_intersect_column(data, r_a, &d_i_c);
	ft_get_hit(data, r_a, &d_i_l, &d_i_c);
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
}

void	ft_init_t_cross(t_cross *ray)
{
	ray->dist = 50000;
	ray->cross.x = 0;
	ray->cross.y = 0;
	ray->delta.x = 0;
	ray->delta.y = 0;
}

int	ft_set_params_dil(t_data *data, double r_a, t_cross *dil)
{
	dil->delta.y = GRID;
	if (r_a >= 359 || r_a <= 1 || (r_a >= 179 && r_a <= 181))
		return (-1);
	else if (r_a > 1 && r_a < 179)
	{
		dil->cross.y = (floor(data->pos.y / GRID) * GRID) - 0.001;
		dil->delta.y = -dil->delta.y;
	}
	else
		dil->cross.y = (floor(data->pos.y / GRID) * GRID) + GRID;
	return (0);
}

void	ft_check_intersect_line(t_data *data, double r_a, t_cross *dil)
{
	ft_init_t_cross(dil);
	if (ft_set_params_dil(data, r_a, dil) < 0)
		return ;
	dil->cross.x = data->pos.x + (((data->pos.y - dil->cross.y)
				/ sin(r_a * DEG)) * cos(r_a * DEG));
	dil->delta.x = -cos(r_a * DEG) * (dil->delta.y / sin(r_a * DEG));
	if (dil->cross.x < 0 || dil->cross.y < 0
		|| dil->cross.x >= (data->mapi.size_x * GRID)
		|| dil->cross.y >= (data->mapi.size_y * GRID))
		return ;
	while (data->map[(int)(dil->cross.y / GRID)]
			[(int)(dil->cross.x / GRID)] == 'X')
	{
		dil->cross.x = dil->cross.x + dil->delta.x;
		dil->cross.y = dil->cross.y + dil->delta.y;
		if (dil->cross.x < 0 || dil->cross.y < 0
			|| dil->cross.x >= (data->mapi.size_x * GRID)
			|| dil->cross.y >= (data->mapi.size_y * GRID))
			return ;
	}
	dil->dist = fabs(((data->pos.y - dil->cross.y) / sin(r_a * DEG))
			* cos((data->dir - r_a) * DEG));
}
