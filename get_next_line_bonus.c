/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:44:00 by nanasser          #+#    #+#             */
/*   Updated: 2025/02/22 20:18:08 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	cleanup(t_list **list)
{
	t_list	*new_node;
	t_list	*last_node;
	int		i;
	int		n;
	char	*buf;

	n = 0;
	i = 0;
	buf = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_list));
	if (!new_node || !buf)
		return ;
	last_node = ft_lstlast(*list);
	while (last_node -> content[i] && last_node -> content[i] != '\n')
		i++;
	while (last_node -> content[i])
		buf[n++] = last_node -> content[++i];
	buf[n] = '\0';
	new_node -> content = buf;
	new_node -> next = NULL;
	ft_lstclear(list, new_node, buf);
}

char	*get_line(t_list *list)
{
	int		len;
	char	*next_str;

	if (!list)
	{
		free(list);
		list = NULL;
		return (NULL);
	}
	len = len_to_nline(list);
	next_str = malloc(len + 1);
	if (!next_str)
		return (NULL);
	str_cpy(list, next_str);
	return (next_str);
}

void	ft_lstjoin(t_list **list, int fd, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	last_node = ft_lstlast(list[fd]);
	if (!new_node)
		return ;
	if (!last_node)
		list[fd] = new_node;
	else
		last_node -> next = new_node;
	new_node -> content = buf;
	new_node -> next = NULL;
}

void	new_lst(t_list **list, int fd)
{
	ssize_t		len;
	char		*buf;

	while (!find_newline(list[fd]))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		len = read(fd, buf, BUFFER_SIZE);
		if (!len)
		{
			free(buf);
			return ;
		}
		buf[len] = '\0';
		ft_lstjoin(list, fd, buf);
	}
}

char	*get_next_line(int fd)
{
	char			*the_line;
	static t_list	*list[4096];

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (list[fd])
		{
			free(list[fd]-> content);
			list[fd]-> content = NULL;
		}
		free(list[fd]);
		list[fd] = NULL;
		return (NULL);
	}
	new_lst(list, fd);
	if (!list[fd])
		return (NULL);
	the_line = get_line(list[fd]);
	cleanup(&list[fd]);
	return (the_line);
}
