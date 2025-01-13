#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    // Child process
        close(pipefd[1]);          // Close unused write end

        // Redirect stdin to read end of pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);          // Close the original read end

        // Execute the second command
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);

    } else {            // Parent process
        close(pipefd[0]);          // Close unused read end

        // Redirect stdout to write end of pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);          // Close the original write end

        // Execute the first command
        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Wait for child process to finish
    wait(NULL);

    return 0;
}