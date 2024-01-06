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
	cmd_execute(cmd);
	if (ft_strncmp(cmd->input, "exit", 4) == 0) //only for testing
	{

		free(cmd->input);
		cmd->input = NULL;
		exit(0); //leak of one
	}
	if (cmd->input)
	{
		free(cmd->input);
		cmd->input = NULL;
	}

}