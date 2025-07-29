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

int	ft_get_newline_pos(char *buffer)
{
	size_t	i;
	char	*str;

	i = 0;
	str = buffer;
	while (str[i])
	{
		if (str[i++] == '\n')
			return (--i);
	}
	return (-1);
}

char	*ft_get_line(char *buffer, char *remainder, size_t end)
{
	char	*str;
	size_t	buf_len;
	size_t	rem_len;

	buf_len = ft_strlen(buffer);
	rem_len = ft_strlen(remainder);
	if (end == 0)
		return (ft_strjoin(buffer, ""));
	if (rem_len > 0)
	{
		str = ft_calloc(rem_len + end + 1, sizeof(char));
		if (!str)
			return ((void *)0);
		ft_strlcpy(str, remainder, rem_len + end + 1);
		ft_strlcpy(str + rem_len, buffer, rem_len + end + 1);
		free(remainder);
	}
	else {
		str = ft_calloc(buf_len + 1, sizeof(char));
		if (!str)
			return ((void *)0);
		ft_strlcpy(str, buffer, buf_len + 1);
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
	if (rem_len > 0 && end != 0)
	{
		str = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = ft_strjoin(str, "");
	}
	else
	{
		remainder = ft_calloc(buf_len + 1, sizeof(char));
		ft_strlcpy(remainder, buffer, buf_len + 1);
	}
	return (remainder);
}

char	*ft_parse_line(char *buffer, int fd, size_t end)
{
	static char	*remainder[OPEN_MAX];
	char		*str;
	size_t		buf_len;

	if (end == 0)
		return (ft_get_line(buffer, remainder[fd], end));
	buf_len = ft_strlen(buffer);
	str = (void *)0;
	if (buf_len == 0)
		return (remainder[fd]);
	if (buf_len > end)
	{
		str = ft_get_line(buffer, remainder[fd], end);
		if (buf_len - end > 1)
		{
			remainder[fd] = ft_calloc(buf_len - end + 1, sizeof(char));
			ft_strlcpy(remainder[fd], buffer + end + 1, buf_len - end + 1);
		}
	}
	else
		remainder[fd] = ft_get_remainder(remainder[fd], buffer, end);
	return (str);
}

char	*get_next_line(int fd)
{
	size_t	size;
	size_t	end;
	char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	end = 0;
	size = read(fd, buffer, BUFFER_SIZE);
	if ((size_t) -1 == size)
		return (0);
	while (size > 0)
	{
		buffer[size] = '\0';
		end = ft_get_newline_pos(buffer);
		if ((size_t) -1 != end)
			return (ft_parse_line(buffer, fd, end));
		ft_parse_line(buffer, fd, size);
		size = read(fd, buffer, BUFFER_SIZE);
	}
	if (size == 0 && (size_t) -1 == end)
		return (ft_parse_line("", fd, end));
	return ((void *)0);
}
