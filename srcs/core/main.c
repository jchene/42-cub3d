/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:03:36 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/04 21:25:14 by jchene           ###   ########.fr       */
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
	(data())->map.c_color = -1;
	(data())->map.f_color = -1;
	(data())->map.n_tex = NULL;
	(data())->map.s_tex = NULL;
	(data())->map.e_tex = NULL;
	(data())->map.w_tex = NULL;
	(data())->screen_width = 1800;
	(data())->screen_height = 900;
	(data())->moved = 1;
	(data())->display.img = NULL;
}

int	is_cub_file(char *path)
{
	short	i;

	i = -1;
	while (path[++i])
		continue ;
	i--;
	if (i < 4 || path[i] != 'b' || path[i - 1] != 'u'
		|| path[i - 2] != 'c' || path[i - 3] != '.')
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	if (!envp[0] && ft_putstr_fd("Error\nNo env, nice try\n", 2))
		return (0);
	init_data();
	if (ac == 2 && is_cub_file(av[1]))
	{
		(data())->mlx.ptr = mlx_init();
		(data())->ret = parse_file(av[1], 0, 0, NULL);
		if (!(data())->ret)
			return (exit_proprely(1));
		if ((data())->ret == -1)
			return (exit_proprely(-1));
		(data())->mlx.win
			= mlx_new_window((data())->mlx.ptr, 1800, 900, "Cub3d");
		mlx_hook((data())->mlx.win, 33, 1L << 2, close_button, NULL);
		mlx_hook((data())->mlx.win, 2, 1L, keypress_hook, NULL);
		mlx_hook((data())->mlx.win, 3, 1L << 1, keyrelease_hook, NULL);
		mlx_loop_hook((data())->mlx.ptr, loop_hook, NULL);
		mlx_loop((data())->mlx.ptr);
	}
	else
		ft_putstr_fd("Error\nWe want 1 .cub file\n", 2);
	return (exit_proprely(0));
}
