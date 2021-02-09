#include <math.h>
#define ANGLE 85.24
#define FOV 30
#define SCR_W 600
#define PLAYER_X64 85.5
#define PLAYER_Y64 85.5

double	modulo(double x, double y)
{
    x -= y * abs(x / y);
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
	float	dist;

	alpha = (((ANGLE - FOV / 2) + 
		column * (FOV / SCR_W)) * M_PI) / 180;
	//check horizontal
	ray_x64 = PLAYER_X64;

	ray_y64 = PLAYER_Y64;
	if (alpha <= M_PI || alpha > (3 * M_PI))
		ray_y64 -= (((PLAYER_X64 / 64) * 64 + 64) - PLAYER_X64) * tan(alpha);
	else
		ray_y64 -= (PLAYER_X64 - ((PLAYER_X64 / 64) * 64)) * tan(modulo(alpha + (M_PI / 2), (M_PI * 2)) * -1);
	return (dist);
}