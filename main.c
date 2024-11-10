
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define DELIMETER " ,\t\n\r"    //Delimeter are space, tab, mewline, and carriage return.
#define ARG_MAX    68           //ARG_MAX on ubuntu (getconf ARG_MAX) is 2097152, this is too much for our use, 32 would be fine for now.


typedef struct 
{
    char **command;
    char * cmd_type;
}cmd_t;


cmd_t* parse_cmd_arg(){

    int pos = 0; 
    size_t input_command_size = 0;  
    cmd_t *cmd = malloc(sizeof(cmd_t));    

    char *input_command = NULL;         //User input command
    // Need an array of strings to capture all the tokenized input commands
    char **tok_commands = malloc(ARG_MAX * sizeof(char*));

    if (tok_commands == NULL){
        fprintf(stderr, "Invalid pointer initialization.");
    }

    printf(GREEN "metro@"RESET);
    printf(BLUE": > "RESET);
    int ret = getline(&input_command, &input_command_size, stdin);

    if (ret < 0) 
        exit(1);

    
    char *token = strtok(input_command, DELIMETER);
    while (token != NULL)
    {
        /* code */
        tok_commands[pos++] = token;
        token = strtok(NULL, DELIMETER);
    }
    tok_commands[pos] = NULL;
    
    cmd->cmd_type = tok_commands[0];
    cmd->command = tok_commands;
    // free(tok_commands);

    

    return cmd;
}

int exec_cmd(cmd_t *cmd){
    int status;


    // early return if exit command or escape button is pressed.
    if (strcmp(cmd->cmd_type,"exit") == 0){
        printf("exiting..\n");
        free(cmd);
        exit(-1);
    }


    pid_t pid; // holds the return value of fork() function
    
    pid = fork();
    if (pid < 0){
        fprintf(stderr, "Failed to create child process");
        free(cmd);
        exit(-1);
    }

    if (pid == 0){
        execvp(cmd->cmd_type, cmd->command);
    }

    do{
        //Wait for the 
        (void)waitpid(pid, &status, WUNTRACED);
    }while(!WIFEXITED(status) && !WIFSIGNALED(status));

    free(cmd);

    return 1;
}


int main(int argc, char **argv){

    cmd_t *cmd;

    while (1){
        cmd = parse_cmd_arg();

        if(cmd != NULL){
            
            exec_cmd(cmd);
        }
    }

    return 0;
}


