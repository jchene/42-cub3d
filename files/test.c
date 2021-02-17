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

/*float	raycast(t_mlx *mlx_ptrs, int column)
{
	int		quart;
	float	local_x;
	float	local_y;
	float	ray_x;
	float	ray_y;
	float	locangle;
	float	dist;

	locangle = fmod(((GAME->angle - GAME->fov / 2) - column *
		(GAME->fov / CONFIG->resolution[0])), 90.0);
	quart = GAME->angle / 90.0;
	ray_x = GAME->player_x64;
	ray_y = GAME->player_y64;
	local_x = 0;
	local_y = 0;
	while (MAP->map[((int)ray_y / 64)][((int)ray_x / 64)] != '1')
	{
		if (locangle < 45.0)
		{
			local_x++;
			local_y += (locangle == 0 ? 0 : tan((locangle*M_PI)/180));
		}
		else
		{
			local_y++;
			local_x += 1/(tan((locangle*M_PI)/180));
		}
		if (quart == 0 || quart == 2)
		{
			ray_x = GAME->player_x64 + (quart == 0 ?
				local_x : (local_x * -1));
			ray_y = GAME->player_y64 - (quart == 0 ?
				local_y : (local_y * -1));
		}
		else if (quart == 1 || quart == 3)
		{
			ray_x = GAME->player_x64 + (quart == 1 ?
				(local_y * -1) : local_y);
			ray_y = GAME->player_y64 - (quart == 1 ?
				local_x : (local_x * -1));
		}	
	}
	printf("hit wall from %f %f to %f %f map: %c column: %d\n",
		GAME->player_x64, GAME->player_y64, ray_x, ray_y,
		MAP->map[(int)(ray_y / 64)][(int)(ray_x / 64)], column);
	dist = sqrt(((ray_x - GAME->player_x64) * 
		(ray_x - GAME->player_x64) +
		((ray_y - GAME->player_y64)) *
		(ray_y - GAME->player_y64)));
	return (dist);
}*/

/*float	raycast(t_mlx *mlx_ptrs, int column)
{
	int		quart;
	float	local_cords[2];
	float	map_cords[2];
	float	locangle;
	float	dist;

	locangle = fmod(((GAME->angle - GAME->fov / 2) - column *
		(GAME->fov / CONFIG->resolution[0])), 90.0);
	quart = GAME->angle / 90.0;
	map_cords[0] = GAME->player_x64;
	map_cords[1] = GAME->player_y64;
	local_cords[0] = 0;
	local_cords[1] = 0;
	while (MAP->map[((int)map_cords[1] / 64)][((int)map_cords[0] / 64)] != '1')
	{
		if (locangle < 45.0)
		{
			local_cords[0]++;
			local_cords[1] += (locangle == 0 ? 0 : tan((locangle*M_PI)/180));
		}
		else
		{
			local_cords[1]++;
			local_cords[0] += 1/(tan((locangle*M_PI)/180));
		}
		if (quart == 0 || quart == 2)
		{
			map_cords[0] = GAME->player_x64 + (quart == 0 ?
				local_cords[0] : (local_cords[0] * -1));
			map_cords[1] = GAME->player_y64 - (quart == 0 ?
				local_cords[1] : (local_cords[1] * -1));
		}
		else if (quart == 1 || quart == 3)
		{
			map_cords[0] = GAME->player_x64 + (quart == 1 ?
				(local_cords[1] * -1) : local_cords[1]);
			map_cords[1] = GAME->player_y64 - (quart == 1 ?
				local_cords[0] : (local_cords[0] * -1));
		}	
	}
	printf("hit wall from %f %f to %f %f map: %c column: %d\n",
		GAME->player_x64, GAME->player_y64, map_cords[0], map_cords[1],
		MAP->map[(int)(map_cords[1] / 64)][(int)(map_cords[0] / 64)], column);
	dist = sqrt(((map_cords[0] - GAME->player_x64) * 
		(map_cords[0] - GAME->player_x64) +
		((map_cords[1] - GAME->player_y64)) *
		(map_cords[1] - GAME->player_y64)));
	return (dist);
}*/

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