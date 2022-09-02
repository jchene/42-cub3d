/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:59:52 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/30 23:47:45 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	fill_colors(int l, int ref, int colors[3])
{
	if (l != 2 && ft_putstr_fd("Error\n Invallid colors\n", 1))
		return (-1);
	if (ref == 'f')
		(data())->map.f_color = get_rgb(colors[0], colors[1], colors[2]);
	else
		(data())->map.c_color = get_rgb(colors[0], colors[1], colors[2]);
	return (1);
}

int	get_colors(char *str, int *i, int l, char ref)
{
	int		colors[3];
	char	color[4];
	int		k;

	color[3] = '\0';
	k = -1;
	l = -1;
	while (str[++(*i) + 1] && ft_iswhitespace(str[*i + 1]))
		continue ;
	while (str[++(*i)] && str[*i] != '\n')
	{
		if (!ft_isdigit(str[*i]) && !ft_ischarset(" ,", str[*i])
			&& ft_putstr_fd("Error\n Invalid colors\n", 1))
			return (-1);
		if (ft_isdigit(str[*i]))
			color[++k] = str[*i];
		if (str[*i] == ',' || str[*i + 1] == '\n')
		{
			while (k < 3)
				color[++k] = '\0';
			k = -1;
			colors[++l] = (int)ft_atoi(color);
		}
	}
	return (fill_colors(l, ref, colors));
}

int	get_map_infos(char *str, int *i, int j, int offset)
{
	if ((data())->map.map_infos
		&& ft_putstr_fd("Error\n Invalid map synthax\n", 1))
		return (-1);
	while (*i + j >= 0 && str[*i + j] != '\n')
		j--;
	if (str[*i + j] == '\n')
		j++;
	offset = j;
	if (*i + j == 0 && ft_putstr_fd("Error\n Map pattern should be last\n", 1))
		return (-1);
	while (str[*i + j])
		j++;
	(data())->map.map_infos = malloc(sizeof(char) * (offset + j + 1));
	if (!(data())->map.map_infos)
		return (0);
	j = 0;
	while (str[*i + j + offset])
	{
		(data())->map.map_infos[j] = str[*i + j + offset];
		j++;
	}
	(data())->map.map_infos[j] = str[*i + j + offset];
	*i += j - 1;
	return (1);
}

int	fill_map_struct(char *str, int i, int j)
{
	while (str[++i])
	{
		if (str[i + 1] && str[i] == 'N' && str[i + 1] == 'O')
			(data())->ret = upload_textures(str, &i, j, 'n');
		if (str[i + 1] && str[i] == 'S' && str[i + 1] == 'O')
			(data())->ret = upload_textures(str, &i, j, 's');
		if (str[i + 1] && str[i] == 'E' && str[i + 1] == 'A')
			(data())->ret = upload_textures(str, &i, j, 'e');
		if (str[i + 1] && str[i] == 'W' && str[i + 1] == 'E')
			(data())->ret = upload_textures(str, &i, j, 'w');
		if (str[i + 1] && str[i] == 'F' && str[i + 1] == ' ')
			(data())->ret = get_colors(str, &i, j, 'f');
		if (str[i + 1] && str[i] == 'C' && str[i + 1] == ' ')
			(data())->ret = get_colors(str, &i, j, 'c');
		if (str[i + 1] && str[i] == '1' && str[i + 1] == '1')
		{
			(data())->ret = get_map_infos(str, &i, 0, 0);
			if (str[i + 1] && ((data())->ret == 1)
				&& ft_putstr_fd("Error\n Map pattern should be last\n", 1))
				return (-1);
		}
		if (!(data())->ret || (data())->ret == -1)
			return ((data())->ret);
	}
	return (create_2d_map(-1, 0, 0, 0));
}
