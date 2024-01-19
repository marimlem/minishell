#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/libft.h"



int main(void) {
	pid_t pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return 2;
	pid = fork();
	if (pid == -1) {
       // Error handling for fork failure
	}
	else if (pid == 0) {
    	// We are the child
		// printf("child\n");
		dup2(fd[1], 1);
		close (fd[0]);
		close (fd[1]);

		char *file = "/bin/echo";
    	// char *const args[] = {"/bin/echo", "~/42/minishell", NULL};
    	char *const args[] = {"/bin/echo", "/home/luca/42/minishell/testing", NULL};
		// char *const env[] = {NULL};


		execve(file, args, NULL);
	
		// execlp( "/usr/bin/echo", "echo", ":)", NULL );
		// write(1, "lol2", 5);
		_exit(2);
	} else {
       // We are the parent
		char	str[111];
		int		status;

		dup2(fd[0], 0);
		close (fd[0]);
		close (fd[1]);
		waitpid(pid, &status, 0);

		char	**args1;
		char	*file1 = "/bin/ls";

		args1 = (char **) malloc(sizeof(char*) * 3);
		if (args1 ==NULL)
			return (2); // error
		args1[0] = ft_strdup(file1);
		if (args1[0] == NULL)
			return 2; //error
		args1[2] = NULL;
		read(0, str, 111);
		printf("read: %s", str);
		args1[1] =ft_strdup(str);
		if (args1[1] ==NULL)
			return 2; //error
		write (1, args1[1], 111);

		int	i=0;
		while (args1[1][i])
		{
			printf("\n%d\n", args1[1][i]);
			write (1, &args1[1][i++], 1);
		}
		args1[1][i-1] = 0;
		// write(1, "end", 3);
		i=0;
		while (args1[i])
		{
			printf("%s*", args1[i]);
			i++;
		}
			
		execve(file1, args1, NULL);



		// execlp( "/usr/bin/wc", "wc", "-l", NULL );
		// read(fd[1], str, 111);
		// printf("parent: %s\n", str);
	}

	return 0;
}