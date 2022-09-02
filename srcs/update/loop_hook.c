/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:25:57 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/02 19:19:33 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	check_for_hit(void)
{
	if ((data())->ray_x < 0 || (data())->ray_x > (data())->map.map_size - 1)
		(data())->hit++;
	else if ((data())->ray_y < 0
		|| (data())->map.map[(data())->ray_x][(data())->ray_y] == -1)
		(data())->hit++;
	else if ((data())->map.map[(data())->ray_x][(data())->ray_y] == 2)
		(data())->hit++;
}

void	find_wall(void)
{
	while (!(data())->hit)
	{
		if (!(data())->dist_y || ((data())->dist_x
				&& (data())->total_dist_x < (data())->total_dist_y))
		{
			(data())->total_dist_x += (data())->dist_x;
			(data())->ray_x += (data())->step_x;
			(data())->side = 0;
		}
		else
		{
			(data())->total_dist_y += (data())->dist_y;
			(data())->ray_y += (data())->step_y;
			(data())->side = 1;
		}
		check_for_hit();
	}
	if ((data())->side == 0)
		(data())->wall_dist = ((data())->ray_x - (data())->pos_x
				+ (1 - (data())->step_x) / 2) / (data())->ray_dir_x;
	else
		(data())->wall_dist = ((data())->ray_y - (data())->pos_y
				+ (1 - (data())->step_y) / 2) / (data())->ray_dir_y;
}

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

void	redraw_screen(void)
{
	(data())->screen_x = -1;
	while (++(data())->screen_x < (data())->screen_width)
	{
		init_values();
		find_wall();
		(data())->line_size = (int)(((data())->screen_height
					/ (data())->wall_dist));
		(data())->draw_start = -((data())->line_size / 2)
			+ ((data())->screen_height / 2);
		if ((data())->draw_start < 0)
			(data())->draw_start = 0;
		(data())->draw_end = ((data())->line_size / 2)
			+ ((data())->screen_height / 2);
		if ((data())->draw_end >= (data())->screen_height)
			(data())->draw_end = (data())->screen_height - 1;
		if ((data())->side == 1)
			(data())->tex_x_offset = (data())->pos_x
				+ ((data())->wall_dist * (data())->ray_dir_x);
		else
			(data())->tex_x_offset = (data())->pos_y
				+ ((data())->wall_dist * (data())->ray_dir_y);
		(data())->tex_x_offset -= floorf((data())->tex_x_offset);
		draw_line((data())->screen_x, -1, 0);
	}
}

int	loop_hook(void)
{
	move();
	if (!(data())->moved)
		return (1);
	(data())->moved = 0;
	(data())->display.img = mlx_new_image((data())->mlx.ptr,
			(data())->screen_width, (data())->screen_height);
	(data())->display.addr = mlx_get_data_addr((data())->display.img,
			&((data())->display.bits_per_pixel),
			&((data())->display.line_length),
			&((data())->display.endian));
	redraw_screen();
	mlx_put_image_to_window((data())->mlx.ptr, (data())->mlx.win,
		(data())->display.img, 0, 0);
	return (1);
}
