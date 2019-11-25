/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelorme <adelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:29:26 by adelorme          #+#    #+#             */
/*   Updated: 2019/11/25 13:40:28 by adelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		test_line(char *line, size_t nb, size_t *offset, t_data *largebuffer)
{
	size_t			i;

	i = *offset;
	while (i < (nb > largebuffer->size ? nb : largebuffer->size))
	{
		if (line[i] == '\n' || line[i] == 26)
		{
			*offset = i;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*extract(t_data *data)
{
	char			*result;
	size_t			size;

	size = data->offset - data->position;
	result = ft_strnew(size);
	ft_memmove(result, (data->content + data->position), size);
	data->position = data->position + size + 1;
	data->offset = data->position;
	return (result);
}

int		append_init(t_data **dest, char *buf, size_t size, int mode)
{
	char			*content;

	if (size == 0 && mode == 0)
		return (0);
	if (mode == 1)
	{
		if (!(*dest = (t_data *)ft_memalloc(sizeof(t_data))))
			return (-1);
		(*dest)->position = 0;
		(*dest)->offset = 0;
		(*dest)->size = 0;
		(*dest)->eof = 0;
		(*dest)->content = NULL;
		return (1);
	}
	if (!(content = (char*)ft_memalloc(sizeof(char) * (size + (*dest)->size))))
		return (-1);
	ft_memmove(content, (*dest)->content, (*dest)->size);
	ft_memmove(content + (*dest)->size, buf, size);
	(*dest)->size = (*dest)->size + size;
	ft_strdel((char **)(&((*dest)->content)));
	(*dest)->content = content;
	return (0);
}

int		clean_content(t_data *data)
{
	char			*temp;
	size_t			new_size;

	if (data->offset < data->size || data->size == 0)
		return (1);
	if (data->eof)
	{
		ft_strdel((char **)(&(data->content)));
		ft_memdel((void *)&data);
		return (0);
	}
	new_size = data->size - data->offset;
	if ((temp = ft_strnew(new_size)) == NULL)
		return (-1);
	ft_memmove(temp, (data->content + data->offset + 1), new_size);
	ft_strdel((char **)(&(data->content)));
	data->content = temp;
	data->position = 0;
	data->offset = 0;
	data->size = new_size;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE];
	ssize_t			read_size;
	static t_data	*lb;
	int				status;

	if (!lb)
		if ((append_init(&lb, buff, 0, 1) == -1))
			return (-1);
	while (!lb->eof && !test_line(lb->content, lb->size, &(lb->offset), lb))
	{
		if ((read_size = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		lb->eof = (read_size == 0) ? 1 : 0;
		if ((append_init(&lb, buff, read_size, 0) == -1))
			return (-1);
	}
	if ((status = clean_content(lb)) != 1)
		return (status);
	if (lb->eof)
		lb->offset = lb->size;
	*line = extract(lb);
	return (1);
}
