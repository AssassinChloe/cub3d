/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:15:38 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/25 11:52:42 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_check_for_comas(char *str)
{
	int	i;
	int	com;

	i = 0;
	com = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			com++;
			i++;
			while (str[i] && ft_isdigit(str[i]) != 1)
			{	
				if (str[i] == ',')
					return (-1);
				i++;
			}
			if (str[i] == '\0')
				return (-1);
		}
		else
			i++;
	}
	return (com);
}

int	ft_check_cf(t_data *data, char *line, char **tab, int i)
{
	if ((ft_check_for_comas(line) == 2 && (i >= 2 && i <= 4)
			&& (ft_strncmp(tab[0], "C", 2) == 0
				|| ft_strncmp(tab[0], "F", 2) == 0))
		|| ((ft_strncmp(tab[0], "EA", 3) == 0
				|| ft_strncmp(tab[0], "NO", 3) == 0
				|| ft_strncmp(tab[0], "SO", 3) == 0
				|| ft_strncmp(tab[0], "WE", 3) == 0)
			&& i == 2 && ft_check_for_comas(line) == 0))
	{
		if (ft_check_for_tex(data, tab) < 0)
		{
			ft_free_tab(tab, i);
			return (ft_error(-4));
		}
		ft_free_tab(tab, i);
		return (0);
	}
	ft_free_tab(tab, i);
	return (ft_error(6));
}

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
}
