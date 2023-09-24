/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:19:18 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:59 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest1;
	const char	*src1;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest1 = (char *) dest;
	src1 = (const char *) src;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}
/*
int	main()
{
	char	str1[50] = "11111";
	char	str11[50] = "11111";
	char	str2[50] = "22222";
	size_t	num = 4;
	char	*ptr = (char*) memcpy(str1, str2, num);
	ft_memcpy(str11, str2, num);
	printf("memcpy: %s\n", ptr);
	printf("ft_memcpy: %s\n", str11);
	
	return 0;
}
*/
