/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsong <ilsong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:26:59 by ilsong            #+#    #+#             */
/*   Updated: 2021/01/19 00:06:08 by ilsong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	free(subline);
	subline = NULL;
	return (join);
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
	int				rlen;
	static	char	*sub_line[OPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || OPEN_MAX < fd || !line)
		return (-1);
	while ((rlen = read(fd, buff, BUFFER_SIZE)) && rlen != -1
		&& !ft_strchr(buff, '\n', rlen))
		sub_line[fd] = ft_mkline(sub_line[fd], buff, rlen);
	if (rlen == -1)
		return (-1);
	sub_line[fd] = ft_mkline(sub_line[fd], buff, rlen);
	*line = ft_strdup(sub_line[fd]);
	nl_loc = ft_strchr(sub_line[fd], '\n', -1);
	ft_delline(sub_line[fd], nl_loc);
	if (rlen < BUFFER_SIZE && !nl_loc)
	{
		free(sub_line[fd]);
		sub_line[fd] = NULL;
		return (0);
	}
	return (1);
}
