/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:59:48 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/03 18:26:15 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	free_textures(void)
{
	if ((data())->map.n_tex)
	{
		if ((data())->map.n_tex->img)
			mlx_destroy_image((data())->mlx.ptr, (data())->map.n_tex->img);
		free((data())->map.n_tex);
	}
	if ((data())->map.s_tex)
	{
		if ((data())->map.s_tex->img)
			mlx_destroy_image((data())->mlx.ptr, (data())->map.s_tex->img);
		free((data())->map.s_tex);
	}
	if ((data())->map.e_tex)
	{
		if ((data())->map.e_tex->img)
			mlx_destroy_image((data())->mlx.ptr, (data())->map.e_tex->img);
		free((data())->map.e_tex);
	}
	if ((data())->map.w_tex)
	{
		if ((data())->map.w_tex->img)
			mlx_destroy_image((data())->mlx.ptr, (data())->map.w_tex->img);
		free((data())->map.w_tex);
	}
}

int	exit_proprely(int ret)
{
	int	i;

	i = -1;
	free_textures();
	if ((data())->mlx.win)
		mlx_destroy_window((data())->mlx.ptr, (data())->mlx.win);
	if ((data())->mlx.ptr)
	{
		mlx_destroy_display((data())->mlx.ptr);
		free((data())->mlx.ptr);
	}
	if ((data())->map.map_infos)
		free((data())->map.map_infos);
	if ((data())->map.map)
	{
		while ((data())->map.map[++i])
			free((data())->map.map[i]);
		free((data())->map.map);
	}
	return (ret);
}
