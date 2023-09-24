/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:01:03 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:52:21 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*t;

	t = (char *) s;
	i = 0;
	while (c >= 256)
		c -= 256;
	while (t[i])
	{
		if (t[i] == c)
			return (&t[i]);
		i++;
	}
	if (t[i] == 0 && c == '\0')
		return (&t[i]);
	return (NULL);
}
/*
int	main()
{
	char	*str = "123456789";
	char	c = '\0';
	
	printf("ft: %s\n", ft_strchr(str, c));
	printf("strchr: %s\n", strchr(str, c));
	
	return 0;
}
*/
