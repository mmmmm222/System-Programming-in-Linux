#include "./include.h"

char * getLine(){

    char *input = NULL;
    // char ** args;
    size_t n = 0;

        printf("911 shell ~~~ ");
        size_t len = getline(&input, &n, stdin);           // here we pass a pointer of the string & a pointer for the size
        
        if(len == -1){
            printf("Error while reading or EOF\n");
            exit(-1);
        }

        input[strlen(input) - 1] = 0;

        return input;    
}