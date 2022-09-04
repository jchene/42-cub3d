/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:25:52 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/03 18:28:47 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	ft_put_pixel_to_image(t_img *data, int x, int y, int color)
{
	char	*addr;

	addr = (data->addr + ((y * data->line_length + x
					* (data->bits_per_pixel / 8))));
	*(unsigned int *)addr = color;
}

void	put_from_tex(int x, int y, int i, int j)
{
	if ((data())->side == 0)
	{
		if ((data())->ray_dir_x > 0)
			(data())->actual_tex = (data())->map.n_tex;
		else
			(data())->actual_tex = (data())->map.s_tex;
	}
	else
	{
		if ((data())->ray_dir_y < 0)
			(data())->actual_tex = (data())->map.e_tex;
		else
			(data())->actual_tex = (data())->map.w_tex;
	}
	i = (data())->tex_x_offset * (data())->actual_tex->width;
	j = (y - (data())->draw_start - (data())->tex_y_offset)
		* (float)((float)(data())->actual_tex->height / (data())->line_size);
	if ((data())->side == 0 && (data())->ray_dir_x > 0)
		i = (data())->actual_tex->width - i - 1;
	if ((data())->side == 1 && (data())->ray_dir_y < 0)
		i = (data())->actual_tex->width - i - 1;
	ft_put_pixel_to_image(&((data())->display), x, y,
		*(unsigned int *)((data())->actual_tex->addr
			+ ((j * (data())->actual_tex->line_length)
				+ (i * ((data())->actual_tex->bits_per_pixel / 8)))));
}

int	draw_line(int x, int y, int color)
{
	while (++y < (data())->screen_height)
	{
		if (y < (data())->draw_start || y > (data())->draw_end
			|| (data())->dont_draw)
		{
			color = (data())->map.c_color;
			if (y >= (data())->screen_height / 2)
				color = (data())->map.f_color;
			ft_put_pixel_to_image(&((data())->display), x, y, color);
		}
		else
			put_from_tex(x, y, 0, 0);
	}
	return (iset(&(data())->dont_draw, 0, 1));
}
