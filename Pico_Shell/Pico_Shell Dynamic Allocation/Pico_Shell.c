#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdio.h>
#include "LinkedStackinterface.h"
#define SIZE 100
#define BUF_COUNT 200
int EXECUTED = 0;

void trv(StackEntry x);



int main(int argc, char **argv)
{
    char buf[BUF_COUNT];

    while (1) {

	printf("Yalla beina -->");

	// Take the command from the user
	char *fgets_ret = fgets(buf, BUF_COUNT, stdin);
	if (fgets_ret == NULL) {
	    printf("error while reading from stdin");
	}
	// remove the /n from the end of the buffer & put null
	buf[strlen(buf) - 1] = 0;
	// if the user just enterd "enter"
	if (strlen(buf) == 0) {
	    continue;
	}
	// -------------- parsing---------------
	// a dynamic allocation stack to store the command line argumenst after parsing it
	Stack new_argvs;
	// initialize the stack
	Stack_voidInit(&new_argvs);
	// parsing "toknize" the command line arguments using ((strtok))
	char *ret = strtok(buf, " ");
	// the paring gives a pointer to the start of each word so we store them one by one
	while (ret != NULL) {
	    // push the parsed word into the stack
	    Stack_voidPush(ret, &new_argvs);
	    // continue parsing on the same command line by enteing "null" at the 1'st argument 
	    ret = strtok(NULL, " ");
	}

	//Element --> is a variable of StackEntry type to store the poped argument from the stack
	StackEntry Element;
	//pop the first element from the stack to make operations on it 
	Stack_voidPop(&Element, &new_argvs);

	// check if the user wants to end the program
	if (strcmp(Element, "exit") == 0) {
	    printf("i will exit now :(\n");
	    exit(1);
	}
	// pwd built in
	else if (strcmp(Element, "pwd") == 0) {
	    //P_Name --> string to store the path of the current working directory
	    char P_Name[100];
	    //Path_Name --> a pointer to charachter to store the state of return from getcwd() to check if there is an error
	    char *Path_Name = getcwd(P_Name, SIZE);
	    // check on error
	    if (Path_Name == NULL) {
		printf("Error in buffer Length\n");
		exit(-1);
	    }
	    // print the path
	    printf("Built in pwd output $");
	    printf("%s\n", P_Name);
	    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities 
	    EXECUTED = 1;
	}
	// if the user wants to use echo utility
	else if (strcmp(Element, "echo") == 0) {
	    // check on the size of stack to print all the text the user enterd
	    while (Stack_u16Size(&new_argvs) != 0) {
		//pop the next word then print
		Stack_voidPop(&Element, &new_argvs);
		printf("%s", Element);
		// if there is more words in the stack print a white space
		if (Stack_u16Size(&new_argvs) != 0) {
		    printf(" ");
		}
	    }
	    //if the stack is empty print new line
	    printf("\n");
	    // make the state of the command EXECUTED "intenally" so no need to fork a new process & ececute from linux utilities
	    EXECUTED = 1;
	}
	// if the user wants to change the current working directory
	else if (strcmp(Element, "cd") == 0) {
	    // ch_status --> variable to store the changing operation status in
	    int ch_status = 0;
	    // the path must be just one word so if it more or less there is an error
	    if (Stack_u16Size(&new_argvs) != 1) {
		printf("too many or few arguments\n");
		exit(-1);
	    }
	    // pop the path 
	    Stack_voidPop(&Element, &new_argvs);
	    // use "chdir()" to change the current working directory
	    ch_status = chdir(Element);
	    // check on the status
	    if (ch_status != 0) {
		printf("Can not change directory");
		return (-1);
	    }
	    //print this message to tell the user that he used the built in utility
	    printf("directory changed internally\n");
	    EXECUTED = 1;
	}
	// if the utility the user needed is not built in so the process will fork & run it from the linux utilities

	// ---------------------------  fork -------------------------------
	// fork_ret --> to carry the return value from fork() , to check where are the program now (in child or parent)
	// wstatus  --> to check on the way of termination of the child  
	int fork_ret, wstatus;
	// fork because the command was not executed
	if (!EXECUTED) {
	    fork_ret = fork();
	    if (fork_ret > 0) {
		// in parent because the fork_ret > 0
		// wait --> force the parent to wait until his child die :(
		wait(&wstatus);
		// if u want to know the  return status of the child process
		//printf("%d" , WEXITSTATUS(wstatus));
	    } else if (fork_ret == 0) {
		// in child because the fork_ret == 0
		//
		// execute the program
		//

		int exec_status;
		// here we do not pass the arguments to the external process because our shell is just a simple shell so pass "Null"
		char *const argv[] = { NULL };
		//use execvp to exexute the program directly by its name not with the full path
		exec_status = execvp(Element, argv);
		// the command can not be executed
		if (exec_status == -1) {
		    printf
			("failed to execute this command i am just a simple shell  :( \n");
		    exit(-1);
		}
	    }
	    // here NOT_EXECUTED is used to clarify if this command has been executed internally so the is no need to frok and exec a new one
	    // so ,if the command has been executed the (NOT_EXECUTED will equal 1)
	    // if not , and the processor has retched this (else if) this means that the command has not been executed internally nor by (frok&execp)
	    else {
		// fork faild
		printf
		    ("the kernel is not in the mood to run this command");
	    }
	}
	// clear the stack to get a new command
	Stack_voidClear(&new_argvs);
	// make the status unexecuted bacuse it is a new command :)
	EXECUTED = 0;
    }
    return 0;
}
