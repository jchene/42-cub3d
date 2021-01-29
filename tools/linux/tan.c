#include <math.h>
#include <stdio.h>

int		main(void)
{
	double	degree;
	double	rad;
	double	tang;

	degree = 60.0;
	rad = ((degree * M_PI) / 180);
	printf("rad: %f\n", rad);
	tang = tan(rad);
	printf("tan: %f\n", tang);
	return (0);
}
