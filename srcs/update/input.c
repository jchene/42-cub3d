/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:25:56 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/03 19:16:31 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	keyrelease_hook(int keycode)
{
	if (keycode == 65307)
	{
		exit_proprely(0);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 119)
		(data())->move_up = 0;
	if (keycode == 115)
		(data())->move_down = 0;
	if (keycode == 97)
		(data())->move_left = 0;
	if (keycode == 100)
		(data())->move_right = 0;
	if (keycode == 65361)
		(data())->turn_left = 0;
	if (keycode == 65363)
		(data())->turn_right = 0;
	return (1);
}

int	keypress_hook(int keycode)
{
	if (keycode == 119)
		(data())->move_up = 1;
	if (keycode == 115)
		(data())->move_down = 1;
	if (keycode == 97)
		(data())->move_left = 1;
	if (keycode == 100)
		(data())->move_right = 1;
	if (keycode == 65361)
		(data())->turn_left = 1;
	if (keycode == 65363)
		(data())->turn_right = 1;
	return (1);
}
