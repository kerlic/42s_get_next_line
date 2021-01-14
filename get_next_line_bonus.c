/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsong <ilsong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:26:59 by ilsong            #+#    #+#             */
/*   Updated: 2021/01/15 01:37:24 by ilsong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_freeline(char *line, int rlen)
{
	char	*temp;

	temp = line;
	while (*line && --rlen)
		*line++ = '\0';
	if (*temp)
		free(temp);
	temp = NULL;
	return ;
}

void	ft_delline(char *subline, char *nl_loc)
{
	if (!subline || !nl_loc)
		return ;
	nl_loc++;
	while (*nl_loc)
		*subline++ = *nl_loc++;
	*subline = '\0';
	return ;
}

char	*ft_mkline(char *subline, char *buff, int rlen)
{
	char	*join;

	if (rlen == -1)
		return (NULL);
	if (subline == NULL)
	{
		subline = (char *)malloc(sizeof(char) * 1);
		*subline = '\0';
	}
	buff[rlen] = 0;
	join = ft_strjoin(subline, buff);
	*subline = 0;
	free(subline);
	subline = join;
	return (subline);
}

char	*ft_strdup(char *s)
{
	char	*buff;
	char	*ptr;
	size_t	slen;

	slen = 0;
	while (s[slen] != '\n' && s[slen])
		slen++;
	if (!(buff = (char *)malloc(sizeof(char) * (slen + 1))))
		return (0);
	ptr = buff;
	while (*s)
	{
		if (*s == '\n')
			break ;
		*buff++ = *s++;
	}
	*buff = '\0';
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	char			*nl_loc;
	size_t			rlen;
	static	char	*sub_line[OPEN_MAX];

	**line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || OPEN_MAX < fd || !line)
		return (-1);
	while ((rlen = read(fd, buff, BUFFER_SIZE)) && !(ft_strchr(buff, '\n')))
		sub_line[fd] = ft_mkline(sub_line[fd], buff, rlen);
	if (rlen == -1)
		return (-1);
	sub_line[fd] = ft_mkline(sub_line[fd], buff, rlen);
	*line = ft_strdup(sub_line[fd]);
	printf("%d ::: %s", fd, line);
	nl_loc = ft_strchr(sub_line[fd], '\n');
	ft_delline(sub_line[fd], nl_loc);
	if (!rlen && !nl_loc)
	{
		ft_freeline(sub_line[fd], rlen);
		return (0);
	}
	return (1);
}
