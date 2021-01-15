#include "../headers/cub3d.h"

int		check_config(int map_id, t_config *file_info)
{
	char	*line;
	int		type;

	while (get_next_line(map_id, &line) &&
		(type = line_type(line)) != 2 && type != -1)
	{
		if (ft_strlen(line) != 0)
			get_arg(line, file_info);
		free(line);
		line = NULL;
	}
	type = line_type(line);
	if (type == 2 && file_info->checksum == 255)
		file_info->first_map_line = ft_strdup(line);
	free(line);
	if (type == -1)
		return (display_error("w-arg"));
	else if (file_info->checksum != 255)
		return (missing_arg(file_info->checksum));
	else if (type == 0)
		return (display_error("no-map"));
	return (0);
}

int		check_map(int *pmap_id, t_config *file_info, t_map *map_file)
{
	map_file->player_x = -1;
	map_file->player_y = -1;
	size_map(*pmap_id, map_file, file_info->first_map_line);
	close(*pmap_id);
	if (!(*pmap_id = open(map_file->name, O_RDONLY)))
		return (-1);
	if ((copy_map(*pmap_id, map_file, file_info->first_map_line)) == -1)
		return (-1);
	fill_spaces(map_file);
	if (check_horizontal(map_file->map) == -1)
		return (-1);
	if (check_vertical(map_file) == -1)
		return (-1);
	return (0);
}

int		init_game_var(t_mlx *mlx_ptrs)
{
	char player;

	if (!(mlx_ptrs->game_var = (t_game_var*)malloc(sizeof(t_game_var))))
		return (-1);
	mlx_ptrs->game_var->block_size = 64;
	mlx_ptrs->game_var->fov = 60;
	mlx_ptrs->game_var->move_speed = 10;
	mlx_ptrs->game_var->angle_speed = 5;
	mlx_ptrs->game_var->player_cords[0] = (mlx_ptrs->map->player_x * 64 + 32);
	mlx_ptrs->game_var->player_cords[1] = (mlx_ptrs->map->player_y * 64 + 32);
	player = mlx_ptrs->map->map[mlx_ptrs->map->player_y][mlx_ptrs->map->player_y];
	if (player == 'N')
		mlx_ptrs->game_var->angle = 90.0;
	else if (player == 'S')
		mlx_ptrs->game_var->angle = 270.0;
	else if (player == 'E')
		mlx_ptrs->game_var->angle = 180.0;
	else
		mlx_ptrs->game_var->angle = 0;
	return (0);
}

int		handle_keys(int key, t_mlx *mlx_ptrs)
{
	if (key == 65307)
	{
		mlx_destroy_image(mlx_ptrs->mlx, mlx_ptrs->img);
		mlx_destroy_window(mlx_ptrs->mlx, mlx_ptrs->win);
		exit(0);
	}
	else if (key == 115)
		mlx_ptrs->game_var->player_cords[1] += mlx_ptrs->game_var->move_speed;
	else if (key == 122)
		mlx_ptrs->game_var->player_cords[1] -= mlx_ptrs->game_var->move_speed;
	else if (key == 113)
		mlx_ptrs->game_var->player_cords[0] -= mlx_ptrs->game_var->move_speed;
	else if (key == 100)
		mlx_ptrs->game_var->player_cords[0] += mlx_ptrs->game_var->move_speed;
	else if (key == 65363)
		mlx_ptrs->game_var->angle = fmod((mlx_ptrs->game_var->angle +
			mlx_ptrs->game_var->angle_speed), 360.0);
	else if (key == 65361)
	{
		mlx_ptrs->game_var->angle = fmod((mlx_ptrs->game_var->angle -
			mlx_ptrs->game_var->angle_speed), 360.0);
		if (mlx_ptrs->game_var->angle < 0)
			mlx_ptrs->game_var->angle += 360;
	}
	return (0);
}

int		init_img_data(t_img_data *img_data, t_mlx *mlx_ptrs)
{
	if (!(img_data->bpp = (int *)malloc(sizeof(int))))
		return (-1);
	if (!(img_data->ln_size = (int *)malloc(sizeof(int))))
		return (-1);
	if (!(img_data->endian = (int *)malloc(sizeof(int))))
		return (-1);
	img_data->start = mlx_get_data_addr(mlx_ptrs->img, img_data->bpp,
		img_data->ln_size, img_data->endian);
	return (0);
}

