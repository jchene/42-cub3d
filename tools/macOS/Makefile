NAME	= tools
CC		= gcc
LIB		= -lm -lmlx -framework OpenGL -framework AppKit
MLX		= ../../macOS_cub3d/utils/minilibx_opengl_20191021/libmlx.a
DEL		= rm -f
$(NAME):
		echo "Choisissez un tool. (make [tool_name])"
get_keys:
		${CC} -o get_keys ./get_keys.c ${MLX} ${LIB}
move_pixel:
		${CC} -o move_pixel ./move_pixel.c ${MLX} ${LIB}
image:
		${CC} -o image ./image.c ${MLX} ${LIB}
sanimage:
		${CC} -o image ./image.c ${MLX} ${LIB} -g -fsanitize=address
math:
		${CC} -o math ./tan.c ${LIB}
clean:
		${DEL} get_keys move_pixel image math
.PHONY:	get_keys move_pixel image sanimage math clean
