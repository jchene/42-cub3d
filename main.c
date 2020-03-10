/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:36:55 by jchene            #+#    #+#             */
/*   Updated: 2020/03/10 19:47:16 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

typedef struct	s_pointers
{
	void		*win_ptr;
	void		*mlx_ptr;
	int			*keylist;
	t_pixel		*pixel;
}				t_mlx_ptrs;

void	move_pixel(t_mlx_ptrs *ptrs, int key)
{
	int		old_x;
	int		old_y;

	old_x = ptrs->pixel->x;
	old_y = ptrs->pixel->y;
	if (key == 0)
		ptrs->pixel->x--;
	else if (key == 1)
		ptrs->pixel->y++;
	else if (key == 2)
		ptrs->pixel->x++;
	else if (key == 13)
		ptrs->pixel->y--;
	mlx_pixel_put(ptrs->mlx_ptr, ptrs->win_ptr, old_x, old_y, 0);
	mlx_pixel_put(ptrs->mlx_ptr, ptrs->win_ptr, ptrs->pixel->x, ptrs->pixel->y, ptrs->pixel->color);
	return ;
}

int		handle_key(int key, void *ptrs)
{
	if (key == 53)
	{
		free(ptrs);
		exit(0);
	}
	else
		move_pixel(ptrs, key);
	return (0);
}

int 	main(void)
{
	t_mlx_ptrs	*ptrs;

	if (!(ptrs = (t_mlx_ptrs*)malloc(sizeof(t_mlx_ptrs))))
		return (-1);
	if (!(ptrs->pixel = (t_pixel *)malloc(sizeof(t_pixel))))
		return (-1);
	ptrs->pixel->x = 100;
	ptrs->pixel->y = 100;
	ptrs->pixel->color = 1308404;
	ptrs->mlx_ptr = mlx_init();
	ptrs->win_ptr = mlx_new_window(ptrs->mlx_ptr, 200, 200, "test");
	mlx_pixel_put(ptrs->mlx_ptr, ptrs->win_ptr, 100, 100, 1308404);
	mlx_key_hook(ptrs->win_ptr, handle_key, ptrs);
	mlx_loop(ptrs->mlx_ptr);
	return (0);
}
