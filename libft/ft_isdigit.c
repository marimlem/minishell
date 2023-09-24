/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:06:05 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:51:18 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int arg)
{
	if (arg >= 48 && arg <= 57)
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
	
	printf("isdigit: \nc: %d\nd: %d", isdigit(c), isdigit(d));
	printf("\nft_isdigit: \nc: %d\nd: %d", ft_isdigit(c), ft_isdigit(d));
	return (0);
}
*/
