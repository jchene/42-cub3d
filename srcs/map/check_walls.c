/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:11:19 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/01 01:52:53 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	check_row(int i, int j, int k, int count)
{
	while (i - ++k >= 0)
		if ((data())->map.map[i - k][j] == 2 && ++count)
			break ;
	k = 0;
	while ((data())->map.map[i + ++k])
		if ((data())->map.map[i + k][j] == 2 && ++count)
			break ;
	if (count != 2)
		return (0);
	return (1);
}

int	check_line(int i, int j, int k, int count)
{
	while (j - ++k >= 0)
		if ((data())->map.map[i][j - k] == 2 && ++count)
			break ;
	k = 0;
	while ((data())->map.map[i][j + ++k] != -1)
		if ((data())->map.map[i][j + k] == 2 && ++count)
			break ;
	if (count != 2)
		return (0);
	return (1);
}

int	check_diago1(int i, int j, int k, int count)
{
	while (i - ++k >= 0 && j - k >= 0)
		if ((data())->map.map[i - k][j - k] == 2 && ++count)
			break ;
	k = 0;
	while ((data())->map.map[i + ++k]
		&& (data())->map.map[i + k][j + k] != -1)
		if ((data())->map.map[i + k][j + k] == 2 && ++count)
			break ;
	if (count != 2)
		return (0);
	return (1);
}

int	check_diago2(int i, int j, int k, int count)
{
	while (i - ++k >= 0 && (data())->map.map[i - k][j + k] != -1)
		if ((data())->map.map[i - k][j + k] == 2 && ++count)
			break ;
	k = 0;
	while (j - ++k >= 0 && (data())->map.map[i + k])
		if ((data())->map.map[i + k][j - k] == 2 && ++count)
			break ;
	if (count != 2)
		return (0);
	return (1);
}

int	check_map_walls(int i, int j)
{
	while ((data())->map.map[++i])
	{
		j = -1;
		while ((data())->map.map[i][++j] != -1)
		{
			if ((data())->map.map[i][j] == 1)
			{
				if (!check_row(i, j, 0, 0))
					return (0);
				if (!check_line(i, j, 0, 0))
					return (0);
				if (!check_diago1(i, j, 0, 0))
					return (0);
				if (!check_diago2(i, j, 0, 0))
					return (0);
			}
		}
	}
	return (1);
}
