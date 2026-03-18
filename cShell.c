/* 
    Author: Rachal Thornton
    Class: CS 366-01
    Assignment: Homework 2 | cShell
    Due: 17 March 2026
    Desc: A basic shell program written in C that supports both an interactive and batch mode.
*/

/* Preprocessor Directives */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

/* Constant Values */
#define MAX_LINE_SIZE 100
#define MAX_ARGS_SIZE 12

/* Function Prototypes */
void interactive_mode();
void batch_mode(char *filename);
void trim(char *str, char *dest);
<<<<<<< HEAD
int run_command(char *command);
=======
void run_command(char *command);
>>>>>>> refs/remotes/origin/main

/* Main */
int main(int argc, char *argv[]) {
    /* Interactive Mode */
    if (argc == 1) { /* No additional args provided besides program name itself */
        interactive_mode();
    /* Batch Mode */
    } else if (argc == 2) { /* One additional arg provided as a batch file */
        batch_mode(argv[1]);
<<<<<<< HEAD
=======
        return 0;
>>>>>>> refs/remotes/origin/main
    /* Too many args */
    } else { /* More than one additional arg provided */
        printf("Correct usage: cShell <batch file>\n");
        return 1;
    }
    return 0;
}

/* Interactive Mode Function 
* Pre: No args specified when running the program
* Post: Runs the shell in interactive mode */
void interactive_mode() {
    char *input = malloc(sizeof(char) * MAX_LINE_SIZE);
    char *dest = malloc(sizeof(char) * MAX_LINE_SIZE);

    /* Infinite loop to run user commands in interactive mode */
    while (1) {
        /* Display prompt and get user input */
        printf("$ ");
        fgets(input, MAX_LINE_SIZE, stdin);
        /* Trim whitespace from input */
        trim(input, dest);

<<<<<<< HEAD
        /* Run the command and check if user wants to quit */
        if (run_command(dest)) {
            break;
        }
=======
        /* Pass trimmed input into run_command */
        run_command(dest);
>>>>>>> refs/remotes/origin/main
    }

    /* Free memory */
    free(input);
    free(dest);
}

<<<<<<< HEAD
/* Batch Mode Function 
* Pre: A batch file is provided as an argument
* Post: Runs commands from the batch file */
void batch_mode(char *filename) {
    /* Create a file pointer to read file */
    FILE *filepointer = fopen(filename, "r");

    if (filepointer == NULL) {
        printf("Error opening file!\n");
=======
/* Batch Mode Function */
void batch_mode(char *filename) {
    FILE *filepointer = fopen(filename, "r");
    if (filepointer == NULL) {
        printf("Error opening file. Please check the filename and try again.\n");
>>>>>>> refs/remotes/origin/main
        exit(1);
    } else {
        char *input = malloc(sizeof(char) * MAX_LINE_SIZE);
        char *dest = malloc(sizeof(char) * MAX_LINE_SIZE);

<<<<<<< HEAD
        printf("Batch mode. File: %s\n", filename);

=======
>>>>>>> refs/remotes/origin/main
        /* Read commands from batch file and run them */
        while (fgets(input, MAX_LINE_SIZE, filepointer) != NULL) {
            /* Trim whitespace from input */
            trim(input, dest);
<<<<<<< HEAD

            /* Run the command and check if user wants to quit */
            if (run_command(dest)) {
                break;
            }
        }

=======
            /* Pass trimmed line into run_command */
            run_command(dest);
        }
>>>>>>> refs/remotes/origin/main
        /* Free memory and close file */
        free(input);
        free(dest);
        fclose(filepointer);
    }
}

/* Trim Function 
* Pre: A string is provided as input
* Post: Removes all whitespace and sends trimmed string to dest */
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

<<<<<<< HEAD
/* Run Command Function 
* Pre: A command string is provided as input
* Post: Executes the command */
int run_command(char *command) {
    /* Check for specific commands or execute command with execvp and fork */
    if (strlen(command) == 0) { /* Empty input */
        return 0;
    } else if (strcmp(command, "quit") == 0) { /* Exit the program */
        return 1;
=======
/* Run Command Function */
void run_command(char *command) {
    /* Check for specific commands or execute command with execvp and fork */
    if (strlen(command) == 0) { /* Empty input */
        return;
    } else if (strcmp(command, "quit") == 0) { /* Exit the shell program */
        exit(0);
>>>>>>> refs/remotes/origin/main
    } else if (strcmp(command, "help") == 0) { /* Help menu */
        printf("This is the help menu. Valid commands in this shell are:\n");
        printf("1. help - displays this menu.\n");
        printf("2. quit - exit the shell program.\n");
        printf("3. <other> - other commands compatible with Base.\n");
<<<<<<< HEAD
        return 0;
=======
>>>>>>> refs/remotes/origin/main
    } else { /* Any other command in Bash */
        char *args[MAX_ARGS_SIZE];
        int i = 0;

        /* Get tokens from command */
<<<<<<< HEAD
        char *token = strtok(command, " \t");
        while (token != NULL && i < MAX_ARGS_SIZE - 1) {
            args[i] = token;
            token = strtok(NULL, " \t");
=======
        char *token = strtok(command, " /t");
        while (token != NULL && i < MAX_ARGS_SIZE - 1) {
            args[i] = token;
            token = strtok(NULL, " /t");
>>>>>>> refs/remotes/origin/main
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
<<<<<<< HEAD
                printf("Invalid command! Please type 'help' for more information.\n");
=======
                printf("Invalid command!\n");
>>>>>>> refs/remotes/origin/main
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
<<<<<<< HEAD
        return 0;
=======
>>>>>>> refs/remotes/origin/main
    } 
}