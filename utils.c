/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:15:38 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/23 12:19:53 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_arg(int argc, char**argv)
{
	int	i;
	int	j;
	int	fd;

	if (argc != 2)
		return (ft_error(1));
	j = 0;
	while (argv[1][j])
		j++;
	i = ft_strncmp(".cub", (argv[1] + (j - 4)), 5);
	if (i != 0)
		return (ft_error(2));
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (ft_error(7));
	}
	return (0);
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
