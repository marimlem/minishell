/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:34:42 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:47 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*t;

	t = (const char *) s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (t[i] == (char) c)
			return ((void *) &t[i]);
		i++;
	}
	return (NULL);
}
/*
int	main()
{
//	char	str[] = {'0', '1', '2', '3', '4', '5'};
//	char	c = '2';
//	int	n = 3 + 48;
	char	str[] = {0, 1, 2, 3, 4, 5};
	int	c = 2;
	int	n = 3;
	char	*str2 = (char *) memchr(str, c, n);
	char	*str3 = (char *) ft_memchr(str, c, n);
//	printf("ft: %s\n", ft_memchr(str, c, n));
	printf("memchr: %s\n", str2);
	printf("ft_memchr: %s\n", str3);
	
	return 0;
}
*/
