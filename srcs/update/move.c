/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:33:13 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/04 22:47:27 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	turn_right(void)
{
	double	old_dir_x;
	double	old_plane_x;

	if ((data())->turn_right && ++(data())->moved)
	{
		old_dir_x = (data())->dir_x;
		(data())->dir_x = (data())->dir_x * cos(-0.2)
			- (data())->dir_y * sin(-0.2);
		(data())->dir_y = old_dir_x * sin(-0.2) + (data())->dir_y * cos(-0.2);
		old_plane_x = (data())->plane_x;
		(data())->plane_x = (data())->plane_x * cos(-0.2) - (data())->plane_y
			* sin(-0.2);
		(data())->plane_y = old_plane_x * sin(-0.2) + (data())->plane_y
			* cos(-0.2);
	}
}

void	turn_left(void)
{
	double	old_dir_x;
	double	old_plane_x;

	if ((data())->turn_left && ++(data())->moved)
	{
		old_dir_x = (data())->dir_x;
		(data())->dir_x = (data())->dir_x * cos(0.2) - (data())->dir_y
			* sin(0.2);
		(data())->dir_y = old_dir_x * sin(0.2) + (data())->dir_y * cos(0.2);
		old_plane_x = (data())->plane_x;
		(data())->plane_x = (data())->plane_x * cos(0.2) - (data())->plane_y
			* sin(0.2);
		(data())->plane_y = old_plane_x * sin(0.2) + (data())->plane_y
			* cos(0.2);
	}
	turn_right();
}

void	move_right(void)
{
	if ((data())->move_right && ++(data())->moved)
	{
		if ((data())->pos_x + (((data())->dir_x * cos(M_PI / -2)
					- (data())->dir_y * sin(M_PI / -2)) * 0.1)
			< (data())->map.map_size
			&& (data())->pos_x + (((data())->dir_x * cos(M_PI / -2)
					- (data())->dir_y * sin(M_PI / -2)) * 0.1) >= 0)
			(data())->pos_x += ((data())->dir_x * cos(M_PI / -2)
					- (data())->dir_y * sin(M_PI / -2)) * 0.1;
		if ((data())->pos_y + (((data())->dir_x * sin(M_PI / -2)
					+ (data())->dir_y * cos(M_PI / -2)) * 0.1) >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + (((data())->dir_x * sin(M_PI / -2)
					+ (data())->dir_y * cos(M_PI / -2)) * 0.1))] != -1)
			(data())->pos_y += ((data())->dir_x * sin(M_PI / -2)
					+ (data())->dir_y * cos(M_PI / -2)) * 0.1;
	}
	turn_left();
}

void	move_left(void)
{
	if ((data())->move_left && ++(data())->moved)
	{
		if ((data())->pos_x + (((data())->dir_x * cos(M_PI / 2)
					- (data())->dir_y * sin(M_PI / 2)) * 0.1)
			< (data())->map.map_size
			&& (data())->pos_x + (((data())->dir_x * cos(M_PI / 2)
					- (data())->dir_y * sin(M_PI / 2)) * 0.1) >= 0)
			(data())->pos_x += ((data())->dir_x * cos(M_PI / 2)
					- (data())->dir_y * sin(M_PI / 2)) * 0.1;
		if ((data())->pos_y + (((data())->dir_x * sin(M_PI / 2)
					+ (data())->dir_y * cos(M_PI / 2)) * 0.1) >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + (((data())->dir_x * sin(M_PI / 2)
					+ (data())->dir_y * cos(M_PI / 2)) * 0.1))] != -1)
			(data())->pos_y += ((data())->dir_x * sin(M_PI / 2)
					+ (data())->dir_y * cos(M_PI / 2)) * 0.1;
	}
	move_right();
}

void	move(void)
{
	if ((data())->move_up && ++(data())->moved)
	{
		if ((data())->pos_x + ((data())->dir_x * 0.2) < (data())->map.map_size
			&& (data())->pos_x + ((data())->dir_x * 0.2) >= 0)
			(data())->pos_x += (data())->dir_x * 0.2;
		if ((data())->pos_y + ((data())->dir_y * 0.2) >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + ((data())->dir_y * 0.2))] != -1)
			(data())->pos_y += (data())->dir_y * 0.2;
	}
	if ((data())->move_down && ++(data())->moved)
	{
		if ((data())->pos_x - ((data())->dir_x * 0.1) < (data())->map.map_size
			&& (data())->pos_x - ((data())->dir_x * 0.1) >= 0)
			(data())->pos_x -= (data())->dir_x * 0.1;
		if ((data())->pos_y - ((data())->dir_y * 0.1) >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y - ((data())->dir_y * 0.1))] != -1)
			(data())->pos_y -= (data())->dir_y * 0.1;
	}
	move_left();
}
