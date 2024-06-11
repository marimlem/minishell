/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:38:11 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 14:38:15 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_ext(t_data *d, char **code, char **exp, int *len)
{
	(*code) = ft_itoa(d->exit_code % 255);
	if ((*code) == NULL)
	{
		d->error = 231;
		return (1);
	}
	*len = ft_strlen((*code));
	(*exp) = (char *) ft_calloc(*len + ft_strlen(d->tmp), sizeof(char));
	if ((*exp) == NULL)
	{
		free ((*code));
		*code = NULL;
		d->error = 231;
		return (1);
	}
	return (0);
}

void	expand_exitstatus(t_data *d)
{
	char	*code;
	char	*exp;
	int		len;

	if (setup_ext(d, &code, &exp, &len) != 0)
		return ;
	ft_memmove(exp, d->tmp, d->i);
	ft_memmove(&exp[d->i], code, len);
	if (d->tmp[d->i + 2] != 0)
		ft_memmove(&exp[ft_strlen(code) + d->i], &d->tmp[d->i + 2],
			ft_strlen(&d->tmp[d->i + 2]));
	else
	{
		while (d->tmp[d->i + len -1])
		{
			d->tmp[d->i + len -1] = 0 ;
			len++;
		}
	}
	d->i = d->i + ft_strlen(code);
	free(d->tmp);
	d->tmp = exp;
	if (code)
		free (code);
	return ;
}