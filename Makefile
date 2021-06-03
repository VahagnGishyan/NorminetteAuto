NAME 						= AutoNorminette

INCLUDES 					= includes

CPP							=	g++

RM							=	rm -f

CPPFLAGS 					= -Wall -Wextra -Werror -I${INCLUDES} -std=c++0x

FILEEDITORFILES 			= ${shell find "./FileEditor" -name "*.cpp"}
FILETEXTEDITORFILES			= ${shell find "./FileTextEditor" -name "*.cpp"}
NORMINETTECORRECTORFILES	= ${shell find "./NorminetteCorrector" -name "*.cpp"}
NORMINETTEAUTOFILES 		= ${shell find "./NorminetteAuto" -name "*.cpp"}

FILES = ${FILEEDITORFILES} ${FILETEXTEDITORFILES} ${NORMINETTECORRECTORFILES} ${NORMINETTEAUTOFILES}


OBJS = ${FILES:.cpp=.o}

all: ${NAME}

%.o: %.cpp
	${CPP} $(CPPFLAGS) -I${INCLUDES} -c $< -o $@

${NAME}: ${OBJS}
	${CPP} $(CPPFLAGS) -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
