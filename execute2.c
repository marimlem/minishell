#include "minishell.h"



void	pipe_handler(t_data *d, int pc, int i)
{
	if (i != pc)
	{
		if (d->old_fd[OUT] < 0)
			dup2(d->p[i][1], STDOUT_FILENO);
		else
			dup2(d->p[i][1], d->old_fd[OUT]);
		close_pipes(d->p[i]);
	}
	if ( i != 0)
	{
		if (d->old_fd[IN] < 0)
			dup2(d->p[i-1][0], STDIN_FILENO);
		else
			dup2(d->p[i-1][0], d->old_fd[IN]);
		close_pipes(d->p[i-1]);
	}
}

//child handler
void	playground(t_data *d, t_com *current ,int pc, int i)
{

	if (current->rdr && rdr_handler(d, current) != 0)
	{
		// ft_putstr_fd("minishell: rdr failed\n", 2);
		free_n_clean(d, 1);
		exit (-1); // i think this might generate errors
	}
	if (pc != 0)
		pipe_handler(d, pc, i);

	if (ft_strcmp(current->args[0], "env") == 0 && current->args[1] == NULL)
	{
		ft_print_list(*(d->env));
		free_n_clean(d, 1);
		exit(0);
	}
	else if (ft_strcmp(current->args[0], "env") == 0 && current->args[1])
	{
		ft_putstr_fd("minishell: too many arguments for command: ", 2);
		ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		free_n_clean(d, 1);
		exit(-1);
	}
   	else if (execve(current->file, current->args, NULL) == -1)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		free_n_clean(d, 1);
		exit(-1);
	}
}

