#include "minishell.h"

void	sig_c(int sig)
{
	(void) sig;
	write (2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	// rl_replace_line("", 0);
	rl_redisplay();
	return ;
}