/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:51:17 by lknobloc          #+#    #+#             */
/*   Updated: 2022/10/28 13:51:19 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	k;
	int	len;

	len = (int) ft_strlen(s1);
	k = 0;
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	k = i;
	i = len - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, k, i - k + 1));
}
/*
int	main()
{
	char	*str = "23123HEHEH212312";
	char	*set = "123";
	char	*trimmed;
    	trimmed = ft_strtrim(str, set);
	printf("result: %s\n", trimmed);
	return 0;	
}
*/

/*	while (s1[i] && ft_strrchr(s1, set[o]))
	{
		printf("strrchr!: %s\n\n", ft_strrchr(s1, set[o]));
		i++;
		o++;
	}
	printf("strrchr: %s\n\n", ft_strrchr(set, s1[i]));
	return (ft_substr(s1, k, i - 1));
	*/
//	while (s1[i] && !ft_strchr(set, s1[i]))
//		i++;
//	return (ft_substr(s1, k, i - k));
