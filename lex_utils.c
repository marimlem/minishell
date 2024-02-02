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

t_tok	*lex_lstlast(t_tok *lst)
{
	t_tok	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

void	lex_lstadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*back;

	if (new == NULL)
		return ;
	back = lex_lstlast(*lst);
	if (back)
		back->next = new;
	else
		*lst = new;
}
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
		else 
			lex_lstadd_back(&cmd->node, p);
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

void	lst_print(t_tok *lst)
{
	t_tok *ptr;

	ptr = lst;
	ft_putstr_fd("\n---\nlistprint:\n", 1);
	while (ptr && ptr->tok)
	{
		ft_putstr_fd(ptr->tok, 1);
		ft_putnbr_fd(ptr->typ, 1);
		ft_putstr_fd("\n", 1);
		ptr = ptr->next;
	}
	ft_putstr_fd("listprint end\n---\n", 1);
}