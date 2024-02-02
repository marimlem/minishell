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
	t_data	*d;

	if (argc != 1)
		return (100);
	d = (t_data *) malloc(sizeof(t_data) * 1);
	if (d == NULL)
		return 1;
	d->input = NULL;
	d->node = NULL;
	d->i = 0;
	d->q = 0;
	while (1)
	{
		inputparsing(d);
		//executor(d);

	}

	(void) argv;
	// (void) command;
	return (0);
}