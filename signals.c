#include "minishell.h"

void	sig_c(int sig)
{
	(void) sig;
	while (g_sig_int == 1)
		pause();
	if (g_sig_int == 0)
	{
		g_sig_int = 1;
		write (2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_replace_line("", 0);
		rl_redisplay();
		g_sig_int = 0;
	}
	return ;
}