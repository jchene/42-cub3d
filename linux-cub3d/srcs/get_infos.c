#include "../headers/cub3d.h"

void	get_path(char *line, char *first_word, t_config *file_info)
{
	char	*path;

	path = get_first_word(line + ft_wordlen(first_word));
	if (!(ft_strcmp(first_word, "NO")) && (file_info->checksum += 64))
		file_info->north_path = ft_strdup(path);
	else if (!(ft_strcmp(first_word, "SO")) && (file_info->checksum += 32))
		file_info->south_path = ft_strdup(path);
	else if (!(ft_strcmp(first_word, "EA")) && (file_info->checksum += 16))
		file_info->east_path = ft_strdup(path);
	else if (!(ft_strcmp(first_word, "WE")) && (file_info->checksum += 8))
		file_info->west_path = ft_strdup(path);
	else
	{
		file_info->sprite_path = ft_strdup(path);
		file_info->checksum += 1;
	}
}

void	get_color(char *line, char *first_word, t_config *file_info)
{
	int		i;
	int		color_len;
	char	*colors;
	char	*number;

	i = 0;
	color_len = 0;
	colors = get_first_word(line + ft_wordlen(first_word), ' ');
	if (!(ft_strcmp(first_word, "C")))
		file_info->checksum += 2;
	else
		file_info->checksum += 4;
	while (i < 3)
	{
		number = first_number(colors + color_len + i);
		color_len += ft_strlen(number);
		if (!(ft_strcmp(first_word, "C")))
			file_info->ceiling_color[i] = ft_weak_atoi(number);
		else
			file_info->floor_color[i] = ft_weak_atoi(number);
		free(number);
		i++;
	}
}

void	get_resolution(char *line, t_config *file_info)
{
	char	*number;
	int		len_buff;

	number = ft_worddup(get_first_word(&line[1]));
	file_info->resolution[0] = ft_weak_atoi(number);
	len_buff = ft_wordlen(number);
	free(number);
	number = ft_worddup(get_first_word(get_first_word(&line[1], ' ') +
		len_buff, ' '));
	file_info->resolution[1] = ft_weak_atoi(number);
	file_info->checksum += 128;
	free(number);
}

void	get_arg(char *line, t_config *file_info)
{
	char	*first_word;

	first_word = ft_worddup(get_first_word(line, ' '));
	if (!(ft_strcmp(first_word, "NO")) || !(ft_strcmp(first_word, "SO"))
		|| !(ft_strcmp(first_word, "EA")) || !(ft_strcmp(first_word, "WE"))
		|| !(ft_strcmp(first_word, "S")))
		get_path(line, first_word, file_info);
	else if (!(ft_strcmp(first_word, "C")) || !(ft_strcmp(first_word, "F")))
		get_color(line, first_word, file_info);
	else
		get_resolution(line, file_info);
	free(first_word);
	first_word = NULL;
}
