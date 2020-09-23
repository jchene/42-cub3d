#include "../headers/cub3d.h"

int		check_path(void)
{
	return (0);
}

int		check_color(char *next_word)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (ft_weak_atoi(&next_word[i]) > 255)
			return (display_wrong_arg("color-range"));
		while (is_charset(next_word[i], "0123456789"))
			i++;
		if ((j == 0 || j == 1) && next_word[i] != ',')
			return (display_wrong_arg("color-comma"));
		i++;
		j++;
	}
	return (0);
}

int		check_resolution(char *line)
{
	char	*length;
	char	*heigth;

	length = get_first_word(line + ft_wordlen(line));
	heigth = get_first_word(length + ft_wordlen(length));
	while (*length != ' ')
	{
		if (*length < '0' || *length++ > '9')
			return (display_wrong_arg("resolution"));
	}
	while (*heigth)
		if (*heigth < '0' || *heigth++ > '9')
			return (display_wrong_arg("resolution"));
	return (0);
}

int		check_arg(char *line)
{
	char	*first_word;
	char	*next_word;
	int		ret;

	first_word = ft_worddup(line);
	if (ft_strcmp(first_word, "NO") && ft_strcmp(first_word, "SO") &&
			ft_strcmp(first_word, "EA") && ft_strcmp(first_word, "WE") &&
			ft_strcmp(first_word, "R") && ft_strcmp(first_word, "S") &&
			ft_strcmp(first_word, "F") && ft_strcmp(first_word, "C"))
	{
		free(first_word);
		return (-1);
	}
	next_word = ft_worddup(get_first_word(line) + ft_wordlen(line));
	if (ft_strlen(first_word) == 2 || !(ft_strcmp(first_word, "S")))
		ret = check_path();
	else if (!(ft_strcmp(first_word, "F")) || !(ft_strcmp(first_word, "C")))
		ret = check_color(next_word);
	else
		ret = check_resolution(line);
	free(first_word);
	free(next_word);
	return (ret);
}

int		line_type(char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (0);
	if (check_arg(line) != -1)
		return (1);
	else
	{
		while (line[i])
			if (!(is_charset(line[i++], " 012NSEW")))
				return (-1);
		return (2);
	}
}
