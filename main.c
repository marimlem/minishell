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
	t_cmd	cmd;

	if (argc != 1)
		return (100);
	while (my_love_for_viktoria > 0)
	{
		inputparsing(&cmd);

	}
	(void) argv;
	// (void) command;
	return (0);
}