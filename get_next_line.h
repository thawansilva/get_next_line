/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:22:51 by thaperei          #+#    #+#             */
/*   Updated: 2025/07/25 11:22:51 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_get_next_line(int fd);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
#endif 
