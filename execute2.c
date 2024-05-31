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

	if (current->builtin == 1)
	{
		execute_builtin(d, current, 0);
		free_n_clean(d, 1);
		exit(0) ;
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

void	execute_builtin(t_data *d, t_com *current, int ec)
{
		if (current->args[1] != NULL)
			ec = ft_atoi(current->args[1]);
		if (is_builtin(d, current) == 1) //echo
			ft_echo(d, current);
		else if (is_builtin(d, current) == 2) //cd
			ft_cd(d, current);
		else if (is_builtin(d, current) == 3) //pwd
		{
			if (!current->args[1])
				ft_pwd();
			else
			{
				if (ft_check_arg_for_pwd(current->args[1]) == 0)
					ft_pwd();
			}
		}
		else if (is_builtin(d, current) == 4) //export
		{
			if (current->args[1])
			{
				if (ft_check_arg_for_export(*d->env, current->args[1]) == 0)
					ft_export(d->env, current->args);
			}
			else
				ft_print_export(*d->env);
		}
		else if (is_builtin(d, current) == 5) //unset
		{
			if (current->args[1])
				if (ft_check_arg_for_unset(current->args[1]) == 0)
					ft_unset(d->env, current->args);
		}
		else if (is_builtin(d, current) == 6) //env
			ft_print_list(*d->env);
		else if (is_builtin(d, current) == 7) //exit
		{
			ft_putstr_fd("exit minishell\n", STDOUT_FILENO);
			if (current->args[1] == NULL)
				ec = ft_atoi(current->args[1]);
			else if (current->args[1] != NULL && current->args[2] != NULL)
			{
				ft_putstr_fd("exit: too many arguments\n", 2);
				return ;
			}
			else
			{
				if (ft_isdigit(current->args[1][0]) == 0) 
				{
					ft_putstr_fd("exit: ", 2);
					ft_putstr_fd((char *)current->args[1], 2);
					ft_putstr_fd(": numeric argument required\n", 2);
					return ;
				}
				else
					ec = ft_atoi(current->args[1]);

			}
			free_n_clean(d, 1);
			exit(ec) ;
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
	if (pc == 0 && current->builtin == 1)
	{
		execute_builtin(d, current, ec);
		return ;
	}


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
		close_rdr(d);
		i++;
		current = current->next;
	}
	current = d->com;
	while (current)
	{
		waitpid(current->pid, &(current->status), 0); 
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
		current->builtin = 0;
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
		else if (((is_builtin(d, current)) >= 1 && (is_builtin(d, current)) <= 8))
		{
			current->builtin = 1;
		}
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



