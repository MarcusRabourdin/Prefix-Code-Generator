CC = gcc
CFLAGS = -std=c99 -Werror -Wall -Wextra -Wvla -pedantic -fsanitize=address -g
SRCS = src/tree/tree.c src/PrefixCode/prefix.c
SRCS += src/rfile/rfile.c src/rfile/utils.c src/main.c
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST:.c=.o)

tree: $(OBJS)
	$(CC) $(OBJS) -o tree -fsanitize=address -g

check: $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o check -fsanitize=address -g
	./check

clean:
	$(RM) *.o tree check
	$(RM) src/tree/tree.o
	$(RM) src/PrefixCode/prefix.o
	$(RM) src/rfile/rfile.o
	$(RM) src/rfile/utils.o
