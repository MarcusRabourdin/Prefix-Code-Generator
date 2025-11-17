#include "tree.h"

static struct tree *create_node(char data)
{
    struct tree *new_node = malloc(sizeof(struct tree));
    new_node->data = data;
    new_node->right_child = NULL;
    new_node->left_child = NULL;
    return new_node;
}

static void add_node(struct tree *root, struct tree *leaf, char *associate_code,
                     size_t j)
{
    if (associate_code[j + 1] != '\0')
    {
        if (associate_code[j] == '0')
        {
            if (!root->left_child)
            {
                root->left_child = create_node('\0');
            }
            add_node(root->left_child, leaf, associate_code, j + 1);
        }
        else if (associate_code[j] == '1')
        {
            if (!root->right_child)
            {
                root->right_child = create_node('\0');
            }
            add_node(root->right_child, leaf, associate_code, j + 1);
        }
        else
        {
            printf("Invalid char: %c", associate_code[j]);
            exit(1);
        }
    }
    if (associate_code[j + 1] == '\0')
    {
        if (associate_code[j] == '1')
            root->right_child = leaf;
        else if (associate_code[j] == '0')
            root->left_child = leaf;
    }

    return;
}

struct tree *build(char *letter, char *associate_code[])
{
    size_t nb_leaf = strlen(letter);
    struct tree *root = create_node('\0');

    for (size_t i = 0; i < nb_leaf; i++)
    {
        struct tree *new_leaf = create_node(letter[i]);
        add_node(root, new_leaf, associate_code[i], 0);
    }

    return root;
}

void print_tree(struct tree *root)
{
    if (root == NULL)
        return;

    print_tree(root->left_child);
    printf("%c -> ", root->data);
    print_tree(root->right_child);
}

void free_tree(struct tree *root)
{
    if (!root)
        return;
    free_tree(root->left_child);
    free_tree(root->right_child);
    free(root);
}

char search(struct tree *root, char *code, int *offset)
{
    if (!root)
    {
        return '+';
    }
    size_t i = 0;
    //putchar(code[i]);
    while (code[i])
    {
        //putchar(code[i]);
        if (code[i] == '0')
        {
            root = root->left_child;
        }
        else if (code[i] == '1')
        {
            root = root->right_child;
        }
        if(!root)
        {
            printf("invalid code\n");
            exit(1);
        }

        if ('a' <= root->data && root->data <= 'z')
            return root->data;
        (*offset)++;
        i++;
    }

    printf("Not found\n");
    exit(1);
}
