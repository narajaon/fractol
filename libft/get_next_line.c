/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 09:19:28 by narajaon          #+#    #+#             */
/*   Updated: 2017/05/28 15:59:29 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		clr_loop(char *current, char **full, char **tmp)
{
	ft_strclr(current);
	ft_strdel(full);
	*full = ft_strdup(*tmp);
	ft_strdel(tmp);
}

static t_line	*init_clr(t_line *line_s,
		char *to_free, char **line, int command)
{
	if (command == 0)
	{
		if (!(FULL = (OUT == 1) ? FULL : ft_strnew(1)))
			return (NULL);
	}
	else
	{
		if (!(*line = ft_strdup(FULL)))
			return (NULL);
		ft_strdel(&to_free);
		ft_strdel(&FULL);
	}
	OUT = 0;
	return (line_s);
}

static int		format(t_line *line_s, char **line, char *to_free)
{
	char	*tmp;
	int		i;

	i = 0;
	(to_free) ? ft_strdel(&to_free) : to_free;
	while (FULL[i] && FULL[i] != '\n')
		i++;
	tmp = ft_strsub(FULL, 0, i);
	*line = ft_strdup(tmp);
	FULL = ft_memmove(FULL, &FULL[i + 1], ft_strlen(FULL));
	if (!(tmp || *line))
		return (-1);
	ft_strdel(&tmp);
	return (OUT = 1);
}

int				get_next_line(int fd, char **line)
{
	static t_line	*line_s;
	char			*tmp;
	char			*current;

	line_s = (line_s) ? line_s : (t_line *)malloc(sizeof(t_line));
	if (!line || fd < 0 || !(line_s = init_clr(line_s, (void *)0, line, 0)))
		return (-1);
	if (ft_strchr(FULL, '\n'))
		return (format(line_s, line, (void *)0));
	current = ft_strnew(BUFF_SIZE);
	while (((RET = read(fd, current, BUFF_SIZE)) > 0))
	{
		if (((RET < BUFF_SIZE) && current[RET - 1] != '\n'))
			current[RET] = '\n';
		if (!(tmp = ft_strjoin(FULL, current)) || !(current))
			return (-1);
		clr_loop(current, &FULL, &tmp);
		if (ft_strchr(FULL, '\n'))
			return (format(line_s, line, current));
	}
	if (!ft_strchr(FULL, '\n') && ft_strcmp(FULL, "\0") && RET == 0)
		return (format(line_s, line, (void *)0));
	if (!(line_s = init_clr(line_s, current, line, 1)) || !(FULL || current))
		return (-1);
	return (RET);
}
