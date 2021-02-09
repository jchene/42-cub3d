#include "../headers/cub3d.h"

int		ft_weak_atoi(char *argument)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (argument[i] >= '0' && argument[i] <= '9')
	{
		ret = ret * 10 + (argument[i] - '0');
		i++;
	}
	return (ret);
}

char	*first_number(char *string)
{
	char	*number;
	int		i;
	int		color_count;

	i = 0;
	color_count = 0;
	while (is_charset(string[i++], "0123456789"))
		color_count++;
	number = (char *)ft_calloc(color_count + 1, sizeof(char));
	ft_strlcpy(string, number, color_count);
	return (number);
}

double	modulo(double x, double y)
{
    x -= y * abs(x / y);
    if (x >= 0.) 
		return (x);
    else
		return (x+y);
}
