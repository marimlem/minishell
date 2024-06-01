#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, sighandler);
		if (g_signal_int == 2)
		{
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
			g_signal_int = 130;
			rl_replace_line("", 0);
			rl_on_new_line();	
			return ;
		}
		else
		{
			ft_putchar_fd('\n', 2);
			// g_signal_int = 1;
			g_signal_int = 130;

			rl_replace_line("", 0);
			rl_on_new_line();	
			rl_redisplay();
		}
	}
	(void) signum;
	return ;
}

void	sigquithandler(int signum)
{
	(void) signum;
	exit (131);

}



void	signal_setup(t_data *d, int modus)
{
	(void) d;
	
	if (modus == MODE_IN)
	{
		signal(SIGINT, sighandler);
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
		// signal(SIGQUIT, SIG_DFL);
		signal(SIGQUIT, sigquithandler);

	}

}
