#include "minishell.h"


// finds and marks operator tokens
// pipe = -124; rdr left = -60; rdr right = -62
void	p_op_type(t_data *d)
{
	t_tok	*current;
	int		t;

	current = d->node;
	t=1;
	d->i = 0;
	while (current && current->tok)
	{
		if ((current->tok[0] == '>' || current->tok[0] == '<' || current->tok[0] == '|'))
		{
			if (ft_strlen(current->tok) > 2)
			{
				d->error = ERR_PAR_SYN;
				return ;
			}
			else if ((current->tok[1] && current->tok[0] == '|') || (current->tok[1] && current->tok[0] != current->tok[1]))
			{
				d->error = ERR_PAR_SYN;
				return ;
			}
			else if (ft_strlen(current->tok) == 1 || (current->tok[1] && current->tok[0] == current->tok[1]))
			{
				if (current->tok[0] == '|')
					t = 1;
				current->typ = current->tok[0] * (-1);
				current = current->next;
				continue ;
			}
		}
		else
		{
			current->typ = t;
			t++;
		}
		current = current->next;
	}
}


// finds and marks proper variable assignment tokens
void	p_var(t_data *d)
{
	t_tok *current;

	current = d->node;
	d->i = 0;
	while (current && current->tok)
	{
		d->i = 0;
		if (current->typ == OP)
		{
			current = current->next;
			continue ;
		}
		while (current->tok[d->i])
		{
			if (current->tok[d->i] == SGLQUOTE || current->tok[d->i] == DBLQUOTE)
				break ;
			if (current->tok[d->i] == '=')
			{
				current->typ = VAR;
				break ;
			}
			d->i++;
		}
		current = current->next;
	}
}

// checks if operators are in syntactically good order (not first, not last, not two in a row)
// pipe cant be first or last
// before a pipe, no other operator can be there ( > |  or | |)
// two in a row check rdr except pipe followed by rdr; rdr must be followed by normal type token
// last token cant be an operator
void	p_syn_check(t_data *d)
{
	t_tok *current;
	int	t;
	int	last;

	t = 0;
	last = 0;
	current = d->node;
	while (current && current->tok)
	{
		if (t == 0 && current->typ == '|' * (-1))
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		else if (current->typ == '|' * (-1) && last < -20)
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		else if ((current->typ == '>' * (-1) || current->typ == '<' * (-1)) && (last == '>' * (-1) || last == '<' * (-1)))
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		last = current->typ;
		t++;
		current = current->next;
	}
	if (last == OP)
		d->error = ERR_PAR_SYN;
}




// quote handler and expander
void	p_quote_exp(t_data *d)
{
	t_tok *current;
	int	q;
//	char	*new;

	q = 0;
	d->i = 0;
	current = d->node;
	while (current && current->tok)
	{
		while (current->tok[d->i])
		{
			if (q == 0 && (current->tok[d->i] == SGLQUOTE || current->tok[d->i] == DBLQUOTE))
				q = current->tok[d->i];
			if (q != 0 && current->tok[d->i] == q)
				q = 0;
			if (q != SGLQUOTE && current->tok[d->i] == '$')
			{
				expander(d, current);
				printf("***expander triggered***\n");

			}
			
			d->i++;
		}
		current = current->next;
		d->i = 0;
	}

}
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
		if (current->typ < 0)
		{
			rdr_c++;
			current = current->next->next;
		}
		else
		{
			arg_c++;
			current = current->next;
		}
	}
	current = t_node;

	if (arg_c == 0)
	{
		d->error = 1; // set some useful error for not enough arguments / no command found
		return ;
	}
	// alloc space in com_current
	if (rdr_c != 0)
	{
		c_cur->rdr = (char **) ft_calloc(rdr_c + 1, sizeof(char *));
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
		else if (current->typ < 0)
		{
			// alloc and append to rdr matrix
			c_cur->rdr[r] = ft_strjoin(current->tok, current->next->tok);
			if (c_cur->rdr[r] == NULL)
			{
				d->error = ERR_PAR_ALL;
				return ;
			}
			r++;
			current = current->next->next;
		}
		else if (current->typ > 0)
		{
			// if file is NULL then strdup to it
			// append string to args matrix
			if (a == 0)
			{
				c_cur->file = ft_strdup(current->tok);
				if (c_cur->file == NULL)
				{
					d->error = ERR_PAR_ALL;
					return ;
				}
			}
			c_cur->args[a] = ft_strdup(current->tok);
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

void	parser(t_data *d)
{
	int	o = 0;
	t_com *c_cur;

	p_op_type(d);
	if (d->error != 0)
		return ;
	p_var(d);
	// if list is completely variable assignment, return

	p_syn_check(d);
	if (d->error != 0)
		return ;
	
	
	//lst_print(d->node);

//	p_quote_exp(d);
	lst_print(d->node);

	init_com(d);
	fill_com(d, d->node, d->com);


// prints command list
	c_cur = d->com;
	while (c_cur && c_cur->args)
	{
		printf("\nfile:%s\n", c_cur->file);
		while (d->com->args[o])
		{
			printf("arg:%s\n", c_cur->args[o]);
			o++;
		}
		c_cur = c_cur->next;
		o= 0;
	}



	(void) d;
	return ;
}