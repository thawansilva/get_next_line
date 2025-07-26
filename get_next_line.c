/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:21:54 by thaperei          #+#    #+#             */
/*   Updated: 2025/07/25 11:21:54 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;

	len_dest = ft_strlen(dest);
	i = 0;
	while (i < size && src[i])
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i]  = '\0';
	return (len_dest + i);
}

int	ft_isnewline(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

size_t	ft_get_newline_pos(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '\n')
			return (--i);
	}
	return (0);
}

char	*ft_get_remainder(char *str)
{
	size_t	size;
	char	*remainder;

	size = ft_strlen(str);
	remainder = (char *) malloc(size + 1);
	if (!remainder)
		return (0);
	ft_strlcpy(remainder, str, size);
	return (remainder);
}
char	*ft_getline(char *buffer, size_t end)
{
	char		*str;
	static char	*remainder;
	size_t		size;

	str = NULL;
	if (end > 0)
	{
		size = ft_strlen(buffer) - end;
		str = (char *) malloc(end + 1);
		ft_strlcpy(str, buffer, end);
		remainder = ft_get_remainder(buffer + size);
	}
	return (str);
}

char	*ft_get_next_line(int fd)
{
	size_t	size;
	size_t	end;
	char	buffer[BUFFER_SIZE + 1];

	if (fd < 0)
		return (0);
	end = 0;
	size = read(fd, buffer, BUFFER_SIZE);
	while (size > 0)
	{
		buffer[size] = '\0';
		if (ft_isnewline(buffer))
		{
			// Show buffer until newline and keep the rest
			end = ft_get_newline_pos(buffer);
			return ft_getline(buffer, end);
		}
		// read next line
		size = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_getline(buffer, end));
}
