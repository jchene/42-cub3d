#include "../headers/cub3d.h"

void	size_map(int map_id, t_map *map_file, char *first_line)
{
	char	*line;

	map_file->map_len = ft_strlen(first_line);
	map_file->map_hei = 1;
	while (get_next_line(map_id, &line) && line_type(line) == 2)
	{
		if (map_file->map_len < ft_strlen(line))
			map_file->map_len = ft_strlen(line);
		map_file->map_hei++;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
}

int		copy_map(int map_id, t_map *map_file, char *first_line)
{
	int		i;
	char	*line;

	while (get_next_line(map_id, &line) && line_type(line) != 2)
		free(line);
	free(line);
	if (!(map_file->map = (char **)ft_calloc(map_file->map_hei + 1,
			sizeof(char *))))
		return (-1);
	i = 0;
	while (i < map_file->map_hei + 1)
		if (!(map_file->map[i++] = (char *)ft_calloc(map_file->map_len + 1,
				sizeof(char))))
			return (-1);
	i = 1;
	map_file->written_lines = 1;
	ft_strcpy(first_line, map_file->map[0]);
	while (get_next_line(map_id, &line) && line_type(line) == 2)
	{
		ft_strcpy(line, &map_file->map[i++][0]);
		map_file->written_lines++;
		free(line);
	}
	free(line);
	return (0);
}

void	fill_spaces(t_map *map_file)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < map_file->map_hei)
	{
		while (j < map_file->map_len)
		{
			if (map_file->map[i][j] == '\0')
				map_file->map[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
}

void	display_map(t_map *map_file)
{
	int		i;

	i = 0;
	printf("Heigth: %d\nLength: %d\n", map_file->map_hei, map_file->map_len);
	while (i < map_file->map_hei)
		printf("|%s|\n", map_file->map[i++]);
}

int		map_errors(char *error)
{
	if (!(ft_strcmp("trou", error)))
		printf("Error\nMap is not closed\n");
	return (-1);
}
