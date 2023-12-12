/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h 	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:49:15 by iniska            #+#    #+#             */
/*   Updated: 2023/12/12 09:29:10 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*s_line;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	setitfree(t_list **list, t_list *clean_line, char *buf);
t_list	*find_last_line(t_list *list);
int		size_of_line(t_list *list);
int		list_the_line(t_list **list, char *line, int fd);
int		look_slash_n(t_list *list);
int		create_line(t_list **list, int fd);
char	*save_line(t_list *list);
void	copy_line(t_list *list, char *str);
int		clean_list(t_list **list);

#endif
