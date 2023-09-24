/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:05:04 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:52:04 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest1;
	char	*src1;

	if (dest == 0 && src == 0)
		return (0);
	dest1 = (char *) dest;
	src1 = (char *) src;
	i = 0;
	if (dest1 < src1)
	{
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
		return (dest);
	}
	i = n;
	while (i > 0)
	{
		i--;
		dest1[i] = src1[i];
	}
	return (dest);
}

/*
int	main()
{
	char	str1[50] = "123456789";
	char	str11[50] = "123456789";
//	char	str2[50] = "22";
	size_t	num = 4;
	char	*ptr = (char*) memmove(str1 + 3, str1, num);
	ft_memmove(str11 + 3, str11, num);
	printf("memmove: %s\n", ptr);
	printf("ft_memmove: %s\n", str1);
	
	return 0;
}
*/
