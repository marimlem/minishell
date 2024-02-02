#include "minishell.h"

void	lex_lstsqueezein(t_tok *current, char *str)
{
	t_tok	*new;
	
	new = lex_lstnew(str);
	if (new == NULL)
		return ;
	new->next = current->next;
	current->next = new;
	return ;
}


void	lex_lst_rmone(t_tok *current)
{
	t_tok *to_delete;
	t_tok *next;

	to_delete = current->next;
	next = current->next->next;
	current->next = next;
	if (to_delete->tok)
		free (to_delete->tok);
	to_delete->next = NULL;
	free (to_delete);
}

char	*lex_strjoin(char const *s1, char const *s2, char deli)
{
	int		k;
	int		len;
	char	*new;

	k = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *) malloc (sizeof(char) * len + 1);
	if (new == NULL)
		return (NULL);
	while (s1[k])
	{
		new[k] = s1[k];
		k++;
	}
	new[k++] = deli;
	while (*(s2))
	{
		new[k++] = *(s2)++;
	}
	new[k] = 0;
	return (new);
}