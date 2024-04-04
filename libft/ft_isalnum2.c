/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:10:47 by hluo              #+#    #+#             */
/*   Updated: 2024/04/04 17:00:00 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum2(char aln)
{
	if ((aln > 47 && aln < 58) || (aln > 64 && aln < 91) || (aln > 96
			&& aln < 123) || (aln == 95))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	int	argument;

	argument = '8';
	printf("%d\n", ft_isalnum(argument));
	return (0);
}*/
