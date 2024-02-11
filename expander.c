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

void 	expand_empty()
{
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

void	expander(t_data *d, t_tok *current)
{
	// expanding here
	if (current->tok[d->i + 1] == '$')
		expand_shellpid();
	else if (is_variable(&current->tok[d->i + 1], d->var_node) == 1)
		expand_var();
	else if (is_env())
		expand_env();
	else
		expand_empty();

}