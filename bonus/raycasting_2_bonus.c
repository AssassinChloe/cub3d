/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 18:19:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/25 11:42:54 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_set_params_dic(t_data *data, double r_a, t_cross *dic)
{
	dic->delta.x = GRID;
	if ((r_a >= 89 && r_a <= 91) || (r_a <= 271 && r_a >= 269))
		return (-1);
	else if ((r_a >= 0 && r_a < 89) || (r_a > 271 && r_a < 360))
	{
		dic->cross.x = (floor(data->pos.x / GRID) * GRID) + GRID;
	}
	else
	{
		dic->cross.x = (floor(data->pos.x / GRID) * GRID) - 0.001;
		dic->delta.x = -dic->delta.x;
	}
	return (0);
}

void	ft_check_intersect_column(t_data *data, double r_a, t_cross *dic)
{
	ft_init_t_cross(dic);
	if (ft_set_params_dic(data, r_a, dic) < 0)
		return ;
	dic->cross.y = data->pos.y + (((data->pos.x - dic->cross.x)
				/ cos(r_a * DEG)) * sin(r_a * DEG));
	dic->delta.y = -sin(r_a * DEG) * (dic->delta.x / cos(r_a * DEG));
	if (dic->cross.x < 0 || dic->cross.y < 0
		|| dic->cross.x >= (data->mapi.size_x * GRID)
		|| dic->cross.y >= (data->mapi.size_y * GRID))
		return ;
	while (data->map[(int)(dic->cross.y / GRID)]
			[(int)(dic->cross.x / GRID)] == 'X')
	{
		dic->cross.x = dic->cross.x + dic->delta.x;
		dic->cross.y = dic->cross.y + dic->delta.y;
		if (dic->cross.x < 0 || dic->cross.y < 0
			|| dic->cross.x >= (data->mapi.size_x * GRID)
			|| dic->cross.y >= (data->mapi.size_y * GRID))
			return ;
	}
	dic->dist = fabs(((data->pos.x - dic->cross.x) / cos(r_a * DEG))
			* cos((data->dir - r_a) * DEG));
}
