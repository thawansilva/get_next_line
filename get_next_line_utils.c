/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:22:39 by thaperei          #+#    #+#             */
/*   Updated: 2025/07/25 11:22:39 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (size);
	while (*str++)
		size++;
	return (size);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	full_size;

	if (!nmemb || !size)
		return ((void *)0);
	if (nmemb > ((size_t)-1 / size))
		return ((void *)0);
	full_size = nmemb * size;
	ptr = (void *) malloc(full_size);
	if (!ptr)
		return ((void *)0);
	i = 0;
	while (i < full_size)
		((unsigned char *)ptr)[i++] = '\0';
	return (ptr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str_join;
	int		s1_len;
	int		s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_join = calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str_join)
		return (NULL);
	ft_strlcpy(str_join, s1, s1_len + 1);
	ft_strlcpy(str_join + s1_len, s2, s2_len + 1);
	return (str_join);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (src_len);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == 0)
		return ((char *)str);
	return (NULL);
}
