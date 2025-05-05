/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:01:43 by mdziadko          #+#    #+#             */
/*   Updated: 2025/04/20 17:10:11 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_fd_list	*get_fd(t_fd_list **head, int fd)
{
	t_fd_list	*node;

	node = *head;
	while (node && node->fd != fd)
		node = node->next;
	if (node)
		return (node);
	node = malloc(sizeof(t_fd_list));
	if (!node)
		return (NULL);
	node->remainder = ft_strjoin("", "");
	if (!node->remainder)
	{
		free(node);
		return (NULL);
	}
	node->fd = fd;
	node->eof = 0;
	node->next = *head;
	*head = node;
	return (node);
}

void	free_node(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->remainder);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	freemem(char *buf, t_fd_list **head, int fd, int is_error)
{
	free(buf);
	if (is_error)
	{
		free_node(head, fd);
		return (-1);
	}
	return (0);
}

int	read_and_store(int fd, t_fd_list **head)
{
	char		*buf;
	int			bytes_read;
	char		*temp;
	t_fd_list	*current;

	current = get_fd(head, fd);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf || !current)
		return (freemem(buf, head, fd, 1));
	while (!ft_strchr(current->remainder, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			current->eof = 1;
			break ;
		}
		buf[bytes_read] = '\0';
		temp = ft_strjoin(current->remainder, buf);
		if (!temp)
			return (freemem(buf, head, fd, 1));
		free(current->remainder);
		current->remainder = temp;
	}
	return (freemem(buf, head, fd, 0));
}

void	extract_line(char **remainder, char **line)
{
	char	*new_line;
	char	*temp;
	size_t	len;

	new_line = ft_strchr(*remainder, '\n');
	if (new_line)
	{
		len = new_line - (*remainder) + 1;
		*line = ft_substr(*remainder, 0, len);
		temp = ft_strjoin(new_line + 1, "");
		free(*remainder);
		*remainder = temp;
	}
	else
	{
		*line = ft_strjoin(*remainder, "");
		free(*remainder);
		*remainder = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*current;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_fd(&head, fd);
	if (!current)
		return (NULL);
	if (!current->remainder)
		current->remainder = ft_strjoin("", "");
	if (!current->remainder)
		return (NULL);
	if (read_and_store(fd, &head) == -1)
		return (NULL);
	if (!current->remainder || !(*current->remainder))
	{
		if (current->eof == 1)
			free_node(&head, fd);
		return (NULL);
	}
	extract_line(&current->remainder, &line);
	return (line);
}
