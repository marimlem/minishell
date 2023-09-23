#include "minishell.h"

void	inputparsing(t_cmd *cmd)
{
	cmd->input = get_next_line(0);
	
	if (ft_strncmp(cmd->input, "exit", 4) == 0)
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