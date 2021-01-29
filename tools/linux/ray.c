#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct   s_player
{
    float posx;
    float posy;
    float dir;
}                player;

int main()
{
    int		quart;
    int		mapx1;
    int		mapy1;
    float	mapx2;
    float	mapy2;
    float	localdir;
    float	dist[2];
	float	factor[2];
	float	mur[4];
    player *p;

	char map[6][6] = {
	{'1','1','1','1','1','\0'},
	{'1','0','0','0','1','\0'},
	{'1','0','0','0','1','\0'},
	{'1','0','0','0','1','\0'},
	{'1','1','1','1','1','\0'},
	{'\0','\0','\0','\0','\0','\0'}};
    
    if (!(p=(player*)malloc(sizeof(player))))
        return (-1);

    p->dir = -45.0;
    p->posx = 127.0;
    p->posy = 127.0;
	if (p->dir >= 360)
		p->dir = fmod(p->dir, 360);
	if (p->dir < 0)
		p->dir += 360;
	printf("dir: %f posx: %f posy: %f\n", p->dir, p->posx, p->posy);
	if (p->dir < 180)
    	mapy1 = (int)(p->posy/64) * 64 - 1;
	else
		mapy1 = (int)(p->posy/64) * 64 + 64;
	mapx1 = p->posx + ((p->posy - mapy1) / tan((p->dir * M_PI) / 180));
	factor[0] = 64 / tan((p->dir * M_PI) / 180);
	factor[1] = (p->dir < 180 ? 64 : -64);
    while (map[(int)(mapy2/64)][(int)(mapx2/64)] != '1')
    {
    	mapx2 = mapx1 + factor[0];
		mapy2 = mapy1 + factor[1];  
    }
	mur[0] = mapx2;
	mur[1] = mapy2;
	if (p->dir > 270 || p->dir < 90)
		mapx1 = (int)(p->posx / 64) * 64 + 64;
	else
		mapx1 = (int)(p->posx / 64) * 64 - 1;
	mapy1 = p->posy + ((p->posx - mapx1) * tan((p->dir * M_PI) / 180)); 
    factor[0] = ((p->dir < 90 || p->dir > 270) ? 64 : -64);
	factor[1] = 64 * tan((p->dir * M_PI) / 180);
	while (map[(int)(mapy2/64)][(int)(mapx2/64)] != '1')
	{
		mapx2 = mapx1 + factor[0];
		mapy2 = mapy1 + factor[1];
	}
	mur[2] = mapx2;
	mur[3] = mapy2;
    dist[0] = (sqrt(pow((p->posx - mur[0]),2)) / cos((p->dir * M_PI) / 180));
    dist[1] = (sqrt(pow((p->posx - mur[2]),2)) / cos((p->dir * M_PI) / 180));
	printf("dist1: %f - dist2: %f\n", dist[0], dist[1]);
	int i = 0;
    int j = 0;
    while (i < 5)
    {
        j = 0;
        while (j < 5)
        {
            if (j == (int)p->posx/64 && i == (int)p->posy/64)
                printf("P");
            else if (j == mapx2/64 && i == mapy2/64)
                printf("W");
            else
                printf("%c",map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
	return (0);

    free(p);
    return (0);
}





