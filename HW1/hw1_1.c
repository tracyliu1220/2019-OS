#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MAX_LINE 80

int main(void)
{
	char *arg[MAX_LINE/2+1] = {}; /*command line arguments*/
    char *buf = malloc(MAX_LINE * sizeof(char));
	int should_run = 1; /*flag to determine when to exit program*/
    int opt_wait = 1; 
    int status = -1;
	
	while(should_run){
		printf("osh>");
		fflush(stdout);
        opt_wait = 1;

		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will not invoke wait()
		*/
        
        int ret = read(0, buf, MAX_LINE);
        buf[ret] = '\0';
        
        char *ptr = strtok(buf, " \n");
        int arg_len = 0;
        for (arg_len = 0; ptr != NULL; arg_len ++) {
            if (!strncmp(ptr, "&", 1))
                opt_wait = 0;
            else
                arg[arg_len] = ptr;
            ptr = strtok(NULL, " \n");
        }

        // exit
        if (!strncmp(arg[0], "exit", 4)) {
            should_run = 0;
            continue;
        }


        int pid = fork();

        // parent
        if (pid > 0) {
            if (opt_wait) {
                waitpid(pid, &status, 0);
                status = -1;
            }
            // clean
            for (int i = 0; i < arg_len; i++)
                arg[i] = NULL;
            continue;
        }

        // exec
        if (!strncmp(arg[0], "ls", 2))
             execvp("ls", arg);
        if (!strncmp(arg[0], "cat", 3))
             execvp("cat", arg);
        if (!strncmp(arg[0], "date", 4))
             execvp("date", arg);
        if (!strncmp(arg[0], "ps", 2))
             execvp("ps", arg);
        
	}

	return 0;
}

