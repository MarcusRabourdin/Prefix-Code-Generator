#define _GNU_SOURCE
#include "rfile.h"

char* skip_last(char* string);


struct Key_value *create_node(char letter, char *code)
{
    struct Key_value *node = malloc(sizeof(struct Key_value));
    if (!node)
    {
        perror("malloc error");
        return NULL;
    }
    node->next = NULL;
    node->letter = letter;
    node->code = skip_last(code);
    node->encoded = NULL;
    return node;
}

struct Key_value *add_node(struct Key_value *node, struct Key_value *to_add)
{
    if (!node)
    {
        perror("add_node to empty list");
        return NULL;
    }

    struct Key_value *current = node;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = to_add;
    return node;
}

void free_list(struct Key_value *node)
{
    if(!node)
        return;
    free(node->encoded);
    
    while(node != NULL)
    {
        struct Key_value *tmp = node;
        node = node->next;
        free(tmp->code);
        free(tmp);


    }
    return;
}

static char *format(char *string)
{
    size_t string_length = strlen(string);
    char *new_string = malloc(string_length * sizeof(char) + 1);
    size_t i = 0;
    size_t j = 0;
    while (string[i])
    {
        char c = string[i];
        if (c != ' ')
        {
            new_string[j] = string[i];
            j++;
        }

        i++;
    }
    new_string[j] = '\0';

    return new_string;
}

struct Key_value *getKeyValue(char *line)
{
    char *formated = format(line);
    if (formated[1] != ':')
    {
        printf("Invalid Format!\n\nshoud be:[letter]:[code]\n");
        printf("get:\n    %s\n",formated);
        free(formated);
        exit(1);
    }

    char letter = line[0];
    char code[10];
    size_t i = 2;
    while(formated[i])
    {
        //putchar(formated[i]);
        code[i - 2] = formated[i];
        i++;
    }
    code[i - 2] = '\0';
    struct Key_value *node = create_node(letter, code);
    free(formated);
    return node;
}

char* getEncodedMessage(char *string)
{
    char* string2 = format(string);
    char* ptr2 = &string2[0];
    string2++;
    char* encoded = malloc(strlen(string) * sizeof(char)+1);
    char* ptr = &encoded[0];
    while (*string2)
    {
        *(ptr++) = *(string2++);
    }
    *ptr = '\0';
    free(ptr2);
    return encoded;
}

void print_list(struct Key_value *node)
{
    printf("encoded_message = %s\n", node->encoded);
    node = node->next; // to skip the start node
    printf("[letter,code]\n");
    while (node != NULL)
    {
        printf("(%c,%s)\n",node->letter, node->code);
        node = node->next;
    }

    return;
}

char* skip_last(char* string)
{
    int len = strlen(string);
    char* new_string = malloc(len* sizeof(char));
    size_t i = 0;
    while(string[i+1])
    {
        new_string[i] = string[i];
        i++;
    }
    new_string[i] = '\0';
    return new_string;
}


size_t list_len(struct Key_value *start)
{
    if(!start)
        return 0;
    return 1+list_len(start->next);
}


void getdata(struct Key_value *list, char* letter, char* key_value[])
{
    if(!list)
        return;
    size_t i = 0;
    list = list->next;
    while(list != NULL)
    {
        letter[i] = list->letter;
        key_value[i] = strdup(list->code);
        list = list->next;
        i++;
    }
    letter[i] = '\0';
    key_value[i] = NULL;
    return;
}



