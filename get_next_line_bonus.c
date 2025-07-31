/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:21:54 by thaperei          #+#    #+#             */
/*   Updated: 2025/07/25 11:21:54 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"

static void	*ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*ft_get_line(char *str)
{
	size_t	line_len;
	char	*line;

	line = NULL;
	line_len = 0;
	while (str[line_len] && str[line_len] != '\n')
		line_len++;
	if (!str[line_len])
		return (str);
	if (str[line_len] == '\n')
		line_len++;
	line = ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (ft_free(line, NULL));
	ft_strlcpy(line, str, line_len + 1);
	return (line);
}

static char	*ft_get_remainder(char *str)
{
	size_t	nl_pos;
	size_t	rem_len;
	char	*remainder;

	nl_pos = 0;
	while (str[nl_pos] && str[nl_pos] != '\n')
		nl_pos++;
	if (str[nl_pos] == '\0')
		return (NULL);
	rem_len = ft_strlen(str) - nl_pos;
	if (rem_len <= 1)
		return (ft_free(str, NULL));
	remainder = ft_calloc(rem_len + 1, sizeof(char));
	if (!remainder)
		return (ft_free(remainder, str));
	ft_strlcpy(remainder, str + nl_pos + 1, rem_len + 1);
	free(str);
	return (remainder);
}

static char	*ft_read_str(char *str, int fd)
{
	char	*buff;
	int		bytes_read;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (ft_free(buff, str));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buff, str));
		buff[bytes_read] = '\0';
		str = ft_strjoin(str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes_read == 0 && (str[0] == '\0' || !str))
		return (ft_free(str, buff));
	ft_free(buff, NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(remainder[fd], NULL));
	remainder[fd] = ft_read_str(remainder[fd], fd);
	if (!remainder[fd])
		return (NULL);
	line = ft_get_line(remainder[fd]);
	if (!line)
		return (ft_free(line, remainder[fd]));
	remainder[fd] = ft_get_remainder(remainder[fd]);
	return (line);
}
