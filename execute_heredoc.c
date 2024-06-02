#include "minishell.h"

char	*heredoc_path(t_data *d)
{
	t_envlist *node;

	node = (*d->env);
	while (node)
	{
		if (ft_strcmp(node->key, "PWD") == 0)
		{
			return (ft_strjoin(node->value, "/minishell_heredoc_tmp"));
		}
		node = node->next;
	}
	return (NULL);
}

void	early_heredoc(t_data *d, t_com *current)
{
	int	j;
	char *heredoc_input;
	int	fd;


	if (!current->rdr)
		return ;
	heredoc_input = NULL;
	j = 0;
	while (current->rdr[j])
	{
		if (current->rdr[j][0] == '<' && current->rdr[j][1] == '<')
		{
			if (d->hd_path == NULL)
			{
				d->hd_path = heredoc_path(d);
				if (d->hd_path == NULL)
				{
					d->error = 1; // alloc error
					return ;
				}
			}
			fd = open(d->hd_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd < 0)
				return ;
			g_signal_int = 2;
			d->heredoc_fd = j;
			while (g_signal_int == 2)
			{
				signal_setup(d, MODE_IN);
				heredoc_input = readline("> ");
				if (g_signal_int == 130)
				{
					signal_setup(d, MODE_DF);
					d->exit_code = 130;
					if (fd >= 0)
						close (fd);
					return ;
				} 
				signal_setup(d, MODE_DF);
				if (!heredoc_input)
				{
					ft_putstr_fd("minishell: warning: here-document delimited by end-of-file instead of given delimiter\n", 2);
					break;
				}
				if (ft_strcmp(heredoc_input, current->rdr[j + 1]) == 0)
					break ;
				if (current->rdr[j][2] != SGLQUOTE)
				{
					heredoc_input = heredoc_expanding(d, heredoc_input);
					if (heredoc_input == NULL)
					{
						g_signal_int = 0;
						if (fd >= 0)
							close (fd);
						return ;
					}
				}
				ft_putstr_fd(heredoc_input, fd);
				ft_putchar_fd('\n', fd);
			}
			g_signal_int = 0;
			if (fd >= 0)
				close (fd);
		}
		j++;
		j++;
	}
}
