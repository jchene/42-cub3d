#include "../headers/cub3d.h"

void	ft_putstr(char *string)
{
	int		i;

	i = 0;
	while (string[i])
		write(1, &string[i++], 1);
}

int		ft_strlen(char *string)
{
	int		i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_strlcpy(char *src, char *dst, int n)
{
	int		i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	ft_strcpy(char *src, char *dst)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
