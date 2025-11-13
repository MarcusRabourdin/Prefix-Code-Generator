CC = gcc
CFLAGS = -std=c99 -Werror -Wall -Wextra -Wvla -pedantic -fsanitize=address -g
SRCS = src/tree/tree.c src/PrefixCode/prefix.c
OBJS = $(SRCS:.c=.o)

tree: $(OBJS)
	$(CC) $(OBJS) -o tree -fsanitize=address -g

clean:
	$(RM) *.o tree
	$(RM) src/tree/tree.o
