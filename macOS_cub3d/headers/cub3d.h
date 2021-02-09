/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchene <jchene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:35:12 by jchene            #+#    #+#             */
/*   Updated: 2021/02/09 16:11:05 by jchene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define CONFIG mlx_ptrs->config
# define MAP mlx_ptrs->map
# define GAME mlx_ptrs->game_var
# define CALC mlx_ptrs->calc_var
# include "../utils/minilibx_opengl_20191021/mlx.h"
# include "../utils/get_next_line/get_next_line.h"
# include "./lib.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_config
{
	int			resolution[2];
	int			floor_color[3];
	int			ceiling_color[3];
	int			checksum;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	char		*sprite_path;
	char		*first_map_line;
}				t_config;

typedef struct	s_map
{
	char		**map;
	char		*name;
	int			map_len;
	int			map_hei;
	int			player_x;
	int			player_y;
	int			written_lines;
}				t_map;

typedef struct		s_game_var
{
	unsigned int	block_size;
	double			angle;
	double			fov;
	double			move_speed;
	double			angle_speed;
	float			player_x64;
	float			player_y64;
}					t_game_var;

typedef struct	s_calc_var
{
	double		wall_dist;
	double		perc_hei;
	double		screen_dist;
}				t_calc_var;

typedef struct	s_img_data
{
	int		*bpp;
	int		*ln_size;
	int		*endian;
	char	*start;
}				t_img_data;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	t_map		*map;
	t_config	*config;
	t_game_var	*game_var;
	t_calc_var	*calc_var;
	int			test;
}				t_mlx;

int				check_path();
int				check_color(char *next_word);
int				check_resolution(char *line);
int				check_arg(char *line);
int				line_type(char *line);

void			get_path(char *line, char *first_word, t_config *file_info);
void			get_color(char *line, char *first_word, t_config *file_info);
void			get_resolution(char *line, t_config *file_info);
void			get_arg(char *line, t_config *file_info);

int				display_error(char *error);
void			display_missing(int argument);
int				display_wrong_arg(char *error);
int				missing_arg(int checksum);
void			display_info(t_config *file_info);

void			free_arg(int argument, t_config *file_info);
int				free_file(t_config *file_info, int map_id);
int				free_all(t_config *file_info, t_map *map_file, t_mlx *mlx_ptrs);
int				free_map(t_map *map);

void			init_file(t_config *file_info);
void			init_map(t_map *map_file, char *name);

void			size_map(int map_id, t_map *map_file, char *first_line);
int				copy_map(int map_id, t_map *map_file, char *first_line);
void			fill_spaces(t_map *map_file);
void			display_map(t_map *map_file);
int				map_errors(char *error);

int				check_horizontal(char **map);
int				init_buffer(t_map *map_file, t_map *new_file);
int				check_vertical(t_map *map_file);
#endif
