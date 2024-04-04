#include "minishell.h"


// int	is_varname()
// {
// 	int i;

// 	i = 0;
// 	if (ft_isdigit(var[i])) 
// 	{

// 	}
// }

// finds variable in variable list
// returns (1) on success
int	is_variable(t_var *node, char *find)
{
	if (node && node->key == NULL)
		return (0);
	if (is_variable(node->next, find) == 1)
		return (1);
	else
	{
		if (ft_strncmp(node->key, find, ft_strlen(node->key) + ft_strlen(find)) == 0)
			return (1);
		return (0);
	}
	
}


void	expand_var(t_data *d, char *new)
{
	(void) d;
	(void) new;
	return ;
}

void 	expand_empty(t_data *d, char *new)
{
	int	i;

	i = 1;
	if (new[i] && ft_isdigit(new[i]))
	{
		ft_memmove(&d->tmp[0], &new[i+1], ft_strlen(&new[i + 1]) + 1);
		return ;
	}
	while (new[i] && (ft_isdigit(new[i]) || ft_isalpha(new[i]) || new[i] == '_'))//(lex_is_separator(new[i]) == 0 || (new[i] == SGLQUOTE || new[i] == DBLQUOTE)))
	{
		i++;
	}
	if (new[i])
		ft_memmove(&d->tmp[0], &new[i], ft_strlen(&new[i]) + 1);
	else
		d->tmp[0] = 0;

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

void	expander(t_data *d, char *new)
{
	// printf("\ntest: %s\n", d->tmp);
	int	i;

	i = 0;
// expanding here
	if (!new[i + 1] || (!ft_isdigit(new[i + 1]) && !ft_isalpha(new[i + 1]) && new[i + 1] != '_'))
	{
		d->i++;
		return ;
	}
	// if (new[i + 1] == '$')
	// 	expand_shellpid();
	// else if (NULL) //is_variable(d->var_node, new) == 1)
	// 	expand_var(d, new);
	if (is_env())
		expand_env();
	else
		expand_empty(d, new);
}

char	*l_to_p_trans(t_data *d, char *token)
{
	char	*new;

	d->i = 0;
	d->q = 0;
	new = ft_strdup(token);
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
			expander(d, &new[d->i]);
			d->tmp = NULL;
			continue ; 
		}
		d->i++;	
		
	}
	
	return (new);

}