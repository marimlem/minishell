#include "minishell.h"

void	inputparsing(t_cmd *cmd)
{
	cmd->input = readline("minishell:$ ");
	if (!cmd || !cmd->input)
		return ;
	if (even_quotes(cmd) == EVEN)
	{
		lexer(cmd);
		// printf("even!");
	}

	//parser

}