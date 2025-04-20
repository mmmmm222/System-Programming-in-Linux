#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Internal_comm.h"

char * getLine();
char** parseInput(char * input);
void FreeTokens(char ** Tokens);
int Check_External_comm(char ** args );

#define MAX_INPUT 1024
extern char **environ;

#endif