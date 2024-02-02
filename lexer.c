#include "minishell.h"

char	**split_data(t_data *d)
{
	char	**matrix;
	// int	i; //testing purposes

	// i = 0;

	matrix = ft_split(d->input, ' ');
	if (matrix == NULL)
	{
		d->error = ERR_LEX_ALL;
		return (NULL);
	}
	// while (matrix && matrix[i]) //testing purposes
	// {
	// 	printf("test: %s\n", matrix[i]);
	// 	i++;
	// }

	// d_split = split_split(d_split);
	return (matrix);
}




	// find | < << > >> outside of quotes that are not alone-standing
		// done: ls| grep a
		// todo: ls |grep a
		// todo echo "he | he" | grep a
void	separate_pipe(t_data *d, t_tok *current)
{
	// int	i;
	char	*str;

	// i=0;
	if (ft_strchr(current->tok, '|') != NULL && ft_strlen(current->tok) > 1)
	{
		str = ft_strchr(current->tok, '|');
		if (current->tok[0] == '|') //if: pipe is the first char of a string
		{
			lex_lstsqueezein(current, &str[1]);
			current->tok[1] = 0;
		}
		// else if (str[1]) //if: there's something more directly after |
		// {
		// 	lex_lstsqueezein(current, &str[1]);
		// 	lex_lstsqueezein(current, "|");
		// }
		else
		{
			lex_lstsqueezein(current, str);
			str[0] = 0;

		}
		// printf("strchr: %s\n", ft_strchr(current->tok, '|'));
		// printf("list new: %s\n", current->next->tok);
		// printf("list after new: %s\n", current->next->next->tok);
	}
	(void)d;
	return;
}




void	quote_merge(t_data *d)
{
	t_tok	*current;
	int	i;
	int	quote;
	
	i = 0;
	quote = 0;
	current = d->node;
	while (current && current->tok)
	{
		if (quote == 0 && current->tok[i] == 0)
		{
			current = current->next;
			i = 0;
			continue;
		}
		else if (quote == 0 && (current->tok[i] == SGLQUOTE || current->tok[i] == DBLQUOTE))
			quote = current->tok[i];
		else if (quote != 0 && (current->tok[i] == quote))
			quote = 0;
		else if (quote != 0 && (current->tok[i] == 0))
		{// append and remove next node
			current->tok = lex_strjoin(current->tok, current->next->tok, ' '); //careful of strjoin leaks
			lex_lst_rmone(current);
			continue;
		}
		i++;
	}
}

void	split_list(t_data *d)
{
	t_tok	*current;

	current = d->node;
	while (current && current->tok)
	{
		// printf("current: %s\n", current->tok);
		if (current->typ != SGLQUOTE && current->typ != DBLQUOTE)
			separate_pipe(d, current);
		current = current->next;
	}
	lst_print(d->node);



	// todo: find quotes and piece them into one node
	// quote_merge(d);
	// lst_print(d->node);
}

void	lexer(t_data *d)
{
	char	**matrix;
	
	matrix = split_data(d);
	if (matrix == NULL)
		return ;
	init_list(d, matrix);
	if (d->error != 0)
		return ;
	quote_merge_2(d); //WIP HERE
	split_list(d);

}



// check for unclosed quotes, error if odd number
// doesn't consider quotes of other type after opened quote
int even_quotes(t_data *d)
{
	int	i;
	char	quote;

	i=0;
	quote = 0;
	while (d && d->input && d->input[i])
	{
		if (quote == 0 && (d->input[i] == SGLQUOTE || d->input[i] == DBLQUOTE))
		{
			quote = d->input[i];
		}
		else if (d->input[i] == quote)
		{
			quote = 0;
		}
		i++;
	}
	if (quote == 0)
		return (EVEN);
	else
		return (ODD);
}
