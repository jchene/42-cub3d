/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:36:55 by jchene            #+#    #+#             */
/*   Updated: 2020/03/06 19:28:53 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <mlx.h>

int		fct_exit()
{
	exit(0);
	return (0);
}

int 	main(void)
{
  void *mlx;
  void *window;
  int	test;
  int	(*pf)();
  
  pf = &fct_exi
  mlx = mlx_init();
  window = mlx_new_window(mlx, 1000, 1000, "Title");
  
  mlx_loop(mlx);
  mlx_key_hook(window, &fct_exit(), test);
  return (0);
}
