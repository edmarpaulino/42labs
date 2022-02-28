# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edpaulin <edpaulin@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 10:35:53 by edpaulin          #+#    #+#              #
#    Updated: 2022/02/26 10:41:55 by edpaulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	:=	all

NAME			=	libmongoose.a

SRC_DIR			=	sources
SRC_FILES		=	mongoose.c

OBJ_DIR			=	objects
OBJ_FILES		=	${addprefix ${OBJ_DIR}/,${SRC_FILES:.c=.o}}

CC				=	gcc
CFLAGS			=	
INC				=	-I includes

MKD				=	mkdir -p ${@D}
AR				=	ar rcs
RM				=	rm -rf

all: ${NAME}

${NAME}: ${OBJ_FILES}
	${AR} ${NAME} ${OBJ_FILES}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	${MKD}
	${CC} ${CFLAGS} ${INC} -c $< -o $@

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re