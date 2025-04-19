#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Internal_comm.h"
#include "./External_comm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * getLine();


#define MAX_INPUT 1024

char** parseInput(char * input);
void FreeTokens(char ** Tokens);


extern char **environ;

#endif