int		draw_column(t_mlx *mlx_ptrs, t_img_data *img_data, int column)
{
	//int		length;
	int		heigth;
	int		line_count;

	//length = mlx_ptrs->config->resolution[0];
	heigth = mlx_ptrs->config->resolution[1];
	/*printf("length: %d - heigth: %d - start: %p\n", length, heigth,
		img_data->start);
	printf("ceiling color: %d - %d - %d\n", mlx_ptrs->config->ceiling_color[0],
		mlx_ptrs->config->ceiling_color[1], mlx_ptrs->config->ceiling_color[2]);*/
	line_count = 0;
	while (line_count < heigth)
	{
		if (line_count < ((heigth / 2) - (mlx_ptrs->calc_var->perc_hei / 2)))
		{
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 0] = mlx_ptrs->config->ceiling_color[2];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 1] = mlx_ptrs->config->ceiling_color[1];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 2] = mlx_ptrs->config->ceiling_color[0];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 3] = (int)0;
		}
		else if (line_count > ((heigth / 2) + (mlx_ptrs->calc_var->perc_hei / 2)))
		{
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 0] = mlx_ptrs->config->floor_color[2];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 1] = mlx_ptrs->config->floor_color[1];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 2] = mlx_ptrs->config->floor_color[0];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 3] = (int)0;
		}
		else
		{
			
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 0] = (int)0;
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 1] = (int)32;
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 2] = (int)170;
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 3] = (int)0;
		}
		line_count+= 1;
	}
	return (0);
}

float	raytrace(t_mlx *mlx_ptrs, int column)
{
	float	mapx;
	float	mapy;
	float	factor[2];
	float	mur[4];
	float	dist[2];
	float	locangle;
	//int		wall;

	locangle = (GAME->angle - (GAME->fov / 2)) +
		(column * (GAME->fov / CONFIG->resolution[0]));
	printf("tracing from %f %f column: %d at angle: %f\n", GAME->player_cords[0],
		GAME->player_cords[1], column, locangle);
	//wall = 0;
	if (locangle < 180)
    	mapy = (int)(GAME->player_cords[1] / 64) * 64 - 1;
	else
		mapy = (int)(GAME->player_cords[1] / 64) * 64 + 64;
	if (locangle > 270 || locangle < 90)
		mapx = GAME->player_cords[0] + abs(GAME->player_cords[1] - mapy) /
			tan((locangle * M_PI) / 180);
	else
		mapx = GAME->player_cords[0] - abs(GAME->player_cords[1] - mapy) /
			tan((locangle * M_PI) / 180);
	factor[0] = (64 / tan((locangle * M_PI) / 180));
	factor[0] = ((locangle < 90 || locangle > 270) ? (factor[0] * -1) : factor[0]);
	factor[1] = (locangle < 180 ? 64 : -64);
	printf("loop with mapx: %f mapy: %f factor: %f %f\n", mapx, mapy, factor[0], factor[1]);
	printf("checking horizontally map[%d][%d]\n", (int)(mapy/64), (int)(mapx/64));
    while (mapx > 0 && mapx < ((MAP->map_len - 1) * 64 - 1) &&
		mapy > 0 && mapy < ((MAP->map_hei - 1) * 64 - 1) &&
		MAP->map[(int)(mapy/64)][(int)(mapx/64)] != '1')
    {
		printf("map: %d %d\nstart: %f %f %d %d\n", (MAP->map_hei - 1) * 64,
			(MAP->map_len - 1) * 64, mapx, mapy, (int)(mapx/64), (int)(mapy/64));
		mapx += factor[0];
		mapy += factor[1];
		//wall = 1;
		printf("end: %f %f %d %d\n", mapx, mapy, (int)(mapx/64), (int)(mapy/64));
    }
	/*if (wall == 1)
	{
		mur[0] = mapx;
		mur[1] = mapy;
		dist[0] = sqrt(pow((GAME->player_cords[0] - mur[0]), 2) +
			pow((GAME->player_cords[1] - mur[1]), 2));
	}*/
	if (mapx < 0 || mapy < 0)
	{
		if (mapx < 0)
			mapx = 0;
		if (mapy < 0)
			mapy = 0;
	}
	if (mapx < ((MAP->map_len - 1) * 64 - 1) &&
		mapy < ((MAP->map_hei - 1) * 64 - 1) &&
		MAP->map[(int)(mapy/64)][(int)(mapx/64)] == '1')
	{
		mur[0] = mapx;
		mur[1] = mapy;
		dist[0] = sqrt(pow((GAME->player_cords[0] - mur[0]), 2) +
			pow((GAME->player_cords[1] - mur[1]), 2));
	}
	else
		dist[0] = MAP->map_len * 64;
	printf("dist[0]: %f\n", dist[0]);
	//wall = 0;
	if (locangle > 270 || locangle < 90)
		mapx = (int)(GAME->player_cords[0] / 64) * 64 + 64;
	else
		mapx = (int)(GAME->player_cords[0] / 64) * 64 - 1;
	if (locangle < 180)
		mapy = GAME->player_cords[1] + abs(GAME->player_cords[0] - mapx) *
			tan((locangle * M_PI) / 180);
	else
		mapy = GAME->player_cords[1] - abs(GAME->player_cords[0] - mapx) *
			tan((locangle * M_PI) / 180);
    factor[0] = ((locangle < 90 || locangle > 270) ? 64 : -64);
	factor[1] = 64 * tan((locangle * M_PI) / 180);
	factor[1] = (locangle > 180 ? factor[1] : (-1 * factor[1]));
	printf("loop with mapx: %f mapy: %f factor: %f %f\n", mapx, mapy, factor[0], factor[1]);
	printf("checking vertically map[%d][%d]\n", (int)(mapy/64), (int)(mapx/64));
	while (mapx > 0 && mapx < ((MAP->map_len - 1) * 64 - 1) &&
		mapy > 0 && mapy < ((MAP->map_hei - 1) * 64 - 1) &&
		MAP->map[(int)(mapy/64)][(int)(mapx/64)] != '1') 
	{
		printf("map: %d %d\nstart: %f %f %d %d\n", (MAP->map_hei - 1) * 64,
			(MAP->map_len - 1) * 64, mapx, mapy, (int)(mapx/64), (int)(mapy/64));
		mapx += factor[0];
		mapy += factor[1];
		//wall = 1;
		printf("end: %f %f %d %d\n", mapx, mapy, (int)(mapx/64), (int)(mapy/64));
	}
	/*if (wall == 1)
	{
		mur[2] = mapx;
		mur[3] = mapy;
		dist[1] = sqrt(pow((GAME->player_cords[0] - mur[2]), 2) +
			pow((GAME->player_cords[1] - mur[3]), 2));
	}*/
	if (mapx < 0 || mapy < 0)
	{
		if (mapx < 0)
			mapx = 0;
		if (mapy < 0)
			mapy = 0;
	}
	if (mapx < ((MAP->map_len - 1) * 64 - 1) &&
		mapy < ((MAP->map_hei - 1) * 64 - 1) &&
		MAP->map[(int)(mapy/64)][(int)(mapx/64)] == '1')
	{
		mur[2] = mapx;
		mur[3] = mapy;
		dist[1] = sqrt(pow((GAME->player_cords[0] - mur[2]), 2) +
			pow((GAME->player_cords[1] - mur[3]), 2));
	}
	else
		dist[1] = MAP->map_hei * 64;
	printf("dist[1]: %f\n", dist[1]);
	printf("short: dist[%d]\n", (dist[0] < dist[1]) ? 0 : 1);
	printf("dist: %f\n\n", (dist[0] < dist[1]) ? dist[0] : dist[1]);
	/*if (dist[1] == sqrt(pow((GAME->player_cords[0] - mur[2]), 2)
		+ pow((GAME->player_cords[1] - mur[3]), 2)))
		dist[1] = MAP->map_len * 64;
	if (dist[0] == sqrt(pow((GAME->player_cords[0] - mur[0]), 2)
		+ pow((GAME->player_cords[1] - mur[1]), 2)))
		dist[0] = MAP->map_len * 64;*/
	return ((dist[0] < dist[1]) ? dist[0] : dist[1]);
}

