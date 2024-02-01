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




	// find | < << > >> outside of quotes that are not alone-standing
		// done: ls| grep a
		// todo: ls |grep a
		// todo echo "he | he" | grep a
void	separate_pipe(t_cmd *cmd, t_tok *current)
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
	(void)cmd;
	return;
}




void	quote_merge(t_cmd *cmd)
{
	t_tok	*current;
	int	i;
	int	quote;
	
	i = 0;
	quote = 0;
	current = cmd->node;
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

void	quote_merge_2(t_cmd *cmd)
{
	int	quote;
	t_tok	*current;
	int	i;


	i=0;
	quote = 0;

	current = cmd->node;
	while (current && current->tok)
	{
		if (quote == 0 && current->tok[i] == 0)
		{
			current = current->next;
			i = 0;
			continue;
		}
		else if (quote == 0 && (current->tok[i] == SGLQUOTE || current->tok[i] == DBLQUOTE))
		{
			quote = current->tok[i];
			if (i != 0 && current->tok[i-1] == '|') // if not the first character
			{
				lex_lstsqueezein(current, &current->tok[i+1]);
				current->tok[i] = 0;
				current = current->next;
				i = 0; 
				continue;
			}
			else if (i != 0) 
			{ // case: hello"world" => helloworld
				ft_memmove(&current->tok[i], &current->tok[i+1], ft_strlen(&current->tok[i+1]) + 1);
				// current->tok[ft_strlen(&current->tok[i+1]) + 1] = 0;
				current->typ = quote;
			}
			else if (i == 0)
			{
				current->tok = &current->tok[i+1];
			}
		}
		else if (quote != 0 && (current->tok[i] == quote))
		{
			current->typ = quote;
			quote = 0;
			if (current->tok[i + 1] != 0 && current->tok[i + 1] != '|')
			{
				ft_memmove(&current->tok[i], &current->tok[i+1], ft_strlen(&current->tok[i+1]) + 1);
				continue;
			}
			else if (current->tok[i + 1] != 0 && current->tok[i + 1] == '|')
			{
				lex_lstsqueezein(current, &current->tok[i+1]);
				current->tok[i] = 0;
				current = current->next;
				i = 0;
				continue;
			}

			current->tok[i] = 0;
		}
		else if (quote != 0 && (current->tok[i] == 0))
		{// append and remove next node
			current->tok = lex_strjoin(current->tok, current->next->tok, ' '); //careful of strjoin leaks
			lex_lst_rmone(current);
			continue;
		}
		i++;
	}

}

void	split_list(t_cmd *cmd)
{
	t_tok	*current;

	current = cmd->node;
	// lst_print(cmd->node);

	quote_merge_2(cmd);

	while (current && current->tok)
	{
		// printf("current: %s\n", current->tok);
		if (current->typ != SGLQUOTE && current->typ != DBLQUOTE)
			separate_pipe(cmd, current);
		current = current->next;
	}
	lst_print(cmd->node);



	// todo: find quotes and piece them into one node
	// quote_merge(cmd);
	// lst_print(cmd->node);
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
