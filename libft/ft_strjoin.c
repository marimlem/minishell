/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:04:10 by lknobloc          #+#    #+#             */
/*   Updated: 2022/10/24 18:39:41 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		k;
	int		len;
	char	*new;

	k = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *) malloc (sizeof(char) * len + 1);
	if (new == NULL)
		return (NULL);
	while (s1[k])
	{
		new[k] = s1[k];
		k++;
	}
	while (*(s2))
	{
		new[k++] = *(s2)++;
	}
	new[k] = 0;
	return (new);
}
/*
   int main()
   {
   char    *str1 = "tripouille";
   char    *str2 = "42";

   char    *join = ft_strjoin(str1, str2);
   printf("joined: %s\n", join);
   return 0;
   }
*/