void	early_heredoc(t_data *d, t_com *current)
{
	int	j;
	char *heredoc_input;
	int	fd;

	// (void) d;
	if (!current->rdr)
		return ;
	heredoc_input = NULL;
		// return (j + 1);

	j = 0;
	while (current->rdr[j])
	{
		if (current->rdr[j][0] == '<' && current->rdr[j][1] == '<')
		{
			fd = open("/home/lknobloc/Documents/minishell/minishell_heredoc_tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return ;
			g_signal_int = 2;
			d->heredoc_fd = j;
			while (g_signal_int == 2)
			{
			//gnl
				/* ft_putstr_fd("> ", 2);
				heredoc_input = get_next_line(STDIN_FILENO);
				if (g_signal_int == 3)
				{
					if (fd >= 0)
						close (fd);
					return ;
				} 
				if (!heredoc_input)
				{
					ft_putstr_fd("\nminishell: warning: here-document delimited by end-of-file instead of given delimiter\n", 2);
					// ft_putchar_fd('\n', 2);
					break;
					// close (fd);
					// 
					// ft_putstr_fd("\nexit\n", 2);
					// free_n_clean(d, 1);
					// exit (-2);
					// break ; // control D should exit everything
				}
				if (strncmp(heredoc_input, current->rdr[j + 1], ft_strlen(current->rdr[j + 1])) == 0 && heredoc_input[ft_strlen(current->rdr[j + 1])] == '\n')
					break ;
				ft_putstr_fd(heredoc_input, fd); */
			//gnl end

			//readline
				// ft_putstr_fd("> ", 2);
				heredoc_input = readline(">");
				if (g_signal_int == 3)
				{
					if (fd >= 0)
						close (fd);
					return ;
				} 
				if (!heredoc_input)
				{
					ft_putstr_fd("\nminishell: warning: here-document delimited by end-of-file instead of given delimiter\n", 2);
					// ft_putchar_fd('\n', 2);
					break;
				}
				if (ft_strcmp(heredoc_input, current->rdr[j + 1]) == 0)
					break ;
				if (current->rdr[j][2] != SGLQUOTE)
				{
					heredoc_input = heredoc_expanding(d, heredoc_input);
					if (heredoc_input == NULL)
					{
						g_signal_int = 1;
						if (fd >= 0)
							close (fd);
						return ;
					}
				}
				ft_putstr_fd(heredoc_input, fd);
				ft_putchar_fd('\n', fd);
			// readline end
			}
			g_signal_int = 1;
			if (fd >= 0)
				close (fd);
		}
		j++;
		j++;
	}
}

void	process_handler(t_data *d, t_com *current, int pc, int i)
{
	int	ec;
	// char	*file;

	// file = ft_strjoin(BIN, current->file);
	// if (file == NULL)
	// 	return ;
	// free (current->file);
	// current->file = file;
	ec = 0;
	if (pc != 0 && i != pc)
		pipe(d->p[i]);

	//simple command without pipes
	if (pc == 0 && ft_strcmp(current->args[0], "exit") == 0)
	{
		if (current->args[1] != NULL)
			ec = ft_atoi(current->args[1]);
		free_n_clean(d, 1);
		exit(ec);
	}


	d->heredoc_fd = 0;
	early_heredoc(d, current);
	if (g_signal_int == 3)
		return ;

	current->pid = fork();
	if (current->pid < 0)
		return ; // fork fail
	else if(current->pid == 0)
	{
		playground(d, current, pc, i);
	}
	else
	{
		if (pc != 0 && i != 0)
			close_pipes(d->p[i - 1]);
	}

}

int	setup_path(t_data *d)
{
	t_envlist *current;

	current = *(d->env);
	while (current && ft_strcmp("PATH", current->key) != 0)
		current = current->next;
	if (current == NULL)
		return (0);
	d->path = ft_split(current->value, ':');
	if (d->path ==NULL)
	{
		// set alloc error
		return (-1);
	}
	return (0);
}

// pc == pipecount
void	execute_loop(t_data *d, int pc)
{
	t_com	*current;
	int	i;

	i = 0;
	current = d->com;
	while (current)
	{
		process_handler(d, current, pc, i);
		if (g_signal_int == 3)
			return ;
		close_rdr(d);
		i++;
		current = current->next;
	}
	current = d->com;
	while (current)
	{
		waitpid(current->pid, &(current->status), 0); 
		if (current->status == -2) // heredoc Control D experiment
		{
			ft_putstr_fd("exit\n", 1);
			free_n_clean(d, 1);
			exit (0);
		}
		d->exit_code = current->status;
		current = current->next;
	}


}
// user input: /usr/bin/ls
// keeps current->file the same, but removes path part from current->arg
int	absolut_path(t_data *d, t_com *current)
{
	char	*ptr;
	int	i;

	i = 1;
	free (current->args[0]);
	current->args[0] = NULL;
	ptr = ft_strrchr(current->file, '/');
	current->args[0] = ft_strdup(&ptr[1]);
	if (current->args[0] == NULL)
	{
		while (current->args[i])
		{
			free (current->args[i]);
			i++;
		}
		return (1);
	}
	// printf("file: %s args: %s\n",current->file, current->args[0]);
	(void) d;
	return (0);
}

int	no_path(t_data *d, t_com *current)
{
	char	*tmp;
	char	*t;
	int	i;
	//check if it is builtin
	//if not continue
	i = 0;
	tmp = NULL;
	// check in current directory? no i dont think so

	//check inside path
	while(current->file && d->path && d->path[i])
	{

		t = ft_strjoin(d->path[i], "/");
		tmp = ft_strjoin(t, current->file);
		free (t);
		t = NULL;
		// printf("tmp: %s\n", tmp);
		if (access(tmp , X_OK) == 0)
		{
			free (current->file);
			current->file = NULL;
			current->file = tmp;
			return (0);
		}
		free (tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}

int	relative_path(t_data *d, t_com *current)
{

	free (current->args[0]);
	current->args[0] = ft_strdup(&current->file[2]);
	if (current->args[0] == NULL)
		return (1); //alloc error
	free (current->file);
	current->file = current->args[0];
	if (current->file == NULL)
		return (1); //alloc error
	(void) d;
	return (0);
}

int	setup_cmdpath(t_data *d)
{
	t_com	*current;

	current = d->com;
	// printf("%s\n%s\n",d->path[0], d->path[1]);
	while (current)
	{
		if (current->file && current->file[0] == '/')
		{
			if (absolut_path(d, current) != 0) // input: /usr/bin/ls
				return (1); // alloc error

		}
		else if (current->file && current->file[0] == '.' && current->file[1] == '/')
		{
			relative_path(d, current); // input: ./minishell ../minishell

		}
		// ~/42/minishell
		else
		{
			no_path(d, current); // input: ls OR input: echo (builtin)
			// printf("file: %s\n", current->file);

		}
		current = current->next;

	}
	return (0);

}


void	executor2(t_data *d)
{
	int	count;

	if (setup_fds(d) != 0 || setup_path(d) != 0 || setup_cmdpath(d) != 0)
		return ; //alloc error
	count = d_lstsize(d->com);
	if (count > 0)
	{
		if (count > 1 && setup_pipes(d, count - 1) != 0)
			return ; // alloc error
		execute_loop(d, count - 1);
	}
}



