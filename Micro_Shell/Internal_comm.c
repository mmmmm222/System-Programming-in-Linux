#include "./Internal_comm.h"

// the state of the command EXECUTED "intenally" or not 
int EXECUTED = 0 , i =0;
// global pointer points to the environment variable
extern char **environ;
// global pointers carries the var conents
char* varName = NULL;
char* varValue = NULL;
char error_fd[MAX_INPUT];char output_fd[MAX_INPUT];char input_fd[MAX_INPUT];
// pointer to the head of the local envs list
Variable *Head = NULL;


/*
 * @Function :  Check_Internal_comm
 * --------------------------
 * @brief    :  CHECK THE COMMAND CAN BE EXECUTED INTERNALLY THEN CALL ITS FUNCTION OR NEED TO EXECUTED EXTERNALLY
 * @parameter:  THE INPUT LINE FROM USER
 *
 * @returns	 : 	AN INTEGER SHOWS IF THE COMMAND EXECUTED OR NOT
 */
int Check_Internal_comm(char ** args ){

    EXECUTED = 0;

    // check for variables
    if(is_var(args)){
        set_local_var();
    }

    if(Check_redirection(args)){
        redirect();
    }

    // terminate the shell session
    if (strcmp(args[0], "exit") == 0) {
        zexit();
    }
    // pwd built in
    else if (strcmp(args[0], "pwd") == 0) {
        zpwd();
    }
    // if the user wants to use echo utility
    else if (strcmp(args[0], "echo") == 0) {
        zecho(args);
    }
    // if the user wants to change the current working directory
    else if (strcmp(args[0], "cd") == 0) {
        zcd(args);
    }
    else if (strcmp(args[0], "env") == 0 || strcmp(args[0], "printenv") == 0) {
        env();
    }
    else if(strcmp(args[0], "export") == 0 ){
        zexport(args);
    }

    return EXECUTED;
}

/*
 * @Function :  zexit
 * --------------------------
 * @brief    :  TERMINATE THE CURRENT WORKING SHELL
 * @parameter:  VOID
 *
 * @returns	 : 	VOID
 */
int zexit(){

    printf("i will exit now :(\n");
    exit(1);

}

/*
 * @Function :  zpwd
 * --------------------------
 * @brief    :  PRINT CURRENT WORKING DIRECTORY
 * @parameter:  THE INPUT LINE FROM USER
 *
 * @returns	 : 	AN INTEGER SHOWS IF THE CWD CHANGED CORRECTLY
 */
int zpwd(){
    //P_Name --> string to store the path of the current working directory
    char* cwd;
    //Path_Name --> a pointer to charachter to store the state of return from getcwd() to check if there is an error
    cwd = getcwd(NULL, 0);
    // check on error
    if (cwd == NULL) {
        printf("Error in buffer Length\n");
        return -1;
    }
    // print the path
    printf("Built in pwd output $$ ");
    printf("%s\n", cwd);
    free(cwd);
    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities 
    EXECUTED = 1;
}

/*
 * @Function :  zecho
 * --------------------------
 * @brief    :  PRING THE PASSED LINE OR PRINT A STORED VARIABLE
 * @parameter:  THE INPUT LINE FROM USER
 *
 * @returns	 : 	AN INTEGER SHOWS IF THE CWD CHANGED CORRECTLY
 * @NOTE     : 	PUT $ BEFORE THE VAR NAME WHICH YOU NEED TO PRINT
 */
int zecho(char ** args){
    i = 1;
        while (args[i] != NULL){
            if(args[i][0] == '$'){
                Variable *var_ptr = Head;
                //check local
                while (var_ptr != NULL)
                {
                    if(strcmp(args[i] + 1 ,var_ptr->Name) == 0){
                        printf("%s\n", var_ptr->Value);
                        return 0;
                    }
                    var_ptr = var_ptr->Next;
                }
                // check environment variables
                char* value = getenv(args[i] + 1);
                if(value){
                    printf("%s\n", value);
                }
                else{
                    printf(" ");
                }
            }
            else{
                // print the token
                printf("%s", args[i]);
                // if there is more words in the stack print a white space
                if (args[i + 1] != NULL) {
                    printf(" ");
                }
            }
            i++;
        }
        //if the stack is empty print new line
        printf("\n");
        // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities
        EXECUTED = 1;
}

