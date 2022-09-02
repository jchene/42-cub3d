/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:06:26 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/30 00:24:52 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	upload_n_tex(char *path)
{
	(data())->map.n_tex = malloc(sizeof(t_img));
	if (!(data())->map.n_tex)
		return (0);
	(data())->map.n_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.n_tex->width, &(data())->map.n_tex->height);
	if (!(data())->map.n_tex->img
		&& ft_putstr_fd("Error\n Invalid north texture path\n", 1))
		return (-1);
	(data())->map.n_tex->addr = mlx_get_data_addr((data())->map.n_tex->img,
			&(data())->map.n_tex->bits_per_pixel,
			&(data())->map.n_tex->line_length,
			&(data())->map.n_tex->endian);
	return (1);
}

int	upload_s_tex(char *path)
{
	(data())->map.s_tex = malloc(sizeof(t_img));
	if (!(data())->map.s_tex)
		return (0);
	(data())->map.s_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.s_tex->width, &(data())->map.s_tex->height);
	if (!(data())->map.s_tex->img
		&& ft_putstr_fd("Error\n Invalid south texture path\n", 1))
		return (-1);
	(data())->map.s_tex->addr = mlx_get_data_addr((data())->map.s_tex->img,
			&(data())->map.s_tex->bits_per_pixel,
			&(data())->map.s_tex->line_length,
			&(data())->map.s_tex->endian);
	return (1);
}

int	upload_e_tex(char *path)
{
	(data())->map.e_tex = malloc(sizeof(t_img));
	if (!(data())->map.e_tex)
		return (0);
	(data())->map.e_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.e_tex->width, &(data())->map.e_tex->height);
	if (!(data())->map.e_tex->img
		&& ft_putstr_fd("Error\n Invalid east texture path\n", 1))
		return (-1);
	(data())->map.e_tex->addr = mlx_get_data_addr((data())->map.e_tex->img,
			&(data())->map.e_tex->bits_per_pixel,
			&(data())->map.e_tex->line_length,
			&(data())->map.e_tex->endian);
	return (1);
}

int	upload_w_tex(char *path)
{
	(data())->map.w_tex = malloc(sizeof(t_img));
	if (!(data())->map.w_tex)
		return (0);
	(data())->map.w_tex->img
		= mlx_xpm_file_to_image((data())->mlx.ptr, path,
			&(data())->map.w_tex->width, &(data())->map.w_tex->height);
	if (!(data())->map.w_tex->img
		&& ft_putstr_fd("Error\n Invalid west texture path\n", 1))
		return (-1);
	(data())->map.w_tex->addr = mlx_get_data_addr((data())->map.w_tex->img,
			&(data())->map.w_tex->bits_per_pixel,
			&(data())->map.w_tex->line_length,
			&(data())->map.w_tex->endian);
	return (1);
}

int	upload_textures(char *str, int *i, int j, char ref)
{
	char	*path;

	*i += 2;
	while (str[*i] && ft_iswhitespace(str[*i]))
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
	if (ref == 'n')
		(data())->ret = upload_n_tex(path);
	if (ref == 's')
		(data())->ret = upload_s_tex(path);
	if (ref == 'e')
		(data())->ret = upload_e_tex(path);
	if (ref == 'w')
		(data())->ret = upload_w_tex(path);
	*i += j - 1;
	free(path);
	return ((data())->ret);
}
