/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:21:49 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/13 20:17:35 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_int;

void	set_err_free(t_data *d)
{

	d->error = 1;
	if (d->env)
	{
		free (d->env);
		d->env = NULL;
	}
	
}

void	init_d_env(t_data **d, char **envp)
{
	*d = (t_data *) ft_calloc(1, sizeof(t_data));
	if (*d == NULL)
		return ;
	init_null(*d);
	(*d)->env = (t_envlist **)ft_calloc(1, sizeof(t_envlist *));
	if ((*d)->env == NULL)
		return ;
	*((*d)->env) = (t_envlist *)ft_calloc(1, sizeof(t_envlist));
	if ((*((*d)->env)) == NULL)
	{
		free((*d)->env);
		(*d)->env = NULL;
		return ;
	}
	init_envlist((*d)->env);
	(*d)->envp = envp;
	if (ft_assign_key_and_value((*d)->env, envp) != 0)
	{
		set_err_free(*d);
		return ;
	}
	(*d)->exit_code = 0;
	g_signal_int = 0;
	signal_setup(*d, MODE_DF);
}

void	clean_shell(t_data *d)
{
	if (g_signal_int == 130)
		d->exit_code = 130;
	g_signal_int = 0;
	free_n_clean(d, 0);
	init_null(d);
}

void	parsing_error(t_data *d)
{
	if (d->error > 1)
		ft_putstr_fd("syntax ", 2);
	if (d->error != 0)
	{
		ft_putstr_fd("error", 2);
		ft_putstr_fd("\n", 2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	if (argc != 1 || *envp == NULL || ft_strcmp(envp[0], "") == 0
		|| raise_shlvl(envp) != 0)
		exit (42);
	d = NULL;
	(void) argv;
	init_d_env(&d, envp);
	if (!d || !d->env || !*(d->env) || d->error != 0)
	{
		free_n_clean(d, 1);
		return (1);
	}
	while (1)
	{
		inputparsing(d);
		parsing_error(d);
		if (d->com && d->error == 0)
			executor2(d);
		clean_shell(d);
	}
	free_n_clean(d, 1);
	return (0);
}
