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

char	*ft_get_line(char *buffer, char *remainder, size_t end)
{
	char	*str;
	size_t	buf_len;
	size_t	rem_len;
	
	buf_len = ft_strlen(buffer);
	rem_len = ft_strlen(remainder);
	if (rem_len > 0) 
	{
		str = ft_calloc(rem_len + end, sizeof(char));
		if (!str)
			return ((void *)0);
		ft_strlcpy(str, remainder, rem_len);
		ft_strlcpy(str, buffer, end);
	}
	else
	{
		str = ft_calloc(buf_len, sizeof(char));
		if (!str)
			return ((void *)0);
		ft_strlcpy(str, buffer, end);
	}
	return (str);
}

char	*ft_get_remainder(char *remainder, char *buffer, size_t end)
{
	size_t	rem_len;
	size_t	buf_len;
	char	*str;

	rem_len = ft_strlen(remainder);
	buf_len = ft_strlen(buffer);
	if (rem_len > 0 && buf_len == end)
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
	return (remainder);
}

char	*ft_parse_line(char *buffer, size_t end)
{
	static char	*remainder;
	char		*str;
	size_t		buf_len;
	size_t		rem_len;

	str = (void *)0;
	buf_len = ft_strlen(buffer);
	rem_len = ft_strlen(remainder);
	if (buf_len > end) 
	{
		str = ft_get_line(buffer, remainder, end);
		remainder = ft_calloc(buf_len - end, sizeof(char));
		ft_strlcpy(remainder, buffer + end + 1, buf_len - end);
	}
	else
		remainder = ft_get_remainder(remainder, buffer, end);
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
