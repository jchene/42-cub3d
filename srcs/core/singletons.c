/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguinau <constantasg@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:31:22 by anguinau          #+#    #+#             */
/*   Updated: 2022/07/01 02:31:34 by anguinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}