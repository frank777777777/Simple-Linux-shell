
//Tis program is coded by Yili Zou(yxz163931) and Jing Zhou(jxz160330)
//It is a simple shell with maximum parameters of 10 
//and maxumum command length of 50.
//Divide command with space, e.g. 'ls -a'.
//Enter 'exit' to end this program.
//to compile this program, use 'gcc -o myshell myshell.c'
//to run the program, use './myshell'

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



void parseCmd(char* cmd, char** params);
int executeCmd(char** params);

#define MAX_COMMAND 50
#define MAX_PARAMS 10

int main()
{
    
    char cmd[MAX_COMMAND + 1];
    char* params[MAX_PARAMS + 1];


    int cmdCount = 0;
	printf("Tis program is coded by Yili Zou(yxz163931) and Jing Zhou(jxz160330).\n");
    printf("It is a simple shell with maximum parameters of 10,\n");
    printf("and maxumum command length of 50.\n");
    printf("Divide command with space, e.g. 'ls -a'.\n");
    printf("Enter 'exit' to end this program.");

    while(1) {
        // Print command prompt, with user name and command count
        char* username = getenv("USER");
        printf("%s@shell %d> ", username, ++cmdCount);

        // Read command
        if(fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            break;
        }


        // Remove new line tailing to the command
        if(cmd[strlen(cmd)-1] == '\n') {
            cmd[strlen(cmd)-1] = '\0';
        }

        // parse the command string and Split cmd into array of parameters
        parseCmd(cmd, params);


        // Exit when user enters "exit"
        if(strcmp(params[0], "exit") == 0)
        {
            break;
        }

        // Execute command, if failed, exit the loop
        if(executeCmd(params) == 0)
        {
            break;
        }

    }
    printf("There were %d commands executed.", cmdCount);
    return 0;
}

// split the cmd String, with delimiter of space
void parseCmd(char* cmd, char** params)
{

    params[0] = strtok(cmd," ");
    int i;

    for(i = 1; i < MAX_PARAMS; i++)
    {
        params[i] = strtok(NULL, " ");
        if(params[i] == NULL)
        {
            break;
        }
    }

}

int executeCmd(char** params)
{
    // Fork system call
    pid_t pid = fork();

    // Error creating a new process
    if (pid == -1) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }

    // Child process execution
    else if (pid == 0) {
        // Execute command, the first element of the array is the file name, pass the others to the program.
        if(execvp(params[0], params)<0)
        {
        // if execvp returns negative, file not found, Error occurred
        char* error = strerror(errno);
        printf("Launching: %s: %s\n", params[0], error);
        }
        return 0;
    }

    // Parent process
    else {
        // Wait for child process to finish
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return 1;
    }
}