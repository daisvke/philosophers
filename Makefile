NAME			=	philo
CC				=	clang $(INC) $(THREADS) $(WFLAGS)
WFLAGS			=	-Wall -Wextra -Werror
INC				=	-I inc
THREADS			=	-pthread
MEM				=	-fsanitize=thread -g
RM				=	rm -rf

SRC_DIR			=	src/
SRC_FILES		=	check_state.c \
					error_handler.c \
					exit.c \
					init_struct.c \
					main.c \
					message_center.c \
					monitor.c \
					philo_routine.c \
					philo_routine_eating.c \
					philo_run.c \
					system_calls.c \
					system_calls_threads.c \
					utils.c
SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR			=	obj/
OBJ_FILES		=	$(SRC_FILES:.c=.o)
OBJ				=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p obj/
		@$(CC) -c $< -o $@  

clean:
		@$(RM) $(OBJ_DIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean flcean re
