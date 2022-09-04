/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:33:13 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/04 17:19:53 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	move_right(void)
{
	float	value;

	if ((data())->move_right && ++(data())->moved)
	{
		value = (((data())->dir_x * cos(M_PI / -2)
					- (data())->dir_y * sin(M_PI / -2)) * SIDE_SPEED);
		if ((data())->pos_x + value < (data())->map.map_size
			&& (data())->pos_x + value >= 0
			&& (data())->map.map
			[(int)((data())->pos_x + value)][(int)(data())->pos_y] != 2)
			(data())->pos_x += value;
		value = (((data())->dir_x * sin(M_PI / -2)
					+ (data())->dir_y * cos(M_PI / -2)) * SIDE_SPEED);
		if ((data())->pos_y + value >= 0
			&& (data())->map.map
			[(int)(data())->pos_x][(int)((data())->pos_y + value)] != -1
			&& (data())->map.map
			[(int)(data())->pos_x][(int)((data())->pos_y + value)] != 2)
			(data())->pos_y += value;
	}
	turn_left();
}

void	move_left(void)
{
	float	value;

	if ((data())->move_left && ++(data())->moved)
	{
		value = (((data())->dir_x * cos(M_PI / 2)
					- (data())->dir_y * sin(M_PI / 2)) * SIDE_SPEED);
		if ((data())->pos_x + value < (data())->map.map_size
			&& (data())->pos_x + value >= 0
			&& (data())->map.map[(int)((data())->pos_x + value)]
			[(int)(data())->pos_y] != 2)
			(data())->pos_x += value;
		value = (((data())->dir_x * sin(M_PI / 2)
					+ (data())->dir_y * cos(M_PI / 2)) * SIDE_SPEED);
		if ((data())->pos_y + value >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + value)] != -1
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + value)] != 2)
			(data())->pos_y += value;
	}
	move_right();
}

void	move_down(void)
{
	float	value;

	if ((data())->move_down && ++(data())->moved)
	{
		value = (data())->dir_x * BWD_SPEED;
		if ((data())->pos_x - value < (data())->map.map_size
			&& (data())->pos_x - value >= 0
			&& (data())->map.map[(int)((data())->pos_x - value)]
			[(int)(data())->pos_y] != 2)
			(data())->pos_x -= value;
		value = (data())->dir_y * BWD_SPEED;
		if ((data())->pos_y - value >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y - value)] != -1
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y - value)] != 2)
			(data())->pos_y -= value;
	}
	move_left();
}

void	move_up(void)
{
	float	value;

	if ((data())->move_up && ++(data())->moved)
	{
		value = (data())->dir_x * FWD_SPEED;
		if ((data())->pos_x + value < (data())->map.map_size
			&& (data())->pos_x + value >= 0
			&& (data())->map.map[(int)((data())->pos_x + value)]
			[(int)(data())->pos_y] != 2)
			(data())->pos_x += value;
		value = (data())->dir_y * FWD_SPEED;
		if ((data())->pos_y + value >= 0
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + value)] != -1
			&& (data())->map.map[(int)(data())->pos_x]
			[(int)((data())->pos_y + value)] != 2)
			(data())->pos_y += value;
	}
	move_down();
}
