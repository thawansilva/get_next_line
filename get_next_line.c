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

static char	*ft_get_line(char *text)
{
	size_t	line_len;
	char	*line;

	line = NULL;
	line_len = 0;
	while (text[line_len] && text[line_len] != '\n')
		line_len++;
	if (!text[line_len])
		return (text);
	if (text[line_len] == '\n')
		line_len++;
	line = ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (ft_free(line, NULL));
	ft_strlcpy(line, text, line_len + 1);
	return (line);
}

static char	*ft_get_remainder(char *text)
{
	size_t	nl_pos;
	size_t	rem_len;
	char	*remainder;

	nl_pos = 0;
	while (text[nl_pos] && text[nl_pos] != '\n')
		nl_pos++;
	if (text[nl_pos] == '\0')
		return (NULL);
	rem_len = ft_strlen(text) - nl_pos;
	if (rem_len <= 1)
		return (ft_free(text, NULL));
	remainder = ft_calloc(rem_len + 1, sizeof(char));
	if (!remainder)
		return (ft_free(remainder, text));
	ft_strlcpy(remainder, text + nl_pos + 1, rem_len + 1);
	free(text);
	return (remainder);
}

static char	*ft_parse_line(char *line, int fd)
{
	char	*buff;
	int		bytes_read;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (ft_free(buff, line));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buff, line));
		buff[bytes_read] = '\0';
		line = ft_strjoin(line, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes_read == 0 && (line[0] == '\0' || !line))
		return (ft_free(line, buff));
	ft_free(buff, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(text, NULL));
	text = ft_parse_line(text, fd);
	if (!text)
		return (NULL);
	line = ft_get_line(text);
	if (!line)
		return (ft_free(line, text));
	text = ft_get_remainder(text);
	return (line);
}
