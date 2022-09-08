/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:36:43 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/08 19:27:43 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	init_plane_dir(char dir)
{
	if (dir == 'N')
	{
		(data())->plane_x = 0;
		(data())->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		(data())->plane_x = 0;
		(data())->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		(data())->plane_x = 0.66;
		(data())->plane_y = 0;
	}
	else if (dir == 'W')
	{
		(data())->plane_x = -0.66;
		(data())->plane_y = 0;
	}
	return (1);
}

int	init_player_pos(int x, int y, char dir)
{
	(data())->pos_x = x;
	(data())->pos_y = y;
	if (dir == 'N')
	{
		(data())->dir_x = -1;
		(data())->dir_y = 0;
	}
	else if (dir == 'S')
	{
		(data())->dir_x = 1;
		(data())->dir_y = 0;
	}
	else if (dir == 'E')
	{
		(data())->dir_x = 0;
		(data())->dir_y = 1;
	}
	else if (dir == 'W')
	{
		(data())->dir_x = 0;
		(data())->dir_y = -1;
	}
	return (init_plane_dir(dir));
}

int	assign_2d_map_values(int j, int k, int l)
{
	if ((data())->map.map_infos[k + l] == ' ')
		(data())->map.map[j][l] = 0;
	else if ((data())->map.map_infos[k + l] == '0')
		(data())->map.map[j][l] = 1;
	else if ((data())->map.map_infos[k + l] == '1')
		(data())->map.map[j][l] = 2;
	else if ((data())->map.map_infos[k + l] == 'N'
		&& init_player_pos(j, l, 'N'))
		(data())->map.map[j][l] = 8;
	else if ((data())->map.map_infos[k + l] == 'S'
		&& init_player_pos(j, l, 'S'))
		(data())->map.map[j][l] = 5;
	else if ((data())->map.map_infos[k + l] == 'E'
		&& init_player_pos(j, l, 'E'))
		(data())->map.map[j][l] = 4;
	else if ((data())->map.map_infos[k + l] == 'W'
		&& init_player_pos(j, l, 'W'))
		(data())->map.map[j][l] = 6;
	else
	{
		free((data())->map.map[j]);
		(data())->map.map[j] = NULL;
		return (0);
	}
	return (1);
}

int	fill_2d_map(int i, int j, int k, int l)
{
	while ((data())->map.map_infos[++i])
	{
		if ((data())->map.map_infos[i] == '\n'
			&& (data())->map.map_infos[i - 1] != '\n')
		{
			(data())->map.map[++j] = malloc(sizeof(int) * (i - k + 1));
			l = -1;
			while (++l < (i - k))
				if (!assign_2d_map_values(j, k, l)
					&& ft_putstr_fd("Error\nWrong map synthax\n", 2))
					return (-1);
			(data())->map.map[j][l] = -1;
			k = i + 1;
		}
	}
	if (i > 0 && (data())->map.map_infos[i - 1] != '\n')
	{
		(data())->map.map[++j] = malloc(sizeof(int) * (i - k + 1));
		l = -1;
		while (++l < (i - k))
			if (!assign_2d_map_values(j, k, l)
				&& ft_putstr_fd("Error\nWrong map synthax\n", 2))
				return (-1);
		(data())->map.map[j][l] = -1;
	}
	return (check_map_infos(-1, 0, 0, 0));
}

int	create_2d_map(int i, int j, int k, int l)
{
	if ((!(data())->map.map_infos || (data())->map.c_color == -1
			|| (data())->map.f_color == -1 || !(data())->map.n_tex
			|| !(data())->map.s_tex || !(data())->map.e_tex
			|| !(data())->map.w_tex)
		&& ft_putstr_fd("Error\nMap data missing\n", 2))
		return (-1);
	while ((data())->map.map_infos[++i])
		if (i != 0 && (data())->map.map_infos[i] == '\n'
			&& (data())->map.map_infos[i - 1] != '\n')
			j++;
	if ((data())->map.map_infos[i - 1] != '\n')
		j++;
	(data())->map.map = malloc(sizeof(int *) * (j + 1));
	if (!(data())->map.map)
		return (0);
	(data())->map.map_size = j;
	(data())->map.map[j] = NULL;
	return (fill_2d_map(-1, -1, k, l));
}
