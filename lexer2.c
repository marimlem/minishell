#include "minishell.h"

void	lex_outside_q(t_cmd *cmd, t_tok **current)
{
	if ((*current)->tok[cmd->i] == 0)
	{
		(*current) = (*current)->next;
		cmd->i = -1;
		return ;
	}
	else if ((*current)->tok[cmd->i] == SGLQUOTE || (*current)->tok[cmd->i] == DBLQUOTE)
	{
		cmd->q = (*current)->tok[cmd->i];
		if (cmd->i != 0 && (*current)->tok[cmd->i-1] == '|') // if not the first character
		{
			lex_lstsqueezein((*current), &(*current)->tok[cmd->i+1]);
			(*current)->tok[cmd->i] = 0;
			(*current) = (*current)->next;
			cmd->i = -1; 
			return ;
		}
		else if (cmd->i != 0) 
		{ // case: hello"world" => helloworld
			ft_memmove(&(*current)->tok[cmd->i], &(*current)->tok[cmd->i+1], ft_strlen(&(*current)->tok[cmd->i+1]) + 1);
			// (*current)->tok[ft_strlen(&(*current)->tok[cmd->i+1]) + 1] = 0;
			(*current)->typ = cmd->q;
		}
		else if (cmd->i == 0)
		{
			(*current)->tok = &(*current)->tok[cmd->i+1];
		}
	}
	else if (cmd->q == 0 && ((*current)->tok[cmd->i] == '<' || (*current)->tok[cmd->i] == '>'))
	{ //should do smth here
		return ;
	}

}
void	lex_inside_q(t_cmd *cmd, t_tok **current)
{
	if ((*current)->tok[cmd->i] == cmd->q)
	{
		(*current)->typ = cmd->q;
		cmd->q = 0;
		if ((*current)->tok[cmd->i + 1] != 0 && (*current)->tok[cmd->i + 1] != '|')
		{
			ft_memmove(&(*current)->tok[cmd->i], &(*current)->tok[cmd->i+1], ft_strlen(&(*current)->tok[cmd->i+1]) + 1);
			cmd->i--;
			return ;
		}
		else if ((*current)->tok[cmd->i + 1] != 0 && (*current)->tok[cmd->i + 1] == '|')
		{
			lex_lstsqueezein((*current), &(*current)->tok[cmd->i+1]);
			(*current)->tok[cmd->i] = 0;
			(*current) = (*current)->next;
			(*current)->typ = '|';
			cmd->i = -1;
			return ;
		}
		(*current)->tok[cmd->i] = 0;
	}
	else if ((*current)->tok[cmd->i] == 0)
	{// append and remove next node
		(*current)->tok = lex_strjoin((*current)->tok, (*current)->next->tok, ' '); //careful of strjoin leaks
		lex_lst_rmone((*current));
		cmd->i--;
		return ;
	}
	
}

void	quote_merge_2(t_cmd *cmd)
{
	t_tok	*current;

	
	current = cmd->node;
	while (current && current->tok)
	{
		//somefunction(&current);
		if (cmd->q == 0)
			lex_outside_q(cmd, &current);
		else if (cmd->q != 0)
			lex_inside_q(cmd, &current);


			
		cmd->i++;
	}

}
