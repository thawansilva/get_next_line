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

	if (!nmemb || !size)
		return ((void *)0); // strdup
	if (nmemb > ((size_t)-1 / size))
		return ((void *)0);
	ptr = (void *) malloc(nmemb * size + 1);
	if (!ptr)
		return ((void *)0);
	i = 0;
	while (i < nmemb * size)
		((unsigned char *)ptr)[i++] = '\0';
	return (ptr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str_join;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_join = (char *) malloc(s1_len + s2_len + 1);
	if (!str_join)
		return ((void *)0);

	ft_strlcpy(str_join, s1, s1_len);
	ft_strlcpy(str_join + s1_len, s2, s1_len + s2_len);
	return (str_join);
}

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
