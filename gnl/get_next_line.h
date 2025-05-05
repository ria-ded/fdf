/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:56:18 by mdziadko          #+#    #+#             */
/*   Updated: 2025/04/22 21:25:15 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 5
# endif

typedef struct s_fd_list
{
	int				fd;
	char			*remainder;
	int				eof;
	struct s_fd_list	*next;
}					t_fd_list;

char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *src);
t_fd_list	*get_fd(t_fd_list **head, int fd);
void		free_node(t_fd_list **head, int fd);
int			read_and_store(int fd, t_fd_list **head);
void		extract_line(char **remainder, char **line);
char		*get_next_line(int fd);

#endif