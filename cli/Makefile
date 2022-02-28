# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edpaulin <edpaulin@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 12:52:46 by edpaulin          #+#    #+#              #
#    Updated: 2022/02/27 19:51:11 by edpaulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEAFULT_GOAL	:=	all

NAME			=	cli42labs

SRC_DIR			=	sources
SRC_FILES		=	main.c

OBJ_DIR			=	objects
OBJ_FILES		=	${addprefix ${OBJ_DIR}/,${SRC_FILES:.c=.o}}

LIB_DIR			=	libft
LIB_INC			=	-I ${LIB_DIR}/inc
LIB				=	-L${LIB_DIR} -lft

CC				=	gcc
CFLAGS			=	
INC				=	-I includes ${LIB_INC}

MKD				=	mkdir -p ${@D}
RM				=	rm -rf

all: ${NAME}

${NAME}: ${OBJ_FILES}
	make all -C ${LIB_DIR} --no-print-directory
	${CC} ${CFLAGS} ${OBJ_FILES} ${INC} ${LIB} -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	${MKD}
	${CC} ${CFLAGS} ${INC} -c $< -o $@

clean:
	make clean -C ${LIB_DIR} --no-print-directory
	${RM} ${OBJ_DIR}

fclean: clean
	make fclean -C ${LIB_DIR} --no-print-directory
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re