/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:39:09 by jchene            #+#    #+#             */
/*   Updated: 2020/01/29 15:05:26 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10
# include <unistd.h>
# include <stdlib.h>
# include "../../headers/lib.h"

int		get_next_line(int fd, char **line);
void	ft_strcpyn(char *dst, char *src);
void	ft_strcatn(char *dst, char *src);
void	*ft_memset(void *s, int c, int n);
void	*ft_calloc(int count, int size);
#endif
