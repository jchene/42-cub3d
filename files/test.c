#include <math.h>
#include <stdio.h>
#define ANGLE 180
#define FOV 60
#define SCR_W 600
#define PLAYER_X64 160.0
#define PLAYER_Y64 160.0

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
	//float	beta;
	float	h_dist;
	float	v_dist;
	int		i;

	//alpha = ((ANGLE + FOV / 2) - column * (FOV / SCR_W)) * M_PI / 180;
	alpha = (255.000004 * M_PI / 180);
	//beta = fabs((ANGLE * M_PI / 180) - alpha);

	//check vertical
	ray_x64 = ((int)PLAYER_X64 / 64) * 64 + ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI)) ? 64 : -1);
	ray_y64 = PLAYER_Y64 - (fabs(PLAYER_X64 - ray_x64) * tan(alpha) * ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI)) ? 1 : -1));
	//check horizontal
	//ray_y64 = ((int)PLAYER_Y64 / 64) * 64 + ((alpha >= M_PI) ? 64 : -1);
	//ray_x64 = PLAYER_X64 - (fabs(PLAYER_Y64 - ray_y64) / tan(alpha) * ((alpha >= M_PI) ? 1 : -1));
	for (i = 0 ; i < 2 ; i++)
	{
		//check vertical
		printf("%d\n", i);
		ray_x64 += ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI)) ? 64 : -64);
		ray_y64 += 64 * tan(alpha) * ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI) ? 1 : -1));
		//check horizontal
		//ray_y64 += ((alpha >= M_PI) ? 64 : -64);
		//ray_x64 += 64 / tan(alpha) * ((alpha >= M_PI) ? -1 : 1);
	}
	printf("p_x: %f\np_y: %f\nx: %f\ny: %f\nangle: %f - %f\n", PLAYER_X64, PLAYER_Y64, ray_x64, ray_y64, alpha, alpha * 180 / M_PI);
	
	return (0.0);
}

int		main()
{
	raycast(1);
	return (0);
}
/* horizontal
1 -   0  (15.000000) ok
2 -  60  (74.999999) ok
3 -  95 (110.000001)  79.333237  82.0207
4 - 155 (169.999996) 164.181198 164.3575
5 - 190 (204.999998) 185.388153 184.9218
6 - 240 (255.000004) 293.157715 289.4256
7 - 285 (299.999996) ok
8 - 335 (350.000021) ok
*/