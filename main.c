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
void	lex_lst_del(t_tok *lst)
{
	t_tok	*c;

	c = lst;
	if (c)
	{
		lex_lst_del(c->next);
		if (c->tok)
			free (c->tok); //invalid free
		c->next = NULL;
		free (c);
	}

}

void	free_n_clean(t_data *d, int b)
{
	lex_lst_del(d->node);
	if (d->input)
		free (d->input);
	d->error = 0;
	d->i = 0;
	d->q = 0;
	if (b == 0)
		return ;
	if (d)
		free (d);
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
	d->var_node = NULL;
	d->i = 0;
	d->q = 0;
	d->error = 0;
	while (1)
	{
		inputparsing(d);
		if (d->error != 0)
			printf("Error (%d)\n", d->error);
		// if list is completely variable assignment type, assign variables, else go to executor
		//executor(d);
		free_n_clean(d, 0);
	}
	free_n_clean(d, 1);
	(void) argv;
	// (void) command;
	return (0);
}