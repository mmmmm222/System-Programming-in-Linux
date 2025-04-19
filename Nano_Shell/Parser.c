#include "./include.h"
#include "parser.h"

/*
 * @Function :  parseInput
 * --------------------------
 * @brief    :  PARSE THE INPUT LINE TO TOKENS
 * @parameter:  THE INPUT LINE FROM USER
 *
 * @returns	 : 	A LIST TO THE TOKENS
 * @NOTE     : 	USE FREE FUNCTION TO FREE THE ALLOCATED MEMORY
 */

char** parseInput(char * input){

    size_t buffer_size = MAX_INPUT;
    // allocate a list "array of pointer string to store the pointers to the tokens"
    char ** tokens = malloc(MAX_INPUT * sizeof(char *));
    char * temp_token = NULL;
    size_t temp_token_len = 0;
    
    // used to store the next position at the list ,which the token will be stored in 
    size_t temp_token_pos = 0;


    // Check The Success of -> malloc(MAX_INPUT * sizeof(char *));
    if(!tokens){
        perror("MALLOC");
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; input[i]; i++)
    {
        // ignore any spaces At the beginning of the input
        while (input[i] == ' ' || input[i] == '\n' || input[i] == '\t' || input[i] == '\r' || input[i] == '\a')
        {
            i++;
        }

        //The end of the command
        if(input[i] == '\0') break;

        // point to the start of the token
        temp_token = &input[i];
        int temp_idx = i;
        // printf("%p\n", temp_token);
        if(input[i] == '"'){

            i++;
            printf("last char is%c\n", input[strlen(input) -1]);

            while(input[i] != '"'){
                i++;
                if(input[i] == 0){
                    perror("input");
                    printf("erro");
                }
                // printf("%c\t",input[i]);
            }
            temp_token = &input[temp_idx+1];
            temp_token[i - 1] = 0;
            temp_token_len =  i - temp_idx - 1;
            // printf("%p\n", temp_token);

        }
        else{
            // loop on the input untill find the first space or end of input 
            while(input[i] != '\0' && input[i] != ' ' && input[i] != '\n' && input[i] != '\t' && input[i] != '\r' && input[i] != '\a')
            {
                // increment the token lenght variable
                temp_token_len++;
                // increment to check the next charachter
                i++;
            }
        }
        // allocate a string in the heap with size equal to the lenght of the previous token
        tokens[temp_token_pos] = malloc((temp_token_len + 1)* sizeof(char));
        
        // Check The Success of -> malloc((temp_token_len + 1)* sizeof(char));
        if(!tokens[temp_token_pos]){
            perror("MALLOC");
            exit(EXIT_FAILURE);
        }
        
        // copy the token to the new allocated pos in the list
        for (size_t j = 0; j < temp_token_len; j++)
        {
            tokens[temp_token_pos][j] = temp_token[j];
        }
        
        //put '\0' at the end of the token
        tokens[temp_token_pos][temp_token_len] = '\0';
        
        // increment the pos for the next token
        temp_token_pos ++;

        // make len = 0 to recalc the new token len 
        temp_token_len = 0;

    }

    // there is no more tokens , null termating list
    tokens[temp_token_pos] = NULL;

    
    return tokens;

}



/*
 * @Function :  FreeTokens
 * --------------------------
 * @brief    :  FREE THE ALLOCATED MEMORY FOR THE TOKENS
 * @parameter:  THE POINTER TO THE TOKENs' LIST
 *
 * @returns	 : 	VOID
 */

 void FreeTokens(char ** Tokens){

    if(!Tokens){
        return;
    }

    // free every location holds a token
    for (size_t i = 0; Tokens[i]; i++)
    {
        free(Tokens[i]);
    }

    // free the list of pointers to the tokens it self
    free(Tokens);

 }