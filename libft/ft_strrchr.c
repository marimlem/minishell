/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:22:27 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:53:27 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last;
	char	*t;

	t = (char *) s;
	i = 0;
	last = -1;
	while (c >= 256)
		c -= 256;
	while (t[i])
	{
		if (t[i] == c)
			last = i;
		i++;
	}
	if (t[i] == 0 && c == '\0')
		return (&t[i]);
	else if (t[i] == 0 && last != -1)
		return (&t[last]);
	else
		return (NULL);
}
/*
int	main()
{
	char	*str = "tripouille";
//	char	c = 't';
	
	printf("ft: %s\n", ft_strrchr(str, 'l' + 253));
	printf("strrchr: %s\n", strrchr(str, 'l' + 253));
	
	return 0;
}
*/
