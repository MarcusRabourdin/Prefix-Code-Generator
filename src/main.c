#include "rfile/rfile.h"
#include "PrefixCode/prefix.h"
#include "decode/decode.h"

#define CODE_SIZE 20

int main(void)
{

    char* path = "tests/filecode.code";
    
    struct Key_value *list = parseFile(path);
    
    print_list(list);
    
    size_t nb_letter = list_len(list) - 1;
    char* encoded = list->encoded;

    char* letter = malloc((nb_letter+1) * sizeof(char));
    char* key_value[27] = {0};
    for(size_t i = 0; i<nb_letter;i++)
    {
        key_value[i] = malloc(CODE_SIZE * sizeof(char));
    }
 
    getdata(list,letter, key_value);

    char* decoded_message = decode(encoded,key_value,letter);
    printf("the message is %s\n",decoded_message);
    free(letter);
    free_list(list);
    return 0;
}




