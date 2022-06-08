CC			= clang++
CFLAGS		= -g -Wall -Wextra -Werror #-std=c++11
# VALGRIND	= valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log

NAME		= solver

SRC_DIR		= src
SRC			= $(patsubst %, $(SRC_DIR)/%, main.cpp parsing_game.cpp astart.cpp generation.cpp \
				solvability.cpp heuristique.cpp other.cpp)
HEADER_DIR	= include

OBJ_DIR		= obj
OBJ			= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_DIR		= dep
DEP			= $(SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
			@echo "$(Green)*** $(UGreen)Successfully compiled $(NAME)$(Green) ***$(nc)"

-include $(DEP)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
			@mkdir -p $(OBJ_DIR) $(DEP_DIR)
			$(CC) -MMD $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@
			@mv $(OBJ_DIR)/*.d $(DEP_DIR)

#----------------------------ALL----------------------------

all:		$(NAME)

clean:
			@echo "$(BRed)/!\\ $(BYellow)Remove containers obj and dep$(BRed) /!\\ $(nc)"
			@$(RM) $(OBJ) $(DEP)

fclean:		clean
			@echo "$(BRed)/!\\ $(BYellow)Remove $(NAME)$(BRed) /!\\ $(nc)"
			@$(RM) $(NAME)

re:			fclean
			@make all --no-print-directory

.PHONY:		all clean fclean re

#------------------------------COLOR------------------------------

nc=\033[0m
Green=\033[0;32m
BRed=\033[1;31m
BYellow=\033[1;33m
UGreen=\033[4;32m
On_Green=\033[42m
