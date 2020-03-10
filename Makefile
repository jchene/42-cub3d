NAME		=	cub3d.a

HEADER		=	headers/

SRCS		=	main.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

DEL			=	rm -f

OBJS		=	${SRCS:.c=.o}

$(NAME):		${OBJS}
				${CC} ${CFLAGS} -c -I ${HEADER} ${SRCS}
				ar rc ${NAME} ${OBJS}

all:			${NAME}

clean:
				${DEL} ${OBJS} *.o

fclean:			clean
				${DEL} ${NAME}

re:				fclean all

.PHONY: 		all clean fclean re
