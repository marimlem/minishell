/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:28:10 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/26 11:26:29 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *) s1;
	s22 = (unsigned char *) s2;
	i = 0;
	while ((s11[i] || s22[i]) && i < n && s11[i] == s22[i])
		i++;
	if (i == n || (s11[i] == '\0' && s22[i] == '\0'))
		return (0);
	else if (s11[i] > s22[i])
		return (1);
	else
		return (-1);
}
