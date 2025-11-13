#include "prefix.h"

int main(void)
{
    char* letter = "abcdef";
    char* key_value[] = {"0","101","100","111","1101","1100",NULL};
    char* encoded = "11011100110001001101";
    

    char* decoded = decode(encoded,key_value,letter);
    printf("le message est %s\n",decoded); 
    
    free(decoded);
    return 0;
}



char* decode(char* encoded,char* key_value[], char* letter)
{
    struct tree *encoded_tree = build(letter,key_value);
    size_t len = strlen(encoded); 
    char* decoded = malloc(len*sizeof(char)); 
    int offset;
    size_t i = 0;         
    while(key_value[i]!=NULL)
    {
       decoded[i] = search(encoded_tree, encoded,&offset); 
       //printf("iteration: %ld\n",i);
       encoded+=offset + 1;
       offset = 0;
       i++;
    }

    decoded[i] = '\0';
    free_tree(encoded_tree);
    return decoded;
}
