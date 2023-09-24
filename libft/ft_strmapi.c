/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:45:54 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:53:11 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	ft_dis(unsigned int i, char c)
{
	c = i + 48;
	write (1, &c, 1);
	return (c);	
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*t;

	t = ft_strdup(s);
	if (t == NULL)
		return (NULL);
	i = 0;
	while (t[i])
	{
		t[i] = f(i, t[i]);
		i++;
	}
	return (t);
}
/*
int	main()
{
	char	*str = ft_strmapi("000", ft_dis);
	printf("\nmain: %s\n", str);
	return 0;
}
*/
