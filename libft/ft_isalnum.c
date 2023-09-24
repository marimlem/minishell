/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:09:03 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:50:49 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int arg)
{
	if (arg >= 48 && arg <= 57)
		return (1);
	else if ((arg >= 65 && arg <= 90) || (arg >= 97 && arg <= 122))
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
	
	printf("isalnum: \nc: %d\nd: %d", isalnum(c), isalnum(d));
	printf("\nft_isalnum: \nc: %d\nd: %d", ft_isalnum(c), ft_isalnum(d));
	return (0);
}
*/
