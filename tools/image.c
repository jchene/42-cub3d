#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../linux-cub3d/utils/minilibx-linux/mlx.h"

typedef struct	s_ptrs
{
		void	*win_ptr;
		void	*mlx_ptr;
		void	*img_ptr;
}				ptrs;	

void	draw_img(char *start, int size_line)
{
	int 			i;
	int 			j;
	int 			k;
	unsigned long	time_stamp;

	j = 0;
		while (j < 500)
	{
		i = 0;
		while (i < size_line)
		{
			time_stamp = (unsigned long)time(NULL);
			start[i + 0 + (j * size_line)] = ((time_stamp % 2) == 0 ? 255 : 0);
			start[i + 1 + (j * size_line)] = ((time_stamp % 2) == 0 ? 255 : 0);
			start[i + 2 + (j * size_line)] = ((time_stamp % 2) == 0 ? 0 : 255);
			start[i + 3 + (j * size_line)] = 0;
			i += 4;
		}
		j++;
	}
	
}

int		update_img(ptrs *mlx_ptrs)
{
		int		*bpp;
		int		*size_line;
		int		*endian;
		char	*start;

		bpp = malloc(sizeof(int));
		size_line = malloc(sizeof(int));
		endian = malloc(sizeof(int));
		start = mlx_get_data_addr(mlx_ptrs->img_ptr, bpp, size_line, endian);
		//printf("bpp: %d\nsize_line: %d\nendian: %d\n", *bpp, *size_line, *endian);
		draw_img(start, *size_line);
		mlx_put_image_to_window(mlx_ptrs->mlx_ptr, mlx_ptrs->win_ptr, mlx_ptrs->img_ptr, 1, 1);
		free(bpp);
		free(size_line);
		free(endian);
		return (0);
}

int		handle_keys(int key, ptrs *mlx_ptrs)
{
	if (key == 65307)
		exit(0);
	return (0);
}

int		main(void)
{
		ptrs	*mlx_ptrs;

		mlx_ptrs = (ptrs*)malloc(sizeof(ptrs));
		mlx_ptrs->mlx_ptr = mlx_init();
		mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->mlx_ptr, 500, 500, "image");
		mlx_ptrs->img_ptr = mlx_new_image(mlx_ptrs->mlx_ptr, 500, 500);	
		mlx_key_hook(mlx_ptrs->win_ptr, handle_keys, mlx_ptrs);
		mlx_loop_hook(mlx_ptrs->mlx_ptr, update_img, mlx_ptrs);
		mlx_loop(mlx_ptrs->mlx_ptr);
		return (0);
}
