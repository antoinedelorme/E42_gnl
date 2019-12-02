/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelorme <adelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:41:18 by adelorme          #+#    #+#             */
/*   Updated: 2019/12/02 13:13:53 by adelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static int	test_line(t_data *data)
{
	size_t i;

	i = data->nxt;
	while (i < data->size)
	{
		if (data->cnt[i] == '\n' || data->cnt[i] == 26)
		{
			data->nxt = i;
			return (1);
		}
		i++;
	}
	if (data->eof)
		data->nxt = data->size;
	return (0);
}

static int	extract(char **line, t_data **dt, int flag)
{
	char	*tp;
	int		result;

	result = ((*dt)->size == 0) ? 0 : 1;
	if (result || !(*dt)->eof)
	{
		tp = ft_strnew((*dt)->nxt - (*dt)->pos);
		(*dt)->error = tp ? (*dt)->error : 1;
		if (!(*dt)->error)
		{
			ft_memmove(tp, ((*dt)->cnt + (*dt)->pos), (*dt)->nxt - (*dt)->pos);
			(*dt)->pos = (*dt)->pos + (*dt)->nxt - (*dt)->pos + 1;
			*line = tp;
			(*dt)->nxt = (*dt)->pos;
			test_line(*dt);
		}
	}
	if (flag || (*dt)->error)
	{
		result = (*dt)->error ? -1 : result;
		ft_strdel(&(*dt)->cnt);
		ft_memdel((void **)dt);
	}
	return (result);
}

static int	append(t_data **dest, char *buf, size_t size)
{
	char *cnt;

	if (!(cnt = (char *)malloc(sizeof(char) * (size + (*dest)->size))))
	{
		(*dest)->error = 1;
		return (0);
	}
	ft_memmove(cnt, (*dest)->cnt, (*dest)->size);
	ft_memmove(cnt + (*dest)->size, buf, size);
	(*dest)->size = (*dest)->size + size;
	if ((*dest)->cnt)
		ft_strdel((&((*dest)->cnt)));
	(*dest)->cnt = cnt;
	return (1);
}

static int	clean_cnt(t_data **data)
{
	char	*tp;
	size_t	new_size;

	if (!(*data) && !(*data = (t_data *)ft_memalloc(sizeof(t_data))))
		return (0);
	if ((*data)->pos == (*data)->nxt)
	{
		new_size = (*data)->size - (*data)->nxt;
		if ((tp = ft_strnew(new_size)))
		{
			ft_memmove(tp, ((*data)->cnt + (*data)->nxt), new_size);
			ft_strdel(&((*data)->cnt));
			(*data)->cnt = tp;
			(*data)->pos = 0;
			(*data)->nxt = 0;
			(*data)->size = new_size;
			return (1);
		}
	}
	ft_strdel(&((*data)->cnt));
	ft_memdel((void **)data);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE];
	ssize_t			read_size;
	static t_data	*lb;
	int				flag;

	if (!lb || lb->pos == lb->nxt)
	{
		if (!clean_cnt(&lb))
			return (-1);
		while (!test_line(lb) && !lb->eof && !lb->error)
		{
			read_size = read(fd, buff, BUFF_SIZE);
			lb->error = (read_size == -1) ? 1 : lb->error;
			if ((lb->eof = (read_size < BUFF_SIZE) ? 1 : 0))
				test_line(lb);
			if (!append(&lb, buff, read_size) || lb->error)
			{
				ft_strdel(&(lb->cnt));
				ft_memdel((void **)&lb);
				return (-1);
			}
		}
	}
	flag = (lb->size == lb->nxt);
	return (extract(line, &lb, flag));
}