/*
 * @Function :  zcd
 * --------------------------
 * @brief    :  CHANGE CURRENT WORKING DIRECTORY
 * @parameter:  THE PATH WHICH TO BE MOVED TO
 *
 * @returns	 : 	AN INTEGER SHOWS IF THE CWD CHANGED CORRECTLY
 * @NOTE     : 	PASS AN ALRDY EXSITING PATH OR IT WILL FAIL
 */
int zcd(char ** args){
        
    // ch_status --> variable to store the changing operation status in
    int ch_status = 0;
    // use "chdir()" to change the current working directory
    ch_status = chdir(args[1]);
    // check on the status
    if (args[1] == NULL) {
        printf("cd need a path\n");
        return -1;
    }
    // check on the status
    else if (ch_status != 0) {
        printf("Can not change directory\n");
        return -1;
    }
    //print this message to tell the user that he used the built in utility
    printf("directory changed internally\n");
    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities 
    EXECUTED = 1;
}

/*
 * @Function :  is_var "helper function not a utility"
 * --------------------------
 * @brief    :  CHECK IF THE BASSED LINE CONTAINS A VAR OR NOT
 * @parameter:  THE INPUT ARGUMENTS FROM USER
 *
 * @returns	 : 	IS IT A VAR OR NOT
 */
bool is_var(char ** args){
    // check if the  arg is just two elements
    char *occurance = strchr(args[0], '=');

    if(occurance && args[1] == NULL){
        *occurance = 0;
        varName = args[0];
        varValue = occurance + 1;
        return true;
    }
    else{
        // perror("not name=value");
        return false;
    }
}

/*
 * @Function :  set_local_var
 * --------------------------
 * @brief    :  ADD THE PASSED VAR "NAME" "VALUE" TO THE LOCAL LIST
 * @parameter:  VOID
 *
 * @returns	 : 	TRUE IF THE VAR ADDED CORRECTLY , FALSE IF THERE IS AN ERROR
 * @NOTE     : 	PASS A VALUE IF YOU DO NOT PASSED A VALUE THERE VALUE WILL BE NON
 */
bool set_local_var(){
    Variable *var_ptr = Head;
    // check if this var is stored before with the same name or not
    while (var_ptr != NULL)
    {
        if(strcmp(varName ,var_ptr->Name) == 0){
            strcpy(var_ptr->Value , varValue);
            return 0;
        }
        var_ptr = var_ptr->Next;
    }

    // store the new var
    Variable *new_var = (Variable*)malloc(sizeof(Variable));

    if(new_var != NULL){
        strcpy(new_var->Name ,varName);
        strcpy(new_var->Value ,varValue);
    }
    
    new_var->Next = Head;
    Head = new_var;
    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities 
    EXECUTED = 1;
}

/*
 * @Function :  env
 * --------------------------
 * @brief    :  PRINT ALL LOCAL & ENVIROMNMENT VARIABLES 
 * @parameter:  VOID
 *
 * @returns	 : 	VOID
 * @NOTE     : 	THERE IS PARAMETERS PUT THEY ARE GLOBAL SO WEW DO NOT PASS THEM
 */
void env(){
    Variable *var_ptr = Head;
    int i = 0;
    // print local
    while (var_ptr != NULL)
    {
      printf("%s=%s\n",var_ptr->Name , var_ptr->Value);
      var_ptr = var_ptr->Next;
    }
    // print environ
    while(environ[i] != NULL){
        printf("%s",environ[i]);
        i++;
    }
    printf("\n");
    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities 
    EXECUTED = 1;
}

