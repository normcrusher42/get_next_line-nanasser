/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:44:02 by nanasser          #+#    #+#             */
/*   Updated: 2025/02/22 18:19:57 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, t_list *new_node, char *buf);
int		find_newline(t_list *list);
void	new_lst(t_list **list, int fd);
void	ft_lstjoin(t_list **list, int fd, char *buf);
int		len_to_nline(t_list *list);
char	*get_line(t_list *list);
void	str_cpy(t_list *list, char *str);
void	cleanup(t_list **list);

#endif