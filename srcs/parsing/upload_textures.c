/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:06:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/09/08 19:26:35 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	upload_e_tex(char *path)
{
	if ((data())->map.e_tex)
	{
		mlx_destroy_image((data())->mlx.ptr, (data())->map.e_tex->img);
		(data())->map.e_tex->img = NULL;
		free((data())->map.e_tex);
		(data())->map.e_tex = NULL;
	}
	(data())->map.e_tex = malloc(sizeof(t_img));
	if (!(data())->map.e_tex)
		return (0);
	(data())->map.e_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.e_tex->width, &(data())->map.e_tex->height);
	free(path);
	if (!(data())->map.e_tex->img
		&& ft_putstr_fd("Error\nInvalid east texture path\n", 2))
		return (-1);
	(data())->map.e_tex->addr = mlx_get_data_addr((data())->map.e_tex->img,
			&(data())->map.e_tex->bits_per_pixel,
			&(data())->map.e_tex->line_length,
			&(data())->map.e_tex->endian);
	return (1);
}

int	upload_w_tex(char *path)
{
	if ((data())->map.w_tex)
	{
		mlx_destroy_image((data())->mlx.ptr, (data())->map.w_tex->img);
		(data())->map.w_tex->img = NULL;
		free((data())->map.w_tex);
		(data())->map.w_tex = NULL;
	}
	(data())->map.w_tex = malloc(sizeof(t_img));
	if (!(data())->map.w_tex)
		return (0);
	(data())->map.w_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.w_tex->width, &(data())->map.w_tex->height);
	free(path);
	if (!(data())->map.w_tex->img
		&& ft_putstr_fd("Error\nInvalid west texture path\n", 2))
		return (-1);
	(data())->map.w_tex->addr = mlx_get_data_addr((data())->map.w_tex->img,
			&(data())->map.w_tex->bits_per_pixel,
			&(data())->map.w_tex->line_length,
			&(data())->map.w_tex->endian);
	return (1);
}

int	thanks_norm(char ref, char *path)
{
	if (ref == 'n' && iset(&(data())->ret, upload_n_tex(path), 1))
		if (!(data())->ret || (data())->ret == -1)
			return ((data())->ret);
	if (ref == 's' && iset(&(data())->ret, upload_s_tex(path), 1))
		if (!(data())->ret || (data())->ret == -1)
			return ((data())->ret);
	if (ref == 'e' && iset(&(data())->ret, upload_e_tex(path), 1))
		if (!(data())->ret || (data())->ret == -1)
			return ((data())->ret);
	if (ref == 'w' && iset(&(data())->ret, upload_w_tex(path), 1))
		if (!(data())->ret || (data())->ret == -1)
			return ((data())->ret);
	return (1);
}

int	upload_textures(char *str, int *i, int j, char ref)
{
	char	*path;

	*i += 2;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	while (str[*i + j] && str[*i + j] != '\n')
		j++;
	path = malloc(sizeof(char *) * (j + 1));
	if (!path)
		return (0);
	j = -1;
	while (str[*i + ++j] && str[*i + j] != '\n')
		path[j] = str[*i + j];
	path[j] = '\0';
	if (!thanks_norm(ref, path) || (data())->ret == -1)
		return ((data())->ret);
	*i += j - 1;
	return ((data())->ret);
}
