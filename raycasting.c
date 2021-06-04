/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:04:37 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/04 17:19:16 by cassassi         ###   ########.fr       */
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

void ft_ray_lenght(int ray_nb, t_data *data, t_cross *cross)
{
	double r_a;
	t_cross d_i_l;
	t_cross d_i_c;
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
int	set_params_dil(t_data *data, double r_a, t_cross *dil)
{
	dil->delta.y = GRID;
	if (r_a >= 359 || r_a <= 1 || (r_a >= 179 && r_a <= 181))
	{
		dil->dist = 10000;
		return (-1);
	}
	else if (r_a > 1 && r_a < 179)
	{
		dil->cross.y = (floor(data->Py/GRID) * GRID) - 0.001;
		dil->delta.y = -dil->delta.y;
	}
	else 
		dil->cross.y = (floor(data->Py/GRID) * GRID) + GRID;
	return (0);
}

void	ft_check_intersect_line(t_data *data, double r_a, t_cross *dil)
{
	if (set_params_dil(data, r_a, dil) < 0)
		return ;
	dil->cross.x = data->Px + (((data->Py - dil->cross.y) /
		sin(r_a * DEG)) * cos(r_a * DEG));
	dil->delta.x = -cos(r_a * DEG) * (dil->delta.y / sin(r_a * DEG));
	while (data->map[(int)(dil->cross.y/GRID)]
			[(int)(dil->cross.x/GRID)] == 0)
	{
		if (dil->cross.x < 0 || dil->cross.y < 0
|| dil->cross.x > ((MAPX + 1) * GRID) || dil->cross.y > ((MAPY + 1) * GRID))
		{
			dil->dist = 10000;
			return ;
		}
		dil->cross.x = dil->cross.x + dil->delta.x;
		dil->cross.y = dil->cross.y + dil->delta.y;
	}
	dil->dist = fabs(((data->Py - dil->cross.y) / sin(r_a * DEG))
			* cos((data->dir - r_a) * DEG));
}

int	set_params_dic(t_data *data, double r_a, t_cross *dic)
{
	dic->delta.x = GRID;
	if ((r_a >= 89 && r_a <= 91) || (r_a <= 271 && r_a >= 269))
	{
		dic->dist = 10000;
		return (-1);
	}
	else if ((r_a >= 0 && r_a < 89) || (r_a > 271 && r_a < 360))
	{
		dic->cross.x = (floor(data->Px/GRID) * GRID) + GRID;
	}
	else
	{
		dic->cross.x = (floor(data->Px/GRID) * GRID) - 0.001;
		dic->delta.x = -dic->delta.x;
	}
	return (0);

}
void ft_check_intersect_column(t_data *data, double r_a, t_cross *dic)
{
	if (set_params_dic(data, r_a, dic) < 0)
		return ;
	dic->cross.y = data->Py + (((data->Px - dic->cross.x) /
			cos(r_a * DEG)) * sin(r_a * DEG));
	dic->delta.y = -sin(r_a * DEG) * (dic->delta.x / cos(r_a * DEG));
	while (data->map[(int)(dic->cross.y/GRID)]
			[(int)(dic->cross.x/GRID)] == 0 )
	{
		if (dic->cross.x < 0 || dic->cross.y < 0
|| dic->cross.x > ((MAPX + 1) * GRID) || dic->cross.y > ((MAPY + 1) * GRID))
		{
			dic->dist = 10000;
			return ;
		}
		dic->cross.x = dic->cross.x + dic->delta.x;
		dic->cross.y = dic->cross.y + dic->delta.y;
	}
	dic->dist = fabs(((data->Px - dic->cross.x) / cos(r_a * DEG))
			* cos((data->dir - r_a) * DEG));
}
