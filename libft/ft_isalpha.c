/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:42:55 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:50:56 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int arg)
{
	if ((arg >= 65 && arg <= 90) || (arg >= 97 && arg <= 122))
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
	
	printf("isalpha: \nc: %d\nd: %d", isalpha(c), isalpha(d));
	printf("\nft_isalpha: \nc: %d\nd: %d", ft_isalpha(c), ft_isalpha(d));
	return (0);
}
*/
