SRCS_VECTOR		=	main_vector.cpp		\

HEADER_VECTOR	=	headers/vector.hpp	\

SRCS_STACK		=	main_stack.cpp		\

HEADER_STACK	=	headers/stack.hpp	\

SRCS_MAP		=	main_map.cpp		\

HEADER_STACK	=	headers/map.hpp		\

SRCS_SET		=	main_set.cpp		\

HEADER_STACK	=	headers/set.hpp		\

SRCS_MAIN		=	main.cpp			\

HEADER_MAIN		=	headers/map.hpp		\
					headers/stack.hpp	\
					headers/vector.hpp	\

INCLUDE =	-Iinclude

OBJS_STACK	= ${SRCS_STACK:.cpp=.o}

OBJS_VECTOR	=	${SRCS_VECTOR:.cpp=.o}

OBJS_MAP	=	${SRCS_MAP:.cpp=.o}

OBJS_SET	=	${SRCS_SET:.cpp=.o}

OBJS_MAIN	=	${SRCS_MAIN:.cpp=.o}

CXXFLAGS	=	-Wall -Werror -Wextra -g3 -std=c++98 #-fsanitize=address

# FLAG_DEBUG	=	-g3

# NAME	=	ft_containers

NAME_STACK = stack
NAME_VECTOR = vector
NAME_MAP = map
NAME_SET = set
NAME_MAIN = main_42

CXX		=	c++

all:		${NAME_STACK} ${NAME_VECTOR} ${NAME_MAP} ${NAME_SET} ${NAME_MAIN}

${NAME_STACK}:	${OBJS_STACK} ${HEADER_STACK}
				${CXX} ${CXXFLAGS} ${OBJS_STACK} -o ${NAME_STACK}

${NAME_VECTOR}:	${OBJS_VECTOR} ${HEADER_VECTOR}
				${CXX} ${CXXFLAGS} ${OBJS_VECTOR} -o ${NAME_VECTOR}

${NAME_MAP}:	${OBJS_MAP} ${HEADER_MAP}
				${CXX} ${CXXFLAGS} ${OBJS_MAP} -o ${NAME_MAP}

${NAME_SET}:	${OBJS_SET} ${HEADER_SET}
				${CXX} ${CXXFLAGS} ${OBJS_SET} -o ${NAME_SET}

${NAME_MAIN}:	${OBJS_MAIN} ${HEADER_MAIN}
				${CXX} ${CXXFLAGS} ${OBJS_MAIN} -o ${NAME_MAIN}

# debug:		${OBJS} ${HEADER}
# 			${CC} ${FLAG} ${FLAG_DEBUG} ${OBJS} -o ${NAME}

vector:		${NAME_VECTOR}

stack:		${NAME_STACK}

map:		${NAME_MAP}

set:		${NAME_SET}

main_42:		${NAME_MAIN}

clean:
			@rm -f ${OBJS_STACK} ${OBJS_VECTOR} ${OBJS_MAP} ${OBJS_SET} ${OBJS_MAIN}

fclean:		clean
			@rm -f ${NAME_STACK} ${NAME_VECTOR} ${NAME_MAP} ${NAME_SET} ${NAME_MAIN}
			@echo "\033[39;33mALL CLEAN !\t\t\tYOU'RE VERY PROPER\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
