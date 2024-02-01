#include "minishell.h"


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
				current->typ = '|';
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
		else if (quote == 0 && (current->tok[i] == '<' || current->tok[i] == '>'))
		{ //should do smth here
			i++;
			continue;
		}
		i++;
	}

}
