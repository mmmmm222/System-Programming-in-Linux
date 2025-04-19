#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Variable
{
    char Name[50];
    char Value[50];
    struct Variable *Next ;
}Variable;

int Check_Internal_comm(char ** args);
int zexit();
int zpwd();
int zecho(char ** args);
int zcd(char ** args);
bool is_var(char ** args);
void env();
bool set_local_var();
int zexport(char** args);