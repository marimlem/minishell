#include "minishell.h"

void	parser(t_data *d)
{
	// int	o = 0;
	// t_com	*c_cur;
	// t_var	*varnode;

	p_op_type(d);
	if (d->error != 0)
		return ;
	// p_var(d);
	// if list is completely variable assignment, create variable list, return
	// lst_print(d->node);
	// if (is_all_var(d) == 0)
	// {
	// 	assign_var(&d);
	// 	if (d->error)
	// 		return ;
	// 	varnode = d->var_node;
	// 	while (varnode && varnode->key && varnode->val)
	// 	{
	// 		printf("key: %s\nval: %s\n", varnode->key, varnode->val);
	// 		varnode = varnode->next;
	// 	}
	// 	return ;
	// }		
/* 	else // remove variable assignments from tokenlist
	{
		rm_var(d);
	} */

	p_syn_check(d);
	if (d->error != 0)
		return ;

	// lst_print(d->node);

	init_com(d);
	fill_com(d, d->node, d->com);


// prints command list
/* 	c_cur = d->com;
	while (c_cur && c_cur->args)
	{
		printf("   file:%s\n", c_cur->file);
		while (c_cur->args[o])
		{
			printf("   arg:%s\n", c_cur->args[o]);
			o++;
		}
		o = 0;
		while (c_cur->rdr && c_cur->rdr[o])
		{
			printf("   rdr:%s\n", c_cur->rdr[o]);
			o++;
		}
		c_cur = c_cur->next;
		o= 0;
	} */



	(void) d;
	return ;
}