#include "main.h"

int main()
{
  struct info PASSED_INFO = get_path();
  
}

struct info get_path(void)
{
    struct info INFO = {0};
    FILE *STREAM = fopen("save.txt","r");
    if(STREAM == NULL){return INFO;}

    char *BUFFER;
    if ( (BUFFER = malloc(1024)) == NULL)
    {
        printf("malloc failed");
        return INFO;
    }    

    fseek(STREAM,0,SEEK_SET); //redundant
    char *P = BUFFER;

    int ch;
    char **ptr = &BUFFER; //ptr to dyn all arr BUFFER ptr 

    while( (ch = fgetc(STREAM)) != EOF)
    {
        **ptr = (char)ch;
        (*ptr)++;
        
    }
    ////////////
    strncpy(INFO.path, P, 1023);
    ////////////
    
    printf("BUFFER CONTENTS>>> %s",P);
    fclose(STREAM);
    free(P);
    return INFO;
}