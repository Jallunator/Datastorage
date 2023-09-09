FLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard srcs/*.c srcs/DataStorage/*.c)
OBJ  = $(SRCS:.c=.o)
TARGET = exe

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(FLAGS) -o $@ $^ -lncurses

%.o: %.c
	gcc -c $< -o $@ -lncurses -I includes

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f *.gch exe

re: fclean all

.PHONY: fclean all clean

