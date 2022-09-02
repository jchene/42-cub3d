/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:48:08 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/30 02:27:33 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	free_parsing_struct(t_parsing *start, int ret, int fd)
{
	t_parsing	*old;

	if (fd)
		close(fd);
	while (start)
	{
		old = start;
		start = start->next;
		free(old);
	}
	return (ret);
}

int	join_letters(t_parsing *start, int i)
{
	char		*str;
	t_parsing	*index;

	if (!start->c)
	{
		ft_putstr_fd("Error\nEmpty map file\n", 1);
		return (-1);
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (free_parsing_struct(start->next, 0, 0));
	i = -1;
	index = start;
	while (index)
	{
		str[++i] = index->c;
		index = index->next;
	}
	free_parsing_struct(start->next, 1, 0);
	(data())->ret = fill_map_struct(str, -1, 0);
	free(str);
	return ((data())->ret);
}

int	parse_file(char *path, int i, int fd, t_parsing *index)
{
	t_parsing	start;
	char		buffer[1];

	index = &start;
	start.c = '\0';
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (read(fd, &buffer, 1))
	{
		i++;
		index->c = buffer[0];
		index->next = malloc(sizeof(t_parsing));
		if (!index->next)
			return (free_parsing_struct(start.next, 0, fd));
		index = index->next;
	}
	close(fd);
	index->c = '\0';
	index->next = NULL;
	return (join_letters(&start, i));
}
