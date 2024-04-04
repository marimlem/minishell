#include "minishell.h"

t_com	*com_lstnew()
{
	t_com *list;

	list = (t_com *) malloc(sizeof(t_tok) * 1);
	if (list == NULL)
		return (NULL); // set error
	list->file = NULL;
	list->args = NULL;
	list->rdr = NULL;
	list->next = NULL;
	return (list);	
}

void	com_lstsqueezein(t_com **current)
{
	t_com	*new;
	
	new = com_lstnew();
	if (new == NULL)
		return ;
	new->next = (*current)->next;
	(*current)->next = new;
	return ;
}

void	init_com(t_data *d)
{
	d->com = com_lstnew();
	if (d->com == NULL)
	{
		d->error = ERR_PAR_ALL;
		return ;
	}
	
}

void	fill_com(t_data *d, t_tok *t_node, t_com *c_node)
{
	t_tok	*current;
	t_com	*c_cur;
	int		rdr_c;
	int		r;
	int		arg_c;
	int		a;

	current = t_node;
	c_cur = c_node;
	
	rdr_c = 0;
	arg_c = 0;
	a = 0;
	r = 0;

	// count the args and rdrs until pipe
	while (current && current->typ != '|' * (-1))
	{
		if (current->typ == VAR)
		{
			arg_c++;
			current = current->next;
		}
		else if (current->typ < 0) // this also affects variable assignments
		{
			rdr_c++;
			if (current->next)
				current = current->next->next;
			else
			{
				d->error = 21; // nothing following a rdr
				return ;
			}
		}
		else
		{
			arg_c++;
			current = current->next;
		}
	}
	current = t_node;

/* 	if (arg_c == 0) // actually not needed :(
	{
		d->error = 1; // set some useful error for not enough arguments / no command found
		return ;
	} */
	// alloc space in com_current
	if (rdr_c != 0)
	{
		c_cur->rdr = (char **) ft_calloc((rdr_c * 2) + 1, sizeof(char *));
		if (c_cur->rdr == NULL)
		{
			d->error = ERR_PAR_ALL;
			return ;
		}
	}
	c_cur->args = (char **) ft_calloc(arg_c + 1, sizeof(char *));
	if (c_cur->args == NULL)
	{
		d->error = ERR_PAR_ALL;
		return ;
	}


	// ignore variable assignments before other types
	while (current && current->tok && current->typ == VAR)
		current = current->next;

	// fill in
	while (current && current->tok)
	{
		if (current->typ == PIPE * (-1))
		{
			// connect new node to command
			// and call this function again? and then return
			com_lstsqueezein(&c_cur);
			fill_com(d, current->next, c_cur->next);
			return ;
		}
		else if (current->typ < 0 && current->typ != VAR)
		{
			// alloc and append to rdr matrix
			c_cur->rdr[r] = ft_strdup(current->tok);
			if (c_cur->rdr[r++] == NULL)
			{
				d->error = ERR_PAR_ALL;
				return ;
			}
			c_cur->rdr[r] =  l_to_p_trans(d, current->next->tok);
			if (c_cur->rdr[r] == NULL)
			{
				d->error = ERR_PAR_ALL;
				return ;
			}
			r++;
			current = current->next->next;
		}
		else if (current->typ > 0 || current->typ == VAR) 
		{
			// if file is NULL then strdup to it
			// append string to args matrix
			if (a == 0)
			{
				c_cur->file = l_to_p_trans(d, current->tok);
				// c_cur->file = ft_strdup(current->tok);
				if (c_cur->file == NULL)
				{
					d->error = ERR_PAR_ALL;
					return ;
				}
			}
			c_cur->args[a] = l_to_p_trans(d, current->tok);
			// c_cur->args[a] = ft_strdup(current->tok);
			if (c_cur->args[a] == NULL)
			{
				d->error = ERR_PAR_ALL;
				return ;
			}
			a++;
			current = current->next;
		}
	}
}
