It is a simple linux shell.

Compile with command: gcc -o myShell myshell.c
Run: ./myShell


Description: A simple C program, when compiled and run, will do what the shell does.

It executes in a loop (until user types exit on the keyboard), prints a prompt on the screen, reads the command typed on the keyboard (terminated by \n), creates a new process and lets the child execute the user’s command, waits for the child to terminate and then goes back to beginning of the loop.
If the command typed is exit, then your program should terminate.
Print the total number of commands executed just before terminating your program.

Assume that each line represents one command only, no command will end with & (all commands will be attached commands, no background execution), user will not type ^c or ^z, all commands are simple commands, etc.