#include "minishell.h"

void	parser(t_data *d)
{
	p_op_type(d);
	if (d->error != 0)
		return ;
	p_syn_check(d);
	if (d->error != 0)
		return ;
	init_com(d);
	fill_com(d, d->node, d->com);
	(void) d;
	return ;
}