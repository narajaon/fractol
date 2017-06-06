/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 09:20:17 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/06 16:27:59 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4024
# include "libft.h"
# define RET line_s->ret
# define FULL line_s->full
# define OUT line_s->out

typedef struct	s_line
{
	char		*full;
	int			ret;
	int			out;
}				t_line;

int				get_next_line(const int fd, char **line);
#endif
