#include "../headers/cub3d.h"

void	init_file(t_config *file_info)
{
	file_info->north_path = NULL;
	file_info->south_path = NULL;
	file_info->east_path = NULL;
	file_info->west_path = NULL;
	file_info->sprite_path = NULL;
	file_info->first_map_line = NULL;
	file_info->checksum = 0;
}

void	init_map(t_map *map_file, char *name)
{
	map_file->map = NULL;
	map_file->name = ft_strdup(name);
	map_file->map_len = -1;
	map_file->map_hei = -1;
	map_file->player_x = -1;
	map_file->player_y = -1;
	map_file->written_lines = 0;
}
