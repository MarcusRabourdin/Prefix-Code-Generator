#define _GNU_SOURCE
#include "rfile.h"

/*
int main(void)
{
    char *path = "tests/filecode.code";

    struct Key_value *list = parseFile(path);
    print_list(list);
    
     
    free_list(list);
    return 1;
}

*/

struct Key_value *parseFile(char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        perror("path doesn't exist");
        exit(1);
    }

    struct Key_value *start = create_node('0', "test");
    //printf("%s\n",start->code);
    char *line = NULL;
    size_t len = 0;
    ssize_t bytes_read;

    while ((bytes_read = getline(&line, &len, fp)) != -1)
    {
        char *colon;
        char *equal;
        if ((colon = strchr(line, ':')) != NULL)
        {
            struct Key_value *node = getKeyValue(line);
            start = add_node(start, node);
        }
        else if ((equal = strchr(line, '=')) != NULL)
        {
            start->encoded = getEncodedMessage(equal);
        }
    }

    free(line);
    fclose(fp);

    return start;
}
