#include <math.h>
#include <stdio.h>
#define ANGLE 285.0
#define FOV 30
#define SCR_W 600
#define PLAYER_X64 160.0
#define PLAYER_Y64 170.0

double	modulo(double x, double y)
{
    x -= y * fabs(x / y);
    if (x >= 0.) 
		return (x);
    else
		return (x+y);
}

float	raycast(int column)
{
	float	ray_x64;
	float	ray_y64;
	float	alpha;
	float	h_dist;
	float	v_dist;

	alpha = (((ANGLE + FOV / 2) - column * (FOV / SCR_W)) * M_PI) / 180;

	//check horizontal
	ray_x64 = ((int)PLAYER_X64 / 64) * 64 + ((alpha <= M_PI || alpha > (1.5 * M_PI)) ? 64 : -1);
	if (alpha <= M_PI || alpha > (3 * M_PI))
		ray_y64 = PLAYER_Y64 - ((ray_x64 - PLAYER_X64) * tan(alpha));
	else
		ray_y64 = PLAYER_Y64 - ((PLAYER_X64 - ray_x64) * tan(modulo(alpha + (M_PI / 2), (M_PI * 2)) * -1));

	printf("p_x: %f\np_y: %f\nx: %f\ny: %f\nangle: %f\n", PLAYER_X64, PLAYER_Y64, ray_x64, ray_y64, alpha);
	return (0.0);
}

int		main()
{
	raycast(1);
	return (0);
}