/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:16:35 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:26 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int arg)
{
	if (arg >= 32 && arg < 127)
		return (1);
	else
		return (0);
}
/*
int	main()
{
	char	c;
	char	d;
//	char	test;
	
	c = 3;
	d = 65;
//	test = 0;
	
	printf("isprint: \nc: %d\nd: %d", isprint(c), isprint(d));
	printf("\nft_isprint: \nc: %d\nd: %d", ft_isprint(c), ft_isprint(d));
/	while (test < 127)
	{
		printf("\n%d is printable?: %c\n", test, test);
		test++;
	}

	return (0);
}
*/
