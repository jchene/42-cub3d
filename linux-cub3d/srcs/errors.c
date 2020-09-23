#include "../headers/cub3d.h"

int		display_error(char *error)
{
	if (!(ft_strcmp("nb-arg", error)))
		ft_putstr("Error\nWrong number of arguments!");
	else if (!(ft_strcmp("file-nf", error)))
		ft_putstr("Error\nFile not found");
	else if (!(ft_strcmp("w-arg", error)))
		ft_putstr("Error\nWrong file arguments!\n");
	else if (!(ft_strcmp("m-arg", error)))
		ft_putstr("Error\nMissing file argument!\n");
	else if (!(ft_strcmp("no-map", error)))
		ft_putstr("Error\nNo map found!\n");
	return (-1);
}

void	display_missing(int argument)
{
	if (argument == 0)
		ft_putstr("Resolution missing!\n");
	else if (argument == 1)
		ft_putstr("North texture path missing!\n");
	else if (argument == 2)
		ft_putstr("South texture path missing!\n");
	else if (argument == 3)
		ft_putstr("East texture path missing!\n");
	else if (argument == 4)
		ft_putstr("West texture path missing!\n");
	else if (argument == 5)
		ft_putstr("Floor color missing!\n");
	else if (argument == 6)
		ft_putstr("Ceiling color missing!\n");
	else if (argument == 7)
		ft_putstr("Sprite texture missing!\n");
}

int		display_wrong_arg(char *error)
{
	if (!(ft_strcmp("color-range", error)))
		ft_putstr("Color range is 0-255!\n");
	else if (!(ft_strcmp("color-comma", error)))
		ft_putstr("Colors must be separated by commas!\n");
	else if (!(ft_strcmp("resolution", error)))
		ft_putstr("Resolution must be two numbers!\n");
	return (-1);
}

int		missing_arg(int checksum)
{
	char	checksum_bin[9];
	int		i;

	i = 0;
	display_error("m-arg");
	while (checksum > 0)
	{
		checksum_bin[7 - i] = '0' + (checksum % 2);
		checksum /= 2;
		i++;
	}
	checksum_bin[8] = '\0';
	i = 0;
	while (i < 8)
	{
		if (checksum_bin[i] == '0')
			display_missing(i);
		i++;
	}
	return (-1);
}

void	display_info(t_config *file_info)
{
	printf("Resolution: %d %d\nFloor color: %d %d %d\nCeiling color: %d %d %d\
		\nNorth texture Path: %s\nSouth texture path: %s\nEast texture path: %s\
		\nWest texture path: %s\nSprite texture path: %s\nFirst line of map: %s\
		\nChecksum: %d\n", file_info->resolution[0],
		file_info->resolution[1], file_info->floor_color[0],
		file_info->floor_color[1], file_info->floor_color[2],
		file_info->ceiling_color[0], file_info->ceiling_color[1],
		file_info->ceiling_color[2], file_info->north_path,
		file_info->south_path, file_info->east_path, file_info->west_path,
		file_info->sprite_path, file_info->first_map_line, file_info->checksum);
}
