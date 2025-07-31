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

static void	*ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*ft_get_line(char *text)
{
	size_t	i;
	char	*line
	return (line);
}

//char	*ft_get_remainder(char *remainder, char *buffer, size_t end)
//{
//}
//
char	*ft_parse_line(char *line, int fd)
{
	char	*buff;
	int		bytes_read;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (ft_free(buff, line));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buff, line));
		buff[bytes_read] = '\0';
		line = ft_strjoin(line, buff);
		if (ft_strchr(buff, '\n'))
			break;
	}
	if (bytes_read == 0 && (line[0] == '\0' || !line))
		return ft_free(line, buff);
	ft_free(buff, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(line, NULL));
	text = ft_get_line(line, fd);
	if (!text)
		return (NULL);
	line = ft_get_line(text);
	if (!line)
		return (ft_free(line, text));
	text = ft_get_remainder(text);
	return (line);
}
