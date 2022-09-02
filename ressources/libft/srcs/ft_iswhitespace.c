/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 23:38:42 by anguinau          #+#    #+#             */
/*   Updated: 2022/06/29 23:42:05 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// Return 1 si C is whitespace, sinon 0
int	ft_iswhitespace(char c)
{
	if (c != ' ' && c != '\t' && c != '\n'
		&& c != '\r' && c != 'v' && c != 'f')
		return (0);
	return (1);
}
