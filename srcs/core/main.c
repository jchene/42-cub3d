/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:03:36 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/03 18:40:34 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	close_button(void)
{
	exit_proprely(0);
	exit(EXIT_SUCCESS);
	return (0);
}

void	init_data(void)
{
	data();
	(data())->mlx.ptr = NULL;
	(data())->mlx.win = NULL;
	(data())->map.map = NULL;
	(data())->map.map_infos = NULL;
	(data())->map.c_color = 0;
	(data())->map.f_color = 0;
	(data())->map.n_tex = NULL;
	(data())->map.s_tex = NULL;
	(data())->map.e_tex = NULL;
	(data())->map.w_tex = NULL;
	(data())->screen_width = 1800;
	(data())->screen_height = 900;
	(data())->moved = 1;
}

int	main(int ac, char **av)
{
	init_data();
	if (ac == 2)
	{
		(data())->mlx.ptr = mlx_init();
		(data())->ret = parse_file(av[1], 0, 0, NULL);
		if (!(data())->ret)
			return (exit_proprely(1));
		if ((data())->ret == -1)
			return (exit_proprely(0));
		(data())->mlx.win
			= mlx_new_window((data())->mlx.ptr, 1800, 900, "Cub3d");
		mlx_hook((data())->mlx.win, 33, 1L << 2, close_button, NULL);
		mlx_hook((data())->mlx.win, 2, 1L, keypress_hook, NULL);
		mlx_hook((data())->mlx.win, 3, 1L << 1, keyrelease_hook, NULL);
		mlx_loop_hook((data())->mlx.ptr, loop_hook, NULL);
		mlx_loop((data())->mlx.ptr);
	}
	else
		ft_putstr_fd("We want 1 .cub file\n", 1);
	return (exit_proprely(0));
}
