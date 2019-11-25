/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelorme <adelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:16:00 by adelorme          #+#    #+#             */
/*   Updated: 2019/11/25 14:21:29 by adelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000
# include <string.h>

typedef	struct		s_data
{
	char			*content;
	size_t			size;
	size_t			position;
	size_t			offset;
	int				eof;
}					t_data;

int					get_next_line(const int fd, char **line);
#endif
