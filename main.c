#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

size_t custom_strcspn(const char *str, const char *delim) {
    const char *ptr = str;
    size_t index = 0;
    int found = 0;

    while (*ptr != '\0') {
        const char *d = delim;
        while (*d != '\0') {
            if (*ptr == *d) {
                found = 1;
                break;
            }
            d++;
        }
        if (found) {
            break;
        }
        ptr++;
        index++;
    }

    return index;
}

void execute_command(char *command) {
    char *args[MAX_ARGUMENTS + 1];
    int arg_count = 0;
    char *token = strtok(command, " ");
    pid_t pid;
    
    while (token != NULL && arg_count < MAX_ARGUMENTS) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    if (arg_count == 0 || strcmp(args[0], "exit") == 0) {
        printf("Exiting shell...\n");
        exit(EXIT_SUCCESS);
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            printf("Command '%s' not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

void read_and_execute() {
    char *command = NULL;
    size_t bufsize = 0;

    while (1) {
        printf("Shell > ");

        if (getline(&command, &bufsize, stdin) == -1) {
            if (feof(stdin)) {
                printf("\nEnd of file (Ctrl+D) detected. Exiting...\n");
                break;
            } else {
                perror("Error reading command");
                exit(EXIT_FAILURE);
            }
        }

        command[custom_strcspn(command, "\n")] = '\0';

        if (strlen(command) > 0) {
            execute_command(command);
        }
    }

    free(command);
}

int main() {
    read_and_execute();
    return 0;
}

