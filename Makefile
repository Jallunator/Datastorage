FLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard srcs/*.c)
OBJ  = $(SRCS:.c=.o)

all: $(OBJ)
	gcc $(FLAGS) -o exe $^ -lncurses hed.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f *.gch exe

re: fclean all

.PHONY: fclean all clean

