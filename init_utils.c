#include "minishell.h"

void	init_envlist(t_envlist **envlist)
{
	(*envlist)->key = NULL;
	(*envlist)->value = NULL;
	(*envlist)->next = NULL;
}

void	init_null(t_data *d)
{
	d->input = NULL;
	d->node = NULL;
	d->com = NULL;
	d->tmp = NULL;
	d->var_node = NULL;
	d->fd = NULL;
	d->old_fd = NULL;
	d->i = 0;
	d->q = 0;
	d->error = 0;
	d->p = NULL;
	d->path = NULL;
	d->hd_path = NULL;
	d = NULL;
	
}
int	raise_shlvl(char **envp)
{
	int	i;
	int	lvl;

	i = 0;
	lvl = -1;
	while(envp && envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			lvl = ft_atoi(&envp[i][6]);
			// printf("lvl: %s\n", d->envp[i]);
			if (lvl >= 9)
			{
				ft_putstr_fd("minishell error: shell-level too high: ", 2);
				ft_putnbr_fd(lvl, 2);
				ft_putstr_fd("\n", 2);
				return (lvl);
			}
			else
			{
				envp[i][6] = envp[i][6] + 1;
			}
			break ;
		}
		i++;
	}
	return (0);
}