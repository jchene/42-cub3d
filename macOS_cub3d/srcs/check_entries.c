#include "../headers/cub3d.h"

int		check_horizontal(char **map)
{
	char	*line;
	char	last_no_floor;
	char	last_case;

	while (**map)
	{
		last_no_floor = ' ';
		last_case = ' ';
		line = *map;
		while (*line)
		{
			if (*line == ' ' && is_charset(last_case, "02NSEW"))
				return (map_errors("trou"));
			if (is_charset(*line, " 1"))
				last_no_floor = *line;
			else if (last_no_floor == ' ')
				return (map_errors("trou"));
			last_case = *line;
			line++;
		}
		if (last_case == '0')
			return (map_errors("trou"));
		map++;
	}
	return (0);
}

int		init_buff(t_map *map_file, t_map *new_file)
{
	int		y;

	new_file->name = ft_strdup("rotate");
	new_file->map_hei = map_file->map_len;
	new_file->map_len = map_file->map_hei;
	new_file->written_lines = map_file->map_len;
	if (!(new_file->map = (char **)ft_calloc(map_file->map_len + 1,
			sizeof(char *))))
		return (-1);
	y = 0;
	while (y < map_file->map_len + 1)
	{
		if (!(new_file->map[y] = (char *)ft_calloc(map_file->map_hei + 1,
				sizeof(char))))
			return (-1);
		y++;
	}
	return (0);
}

int		check_vertical(t_map *map_file)
{
	int		x;
	int		y;
	t_map	*new_file;

	if (!(new_file = (t_map *)ft_calloc(1, sizeof(t_map))))
		return (-1);
	init_buff(map_file, new_file);
	y = -1;
	while (++y < map_file->map_hei)
	{
		x = -1;
		while (++x < map_file->map_len)
		{
			if (is_charset(map_file->map[y][x], "NSEW"))
			{
				map_file->player_x = x;
				map_file->player_y = y;
			}
			new_file->map[map_file->map_len - x - 1][y] = map_file->map[y][x];
		}
	}
	if (check_horizontal(new_file->map) == -1)
		return (free_map(new_file));
	free_map(new_file);
	return (0);
}
