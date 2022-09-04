/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:25:57 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/04 17:10:46 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	check_for_hit(void)
{
	if ((data())->ray_x < 0 || (data())->ray_x > (data())->map.map_size - 1)
	{
		(data())->hit++;
		(data())->dont_draw = 1;
	}
	else if ((data())->ray_y < 0
		|| (data())->map.map[(data())->ray_x][(data())->ray_y] == -1
		|| (data())->map.map[(data())->ray_x][(data())->ray_y] == 0)
	{
		(data())->hit++;
		(data())->dont_draw = 1;
	}
	else if ((data())->map.map[(data())->ray_x][(data())->ray_y] == 2)
		(data())->hit++;
}

void	get_dist(void)
{
	if ((data())->side == 0)
		(data())->wall_dist = ((data())->ray_x - (data())->pos_x
				+ (1 - (data())->step_x) / 2) / (data())->ray_dir_x;
	else
		(data())->wall_dist = ((data())->ray_y - (data())->pos_y
				+ (1 - (data())->step_y) / 2) / (data())->ray_dir_y;
	if ((data())->wall_dist < 0.1)
		(data())->wall_dist = 0.1;
	(data())->line_size = (int)(((data())->screen_height
				/ (data())->wall_dist));
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
	get_dist();
}

void	redraw_screen(void)
{
	while (++(data())->screen_x < (data())->screen_width)
	{
		init_values();
		find_wall();
		(data())->draw_start = -((data())->line_size / 2)
			+ ((data())->screen_height / 2);
		(data())->tex_y_offset = 0;
		if ((data())->draw_start < 0)
			(data())->tex_y_offset = (data())->draw_start;
		if ((data())->draw_start < 0)
			(data())->draw_start = 0;
		(data())->draw_end = ((data())->line_size / 2)
			+ ((data())->screen_height / 2) - 1;
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
	move_up();
	if (!(data())->moved)
		return (1);
	(data())->moved = 0;
	(data())->display.img = mlx_new_image((data())->mlx.ptr,
			(data())->screen_width, (data())->screen_height);
	(data())->display.addr = mlx_get_data_addr((data())->display.img,
			&((data())->display.bits_per_pixel),
			&((data())->display.line_length),
			&((data())->display.endian));
	(data())->screen_x = -1;
	redraw_screen();
	mlx_put_image_to_window((data())->mlx.ptr, (data())->mlx.win,
		(data())->display.img, 0, 0);
	mlx_destroy_image((data())->mlx.ptr, (data())->display.img);
	return (1);
}
