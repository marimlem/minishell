#include "minishell.h"

char	**split_cmd(t_cmd *cmd)
{
	char	**matrix;
	// int	i; //testing purposes

	// i = 0;

	matrix = ft_split(cmd->input, ' ');
	if (matrix == NULL)
		return (NULL);
	// while (matrix && matrix[i]) //testing purposes
	// {
	// 	printf("test: %s\n", matrix[i]);
	// 	i++;
	// }

	// cmd_split = split_split(cmd_split);
	return (matrix);
}

void	lex_lstsqueezein(t_tok *current, char *str)
{
	t_tok	*new;
	
	new = lex_lstnew(str);
	new->next = current->next;
	current->next = new;
	return ;
}


	// find | < << > >> outside of quotes that are not alone-standing
		// e.g. ls| grep a
void	separate_pipe(t_cmd *cmd, t_tok *current)
{
	// int	i;
	char	*str;

	// i=0;
	if (ft_strchr(current->tok, '|') != NULL && ft_strlen(current->tok) > 1)
	{
		str = ft_strchr(current->tok, '|');
		lex_lstsqueezein(current, str);
		str[0] = 0;
		// printf("strchr: %s\n", ft_strchr(current->tok, '|'));
		// printf("list new: %s\n", current->next->tok);
		// printf("list after new: %s\n", current->next->next->tok);
	}
	(void)cmd;
	return;
}



void	split_list(t_cmd *cmd)
{
	t_tok	*current;

	current = cmd->node;
	// lst_print(cmd->node);
	while (current && current->tok)
	{
		// printf("current: %s\n", current->tok);
		separate_pipe(cmd, current);
		current = current->next;
	}
	// lst_print(cmd->node);



	// todo: find quotes and piece them into one node
}

void	lexer(t_cmd *cmd)
{
	char	**matrix;
	
	matrix = split_cmd(cmd);
	init_list(cmd, matrix);
	split_list(cmd); //WIP HERE
}



// check for unclosed quotes, error if odd number
// doesn't consider quotes of other type after opened quote
int even_quotes(t_cmd *cmd)
{
	int	i;
	char	quote;

	i=0;
	quote = 0;
	while (cmd && cmd->input && cmd->input[i])
	{
		if (quote == 0 && (cmd->input[i] == SGLQUOTE || cmd->input[i] == DBLQUOTE))
		{
			quote = cmd->input[i];
		}
		else if (cmd->input[i] == quote)
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
