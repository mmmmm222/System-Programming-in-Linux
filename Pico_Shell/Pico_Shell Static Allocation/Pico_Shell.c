#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 100
#define BUF_COUNT 100
int EXECUTED = 0;

int main(int argc, char **argv)
{
    char buf[BUF_COUNT];

    while (1) {

	fflush(stdin);
	printf("Yalla beina -->");

	// Take the command from the user
	char *fgets_ret = fgets(buf, BUF_COUNT, stdin);
	if (fgets_ret == NULL) {
	    printf("error while reading from stdin");
	}
	// remove the /n from the end of the buffer & put null
	buf[strlen(buf) - 1] = 0;

	// -------------- parsing---------------
	char *new_argvs[10] = { NULL };
	char *ret = strtok(buf, " ");
	int i = 0;
	while (ret != NULL) {
	    new_argvs[i] = ret;
	    ret = strtok(NULL, " ");
	    i++;
	}

	// check if the user just entered an "enter"
	if (strlen(buf) == 0) {
	    continue;
	}
	// check if the user wants to end the program
	else if (strcmp((new_argvs[0]), "exit") == 0) {
	    printf("i will exit now \n");
	    exit(1);
	}
	// pwd built in
	else if (strcmp(new_argvs[0], "pwd") == 0) {
	    char P_Name[100];
	    char *Path_Name = getcwd(P_Name, SIZE);

	    if (Path_Name == NULL) {
		printf("Error in buffer Length\n");
		exit(-1);
	    }
	    printf("Built in pwd output $");
	    printf("%s\n", P_Name);
	    EXECUTED = 1;
	}
	// ---------------------------  fork -------------------------------
	// fork_ret --> to carry the return value from fork() , to check where are the program now (in child or parent)
	// wstatus  --> to check on the way of termination of the child  
	int fork_ret, wstatus;
	if (!EXECUTED) {
	    fork_ret = fork();
	    if (fork_ret > 0) {
		// in parent
		// wait --> force the parent to wait until his child die :(
		wait(&wstatus);
		// if u want to know the  return status of the child process
		//printf("%d" , WEXITSTATUS(wstatus));
	    } else if (fork_ret == 0) {
		// in child
		//
		// execute the program
		//

		int exec_status;
		char *const argv[] = { NULL };
		char *new_envp[] = { NULL };
		exec_status = execvp(buf, argv);
		// the command can not be executed
		if (exec_status == -1) {
		    printf
			("failed to execute this command i am just a simple shell  :( \n");
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

    }
    return 0;
}
