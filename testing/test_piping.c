#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



int main(void) {
	pid_t pid;
	int	fd2[2];
	int	fd1[2];

	if (pipe(fd1) == -1)
		return 2;
	if (pipe(fd2) == -1)
		return 2;
	pid = fork();
	if (pid == -1) {
       // Error handling for fork failure
	}
	else if (pid == 0) {
    	// We are the child
    	char *file = "/bin/echo";
    	char *const args[] = {"/bin/echo", "~/42/minishell", NULL};
		char *const env[] = {NULL};


		close (fd1[1]);
		dup2(fd1[1], 1);
		execve(file, args, env);

       // execve only returns on error
		_exit(2);
	} else {
       // We are the parent
    	char *file1 = "/bin/ls";
    	char **args1;
		char *const env1[] = {NULL};
		int status;
		char	getstring[1000];

		dup2(fd1[1], 0);
		args1 = (char **) malloc(sizeof(char*) * 3);
		if (args1 ==NULL)
			return (2); // error
		args1[0] = strdup(file1);
		if (args1[0] == NULL)
			return 2; //error
		args1[2] = NULL;
		close (fd1[0]);
		close (fd1[1]);
		waitpid(pid, &status, 0);
		close (fd2[1]);
		read(fd2[0], getstring, 1000);
		args1[1] = strdup(getstring);
		if (args1[1] == NULL)
			return 2; //error
		printf("test: %s\ntest: %s", getstring, args1[1]);
		// execve(file1, args1, env1);
		close (fd2[0]);

	}

	return 0;
}