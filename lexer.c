#include "minishell.h"

t_tok	*lex_lstnew(char *ptr)
{
	t_tok *list;

	list = (t_tok *) malloc(sizeof(t_tok) * 1);
	if (list == NULL)
		return (NULL); // set error
	list->tok = NULL;
	list->typ = 0;
	list->next = NULL;
	list->before = NULL;
	if (ptr == NULL)
		return (list);
	list->tok = ft_strdup(ptr);
	if (list->tok == NULL)
	{
		free (list);
		return (NULL);
	}
	return (list);
}

int	isnot_deli(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	
	return (0);
}

// char	**split_split(char **in);
// {
// 	int	i;
// 	int	j;

// 	i =0;
// 	j =0;
// 	while (in[i] && in[i][j])
// 	{
// 		if (c == '<' || c == '>' || c == '|')
			
// 		j++;
// 	}
// }

// void	node_add(t_tok *p, char *in)
// {
// 	p = p->next;

// }

void	init_list(t_cmd *cmd, char **cmd_split)
{
	int	y;
	// int	i;
	// int	j;
	t_tok *p;
	
	y = 0;
	// cmd->node = lex_lstnew(cmd_split[y++]);
	// if (cmd->node == NULL)
	// 	return ; // set error
	p = cmd->node;
	// i = 0;
	// j = 0;
	while (cmd_split[y])
	{
		p= lex_lstnew(cmd_split[y]);
		if (p == NULL)
		{ // error; have to free and exit
			break;
		}
		else if (y == 0)
			cmd->node = p;

		p = p->next;
		y++;
	}

				//testing purposes: checking if the list is filled
				// p = cmd->node;
				// while (p)
				// {
				// 	printf("list: %s\n", p->tok);
				// 	p = p->next;
				// }
}

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
/* 
void	separate_pipe(t_cmd *cmd, t_cmd *current)
{
	return;
}


void	split_list(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd->node->next;
	// find | < << > >> outside of quotes that are not alone-standing
		// e.g. ls| grep a
	separate_pipe(cmd, current)

	// find quotes 


} */

void	lexer(t_cmd *cmd)
{
	char	**matrix;
	
	matrix = split_cmd(cmd);
	init_list(cmd, matrix);
	// split_list(cmd); //WIP HERE
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
