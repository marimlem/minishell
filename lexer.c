#include "minishell.h"

void	tok_init(t_cmd *cmd)
{
	cmd->start = (t_tok *) malloc(sizeof(t_tok) * 1);
	if (cmd->start == NULL)
		return ; // set error
	cmd->start->tok = NULL;
	cmd->start->typ = 0;
	cmd->start->next = NULL;
	cmd->start->before = NULL;
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

void	init_list(t_cmd *cmd, char **cmd_split)
{
	int	i;
	t_tok *p;

	p = cmd->start;

	i = 0;
	while (cmd_split[i])
	{
		new_node()
	}
}

void	split_cmd(t_cmd *cmd)
{
	char	**cmd_split;
	int	i; //testing purposes

	i = 0;

	cmd_split = ft_split(cmd->input, ' ');
	if (cmd_split == NULL)
		return;
	while (cmd_split && cmd_split[i]) //testing purposes
	{
		printf("test: %s\n", cmd_split[i]);
		i++;
	}
	init_list(cmd, cmd_split);
	// cmd_split = split_split(cmd_split);
}

void	lexer(t_cmd *cmd)
{
	tok_init(cmd);
	if (cmd->start == NULL)
		return ; // set error
	split_cmd(cmd);
	
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
