/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:02:34 by lknobloc          #+#    #+#             */
/*   Updated: 2023/08/09 17:03:09 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*lu_eof(char **tmp, char **buffer, char **str, int size)
{
	*tmp = NULL;
	if (*buffer)
		free (*buffer);
	*buffer = NULL;
	if (!*str)
		return (NULL);
	if (size == -1)
	{
		free (*str);
		return (NULL);
	}
	return (*str);
}

char	*lu_cut_str_1(char *str, char *result, int i)
{
	if (str[i] == '\n')
	{
		result[i + 1] = 0;
		str = gnl_strdup(&str[i + 1]); //malloc protect OK
		if (str == NULL)
			return (NULL);
	}
	else
	{
		str = gnl_strdup("\0"); //malloc protect OK
		if (str == NULL)
			return (NULL);
		result[i] = 0;
	}
	return (str);
}


char	*lu_cut_str(char **str)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	tmp = *str;
	result = gnl_strdup(*str); // malloc protect OK
	if (result == NULL) //OK no leaks
	{
		free (tmp);
		return (NULL);
	}
	while (str[0][i] && str[0][i] != '\n')
		i++;
	*str = lu_cut_str_1(*str, result, i);
	if (*str == NULL) // OK no leaks
	{
		free (tmp);
		free (result);
		return (NULL); //OK no leaks
	}
	free (tmp);
	tmp = NULL;
	return (result);
}

char	*lu_read(int fd, char *str)
{
	char	*tmp;
	char	*buffer;
	int		size;

	size = 1;
	buffer = NULL;
	while (size > 0 && !gnl_strchr(str, '\n'))
	{
		if (buffer == NULL || !buffer)
			buffer = (char *) gnl_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (lu_eof(&tmp, &buffer, &str, size)); // OK no leaks
		size = read(fd, buffer, BUFFER_SIZE);
		if (size <= 0)
			return (lu_eof(&tmp, &buffer, &str, size));
		tmp = str;
		str = gnl_strjoin(str, buffer);
		free (tmp);
		if (str == NULL)
			return (lu_eof(&tmp, &buffer, &str, size)); // OK: tmp is freed before, NO LEAKS
		free (buffer);
		buffer = NULL;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*result;

	if (fd < 0)
		return (NULL);
	if (!str)
		str = (char *) gnl_calloc(sizeof(char), 1);
	if (str == NULL)
		return (NULL);
	str = lu_read(fd, str);
	if (str == NULL)
		return (NULL);
	result = lu_cut_str(&str); //malloc protect
	if (result == NULL)
		return (NULL);
	if (result[0] == '\0')
	{
		free (result);
		free (str);
		result = NULL;
		str = NULL;
	}
	return (result);
}

	
/* 	if (str[0][i] == '\n')
	{
		result[i + 1] = 0;
		*str = gnl_strdup(&str[0][i + 1]); //malloc protect
	}
	else
	{
		*str = gnl_strdup("\0"); //malloc protect
		result[i] = 0;
	} */