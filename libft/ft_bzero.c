/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:41:49 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:50:27 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
int	main()
{
	char	str[50] = "222";
	char	str2[50] = "222";
	int	c = 117;
	size_t	n = 4;
	
	printf("str before: %s\nc: %d\n", str, c);
	
	bzero(str, n);
	ft_bzero(str2, n);

	size_t	i = 0;
	while (i < n + 1)
	{
		printf("%d, ", str[i]);
		i++;
	}
	printf("\n");
	i = 0;
	
	while (i < n + 1)
	{
		printf("%d, ", str2[i]);
		i++;
	}

	printf("bzero: %s\n", str);
	printf("ft_bzero: %s\n", str2);
	
	return (0);
}
*/
