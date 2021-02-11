/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:35:05 by jchene            #+#    #+#             */
/*   Updated: 2021/02/11 16:22:45 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	map_file->map[map_file->map_hei - 1][map_file->map_len - 1] = '1';
	display_map(map_file);
	if (check_horizontal(map_file->map) == -1)
		return (-1);
	if (check_vertical(map_file) == -1)
		return (-1);
	return (0);
}

int		init_game_var(t_mlx *mlx_ptrs)
{
	char player;

	if (!(GAME = (t_game_var*)malloc(sizeof(t_game_var))))
		return (-1);
	GAME->block_size = 64;
	GAME->fov = 60;
	GAME->move_speed = 10;
	GAME->angle_speed = 5;
	GAME->player_x64 = (MAP->player_x * 64 + 32);
	GAME->player_y64 = (MAP->player_y * 64 + 32);
	player = MAP->map[MAP->player_y][MAP->player_y];
	if (player == 'N')
		GAME->angle = 90.0;
	else if (player == 'S')
		GAME->angle = 270.0;
	else if (player == 'E')
		GAME->angle = 180.0;
	else
		GAME->angle = 0;
	return (0);
}

/*int		handle_direction(int key, t_mlx *mlx_ptrs)
{

}*/

int		handle_keys(int key, t_mlx *mlx_ptrs)
{
	if (key == 53)
	{
		mlx_destroy_image(mlx_ptrs->mlx, mlx_ptrs->img);
		mlx_destroy_window(mlx_ptrs->mlx, mlx_ptrs->win);
		exit(0);
	}
	else if (key == 1)
		GAME->player_y64 += GAME->move_speed;
	else if (key == 13)
		GAME->player_y64 -= GAME->move_speed;
	else if (key == 2)
		GAME->player_x64 -= GAME->move_speed;
	else if (key == 0)
		GAME->player_x64 += GAME->move_speed;
	else if (key == 124)
		GAME->angle = fmod((GAME->angle +
			GAME->angle_speed), 360.0);
	else if (key == 123)
	{
		GAME->angle = fmod((GAME->angle -
			GAME->angle_speed), 360.0);
		if (GAME->angle < 0)
			GAME->angle += 360;
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
	int		heigth;
	int		line_count;
	//int		length;

	//length = CONFIG->resolution[0];
	heigth = CONFIG->resolution[1];
	/*printf("length: %d - heigth: %d - start: %p\n", length, heigth,
		img_data->start);
	printf("ceiling color: %d - %d - %d\n", CONFIG->ceiling_color[0],
		CONFIG->ceiling_color[1], CONFIG->ceiling_color[2]);*/
	line_count = 0;
	while (line_count < heigth)
	{
		if (line_count < ((heigth / 2) - (CALC->perc_hei / 2)))
		{
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 0] = CONFIG->ceiling_color[2];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 1] = CONFIG->ceiling_color[1];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 2] = CONFIG->ceiling_color[0];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 3] = 0;
		}
		else if (line_count > ((heigth / 2) + (CALC->perc_hei / 2)))
		{
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 0] = CONFIG->floor_color[2];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 1] = CONFIG->floor_color[1];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 2] = CONFIG->floor_color[0];
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 3] = 0;
		}
		else
		{
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 0] = 125;
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 1] = 0;
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 2] = 123;
			img_data->start[((column * 4) + (line_count * *(img_data->ln_size)))
				+ 3] = 0;
		}
		line_count+= 1;
	}
	return (0);
}

void	check_limits(float *ray_x64, float *ray_y64, t_mlx *mlx_ptrs)
{
	if (*ray_x64 / 64 > MAP->map_len - 1 )
		*ray_x64 = (MAP->map_len - 1) * 64 - 1;
	if (*ray_y64 / 64 > MAP->map_hei - 1)
		*ray_y64 = (MAP->map_hei - 1) * 64 - 1;
	if (*ray_x64 < 0)
		*ray_x64 = 1;
	if (*ray_y64 < 0)
		*ray_y64 = 1;
}

