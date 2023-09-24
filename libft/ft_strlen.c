/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:24:37 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:53:05 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}
/*
int	main()
{
	char	*str = "1234";
	
	printf("str: %s\nstrlen: %ld\n", str, strlen(str));
	printf("ft_strlen: %ld\n", ft_strlen(str));
	return 0;
}
*/
