NAME		=	cub3d

SRCS		=	./srcs/*.c\
				./lib/*.c\
				./utils/get_next_line/*.c

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

SANFLAGS	=	-g -fsanitize=address

LIB			=	-lm -Lmlx -lmlx -framework OpenGL -framework AppKit

MLX			=	./utils/minilibx_opengl_20191021/libmlx.a

DEL			=	rm -f

$(NAME):
				${CC} -o ${NAME} ${SRCS} ${MLX} ${LIB} ${CFLAGS}

all:			${NAME}

san:
				${CC} -o ${NAME} ${SRCS} ${MLX} ${LIB} ${CFLAGS} ${SANFLAGS}

clean:
				${DEL} ${NAME}

fclean:			clean

re:				fclean all

.PHONY: 		all san lean fclean re
