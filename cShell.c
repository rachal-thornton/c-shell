/* 
    Author: Rachal Thornton
    Class: CS 366-01
    Assignment: Homework 2 | cShell
    Due: 17 March 2026
    Desc: A basic shell program written in C that supports an interactive and batch mode.
*/

/* Preprocessor Directives */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_LINE_SIZE 100
#define MAX_ARGS_SIZE 12

/* Function Prototypes */
void interactive_mode();
void batch_mode();
void trim(char *str, char *dest);

/* Main */
int main(int argc, char *argv[]) {
    /* Interactive Mode */
    if (argc == 1) { /* No additional args provided besides program name itself */
        interactive_mode();
        return 0;
    /* Batch Mode */
    } else if (argc == 2) { /* One additional arg provided as a batch file */
        batch_mode();
        return 0;
    /* Too many args */
    } else { /* More than one additional arg provided */
        printf("Too many args provided. Please provide at most 1 additional arg for batch mode.\n");
        return 1;
    }
}

/* Interactive Mode Function */
void interactive_mode() {
    char *input = malloc(sizeof(char) * MAX_LINE_SIZE);
    char *dest = malloc(sizeof(char) * MAX_LINE_SIZE);
    char *args[MAX_ARGS_SIZE];

    /* Infinite loop to run user commands in interactive mode */
    while (1) {
        /* Display prompt and get user input */
        printf("$ ");
        fgets(input, MAX_LINE_SIZE, stdin);
        /* Trim whitespace from input */
        trim(input, dest);
        
        /* Check for specific commands or execute command with execvp and fork */
        if (strlen(dest) == 0) { /* Empty input */
            continue;
        } else if (strcmp(dest, "quit") == 0) { /* Exit the shell program */
            break;
        } else if (strcmp(dest, "help") == 0) { /* Help menu */
            printf("This is the help menu. Valid commands in this shell are:\n");
            printf("1. help - displays this menu.\n");
            printf("2. quit - exit the shell program.\n");
            printf("3. <other> - other commands compatible with Base.\n");
        } else { /* Any other command in Bash */
            int i = 0;
            
            char *token = strtok(dest, " ");
            while (token != NULL && i < MAX_ARGS_SIZE - 1) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            args[i] = NULL; /* Null-terminate the args array */

            /* Fork a new process */
            int p = fork();
            if (p == -1) {
                printf("Error forking new process!\n");
            } else if (p == 0) {
                /* Child process */
                if (execvp(args[0], args) == -1) {
                    printf("Invalid command!\n");
                }
                abort();
            } else {
                /* Parent process */
                int child_status;
                int tpid;
                do {
                    tpid = wait(&child_status);
                } while (tpid != p);
            }
        }
    }
    /* Free memory */
    free(input);
    free(dest);
}

/* Batch Mode Function */
void batch_mode() {
}

/* Trim Function */
void trim(char *str, char *dest) {
    memset(dest, '\0', sizeof(char) * MAX_LINE_SIZE);

    while (isspace(*str)) {
        str++;
    }

    int len = strlen(str);
		int i;
		for(i = len - 1; ; i--) {
			if(!isspace(str[i])) {
				break;
			}	
		}

	strncpy(dest, str, i + 1);
}


