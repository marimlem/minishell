#include "minishell.h"

//check for unclosed quotes, error if odd number
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