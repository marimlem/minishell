/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:22:19 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/19 15:08:54 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighdhandler(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, sighdhandler);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_signal_int = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		return ;
	}
	(void) signum;
	return ;
}

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, sighandler);
		ft_putchar_fd('\n', 2);
		g_signal_int = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void) signum;
	return ;
}

void	signal_setup(t_data *d, int modus)
{
	(void) d;
	if (modus == MODE_IN)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (modus == MODE_HD)
	{
		signal(SIGINT, sighdhandler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (modus == MODE_IG)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (modus == MODE_DF)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

int	hd_sig_int(t_data *d, char *heredoc_input, int fd)
{
	if (g_signal_int != 130)
		return (0);
	if (heredoc_input)
		free(heredoc_input);
	d->exit_code = 130;
	if (fd >= 0)
		close (fd);
	return (1);
}
