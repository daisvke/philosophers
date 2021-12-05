NAME			=	philo
CC				=	clang $(INC) $(THREADS) -g
WFLAGS			=	-Wall -Wextra -Werror
INC				=	-I inc
THREADS			=	-pthread
MEM				=	-fsanitize=address
RM				=	rm -rf

SRC_DIR			=	src/
SRC_FILES		=	check_state.c \
					eat.c \
					error_handler.c \
					exit.c \
					init_struct.c \
					main.c \
					message_center.c \
					monitor.c \
					philo_routine.c \
					run_philo.c \
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
