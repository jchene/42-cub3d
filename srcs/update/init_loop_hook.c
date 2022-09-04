/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loop_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:18:57 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/03 15:21:04 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	init_values_bis(void)
{
	if ((data())->ray_dir_x < 0)
	{
		(data())->step_x = -1;
		(data())->total_dist_x = ((data())->pos_x - (data())->ray_x)
			* (data())->dist_x;
	}
	else
	{
		(data())->step_x = 1;
		(data())->total_dist_x = ((data())->ray_x + 1 - (data())->pos_x)
			* (data())->dist_x;
	}
	if ((data())->ray_dir_y < 0)
	{
		(data())->step_y = -1;
		(data())->total_dist_y = ((data())->pos_y - (data())->ray_y)
			* (data())->dist_y;
	}
	else
	{
		(data())->step_y = 1;
		(data())->total_dist_y = ((data())->ray_y + 1 - (data())->pos_y)
			* (data())->dist_y;
	}
}

void	init_values(void)
{
	(data())->ratio
		= ((float)(data())->screen_x - (float)((data())->screen_width * 0.5))
		/ (float)((data())->screen_width * 0.5);
	(data())->ray_dir_x = (data())->dir_x
		+ ((data())->plane_x * (data())->ratio);
	(data())->ray_dir_y = (data())->dir_y
		+ ((data())->plane_y * (data())->ratio);
	(data())->ray_x = (data())->pos_x;
	(data())->ray_y = (data())->pos_y;
	if (!(data())->ray_dir_x)
		(data())->dist_x = 0;
	else
		(data())->dist_x = sqrtf(1 + (powf((data())->ray_dir_y, 2)
					/ powf((data())->ray_dir_x, 2)));
	if (!(data())->ray_dir_y)
		(data())->dist_y = 0;
	else
		(data())->dist_y = sqrtf(1 + (powf((data())->ray_dir_x, 2)
					/ powf((data())->ray_dir_y, 2)));
	init_values_bis();
	(data())->hit = 0;
}
