/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:21:28 by hluo              #+#    #+#             */
/*   Updated: 2024/04/19 10:08:14 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup2(char *src)
{
	int		i;
	char	*dest;
	char	*comp;

	i = 0;
	comp = ((dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1)));
	if (!comp)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/* 
int	main(void)
{
	char *ptr;

	ptr = "test";
	printf("Das Originale ist: \"%s\"\n", ptr);
	printf("Das duplizierte ist: \"%s\"\n", ft_strdup(ptr));
	return (0);
} */