/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:03:23 by lknobloc          #+#    #+#             */
/*   Updated: 2022/10/24 17:03:25 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intsize(int n)
{
	int	size;
	int	temp;

	temp = n;
	size = 1;
	if (n == -2147483647 - 1)
		return (11);
	else if (n == -0 || n == 0)
		return (size);
	else if (n < 0 && n != 0)
	{
		temp *= -1;
		size += 1;
	}
	while (temp > 9)
	{
		temp /= 10;
		size += 1;
	}
	return (size);
}

static char	*ft_dostr(int n)
{
	char	*str;

	str = NULL;
	if (n == -2147483647 -1)
		str = ft_strdup("-2147483648");
	else if (n == -0 || n == 0)
		str = ft_strdup("0");
	return (str);
}

char	*ft_itoa(int n)
{
	int		temp;
	int		m;
	char	*str;

	m = 1;
	temp = n;
	if (n == -2147483647 -1 || n == -0 || n == 0)
		return (ft_dostr(n));
	str = (char *) malloc(sizeof(char) * (ft_intsize(n) + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		temp *= -1;
	while (temp != 0)
	{
		str[ft_intsize(n) - m] = (char)(temp % 10) + 48;
		temp = temp / 10;
		m++;
	}
	if (n < 0)
		str[ft_intsize(n) - m] = '-';
	str[ft_intsize(n)] = 0;
	return (str);
}
/*
int main()
{
	char    *s = ft_itoa(-2147483648);
	printf("stringprint: %s\n", s);
	printf("\n");
	printf("\n");

	printf("%d\n", s[0]);
	printf("%d\n", s[1]);
	printf("%d\n", s[2]);
	printf("%d\n", s[3]);

	return 0;
}
*/
	//long int x = (long int) n;
	//
