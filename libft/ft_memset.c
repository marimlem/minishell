/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:30:36 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:52:09 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	d;
	unsigned char	*str;

	str = (unsigned char *) s;
	d = c;
	while (n > 0)
	{
		*str++ = d;
		n--;
	}
	return (s);
}
/*
int	main()
{
	char	str[5] = "2222";
	char	str2[5] = "1111";
	int	c = 117;
	size_t	n = 1;
	
	printf("str before: %s\nc: %d\n", str, c);
	
	memset(str, c, n);
	ft_memset(str2, c, n);
	printf("memset: %s\n", str);
	printf("ft_memset: %s\n", str2);
	
	return (0);
}
*/
