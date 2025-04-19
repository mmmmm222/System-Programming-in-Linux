#include "./include.h"

int Check_External_comm(char ** args){

    // ---------------------------  fork -------------------------------
	// fork_ret --> to carry the return value from fork() , to check where are the program now (in child or parent)
	// wstatus  --> to check on the way of termination of the child  
    int fork_ret, wstatus;

	
    fork_ret = fork();
    
    if (fork_ret > 0) {
        // in parent because the fork_ret > 0
        // wait --> force the parent to wait until his child die :(
        wait(&wstatus);
        // if u want to know the  return status of the child process
        //printf("%d" , WEXITSTATUS(wstatus));
    }
    else if (fork_ret == 0) {
        // in child because the fork_ret == 0 , execute the program
        int exec_status;

        // here we do not pass the arguments to the external process because our shell is just a simple shell so pass "Null"
        char *const argv[] = { NULL };
        
        //use execvp to exexute the program directly by its name not with the full path
        exec_status = execvp(args[0], argv);
        
        // the command can not be executed
        if (exec_status == -1) {
            printf
            ("failed to execute this command i am just a simple shell  :( \n");
            exit(-1);
        }
    }
    // fork faild
    else {
        printf("the kernel is not in the mood to run this command");
    }
}
