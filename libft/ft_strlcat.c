/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 10:58:21 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:52:51 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ld;
	size_t	ls;
	size_t	i;
	size_t	j;

	ld = ft_strlen(dest);
	ls = ft_strlen(src);
	i = ld;
	j = 0;
	if (dest[ld] || src[ls])
		return (0);
	if (size == 0 || size <= ld)
		return (ls + size);
	while (src[j] && j < size - ld - 1)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (ld + ls);
}
/*
int	main()
{
	char	dest[30];	
	memset(dest, 0, 30);
	dest[0] = 'B';
	memset(dest, 'B', 4); //3 4
//	memset(dest, 'C', 5); //5
  //      memset(dest, 'C', 15); //6
    //    memset(dest, 0, 30); //7
      //  memset(dest, 0, 30); memset(dest, '1', 10); //8


	char	*src = (char *) "AAAAAAAAA";
	printf("dest: %s\nsource: %s\n\n", dest, src);
	int	result = ft_strlcat(dest, src, 6);
	printf("dest: %s\nresult: %d\n", dest, result);
}
*/
/*
 The strlcat() function appends the NUL-terminated string src to the end
     of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-termi‐
     nating the result.
     
     Note, however, that if strlcat() traverses size characters without find‐
     ing a NUL, the length of the string is considered to be size and the des‐
     tination string will not be NUL-terminated (since there was no space for
     the NUL).  This keeps strlcat() from running off the end of a string.  In
     practice this should not happen (as it means that either size is incor‐
     rect or that dst is not a proper “C” string).  The check exists to pre‐
     vent potential security problems in incorrect code.

*/
