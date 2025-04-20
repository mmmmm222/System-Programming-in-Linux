#include "./include.h"


int main(int argc , char ** argv){

    (void)argc;
    (void)argv;

    char *input = NULL;
    char ** args = NULL;
    
    size_t buffer_size = 1024;

    int EXECUTED_INTERNALLY = 0;
    int EXECUTED_EXTERNALLY = 0;

    while(1){

        // free the tokens to get new ones , i put it here to handel continue statement 
        FreeTokens(args);
        // store the input from user
        input = getLine();
        // store the tokens
        args = parseInput(input);
        
        if(args[0] == NULL){
            continue;
        }
        else{
            // // check if the command can be executed internally
            // EXECUTED_INTERNALLY = Check_Internal_comm(args);
            
            // if the command can not be executed internally check external bin
            if(!Check_Internal_comm(args)){

                if(!Check_External_comm(args))
                {
                    printf("This command can not be executed internally neither externally :(\n");
                }
            }
        }

        if (input) {
            free(input);
            input = NULL;  // Set to NULL after freeing to avoid double free
        }
    }
}
