#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	// char *command;
	t_cmd	*cmd;

	if (argc != 1)
		return (100);
	cmd = (t_cmd *) malloc(sizeof(t_cmd) * 1);
	if (cmd == NULL)
		return 1;
	cmd->input = NULL;
	cmd->node = NULL;
	cmd->i = 0;
	cmd->q = 0;
	while (1)
	{
		inputparsing(cmd);
		//executor(cmd);

	}

	(void) argv;
	// (void) command;
	return (0);
}