/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:59:52 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/04 18:23:13 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	get_map_infos(char *str, int *i, int j, int offset)
{
	if ((data())->map.map_infos
		&& ft_putstr_fd("Error\nWrong map synthax\n", 2))
		return (-1);
	while (*i + j >= 0 && str[*i + j] != '\n')
		j--;
	if (*i + j == 0 && ft_putstr_fd("Error\nMap pattern should be last\n", 2))
		return (-1);
	if (str[*i + j] == '\n')
		j++;
	offset = j;
	while (str[*i + j + offset])
		j++;
	(data())->map.map_infos = malloc(sizeof(char) * (j + 1));
	if (!(data())->map.map_infos)
		return (0);
	j = 0;
	while (str[*i + j + offset])
	{
		(data())->map.map_infos[j] = str[*i + j + offset];
		j++;
	}
	(data())->map.map_infos[j] = str[*i + j + offset];
	*i += j + offset - 1;
	return (1);
}

void	fill_map_struct_bis(char *str, int *i, int j)
{
	if (str[*i + 1] && str[*i] == 'E' && str[*i + 1] == 'A' && str[*i + 2]
		&& str[*i + 2] == ' ')
		if (!upload_textures(str, i, j, 'e') || (data())->ret == -1)
			return ;
	if (str[*i + 1] && str[*i] == 'W' && str[*i + 1] == 'E' && str[*i + 2]
		&& str[*i + 2] == ' ')
		if (!upload_textures(str, i, j, 'w') || (data())->ret == -1)
			return ;
	if (str[*i + 1] && str[*i] == 'F' && str[*i + 1] == ' ')
		if (!get_colors(str, i, -1, 'f') || (data())->ret == -1)
			return ;
	if (str[*i + 1] && str[*i] == 'C' && str[*i + 1] == ' ')
		get_colors(str, i, -1, 'c');
}

int	fill_map_struct(char *str, int i, int j)
{
	(data())->ret = 1;
	while (str[++i])
	{
		if (str[i + 1] && str[i] == 'N' && str[i + 1] == 'O' && str[i + 2]
			&& str[i + 2] == ' ')
			if (!upload_textures(str, &i, j, 'n') || (data())->ret == -1)
				return ((data())->ret);
		if (str[i + 1] && str[i] == 'S' && str[i + 1] == 'O' && str[i + 2]
			&& str[i + 2] == ' ')
			if (!upload_textures(str, &i, j, 's') || (data())->ret == -1)
				return ((data())->ret);
		fill_map_struct_bis(str, &i, j);
		if (!(data())->ret || (data())->ret == -1)
			return ((data())->ret);
		if (str[i] == '1')
		{
			(data())->ret = get_map_infos(str, &i, 0, 0);
			if (!(data())->ret || (data())->ret == -1)
				return ((data())->ret);
		}
	}
	return (create_2d_map(-1, 0, 0, 0));
}
