/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:04:32 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:52:59 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src[ft_strlen(src)] != 0)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	if (i < size)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
		return (ft_strlen(src));
	}
	else
		return (0);
}

/*
   int	main()
   {
   char    src[] = "coucou";
   char    dst[10];
   ft_memset(dst, 'A', 10);
   int n = 0;
   printf("dest: %s\n", dst);
   printf("source: %s\n\n", src);
   int result = ft_strlcpy(dst, src, n);

   printf("length of source: %d\nsource: %s\ndest: %s\n\n", result, src, dst);
   ft_putchar_fd(dst[2], 1);
   return 0;
   }
*/
