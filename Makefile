CC				=	clang -Wall -Wextra -Werror $(FLAGS)
FLAGS			=	-Wall -Wextra -Werror $(THREADS)
THREADS			=	-pthread
MEM				=	-fsanitize=address
