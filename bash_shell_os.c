#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_cd(char *args[]);
void handle_echo(char *args[]);
void handle_pwd();
void handle_ls(char *args[]);
void handle_cat(char *args[]);
void handle_date(char *args[]);
void handle_rm(char *args[]);
void handle_mkdir(char *args[]);

int main() {
    char input[1024];
    char *args[64];
printf("***************Welcome to my shell**************");
printf("\n\n\n\n");
    while (1) {
        printf("$my shell$");
        fflush(stdout);

        // Read user input
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        // Split input into arguments
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        } else if (strcmp(args[0], "cd") == 0) {
            handle_cd(args);
        } else if (strcmp(args[0], "echo") == 0) {
            handle_echo(args);
        } else if (strcmp(args[0], "pwd") == 0) {
            handle_pwd();
        } else if (strcmp(args[0], "ls") == 0) {
            handle_ls(args);
        } else if (strcmp(args[0], "cat") == 0) {
            handle_cat(args);
        } else if (strcmp(args[0], "date") == 0) {
            handle_date(args);
        } else if (strcmp(args[0], "rm") == 0) {
            handle_rm(args);
        } else if (strcmp(args[0], "mkdir") == 0) {
            handle_mkdir(args);
        } else {
            printf("Invalid command\n");
        }
    }
}

void handle_cd(char *args[]) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
    } else if (chdir(args[1]) != 0) {
        perror("cd");
    }
}

void handle_echo(char *args[]) {
    int i = 1;
    while (args[i] != NULL) {
        printf("%s ", args[i++]);
    }
    printf("\n");
}

void handle_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void handle_ls(char *args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (args[1] != NULL && args[2] != NULL) {
            execl("/bin/ls", "ls", args[1], args[2], NULL);
        } else if (args[1] != NULL) {
            execl("/bin/ls", "ls", args[1], NULL);
        } else {
            execl("/bin/ls", "ls", NULL);
        }
        perror("ls");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
    }
}

void handle_cat(char *args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (args[1] == NULL) {
fprintf(stderr, "cat: missing file operand\n");
exit(1);
}
execl("/bin/cat", "cat", args[1], NULL);
perror("cat");
exit(1);
} else {
// Parent process
wait(NULL);
}
}

void handle_date(char *args[]) {
pid_t pid = fork();
if (pid == 0) {
// Child process
execl("/bin/date", "date", NULL);
perror("date");
exit(1);
} else {
// Parent process
wait(NULL);
}
}

void handle_rm(char *args[]) {
pid_t pid = fork();
if (pid == 0) {
// Child process
if (args[1] == NULL) {
fprintf(stderr, "rm: missing operand\n");
exit(1);
}
execl("/bin/rm", "rm", args[1], NULL);
perror("rm");
exit(1);
} else {
// Parent process
wait(NULL);
}
}

void handle_mkdir(char *args[]) {
pid_t pid = fork();
if (pid == 0) {
// Child process
if (args[1] == NULL) {
fprintf(stderr, "mkdir: missing operand\n");
exit(1);
}
execl("/bin/mkdir", "mkdir", args[1], NULL);
perror("mkdir");
exit(1);
} else {
// Parent process
wait(NULL);
}
}




