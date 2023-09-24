/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:03:52 by lknobloc          #+#    #+#             */
/*   Updated: 2022/10/24 18:37:05 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*t;

	i = 0;
	size = (int) ft_strlen(s);
	t = (char *) malloc(sizeof(char) * size + sizeof(char));
	if (t == NULL)
		return (NULL);
	while (s[i])
	{
		t[i] = s[i];
		i++;
	}
	t[i] = 0;
	return (&t[0]);
}
/*
   int	main()
   {
   char	*str = "lol";

// ft_strdup(str);

char	*new = ft_strdup(str);
printf("%s\n", new);
// WIP: free space here
return 0;
}
*/
