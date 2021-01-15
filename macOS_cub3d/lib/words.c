#include "../headers/cub3d.h"

char	*get_first_word(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (&line[i]);
}

int		ft_wordlen(char *word)
{
	int		i;

	i = 0;
	while (word[i] != '\0' && word[i] != ' ')
		i++;
	return (i);
}

char	*ft_worddup(char *word)
{
	char	*ret_word;

	while (*word == ' ')
		word++;
	ret_word = (char *)malloc(sizeof(char) * (ft_wordlen(word) + 1));
	ft_strlcpy(word, ret_word, ft_wordlen(word));
	return (ret_word);
}
