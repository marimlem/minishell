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
void	com_lst_del(t_com *lst)
{
	t_com	*c;
	int	i;

	i = 0;
	c = lst;
	if (c)
	{
		com_lst_del(c->next);
		if (c->file)
			free (c->file);
		c->file = NULL;
		if (c->args)
		{
			while (c->args[i])
			{
				free (c->args[i]);
				c->args[i++] = NULL;
			}
			free (c->args);
			c->args = NULL;
		}
		i = 0;
		if (c->rdr)
		{
			while (c->rdr[i])
			{
				free (c->rdr[i]);
				c->rdr[i++] = NULL;
			}
			free (c->rdr);
			c->rdr = NULL;
		}
		c->next = NULL;
		free (c);

	}

}

void	free_n_clean(t_data *d, int b)
{
	lex_lst_del(d->node);
	com_lst_del(d->com);
	
	if (d->input)
		free (d->input);
	// if (d->node)
		// free (d->node);
	// if (d->com)
		// free (d->com);
	if (d->tmp)
		free (d->tmp);
	d->error = 0;
	d->i = 0;
	d->q = 0;
	if (b == 0)
		return ;
	if (d)
		free (d);
	d = NULL;
}

void	init_null(t_data *d)
{
	d->input = NULL;
	d->node = NULL;
	d->com = NULL;
	d->tmp = NULL;
	d->var_node = NULL;
	d->i = 0;
	d->q = 0;
	d->error = 0;
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
	while (1)
	{
		init_null(d);
		inputparsing(d);
		if (d->error == -1)
		{
			printf("exit minishell\n");
			break ;
		}
		if (d->error != 0)
			printf("Error (%d)\n", d->error);
		// if list is completely variable assignment type, assign variables, else go to executor
		//executor(d);
		
		free_n_clean(d, 0);
		printf("\n");

	}
	if (d->var_node)
		free (d->var_node);
	d->var_node = NULL;
	free_n_clean(d, 1);
	(void) argv;
	// (void) command;
	return (0);
}