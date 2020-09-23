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

int		handle_keys(int key, t_mlx *mlx_ptrs)
{
	if (key == 65307)
	{
		mlx_destroy_window(mlx_ptrs->mlx, mlx_ptrs->win);
	}
	return (0);
}

int		start_mlx(int map_id, t_config *file_info, t_map *mapf, t_mlx *mlx_ptrs)
{
	int		res_x;
	int		res_y;
	//t_root	*tofree;	

	//if (!(tofree = (t_root *)ft_calloc(1, sizeof(t_root))))
	//	return (-1);
	//i
	if ((mlx_ptrs->mlx = mlx_init()) == NULL)
		return (-1);
	res_x = (file_info->resolution[0] > 1920 ? 1920 : file_info->resolution[0]);
	res_y = (file_info->resolution[1] > 1080 ? 1080 : file_info->resolution[1]);
	mlx_ptrs->win = mlx_new_window(mlx_ptrs->mlx, res_x, res_y, "test");
	mlx_key_hook(mlx_ptrs->win, handle_keys, mlx_ptrs);
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
	if ((start_mlx(map_id, file_info, map_file, mlx_ptrs)) == -1)
		return (free_file(file_info, map_id) + free_map(map_file));
	return (0);
}
