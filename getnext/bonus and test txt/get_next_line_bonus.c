/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:04:27 by iniska            #+#    #+#             */
/*   Updated: 2023/12/12 09:32:21 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	clean_list(t_list **list)
{
	t_list	*last_line;
	t_list	*new_line;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	new_line = malloc(sizeof(t_list));
	if (new_line == NULL)
		return (free(buf), -1);
	last_line = find_last_line(*list);
	i = 0;
	k = 0;
	while (last_line->s_line[i] && last_line->s_line[i] != '\n')
		i++;
	while (last_line->s_line[i] && last_line->s_line[i++])
		buf[k++] = last_line->s_line[i];
	buf[k] = '\0';
	new_line->s_line = buf;
	new_line->next = NULL;
	setitfree(list, new_line, buf);
	return (0);
}

void	copy_line(t_list *list, char *str)
{
	int	i;
	int	k;

	if (list == NULL)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->s_line[i] && i < BUFFER_SIZE)
		{
			if (list->s_line[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->s_line[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

char	*save_line(t_list *list)
{
	int		str_len;
	char	*str;

	if (list == NULL)
		return (NULL);
	str_len = size_of_line(list);
	str = malloc(str_len + 1);
	if (str == NULL)
		return (NULL);
	copy_line(list, str);
	return (str);
}

int	create_line(t_list **list, int fd)
{
	int		char_read;
	char	*line;

	while (!look_slash_n(list[fd]))
	{
		line = malloc(BUFFER_SIZE + 1);
		if (line == NULL)
			return (-1);
		char_read = read(fd, line, BUFFER_SIZE);
		if (char_read < 0)
			return (free(line), -1);
		if (char_read == 0)
			return (free(line), 0);
		line[char_read] = '\0';
		if (list_the_line(list, line, fd) < 0)
			return (free(line), -1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*nextline;
	int				status;

	if (fd < 0 || (BUFFER_SIZE <= 0) || fd > 4096)
		return (NULL);
	status = create_line(list, fd);
	if (!list[fd] || status < 0)
		return (setitfree(&list[fd], 0, 0), NULL);
	nextline = save_line(list[fd]);
	if (nextline == NULL)
		return (setitfree(&list[fd], 0, 0), NULL);
	status = clean_list(&list[fd]);
	if (status < 0)
		return (free(nextline), setitfree(&list[fd], 0, 0), NULL);
	return (nextline);
}

/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1, fd2, fd3;
    char *line;

    // Open the first file
    fd1 = open("cats.txt", O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening file1");
        return 1;
    }

    // Open the second file
    fd2 = open("testytest.txt", O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening file2");
        close(fd1);
        return 1;
    }

    // Open the third file
    fd3 = open("onemore.txt", O_RDONLY);
    if (fd3 == -1) {
        perror("Error opening file3");
        close(fd1);
        close(fd2);
        return 1;
    }

    // Read and print lines from each file
    while ((line = get_next_line(fd1)) || (line = get_next_line(fd2)) || (line = get_next_line(fd3))) {
        if (line != NULL) {
            printf("File 1: %s\n", line);
            free(line);
        }

        if ((line = get_next_line(fd2)) != NULL) {
            printf("File 2: %s\n", line);
            free(line);
        }

        if ((line = get_next_line(fd3)) != NULL) {
            printf("File 3: %s\n", line);
            free(line);
        }
    }

    // Close the file descriptors
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
*/