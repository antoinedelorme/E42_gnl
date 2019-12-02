/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:14:40 by adelorme          #+#    #+#             */
/*   Updated: 2019/12/02 13:18:11 by adelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <strings.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 2

typedef struct	s_data
{
	char	*cnt;
	size_t	pos;
	size_t	nxt;
	size_t	size;
	int		error;
	int		eof;
}				t_data;

int				get_next_line(const int fd, char **line);
#endif
