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

typedef struct s_list
{
	void	*content;
	void	*next;
}			t_list;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_getline(char *buffer, size_t end);
int		ft_isnewline(char *str);
size_t	ft_get_newline_pos(char *str);
char	*ft_get_next_line(int fd);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
#endif 
