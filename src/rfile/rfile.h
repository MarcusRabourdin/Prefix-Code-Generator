#ifndef RFILE_H
#define RFILE_H

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


struct Key_value
{
    struct Key_value *next;
    char letter;
    char* code;
    char* encoded;
};

void decode(char* path);
struct Key_value *create_node(char letter, char* code);
struct Key_value *add_node(struct Key_value *node,struct Key_value *to_add);
void free_list(struct Key_value *node);
void print_list(struct Key_value *node);
struct Key_value *parseFile(char* path);
struct Key_value *getKeyValue(char* line);
char* getEncodedMessage(char* string);

#endif // ! RFILE_H
