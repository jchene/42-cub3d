/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_textures_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:10:54 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/08 19:26:12 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	upload_n_tex(char *path)
{
	if ((data())->map.n_tex)
	{
		mlx_destroy_image((data())->mlx.ptr, (data())->map.n_tex->img);
		(data())->map.n_tex->img = NULL;
		free((data())->map.n_tex);
		(data())->map.n_tex = NULL;
	}
	(data())->map.n_tex = malloc(sizeof(t_img));
	if (!(data())->map.n_tex)
		return (0);
	(data())->map.n_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.n_tex->width, &(data())->map.n_tex->height);
	free(path);
	if (!(data())->map.n_tex->img
		&& ft_putstr_fd("Error\nInvalid north texture path\n", 2))
		return (-1);
	(data())->map.n_tex->addr = mlx_get_data_addr((data())->map.n_tex->img,
			&(data())->map.n_tex->bits_per_pixel,
			&(data())->map.n_tex->line_length,
			&(data())->map.n_tex->endian);
	return (1);
}

int	upload_s_tex(char *path)
{
	if ((data())->map.s_tex)
	{
		mlx_destroy_image((data())->mlx.ptr, (data())->map.s_tex->img);
		(data())->map.s_tex->img = NULL;
		free((data())->map.s_tex);
		(data())->map.s_tex = NULL;
	}
	(data())->map.s_tex = malloc(sizeof(t_img));
	if (!(data())->map.s_tex)
		return (0);
	(data())->map.s_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.s_tex->width, &(data())->map.s_tex->height);
	free(path);
	if (!(data())->map.s_tex->img
		&& ft_putstr_fd("Error\nInvalid south texture path\n", 2))
		return (-1);
	(data())->map.s_tex->addr = mlx_get_data_addr((data())->map.s_tex->img,
			&(data())->map.s_tex->bits_per_pixel,
			&(data())->map.s_tex->line_length,
			&(data())->map.s_tex->endian);
	return (1);
}
