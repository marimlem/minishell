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
	if (last < -10) //what about var
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
				// expander(d, current);
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
		else if (current->typ > 0)
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


// returns (1) if NOT all var
int	is_all_var(t_data *d)
{
	t_tok *current;

	current = d->node;
	while (current && current->typ == VAR)
	{
		current = current->next;
	}
	if (current)
		return (1);
	return (0);
}

void	assign_var(t_data *d)
{
	int		i;
	t_tok	*tok_c;
	t_var	*var_c;

	i = 0;
	tok_c = d->node;
	d->var_node = (t_var *) malloc(sizeof(t_var) * 1);
	if (d->var_node == NULL)
	{
		d->error = 1; // alloc error
		return ;
	}
	var_c = d->var_node;
	var_c->key = NULL;
	var_c->val = NULL;
	var_c->next = NULL;
	while (tok_c)
	{
		var_c->key = ft_strdup(tok_c->tok);
		if (var_c->key == NULL)
		{
			d->error = 1;// alloc error
			return ;
		}
		while (tok_c->tok && tok_c->tok[i] != '=')
			i++;
		if (tok_c->tok[i] != '=')
		{
			d->error = 2; //strange error, there should in all cases be an equal sign somewhere in the tok, but anyways, safe is safe
			return ;
		}
		var_c->key[i] = 0;
		if (tok_c->tok[i] && tok_c->tok[i + 1])
			// var_c->val = ft_strdup(&tok_c->tok[i + 1]); // strdup not good enough, need to expand :(
			var_c->val = l_to_p_trans(d, &tok_c->tok[i+1]);
		else
			var_c->val = (char *) ft_calloc(sizeof(char), 1);
		if (var_c->val == NULL)
		{
			d->error = 1; // alloc error
			return ;
		}
		// have to add new node in varnode list here
		tok_c = tok_c->next;
		i = 0;

	}
	return ;
}

void	rm_var(t_data *d)
{
	t_tok	*current;
	t_tok	*last;

	current = d->node;
	last = NULL;
	while (current)
	{
		if (current->typ == VAR)
		{
			if (last == NULL) // if VAR is first token
			{
				free (current->tok);
				current->tok = NULL;
				current = current->next;
				if (current == NULL)
					return ;
				d->node = current;
			}
			else
			{
				last->next = current->next;
				free (current->tok);
				current->tok = NULL;
				current = last->next;
			}
		}
		else
		{
			last = current;
			current = current->next;
		}
	}
}

void	parser(t_data *d)
{
	int	o = 0;
	t_com	*c_cur;
	t_var	*varnode;

	p_op_type(d);
	if (d->error != 0)
		return ;
	p_var(d);
	// if list is completely variable assignment, create variable list, return
	lst_print(d->node);
	if (is_all_var(d) == 0)
	{
		assign_var(d);
		varnode = d->var_node;
		while (varnode && varnode->key && varnode->val)
		{
			printf("key: %s\nval: %s\n", varnode->key, varnode->val);
			varnode = varnode->next;
		}
		return ;
	}		
	else // remove variable assignments from tokenlist
	{
		rm_var(d);
	}

	p_syn_check(d);
	if (d->error != 0)
		return ;
	
	

//	p_quote_exp(d);
	// lst_print(d->node);

	init_com(d);
	fill_com(d, d->node, d->com);


// prints command list
	c_cur = d->com;
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
	}



	(void) d;
	return ;
}