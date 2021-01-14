NAME		=	cub3d

SRCS		=	./srcs/*.c\
				./lib/*.c\
				./utils/get_next_line/*.c

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

SANFLAGS	=	-g -fsanitize=address

LIB			=	-lm -lX11 -lXext

MLX			=	./utils/minilibx-linux/libmlx_Linux.a

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
