/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:55:17 by hluo              #+#    #+#             */
/*   Updated: 2024/06/12 19:55:18 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_com *current)
{
	if (!(current && current->args && current->args[0]))
		return (-1);
	if (ft_strcmp(current->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(current->args[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(current->args[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(current->args[0], "export") == 0)
		return (4);
	else if (ft_strcmp(current->args[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(current->args[0], "env") == 0)
		return (6);
	else if (ft_strcmp(current->args[0], "exit") == 0)
		return (7);
	return (0);
}