/*float	raytrace(t_mlx *mlx_ptrs, int column)
{
	int		quart;
	float	local_cords[2];
	float	map_cords[2];
	float	locangle;
	float	dist;

	locangle = fmod(((GAME->angle - GAME->fov / 2) + column *
		(GAME->fov / CONFIG->resolution[0])), 90.0);
	quart = GAME->angle / 90.0;
	map_cords[0] = GAME->player_cords[0];
	map_cords[1] = GAME->player_cords[1];
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
            map_cords[0] = GAME->player_cords[0] + (quart == 0 ?
				local_cords[0] : (local_cords[0] * -1));
            map_cords[1] = GAME->player_cords[1] - (quart == 0 ?
				local_cords[1] : (local_cords[1] * -1));
        }
        else if (quart == 1 || quart == 3)
        {
            map_cords[0] = GAME->player_cords[0] + (quart == 1 ?
				(local_cords[1] * -1) : local_cords[1]);
            map_cords[1] = GAME->player_cords[1] - (quart == 1 ?
				local_cords[0] : (local_cords[0] * -1));
        }	
	}
	printf("hit wall from %f %f to %f %f map: %c column: %d\n",
		GAME->player_cords[0], GAME->player_cords[1], map_cords[0], map_cords[1],
		MAP->map[(int)(map_cords[1] / 64)][(int)(map_cords[0] / 64)], column);
	dist = sqrt(((map_cords[0] - GAME->player_cords[0]) * 
		(map_cords[0] - GAME->player_cords[0]) +
		((map_cords[1] - GAME->player_cords[1])) *
		(map_cords[1] - GAME->player_cords[1])));
	return (dist);
}*/