float	raycast(t_mlx *mlx_ptrs, int column)
{
	float	ray_x64;
	float	ray_y64;
	float	alpha;
	float	h_dist;
	float	v_dist;

	alpha = (((GAME->angle + GAME->fov / 2) - 
		column * (GAME->fov / CONFIG->resolution[0])) * M_PI) / 180;

	ray_x64 = ((int)GAME->player_x64 / 64) * 64 + ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI)) ? 64 : -1);
	ray_y64 = GAME->player_y64 - (fabs(GAME->player_x64 - ray_x64) * tan(alpha) * ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI)) ? 1 : -1));
	check_limits(&ray_x64, &ray_x64, mlx_ptrs);
	while (MAP->map[(int)(ray_y64 / 64)][(int)(ray_x64 / 64)] != '1')
	{
		ray_x64 += ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI)) ? 64 : -64);
		ray_y64 += 64 * tan(alpha) * ((alpha <= (M_PI / 2) || alpha > (1.5 * M_PI) ? 1 : -1));
		check_limits(&ray_x64, &ray_x64, mlx_ptrs);
	}
	v_dist = sqrt(pow(fabs(ray_x64 - GAME->player_x64), 2) + pow(fabs(ray_y64 - GAME->player_y64), 2));
	
	ray_y64 = ((int)GAME->player_y64 / 64) * 64 + ((alpha >= M_PI) ? 64 : -1);
	ray_x64 = GAME->player_x64 - (fabs(GAME->player_y64 - ray_y64) / tan(alpha) * ((alpha >= M_PI) ? 1 : -1));
	check_limits(&ray_x64, &ray_x64, mlx_ptrs);
	while (MAP->map[(int)(ray_y64 / 64)][(int)(ray_x64 / 64)] != '1')
	{
		ray_y64 += ((alpha >= M_PI) ? 64 : -64);
		ray_x64 += 64 / tan(alpha) * ((alpha >= M_PI) ? 1 : -1);
		check_limits(&ray_x64, &ray_x64, mlx_ptrs);
	}
	h_dist = sqrt(pow(fabs(ray_x64 - GAME->player_x64), 2) + pow(fabs(ray_y64 - GAME->player_y64), 2));
	return ((h_dist < v_dist ? h_dist : v_dist));
}

/*float	raycast(t_mlx *mlx_ptrs, int column)
{
	int		quart;
	float	local_cords[2];
	float	map_cords[2];
	float	locangle;
	float	dist;

	locangle = fmod(((GAME->angle - GAME->fov / 2) + column *
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

int		draw_img(t_img_data *img_data, t_mlx *mlx_ptrs)
{
	int		column;
	int		length;
	
	column = 0;
	length = *(img_data->ln_size) / (*(img_data->bpp) / 8);
	if (!(CALC = (t_calc_var *)malloc(sizeof(t_calc_var))))
		return (-1);
	CALC->screen_dist = ((length / 2) /
		(tan((((GAME->fov / 2) * M_PI) / 180))));
	while (column < length)
	{
		CALC->wall_dist = raycast(mlx_ptrs, column);
		CALC->perc_hei = (CALC->screen_dist *
			(GAME->block_size / CALC->wall_dist));
		/*printf("b_size: %d - angle: %f - x: %f - y: %f\n",
			GAME->block_size, GAME->angle, GAME->player_x64, GAME->player_y64);*/
		/*printf("----%d %d\n", MAP->player_x, MAP->player_y);*/
		draw_column(mlx_ptrs, img_data, column);
		//printf("column: %d - hp: %f - start: %p\n", column,
			//CALC->perc_hei, img_data->start);
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
	MAP = map_file;
	CONFIG = file_info;
	if ((start_mlx(file_info, mlx_ptrs)) == -1)
		return (free_file(file_info, map_id) + free_map(map_file));
	return (0);
}
