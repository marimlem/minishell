#include "minishell.h"

void	free_n_clean(t_data *d, int b)
{
	int	i;

	i = 0;
	
	lex_lst_del(d->node);
	com_lst_del(d->com);
	
	if (d->input)
		free (d->input);

	if (d->tmp)
		free (d->tmp);
	d->error = 0;
	d->i = 0;
	d->q = 0;
	if (d->fd)
		free (d->fd);
	if (d->old_fd)
		free(d->old_fd);
	if (d->path)
	{
		while (d->path[i])
		{
			free(d->path[i]);
			d->path[i++] = NULL;
		}
		free (d->path);
	}

	i = 0;
	if (d->p)
	{
		while (d->p[i])
		{
			free (d->p[i]);
			d->p[i++] = NULL;
		}
		free (d->p);
		d->p = NULL;
	}
	if (d->hd_path)
	{
		unlink(d->hd_path);
		free (d->hd_path);
		d->hd_path = NULL;
	}

	if (b == 0)
		return ;
	free_list(d->env);
	if (d)
		free (d);
	d = NULL;
	

}
