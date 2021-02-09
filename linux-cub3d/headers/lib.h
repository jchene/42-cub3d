#ifndef LIB_H
# define LIB_H

int		ft_weak_atoi(char *argument);
char	*first_number(char *string);

char	*get_first_word(char *line, char sep);
int		ft_wordlen(char *word);
char	*ft_worddup(char *word);

void	ft_putstr(char *string);
int		ft_strlen(char *string);
int		ft_strcmp(char *s1, char *s2);
void	ft_strlcpy(char *src, char *dst, int n);
void	ft_strcpy(char *src, char *dst);
char	*ft_strdup(char *string);

int		is_charset(char c, char *charset);
int		find_charset(char *buff, char *charset);
#endif