int		draw_img(t_img_data *img_data, t_mlx *mlx_ptrs)
{
	int		column;
	int		length;
	
	column = 0;
	length = *(img_data->ln_size) / (*(img_data->bpp) / 8);
	if (!(mlx_ptrs->calc_var = (t_calc_var *)malloc(sizeof(t_calc_var))))
		return (-1);
	mlx_ptrs->calc_var->screen_dist = ((length / 2) /
		(tan((((mlx_ptrs->game_var->fov / 2) * M_PI) / 180))));
	while (column < length)
	{
		mlx_ptrs->calc_var->wall_dist = raytrace(mlx_ptrs, column);
		mlx_ptrs->calc_var->perc_hei = (mlx_ptrs->calc_var->screen_dist *
			(mlx_ptrs->game_var->block_size / mlx_ptrs->calc_var->wall_dist));
		printf("b_size: %d - angle: %f - x: %f - y: %f\n",
			mlx_ptrs->game_var->block_size, mlx_ptrs->game_var->angle, mlx_ptrs->game_var->player_cords[0], mlx_ptrs->game_var->player_cords[1]);
		/*printf("----%d %d\n", mlx_ptrs->map->player_x, mlx_ptrs->map->player_y);*/
		draw_column(mlx_ptrs, img_data, column);
		//printf("column: %d - hp: %f - start: %p\n", column,
			//mlx_ptrs->calc_var->perc_hei, img_data->start);
		column++;
	}
	return (0);
}

int		update_img(t_mlx *mlx_ptrs)
{
	t_img_data	*img_data;

	if (!(img_data = (t_img_data *)malloc(sizeof(t_img_data))))
		return (-1);
	init_img_data(img_data, mlx_ptrs);
		//printf("bpp: %d - line size: %d - endian: %d - start: %p\n",
		//*(img_data->bpp), *(img_data->ln_size), *(img_data->endian),
			//img_data->start);
	draw_img(img_data, mlx_ptrs);
	mlx_put_image_to_window(mlx_ptrs->mlx, mlx_ptrs->win, mlx_ptrs->img, 0, 0);
	free(img_data->bpp);
	free(img_data->ln_size);
	free(img_data->endian);
	free(img_data);
	return (0);
}

int		start_mlx(t_config *file_info, t_mlx *mlx_ptrs)
{
	int			res_x;
	int			res_y;
	
	init_game_var(mlx_ptrs);
	if ((mlx_ptrs->mlx = mlx_init()) == NULL)
		return (-1);
	mlx_ptrs->test = 500;
	res_x = (file_info->resolution[0] > 1920 ? 1920 : file_info->resolution[0]);
	res_y = (file_info->resolution[1] > 1080 ? 1080 : file_info->resolution[1]);
	mlx_ptrs->win = mlx_new_window(mlx_ptrs->mlx, res_x, res_y, "test");
	mlx_ptrs->img = mlx_new_image(mlx_ptrs->mlx, res_x, res_y);
	mlx_key_hook(mlx_ptrs->win, handle_keys, mlx_ptrs);
	mlx_loop_hook(mlx_ptrs->mlx, update_img, mlx_ptrs);
	mlx_loop(mlx_ptrs->mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	int			map_id;
	t_config	*file_info;
	t_map		*map_file;
	t_mlx		*mlx_ptrs;

	if (argc != 2)
		return (display_error("nb-arg"));
	if ((map_id = open(argv[1], O_RDONLY)) == -1)
		return (display_error("file-nf"));
	if (!(file_info = (t_config *)ft_calloc(1, sizeof(t_config))))
		return (-1);
	init_file(file_info);
	if ((check_config(map_id, file_info)) == -1)
		return (free_file(file_info, map_id));
	if (!(map_file = (t_map *)ft_calloc(1, sizeof(t_map))))
		return (free_file(file_info, map_id));
	init_map(map_file, argv[1]);
	if ((check_map(&map_id, file_info, map_file)) == -1)
		return (free_file(file_info, map_id) + free_map(map_file));
	if (!(mlx_ptrs = (t_mlx *)ft_calloc(1, sizeof(t_mlx))))
		return (free_file(file_info, map_id) + free_map(map_file));
	mlx_ptrs->map = map_file;
	mlx_ptrs->config = file_info;
	if ((start_mlx(file_info, mlx_ptrs)) == -1)
		return (free_file(file_info, map_id) + free_map(map_file));
	return (0);
}
