/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:23:32 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:52 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	s11 = (unsigned char *) s1;
	s22 = (unsigned char *) s2;
	i = 0;
	if (i == n)
		return (0);
	while (i < n)
	{
		if (s11[i] == s22[i])
			i++;
		else
			return (s11[i] - s22[i]);
	}
	return (s11[i - 1] - s22[i - 1]);
}

/*
int	main()
{
	char	str1[] = {-128, 0, 127, 0};
	char	str2[] = {-128, 0, 127, 0};
	int	n = 3;

	printf("s1: %s\ns2: %s\nn: %d\n\n", str1, str2, n);
	printf("f: %d\n", ft_memcmp(str1, str2, n));
	printf("o: %d\n", memcmp(str1, str2, n));
	return 0;
}
*/
// return value not specified
