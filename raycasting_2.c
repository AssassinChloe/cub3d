/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 18:19:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 18:20:57 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		dic->cross.x = (floor(data->Px / GRID) * GRID) + GRID;
	}
	else
	{
		dic->cross.x = (floor(data->Px / GRID) * GRID) - 0.001;
		dic->delta.x = -dic->delta.x;
	}
	return (0);
}

void	ft_check_intersect_column(t_data *data, double r_a, t_cross *dic)
{
	if (set_params_dic(data, r_a, dic) < 0)
		return ;
	dic->cross.y = data->Py + (((data->Px - dic->cross.x)
				/ cos(r_a * DEG)) * sin(r_a * DEG));
	dic->delta.y = -sin(r_a * DEG) * (dic->delta.x / cos(r_a * DEG));
	while (data->map[(int)(dic->cross.y / GRID)]
			[(int)(dic->cross.x / GRID)] == 0)
	{
		if (dic->cross.x < 0 || dic->cross.y < 0
			|| dic->cross.x > ((MAPX + 1) * GRID)
			|| dic->cross.y > ((MAPY + 1) * GRID))
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
