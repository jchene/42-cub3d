#include "../headers/cub3d.h"

char	*ft_strdup(char *string)
{
	char	*ret_str;

	ret_str = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	ft_strlcpy(string, ret_str, ft_strlen(string));
	return (ret_str);
}
