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
void	init_list2(t_data *d, char *input)
{

	d->node = lex_lstnew(input);
	if (d->node == NULL)
	{ // error; have to free and exit
		d->error = ERR_LEX_ALL;
	}
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