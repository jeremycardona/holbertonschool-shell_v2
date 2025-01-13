#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int status;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

	for (int i = 0; i < 5; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			// Child process
			if (execve(argv[0], argv, NULL) == -1) {
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else {
			// Parent process
			if (wait(&status) == -1) {
				perror("wait");
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}