/*
 * @Function :  zexport
 * --------------------------
 * @brief    :  EXPORT THE INPUT VAR TO ENVIRONS
 * @parameter:  THE INPUT ARGUMENTS FROM USER
 *
 * @returns	 : 	INTEGER
 * @NOTE     : 	THE LOCAL VAR STILL IN LOCAL LIST AFTER BEING EXPORTED
 */

 int zexport(char** args){
    if(args[1] == NULL){
        perror("must give an env to export");
        return -1;
    }
    
    Variable *var_ptr = Head;
    
    //check the if the value is updated then update the global pointers to carry the new Name & its value
    char *occurance = strchr(args[1], '=');
    
    if(occurance && args[2] == NULL){
        *occurance = 0;
        // update the name & value in the global ptrs
        varName = args[1];
        varValue = occurance + 1;
        // update the value in local then export
        while (var_ptr != NULL)
        {
            if(strcmp(varName ,var_ptr->Name) == 0){
                strcpy(var_ptr->Value , varValue);
                setenv(var_ptr->Name , var_ptr->Value, 1);
                return 0;
            }
            var_ptr = var_ptr->Next;
        }
    }
    else{
        // perror("not name=value");
        exit(-1);
    }
    // check the stored value with the same name then export
    while (var_ptr != NULL)
    {
        if(strcmp(varName ,var_ptr->Name) == 0){
            // export the old value because there is no new one
            setenv(var_ptr->Name , var_ptr->Value, 1);
            return 0;
        }
        var_ptr = var_ptr->Next;
    }
    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities 
    EXECUTED = 1;
 }

/*
 * @Function :  zexport
 * --------------------------
 * @brief    :  EXPORT THE INPUT VAR TO ENVIRONS
 * @parameter:  THE INPUT ARGUMENTS FROM USER
 *
 * @returns	 : 	INTEGER
 * @NOTE     : 	THE LOCAL VAR STILL IN LOCAL LIST AFTER BEING EXPORTED
 */
 bool Check_redirection(char** args){

    for(int c =0; c< MAX_INPUT; c++){
        error_fd[c] = 0; output_fd[c] = 0; input_fd[c] = 0;
    }
    char *occurance;
    for(int cnt = 0; args[cnt]; cnt++){
        //check error redirection
        if(occurance = strstr(args[cnt], "2>")){
            // check the format is >nfd || > nfd
            if(strlen(args[cnt]) == 2){
                strcpy(error_fd , args[cnt+1]);
            }
            else if(strlen(args[cnt]) > 2 ) { 
                strcpy(error_fd , occurance+2);
            }
        }
        //check output redirection
        if(occurance = strchr(args[cnt], '>')){
            // check the format is >nfd || > nfd
            if(strlen(args[cnt]) == 1){
                strcpy(output_fd , args[cnt+1]);
            }
            else if((strlen(args[cnt]) > 1) && (strstr(occurance - 1, "2")) == NULL ) { 
                strcpy(output_fd , occurance+1);
            }
        }
        //check input redirection
        if(occurance = strchr(args[cnt], '<')){
            if(strlen(args[cnt]) == 1){
                strcpy(input_fd , args[cnt+1]);
            }
            else{
                strcpy(input_fd , occurance+1);
            }
        }
    }
    if(strlen(error_fd) > 0 || strlen(output_fd) > 0 || strlen(input_fd) > 0 ){
        return 1;
    }

    return 0;
 }

/*
 * @Function :  zexport
 * --------------------------
 * @brief    :  EXPORT THE INPUT VAR TO ENVIRONS
 * @parameter:  THE INPUT ARGUMENTS FROM USER
 *
 * @returns	 : 	INTEGER
 * @NOTE     : 	THE LOCAL VAR STILL IN LOCAL LIST AFTER BEING EXPORTED
 */
void redirect(){
    if(strlen(error_fd) > 0){
       int E_fd = open(error_fd, O_WRONLY | O_CREAT | O_TRUNC , 0644);
       dup2(E_fd, 2);
       close(E_fd);
    }
    if(strlen(output_fd) > 0){
        int O_fd = open(output_fd, O_WRONLY | O_CREAT, 0644);
        dup2(O_fd, 1);
        close(O_fd);
    }
    if(strlen(input_fd) > 0){
        int I_fd = open(input_fd, O_RDONLY, 0644);
        dup2(I_fd,0);
        close(I_fd);
    }
 }