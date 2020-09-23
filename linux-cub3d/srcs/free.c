#include "../headers/cub3d.h"

void	free_arg(int argument, t_config *file_info)
{
	if (argument == 1)
		free(file_info->north_path);
	else if (argument == 2)
		free(file_info->south_path);
	else if (argument == 3)
		free(file_info->east_path);
	else if (argument == 4)
		free(file_info->west_path);
	else if (argument == 7)
		free(file_info->sprite_path);
}

int		free_file(t_config *file_info, int map_id)
{
	char	checksum_bin[9];
	int		i;

	i = 0;
	while (file_info->checksum > 0)
	{
		checksum_bin[7 - i] = '0' + (file_info->checksum % 2);
		file_info->checksum /= 2;
		i++;
	}
	checksum_bin[8] = '\0';
	i = 0;
	while (i < 8)
	{
		if (checksum_bin[i] == '1')
			free_arg(i, file_info);
		i++;
	}
	if (file_info->first_map_line != NULL)
		free(file_info->first_map_line);
	free(file_info);
	close(map_id);
	return (-1);
}

int		free_all(t_config *file_info, t_map *map_file, t_mlx *mlx_ptrs)
{
	int		i;

	i = 0;
	free(file_info->north_path);
	free(file_info->south_path);
	free(file_info->west_path);
	free(file_info->east_path);
	free(file_info->sprite_path);
	free(file_info->first_map_line);
	free(file_info);
	while (i < map_file->map_hei + 1)
		free(map_file->map[i++]);
	free(map_file->map);
	free(map_file->name);
	free(map_file);
	free(mlx_ptrs->mlx);
	free(mlx_ptrs->win);
	free(mlx_ptrs);
	return (0);
}

int		free_map(t_map *map_file)
{
	int		i;

	i = 0;
	while (i < map_file->written_lines + 1)
		free(map_file->map[i++]);
	free(map_file->map);
	free(map_file->name);
	free(map_file);
	return (0);
}
