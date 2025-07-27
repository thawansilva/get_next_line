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

int	ft_get_newline_pos(char *str)
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

//char	*ft_get_remainder(char *str)
//{
//	size_t	size;
//	char	*remainder;
//
//	size = ft_strlen(str);
//	remainder = (char *) malloc(size + 1);
//	if (!remainder)
//		return (0);
//	ft_strlcpy(remainder, str, size);
//	return (remainder);
//}

char	*ft_parse_line(char *buffer, size_t end)
{
	static char	*remainder;
	char		*str;
	size_t		buf_len;
	size_t		rem_len;

	str = (void *)0;
	buf_len = ft_strlen(buffer);
	rem_len = ft_strlen(remainder);
	if (buf_len > end) // buffer with \n
	{
		if (rem_len > 0) // filled remainder
		{
			str = ft_calloc(rem_len + end, sizeof(char));
			if (!str)
				return ((void *)0);
			ft_strlcpy(str, remainder, rem_len);
			ft_strlcpy(str, buffer, end);
		}
		else // empty remainder
		{
			str = ft_calloc(buf_len, sizeof(char));
			if (!str)
				return ((void *)0);
			ft_strlcpy(str, buffer, end);
		}
		remainder = ft_calloc(buf_len - end, sizeof(char));
		ft_strlcpy(remainder, buffer + end + 1, buf_len - end);
	}
	else // buffer without \n
	{
		if (rem_len > 0 && buf_len == end) // filled remainder
		{
			str = ft_strjoin(remainder, buffer);
			free(remainder);
			remainder = ft_strjoin(str, "");
		}
		else
		{
			remainder = ft_calloc(buf_len, sizeof(char));
			ft_strlcpy(remainder, buffer, buf_len);
		}
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
		end = ft_get_newline_pos(buffer);
		if (end != 0)
			return (ft_parse_line(buffer, end));
		else
			ft_parse_line(buffer, size);
		size = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_parse_line(buffer, end));
}
