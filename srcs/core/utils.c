/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:55:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/04 17:16:23 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	iset(int *to_set, int value, int ret)
{
	*to_set = value;
	return (ret);
}

void	turn_right(void)
{
	float	old_dir_x;
	float	old_plane_x;

	if ((data())->turn_right && ++(data())->moved)
	{
		old_dir_x = (data())->dir_x;
		(data())->dir_x = (data())->dir_x * cos(-ROTATE_SPEED)
			- (data())->dir_y * sin(-ROTATE_SPEED);
		(data())->dir_y = old_dir_x * sin(-ROTATE_SPEED) + (data())->dir_y
			* cos(-ROTATE_SPEED);
		old_plane_x = (data())->plane_x;
		(data())->plane_x = (data())->plane_x * cos(-ROTATE_SPEED)
			- (data())->plane_y * sin(-ROTATE_SPEED);
		(data())->plane_y = old_plane_x * sin(-ROTATE_SPEED) + (data())->plane_y
			* cos(-ROTATE_SPEED);
	}
}

void	turn_left(void)
{
	float	old_dir_x;
	float	old_plane_x;

	if ((data())->turn_left && ++(data())->moved)
	{
		old_dir_x = (data())->dir_x;
		(data())->dir_x = (data())->dir_x * cos(ROTATE_SPEED) - (data())->dir_y
			* sin(ROTATE_SPEED);
		(data())->dir_y = old_dir_x * sin(ROTATE_SPEED) + (data())->dir_y
			* cos(ROTATE_SPEED);
		old_plane_x = (data())->plane_x;
		(data())->plane_x = (data())->plane_x * cos(ROTATE_SPEED)
			- (data())->plane_y * sin(ROTATE_SPEED);
		(data())->plane_y = old_plane_x * sin(ROTATE_SPEED) + (data())->plane_y
			* cos(ROTATE_SPEED);
	}
	turn_right();
}
