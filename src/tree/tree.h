#ifndef TREE_H
#define TREE_H
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct tree
{   
    struct tree *right_child;
    struct tree *left_child;
    char data;

};

struct tree* build(char* letter, char* associate_code[]);
void print_tree(struct tree *root);
void free_tree(struct tree *root);
char search(struct tree *root, char* code, int* offset);
#endif // ! TREE_H
