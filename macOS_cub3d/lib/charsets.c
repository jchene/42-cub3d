#include "../headers/cub3d.h"

int		is_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
		if (charset[i++] == c)
			return (1);
	return (0);
}

int		find_charset(char *buff, char *charset)
{
	int i;
	int j;

	i = 0;
	while (buff[i])
	{
		j = 0;
		while (charset[j])
		{
			if (buff[i] == charset[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
