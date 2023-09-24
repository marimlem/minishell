/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:13:52 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:01 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int arg)
{
	if (arg >= 0 && arg <= 127)
		return (1);
	else
		return (0);
}
/*
int	main()
{
	char	c;
	char	d;
	
	c = 'A';
	d = '2';
	
	printf("isascii: \nc: %d\nd: %d", isascii(c), isascii(d));
	printf("\nft_isascii: \nc: %d\nd: %d", ft_isascii(c), ft_isascii(d));
	return (0);
}
*/
