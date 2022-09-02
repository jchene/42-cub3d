/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_infos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:33:18 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/01 02:15:35 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_missing_value(int i, int j, int count)
{
	int	finded[2];

	finded[0] = 0;
	finded[1] = 0;
	while ((data())->map.map[++i])
	{
		j = -1;
		while ((data())->map.map[i][++j] != -1)
		{
			if ((data())->map.map[i][j] == 1 && !finded[0] && ++count)
				finded[0] = 1;
			if ((data())->map.map[i][j] == 2 && !finded[1] && ++count)
				finded[1] = 1;
			if (((data())->map.map[i][j] == 8 || (data())->map.map[i][j] == 6
				|| (data())->map.map[i][j] == 4 || (data())->map.map[i][j] == 5)
				&& ++count)
				finded[1] = 1;
		}
	}
	if (!finded[0] || !finded[1])
		return (-1);
	return (count);
}

int	check_that_case(int *i, int *j, int *inside)
{
	if ((data())->map.map[*i][*j] == 2)
			*inside = 1;
	if (!inside && (data())->map.map[*i][*j] != 0
		&& ft_putstr_fd("Error\nWrong map synthax\n", 1))
		return (0);
	if (*inside)
		if ((data())->map.map[*i][*j] != 2 && (data())->map.map[*i][*j] != 1
			&& (data())->map.map[*i][*j] != 8 && (data())->map.map[*i][*j] != 5
			&& (data())->map.map[*i][*j] != 4 && (data())->map.map[*i][*j] != 6
			&& (data())->map.map[*i][*j] != 0
			&& ft_putstr_fd("Error\nWrong map synthax\n", 1))
			return (0);
	if ((data())->map.map[*i][*j] == -1)
		(*j)--;
	return (1);
}

int	check_that_line(int *i, int *j, int *inside, int k)
{
	*j = -1;
	*inside = 0;
	while ((data())->map.map[*i][++(*j)] != -1)
		if (!check_that_case(i, j, inside))
			return (0);
	while ((data())->map.map[*i][*j - ++k] != 2)
		if ((data())->map.map[*i][*j - k] != 0
			&& ft_putstr_fd("Error\nWrong map synthax\n", 1))
			return (0);
	return (1);
}

int	check_map_infos(int i, int j, int inside, int e_count)
{
	e_count = check_missing_value(-1, -1, 0);
	if (e_count != 3 && ft_putstr_fd("Error\nWrong map synthax\n", 1))
		return (-1);
	if (!check_map_walls(-1, -1)
		&& ft_putstr_fd("Error\nWalls don't cover the map\n", 1))
		return (-1);
	while ((data())->map.map[++i])
		if (!check_that_line(&i, &j, &inside, 0))
			return (-1);
	return (1);
}
