#include <stdio.h>
#include <stdlib.h>
#include "../../files/utils/minilibx_opengl_20191021/mlx.h"

int	print_key(int key, int *test)
{
	printf("%d\n", key);
	*test = 1;
	return (0);
}

int	main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	int  test;

	test = 0;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1, 1, "key hook");
	mlx_key_hook(win_ptr, print_key, &test);
	mlx_loop(mlx_ptr);
	return (0);	
}
