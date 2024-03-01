#include "minishell.h"

// finds variable in variable list
// returns (1) on success
int	is_variable(char *tok, t_var *node)
{
	int	i;

	i=0;
	i++;
	if (node == NULL || node->key == NULL)
		return (0);
	else
	{
		if (is_variable(tok, node->next) != 0)
			return (1);

		if (ft_strncmp(node->key, tok, ft_strlen(node->key)) != 0) // strncmp lacking protection
			return (0);
		else
			return (1);
	}
	return (0);
//	return (is_variable(tok, node->next))
}


void	expand_var()
{
	return ;
}

void 	expand_empty(t_data *d, char *new)
{
	int	i;


	i = 0;
	while (new[i] || lex_is_separator(new[i]) == 0 || (new[i] == SGLQUOTE || new[i] == DBLQUOTE))
	{
		i++;
	}
	if (new[i])
		memmove(&d->tmp[d->i], &new[i], ft_strlen(&new[i]) + 1);
	else
		d->tmp[d->i] = 0;

	(void) d;
	return ;
}

void 	expand_shellpid()
{
	return ;
}

void 	expand_env()
{
	return ;
}

int	is_env()
{
	return (0);
}

void	expander(t_data *d, t_tok *current, char *new)
{
	// printf("\ntest: %s\n", d->tmp);
	(void) current;
// expanding here
	if (new[d->i + 1] == '$')
		expand_shellpid();
	else if (is_variable(&new[d->i + 1], d->var_node) == 1)
		expand_var();
	else if (is_env())
		expand_env();
	else
		expand_empty(d, new);
}

char	*l_to_p_trans(t_data *d, t_tok *current)
{
	char	*new;

	d->i = 0;
	d->q = 0;
	new = ft_strdup(current->tok);
	if (new == NULL)
	{
		d->error = ERR_EXP_ALL;
		return (NULL);
	}
	while (new && new[d->i])
	{
		if (d->q == 0 && (new[d->i] == DBLQUOTE || new[d->i] == SGLQUOTE))
		{
			d->q = new[d->i];
			memmove(&new[d->i], &new[d->i+1], ft_strlen(&new[d->i+1]) + 1);
			new[ft_strlen(new)] = 0;
			continue ;
		}
		else if(d->q != 0 && d->q == new[d->i]) // doubles up here
		{
			d->q = 0;
			memmove(&new[d->i], &new[d->i+1], ft_strlen(&new[d->i+1]));
			new[ft_strlen(new) - 1] = 0;
			continue ;
		}
		else if ((d->q == 0 || d->q == DBLQUOTE) && new[d->i] == '$')
		{
			d->tmp = &new[d->i];
			// printf("\ntest: %s\n", d->tmp);
			expander(d, current, &new[d->i]);
			continue ; 
		}
		d->i++;	
		
	}
	
	return (new);

}