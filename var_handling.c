#include "minishell.h"

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

t_var	*var_lst_new()
{
	t_var *lst;

	lst = (t_var *) malloc(sizeof(t_var) * 1);
	if (lst == NULL)
		return (NULL);
	lst->key = NULL;
	lst->val = NULL;
	lst->next = NULL;
	return (lst);
}

void	assign_var(t_data **d)
{
	int		i;
	t_tok	*tok_c;
	t_var	*var_c;

	i = 0;
	tok_c = (*d)->node;
	var_c = (*d)->var_node;
	while (var_c && var_c->next)
		var_c = var_c->next;
	if (var_c)
		var_c->next = var_lst_new();
	else
	{
		(*d)->var_node = var_lst_new();
		var_c = (*d)->var_node;
	}
	
	if (var_c == NULL)
	{
		(*d)->error = 1; //alloc error
		return ;
	}
	while (tok_c)
	{
		var_c->key = ft_strdup(tok_c->tok);
		if (var_c->key == NULL)
		{
			(*d)->error = 1;// alloc error
			return ;
		}
		while (tok_c->tok && tok_c->tok[i] != '=')
			i++;
		if (tok_c->tok[i] != '=')
		{
			(*d)->error = 2; //strange error, there should in all cases be an equal sign somewhere in the tok, but anyways, safe is safe
			return ;
		}
		var_c->key[i] = 0;
		if (tok_c->tok[i] && tok_c->tok[i + 1])
			// var_c->val = ft_strdup(&tok_c->tok[i + 1]); // strdup not good enough, need to expand :(
			var_c->val = l_to_p_trans(*d, &tok_c->tok[i + 1], 1);
		else
			var_c->val = (char *) ft_calloc(sizeof(char), 1);
		if (var_c->val == NULL)
		{
			(*d)->error = 1; // alloc error
			return ;
		}
		// have to add new node in varnode list here
		var_c->next = var_lst_new();
		if (var_c->next == NULL)
		{
			(*d)->error = 1; //alloc error
			return ;
		}
		var_c = var_c->next;
		tok_c = tok_c->next;
		i = 0;

	}
	// (*d)->var_node = var_c;
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
