/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:40:09 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/08 19:44:41 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	fill_colors(int l, int ref, int colors[3])
{
	if (l != 2 && ft_putstr_fd("Error\nInvalid colors\n", 2))
		return (iset(&(data())->ret, -1, -1));
	if (colors[0] > 255 || colors[1] > 255 || colors[2] > 255)
	{
		ft_putstr_fd("Error\nInvalid colors\n", 2);
		return (iset(&(data())->ret, -1, -1));
	}
	if (ref == 'f')
		(data())->map.f_color = (colors[0] << 16 | colors[1] << 8 | colors[2]);
	else
		(data())->map.c_color = (colors[0] << 16 | colors[1] << 8 | colors[2]);
	return (1);
}

int	get_colors(char *str, int *i, int l, char ref)
{
	int		colors[3];
	char	color[4];
	int		k;

	while (str[++(*i) + 1] && str[*i + 1] == ' ')
		continue ;
	while (str[*i] != '\n' && str[++(*i)])
	{
		if (!ft_isdigit(str[*i]) && !ft_ischarset(" ,", str[*i])
			&& ft_putstr_fd("Error\nInvalid colors\n", 2))
			return (iset(&(data())->ret, -1, -1));
		if (ft_isdigit(str[*i]))
		{
			k = 0;
			while (ft_isdigit(str[*i]) && k < 3)
				color[k++] = str[(*i)++];
			color[k] = '\0';
			if ((!ft_ischarset(" ,\n", str[*i]) || l >= 3)
				&& ft_putstr_fd("Error\nInvalid colors\n", 2))
				return (iset(&(data())->ret, -1, -1));
			colors[++l] = ft_atoi(color);
		}
	}
	return (fill_colors(l, ref, colors));
}
