/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:48 by lknobloc          #+#    #+#             */
/*   Updated: 2022/10/24 17:02:50 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	if (nmemb >= 2147483647 || size >= 2147483647)
		return (NULL);
	ptr = (unsigned char *) malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (&ptr[0]);
}

/*
int	main()
{
	
	char	*newarray = (char *) ft_calloc(5, sizeof(char));
	newarray = "678";

	printf("%s\n", newarray);
//	printf("%d\n", newarray[1]);
//	printf("%d\n", newarray[2]);
	// printf("%d\n", newarray[1][0]);
	free(newarray);
	return 0;
}
*/
