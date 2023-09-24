/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:23:28 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:53:23 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if ((char) little[k] == 0 && (char) big[i] == 0)
		return ((char *) &big[k]);
	if ((char) little[k] == 0)
		return ((char *) &big[k]);
	while ((char) big[i] && i < len)
	{
		if ((char) big[i] == (char) little[k])
		{
			if ((char) little[k + 1] == '\0')
				return ((char *) &big[i - k]);
			i++;
			k++;
		}
		else
		{
			i = i - k + 1;
			k = 0;
		}
	}
	return (NULL);
}
/*
int	main()
{
	char	*str = (char *) "";
	char	*str2 = "";
	int	num = -1;
	
//	printf("strstr: %s\n", strstr(str, str2));
	printf("ft_strnstr: %s\n", ft_strnstr(str, str2, num));
	return 0;
}
*/
